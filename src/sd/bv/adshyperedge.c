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
#include "adshyperedge.h"
#include "adshypergraph.h"
#include "adsproperty.h"
#include "adsvariable.h"
#include "outputfile.h"
#include "adsclockconstraint.h"
//#include <stdlib.h> // for NULL only



     
ADSHyperEdge::ADSHyperEdge(ADSHyperGraph *a, Edge *e): HyperEdge(a,e){
  cc=NULL;
  edgelist.add(e);
  sendevent=NULL;
};

bool ADSHyperEdge::AddProp(Prop *p){
  for (propl.first();!propl.done();propl.next()){
    if (*propl.cur()==*p) return False;
  }
  propl.add(p);
  return True;
}

bool ADSHyperEdge::AddVar(ADSVar *v){
  for (varl.first();!varl.done();varl.next()){
    if (*varl.cur()==*v) return False;
  }
  varl.add(v);
  return True;
}

void ADSHyperEdge::GetPropList(List <Prop *> &p){
  p=propl;
}

void ADSHyperEdge::GetVarList(List <ADSVar *> &v){
  v=varl;
}


void ADSHyperEdge::SetClockConstraint(ClockConstraint *c){
  cc=c;
}


ClockConstraint *ADSHyperEdge::GetClockConstraint(){
  return cc;
}


bool ADSHyperEdge::hasClockConstraint(){
  return (cc!=NULL);
}


bool ADSHyperEdge::conflicts(ADSHyperEdge *he){
  return conflict.contains(he);
}

bool ADSHyperEdge::isconflicting(){
  return (conflict.count()>0);
}

void ADSHyperEdge::AddEdges(List <Subject *> l){
  for (l.first();!l.done();l.next()){
    edgelist.add(l.cur());
  }
}

void ADSHyperEdge::GetEdges(List <Subject *> *l){
  for (edgelist.first();!edgelist.done();edgelist.next()){
    l->add(edgelist.cur());
  }
}


string ADSHyperEdge::GetUniqueName(){
  string str="HE_"; 
  string hid=(unsigned int)GetId();
  return str+hid;
}

void ADSHyperEdge::WriteMembers(OutputFile *f){
  (*f) << "HYPEREDGE ID " << GetId() <<"\n";
  HyperEdge::WriteMembers(f);
  for (propl.first();!propl.done();propl.next()){ 
    (*f) << "\tPRoperty\n";
    propl.cur()->Write(f);
    (*f) << "\n";
  }
  (*f) << "Clock constraint\n";
  if (cc!=NULL) cc->Write(f);
  if (sendevent!=NULL){
    (*f) << "\tSEND EVENT:\t"; 
    sendevent->Write(f);
    (*f) << "\n";
  }
  for (inlist.first();!inlist.done();inlist.next()){ 
    (*f) << "INLIST\n\t\t";
    inlist.cur()->Write(f);
    (*f) << "\n";
  }
  for (notinlist.first();!notinlist.done();notinlist.next()){ 
    (*f) << "NOT INLIST\n\t\t";
    notinlist.cur()->Write(f);
    (*f) << "\n";
  }
  for (edgelist.first();!edgelist.done();edgelist.next()){
    (*f) << "\tedge ID:\t" << edgelist.cur()->GetId() << "\n";
  }
  (*f) << "\n";
}

void ADSHyperEdge::WriteScreen(){
  std::cout << "HYPEREDGE ID " << GetId() <<"\n";

  for (propl.first();!propl.done();propl.next()){ 
    std::cout << "\tPRoperty\n";
    propl.cur()->Write();
    std::cout << "\n";
  }

}


