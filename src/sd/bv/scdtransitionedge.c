////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "scdtransitionedge.h"
#include "scgraph.h"
#include "inputfile.h"
#include "outputfile.h"
#include "error.h"


#include "adsproperty.h"
#include "scnode.h"

SCDTransitionEdge::SCDTransitionEdge(SCGraph *g, Subject *n1, Subject *n2)
	:Edge(g, n1, n2)
{
	SetDirected(True);

	sendevent=0;
	cc=0;
	label="";
}

string SCDTransitionEdge::GetLabel(){
  return label;
}
 
void SCDTransitionEdge::SetLabel(string s){
  label=s;
}
 
 
string SCDTransitionEdge::GetEvent(){
  string txt="";
  unsigned i=0;
  while (i<label.length()){
    if ((label[i]=='[')||(label[i]=='/')) return txt;
    else {
      txt= txt +label[i];
      i++;
    }
  }
  return txt;
}  
 
string SCDTransitionEdge::GetGuard(){
  string txt="";
  unsigned i=0;
  while ((i<label.length()) && (label[i]!='[')) i++;
  if (i==label.length()) return txt;
  else {
    while ((i<label.length())&&(label[i]!='/')){
      txt = txt + label[i];
      i++;
    }
    return txt;
  }  
}
 
 
 
bool SCDTransitionEdge::HasEmptyEvent(){
  return (GetEvent()=="");
}
 
 
bool SCDTransitionEdge::HasEmptyGuard(){     
  return (GetGuard()=="");
}
 
 

bool SCDTransitionEdge::AddProp(Prop *p){
  for (propl.first();!propl.done();propl.next()){
    if (*propl.cur()==*p) return False;
  }
  propl.add(p);
  return True;
}

void SCDTransitionEdge::GetPropList(List <Prop *> &p){
  p=propl;
}


void SCDTransitionEdge::SetClockConstraint(ClockConstraint *c){
  cc=c;
}


ClockConstraint *SCDTransitionEdge::GetClockConstraint(){
  return cc;
}


bool SCDTransitionEdge::hasClockConstraint(){
  return (cc!=0);
}

string SCDTransitionEdge::GetUniqueName(){
  string str="HE_"; 
  string hid=(unsigned int)GetId();
  return str+hid;
}


SCNode *SCDTransitionEdge::GetScope(){
  if (!GetSubject1()->GetParent()) return 0;
  List <SCNode *> scnodes;
  GetGraph()->GetNodes((List <Subject *> *)&scnodes);
  SCNode *scope=0;
  for (scnodes.first();!scnodes.done();scnodes.next()){
    if (scnodes.cur()->GetClassType()==Code::SCD_OR_STATE){
      if (((SCNode *)(GetSubject1()))->isancestor(scnodes.cur())
	   && (((SCNode * )GetSubject2())->isancestor(scnodes.cur()))){
	if (scope){
	  if (scnodes.cur()->isancestor(scope)){
	    scope=scnodes.cur();
	  }
	}
	else scope=scnodes.cur();
      }
    }
  }
  return scope;
}

