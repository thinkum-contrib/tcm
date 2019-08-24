////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "util.h"
#include "outputfile.h"

Graph::Graph() {
	nodes = new List<Node *>;
	edges = new List<Edge *>;
	nodeTypes = new int[static_cast<int>(MAX_TYPES)];
	edgeTypes = new int[static_cast<int>(MAX_TYPES)];
	int m = MAX_TYPES;
	for (int i=0;i<m;i++)
		for (int j=0;j<m;j++)
			for (int k=0;k<m;k++)
				connections [i][j][k]= False;
	counter = 1;
	indexPrefix = "";
}

Graph::~Graph() {
	nodes->clear();
	edges->clear();
	delete nodes;
	delete edges;
	delete[] nodeTypes;
	delete[] edgeTypes;
}

void Graph::AddNode(Node *node) {
	if (!HasNode(node)) nodes->add(node);}

void Graph::AddEdge(Edge *edge) {
	if (!HasEdge(edge)) edges->add(edge);}

bool Graph::CheckConnection(int subjecttype1, int subjecttype2, int edgetype) {
	return connections
		[Code::GetIndex(subjecttype1, nodeTypes)]
		[Code::GetIndex(subjecttype2, nodeTypes)]
		[Code::GetIndex(edgetype, edgeTypes)];
}

bool Graph::IsConnected(Subject *s1, Subject *s2) {
	return IsConnected(s1, s2, -1);
}

bool Graph::IsConnected(Subject *s1, Subject *s2, int t) {
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (!check(edge))
			return False;
		if (edge->GetClassType()==t || t==-1) {
			if (edge->IsDirected()) {
				if (edge->GetSubject1()==s1 && 
				    edge->GetSubject2()==s2)
					return True;
			}
			else
				if (edge->PartOf(s1)&&edge->PartOf(s2))
					return True;
		}
	}
	return False;
}

bool Graph::IsConnected(Subject *s1, Subject *s2, const string *s) {
	return IsConnected(s1, s2, s, -1);
}

bool Graph::IsConnected(Subject *s1, Subject *s2, 
		const string *s, int t) {
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (!check(edge))
			return False;
		if (*edge->GetName()==*s && 
				(edge->GetClassType()==t || t==-1)) {
			if (edge->IsDirected()) {
				if (edge->GetSubject1()==s1 && 
				    edge->GetSubject2()==s2)
					return True;
			}
			else
				if (edge->PartOf(s1) && edge->PartOf(s2))
					return True;
		}
	}
	return False;
}

int Graph::GetConnected(List<Subject *> *l, Subject *s) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (!check(edge))
			break;
		Subject *n1 = edge->GetSubject1();
		Subject *n2 = edge->GetSubject2();
		if (edge->IsDirected()) {
			if (n1==s && l->find(n2) == -1)
			l->add(n2);
		}
		else {
			if (n1==s && l->find(n2) == -1)
				l->add(n2);
			else if (n2==s && l->find(n1) == -1)
				l->add(n1);
		}
	}
	return l->count()-c;
}
 
int Graph::CompleteSubjects(List<Subject *> *l) {
	int c = l->count();
	for (l->last(); !l->done(); l->prev()) {
		Subject *s = l->cur();
		if (check(s))
			CompleteSubject(l, s);
	}
	return l->count()-c;
}
 
int Graph::CompleteSubject(List<Subject *> *l, Subject *s) {
	int c = l->count();
	List<Edge *> newEdges;
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (!check(edge))
			break;
		if (edge->PartOf(s))
			if (l->find(edge) == -1) {
				newEdges.add(edge);
				l->add(edge);
			}
	}
	// complete newly added edges.
	for (newEdges.first(); !newEdges.done(); newEdges.next())
		CompleteSubject(l, newEdges.cur());
	return l->count()-c;
}

int Graph::CompleteSubject(List<Subject *> *l, Subject *s1, Subject *s2) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (!check(edge))
			break;
		if (edge->PartOf(s1) && edge->PartOf(s2))
			if (l->find(edge) == -1)
				l->add(edge);
	}
	return l->count()-c;
}

int Graph::CompleteEdges(List<Subject *> *l) {
	int c = l->count();
	List<Subject *> newEdges;
	for (l->last(); !l->done(); l->prev()) {
		Subject *subj;
		Subject *s = l->cur();
		if (check(s)) {
			if (s->IsEdge()) {
				subj = ((Edge *)s)->GetSubject1();
				if (l->find(subj) == -1) {
					if (subj->IsEdge()) 
						newEdges.add(subj);	
					else
						l->add(subj);
				}
				subj = ((Edge *)s)->GetSubject2();
				if (l->find(subj) == -1) {
					if (subj->IsEdge()) 
						newEdges.add(subj);	
					else
						l->add(subj);
				}
			}
		}
	}
	if (newEdges.count() > 0) {
		CompleteEdges(&newEdges);
		for (newEdges.first(); !newEdges.done(); newEdges.next())
			if (l->find(newEdges.cur()) == -1)
				l->add(newEdges.cur());
	}
	return l->count()-c;
}

int Graph::GetNodes(List<Subject *> *l) {
	int c = l->count();
	for (nodes->first(); !nodes->done(); nodes->next()) {
		if (check(nodes->cur() && !nodes->cur()->IsEdge()))
			l->add(nodes->cur());
	}
	return l->count()-c;
}

int Graph::GetNodes(List<Subject *> *l, int t) {
	int c = l->count();
	for (nodes->first(); !nodes->done(); nodes->next()) {
		Subject *s = nodes->cur();
		if (check(s && !s->IsEdge())) {
			if (s->GetClassType() == t)
				l->add(s);
		}
	}
	return l->count()-c;
}

int Graph::GetNodes(List<Subject *> *l, const string *n) {
	int c = l->count();
	for (nodes->first(); !nodes->done(); nodes->next()) {
		Subject *s = nodes->cur();
		if (check(s && !s->IsEdge())) {
			if (*s->GetName() == *n)
				l->add(s);
		}
	}
	return l->count()-c;
}

int Graph::GetNodes(List<Subject *> *l, const string *n, int t) {
	int c = l->count();
	for (nodes->first(); !nodes->done(); nodes->next()) {
		Subject *s = nodes->cur();
		if (check(s && !s->IsEdge())) {
			if (s->GetClassType() == t && *s->GetName() == *n)
				l->add(s);
		}
	}
	return l->count()-c;
}


int Graph::GetEdges(List<Subject *> *l) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) 
			l->add(e);
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t)
				l->add(e);
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, const string *n) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (*e->GetName() == *n)
				l->add(e);
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, const string *n, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t && *e->GetName() == *n)
				l->add(e);
		}
	}
	return l->count()-c;
}


int Graph::GetEdgesFrom(List<Subject *> *l, Subject *s) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->IsDirected() && e->GetSubject1() == s)
				l->add(e);
			else if (!e->IsDirected() && (e->PartOf(s)))
				l->add(e);
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesFrom(List<Subject *> *l, Subject *s, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t) {
				if (e->IsDirected() && e->GetSubject1() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesFrom(List<Subject *> *l, Subject *s, const string *n) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (*e->GetName() == *n) {
				if (e->IsDirected() && e->GetSubject1() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesFrom(List<Subject *> *l, Subject *s, const string *n, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t && *e->GetName() == *n) {
				if (e->IsDirected() && e->GetSubject1() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesTo(List<Subject *> *l, Subject *s) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->IsDirected() && e->GetSubject2() == s)
				l->add(e);
			else if (!e->IsDirected() && (e->PartOf(s)))
				l->add(e);
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesTo(List<Subject *> *l, Subject *s, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t) {
				if (e->IsDirected() && e->GetSubject2() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesTo(List<Subject *> *l, Subject *s, const string *n) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (*e->GetName() == *n) {
				if (e->IsDirected() && e->GetSubject2() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdgesTo(List<Subject *> *l, Subject *s, const string *n, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType() == t && *e->GetName() == *n) {
				if (e->IsDirected() && e->GetSubject2() == s)
					l->add(e);
				else if (!e->IsDirected() && (e->PartOf(s)))
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, Subject *s1, Subject *s2) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetSubject1() == s1 && e->GetSubject2() == s2)
				l->add(e);
			else if (!e->IsDirected() && s1 != s2 && 
					e->GetSubject1() == s2 &&
					e->GetSubject2() == s1)
				l->add(e);
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, Subject *s1, Subject *s2, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (e->GetClassType()==t) {
				if (e->GetSubject1() == s1 && 
				    e->GetSubject2() == s2)
					l->add(e);
				else if (!e->IsDirected() && s1 != s2 && 
				    e->GetSubject1() == s2 && 
				    e->GetSubject2() == s1)
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, Subject *s1, Subject *s2, const string *n) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (*e->GetName()==*n) {
				if (e->GetSubject1() == s1 && 
				    e->GetSubject2() == s2)
					l->add(e);
				else if (!e->IsDirected() && s1 != s2 && 
				    e->GetSubject1() == s2 && 
				    e->GetSubject2() == s1)
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::GetEdges(List<Subject *> *l, Subject *s1, Subject *s2, const string *n, int t) {
	int c = l->count();
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *e = edges->cur();
		if (check(e)) {
			if (*e->GetName()==*n && e->GetClassType() == t) {
				if (e->GetSubject1() == s1 && 
				    e->GetSubject2() == s2)
					l->add(e);
				else if (!e->IsDirected() && s1 != s2 && 
				    e->GetSubject1() == s2 && 
				    e->GetSubject2() == s1)
					l->add(e);
			}
		}
	}
	return l->count()-c;
}

int Graph::CountNodes() {
	return nodes->count();
}

int Graph::CountNodes(int t) {
	List<Subject *> s;
	return GetNodes(&s, t);
}

int Graph::CountNodes(const string *n) {
	List<Subject *> s;
	return GetNodes(&s, n);
}

int Graph::CountNodes(const string *n, int t) {
	List<Subject *> s;
	return GetNodes(&s, n, t);
}

int Graph::CountEdges() {
	return edges->count();
}

int Graph::CountEdges(int t) {
	List<Subject *> e;
	return GetEdges(&e, t);
}

int Graph::CountEdges(const string *n) {
	List<Subject *> e;
	return GetEdges(&e, n);
}

int Graph::CountEdges(const string *n, int t) {
	List<Subject *> e;
	return GetEdges(&e, n, t);
}

int Graph::CountEdgesFrom(Subject *s) {
	List<Subject *> e;
	return GetEdgesFrom(&e, s);
}

int Graph::CountEdgesFrom(Subject *s, const string *n) {
	List<Subject *> e;
	return GetEdgesFrom(&e, s, n);
}

int Graph::CountEdgesFrom(Subject *s, int t) {
	List<Subject *> e;
	return GetEdgesFrom(&e, s, t);
}

int Graph::CountEdgesFrom(Subject *s, const string *n, int t) {
	List<Subject *> e;
	return GetEdgesFrom(&e, s, n, t);
}

int Graph::CountEdgesTo(Subject *s) {
	List<Subject *> e;
	return GetEdgesTo(&e, s);
}

int Graph::CountEdgesTo(Subject *s, const string *n) {
	List<Subject *> e;
	return GetEdgesTo(&e, s, n);
}

int Graph::CountEdgesTo(Subject *s, int t) {
	List<Subject *> e;
	return GetEdgesTo(&e, s, t);
}

int Graph::CountEdgesTo(Subject *s, const string *n, int t) {
	List<Subject *> e;
	return GetEdgesTo(&e, s, n, t);
}

int Graph::CountEdges(Subject *s1, Subject *s2) {
	List<Subject *> e;
	return GetEdges(&e, s1, s2);
}

int Graph::CountEdges(Subject *s1, Subject *s2, const string *n) {
	List<Subject *> e;
	return GetEdges(&e, s1, s2, n);
}

int Graph::CountEdges(Subject *s1, Subject *s2, int t) {
	List<Subject *> e;
	return GetEdges(&e, s1, s2, t);
}

int Graph::CountEdges(Subject *s1, Subject *s2, const string *n, int t) {
	List<Subject *> e;
	return GetEdges(&e, s1, s2, n, t);
}

// PathExists members are implemented by David Jansen
// <dnjansen@cs.utwente.nl> on 28 September 2000.
bool Graph::PathExists(Subject *s1, Subject *s2) {
	return PathExists(s1, s2, 0, True);
}

bool Graph::PathExists(Subject *s1, Subject *s2, int t) {
	return PathExists(s1, s2, t, True);
}

bool Graph::UndirectedPathExists(Subject *s1, Subject *s2) {
	return PathExists(s1, s2, 0, False);
}

bool Graph::PathExists(Subject *s1, Subject *s2,			
		       int edgetype, bool Directed) {		  
	// The procedure looks for a path from s1 to s2, composed of  
	// edges of the given type (edgetype, Directed).	     
	// It doesn't account for composed edges.		   
	List<Subject *> edgelist;				 
	if ( edgetype )					  
		GetEdges(&edgelist, edgetype);		  
	else						   
		GetEdges(&edgelist);			  

	List<Subject *> visitsubj;				     
	visitsubj.add(s1);					      
	bool done;						      
	do {							    
		done = True;					    
		for ( edgelist.first() ; ! edgelist.done() ; ) {	
			Edge *edge = dynamic_cast<Edge *>(edgelist.cur());
			if ( ! check(edge) )			    
				// shouldn't happen.		    
				return False;			   
			Subject *n1 = edge->GetSubject1();	     
			Subject *n2 = edge->GetSubject2();	    
			bool subj1 = True; 
			if ( ! visitsubj.contains(n1) ) {
				if ( Directed && edge->IsDirected()
				  || ! visitsubj.contains(n2) ) {
					edgelist.next();
					continue;
			   	}
				subj1 = False;
				Subject *tmp = n1;
				n1 = n2;
				n2 = tmp;
			}
			if ( n2 == s2 )			     
				return True;			
			if ( ! subj1 || ! visitsubj.contains(n2) ) {
				done = False;		      
				visitsubj.add(n2);		
			}					
			edgelist.removecur();		   
		}
	} while ( ! done );				   
	return False;					
}
 

/*
old and slow implementation.
bool Graph::PathExists(Subject *s1, Subject *s2,
		       int edgetype, bool Directed) {
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (edgetype > 0 && edge->GetClassType()!=edgetype)
			continue;
		if (!check(edge))
			return False;
		Subject *n1 = edge->GetSubject1();
		Subject *n2 = edge->GetSubject2();
		bool step = False;
		// directed: only n1 -> n2.
		if (n1 == s1 && edge->IsDirected()) {
			step = True;
		}
		// undirected: both n1 -> n2 and n1 <- n2 allowed.
		else if ((!edge->IsDirected() || !Directed) &&
			   (n1 == s1 || n2 == s1)) {
			step = True;
			if (s1 == n2) {
				Subject *tmp = n1;
				n1 = n2;
				n2 = tmp;
			}
		}
		if (step) {
			if (n2 == s2) {
				path->add(edge);
				return True;
			}
			else if (path->find(edge) == -1) {
				path->add(edge);
				if (PathExists(n2, s2, path, edgetype, Directed))
					return True;
				path->remove(edge);
				if (!edges->setcur(edge))
					error("%s %d: internal graph error\n", 
						__FILE__, __LINE__);
			}
			step = False;
		}
	}
	return False;
}
*/

void Graph::WriteSubjects(OutputFile *f) {
	(*f) << "# GRAPH NODES\n\n";
	for (nodes->first(); !nodes->done(); nodes->next()) {
		if (check(nodes->cur()))
			nodes->cur()->Write(f);
	}
	(*f) << "# GRAPH EDGES\n\n";
	for (edges->first(); !edges->done(); edges->next()) {
		if (check(edges->cur()))
			edges->cur()->Write(f);
	}
}

int Graph::CountIndex(const string *index, List<Subject *> *l) {
	int count = 0;
	for (l->first(); !l->done(); l->next()) {
		if (!l->cur()->IsEdge()) {
			Node *node = (Node *)l->cur();
			if (*node->GetIndex() == *index) {
				count++;
			}
		}
	}
	return count;
}

void Graph::GetIndex(string *s) {
	*s = *GetIndexPrefix();
	if (*s != "")
		*s += ".";
	if (GetCounter() > 0)
		*s += GetCounter();
}

void Graph::GetNextIndex(string *index) {
	GetIndex(index);
	// make index one higher, until a unique index is found.
	if (GetCounter() > 0) {
		SetCounter(0);
		List<Subject *> l;
		GetNodes(&l);
		do {
			SetCounter(GetCounter()+1);
			GetIndex(index);
		} while (CountIndex(index, &l) != 0);
	}
}
 
int Graph::CountIndexes(const string *index) {
	List<Subject *> l;
	GetNodes(&l);
	return CountIndex(index, &l);
}

