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

%{ KC_TYPES_HEADER
#include <Core/Dimensions.h>
#include <Formula/StatePredicate/StatePredicate.h>
#include <Formula/LTL/BuechiAutomata.h>
#include <Formula/LTL/BuechiFromLTL.h>
#include <Formula/CTL/CTLFormula.h>
#include <cstring>
#include <map>
#include <string>

// required, because the abstract grammar does not allow pointer types
typedef StatePredicate* StatePredicate_p;
typedef BuechiAutomata* BuechiAutomata_p;
typedef CTLFormula* CTLFormula_p;
typedef tl_Node* LTLTree_p;
typedef char* char_p;

// don't use hash sets, since they are deprecated and unordered sets are not yet supported by Kimwitu++
#define DONT_USE_HASHSET
%}

tFormula:
  StatePredicateFormula(tStatePredicate)
{
    formula_t type;
    StatePredicate_p formula = NULL;
    CTLFormula_p ctl_formula = NULL;
    LTLTree_p ltl_tree = NULL;
}
;

tStatePredicate:
  AtomicProposition(tAtomicProposition)
| Negation(tStatePredicate)                               // removed in phase 3
| Conjunction(tStatePredicate tStatePredicate)     // removed in phase 4 for simple properties
| Disjunction(tStatePredicate tStatePredicate)     // removed in phase 4 for simple properties
| ExclusiveDisjunction(tStatePredicate tStatePredicate)   // removed in phase 1
| Implication(tStatePredicate tStatePredicate)            // removed in phase 1
| Equivalence(tStatePredicate tStatePredicate)            // removed in phase 1
| AllPath(tStatePredicate)
| ExPath(tStatePredicate)
| Always(tStatePredicate)
| Eventually(tStatePredicate)
| NextState(tStatePredicate)
| Until(tStatePredicate tStatePredicate)
| Release(tStatePredicate tStatePredicate)
| AU(tStatePredicate tStatePredicate)               // created in phase 5
| EU(tStatePredicate tStatePredicate)               // created by in phase 5
| AR(tStatePredicate tStatePredicate)               // created by in phase 5
| ER(tStatePredicate tStatePredicate)               // created by in phase 5
| AF(tStatePredicate)                               // created by in phase 5
| EF(tStatePredicate)                               // created by in phase 5
| AG(tStatePredicate)                               // created by in phase 5
| EG(tStatePredicate)                               // created by in phase 5
| AX(tStatePredicate)                               // created by in phase 5
| EX(tStatePredicate)                               // created by in phase 5
| ConjunctionList(tConjunction_list)                // created in phase 4 for simpleproperties
| DisjunctionList(tDisjunction_list)                // created in phase 4 for simpleproperties
{
    /// whether the formula contains a temporal operator
    bool containsTemporal = false;
    /// whether the formula is a valid CTL path formula
    bool validCTLPathFormula = false;
    /// whether the formula is a valid CTL state formula
    bool validCTLStateFormula = false;
    /// whether the formula is a valid LTL formula
    bool validLTLFormula = false;
    int priority = 0;
}
;

tConjunction_list:
  list tStatePredicate
;

tDisjunction_list:
  list tStatePredicate
;

tAtomicProposition:
  EqualsAtomicProposition(tTerm tTerm)                // removed in phase 2
| NotEqualsAtomicProposition(tTerm tTerm)             // removed in phase 2
| GreaterAtomicProposition(tTerm tTerm)               
| GreaterEqualAtomicProposition(tTerm tTerm)          // removed in phase 2
| LessAtomicProposition(tTerm tTerm)                  // removed in phase 2
| LessEqualAtomicProposition(tTerm tTerm)
| True()
| False()
| NoDeadlock()					      // only introduced through
				                      // elemination of negation in phase 3
| Deadlock()
| Initial()                                           // removed in phase 1
| Fireable(integer)                                   // removed in phase 1
;

tTerm:
  Node(integer)
| Number(integer)
| Sum(tTerm tTerm)                                    // removed in phase 2
| Difference(tTerm tTerm)                             // removed in phase 2
| Product(integer tTerm)
| ProductList(tProduct_list)                          // created in phase 2
;

tProduct_list:
  list tTerm   // in fact only Product()
;


tBuechiAutomata:
  BuechiAutomaton(tBuechiRules tAcceptingSet)
| BuechiNull()
{
	BuechiAutomata_p automata;
}
;

tBuechiRules:
  EmptyBuechiRules()
| BuechiRule(integer tTransitionRules)
| ExpandedBuechiRule(integer tFormula integer)
| BuechiRules(tBuechiRules tBuechiRules)
;

tTransitionRules:
  EmptyTransitionRules()
| TransitionRule(tFormula integer)
| TransitionRules(tTransitionRules tTransitionRules)
;

tAcceptingSet:
  EmptyAcceptingSet()
| AcceptingState(integer)
| AcceptingSet(tAcceptingSet tAcceptingSet)
;
