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

// Eliminate pseudo state nodes from graph structure by replacing edges
// with hyperedges.

#include <string.h>
#include "atddecisionstatenode.h"
#include "code.h"
#include "atdiagram.h"
#include "adseliminatepseudostatenodes.h"
#include "limits.h"
#include "bool.h"
#include "graph.h"
#include "atdtransitionedge.h"
#include "outputfile.h"
#include "../../dg/hyperedge.h"
#include "adsclock.h"
#include "adsclockconstraint.h"
#include "adsedgelabelparse.h"
#include "adsproperty.h"
#include "adspropertyvaluation.h"
#include "adsvariable.h"
#include "adshyperedge.h"




// some generic checks on activity graphs needed in order to make
// sure that the elimination of pseudo state nodes can be conducted
bool Elim::Check(Graph *g){
  List <Subject *>  gnodes;
  g->GetNodes(&gnodes); // the nodes of g
  for (gnodes.first();!gnodes.done();gnodes.next()){
    Subject *curnode;
    curnode=gnodes.cur();
    if (curnode->IsEdge()) {
      error("There is an edge having an edge as source or target!\n");
      return False;
    }
    if ((curnode->GetClassType()==Code::ATD_SYNCHRONIZATION_NODE) ||
	(curnode->GetClassType()==Code::ATD_DECISION_STATE_NODE)){
      List <Subject *> tempedges;
      if (g->GetEdgesFrom(&tempedges,curnode)==0) {
	error("There is a pseudo state node with no outgoing edges!\n");
	return False;
      }
      List <Subject *> tempedges2;
      if (g->GetEdgesTo(&tempedges2,curnode)==0) {
	error("There is a pseudo state node with no incoming edges!\n");
	return False;
      }
    }
    if (curnode->GetClassType()==Code::ATD_INITIAL_STATE_NODE){
      List <Subject *> tempedges;
      // initial state should have no incoming edges
      if (g->GetEdgesTo(&tempedges,curnode)>0) return False; 
    }
    if (curnode->GetClassType()==Code::FINAL_STATE){
      List <Subject *> tempedges;
      // final state should have no outgoing edges
      if (g->GetEdgesFrom(&tempedges,curnode)>0) return False;
    }
    if (curnode->GetClassType()==Code::ATD_DECISION_STATE_NODE){
      List <Subject *> tempedges;
      bool found=False;
      // final state should have no outgoing edges
      g->GetEdgesFrom(&tempedges,curnode);
      if (tempedges.count()>1){
	for (tempedges.first();!tempedges.done();tempedges.next()){
	  if ((tempedges.cur()->GetName()->contains("[else]"))||(tempedges.cur()->GetName()->length()==0)){
	    found=True;
	  }
	}
	if (!found){
	  error("There is a decision node with no [else] branch!\n");
	  return False;
	}
      }      
    }
  }

  List <Subject *>  gedges;
  g->GetEdges(&gedges); // the edges of g
  for (gedges.first();!gedges.done();gedges.next()){
    if (gedges.cur()->GetName()->contains("[else]")){
      if (((Edge *)gedges.cur())->GetSubject1()->GetClassType()!=Code::ATD_DECISION_STATE_NODE){
	error("There is a [else] branch that does not leave a decision node!\n");
	return False;
      }
    }
  }

  if (g->CountNodes(Code::ATD_INITIAL_STATE_NODE)==0){
    error("There is no initial node!\n");
    return False;
  }

  return True;
}



// eliminate every OR node by
// replacing every possible combination of an OR-entering hyperedge and an OR-exiting hyperedge by a new hyperedge
bool Elim::ElimOrNodes(ADSHyperGraph *h){
  List <Subject *> hnodes; // the nodes of activity machine h
  h->GetNodes(&hnodes);  
  for (hnodes.first();!hnodes.done();hnodes.next()){
    if (hnodes.cur()->GetClassType()==Code::ATD_DECISION_STATE_NODE){ // if OR node
      List <Subject *> eto; // hyperedges entering the OR node
      h->GetHyperEdgesTo(&eto,hnodes.cur());
      List <Subject *> efrom; // hyperedges exiting the OR node
      h->GetHyperEdgesFrom(&efrom,hnodes.cur());
      for (eto.first();!eto.done();eto.next()){ // for every hyperedge entering the OR node ...
	for (efrom.first();!efrom.done();efrom.next()){ // for every hyperedge exiting the OR node ...
	  if (efrom.cur()==eto.cur()) { // cycle detected
	    error("There is an or state node with a cycle\n");
	    return False;
	  }
	  
	  if (((ADSHyperEdge *)efrom.cur())->hasClockConstraint() && 
	      ((ADSHyperEdge *)eto.cur())->hasClockConstraint()){ // two clock constraints for same hyperedge
	    error("There are two segments in the hyperedge with a clock constraint\n");
	    return False;
	  }
	  
	  ADSHyperEdge *he =new ADSHyperEdge(h); // Create new hyperedge he for this combination of efrom.cur() and eto.cur()

	  // keep track of the simple edges that belong to this hyperedge;
	  // necessary to animate models and to give feedback etc, but not for execution 
	  List <Subject *> ls; 
	  ((ADSHyperEdge *)eto.cur())->GetEdges(&ls);
	  he->AddEdges(ls);
	  ls.empty();
	  ((ADSHyperEdge *)efrom.cur())->GetEdges(&ls);
	  he->AddEdges(ls);
	  ls.empty();

	  //
	  //	  he->AddPseudoNode(hnodes.cur());

	  string event;
	  // initialise event with the event label of either eto.cur() or efrom.cur()
	  if (((ADSHyperEdge *)eto.cur())->HasEmptyEvent())
	    event=((ADSHyperEdge *)efrom.cur())->GetEvent();
	  else if (((ADSHyperEdge *)efrom.cur())->HasEmptyEvent())
	    event=((ADSHyperEdge *)eto.cur())->GetEvent();
	  else {
	    error("Two edges connected by diamond have an event label");
	    return False;
	  }
	 

	  string s1=((ADSHyperEdge *)efrom.cur())->GetGuard(); // guard of exiting edge
	  string s2=((ADSHyperEdge *)eto.cur())->GetGuard(); // guard of entering edge
	  string guard;
	  if (s1=="") {
	    guard=s2;
	  }
	  else 
	    if (s2=="") 
	      guard=s1;
	    else{ // s1!="" && s2!=""		
	      s1.remove(0); // strip  [
	      s1.remove();// strip  ]
	      s2.remove(0); // strip [
	      s2.remove(); // strip ]
	      guard= "[("+ s2 + ")" + "&" + "(" + s1 + ")]";
	    }
	  he->SetLabel(event+guard);



	  // fill he with properties
	  List <Prop *> p1;
	  ((ADSHyperEdge *)eto.cur())->GetPropList(p1);
	  for (p1.first();!p1.done();p1.next()){
	    he->AddProp(p1.cur());
	  }
	  List <Prop *> p2;
	  ((ADSHyperEdge *)efrom.cur())->GetPropList(p2);
	  for (p2.first();!p2.done();p2.next()){
	    he->AddProp(p2.cur());
	  }
	  
	  // fill he with variables
	  List <ADSVar *> v1;
	  ((ADSHyperEdge *)eto.cur())->GetVarList(v1);
	  for (v1.first();!v1.done();v1.next()){
	    he->AddVar(v1.cur());
	  }
	  List <ADSVar *> v2;
	  ((ADSHyperEdge *)efrom.cur())->GetVarList(v2);
	  for (v2.first();!v2.done();v2.next()){
	    he->AddVar(v2.cur());
	  }
	      
	  // fill he with `in' nodes
	  List <Subject *> n1;
	  ((ADSHyperEdge *)eto.cur())->GetInNodes(&n1);
	  for (n1.first();!n1.done();n1.next()){
	    he->AddInNode(n1.cur());
	  }
	  List <Subject *> n2;
	  ((ADSHyperEdge *)efrom.cur())->GetInNodes(&n2);
	  for (n2.first();!n2.done();n2.next()){
	    he->AddInNode(n2.cur());
	  }

	  // fill he with `not in' nodes
	  List <Subject *> n3;
	  ((ADSHyperEdge *)eto.cur())->GetNotInNodes(&n3);
	  for (n3.first();!n3.done();n3.next()){
	    he->AddNotInNode(n3.cur());
	  }
	  List <Subject *> n4;
	  ((ADSHyperEdge *)efrom.cur())->GetNotInNodes(&n4);
	  for (n4.first();!n4.done();n4.next()){
	    he->AddNotInNode(n4.cur());
	  }
	       

	  //
	  if ((((ADSHyperEdge *)efrom.cur())->GetClockConstraint()) && (((ADSHyperEdge *)eto.cur())->GetClockConstraint())){ 
	    error("There are two clock constraints events in one hyperedge: I cannot deal with this (yet)\n");
	    return False;
	  }
	  else{
	    ClockConstraint *cnew=NULL;
	    if (((ADSHyperEdge *)efrom.cur())->GetClockConstraint()){
	      //cnew= new ClockConstraint(*(((ADSHyperEdge *)efrom.cur())->GetClockConstraint()));
	      cnew=(((ADSHyperEdge *)efrom.cur())->GetClockConstraint());
	    }
	    if (((ADSHyperEdge *)eto.cur())->GetClockConstraint()){
      	      // cnew= new ClockConstraint(*(((ADSHyperEdge *)eto.cur())->GetClockConstraint()));	    
	      cnew= (((ADSHyperEdge *)eto.cur())->GetClockConstraint());
	    }
	    he->SetClockConstraint(cnew); //possibly NULL
	  }

	  //
	  if ((((ADSHyperEdge *)efrom.cur())->GetSendEvent()) && (((ADSHyperEdge *)eto.cur())->GetSendEvent())){ 
	    error("There are two send events in one hyperedge: I cannot deal with this (yet)\n");
	    return False;
	  }
	  else{
	    if (((ADSHyperEdge *)efrom.cur())->GetSendEvent()){
	      he->SetSendEvent(((ADSHyperEdge *)efrom.cur())->GetSendEvent());
	    }
	    else he->SetSendEvent(((ADSHyperEdge *)eto.cur())->GetSendEvent()); //possibly NULL
	  }

	  // fill he with outgoing hyperedge	       
	  List <Subject *> *sources;
	  sources = ((ADSHyperEdge *)efrom.cur())->GetSubject1();
	  for (sources->first();!sources->done();sources->next()){ 
	    if (sources->cur()!=hnodes.cur()) 
	      he->AddSubject1(sources->cur()); //new
	  }
	  
	  List <Subject *> *targets;
	  targets = ((ADSHyperEdge *)efrom.cur())->GetSubject2();
	  for (targets->first();!targets->done();targets->next()){
	    if (targets->cur()!=hnodes.cur())
	      he->AddSubject2(targets->cur()); //new
	  }
	       
	  // fill he with incoming hyperedge
	  sources = ((ADSHyperEdge *)eto.cur())->GetSubject1();
	  for (sources->first();!sources->done();sources->next()){ 
	    if (sources->cur()!=hnodes.cur()) 
	      he->AddSubject1(sources->cur()); //new
	  }

	  targets = ((ADSHyperEdge *)eto.cur())->GetSubject2();
	  for (targets->first();!targets->done();targets->next()){
	    if (targets->cur()!=hnodes.cur()) 
	      he->AddSubject2(targets->cur()); //new
	  }

	  // check the resulting hyperedge
	  if (!he->GetSubject1()->isSet()){ 
	    error("There is a hyper edge whose source is no set!\n");
	    delete he;
	    return False;
	  } 
	  else if (!he->GetSubject2()->isSet()){ 
	    error("There is a hyper edge whose target is no set!\n");
	    delete he;
	    return False;
	  }
	  if (!h->ExistsSimilarHyperEdge(he)) h->AddHyperEdge(he);
	  else delete he;
	}
      }
      h->RemoveNode((Node *)hnodes.cur());
    }
  }
  return True;
}




// wrapper to call the parser
bool Elim::ParseGuardLabel(const string *str) {
  YY_BUFFER_STATE y = ::adsedgelabel_scan_string(str->getstr());
  strcpy(::adsedgelabel_constraint, "");
  bool b = !adsedgelabelparse();
  adsedgelabel_delete_buffer(y);
  return (b);
}

 
extern string replace(string s); // defined in adscks



// h is initialised with g. 
bool Elim::FillAH(Graph *g, ADSHyperGraph *h){
  // Fill h with nodes of g
  List <Subject *> gnodes; // nodes of g
  g->GetNodes(&gnodes);
  for (gnodes.first();!gnodes.done();gnodes.next()){
    if ((gnodes.cur()->GetClassType()==Code::NOTE)|| (gnodes.cur()->GetClassType()==Code::COMMENT)) continue;
    if (check(gnodes.cur()))
	      h->AddNode((Node *)gnodes.cur()); // BUG: gnodes.cur() now part of both g and h Fixing this bug is too much work for the moment. If the new hypergraph architecture for TCM is adopted, the problem will disappear
  }


  // Fill h with edges of g
  List <Subject *> gedges; // edges of g
  g->GetEdges(&gedges);
  for (gedges.first();!gedges.done();gedges.next()){
    string cons; // the string to be parsed
    if (gedges.cur()->GetName()->contains("[else]")){
      List <Subject *> outgoing;
      g->GetEdgesFrom(&outgoing,((Edge *)(gedges.cur()))->GetSubject1()); // get all edges that leave gedges.cur() 
      string str=""; // the string that will replace "else"
      for (outgoing.first();!outgoing.done();outgoing.next()){ 
	if (outgoing.cur()!=gedges.cur()){ // do not check gedges.cur()
	  string temp=outgoing.cur()->GetName()->getstr(); //::adsedgelabel_constraint;
	  if (temp.contains("else")) return False;
	  if (temp.contains('[')){  // if label has guard
	    while (!(temp[0]=='[')) temp.remove(0); // strip event part
	    temp.replace('[','('); 
	    temp.replace(']',')');
	  }
	  else temp="true"; // if label has no guard, guard "true" is assumed
	  if (str!="") str= str + "|" + temp; // put or (|) only if there is more than basic guard constraint 
	  else str = temp; // 
	}
      }
      
      if (str=="")  // else was the only outgoing edge of gedges.cur() ...
	return False;  // that is against syntax
      else 
	str = "[~(" +  str + ")]"; // make str a guard expression      
      string event = gedges.cur()->GetName()->getstr();	
      while (!event.endsWith("[")) event.remove(); // get the event part of adsedgelabel constraint (might be NULL)
      event.remove(); // remove [
      
      cons=event+str;  // new label for gedges.cur
    } 
    else{
      cons = gedges.cur()->GetName()->getstr();
    }
    ADSHyperEdge *he= new ADSHyperEdge(h,(Edge *)gedges.cur()); //source and target of new hyperedge he are copied from gedges.cur()
     
    // parse the label of gedges.cur()
    // initialise variables of the parser
    ::iprop=0;   // counter for propisitions in guards
    ::ivar=0; // counter for propisitions in guards
    ::iselse=0; // 
    ::iclock=0;
    ::isclock=0;
    ::indexin=0;
    ::notindexin=0;
    cons.replace('-','_');

    if (ParseGuardLabel(&cons)){ // the label can be parsed

      if (::isclock){ // event part is clock constraint (e.g. after(10))
	if (cons.contains('[')){ // cons has guard
	  while (!(cons[0]=='[')) cons.remove(0); // strip event part (clock constraint) from cons
	}
	else{
	  cons=""; // empty trigger event; clock constraint is modelled separately
	}
      }
      he->SetLabel(cons); 

      int j;
      // insert the properies into h and he
      for (j=0;j<(::iprop);j++){
	Prop *p=new Prop(::propname[j],::proptype[j]);
	if (!(h->AddProp(p))){
	  he->AddProp(h->FindSimilarProp(p));
	  delete p;
	}			    			    
	else he->AddProp(p);
      }      

      // insert the vars into h and he
      for (j=0;j<(::ivar);j++){
	ADSVar *v=new ADSVar(::varname[j],::vartype[j]);  
	if (!(h->AddVar(v))){
	  he->AddVar(h->FindSimilarVar(v));
	  delete v;
	}
	else he->AddVar(v);		  
      }	     

      // insert clock constraint into he
      for (j=0;j<(::iclock);j++){
	if (he->hasClockConstraint()) return False; // cannot occur in practice
	Clock *c;
	if (::clockconstrainttype[j]==AFTER){
	  c = new Clock(he);
	  ClockConstraint *cc=new ClockConstraint(c,AFTER,clockconstraint[j]);
	  he->SetClockConstraint(cc);	
	}
	else{  // when, not yet implemented
	  c = new Clock();
	}				
      }

      // insert `in' nodes
      List <Subject *> hnodes; // nodes of h
      h->GetNodes(&hnodes);     
      for (j=0;j<(::indexin);j++){
	string iname=inname[j];
	for (hnodes.first();!hnodes.done();hnodes.next()){
	  string hname=*(hnodes.cur()->GetName());
	  if (replace(hname)==replace(iname)){
	    he->AddInNode(hnodes.cur());
	    break;
	  }
	}
      }

 
      // insert `notin' nodes 
      for (j=0;j<(::notindexin);j++){
	string notiname=notinname[j];
	for (hnodes.first();!hnodes.done();hnodes.next()){
	  string hname=*(hnodes.cur()->GetName());
	  if (replace(hname)==replace(notiname)){
	    he->AddNotInNode(hnodes.cur());
	    break;
	  }
	}
      }

      if (::hasaction){ //TODO : add check that action is double defined
	Prop *p=new Prop(::sendeventname,SENDEVENT);
	h->AddProp(p);
	he->SetSendEvent(p);
      }
    } 
    else { // not Parseguardlabel
      error( "Guard label %s could not be parsed! (edge %d)\n",gedges.cur()->GetName()->getstr(), gedges.cur()->GetId());
      return False;
    }
    //    he->Write();
    h->AddHyperEdge(he);	        // add he to h 
  }
  return True;
}




// for every AND pseudo state do 
// glue all in and out going hyper edges together
bool Elim::ElimAndNodes(ADSHyperGraph *h){
  List <Subject *> l; // nodes of h
  h->GetNodes(&l);  
  for (l.first();!l.done();l.next()){
    if (l.cur()->GetClassType()==Code::ATD_SYNCHRONIZATION_NODE){ // AND pseudo state node
      ADSHyperEdge *he =new ADSHyperEdge(h); // the new hyperedge

      List <Subject *> efrom;       //  hyperedges that enter the AND node
      h->GetHyperEdgesFrom(&efrom,l.cur());

      List <Subject *> eto; //  hyperedges that leave the AND node
      h->GetHyperEdgesTo(&eto,l.cur());

      for (efrom.first();!efrom.done();efrom.next()){
	for (eto.first();!eto.done();eto.next()){
	  if (efrom.cur()==eto.cur()) { // hyperedge has AND as source and target
	    error("There is an and state node with a cycle\n");
	    return False;
	  }
	  if (((ADSHyperEdge *)efrom.cur())->hasClockConstraint() && 
	      ((ADSHyperEdge *)eto.cur())->hasClockConstraint()){
	    error("There are two segments in the hyperedge with a clock constraint\n");
	    return False;
	  }
	}
      }


      string event; // only of one incoming edge

      ClockConstraint *cc=NULL; // only of one incoming edge

      // fill the new hyperedge he with all the sources 
      // of all hyperedges that enter the and node
      for (eto.first();!eto.done();eto.next()){
	cc= ((ADSHyperEdge *)eto.cur())->GetClockConstraint();
	if ((!((ADSHyperEdge *)eto.cur())->HasEmptyEvent()) && (event=="")){
	  event=((ADSHyperEdge *)eto.cur())->GetEvent();
	  List <Prop *> p;
	  ((ADSHyperEdge *)eto.cur())->GetPropList(p);
	  for (p.first();!p.done();p.next()){
	    if (p.cur()->GetType()==EVENT) he->AddProp(p.cur());
	  }	  
	}
	List <Subject *> *sources;
	sources = ((ADSHyperEdge *)eto.cur())->GetSubject1();
	for (sources->first();!sources->done();sources->next()){ 
	  if (sources->cur()!=l.cur()) // do not insert the AND node as sources
	    he->AddSubject1(sources->cur()); 
	}
	
	List <Subject *> *targets;
	targets = ((ADSHyperEdge *)eto.cur())->GetSubject2();
	for (targets->first();!targets->done();targets->next()){
	  if (targets->cur()!=l.cur()) // do not insert the AND node as sources
	    he->AddSubject2(targets->cur()); 
	}
	List <Subject *> ls;
	((ADSHyperEdge *)eto.cur())->GetEdges(&ls);// the edges in the original activity diagram that are represented by the hyperedge
	he->AddEdges(ls); 
      } 

      // add to he the pseudo state node that is being eliminated
      //      he->AddPseudoNode(l.cur());

      // fill the new hyperedge he with all the targets 
      // of all hyperedges that leave the and node
      for (efrom.first();!efrom.done();efrom.next()){
	if ((!((ADSHyperEdge *)efrom.cur())->HasEmptyEvent()) && (event=="")){
	  event=((ADSHyperEdge *)efrom.cur())->GetEvent();
	  List <Prop *> p;
	  ((ADSHyperEdge *)efrom.cur())->GetPropList(p);
	  for (p.first();!p.done();p.next()){
	    if (p.cur()->GetType()==EVENT) he->AddProp(p.cur());
	  }	  
	}

	List <Subject *> *sources;
	sources = ((ADSHyperEdge *)efrom.cur())->GetSubject1();
	for (sources->first();!sources->done();sources->next()){ 
	  if (sources->cur()!=l.cur())  // do not insert the AND node as target
	    he->AddSubject1(sources->cur()); 
	}
	List <Subject *> *targets;
	targets = ((ADSHyperEdge *)efrom.cur())->GetSubject2();
	for (targets->first();!targets->done();targets->next()){
	  if (targets->cur()!=l.cur())  // do not insert the AND node as target
	    he->AddSubject2(targets->cur()); 
	}
	List <Subject *> ls;
	((ADSHyperEdge *)efrom.cur())->GetEdges(&ls); // the edges in the original activity diagram that are represented by the hyperedge
	he->AddEdges(ls);
      }

      he->SetLabel(event); 
      he->SetClockConstraint(cc); 

      if (!he->GetSubject1()->isSet()){ 
	error("There is a hyper edge whose source is no set!\n");
	return False;
      } 
      else 
	if (!he->GetSubject2()->isSet()){ 
	  error("There is a hyper edge whose target is no set!\n");
	   return False;
	}
      
      if (!h->ExistsSimilarHyperEdge(he)) h->AddHyperEdge(he);
      h->RemoveNode((Node *)l.cur()); // remove the and node      
    }
  }  
  return True;
}



// set for each basic prop that refers to a var, the var it refers to.
// not necessary for elimination of pseudo state nodes
void Elim::UpdatePropList(ADSHyperGraph *ah){
  List <Prop *> pl;
  ah->GetPropList(pl);
  
  List <ADSVar *> vl;
  ah->GetVarList(vl);
  
  for (pl.first();!pl.done();pl.next()){
    if ((pl.cur()->GetType() == (::INT))||(pl.cur()->GetType() == (::PROP)) || (pl.cur()->GetType() == (::STRING))){
      ::iprop=0;   // counter for propisitions in guards
      ::ivar=0;
      ::iselse=0;
      ::iclock=0;
      ::isclock=0;
      ::indexin=0;
      ::notindexin=0;
      string prop =pl.cur()->GetName();
      string guard= "[" + prop + "]";      
      if (ParseGuardLabel(&guard)) { // always true
	 int j;
	 for (j=0;j<(::ivar);j++){
	   ADSVar *v=new ADSVar(::varname[j],::vartype[j]);  
	   bool found=False;
	   for (vl.first();!vl.done();vl.next()){
	     if (*v==*vl.cur()){
	       pl.cur()->SetVar(vl.cur());
	       found=True;
	       break;
	     }
	   }
	   if (!found) error("I could not find the variable...!\n"); // var should already be present
	 }
      }
      else error( "I could not parse a label that I could parse before. Am I growing old?\n");
    }
  }
}


    
  





bool Elim::EliminatePseudoStateNodes(Graph *g, ADSHyperGraph *h){
  if (Check(g)){ 
     if (FillAH(g,h)){ 
       ElimAndNodes(h);     
       ElimOrNodes(h);    
       UpdatePropList(h);  
       return True;
     }
  }
  return False;
}



