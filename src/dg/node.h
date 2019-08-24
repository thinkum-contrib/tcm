//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
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
//-----------------------------------------------------------------------------
#ifndef _NODE_H
#define _NODE_H

#include "subject.h"
#include "hypergraph.h"


/// Node class (base class for all specific node classes).
class Node: public Subject {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Node(Graph *g);

	///
	Node(HyperGraph *hg);

	/// a node is not an edge
	bool IsEdge() const {return False;}

	/// a node is not a hyperedge				/*new*/
	bool IsHyperEdge() const {return False;}		/*new*/

	/// is node in the graph?
	bool InGraph() const;

	///
	const string *GetIndex() const {return &index;}

	/// set and check index
	virtual Subject::NameErrType SetIndex(const string *s);

	///
	void WriteMembers(OutputFile *f);

	///
	bool ReadMembers(InputFile *f, double format);

	/// put in pindex the index of the parent node.
	void GetParentIndex(string *pindex);
private:
	/// an index label (not necessarily used).
	string index;
};
#endif
