//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _DIAGRAMCHECKS_H
#define _DIAGRAMCHECKS_H

#include "bool.h"
#include <limits.h>
class Graph;
class Diagram;
class string;

/// implements generic checks for soft constraints on diagrams.
class DiagramChecks {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DiagramChecks(Diagram *d, Graph *g);

	// Error messages are appended to chkbuf. The functions return the
	// number of errors found.

	/// diagram should have count nodes of nodeType.
	unsigned CheckNodeCount(unsigned count, int nodeType, string &chkbuf);

	/// diagram should have min <= count <= max nodes of nodeType.
	unsigned CheckNodeCount(unsigned min, unsigned max, 
		int nodeType, string &chkbuf);

	/// diagram should have count edges of edgeType
	unsigned CheckEdgeCount(unsigned count, int edgeType, string &chkbuf);

	/// diagram should have min <= count <= max edges of edgeType.
	unsigned CheckEdgeCount(unsigned min, unsigned max, 
		int edgeType, string &chkbuf);

	/// check that nodes unique indexes.
	unsigned CheckDoubleIndexes(string &chkbuf);

	/// diagram should have no nameless nodes of nodeType
	unsigned CheckNamelessNodes(int nodeType, string &chkbuf); 

	/// diagram should have no nameless edges of edgeType
	unsigned CheckNamelessEdges(int edgeType, string &chkbuf); 

	/// diagram should have no nodes of nodeType named 'name'. 
	unsigned CheckIllegalNodeNames(int nodeType, const string *name, 
			string &chkbuf); 

	/// diagram should have no edges of edgeType named 'name'.
	unsigned CheckIllegalEdgeNames(int edgeType, const string *name, 
			string &chkbuf); 

	/// diagram should have no nameless edges of edgeType between types. 
	unsigned CheckNamelessEdges(
		int edgeType, int type1, int type2, string &chkbuf);

	/// diagram shouldn't have double nameless edges between these types. 
	unsigned CheckDoubleNamelessEdges(int edgeType, int type1, 
		int type2, string &chkbuf);

	/// diagram should not have multiple nodes of nodeType with same name.
	unsigned CheckDoubleNodes(int nodeType, string &chkbuf);

	/// nodeType nodes should be connected (index: name or index in msg)
	unsigned CheckConnected(int nodeType, bool index, string &chkbuf);

	/// nodeType nodes should be connected (index: name or index in msg)
	unsigned CheckConnected(int nodeType, int toNode, int min, int max, 
		bool index, string &chkbuf);

	/// nodes of nodeType connected by 1 parent edge and minChildren edges.
	unsigned CheckJunctionCoherence(int nodeType, int parenttype, 
			int childtype, unsigned minChildren, string &chkbuf);

	/// nodes of nodeType should have min/max departing edges of edgeType.
	unsigned CheckCountEdgesFrom(int nodeType, int edgeType, unsigned min, 
			unsigned max, bool zeroAllowed, bool index, 
			string &chkbuf);

	/// nodes of nodeType are reachable from >= 1 nodes of rootType.
	unsigned CheckReachability(int rootType, int nodeType, 
			bool index, string &chkbuf);

protected:
	///
	Graph *GetGraph() const {return graph;}
	///
	Diagram *GetDiagram() const {return diagram;}
	///
	unsigned CheckCount(unsigned min, unsigned max, int type, 
		string &chkbuf, bool node);
	///
	unsigned CheckIllegalNames(int type, const string *name,
		string &chkbuf, bool node);
private:
	///
	Graph *graph;
	///
	Diagram *diagram;
};
#endif
