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
#ifndef _GRAPH_H
#define _GRAPH_H

#include "llist.h"
#include "point.h"
#include "lstring.h"
class Node;
class Edge;
class Subject;
class OutputFile;

/// (abstract) graph class.
class Graph {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Graph(); 
	///
	virtual ~Graph();
	///
	void AddNode(Node *node);
	///
	void AddEdge(Edge *edge);
	///
	void RemoveNode(Node *node) {nodes->remove(node);}
	///
	void RemoveEdge(Edge *edge) {edges->remove(edge);}
	///
	bool HasNode(Node *node) {return nodes->find(node) != -1;}
	///
	bool HasEdge(Edge *edge) {return edges->find(edge) != -1;}
	///
	void ClearNodes() {nodes->clear();}
	///
	void ClearEdges() {edges->clear();}

	/// checks if edge type may connect subject types 1 and 2.
	bool CheckConnection(int stype1, int stype2, int edgetype);

	/// checks if there is an edge in the graph that connects s1 and s2.
	bool IsConnected(Subject *s1, Subject *s2);

	/// same as above, but edge should also have name n.
	bool IsConnected(Subject *s1, Subject *s2, const string *n);

	/// here edge should also be of type t.
	bool IsConnected(Subject *s1, Subject *s2, int t);

	/// combination of the two members above.
	bool IsConnected(Subject *s1, Subject *s2, const string *n, int t);

	// the "Get" and "Complete" functions return the number of
	// elements added to the given output list.

	/// add to l all edges which connect the subjects.
	int CompleteSubjects(List<Subject *> *l);

	/// add to l all edges of which subject s is part.
	int CompleteSubject(List<Subject *> *l, Subject *s);

	/// add to l all edges which connect subjects s1 and s2.
	int CompleteSubject(List<Subject *> *l, Subject *s1, Subject *s2);
 
	/// add to l all subjects which are connected by edges already in l.
	int CompleteEdges(List<Subject *> *l);

	/// add to l the subjects that are directly connected to subject s.
	int GetConnected(List<Subject *> *l, Subject *s);

	/// add to l all nodes in the graph.
	int GetNodes(List<Subject *> *l);

	/// add to l all nodes of type t in the graph.
	int GetNodes(List<Subject *> *l, int t);

	/// add to l all nodes having name n in the graph.
	int GetNodes(List<Subject *> *l, const string *n);

	/// combination of two above members.
	int GetNodes(List<Subject *> *l, const string *n, int t);

	/// add to l all edges in the graph.
	int GetEdges(List<Subject *> *l);

	/// add to l all edges of type t in the graph.
	int GetEdges(List<Subject *> *l, int t);

	/// add to l all edges having name n in the graph.
	int GetEdges(List<Subject *> *l, const string *n);

	/// combination of two above members.
	int GetEdges(List<Subject *> *l, const string *n, int t);

	/// add to l all edges departing from subject s in the graph.
	int GetEdgesFrom(List<Subject *> *l, Subject *s);

	/// add to l all edges of type t departing from subject s.
	int GetEdgesFrom(List<Subject *> *l, Subject *s, int t);

	/// add to l all edges having name n departing from subject s.
	int GetEdgesFrom(List<Subject *> *l, Subject *s, const string *n);

	/// combination of two above members.
	int GetEdgesFrom(List<Subject *> *l, Subject *s, const string *n, int t);

	/// add to l all edges going to subject s.
	int GetEdgesTo(List<Subject *> *l, Subject *s);

	/// add to l all edges of type t going to subject s.
	int GetEdgesTo(List<Subject *> *l, Subject *s, int t);

	/// add to l all edges having name n going to subject s.
	int GetEdgesTo(List<Subject *> *l, Subject *s, const string *n);

	/// combination of the two above members.
	int GetEdgesTo(List<Subject *> *l, Subject *s, const string *n, int t);

	/// add to l all edges between subjects from and to
	int GetEdges(List<Subject *> *l, Subject *from, Subject *to);

	/// add to l all edges of type t between subjects from and to
	int GetEdges(List<Subject *> *l, Subject *from, Subject *to, int t);

	/// combination of the two above members.
	int GetEdges(List<Subject *> *l, Subject *from, Subject *to, const string *n);

	/// combination of two above members.
	int GetEdges(List<Subject *> *l, Subject *from, Subject *to, const string *n, int t);

	/// return number of nodes in the graph
	int CountNodes();

	/// return number of nodes of type t in the graph
	int CountNodes(int t);

	/// return number of nodes having name n in the graph
	int CountNodes(const string *n);

	/// return nr. of nodes of type t, having name n in the graph
	int CountNodes(const string *n, int t);

	/// return number of edges in the graph
	int CountEdges();

	/// return number of edges of type t in the graph
	int CountEdges(int t);

	/// return number of edges having name n in the graph
	int CountEdges(const string *n);

	/// return nr. of edges of type t, having name n in the graph
	int CountEdges(const string *n, int t);

	/// return nr. of edges departing from subject s
	int CountEdgesFrom(Subject *s);

	/// return nr. of edges of type t departing from subject s
	int CountEdgesFrom(Subject *s, int t);

	/// return number of edges having name n departing from subject s
	int CountEdgesFrom(Subject *s, const string *n);

	/// return number of edges of type t, having name n, departing from subject s
	int CountEdgesFrom(Subject *s, const string *n, int t);

	/// return nr. of edges going to subject s
	int CountEdgesTo(Subject *s);

	/// return nr. of edges of type t going to subject s
	int CountEdgesTo(Subject *s, int t);

	/// return number of edges having name n going to subject s
	int CountEdgesTo(Subject *s, const string *n);

	/// return number of edges of type t, having name n going to subject s
	int CountEdgesTo(Subject *s, const string *n, int t);

	/// return number of edges between subjects s1 and s2
	int CountEdges(Subject *s1, Subject *s2);

	/// return number of edges of type t between subjects s1 and s2
	int CountEdges(Subject *s1, Subject *s2, int t);

	/// return number of edges having name n between subjects s1 and s2
	int CountEdges(Subject *s1, Subject *s2, const string *n);

	/// return number of edges of type t, having name n between subjects s1 and s2
	int CountEdges(Subject *s1, Subject *s2, const string *n, int t);


	/// returns if there is some connected path of graph edges from s1 to s2.
	bool PathExists(Subject *s1, Subject *s2);

	/// returns if there is some conn. path of graph edges of type t from s1 to s2.
	bool PathExists(Subject *s1, Subject *s2, int t);

	// returns list of edges visited. takes edge direction into account.
	// not implemented due to different implementation method
	// by David Jansen <dnjansen@cs.utwente.nl>
	// bool PathExists(Subject *s1, Subject *s2, List<Edge *> *path);

	/// return if there's path from s1 to s2. irregardless edge direction.
	bool UndirectedPathExists(Subject *s1, Subject *s2);
 
	/// Writes all nodes and edges to outputfile f.
	void WriteSubjects(OutputFile *f); 

	/// initializes the table containing all allowed connections.
	virtual void InitConnections()=0;

	/// some counter can be used
	void SetCounter(int n) {counter = n;}
	///
	int GetCounter() {return counter;}

	/// some string can be used as index prefix.
	void SetIndexPrefix(const char *s) {indexPrefix = s;}
	///
	void SetIndexPrefix(const string *s) {indexPrefix = *s;}
	///
	const string *GetIndexPrefix() const {return &indexPrefix;}

	/// index string := prefix + counter.
	void GetIndex(string *s);

	/// assign to index a new unique index
	virtual void GetNextIndex(string *index);

	/// return number of nodes in the graph having this index.
	virtual int CountIndexes(const string *index);

protected:
	/// Allowed 'connected' types in graph (depends on type of editor).
	int *nodeTypes;

	/// Allowed edges type in graph (depends on type of editor).
	int *edgeTypes;

	/// Max. number of different connected types and edge types.
	enum {MAX_TYPES=14};

	/// matrix to store what types can be connected by what edge types.
	int connections[MAX_TYPES][MAX_TYPES][MAX_TYPES]; 

	/// the graph nodes.
	List<Node *> *nodes;

	/// the graph edges.
	List<Edge *> *edges;

	// bool PathExists(Subject *s1, Subject *s2, List<Edge *> *path, 
	// 		int edgetype, bool Directed);
	/// used by other PathExists.
	bool PathExists(Subject *s1, Subject *s2,
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
