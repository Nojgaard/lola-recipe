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
\author Christian Koch
\status new
\ingroup ctl

\brief Definition of conjunctions for CTL.
*/

#pragma once

#include <vector>

struct CTLFormula;

class ConjunctionFormula : public CTLFormula
{
public:
    explicit ConjunctionFormula(std::vector<CTLFormula *>);
    /// returns info on a particular node in the formula tree
    FormulaInfo *getInfo() const;
    /// returns the number of subformulas
    int countSubFormulas() const;

private:
    inline void initAtomics(NetState &ns);
    inline void updateAtomics(NetState &ns, arrayindex_t t);
    inline void revertAtomics(NetState &ns, arrayindex_t t);

    bool check(Store<void *> &s, NetState &ns, Firelist &firelist,
               std::vector<int> &witness);

    void DEBUG_print();

    void gatherPayloadInformation(arrayindex_t &numDFS, arrayindex_t &numCachedResults);
    void setPayloadInformation(arrayindex_t cachedResultOffset, size_t payloadSize);

    /// the subformulae for the conjunction
    CTLFormula **subs;
    /// the number of subformulae (length of array subs)
    arrayindex_t cardSubs;
};
