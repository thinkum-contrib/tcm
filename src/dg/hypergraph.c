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
#include "hypergraph.h"
#include "node.h"
#include "hyperedge.h"
#include "util.h"
#include "outputfile.h"

HyperGraph::HyperGraph() {
	nodes = new List<Node *>;
	hedges = new List<HyperEdge *>;
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

HyperGraph::~HyperGraph() {
	nodes->clear();
	hedges->clear();
	delete nodes;
	delete hedges;
	delete[] nodeTypes;
	delete[] edgeTypes;
}




void HyperGraph::AddNode(Node *node) {
	if (!HasNode(node)) nodes->add(node);}

void HyperGraph::AddHyperEdge(HyperEdge *edge) {
	if (!HasHyperEdge(edge)) hedges->add(edge);
}

void HyperGraph::WriteSubjects(OutputFile *f) {
	(*f) << "# GRAPH NODES\n\n";
	for (nodes->first(); !nodes->done(); nodes->next()) {
		if (check(nodes->cur()))
			nodes->cur()->Write(f);
	}
	(*f) << "# GRAPH HYPEREDGES\n\n";
	for (hedges->first(); !hedges->done(); hedges->next()) {
	        if (check(hedges->cur()))
			hedges->cur()->WriteMembers(f);
	}
}



void HyperGraph::GetNodes(List <Subject *> *l){
	for (nodes->first(); !nodes->done(); nodes->next()) {
		if (check(nodes->cur() && !nodes->cur()->IsHyperEdge()))
			l->add(nodes->cur());
	}
}


void HyperGraph::GetNodes(List<Subject *> *l, int t) {
	// int c = l->count();
	for (nodes->first(); !nodes->done(); nodes->next()) {
		Subject *s = nodes->cur();
		if (check(s && !s->IsEdge())) {
			if (s->GetClassType() == t)
				l->add(s);
		}
	}
}

void HyperGraph::RemoveNode(Node *node){
	nodes->remove(node);
	for (hedges->first();!hedges->done(); ) {
	HyperEdge *e = hedges->cur();
	if (check(e)) {
			List <Subject *> *n1=e->GetSubject1();
			if (n1->contains(node)) hedges->removecur();
			     else{
			       List <Subject *> *n2=e->GetSubject2();
			       if (n2->contains(node)) hedges->removecur();
			       else hedges->next();
			}
	     }
	else hedges->next();
	}
}

void HyperGraph::GetHyperEdges(List <Subject *> *l){
	for (hedges->first(); !hedges->done(); hedges->next()) {
		HyperEdge *e = hedges->cur();
		if (check(e)) 
			l->add(e);
	}
}


void HyperGraph::GetHyperEdgesFrom(List <Subject *> *l,Subject *s){
	for (hedges->first(); !hedges->done(); hedges->next()) {
		HyperEdge *e = hedges->cur();
		if (check(e)) {
			if (e->IsDirected() && e->GetSubject1()->contains(s))
				l->add(e);
		}
	}
}

void HyperGraph::GetHyperEdgesTo(List <Subject *> *l,Subject *s){
	for (hedges->first(); !hedges->done(); hedges->next()) {
		HyperEdge *e = hedges->cur();
		if (check(e)) {
			if (e->IsDirected() && e->GetSubject2()->contains(s))
				l->add(e);

		}
	}
}


void HyperGraph::GetHyperEdgesFrom(List <HyperEdge *> *l,List <Subject *> *cfg){
	for (hedges->first(); !hedges->done(); hedges->next()) {
		HyperEdge *e = hedges->cur();
		if ((check(e)) && (e->IsDirected())){
		  List <Subject *> *source=e->GetSubject1();
		  bool Found=True;
		  for (source->first();!source->done();source->next()){
		    if (cfg->find(source->cur())<0) { // source->cur() not in cfg
		      Found=False;
		      break; // jump out of the for-loop
		    }
		  }
		  if (Found) // all sources of e are in cfg
		    l->add(e);
		}
	}
}

bool HyperGraph::ExistsSimilarHyperEdge(HyperEdge *he){
  for (hedges->first(); !hedges->done(); hedges->next()) {
    HyperEdge *e = hedges->cur();
    if (check(e)){
      if (*e==*he) return True;
    }
  }  
  return False;
}

