#include <Exploration/StatePredicateProperty.h>
#include <Formula/LTL/BuechiAutomata.h>
#include <Formula/StatePredicate/AtomicStatePredicate.h>
#include <Net/Net.h>
#include <Net/NetState.h>

#include <cstdlib>
#include <vector>
#include <math.h>

int BuechiAutomata::getSuccessors(arrayindex_t **list,
                                  arrayindex_t currentState)
{
    arrayindex_t cardTransitionList = cardTransitions[currentState];
    uint32_t **transitionsList = transitions[currentState];

    *list = new arrayindex_t[cardEnabled[currentState]];
    int curCard = 0;

    ////rep->message("SIZE %d (curState %d)",cardEnabled[currentState], currentState);
    for (arrayindex_t i = 0; i < cardTransitionList; i++)
    {
        ////rep->message("checking %d (%d) -> %d",currentState, atomicPropositions[transitionsList[i][0]]->getPredicate()->value,transitionsList[i][1]);
        if (atomicPropositions[transitionsList[i][0]]->getPredicate()->value)
        {
            ////rep->message("NOW PROP %d (p:%d)--> TRUE",i,atomicPropositions[transitionsList[i][0]]);

            //rep->message("List(%d) %d = %d @ %d/%d [%d] (p: %d)",i,curCard,transitionsList[i][1], cardEnabled[currentState],cardTransitionList,currentState,atomicPropositions[transitionsList[i][0]]);
            (*list)[curCard++] = transitionsList[i][1];
        } //else
    }
    ////rep->message("END");
    return curCard;
}

void BuechiAutomata::updateProperties(NetState &ns, arrayindex_t transition)
{
    //rep->message("UPDATE");
    for (arrayindex_t i = 0; i < cardStates; i++)
    {
        cardEnabled[i] = 0;
    }
    for (arrayindex_t i = 0; i < cardAtomicPropositions; i++)
        if (atomicPropositions[i]->checkProperty(ns, transition))
        {
            //rep->message("CHECK PROP %d (s = %d, p:%d) --> TRUE",i,atomicPropotions_backlist[i],atomicPropositions[i]);
            cardEnabled[atomicPropotions_backlist[i]]++;
        } //else
    ////rep->message("CHECK PROP %d (s = %d, p:%d)--> FALSE",i,atomicPropotions_backlist[i],atomicPropositions[i]);
}

void BuechiAutomata::initProperties(NetState &ns)
{
    //rep->message("INIT");
    for (arrayindex_t i = 0; i < cardAtomicPropositions; i++)
    {
        //rep->message("INIT %d",i);
        if (atomicPropositions[i]->initProperty(ns))
        {
            cardEnabled[atomicPropotions_backlist[i]]++;
            //rep->message("TRUE %d",cardEnabled[atomicPropotions_backlist[i]]);
        } //else
        //rep->message("FALSE");
    }
}

void BuechiAutomata::revertProperties(NetState &ns, arrayindex_t transition)
{
    ////rep->message("REVERT");
    for (arrayindex_t i = 0; i < cardStates; i++)
    {
        cardEnabled[i] = 0;
    }
    for (arrayindex_t i = 0; i < cardAtomicPropositions; i++)
        if (atomicPropositions[i]->updateProperty(ns, transition))
        {
            cardEnabled[atomicPropotions_backlist[i]]++;
        }
}

bool BuechiAutomata::isAcceptingState(arrayindex_t state)
{
    return isStateAccepting[state];
}

arrayindex_t BuechiAutomata::getNumberOfStates()
{
    return cardStates;
}

BuechiAutomata::~BuechiAutomata()
{
    for (arrayindex_t i = 0; i < cardAtomicPropositions; i++)
    {
        delete atomicPropositions[i]->getPredicate();
        delete atomicPropositions[i];
    }

    // allocated in Task::setFormula()
    delete[] atomicPropositions;

    for (arrayindex_t i = 0; i < cardStates; i++)
    {
        for (arrayindex_t j = 0; j < cardTransitions[i]; j++)
        {
            delete[] transitions[i][j];
        }
        delete[] transitions[i];
    }

    delete[] transitions;
    delete[] cardTransitions;
    delete[] isStateAccepting;
    delete[] atomicPropotions_backlist;
}


int current_next_string_index_number = 1;

char *produce_next_string(int *val)
{
    current_next_string_index_number++;
    int length = (int) log10(current_next_string_index_number) + 2;
    char *buf = new char[length]();
    sprintf(buf, "%d", current_next_string_index_number);
    *val = current_next_string_index_number;
    return buf;
}
