/****************************************************************************
  This file is part of LoLA.

  LoLA is free software: you can redistribute it and/or modify it under the
  terms of the GNU Affero General Public License as published by the Free
  Software Foundation, either version 3 of the License, or (at your option)
  any later version.

  LoLA is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
  FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
  more details.

  You should have received a copy of the GNU Affero General Public License
  along with LoLA. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#include <config.h>
#include <CoverGraph/CoverPayload.h>
#include <Exploration/CTLExploration.h>
#include <Exploration/ChooseTransition.h>
#include <Exploration/ChooseTransitionHashDriven.h>
#include <Exploration/ChooseTransitionRandomly.h>
#include <Exploration/DFSExploration.h>
#include <Exploration/DeadlockExploration.h>
#include <Exploration/TSCCExploration.h>
#include <Exploration/Firelist.h>
#include <Exploration/FirelistStubbornDeadlock.h>
#include <Exploration/FirelistStubbornTscc.h>
#include <Exploration/FirelistStubbornDeletion.h>
#include <Exploration/FirelistStubbornStatePredicate.h>
#include <Exploration/LTLExploration.h>
#include <Exploration/ParallelExploration.h>
#include <Exploration/SimpleProperty.h>
#include <Exploration/StatePredicateProperty.h>
#include <Formula/LTL/BuechiFromLTL.h>
#include <Formula/StatePredicate/AtomicStatePredicate.h>
#include <Formula/StatePredicate/ConjunctionStatePredicate.h>
#include <Formula/StatePredicate/DisjunctionStatePredicate.h>
#include <Formula/StatePredicate/StatePredicate.h>
#include <Formula/StatePredicate/TruePredicate.h>
#include <Frontend/Parser/ast-system-k.h>
#include <Frontend/Parser/ast-system-rk.h>
#include <Frontend/Parser/ast-system-unpk.h>
#include <Frontend/SymbolTable/SymbolTable.h>
#include <InputOutput/InputOutput.h>
#include <Net/Marking.h>
#include <Net/Net.h>
#include <Net/NetState.h>
#include <Net/Transition.h>
#include <Planning/Task.h>
#include <Stores/Store.h>
#include <SweepLine/SweepEmptyStore.h>
#include <Witness/Path.h>

#include <errno.h>
#include <sstream>
#include <map>
#include <vector>

// the parsers
extern int ptformula_parse();
extern int ptformula_lex_destroy();
extern int ptbuechi_parse();
extern int ptbuechi_lex_destroy();

// input files
extern FILE *ptformula_in;
extern FILE *ptbuechi_in;

// code to parse from a string
struct yy_buffer_state;
typedef yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE ptformula__scan_string(const char *yy_str);
extern YY_BUFFER_STATE ptbuechi__scan_string(const char *yy_str);

extern SymbolTable *buechiStateTable;
extern FILE *tl_out;

// Kimwitu++ objects
extern kc::tFormula TheFormula;
extern kc::tBuechiAutomata TheBuechi;


/*!
\ingroup g_globals
\todo Is this mapping actually needed or was it this just added for debugging
purposes.
*/
std::map<int, AtomicStatePredicate *> predicateMap;


/// special store creation for stores without payload support (e.g. BloomStore)
template<>
Store<void> *StoreCreator<void>::createSpecializedStore(threadid_t number_of_threads)
{
    NetStateEncoder *enc = 0;
    switch (RT::args.encoder_arg)
    {
    case encoder_arg_bit:
        enc = new BitEncoder(number_of_threads);
        break;
    case encoder_arg_copy:
        enc = new CopyEncoder(number_of_threads);
        break;
    case encoder_arg_simplecompressed:
        enc = new SimpleCompressedEncoder(number_of_threads);
        break;
    case encoder_arg_fullcopy:
        enc = new FullCopyEncoder(number_of_threads);
        break;
    case encoder__NULL:
        assert(false);
    }

    switch (RT::args.store_arg)
    {
    case store_arg_bloom:
        RT::rep->status("using Bloom filter with %lu bit (%lu MB)", (unsigned long)
                        BLOOM_FILTER_SIZE, BLOOM_FILTER_SIZE / 1048576);
        RT::rep->status("using Bloom filter with %d hash functions (%s)",
                        RT::args.hashfunctions_arg,
                        RT::rep->markup(MARKUP_PARAMETER, "--hashfunctions").str());

        if (RT::args.bucketing_given)
        {
            return new PluginStore<void>(enc,
                                         new HashingWrapperStore<void>(new BinaryVectorStoreCreator < void,
                                                 VBloomStore < (unsigned long)  BLOOM_FILTER_SIZE / SIZEOF_MARKINGTABLE + 1 > , arrayindex_t,
                                                 size_t > (number_of_threads, RT::args.hashfunctions_arg)), number_of_threads);
        }
        else
        {
            return new PluginStore<void>(enc,
                                         new VBloomStore<BLOOM_FILTER_SIZE>(number_of_threads,
                                                 RT::args.hashfunctions_arg), number_of_threads);
        }

    default:
        storeCreationError();
        return NULL;
    }
}


Task::Task() :
    formulaType(FORMULA_REACHABLE), spFormula(NULL), ctlFormula(NULL),
    bauto(NULL), p(NULL), fl(NULL), exploration(NULL), ltlExploration(NULL),
    ctlExploration(NULL), ns(NULL), store(NULL), ltlStore(NULL), ctlStore(NULL),
    covStore(NULL), number_of_threads(static_cast<threadid_t>(RT::args.threads_arg))
{
    // process formula

    if (RT::args.formula_given)
    {
        setFormula();
    }
    if (RT::args.buechi_given)
    {
        setBuechiAutomata();
    }

    if (RT::args.check_arg == check_arg_modelchecking)
    {
        if (not RT::args.formula_given and not RT::args.buechi_given)
        {
            RT::rep->message("%s given without %s or %s",
                             RT::rep->markup(MARKUP_PARAMETER, "--check=modelchecking").str(),
                             RT::rep->markup(MARKUP_PARAMETER, "--formula").str(),
                             RT::rep->markup(MARKUP_PARAMETER, "--buechi").str());
            RT::rep->abort(ERROR_COMMANDLINE);
        }
    }

    // set the net
    ns = NetState::createNetStateFromInitial();

    // compute symmetries
    if (RT::args.symmetry_given)
    {
        SymmetryCalculator *SC = NULL;

        if (ctlFormula)
        {
            SC = new SymmetryCalculator(ctlFormula);
        }
        else
        {
            if (spFormula)
            {
                SC = new SymmetryCalculator(spFormula);
            }
            else
            {
                SC = new SymmetryCalculator();
            }
        }

        assert(SC);
        SC->ComputeSymmetries();
        delete SC;
    }

    // prepare task
    setStore();
    setProperty();
}


/*!
\post memory for all members is deallocated
*/
Task::~Task()
{
    // quick exit to avoid lengthy destructor calls
#ifndef USE_PERFORMANCE
    delete ns;
    delete store;
    delete ltlStore;
    delete ctlStore;
    delete covStore;
    delete p;
    delete spFormula;
    delete fl;
    delete exploration;
    delete ltlExploration;
    delete ctlExploration;
    delete bauto;
#endif
}


/* prints the content of a set for spin */
StatePredicate *buildPropertyFromList(int *pos, int *neg)
{
    std::vector<StatePredicate *> subForms;

    // bad hack from library
    int mod = 8 * SIZEOF_INT;

    for (int i = 0; i < sym_size; i++)
    {
        for (int j = 0; j < mod; j++)
        {
            if (pos[i] & (1 << j))
            {
                // the compiler doesn't have a clue which function i mean, so tell him
                if (atoi(sym_table[mod * i + j]) > 1)
                {
                    subForms.push_back(
                        predicateMap[atoi(sym_table[mod * i + j])]->StatePredicate::copy());
                }
            }
            if (neg[i] & (1 << j))
            {
                if (atoi(sym_table[mod * i + j]) > 1)
                {
                    subForms.push_back(predicateMap[atoi(sym_table[mod * i + j])]->negate());
                }
            }
        }
    }

    if (subForms.empty())
    {
        return new TruePredicate();
    }

    ConjunctionStatePredicate *result = new ConjunctionStatePredicate(subForms.size());
    for (arrayindex_t i = 0; i < subForms.size(); i++)
    {
        result->addSub(i, subForms[i]);
    }
    return result;
}


/*
Initialize the members Task::spFormula, Task::ctlFormula, or Task::bauto from a
formula given via the `--formula` command line parameter.

\post Members Task::spFormula, Task::ctlFormula, or Task::bauto are initialized;
they are deallocated by the destructor.
*/
void Task::setFormula()
{
    RT::currentInputFile = NULL;

    // Check if the paramter of --formula is a file that we can open: if that
    // works, parse the file. If not, parse the string.
    FILE *file = fopen(RT::args.formula_arg, "r");
    if (file == NULL and (errno == ENOENT or errno == ENAMETOOLONG))
    {
        // reset error
        errno = 0;
        ptformula__scan_string(RT::args.formula_arg);
    }
    else
    {
        fclose(file);
        RT::currentInputFile = new Input("formula", RT::args.formula_arg);
        ptformula_in = *RT::currentInputFile;
    }

    // parse the formula
    ptformula_parse();

    // output formula as parsed
    unparsed.clear();
    TheFormula->unparse(stringprinter, kc::out);
    if (unparsed.size() < FORMULA_PRINT_SIZE)
    {
        RT::rep->status("read: %s", unparsed.c_str());
    }
    else
    {
        RT::rep->status("read: %s... (shortened)", unparsed.substr(0, FORMULA_PRINT_SIZE).c_str());
    }
    RT::rep->status("formula length: %d", unparsed.size());
    RT::data["analysis"]["formula"]["parsed"] = unparsed;
    RT::data["analysis"]["formula"]["parsed_size"] = static_cast<int>(unparsed.size());

    // restructure the formula:

    // Phase 1: remove syntactic sugar
    TheFormula = TheFormula->rewrite(kc::goodbye_doublearrows);
    TheFormula = TheFormula->rewrite(kc::goodbye_singlearrows);
    TheFormula = TheFormula->rewrite(kc::goodbye_xor);
    TheFormula = TheFormula->rewrite(kc::goodbye_fireable);
    TheFormula = TheFormula->rewrite(kc::goodbye_initial);

    // Phase 2: Normalize atomic propositions
    // - places to left, constants to right
    TheFormula = TheFormula->rewrite(kc::sides);
    // - left side to lists
    TheFormula = TheFormula->rewrite(kc::productlists);
    // - remove == != >= < (<= and > remain)
    TheFormula = TheFormula->rewrite(kc::leq);

    // Phase 3: Apply logical tautologies.
    TheFormula = TheFormula->rewrite(kc::tautology);

    // 4a: detect formula type
    TheFormula->unparse(myprinter, kc::temporal);
    formulaType = TheFormula->type;

    // process the formula according to the type
    switch (formulaType)
    {
    case FORMULA_DEADLOCK:
        RT::rep->status("checking reachability of deadlocks");
        RT::data["analysis"]["formula"]["type"] = "deadlock";
        // set formula to NULL to make deadlock check detectable
        spFormula = NULL;
        return;
    case FORMULA_NODEADLOCK:
        RT::rep->status("checking absence of deadlocks");
        RT::data["analysis"]["formula"]["type"] = "nodeadlock";
        // set formula to NULL to make deadlock check detectable
        spFormula = NULL;
        return;
    case FORMULA_REACHABLE:
        RT::rep->status("checking reachability");
        RT::data["analysis"]["formula"]["type"] = "reachability";
        TheFormula = TheFormula->rewrite(kc::singletemporal);
        TheFormula = TheFormula->rewrite(kc::booleanlists);
        break;
    case FORMULA_INVARIANT:
        RT::rep->status("checking invariance");
        RT::data["analysis"]["formula"]["type"] = "invariance";
        TheFormula = TheFormula->rewrite(kc::singletemporal);
        TheFormula = TheFormula->rewrite(kc::simpleneg);
        TheFormula = TheFormula->rewrite(kc::booleanlists);
        break;
    case FORMULA_LIVENESS:
        RT::rep->status("checking liveness");
        RT::data["analysis"]["formula"]["type"] = "liveness";
        //TODO shouldent this be placed elsewhere?
        if (RT::args.search_arg == search_arg_covergraph)
        {
            TheFormula = TheFormula->rewrite(kc::singletemporal);
            TheFormula = TheFormula->rewrite(kc::booleanlists);
            break;
        }
        else if (!RT::args.tscc_flag)
        {
            formulaType = FORMULA_CTL;
        }

        break;
    case FORMULA_EGAGEF:
        RT::rep->status("checking EGAGEF");
        break;
    case FORMULA_FAIRNESS:
        RT::rep->status("checking fairness");
        RT::data["analysis"]["formula"]["type"] = "fairness";
        RT::rep->status("fairness not yet implemented, converting to LTL...");
        formulaType = FORMULA_LTL;
        break;
    case FORMULA_STABILIZATION:
        RT::rep->status("checking stabilization");
        RT::data["analysis"]["formula"]["type"] = "stabilization";
        RT::rep->status("stabilization not yet implemented, converting to LTL...");
        formulaType = FORMULA_LTL;
        break;
    case FORMULA_EVENTUALLY:
        RT::rep->status("checking eventual occurrence");
        RT::data["analysis"]["formula"]["type"] = "eventual occurrence";
        RT::rep->status("eventual occurrence not yet implemented, converting to LTL...");
        formulaType = FORMULA_LTL;
        break;
    case FORMULA_INITIAL:
        RT::rep->status("checking initial satisfiability");
        RT::data["analysis"]["formula"]["type"] = "initial satisfiability";
        break;
    case FORMULA_LTL:
        RT::rep->status("checking LTL");
        RT::data["analysis"]["formula"]["type"] = "LTL";
        break;
    case FORMULA_CTL:
        RT::rep->status("checking CTL");
        RT::data["analysis"]["formula"]["type"] = "CTL";
        break;
    case FORMULA_MODELCHECKING:
        RT::rep->status("checking CTL*");
        RT::data["analysis"]["formula"]["type"] = "CTL*";
        break;
    }

    RT::rep->status("processing formula");

    // simplify CTL formula to fewer operators
    if (formulaType == FORMULA_CTL)
    {
        // replace path quantor+temporal operator by dedicated CTL operator
        TheFormula = TheFormula->rewrite(kc::ctloperators);
    }

    // output formula as processed
    unparsed.clear();
    TheFormula->unparse(stringprinter, kc::out);
    if (unparsed.size() < FORMULA_PRINT_SIZE)
    {
        RT::rep->status("processed formula: %s", unparsed.c_str());
    }
    else
    {
        RT::rep->status("processed formula: %s... (shortened)", unparsed.substr(0,
                        FORMULA_PRINT_SIZE).c_str());
    }
    RT::rep->status("processed formula length: %d", unparsed.size());
    RT::data["analysis"]["formula"]["processed"] = unparsed;
    RT::data["analysis"]["formula"]["processed_size"] = static_cast<int>(unparsed.size());

    RT::rep->status("%d rewrites", rule_applications);

    // prepare counting of place in the formula
    extern bool *place_in_formula;
    extern unsigned int places_mentioned;
    extern unsigned int unique_places_mentioned;
    place_in_formula = new bool[Net::Card[PL]]();
    places_mentioned = 0;
    unique_places_mentioned = 0;

    switch (formulaType)
    {
    case FORMULA_REACHABLE:
    case FORMULA_INVARIANT:
    case FORMULA_INITIAL:
    case FORMULA_EGAGEF:
    case FORMULA_LIVENESS: // currently only for cover graphs!
    {
        // copy restructured formula into internal data structures
        TheFormula->unparse(myprinter, kc::internal);
        StatePredicate *result = TheFormula->formula;

        assert(result);
        RT::rep->status("processed formula with %d atomic propositions",
                        result->countAtomic());
        RT::data["analysis"]["formula"]["atomic_propositions"] = static_cast<int>(result->countAtomic());

        spFormula = result;
        break;
    }
    case FORMULA_CTL:
    {
        TheFormula->unparse(myprinter, kc::ctl);
        ctlFormula = TheFormula->ctl_formula;

        assert(ctlFormula);
        break;
    }

    // this case is much to long we should capsulate something...
    case FORMULA_LTL:
    {
        RT::rep->message("transforming LTL-Formula into a Büchi-Automaton");
        // extract the Node*
        TheFormula->unparse(myprinter, kc::ltl);

        tl_Node *n = TheFormula->ltl_tree;
        //n = bin_simpler(n);
        assert(n);
        tl_out = stdout;
        trans(n);
        // build the buechi-automation structure needed for LTL model checking
        // put the state predicates
        bauto = new BuechiAutomata();

        // extract the states from the ltl2ba data structures
        if (bstates->nxt == bstates)
        {
            // TODO the search result is FALSE!
            RT::rep->message("Not yet implemented, result FALSE");
            RT::rep->abort(ERROR_COMMANDLINE);
        }

        if (bstates->nxt->nxt == bstates && bstates->nxt->id == 0)
        {
            // TODO the search result is TRUE!
            RT::rep->message("Not yet implemented, result TRUE");
            RT::rep->abort(ERROR_COMMANDLINE);
        }

        bauto->cardStates = 0;
        // map-> final,id
        std::map<int, std::map<int, int > > state_id;
        BState *s;
        BTrans *t;
        for (s = bstates->prv; s != bstates; s = s->prv)
        {
            state_id[s->final][s->id] = bauto->cardStates;
            bauto->cardStates++;
        }

        //RT::rep->message("Buechi-automaton has %d states", bauto->cardStates);
        // now i do know the number of states
        bauto->cardTransitions = new uint32_t[bauto->cardStates]();
        bauto->transitions = new uint32_t **[bauto->cardStates]();
        bauto->cardEnabled = new arrayindex_t[bauto->cardStates]();
        bauto->isStateAccepting = new bool[bauto->cardStates]();

        std::vector<StatePredicate *> neededProperties;
        std::map<StatePredicate *, int> neededProperties_backmap;

        // read out the datastructure
        int curState = -1;
        int curProperty = 0;
        for (s = bstates->prv; s != bstates; s = s->prv)
        {
            curState++;
            if (s->id == 0)
            {
                // build a TRUE-loop
                bauto->isStateAccepting[curState] = true;
                bauto->cardTransitions[curState] = 1;
                bauto->transitions[curState] = new uint32_t *[1]();
                bauto->transitions[curState][0] = new uint32_t[2]();
                bauto->transitions[curState][0][0] = neededProperties.size();
                bauto->transitions[curState][0][1] = curState;
                curProperty++;
                neededProperties.push_back(new TruePredicate());
                neededProperties_backmap[neededProperties.back()] = curState;
                continue;
            }
            if (s->final == accepting_state)
            {
                bauto->isStateAccepting[curState] = true;
            }


            // build the successor list
            bauto->cardTransitions[curState] = 0;
            for (t = s->trans->nxt; t != s->trans; t = t->nxt)
            {
                // now build the property
                std::vector<StatePredicate *> disjunctionproperty;
                disjunctionproperty.push_back(buildPropertyFromList(t->pos, t->neg));
                BTrans *t1;
                for (t1 = t; t1->nxt != s->trans; )
                {
                    if (t1->nxt->to->id == t->to->id && t1->nxt->to->final == t->to->final)
                    {
                        disjunctionproperty.push_back(buildPropertyFromList(t1->nxt->pos,
                                                      t1->nxt->neg));
                        t1->nxt = t1->nxt->nxt;
                    }
                    else
                    {
                        t1 = t1->nxt;
                    }
                }

                if (disjunctionproperty.size() == 1)
                {
                    neededProperties.push_back(disjunctionproperty[0]);
                }
                else
                {
                    DisjunctionStatePredicate *disjucntion = new DisjunctionStatePredicate(
                        disjunctionproperty.size());
                    for (size_t i = 0; i < disjunctionproperty.size(); i++)
                    {
                        disjucntion->addSub(i, disjunctionproperty[i]);
                    }
                    neededProperties.push_back(disjucntion);
                }
                //RT::rep->message("CREATE %d -> %d", neededProperties.size(), curState);
                neededProperties_backmap[neededProperties.back()] = curState;

                // increment number of transitions
                bauto->cardTransitions[curState]++;
            }

            bauto->transitions[curState] = new uint32_t *[bauto->cardTransitions[curState]]();
            int current_on_trans = -1;
            for (t = s->trans->nxt; t != s->trans; t = t->nxt)
            {
                // bauto data structures
                current_on_trans++;
                bauto->transitions[curState][current_on_trans] = new uint32_t[2]();
                //RT::rep->message("Transition %d -> %d", curState, state_id[t->to->final][t->to->id]);
                bauto->transitions[curState][current_on_trans][0] = curProperty++;
                bauto->transitions[curState][current_on_trans][1] =
                    state_id[t->to->final][t->to->id];
                //RT::rep->message("FROM TO %d %d", curState, state_id[t->to->final][t->to->id]);
            }
        }

        //
        // build a list of all needed propositions
        //

        // if the automata contains an all-accepting state
        bauto->cardAtomicPropositions = neededProperties.size();
        bauto->atomicPropositions = new StatePredicateProperty *[bauto->cardAtomicPropositions]();
        bauto->atomicPropotions_backlist = new arrayindex_t[bauto->cardAtomicPropositions]();
        for (size_t i = 0; i < neededProperties.size(); i++)
        {
            bauto->atomicPropositions[i] = new StatePredicateProperty(neededProperties[i]);
            //RT::rep->message("BL %d %d", i, neededProperties_backmap[neededProperties[i]]);
            bauto->atomicPropotions_backlist[i] =
                neededProperties_backmap[neededProperties[i]];
        }

        RT::rep->status("the resulting Büchi automaton has %d states", bauto->getNumberOfStates());
        break;
    }

    default:
        RT::rep->message("check not yet implemented");
        RT::rep->abort(ERROR_COMMANDLINE);
    }

    // tidy parser
    ptformula_lex_destroy();

    delete TheFormula;

    // report places mentioned in the formula and clean up
    RT::rep->status("formula mentions %d of %d places; total mentions: %d",
                    unique_places_mentioned, Net::Card[PL], places_mentioned);
    delete[] place_in_formula;

    RT::data["analysis"]["formula"]["places_mentioned"] = static_cast<int>(places_mentioned);
    RT::data["analysis"]["formula"]["places_mentioned_unique"] = static_cast<int>
            (unique_places_mentioned);

    if (RT::args.formula_given)
    {
        delete RT::currentInputFile;
        RT::currentInputFile = NULL;
    }
}


/*!
Initialize the member Task::bauto from a Büchi automaton given via the `--buchi`
command line parameter.

\post Member Task::bauto is initialized; it is deallocated by the destructor.
*/
void Task::setBuechiAutomata()
{
    RT::currentInputFile = NULL;
    buechiStateTable = new SymbolTable();

    // Check if the paramter of --buechi is a file that we can open: if that
    // works, parse the file. If not, parse the string.
    FILE *file;
    if ((file = fopen(RT::args.buechi_arg, "r")) == NULL and errno == ENOENT)
    {
        // reset error
        errno = 0;
        ptbuechi__scan_string(RT::args.buechi_arg);
    }
    else
    {
        fclose(file);
        RT::currentInputFile = new Input("Buechi", RT::args.buechi_arg);
        ptbuechi_in = *RT::currentInputFile;
    }

    //RT::rep->message("Parsing Büchi-Automaton");
    // parse the formula
    ptbuechi_parse();

    //RT::rep->message("Finished Parsing");

    // restructure the formula: unfold complex constructs and handle negations and tautologies
    TheBuechi = TheBuechi->rewrite(kc::goodbye_doublearrows);
    TheBuechi = TheBuechi->rewrite(kc::goodbye_singlearrows);
    TheBuechi = TheBuechi->rewrite(kc::goodbye_xor);
    TheBuechi = TheBuechi->rewrite(kc::goodbye_fireable);
    TheBuechi = TheBuechi->rewrite(kc::goodbye_initial);
    TheBuechi = TheBuechi->rewrite(kc::goodbye_initial);

    // restructure the formula: again tautoglies and simplification
    TheBuechi = TheBuechi->rewrite(kc::sides);
    TheBuechi = TheBuechi->rewrite(kc::productlists);
    TheBuechi = TheBuechi->rewrite(kc::leq);
    TheBuechi = TheBuechi->rewrite(kc::tautology);

    // expand the transitions rules
    TheBuechi = TheBuechi->rewrite(kc::rbuechi);

    //RT::rep->message("parsed Buechi");
    //TheBuechi->unparse(myprinter, kc::out);

    //RT::rep->message("checking LTL");

    // prepare counting of place in the formula
    extern bool *place_in_formula;
    extern unsigned int places_mentioned;
    extern unsigned int unique_places_mentioned;
    place_in_formula = new bool[Net::Card[PL]]();
    places_mentioned = 0;
    unique_places_mentioned = 0;

    // copy restructured formula into internal data structures
    TheBuechi->unparse(myprinter, kc::buechi);
    bauto = TheBuechi->automata;
    // XXX: this _must_ work according to the kimwitu docu, but it does not, kimwitu produces memory leaks!
    //TODO: this makes buechi LTL checks segfaulting in some cases ( now leakes
    //memory (we have to take a closer look)
    //TheBuechi->free(true);
    //delete TheBuechi;
    delete buechiStateTable;

    //RT::rep->message("Processed Büchi-Automaton");

    // report places mentioned in the formula and clean up
    RT::rep->status("formula mentions %d of %d places; total mentions: %d",
                    unique_places_mentioned, Net::Card[PL], places_mentioned);
    delete[] place_in_formula;

    // tidy parser
    ptbuechi_lex_destroy();
    //delete TheFormula;

    if (RT::args.buechi_given)
    {
        delete RT::currentInputFile;
        RT::currentInputFile = NULL;
    }

    // reading the buechi automata
    assert(bauto);
}


/*!
Sets the store for the state exploration. It uses StoreCreator::createStore and
the command-line parameters to choose the store and whether it is assigned to
the member Task::store, Task::ctlStore, or Task::ltlStore

\post a Store object is allocated for member Task::store, Task::ctlStore, or
Task::ltlStore using StoreCreator::createStore according to the command-line
parameters; it is deallocated by the destructor.

\todo The members Task::store, Task::ctlStore, or Task::ltlStore should be
combined.
*/
void Task::setStore()
{
    // set some global information on all stores
    RT::data["store"]["bucketing"] = static_cast<int>(RT::args.bucketing_arg);
    RT::data["store"]["threads"] = static_cast<int>(RT::args.threads_arg);

    // information about the limits
    if (RT::args.timelimit_arg != 0)
    {
        RT::data["limits"]["time"] = static_cast<int>(RT::args.timelimit_arg);
    }
    else
    {
        RT::data["limits"]["time"] = JSON::null;
    }

    if (RT::args.markinglimit_arg != 0)
    {
        RT::data["limits"]["markings"] = static_cast<int>(RT::args.markinglimit_arg);
    }
    else
    {
        RT::data["limits"]["markings"] = JSON::null;
    }

    switch (RT::args.search_arg)
    {
    case search_arg_findpath:
    {
        RT::data["store"]["type"] = "empty";
        RT::data["store"]["search"] = "findpath";
        store = new EmptyStore<void>(number_of_threads);
        break;
    }
    case search_arg_sweepline:
    {
        // dummy store for the sweepline method, only counts markings and calls
        RT::data["store"]["type"] = "empty";
        RT::data["store"]["search"] = "sweepline";
        store = new SweepEmptyStore();
        break;
    }
    case search_arg_covergraph:
    {
        RT::data["store"]["search"] = "covergraph";
        if (RT::args.encoder_arg != encoder_arg_fullcopy)
        {
            RT::rep->status("warning: encoder does not fully support coverability graphs");
        }
        covStore = StoreCreator<CoverPayload>::createStore(number_of_threads);
        break;
    }
    case search_arg_depth:
    {
        RT::data["store"]["search"] = "depth_first_search";

        // choose a store
        if (bauto)
        {
            ltlStore = StoreCreator<AutomataTree *>::createStore(number_of_threads);
        }
        else if (ctlFormula)
        {
            ctlStore = StoreCreator<void *>::createStore(number_of_threads);
        }
        else
        {
            if (RT::args.tscc_flag)
            {
                tsccStore = StoreCreator<statenumber_t>::createStore(number_of_threads);
            }
            else
            {
                store = StoreCreator<void>::createStore(number_of_threads);
            }
        }
        break;
    }
    case search__NULL:
        assert(false);
    }
}


/*!
Sets the property (simple property, deadlock, or state predicate), firelist
(used stubborn sets) and exploration method (depth first, CTL, LTL, or parallel
exploration).

\post Members Task::p, Task::fl, Task::exploration, Task::ctlExploration, and
Task::ltlExploration are initialized; memory is deallocated by the destructor.

\todo DFSExploration, LTLExploration, and CTLExploration should have a common
parent class "Exploration". This would avoid multiple members Task::exploration,
Task::ctlExploration, and Task::ltlExploration.
*/
void Task::setProperty()
{
    // choose a simple property
    switch (RT::args.check_arg)
    {
    case check_arg_full:
        RT::rep->status("building the complete state space (%s)",
                        RT::rep->markup(MARKUP_PARAMETER, "--check=full").str());
        RT::data["analysis"]["type"] = "full";
        p = new SimpleProperty();
        fl = new Firelist();
        if (RT::args.tscc_flag)
        {
            if (formulaType == FORMULA_LIVENESS)
            {
                tsccExploration = new TSCCExplorationAGEF();
            }
            else if (formulaType == FORMULA_EGAGEF )
            {
                tsccExploration = new TSCCExplorationEGAGEF();
            }
            assert(spFormula);
            p = new StatePredicateProperty(spFormula);
            fl = new FirelistStubbornTscc(p);
        }
        break;

    case check_arg_modelchecking:
        RT::rep->status("checking a formula (%s)",
                        RT::rep->markup(MARKUP_PARAMETER, "--check=modelchecking").str());
        RT::data["analysis"]["type"] = "modelchecking";
        if (bauto)
        {
            fl = new Firelist();
        }
        else if (ctlFormula)
        {
            fl = new Firelist();
        }
        else if (spFormula)
        {
            p = new StatePredicateProperty(spFormula);
            if (RT::args.stubborn_arg == stubborn_arg_deletion)
            {
                fl = new FirelistStubbornDeletion(spFormula);
            }
            else
            {
                fl = new FirelistStubbornStatePredicate(spFormula);
            }
        }
        else
        {
            // if spFormula == NULL, check for deadlocks
            p = new DeadlockExploration();
            if (RT::args.stubborn_arg == stubborn_arg_deletion)
            {
                fl = new FirelistStubbornDeletion();
            }
            else
            {
                fl = new FirelistStubbornDeadlock();
            }
        }
        break;

    case check__NULL:
    case check_arg_none:
        RT::rep->status("checking nothing (%s)",
                        RT::rep->markup(MARKUP_PARAMETER, "--check=none").str());
        RT::data["analysis"]["type"] = "none";
        break;
    }


    // set the correct exploration algorithm
    switch (RT::args.check_arg)
    {
    case check_arg_full:
    case check_arg_modelchecking:
        if (ctlFormula)
        {
            ctlExploration = new CTLExploration();
        }
        else if (bauto)
        {
            ltlExploration = new LTLExploration(RT::args.ltlmode_arg == ltlmode_arg_tree);
        }
        else     // state predicate checking
        {
            if (number_of_threads == 1)
            {
                exploration = new DFSExploration();
            }
            else
            {
                exploration = new ParallelExploration();
            }
        }
        break;

    case check__NULL:
    case check_arg_none:
        break;
    }
}


/*!
This method starts the actual state space exploration and returns the raw
result.

\return the result of the state exploration
\note This result needs to be interpreted by Task::interpreteResult.
*/
ternary_t Task::getResult()
{
    //TODO can we make these assumptions clearer that the asserts are creating
    assert(ns);
    assert(!ctlFormula || ctlStore); //ctlFormula ==> ctlStore
    assert(!bauto || ltlStore); //bauto ==> ltlStore
    assert(ctlFormula || bauto || store || covStore || tsccStore);
    assert(!ctlFormula || ctlExploration);
    assert(!bauto || ltlExploration); //bauto ==> ltlExploration
    assert(ctlFormula || bauto || exploration);
    assert(ctlFormula || bauto || p);
    assert(fl);

    bool bool_result(false);
    ternary_t result(TERNARY_FALSE);
    if (ctlFormula)
    {
        bool_result = ctlExploration->checkProperty(ctlFormula, *ctlStore, *fl, *ns);
    }
    else if (bauto)
    {
        bool_result = ltlExploration->checkProperty(*bauto, *ltlStore, *fl, *ns);
    }
    else
    {
        if (formulaType == FORMULA_INITIAL)
        {
            bool_result = p->initProperty(*ns);
        }
        else
        {
            //TODO remove this when tscc is included to the frontend
            if (RT::args.tscc_flag)
            {
                bool_result = tsccExploration->depth_first(*p, *ns, *tsccStore, *fl, number_of_threads);
            }
            else
            {
                switch (RT::args.search_arg)
                {
                case search_arg_depth:
                    bool_result = exploration->depth_first(*p, *ns, *store, *fl, number_of_threads);
                    break;

                case search_arg_findpath:
                    RT::rep->status("starting randomized, memory-less exploration (%s)",
                                    RT::rep->markup(MARKUP_PARAMETER, "--search=findpath").str());

                    RT::rep->status("searching for paths with maximal depth %d (%s)",
                                    RT::args.depthlimit_arg,
                                    RT::rep->markup(MARKUP_PARAMETER, "--depthlimit").str());

                    if (RT::args.retrylimit_arg == 0)
                    {
                        RT::rep->status("no retry limit given (%s)",
                                        RT::rep->markup(MARKUP_PARAMETER, "--retrylimit").str());
                    }
                    else
                    {
                        RT::rep->status("restarting search at most %d times (%s)",
                                        RT::args.retrylimit_arg,
                                        RT::rep->markup(MARKUP_PARAMETER, "--retrylimit").str());
                    }

                    // added a scope to allow a local definition of choose
                    {
                        ChooseTransition *choose = NULL;
                        if (formulaType == FORMULA_DEADLOCK or formulaType == FORMULA_NODEADLOCK)
                        {
                            RT::rep->status("transitions are chosen randomly");
                            choose = new ChooseTransitionRandomly();
                        }
                        else
                        {
                            RT::rep->status("transitions are chosen hash-driven");
                            choose = new ChooseTransitionHashDriven();
                        }
                        bool_result = exploration->find_path(*p, *ns, RT::args.retrylimit_arg,
                                                             RT::args.depthlimit_arg, *fl, *((EmptyStore<void> *)store), *choose);
                        delete choose;
                    }
                    break;

                case search_arg_sweepline:
                    RT::rep->status("using sweepline method (%s)", RT::rep->markup(MARKUP_PARAMETER,
                                    "--search=sweepline").str());
                    // no choice of stores for sweepline method here
                    bool_result = exploration->sweepline(*p, *ns, *reinterpret_cast<SweepEmptyStore *>(store), *fl,
                                                         RT::args.sweepfronts_arg, number_of_threads);
                    break;

                case search_arg_covergraph:
                    RT::rep->status("using coverability graph (%s)", RT::rep->markup(MARKUP_PARAMETER,
                                    "--search=cover").str());

                    result = exploration->cover_breadth_first(*p, *ns, *covStore, *fl, number_of_threads, formulaType);
                    break;

                default:
                    assert(false);
                }
            }
        }
    }

    // temporary result transfer, as long as the variable bool_result is needed
    if (bool_result)
    {
        result = TERNARY_TRUE;
    }

    return result;
}


/*!
\post The result is interpreted and printed using Reporter::message
\warning This method must not be called more than once.

\todo This method should be internal and automatically be called by
Task::getResult after the result was calculated. Then, a member of type
trinary_t can be displayed.
*/
void Task::interpreteResult(ternary_t result)
{
    if (RT::args.store_arg == store_arg_bloom)
    {
        const double n = static_cast<double>(getMarkingCount());
        const double k = RT::args.hashfunctions_arg;
        const double m = static_cast<double>(BLOOM_FILTER_SIZE);
        RT::rep->status("Bloom filter: probability of false positive is %.10lf",
                        pow((1.0 - exp((-k * n) / m)), k));
        RT::rep->status("Bloom filter: optimal number of hash functions is %.1f",
                        log(m / n) / log(2.0));
    }

    // in case AG is used, the result needs to be negated
    if (RT::args.formula_given)
        if (formulaType == FORMULA_INVARIANT || formulaType == FORMULA_LTL
                || formulaType == FORMULA_NODEADLOCK)
        {
            if (result == TERNARY_TRUE)
            {
                result = TERNARY_FALSE;
            }
            else if (result == TERNARY_FALSE)
            {
                result = TERNARY_TRUE;
            }
        }

    // if the Bloom store did not find anything, the result is unknown
    if (RT::args.store_arg == store_arg_bloom)
    {
        switch (RT::args.check_arg)
        {
        case check_arg_modelchecking:
            if (result == TERNARY_FALSE)
            {
                result = TERNARY_UNKNOWN;
            }
            break;

        case check__NULL:
        case check_arg_none:
        case check_arg_full:
            break;
        }
    }

    // in case findpath did not find a result, we cannot be sure
    if (RT::args.search_arg == search_arg_findpath)
    {
        if (result == TERNARY_FALSE)
        {
            result = TERNARY_UNKNOWN;
        }
    }

    switch (result)
    {
    case TERNARY_TRUE:
        RT::rep->status("result: %s", RT::rep->markup(MARKUP_GOOD, "yes").str());
        RT::data["analysis"]["result"] = true;

        switch (RT::args.check_arg)
        {
        case check_arg_modelchecking:
            RT::rep->status("%s", RT::rep->markup(MARKUP_GOOD, "The net satisfies the given formula.").str());
            break;
        default:
            break; // cannot happen - only to silence compiler  LCOV_EXCL_LINE
        }

        break;

    case TERNARY_FALSE:
        RT::rep->status("result: %s", RT::rep->markup(MARKUP_BAD, "no").str());
        RT::data["analysis"]["result"] = false;

        switch (RT::args.check_arg)
        {
        case check_arg_modelchecking:
            RT::rep->status("%s", RT::rep->markup(MARKUP_BAD,
                                                  "The net does not satisfy the given formula.").str());
            break;
        default:
            break; // cannot happen - only to silence compiler  LCOV_EXCL_LINE
        }

        break;

    case TERNARY_UNKNOWN:
        RT::rep->status("result: %s", RT::rep->markup(MARKUP_WARNING, "unknown").str());
        RT::data["analysis"]["result"] = JSON::null;

        switch (RT::args.check_arg)
        {
        case check_arg_modelchecking:
            RT::rep->status("%s", RT::rep->markup(MARKUP_WARNING,
                                                  "The net may or may not satisfy the given formula.").str());
            break;
        default:
            break; // cannot happen - only to silence compiler  LCOV_EXCL_LINE
        }

        break;
    }
}


Path Task::getWitnessPath() const
{
    if (ctlFormula)
    {
        // CTL
        return ctlExploration->path();
    }
    else if (bauto)
    {
        // LTL
        return ltlExploration->path();
    }
    else if (exploration and RT::args.search_arg == search_arg_findpath)
    {
        // findpath
        return exploration->path();
    }
    else if (exploration and RT::args.search_arg == search_arg_covergraph)
    {
        // cover graph
        return exploration->path();
    }
    else
    {
        // simple property
        return p->path();
    }
}


capacity_t *Task::getMarking() const
{
    // we only provide witness states for simple properties where we found
    // a result
    if (p and p->value)
    {
        return ns->Current;
    }
    else
    {
        return NULL;
    }
}


/*!
\return the number of stored markings (viz. nodes in the reachability graph)
*/
uint64_t Task::getMarkingCount() const
{
    uint64_t result = 0;

    if (store)
    {
        result = store->get_number_of_markings();
    }
    else if (ltlStore)
    {
        result = ltlStore->get_number_of_markings();
    }
    else if (ctlStore)
    {
        result = ctlStore->get_number_of_markings();
    }
    else if (covStore)
    {
        result = covStore->get_number_of_markings();
    }
    else if (tsccStore)
    {
        result = tsccStore->get_number_of_markings();
    }


    RT::data["analysis"]["stats"]["states"] = static_cast<int>(result);
    return result;
}


/*!
\return the number of fired transitions (viz. edges in the reachability graph)

\todo Check whether `result--` is needed and if it is correct.
*/
uint64_t Task::getEdgeCount() const
{
    uint64_t result = 0;

    if (store)
    {
        result = store->get_number_of_calls();
    }
    else if (ltlStore)
    {
        result = ltlStore->get_number_of_calls();
    }
    else if (ctlStore)
    {
        result = ctlStore->get_number_of_calls();
    }
    else if (covStore)
    {
        result = covStore->get_number_of_calls();
    }
    else if (tsccStore)
    {
        result = tsccStore->get_number_of_markings();
    }

    if (result)
    {
        result--;
    }

    RT::data["analysis"]["stats"]["edges"] = static_cast<int>(result);
    return result;
}
