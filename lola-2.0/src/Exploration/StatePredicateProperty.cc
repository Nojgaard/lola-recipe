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

/*!
\file
\author Karsten
\status new

\brief Evaluates state predicate

Actual property is virtual, default (base class) is full exploration
*/

#include <Exploration/StatePredicateProperty.h>
#include <Formula/StatePredicate/AtomicStatePredicate.h>
#include <Formula/StatePredicate/DeadlockPredicate.h>
#include <Formula/StatePredicate/StatePredicate.h>
#include <Net/Net.h>
#include <Net/Transition.h>

#include <cstdlib>

StatePredicateProperty::StatePredicateProperty(StatePredicate *f)
{
    // set formula
    predicate = f;
    f->top = f;

    const arrayindex_t cardAtomic = f->countAtomic();
    AtomicStatePredicate **atomic = new AtomicStatePredicate *[cardAtomic];
    f->collectAtomic(atomic);

    cardDeadlock = f->countDeadlock();
    changedDeadlock = new DeadlockPredicate *[cardDeadlock];
    const arrayindex_t c = f->collectDeadlock(changedDeadlock);
    assert(c == cardDeadlock);

    // initialize up sets
    for (arrayindex_t i = 0; i < cardAtomic; i++)
    {
        atomic[i]->setUpSet();
    }

    cardChanged = new arrayindex_t[Net::Card[TR]]();
    // cannot be allocated with new[] due to a later realloc
    changedPredicate = (AtomicStatePredicate ** *) malloc(Net::Card[TR] * SIZEOF_VOIDP);
    // cannot be allocated with new[] due to a later realloc
    changedSum = reinterpret_cast<int **>(malloc(Net::Card[TR] * SIZEOF_VOIDP));
    for (arrayindex_t t = 0; t < Net::Card[TR]; t++)
    {
        changedPredicate[t] = reinterpret_cast<AtomicStatePredicate **>(malloc(cardAtomic * SIZEOF_VOIDP));
        changedSum[t] = reinterpret_cast<int *>(malloc(cardAtomic * SIZEOF_INT));
        for (arrayindex_t i = 0; i < cardAtomic; i++)
        {
            int s = 0;
            // evaluate delta that t causes on this predicate
            for (arrayindex_t j = 0; j < Transition::CardDeltaT[PRE][t]; j++)
            {
                const arrayindex_t p = Transition::DeltaT[PRE][t][j];
                for (arrayindex_t k = 0; k < atomic[i]->cardPos; k++)
                {
                    if (atomic[i]->posPlaces[k] == p)
                    {
                        s -= Transition::MultDeltaT[PRE][t][j]
                             * atomic[i]->posMult[k];
                        break;
                    }
                }
                for (arrayindex_t k = 0; k < atomic[i]->cardNeg; k++)
                {
                    if (atomic[i]->negPlaces[k] == p)
                    {
                        s += Transition::MultDeltaT[PRE][t][j]
                             * atomic[i]->negMult[k];
                        break;
                    }
                }
            }
            for (arrayindex_t j = 0; j < Transition::CardDeltaT[POST][t]; j++)
            {
                const arrayindex_t p = Transition::DeltaT[POST][t][j];
                for (arrayindex_t k = 0; k < atomic[i]->cardPos; k++)
                {
                    if (atomic[i]->posPlaces[k] == p)
                    {
                        s += Transition::MultDeltaT[POST][t][j]
                             * atomic[i]->posMult[k];
                        break;
                    }
                }
                for (arrayindex_t k = 0; k < atomic[i]->cardNeg; k++)
                {
                    if (atomic[i]->negPlaces[k] == p)
                    {
                        s -= Transition::MultDeltaT[POST][t][j]
                             * atomic[i]->negMult[k];
                        break;
                    }
                }
            }
            if (s)
            {
                changedPredicate[t][cardChanged[t]] = atomic[i];
                changedSum[t][cardChanged[t]++] = s;
            }
        }
        changedPredicate[t] = reinterpret_cast<AtomicStatePredicate **>(realloc(changedPredicate[t],
                              cardChanged[t] * SIZEOF_VOIDP));
        changedSum[t] = reinterpret_cast<int *>(realloc(changedSum[t],
                                                cardChanged[t] * SIZEOF_ARRAYINDEX_T));
    }
    delete[] atomic;
}


StatePredicateProperty::~StatePredicateProperty()
{
    for (arrayindex_t t = 0; t < Net::Card[TR]; ++t)
    {
        free(changedPredicate[t]);
        free(changedSum[t]);
    }
    free(changedPredicate);
    delete[] changedDeadlock;
    free(changedSum);
    delete[] cardChanged;
}


bool StatePredicateProperty::initProperty(NetState &ns)
{
    predicate->evaluate(ns);
    assert(predicate->DEBUG__consistency(ns));
    return predicate->value;
}

bool StatePredicateProperty::checkProperty(NetState &ns, arrayindex_t t)
{
    for (arrayindex_t i = 0; i < cardChanged[t]; i++)
    {
        changedPredicate[t][i]->update(ns, changedSum[t][i]);
    }
    for (arrayindex_t i = 0; i < cardDeadlock; i++)
    {
        changedDeadlock[i]->update(ns);
    }
    assert(predicate->DEBUG__consistency(ns));
    return predicate->value;
}

bool StatePredicateProperty::updateProperty(NetState &ns, arrayindex_t t)
{
    for (arrayindex_t i = 0; i < cardChanged[t]; i++)
    {
        changedPredicate[t][i]->update(ns, -changedSum[t][i]);
    }
    for (arrayindex_t i = 0; i < cardDeadlock; i++)
    {
        changedDeadlock[i]->update(ns);
    }
    assert(predicate->DEBUG__consistency(ns));
    return predicate->value;
}


SimpleProperty *StatePredicateProperty::copy()
{
    StatePredicateProperty *spp = new StatePredicateProperty(predicate->copy());
    spp->stack = stack;
    spp->value = value;
    return spp;
}

bool StatePredicateProperty::checkOmegaProperty(NetState &ns)
{
    predicate->evaluateOmega(ns);
    //    assert(predicate->DEBUG__consistency(ns));
    return predicate->value;
}

bool StatePredicateProperty::isUnknown()
{
    return predicate->unknown;
}
