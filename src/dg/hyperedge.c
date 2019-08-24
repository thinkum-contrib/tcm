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
#include "inputfile.h"
#include "outputfile.h"
#include "util.h"
#include "assoclist.h"
#include "hypergraph.h"
#include "hyperedge.h"
#include "string.h"


HyperEdge::HyperEdge(HyperGraph *g, List<Subject *> *n1, List<Subject *> *n2): Subject(g) {
  subject1 = n1; 
  subject2 = n2;
  directed = True;
}

HyperEdge::HyperEdge(HyperGraph *g,Edge *e): Subject(g) {
  subject1= new List<Subject *>();
  subject1->add(e->GetSubject1()); 
  subject2= new List<Subject *>();
  subject2->add(e->GetSubject2());
  directed = True;
}

HyperEdge::HyperEdge(HyperGraph *g): Subject(g){
  subject1= new List <Subject *>;
  subject2= new List <Subject *>; 
  directed = True;
}

bool HyperEdge::operator==(HyperEdge &comp){
  // compare the configurations
  // compare the property valuations
  int sourcelen=subject1->count();
  int compsourcelen=comp.subject1->count();
  int i,j;
  for (i=0;i<sourcelen;i++){
    if (!comp.subject1->contains((*subject1)[i])) return False;
  }
  for (j=0;j<compsourcelen;j++){
    if (!subject1->contains((*(comp.subject1))[j])) return False;
  }

  int targetlen=subject2->count();
  int comptargetlen=comp.subject2->count();
 
  for (i=0;i<targetlen;i++){
    if (!comp.subject2->contains((*subject2)[i])) return False;
  }
  for (j=0;j<comptargetlen;j++){
    if (!subject2->contains((*(comp.subject2))[j])) return False;
  }
 
  return (label==comp.label);
}
 



HyperEdge::~HyperEdge() {
  delete subject1;
  delete subject2;
}


bool HyperEdge::InGraph() const {
  return GetHyperGraph()->HasHyperEdge((HyperEdge *)this);
}

 
void HyperEdge::WriteMembers(OutputFile *ofile) {
  Subject::WriteMembers(ofile);
  for (subject1->first();!subject1->done();subject1->next()){
    (*ofile) << "\t{ Subject1 " << (check(subject1->cur())? 
				    subject1->cur()->GetId():0) << " }\n";
  }
  for (subject2->first();!subject2->done();subject2->next()){
    (*ofile) << "\t{ Subject2 " << (check(subject2->cur())? 
				    subject2->cur()->GetId():0) << " }\n";
  }
  (*ofile) << "\t{ Label: " << label <<"\n";
  (*ofile) << "}\n";
}


void HyperEdge::AddSubject1(Subject *s){
  subject1->add(s);
}

void HyperEdge::AddSubject2(Subject *s){
  subject2->add(s);
}



string HyperEdge::GetLabel(){ 
  return label;
}

void HyperEdge::SetLabel(string s){ 
  label=s;
}


string HyperEdge::GetEvent(){
  string txt="";
  unsigned i=0;
  while (i<label.length()){
    if (label[i]=='[') return txt;
    else {
      txt= txt +label[i]; 
      i++;
    }
  }
  return txt;
}

string HyperEdge::GetGuard(){
  string txt="";
  unsigned i=0;
  while ((i<label.length()) && (label[i]!='[')) i++;
  if (i==label.length()) return txt;
  else {
    while (i<label.length()){
      txt = txt + label[i];
      i++;
    }
    return txt;
  }
}



bool HyperEdge::HasEmptyEvent(){
  return (GetEvent()=="");
}




bool HyperEdge::HasEmptyGuard(){
  return (GetGuard()=="");
}


