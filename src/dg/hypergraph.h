////////////////////////////////////////////////////////////////////////////////
//
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
#ifndef _HYPERGRAPH_H
#define _HYPERGRAPH_H

#include "llist.h"
#include "point.h"
#include "lstring.h"
//#include "subject.h"
//#include "outputfile"
class Node;
class HyperEdge;
class Subject;
class OutputFile;
class Prop;
class ADSVar;

/// (abstract) graph class.
class HyperGraph {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	HyperGraph(); 
	///
	virtual ~HyperGraph();
	///
	void AddNode(Node *node);
	///
	void AddHyperEdge(HyperEdge *edge);
	/// Removes both node and all connected hyperedges
	void RemoveNode(Node *node);
	///
	void RemoveHyperEdge(HyperEdge *edge) {hedges->remove(edge);}
	///
	bool HasNode(Node *node) {return nodes->find(node) != -1;}
	///
	bool HasHyperEdge(HyperEdge *edge) {return hedges->find(edge) != -1;}
	///
	void ClearNodes() {nodes->clear();}
	///
	void ClearHyperHedges() {hedges->clear();}
	///
	void WriteSubjects(OutputFile *f);
	///
	void Write();
	///
	void GetNodes(List <Subject *> *);
	///
	void GetNodes(List<Subject *> *l, int t);
	/// gives copy;
	void GetHyperEdges(List <Subject *> *);
	/// get every hyperedge whose source contains s
	void GetHyperEdgesFrom(List <Subject *> *l,Subject *s);
	/// get every hyperedge whose source is contained in cfg
	void GetHyperEdgesFrom(List <HyperEdge *> *l,List <Subject *> *cfg);
	/// get every hyperedge whose target contains s
	void GetHyperEdgesTo(List <Subject *> *l,Subject *s);
	/// 
        bool ExistsSimilarHyperEdge(HyperEdge *he);


protected:
	/// Allowed 'connected' types in graph (depends on type of editor).
	int *nodeTypes;

	/// Allowed hedges type in graph (depends on type of editor).
	int *edgeTypes;

	/// Max. number of different connected types and edge types.
	enum {MAX_TYPES=14};

	/// matrix to store what types can be connected by what edge types.
	int connections[MAX_TYPES][MAX_TYPES][MAX_TYPES]; 

	/// the graph nodes.
	List<Node *> *nodes;

	/// the graph hedges.
	List<HyperEdge *> *hedges;

	/// used by other PathExists.
	bool PathExists(Subject *s1, Subject *s2, List<HyperEdge *> *path, 
			int edgetype, bool Directed);

	/// return number of nodes in l having this index 
	int CountIndex(const string *index, List<Subject *> *l);

private:
	/// current index prefix
	string indexPrefix;

	/// current counter
	int counter;
};
#endif
