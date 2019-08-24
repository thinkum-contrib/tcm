//////////////////////////////////////////////////////////////////////////////////
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Rik Eshuis (eshuis@cs.utwente.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// TCM is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#ifndef _ELIM_H
#define _ELIM_H


#include "adshypergraph.h"
#include "atdiagram.h"
#include "atgraph.h"
#include "graph.h"
#include "llist.h"
#include "bool.h"
#include "edge.h"
#include "lstring.h"


class Elim{
/*@Doc: {\large {\bf scope:} } */
 public:
	/// some generic checks on activity graphs needed in order to make
        /// sure that the elimination of pseudo state nodes can be conducted
	bool Check(Graph *);

	///  copy g to h and parse the labels on g's edges
	bool FillAH(Graph *g, ADSHyperGraph *h );

	/// eliminate the OR nodes in h
	bool ElimOrNodes(ADSHyperGraph *h);

	/// used for parsing labels on simple edges
	bool ParseGuardLabel(const string *str);

	/// eliminate the AND nodes in h
	bool ElimAndNodes(ADSHyperGraph *h);

	/// update the proplist in ah by setting for each property 
	/// which variables that property refers to
	void UpdatePropList(ADSHyperGraph *ah);

	/// main procedure
	bool EliminatePseudoStateNodes(Graph *g, ADSHyperGraph *h);

};

#endif
