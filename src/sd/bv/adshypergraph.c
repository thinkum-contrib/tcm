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
#include "adshypergraph.h"
#include "code.h"
#include "atdactionstatenode.h"
#include "adsactivity.h"
#include "adshyperedge.h"
#include "adsvariable.h"
#include "adsproperty.h"
#include "outputfile.h"
#include "adsclock.h"
#include "node.h"
#include "adsclockconstraint.h"
#include "util.h"
#include "adssemantics.h"


 
extern string replace(string s); // defined in adscks


ADSHyperGraph::ADSHyperGraph() :HyperGraph() {
  timeoutnumber=0;
}

ADSHyperGraph::~ADSHyperGraph(){}



void ADSHyperGraph::ComputeInternalProperties(){
  intproplist.empty();
  for (updatedinactivities.first();!updatedinactivities.done();updatedinactivities.next()){
    for (propl.first();!propl.done();propl.next()){
      if (propl.cur()->GetVar()==updatedinactivities.cur()){ // note == on addr
	  switch (propl.cur()->GetType()) {
	  case ::INT :     propl.cur()->SetType(::INTERNAL_INT);break;
	  case ::PROP :    propl.cur()->SetType(::INTERNAL_PROP);break;
	  case ::STRING :  propl.cur()->SetType(::INTERNAL_STRING);break;
	  default : ;
	  }
	  intproplist.add(propl.cur());
      }
    }
  }
  int length=propl.count();
  for (int i=0;i<length;i++){
    if (propl[i]->GetType()==EVENT){ 
      List <Subject *> edges;
      GetHyperEdges(&edges);
      for (edges.first();!edges.done();edges.next()){	
	Prop *p=((((ADSHyperEdge *)edges.cur())->GetSendEvent()));
	if ((p) && (*p==*propl[i])){ // EVENT is triggered by SENDEVENT
	  propl[i]->SetType(::SENDEVENT); // then set EVENT to SENDEVENT
	  continue;
	}
      }	
    }
  }
}

void ADSHyperGraph::ComputeInternalHyperEdges(){
  List <Subject *> edges;
  GetHyperEdges(&edges);
  for (edges.first();!edges.done();edges.next()){	
    List <Prop *> proplist;
    ((ADSHyperEdge *)edges.cur())->GetPropList(proplist);
    for (proplist.first();!proplist.done();proplist.next()){
      if (proplist.cur()->GetType()==::SENDEVENT){
	((ADSHyperEdge *)edges.cur())->SetInternal();
      }
    }
  }
}
	  


void ADSHyperGraph::ComputeExternalProperties(){
  extproplist.empty();
  for (propl.first();!propl.done();propl.next()){
    if (!(propl.cur()->isInternal())){
	extproplist.add(propl.cur());
      }    
  }
}


void ADSHyperGraph::ComputeActivities(){
  actlist.empty();
  updatedinactivities.empty();

  for (nodes->first();!nodes->done();nodes->next()){
    if (((ATDActionStateNode *)nodes->cur())->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      string s=*(nodes->cur()->GetName());
      ADSActivity *newact=new ADSActivity(s); // create new activity

      // insert newact into actlist, if it was not in it already
      bool b=True;
      for (actlist.first();!actlist.done();actlist.next()){
	if (*actlist.cur()==*newact) {
	  b=False; 
	  delete newact;
	  newact=actlist.cur();
	  break;
	}
      }
      if (b) actlist.add(newact);
      ((ATDActionStateNode *)nodes->cur())->SetActivity(newact); 
    

      List <Subject *> *l=new List <Subject *>;
      GetHyperEdgesFrom(l,nodes->cur());
      for (l->first();!l->done();l->next()){
	List <ADSVar *> vl;
	((ADSHyperEdge *)l->cur())->GetVarList(vl);
	for (vl.first();!vl.done();vl.next()){
	  newact->AddUpdate(vl.cur());
	  
	  // update updatedinactivities
	  bool found=False;
	  for (updatedinactivities.first();!updatedinactivities.done();updatedinactivities.next()){		   
	    if (*updatedinactivities.cur()==*vl.cur()){
	      found=True;
	      break;
	    }
	  }
	  if (!found) updatedinactivities.add(vl.cur());
	}
      }    
      
    }
  }
}


void ADSHyperGraph::ComputeInterferences(){
  int count=actlist.count();
  int i,j;
  // Begin computation of conflicts
  for (i=0;i<count;i++){
    List <ADSVar *> l1;
    actlist[i]->GetUpdateList(l1);
    
    for (j=i;j<count;j++){
      List <ADSVar *> l2;
      actlist[j]->GetUpdateList(l2);
      interference[i][j]=0;
      for (l1.first();!l1.done();l1.next()){

	bool b=False;
	for (l2.first();!l2.done();l2.next()){
	  ADSVar *v1=l1.cur();
	  ADSVar *v2=l2.cur();
	  if (*v1==*v2){
	    interference[i][j]=1;
	    b=True;
	    break;
	  }
	}
	if (b) break; // conflict[i][j] already found
      }
    }
  }
}

bool ADSHyperGraph::GetInterference(ADSActivity *a1,ADSActivity *a2){ // action state node???
  int i1=actlist.find(a1);
  int i2=actlist.find(a2);
  if ((i1==-1) || (i2==-1)) return False;
  if (i1<i2) 
    return interference[i1][i2];
  else 
    return interference[i2][i1];
}

bool ADSHyperGraph::GetInterference(ATDActionStateNode *a1, ATDActionStateNode *a2){
  string a1name=*a1->GetName();
  string a2name=*a2->GetName();
  ADSActivity *a1new= new ADSActivity(a1name);
  ADSActivity *a2new= new ADSActivity(a2name);
  ADSActivity *a1old=0, *a2old=0;
  bool b1=False;
  bool b2=False;
  for (actlist.first();!actlist.done();actlist.next()){
    if (*a1new==*actlist.cur()) {a1old=actlist.cur();b1=True;}
    if (*a2new==*actlist.cur()) {a2old=actlist.cur();b2=True;}
    if (b1&&b2) break;
  }
  if (b1&&b2) 
    return GetInterference(a1old,a2old);
  else // not found? I'm confused!
    return False;
}


void ADSHyperGraph::Initialise(){
  ComputeActivities();
  ComputeInterferences();
  ComputeConflicts();
  ComputeInternalProperties();
  ComputeExternalProperties();
  ComputeInternalHyperEdges();
  ComputeNrTimeouts();
  SetInitialFinalNames();
  InitialiseBounds();
}

void ADSHyperGraph::Finalise(){
   UnSetInitialFinalNames();
}

bool ADSHyperGraph::AddProp(Prop *p){
  for (propl.first();!propl.done();propl.next()){
    if (*propl.cur()==*p) return False;
  }
  propl.add(p);
  return True;
}

bool ADSHyperGraph::AddVar(ADSVar *v){
  for (varl.first();!varl.done();varl.next()){
    if (*varl.cur()==*v) return False;
  }
  varl.add(v);
  return True;
}


void ADSHyperGraph::RemoveProp(Prop *p){ 
  propl.remove(p);
}

void ADSHyperGraph::GetPropList(List <Prop *> &p){
  p=propl;
}

void ADSHyperGraph::GetExtPropList(List <Prop *> &p){
  p=extproplist;
}

void ADSHyperGraph::GetIntPropList(List <Prop *> &p){
  p=intproplist;
}

void ADSHyperGraph::GetVarList(List <ADSVar *> &v){
  v=varl;
}

Prop *ADSHyperGraph::FindSimilarProp(Prop *p){
  for (propl.first();!propl.done();propl.next()){
    if (*propl.cur()==*p) return propl.cur();
  }
  return 0;
}  

ADSVar *ADSHyperGraph::FindSimilarVar(ADSVar *p){
  for (varl.first();!varl.done();varl.next()){
    if (*varl.cur()==*p) return varl.cur();
  }
  return 0;
}  

Node *ADSHyperGraph::FindNode(string name){
  //  List <Subject *> nodes;
  //  GetNodes(&nodes);
  for (nodes->first();!nodes->done();nodes->next()){
    if (replace(*(nodes->cur()->GetName()))==replace(name)){
      return (Node*)(nodes->cur());
    }
  }
  return NULL;
}


//ADSActivity *ADSHyperGraph::FindAct(string s){
//  ADSActivity *a = new ADSActivity(s);
//  for (actlist.first();!actlist.done();actlist.next()){
//    if (*actlist.cur()==*a) return actlist.cur();
//  }
//  return 0;
//}



// The now following procedure is old, since we now discretise 
// all clocks with 1, not with 1/nr of timeouts
void ADSHyperGraph::ComputeNrTimeouts(){
  //  List <Subject *> amhedges;
  //  GetHyperEdges(&amhedges);
  // for (amhedges.first(); !amhedges.done(); amhedges.next()) {
  //    if (((ADSHyperEdge *)amhedges.cur())->hasClockConstraint()) timeoutnumber++;
  //  }
  timeoutnumber=0; // discretisation with 1
}

void ADSHyperGraph::WriteSubjects(OutputFile *f) {
  HyperGraph::WriteSubjects(f);
  (*f) << "INTERNAL PROPERTY LIST \n";
  for (intproplist.first();!intproplist.done();intproplist.next()){
    intproplist.cur()->Write(f);
  }
  (*f) << "EXTERNAL PROPERTY LIST \n";
  for (extproplist.first();!extproplist.done();extproplist.next()){
    extproplist.cur()->Write(f);
  }
  List <Subject *> amhedges;
  GetHyperEdges(&amhedges);
  int actcount=actlist.count();
  for (int i=0;i<actcount;i++){
    (*f) << i << ":\t";
    actlist[i]->Write(f);
    for (int j=i+1;j<actcount;j++){
      if (GetInterference(actlist[i],actlist[j])){
	(*f) << "1";;
      }
      else (*f) << "0";
    }
    (*f) << "\n";
  } 
}



void ADSHyperGraph::UpdateBounds(Bag <Subject *> *cfg){
  List <Subject *> ls;
  cfg->GetSet(&ls);
  List <Node *> ahnodes;
  GetNodes((List <Subject *> *)&ahnodes);
  int count=ahnodes.count();
  for (int i=0;i<count;i++){ 
    int c=cfg->count(ahnodes[i]);
    if (c>bound[i]) bound[i]=c;
  }
}

void ADSHyperGraph::InitialiseBounds(){
  List <Node *> ahnodes;
  GetNodes((List <Subject *> *)&ahnodes);
  int ahnodescount=ahnodes.count();
  int i;
  for (i=0;i<ahnodescount;i++){
    bound[i]=0;
  }
}

int ADSHyperGraph::GetBound(Subject *s){
  List <Subject *> ahnodes;
  GetNodes(&ahnodes);
  int index=ahnodes.find(s);
  if (index==-1) error ("A node that does not exist cannot have a bound!\n");
  return bound[index];
}


void ADSHyperGraph::ComputeConflicts(){
  List <ADSHyperEdge *> hyperedges;
  GetHyperEdges((List <Subject *> *)&hyperedges);
  int hedgescount = hyperedges.count();
  for (int i=0;i<hedgescount;i++){
    // the same hyperedges cannot be in conflict since otherwise they would not have enabled simultaneously
    List <Subject *> *source_i=hyperedges[i]->GetSubject1();
    for (int j=i+1;j<hedgescount;j++){      
      List <Subject *> *source_j=hyperedges[j]->GetSubject1();
      for (source_j->first();!source_j->done();source_j->next()){
	if (source_i->find(source_j->cur())>-1){ // hyperedges[i] and hyperedges[j] have overlapping sources
	  hyperedges[i]->AddConflict(hyperedges[j]);
	  hyperedges[j]->AddConflict(hyperedges[i]);
	  break; // jump out of for-loop
	}
      }
    }
  }
}

void ADSHyperGraph::SetInitialFinalNames(){
  List <Subject *> ahnodes;
  GetNodes(&ahnodes);
  for (ahnodes.first();!ahnodes.done();ahnodes.next()){
    string s=(*(ahnodes.cur()->GetName()));
    if (ahnodes.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE){
      s="I___INITIAL";ahnodes.cur()->SetName(&s);
    }
    if (ahnodes.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE){
      string t = (int)ahnodes.cur()->GetId();
      s="F___FINAL"+t; ahnodes.cur()->SetName(&s);
    }
  }
}    
 
void ADSHyperGraph::UnSetInitialFinalNames(){
  List <Subject *> ahnodes;
  GetNodes(&ahnodes);
  for (ahnodes.first();!ahnodes.done();ahnodes.next()){
    if ((ahnodes.cur()->GetClassType()!=Code::ATD_INITIAL_STATE_NODE)||(ahnodes.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE)) continue; // skip these
    if (ahnodes.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE){
      string s=""; ahnodes.cur()->SetName(&s);
    }
    if (ahnodes.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE){
      string s=""; ahnodes.cur()->SetName(&s);
    }
  }
}    
 

void PrintBag(Bag <ADSHyperEdge *> *b){
  List <ADSHyperEdge *> l;
  b->GetList(l);
  for (l.first();!l.done();l.next()){
    std::cout << l.cur()->GetId() <<":\t" << b->count(l.cur()) <<"\n";
  }
}

bool ADSHyperGraph::isConflicting(Bag <ADSHyperEdge *> *step, ADSHyperEdge *he){
  List <ADSHyperEdge *> al; // the list of hyperedges in conflict with he
  he->GetConflict(&al); 
  for (al.first();!al.done();al.next()){
    if (step->count(al.cur())) return True;
  }
  return False;
}

 
 
string ADSHyperGraph::DeadEdgesNodesConstraints(){
  string constraint;
  List <ADSHyperEdge *> hyperedges;
  GetHyperEdges((List <Subject *> *)&hyperedges);
  int hedgescount = hyperedges.count();
  for (int i=0;i<hedgescount;i++){
    if (i)
      constraint += " & ";
 
    List <Subject *> *source_i=hyperedges[i]->GetSubject1();
    bool First=True;
    string sourceconstraint;
    for (source_i->first();!source_i->done();source_i->next()){
      if (!First)
        sourceconstraint+=" & ";
      else
        First=False;
      string s=(*(source_i->cur()->GetName()));
      sourceconstraint += replace(s) + " > 0 " ;
    }
 
    List <Subject *> *target_i=hyperedges[i]->GetSubject2();
    First=True;
    string targetconstraint;
    for (target_i->first();!target_i->done();target_i->next()){
      if (!First)
        targetconstraint+=" & ";
      else
        First=False;
      string s=(*(target_i->cur()->GetName()));
      targetconstraint += replace(s) + " > 0 ";
    }
    constraint += "( EF (" + sourceconstraint + " & (EX (" + targetconstraint +
"))))";
  }
 
  return constraint;
}





string ADSHyperGraph::ComputeFinalPredicate(){
  string final="( (";
  List <Subject *> ls;
  GetNodes(&ls); // get all the nodes
  bool First=True;
  for (ls.first();!ls.done();ls.next()){
    if ((ls.cur()->GetClassType()==Code::NOTE)||(ls.cur()->GetClassType()==Code::COMMENT)||(ls.cur()->GetClassType()==Code::ATD_DECISION_STATE_NODE)||(ls.cur()->GetClassType()==Code::ATD_SYNCHRONIZATION_NODE)||(ls.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE)) continue; // skip these
    if (!First){
      final += " & ";
    }
    else{
      First=False;
    }
    if (ls.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE){
      final+="I___INITIAL=0";
    }
    else{ // action or wait state node
      string stemp=(*(ls.cur()->GetName()));
      stemp.replace("-\r","");
      stemp.replace('\r','_');
      stemp.replace(' ','_');
      stemp.replace('/','_');
      stemp.replace('.','_');
      stemp.replace('-','_');
      stemp += "=0";
      final+=stemp;
    }
  }  
  final += ") & ( 0 ";


  // First=True;
  string finalexpr;
  for (ls.first();!ls.done();ls.next()){
    if (ls.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE){
      finalexpr += " | ";
      finalexpr+="F___FINAL";
      string index = (int)ls.cur()->GetId();
      finalexpr = finalexpr + index + ">0";
    }
  }  

  final += finalexpr;
  final += ") )";
  return final;
}


void ADSHyperGraph::GetFinalNodes(List <Subject *> *final){
  for (nodes->first();!nodes->done();nodes->next()){
    if (nodes->cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE){
      final->add(nodes->cur());
    }
  }  
}



// Note: only works for safe activity graphs
void ADSHyperGraph::WriteNuSMV(OutputFile *ofile, bool sf){ 
  (*ofile) <<  "MODULE main\n\nVAR\n";
  List <Subject *> amnodes;
  GetNodes(&amnodes);
  List <ADSHyperEdge *> amedges;
  GetHyperEdges((List<Subject *> *)&amedges);

  List <Subject *> writtennodes; // nodes written as var so far
  List <Subject *> writtenedges; // edges written as var so far
  List <Prop *> writtenprop; // edges written as var so far
  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if (amnodes.cur()->GetClassType()!=Code::ATD_INITIAL_STATE_NODE) continue; // skip these nodes
    string s=(*(amnodes.cur()->GetName()));
    writtennodes.add(amnodes.cur());
    (*ofile ) << "\t"<< replace(s) << " : boolean;\n";
  }

  while(writtennodes.count()<amnodes.count())  {
    List <ADSHyperEdge *> newenabled;
    GetHyperEdgesFrom((List <HyperEdge *> *)&newenabled,&writtennodes);
    for (newenabled.first();!newenabled.done();newenabled.next()){
      if (!writtenedges.contains(newenabled.cur())){
	writtenedges.add(newenabled.cur());
	List <Prop *> pl;
	newenabled.cur()->GetPropList(pl);
	for (pl.first();!pl.done();pl.next()){
	  if (!((pl.cur()->GetType()==PROP)||(pl.cur()->GetType()==PROP)||(pl.cur()->GetType()==EVENT))) continue; // only events and stuff
	  if (!writtenprop.contains(pl.cur())){
	    writtenprop.add(pl.cur());
	    (*ofile) << "\t" << replace(pl.cur()->GetName()) <<  " : boolean;\n";
	  }
	}

	if (newenabled.cur()->hasClockConstraint()){
	  string name=newenabled.cur()->GetUniqueName();
	  (*ofile) <<  "\t" << name << "-timer:0.." << ((GetNrTimeouts() + 1 )  * (newenabled.cur()->GetClockConstraint()->GetLimit())) << ";\n";
	}
	

	if ((newenabled.cur()->GetSendEvent()) && (!writtenprop.contains(newenabled.cur()->GetSendEvent()))){
	  writtenprop.add(newenabled.cur()->GetSendEvent());
	  (*ofile) << "\t" << replace(newenabled.cur()->GetSendEvent()->GetName()) << " : boolean;\n";
	}
      }

      List <Subject *> *target=newenabled.cur()->GetSubject2();
      for (target->first();!target->done();target->next()){
	if (writtennodes.contains(target->cur())) continue;
	string s=(*(target->cur()->GetName()));
	writtennodes.add(target->cur());
	(*ofile ) << "\t"<< replace(s) << " : boolean;\n";
	if (target->cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	  (*ofile ) << "\tT_" << replace(s) << " : boolean;\n";
	  for (actlist.first();!actlist.done();actlist.next()){
	    if (replace(actlist.cur()->GetName())==replace(s)){
	      List <ADSVar *> varlist;
	      actlist.cur()->GetUpdateList(varlist);
	      for (intproplist.first();!intproplist.done();intproplist.next()){
		if (writtenprop.contains(intproplist.cur())) continue;
		if (((intproplist.cur()->GetType()==INTERNAL_PROP)||(intproplist.cur()->GetType()==INTERNAL_STRING))&&(varlist.contains(intproplist.cur()->GetVar()))){	  
		  (*ofile) << "\t" << replace(intproplist.cur()->GetName()) << ": boolean;\n";
		  writtenprop.add(intproplist.cur());
		}
	      }
	    }
	  }
	}
      }
    }
  }


  (*ofile) << "\nINIT  -- state nodes\n";
  bool FirstInit=True;
  //  (*ofile) << "\tc____counter = 0 & \n "; // because of assign number
  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if ((amnodes.cur()->GetClassType()==Code::NOTE)||(amnodes.cur()->GetClassType()==Code::COMMENT)) continue; // skip these 
    if (FirstInit) FirstInit=False;
    else (*ofile) << " &\n";
    string s=(*(amnodes.cur()->GetName()));
    if ((amnodes.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE)){
      (*ofile) << "\t" << replace(s) << "\t = TRUE";
    }
    else{
      (*ofile) << "\t" << replace(s) << "\t = FALSE" ;
    }
    if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      (*ofile ) << " &\n\tT_" << replace(s) << "\t = FALSE" ;
    }
  }
  FirstInit=True;
  for (propl.first();!propl.done();propl.next()){
    if (FirstInit){
      FirstInit=False;
      (*ofile) << "\n\nINIT -- events etc.\n";
    }
    else (*ofile) << " &\n";
    string s=propl.cur()->GetName();
    (*ofile ) << "\t" << replace(s) << "\t = FALSE";    
  }
  (*ofile) << "\n\n";


  FirstInit=True;
  for (amedges.first();!amedges.done();amedges.next()){
    if (amedges.cur()->hasClockConstraint()){
      if (FirstInit){
	FirstInit=False;
	(*ofile) << "\n\nINIT -- timers \n";
      }
      else (*ofile) << " &\n";
      string name=amedges.cur()->GetUniqueName();
      (*ofile) << "\t" << name << "-timer = 0\n";
    }
  }

  for (amedges.first();!amedges.done();amedges.next()){
    (*ofile) << "DEFINE -- hyperedges \n\n";  
    string name=amedges.cur()->GetUniqueName();
    (*ofile) << "\t" << name+"-relevant := ";
    List <Subject *> *source=amedges.cur()->GetSubject1();
    bool First=True;
    for (source->first();!source->done();source->next()){
      if (First) First=False;
      else (*ofile) << " & ";
      string sourcename=*(source->cur()->GetName());
      (*ofile) << replace(sourcename) ;
    }
    (*ofile) << ";\n\t" << name+"-enabled := " << name << "-relevant ";
    if (!amedges.cur()->HasEmptyEvent()){
      (*ofile) << " & " << replace(amedges.cur()->GetEvent()) ;
    }
    for (source->first();!source->done();source->next()){
      if (source->cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	string sourcename=*(source->cur()->GetName());
	(*ofile) << " & T_" << replace(sourcename)  ;
      }
    }
    if (!amedges.cur()->HasEmptyGuard()){
      string guard=amedges.cur()->GetGuard();
      guard.replace('[','(');
      guard.replace(']',')');
      guard.replace('~','!');
      guard.replace("IN","");
      (*ofile) << " & " << replace(guard) ;
    }
    if (amedges.cur()->hasClockConstraint()){       
      (*ofile) << " & " << name << "-timer = " << (1+GetNrTimeouts()) * (amedges.cur()->GetClockConstraint()->GetLimit()) ;
    }
    (*ofile) << ";\n"; 


    ///
    List <Subject *> *target=amedges.cur()->GetSubject2();
    (*ofile) << "\t" << name+"-taken := " << name+"-enabled ";
    for (source->first();!source->done();source->next()){
      if (!target->contains(source->cur())){
	(*ofile) << " & ";
	string sourcename=*(source->cur()->GetName());
	(*ofile) << "(next(" + replace(sourcename) + ")=FALSE)" ;
      }
    }    

    for (target->first();!target->done();target->next()){
      (*ofile) << " & ";
      string targetname=*(target->cur()->GetName());
      (*ofile) << "next("+replace(targetname)+")";      
      //}
    }  
    (*ofile) << ";\n";

    ///
    (*ofile) << "\nTRANS\n";
    (*ofile) << "\t" << "(!"+name+"-enabled)";
    List <ADSHyperEdge *> conflict;
    amedges.cur()->GetConflict(&conflict);
    (*ofile) << "| ((!" << name << "-taken) <-> ( FALSE";
    for (conflict.first();!conflict.done();conflict.next()){
      (*ofile) << " | ";
      (*ofile) << replace(conflict.cur()->GetUniqueName())<<"-taken";	
    }
    (*ofile) << " ))\n\n";    
    (*ofile) << "\n";
    
    ///
    (*ofile) << "\nDEFINE -- timers\n\n";
    if (amedges.cur()->hasClockConstraint()){
      (*ofile) << "\t" << name << "-timer_on := (!" << name << "-relevant) & next(" <<  name << "-relevant);\n";
      
      
      (*ofile) << "TRANS\n";
      (*ofile) << "\t!next(" << name << "-relevant) -> next(" <<  name << "-timer)=0\n";

      (*ofile) << "TRANS\n";     
      (*ofile) << "\t(" << name << "-timer_on ) -> next(" << name << "-timer) = 0\n";
      (*ofile) << "TRANS\n";
      (*ofile) << "\t( stable & " << name << "-relevant & " ;  
      (*ofile)<< "next(" << name << "-relevant)) -> (next(" <<  name << "-timer) = " << name << "-timer + 1)\n";
      (*ofile) << "TRANS\n";
      (*ofile) << "\t(!stable & " << name << "-relevant & next(" << name << "-relevant)) -> (next(" <<  name << "-timer) = " << name << "-timer )\n\n";
    }
  }

  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if ((amnodes.cur()->GetClassType()==Code::NOTE)||(amnodes.cur()->GetClassType()==Code::COMMENT)) continue; // skip these 
    string s = *(amnodes.cur()->GetName());
    (*ofile) << "TRANS\n\t(" << replace(s)  << " = next(" << replace(s) << "))";
    for (amedges.first();!amedges.done();amedges.next()){
      List <Subject *> *source=amedges.cur()->GetSubject1();
      if (source->contains(amnodes.cur())) 
	(*ofile) << " | " << amedges.cur()->GetUniqueName()<<"-taken"  << "\n";
      List <Subject *> *target=amedges.cur()->GetSubject2();
      if (target->contains(amnodes.cur())) 
	(*ofile) << " | " << amedges.cur()->GetUniqueName()<<"-taken"  << "\n";    
    }
    (*ofile) << "\n";
  }
  // EVENT GENERATION
  (*ofile) << "\n-- external event generation\n";
  (*ofile) <<  "ASSIGN\n";
  for (propl.first();!propl.done();propl.next()){
    if (propl.cur()->GetType()==EVENT){ // external event
      string s=propl.cur()->GetName();
      (*ofile ) << "\tnext(" << replace(s) << ") :=\n\t\tcase\n\t\t\tstable:{FALSE,TRUE};\n\t\t\t\tTRUE:FALSE;\n\t\tesac;\n"; 
    }
    if (propl.cur()->GetType()==SENDEVENT){// internal event
      string s=propl.cur()->GetName();
      (*ofile ) << "\tnext(" << replace(s) << ") :=\n";
      bool FirstSendEvent=True;
      for (amedges.first();!amedges.done();amedges.next()){
	if ((amedges.cur()->GetSendEvent())&&(*(amedges.cur()->GetSendEvent())==*propl.cur())){
	  (*ofile) << "\t\t";
	  if (FirstSendEvent) {FirstSendEvent=False;(*ofile) << "   ";}
	  else (*ofile) << " | ";
	  (*ofile) << amedges.cur()->GetUniqueName()<<"-taken" <<"\n";
	}
      }
      (*ofile) <<"\t\t;\n";
    }  
  }
  (*ofile) << "\n-- termination event generation\n";
  // termination events
  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      string s=*(amnodes.cur()->GetName());
      (*ofile ) << "\tnext(T_" << replace(s) << ") :=\n\t\tcase\n\t\t\t(stable & " << replace(s) <<  "):{FALSE,TRUE};\n\t\t\tTRUE:FALSE;\n\t\tesac;\n";     
    }
  }

  (*ofile) << "\n-- property update\n";
  for (propl.first();!propl.done();propl.next()){
    if ((propl.cur()->isInternal()&&(propl.cur()->GetType()!=SENDEVENT))){ // property is updated internally
      (*ofile) << "TRANS\n\t("<<replace(propl.cur()->GetName()) << "=next(" << replace(propl.cur()->GetName()) << "))" ;
      for (amnodes.first();!amnodes.done();amnodes.next()){
	if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	  string s=*(amnodes.cur()->GetName());
	  //	  ADSActivity *a=FindAct(s);
	  ADSActivity *a=((ATDActionStateNode *)amnodes.cur())->GetActivity();
	  if (a->isUpdated(propl.cur()->GetVar()))
	    (*ofile) << " | next(T_" << replace(s) << ")\n"; // update on variable
	}
      }
    }
  }


  if (sf){
    // COMPASSION CONSTRAINTS
    for (amedges.first();!amedges.done();amedges.next()){
      if (amedges.cur()->GetInternal()) continue;
      if (amedges.cur()->hasClockConstraint()) continue;
      (*ofile) << "\nCOMPASSION\n"; 
      (*ofile) << "(" << amedges.cur()->GetUniqueName() << "-relevant, " << amedges.cur()->GetUniqueName() << "-taken)\n";
    }
    (*ofile) << "\n\n";
  }


  List <Subject *> finalnodes;

  // INTERFERENCE
  (*ofile) << "\n-- interference\n";
  int amlen=amnodes.count();
  for (int i=0;i<amlen;i++){    
    for (int j=i+1;j<amlen;j++){
      if ((amnodes[i]->GetClassType()==Code::ATD_ACTION_STATE_NODE)&&
	  (amnodes[j]->GetClassType()==Code::ATD_ACTION_STATE_NODE)&&
	  (GetInterference((ATDActionStateNode*)amnodes[i],(ATDActionStateNode*)amnodes[j]))){
	(*ofile) << "TRANS\n\t!(";
	string s1 = *(amnodes[i]->GetName());
	string s2 = *(amnodes[j]->GetName());
	(*ofile) << "next(" << replace(s1) << ") & next(" << replace(s2) << "))\n";
      }
    }
    if (amnodes[i]->GetClassType()==Code::ATD_FINAL_STATE_NODE){
      finalnodes.add(amnodes[i]);
    }
  }

  // final nodes
  if (finalnodes.count()){
//  bool FirstFinal=True;
    (*ofile) << "\n -- events cannot be generated if the configuration is final\n";
    (*ofile) << "INVAR\n";
    (*ofile) << "\t" << ComputeFinalPredicate() << "\t\t-> stable\n\n";

  }


  // ENABLEDNESS
  (*ofile) << "\n-- enabledness\n";
  (*ofile) << "DEFINE\n\tstable := !enabled & !events;\n";
  (*ofile) << "DEFINE\n\tenabled := \n";
  bool FirstEnabled=True; 
  for (amedges.first();!amedges.done();amedges.next()){
    (*ofile) << "\t\t";
    if (FirstEnabled){
      FirstEnabled=False; (*ofile) << "   ";
    }
    else (*ofile) << " | ";
    (*ofile) << amedges.cur()->GetUniqueName()<<"-enabled" << "\n"; 
  }
  (*ofile) << "\t\t;\n\n";

  (*ofile) << "DEFINE\n\tevents := FALSE \n";
  for (propl.first();!propl.done();propl.next()){
    if ((propl.cur()->GetType()==EVENT)||(propl.cur()->GetType()==SENDEVENT)){ // external or internal event
      (*ofile) << " | ";
      string s=propl.cur()->GetName();
      (*ofile ) << "\t\t" << replace(s) <<"\n"; 
    }
  }
  for (int i=0;i<amlen;i++){    
    if (amnodes[i]->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      (*ofile) << " | ";
      string s = *(amnodes[i]->GetName());
      (*ofile) << "\t\tT_"<< replace(s) << "\n";
    }
  }
  (*ofile) << "\t\t ;\n\n";

  // 
  (*ofile) << "-- disable concurrent enabling of two hyperedges where the source and target of one are contained in the source and target of other\n";
  int elen=amedges.count();  
  for (int i=0;i<elen-1;i++){
    for (int j=i+1;j<elen;j++){
	// check if sources and targets of amedges[i] are contained in those of conflict.cur()
      //      List <Subject *> *source=amedges[i]->GetSubject1();
      bool FoundConflict=(amedges[i]->conflicts(amedges[j]));
      if (!FoundConflict){
	List <Subject *> *target=amedges[i]->GetSubject2();
	bool FoundTargets=True;
	for (target->first();!target->done();target->next()){
	  if (!amedges[j]->GetSubject2()->contains(target->cur())){
	    FoundTargets=False;
	    break;
	  }
	}
	if (FoundTargets){ // amedges[i] is contained in amedges[j]
	  (*ofile) << "TRANS\n\tnext(" << amedges[i]->GetUniqueName() << "-enabled) -> ! next(" <<  amedges[j]->GetUniqueName() << "-enabled)\n";
	}
      }
       	       
      if (!FoundConflict){	
	List <Subject *> *target=amedges[j]->GetSubject2();
	bool FoundTargets=True;
	for (target->first();!target->done();target->next()){
	  if (!amedges[i]->GetSubject2()->contains(target->cur())){
	    FoundTargets=False;
	    break;
	  }
	}
	if (FoundTargets){ // amedges[j] is contained in amedges[i]
	  (*ofile) << "TRANS\n\tnext(" <<  amedges[j]->GetUniqueName() << "-enabled) -> ! next(" << amedges[i]->GetUniqueName() << "-enabled)\n";
	}
      }
    }
  }
  (*ofile) << "\n";
}






void ADSHyperGraph::RemoveNodes(List <Node *> nodeused, List <ADSVar *> varused, bool reduction){
  List <Subject *> amhedges;
  List <Subject *> remove;
  GetHyperEdges(&amhedges);
  int hedgecount=amhedges.count();
  bool hedgeremove[200];
  for (int i=0;i<hedgecount;i++){
    hedgeremove[i]=False;
    if (isRemovableHyperEdge((ADSHyperEdge *)amhedges[i],nodeused,varused,reduction)){    
      remove.add(amhedges[i]);
      hedgeremove[i]=True;
    }    
  }

  for (remove.first();!remove.done();remove.next()){    
    // remove.cur() has only one source, due to the reduction rules
    Subject *node=((HyperEdge *)remove.cur())->GetSubject1()->cur();
    List <Subject *> newhedges;
    GetHyperEdges(&newhedges);
    for (newhedges.first();!newhedges.done();newhedges.next()){
      List <Subject *> *target=((HyperEdge *)newhedges.cur())->GetSubject2();
      if (!target) continue;
      if (!target->contains(node)) continue;
      // hyperedge newhedges.cur() makes remove.cur() relevant
      target->remove(node);
      List <Subject *> *newtarget=((HyperEdge *)remove.cur())->GetSubject2();
      for (newtarget->first();!newtarget->done();newtarget->next()){
	target->add(newtarget->cur());
      }
      // get the simple edges from remove.cur () and put them in newhedges.cur()
      // this is necessary for displaying the feedback of the model checker
      List <Subject *> ls;
      ((ADSHyperEdge *)remove.cur())->GetEdges(&ls); // the edges in the original activity diagram that are represented by the hyperedge
      ((ADSHyperEdge *)newhedges.cur())->AddEdges(ls);
      
    }
    
    RemoveNode((Node *)node); // hyperedge remove.cur() is removed automatically
  }
}




bool ADSHyperGraph::isRemovableHyperEdge(ADSHyperEdge *hedge, List <Node *> nodeused, List <ADSVar *> varused, bool reduction){

  if (hedge->isconflicting()) return False;

  List <Subject *> *source=hedge->GetSubject1();
  List <Subject *> *target=hedge->GetSubject2();
  
  if (source->count()>1) return False;
  source->first();
  // hedge is non conflicting hyperedge with one source
  if (!((source->cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE)||(source->cur()->GetClassType()==Code::ATD_WAIT_STATE_NODE))) return False;
 
  // rule1
  if (nodeused.contains((Node*)source->cur())) return False;
  bool found=False;
  for (target->first();!target->done();target->next()){
    if (nodeused.contains((Node*)target->cur())){
      found = True;
      break;
    }
  }
  if (found) return False;
  for (varused.first();!varused.done();varused.next()){
    if (hedge->refersto(varused.cur())){
      found=True;
      break;
    }
  }
  if (found)return False;

  // rule 2
  if   (NodeReferredToBySomeInpredicate(source->cur())) return False;
  for (target->first();!target->done();target->next()){
    if (NodeReferredToBySomeInpredicate(target->cur())){
      found=True;
      break;
    }
  }
  if (found) return False;

  // rule 3
  if (hedge->GetClockConstraint()) return False;

  // rule 4
  if ((source->cur()->GetClassType()==Code::ATD_WAIT_STATE_NODE) && !reduction) return False;

 // all rules checked, so both source->cur() and hedges.cur() can be removed
  return True;
}


bool ADSHyperGraph::NodeReferredToBySomeInpredicate(Subject *n){
  for (hedges->first();!hedges->done();hedges->next()){
    if (((ADSHyperEdge*)hedges->cur())->inpredicaterefersto(n)) return True;
  }
  return False;
}


// used is list of variables used in property	
void ADSHyperGraph::RemoveLocalVariables(List <ADSVar *> *usedinprop){
  for (varl.first();!varl.done();varl.next()){
    // rule 2
    if (usedinprop->contains(varl.cur())) continue; // varl.cur() is used in property so skip


    // rule 1
    if (VarUpdatedByTwoActivities(varl.cur())) continue;

    // rule 3
    if (VarTestedInHyperEdgeWithoutUpdate(varl.cur())) continue;

    // rule 4 checked elsewhere (eliminate pseudo nodes)

    // varl.cur() can be removed

    // remove varl.cur() from update in activity
    for(actlist.first();!actlist.done();actlist.next()){
      actlist.cur()->RemoveUpdate(varl.cur());      
    }
    for(propl.first();!propl.done();){
      if (propl.cur()->GetVar()==varl.cur()){
	extproplist.remove(propl.cur());
	intproplist.remove(propl.cur());  
	propl.removecur();
      }    
      else propl.next();
    }
    // NOTE varl.cur() is still in hyperedge's varlist
    // so printing the hypergraph gives inaccurate information
  }
}


// return True iff 
// ( there is a hyperedge h such that
// v is tested in h's guard h AND 
// none of h's sources update v )
bool ADSHyperGraph::VarTestedInHyperEdgeWithoutUpdate(ADSVar *v){
  List <Subject *> edges;
  GetHyperEdges(&edges);
  for (edges.first();!edges.done();edges.next()){
    if (!((ADSHyperEdge*)edges.cur())->refersto(v)) continue;
    // the guard of edges.cur() refers to v
    List <Subject *> *source=((HyperEdge *)edges.cur())->GetSubject1();
    bool found=False;
    for (source->first();!source->done();source->next()){
      if (source->cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	if (((ATDActionStateNode *)source->cur())->GetActivity()->isUpdated(v)){
	  // v is updated by one of the sources
	  found=True;
	}
      }
    }
    if (!found){  // v is not updated by any of edges.cur()'s sources
      return True;
    }
  }
  return False;
}


// return True iff 
// ( v is updated by two activities )
bool ADSHyperGraph::VarUpdatedByTwoActivities(ADSVar *v){
  int actcount=actlist.count();
  for (int i=0;i<actcount;i++){
    for (int j=i+1;j<actcount;j++){
      if ((GetInterference(actlist[i],actlist[j])) &&(actlist[i]->isUpdated(v))&&(actlist[j]->isUpdated(v))){
	actlist[i]->Write();
	actlist[j]->Write();
	List <Subject *> nods;
	ATDActionStateNode *activity_i = NULL;	//init?
	ATDActionStateNode *activity_j = NULL;	//init?
	GetNodes(&nods, Code::ATD_ACTION_STATE_NODE);
	for (nods.first();!nods.done();nods.next()){
	  if (((ATDActionStateNode*)nods.cur())->GetActivity()==actlist[i]){
	    activity_i=(ATDActionStateNode *)nods.cur();
	  }
	  if (((ATDActionStateNode*)nods.cur())->GetActivity()==actlist[j]){
	    activity_j=(ATDActionStateNode *)nods.cur();
	  }	    
	}
	ADSSem test;
	if (test.inparallel(this,(Subject *)activity_i,(Subject*)activity_j)){
	  return True;
	}
      }
    }
  }
  return False;  
}


