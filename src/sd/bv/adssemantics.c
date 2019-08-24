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
#include "adsactivity.h"
#include "adssemantics.h"
#include "adshyperedge.h"
#include "adscks.h"
#include "graph.h"
#include "initialstate.h"
#include <ctype.h>
#include "lstring.h"
#include "adspropertyvaluation.h"
#include "adsedgelabelevaluationparse.h"
#include <stdlib.h>
#include "bag.h"
#include "adsvariable.h"
#include "outputfile.h"



bool ADSSem::inparallel(ADSHyperGraph *ah,Subject *a, Subject *b){
  ADSCks *c=new ADSCks(ah);
  tokengame(ah,c);
  List <ADSValuation *> nodes;
  c->GetNodes((List<Subject *> *)&nodes);
  for (nodes.first();!nodes.done();nodes.next()){
    Bag <Subject *> cfg; // the current configuration bag
    nodes.cur()->GetConfig(&cfg);
    if ((cfg.count(a)>0) && (cfg.count(b)>0)){
      return True;
    }
  }
  return False;
}


void ADSSem::tokengame(ADSHyperGraph *h,ADSCks *c){
  List <ADSValuation *> unprocessed; // valuations to be processed
  ADSValuation *knew=new ADSValuation(c,unstable); // the initial valuation
  List <Subject *> initStates; // the list of initial states (if correct will contain a single element only) 
  h->GetNodes(&initStates, Code::ATD_INITIAL_STATE_NODE);
  if (initStates.count()==1){ // there can be only one initial state
    Bag <Subject *> b(initStates,1); // the initial configuration
    knew->SetConfig(b);
    c->AddNode(knew); // add the initial valuation to c
    
    unprocessed.add(knew); // add the initial valuation to unprocessed
    while (unprocessed.count()>0){ // while some valuations need to be processed
      // pick the first valuation in unprocessed
      unprocessed.first(); 
      //      std::cout << "."; // progress indication 
      //      std::cout.flush();
      ADSValuation *adk=unprocessed.cur();     
      Bag <Subject *> cfg; // the current configuration bag
      adk->GetConfig(&cfg);
      List <Subject *> cfgl; // the current configuration set
      cfg.GetSet(&cfgl);   
      
      
      List <ADSHyperEdge *> rel;   // the list of relevant hyperedges
      h->GetHyperEdgesFrom((List <HyperEdge *> *)&rel,&cfgl); // the SET of relevant hyperedges
      for (rel.first();!rel.done();rel.next()){
	Bag <Subject *> left(*(rel.cur()->GetSubject1()),1);
	Bag <Subject *> enter(*(rel.cur()->GetSubject2()),1);
	cfg.diff(left);
	cfg.join(enter);
	ADSValuation *adknew= new ADSValuation(c,unstable);
	adknew->SetConfig(cfg);
	ADSValuation *oldadk=c->FindSimilarNode(adknew);
	if (!oldadk){ // eadkl.cur() does not yet exist in c
	  c->AddNode(adknew); // so add it to c
	  unprocessed.add(adknew); // and to unprocessed
	  ADSTransition *ktnew = new ADSTransition(c,adk,adknew); // make a new transition	    
	  c->AddEdge(ktnew);
	  string str;
	  if (c->GrowsInfinite(adknew,str)){
	    string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
	    char s1[100];
	    strcpy(s1,s.getstr());
	    error(s1);
	    return;
	  }
	}
	else{
	  //  ADSValuation *old=c->FindSimilarNode(eadkl.cur()); // eadkl.cur() exists already, so find this old copy
	  ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
	  if (!c->ExistsSimilarEdge(ktnew)){
	    c->AddEdge(ktnew);
	  }	    
	  else delete ktnew;
	}    
	
	cfg.diff(enter);
	cfg.join(left);
      }
      unprocessed.remove(adk); // adk is processed so remove it
    }  
  }
}

// for debugging only
void PrintBag(Bag <Subject *> *b){
  List <Subject *> l;
  b->GetList(l);
  for (l.first();!l.done();l.next()){
    std::cout << l.cur()->GetId() <<":\t" << b->count(l.cur()) <<"\n";
  }
}

// for debugging only
void PrintBag(Bag <ATDActionStateNode *> *b){
  List <ATDActionStateNode *> l;
  b->GetList(l);
  for (l.first();!l.done();l.next()){
    std::cout << l.cur()->GetId() <<":\t" << b->count(l.cur()) <<"\n";
  }
}




// Execute event step from current location ak
// Result locations are returned (note that some may already have been part
// of the CLKS, so these can be skipped?)
// CLKS *c is updated


// true iff there is an activity `a' in `b' 
// such that in `a' variabe `v' is updated
//bool canbeUpdated(ADSHyperGraph *h,Bag <ATDActionStateNode *> b, ADSVar *v){
//  List <ATDActionStateNode *> l;
//  b.GetSet(&l);
//  for (l.first();!l.done();l.next()){
//    string s=*l.cur()->GetName();
//    ADSActivity *a=h->FindAct(s);
//    if (a->isUpdated(v)) return True;
//  }
//  return False;
//}


// find given a list of PropVal the Val of a Prop
PropVal *getPropVal(List <PropVal *> *plist, Prop *p){
	for (plist->first();!plist->done();plist->next()){
		if (*(plist->cur()->GetProp())==*p){
			return plist->cur();
		}
	}
	return NULL;
}


// the actual execution algorithm
// the semantics maps h into c.
// loop in which states are processed. By performing transitions new
// states are added.
void ADSSem::ComputeCKS(ADSHyperGraph *h, ADSCks *c, bool reduce){
  List <ADSValuation *> unprocessed; // valuations to be processed

//  int counter=0;		//unused

  // compute the initial valuation
  ADSValuation *knew=new ADSValuation(c,unstable); // the initial valuation
  List <Subject *> initStates; // the list of initial states (if correct will contain a single element only) 
  h->GetNodes(&initStates, Code::ATD_INITIAL_STATE_NODE);
  if (initStates.count()==1){ // there can be only one initial state
    Bag <Subject *> b(initStates,1); // the initial configuration
    knew->SetConfig(b);
    List <PropVal *> pl;
    List <Prop *> extproplist;
    h->GetPropList(extproplist);
    for (extproplist.first();!extproplist.done();extproplist.next()){
      PropVal *pv=new PropVal(extproplist.cur(),False); // initially every external property (including events) is false
      pl.add(pv);
    }
    knew->SetPropList(pl);
    c->AddNode(knew); // add the initial valuation to c
    
    unprocessed.add(knew); // add the initial valuation to unprocessed
    while (unprocessed.count()>0){ // while some valuations need to be processed
      // pick the first valuation in unprocessed
      unprocessed.first(); 
      //      std::cout << "."; // progress indication 
      //      std::cout.flush();
      ADSValuation *adk=unprocessed.cur(); 
  
      // update bounds
      Bag <Subject *> tmpcfg;
      adk->GetConfig(&tmpcfg);
      h->UpdateBounds(&tmpcfg);

      if (adk->isStable()){ 
	List<ADSValuation *> eadkl; // list of new unstable states that can be reached from adk by executing an event transition
	if (reduce){
	  InterleavedEvent(h,adk,&eadkl,reduce); // compute eadkl
	}
	else{
	  Event(h,adk,&eadkl,reduce);
	}
	for (eadkl.first();!eadkl.done();){ 	  
	  ADSValuation *oldadk=c->FindSimilarNode(eadkl.cur());
	  if (!oldadk){ // eadkl.cur() does not yet exist in c
	    c->AddNode(eadkl.cur()); // so add it to c
	    unprocessed.add(eadkl.cur()); // and to unprocessed
	    ADSTransition *ktnew = new ADSTransition(c,adk,eadkl.cur()); // make a new transition	    
	    c->AddEdge(ktnew);
	    string str;
	    if (c->GrowsInfinite(eadkl.cur(),str)){
	      string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
	      char s1[100];
	      strcpy(s1,s.getstr());
	      error(s1);
	      return;
	    }
	    eadkl.next(); // next in list
	  }
	  else{
	    //  ADSValuation *old=c->FindSimilarNode(eadkl.cur()); // eadkl.cur() exists already, so find this old copy
	    ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
	    if (!c->ExistsSimilarEdge(ktnew)){
	      c->AddEdge(ktnew);
	    }	    
	    else delete ktnew;
	    eadkl.removecur(); // remove eadkl.cur() from list
	  }          
	}
      }
      else{ // adk is unstable, hence a reaction (step) must be taken
	Bag <ADSHyperEdge *> enab; // the bag of enabled hyperedges
	ComputeEnabled(h,adk,&enab); // fill enab with enabled hyperedges

	List<Bag<ADSHyperEdge *> *> steplist; // the list of all possible steps
	Step(h,adk,&enab,&steplist); // compute steplist (list of steps)
	
	// not every step in the steplist is maximal
	// therefore the maximal steps are filtered out next
       
	int slength=steplist.count();
	int i;

	for (i=0;i<slength;i++){	  
	  ADSValuation *klnew=TakeStep(h,c,adk,steplist[i]); // take the step. This results in a unique next valuation
	  ADSValuation *oldklnew = c->FindSimilarNode(klnew);
	  if (!oldklnew){
	    c->AddNode(klnew);
	    unprocessed.add(klnew);
	    ADSTransition *ktnew = new ADSTransition(c,adk,klnew,steplist[i]); // make a transition in which a step is taken	   
	    c->AddEdge(ktnew);
	    string str;
	    if (c->GrowsInfinite(klnew,str)){
	      string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
	      char s1[100];
	      strcpy(s1,s.getstr());
	      error(s1);
	      return;
	    }
	  }
	  else{  // there exists already a similar node
	    //	    ADSValuation *old=c->FindSimilarNode(klnew);
	    delete klnew;
	    ADSTransition *ktnew = new ADSTransition(c,adk,oldklnew,steplist[i]); 
	    if (!c->ExistsSimilarEdge(ktnew)){
	      c->AddEdge(ktnew);
	    }	 
	    else delete ktnew;
	  }
	}
      }
      unprocessed.remove(adk); // adk is processed so remove it
    }
  }   
}




// Compute all the possible next unstable states in eadkl, given stable valuation ak
// only_relevant is true <-> irrelevant events are not considered
void ADSSem::Event(ADSHyperGraph *h, ADSValuation *ak,List <ADSValuation *> *eadkl, bool only_relevant){

  Bag <Subject *> cfg; // the current configuration bag
  ak->GetConfig(&cfg);
  List <Subject *> cfgl; // the current configuration set
  cfg.GetSet(&cfgl);   


  Bag <ATDActionStateNode *> term; // the terminated action state nodes
  ak->GetTerminated(&term);
  
  // define ep
  List<Prop *> ep; // the set of external properties
  //h->GetExtPropList(ep);
  
  if (only_relevant){ 
    List <ADSHyperEdge *> rel;   // the list of relevant hyperedges
    h->GetHyperEdgesFrom((List <HyperEdge *> *)&rel,&cfgl); // the SET of relevant hyperedges
    for (rel.first();!rel.done();rel.next()){
      List <Prop *> proplist;
      rel.cur()->GetPropList(proplist);
      for (proplist.first();!proplist.done();proplist.next()){
	if (proplist.cur()->isInternal()) continue;
	if (!ep.contains(proplist.cur())) ep.add(proplist.cur());
      }
    }
  }
  else{
    h->GetExtPropList(ep);
  }

  // define ip
  List<Prop *> ip; // the set of internal properties
  h->GetIntPropList(ip);

  // define a. a is used to generate activity termination events.
  List<ATDActionStateNode *> a; // bag of running activities 

  // fill a & check whether cfgl!= FINAL
  bool final=True;
  for (cfgl.first();!cfgl.done();cfgl.next()){
    if (cfgl.cur()->GetClassType()!=Code::ATD_FINAL_STATE_NODE) final=False;
    if (cfgl.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	int i;
	int l=cfg.count(cfgl.cur()) - term.count((ATDActionStateNode *)cfgl.cur()); // only activities that have not yet terminated can terminate!
	for (i=0;i<l;i++){
	  	a.add((ATDActionStateNode *)cfgl.cur());
	}
    }
  }

  if (final) { // final state is reached, so no event possible
    return;
  }  



  // compute proper subsets of a and p and        
  int epcount = ep.count(); // number of external properties
//  int ipcount = ip.count(); // number of internal properties : unused
  int acount = a.count(); // number of running activity instances
  int ccount=0;
  if ((ak->GetClockManager().ExistScheduled())&&(!(ak->GetClockManager().ExistTimeouts()))) ccount=1;

  
  unsigned long int subsetsep = 1<< epcount; 
// unsigned long int subsetsip = 1<< ipcount; 	// unused
  unsigned long int subsetsa = 1<< acount;
  unsigned long int subsetsc = 1<< ccount;


  //  int teller=0;

  unsigned long int c1; // counter on subsets of ep
  for (c1=0;c1<subsetsep;c1++){ // for all possibe subsets of ep

    List <PropVal *> epl; // the valuation of properties
    int ctemp;
    for (ctemp=0;ctemp<epcount;ctemp++){
      if ((1<<ctemp) & c1 ){
	PropVal *pv=new PropVal(ep[ctemp],True);
	epl.add(pv);
      }
      else{
	PropVal *pv=new PropVal(ep[ctemp],False);
	epl.add(pv);
      }
    } 
	  
    unsigned long int c2;
    for (c2=0;c2<subsetsa;c2++){ // for all possibe subsets of a

       
      // compute the terminated activity instances
      Bag <ATDActionStateNode *> al; 
      List <ADSVar *> varl; // list of variables that are updated in terminating activities


      for (ctemp=0;ctemp<acount;ctemp++){
	if ((1<<ctemp) &  c2) {
	  al.add(a[ctemp]);
	  ADSActivity *act=a[ctemp]->GetActivity();
	  List <ADSVar *> vartemp;
	  act->GetUpdateList(vartemp);
	  for (vartemp.first();!vartemp.done();vartemp.next()){
	    if (!varl.contains(vartemp.cur())) // update varl
	      varl.add(vartemp.cur());	  
	  }
	}
      }  

      List <Prop *> updatedpropl; // list of properties that are updated in terminating activities
      for (ip.first();!ip.done();ip.next()){
	if (varl.contains(ip.cur()->GetVar())){
	  updatedpropl.add(ip.cur());
	}	
      }




      unsigned long int c4;  // depending upon c2 (computing al) !!!!!
      
      //   unsigned long int subsetsvarl = 1 << varl.count();
      int upcount= updatedpropl.count();
      unsigned long int subsetsup =1 << upcount;

      for (c4=0; c4<subsetsup;c4++) {      
      List <PropVal *> ipl;
  
      for (ctemp=0;ctemp<upcount;ctemp++){
	if ((1<< ctemp)&c4) {
	  //	  for (ip.first();!ip.done();ip.next()){
	  //	    if (ip.cur()->GetVar()==varl[ctemp]){
	      PropVal *pv=new PropVal(updatedpropl[ctemp],True);
	      ipl.add(pv);
	      //	    }
	      //}	    
	}
	else{
	  //	  for (ip.first();!ip.done();ip.next()){
	  //	    if (ip.cur()->GetVar()==varl[ctemp]){
	      PropVal *pv=new PropVal(updatedpropl[ctemp],False);
	      ipl.add(pv);
	      //	    }
	      // }
	} 
      }


	
      List <PropVal *> oldproplist;
      ak->GetPropList(&oldproplist);
      
      for (ip.first();!ip.done();ip.next()){
	if (!varl.contains(ip.cur()->GetVar())){ 
	  // retrieve old value
	  PropVal *pv=getPropVal(&oldproplist,ip.cur()); // take old value
	  if (pv!=NULL) ipl.add(pv);
	}
      }


      /// check that a string variable is not assigned two different values
      int iplcount=ipl.count();
      int xx,yy;
      bool found=False;
      
      for (xx=0;xx<iplcount;xx++){
	for (yy=xx+1;yy<iplcount;yy++){
	  if ((ipl[xx]->GetProp()->GetVar()==ipl[yy]->GetProp()->GetVar()) && (!(ipl[xx]->GetProp()==ipl[yy]->GetProp()))&& (ipl[xx]->GetBool()&&ipl[yy]->GetBool())){
	    found=True;
	  }
	} 
      }
      

      if (found) continue; // two assignments to same string variable is impossible, so skip this valuation





	unsigned long int c3;
	ClockManager cmnew=ak->GetClockManager();
	for (c3=0;c3<subsetsc;c3++){ // for all possibe subsets of c (1)
	  if (c3){
	    if (!cmnew.Tick()) std::cout << "I cannot tick in state " << ak->GetId() << "\n";;
	  }
	  
	  List <ClockConstraint *> timeout;
	  if ((ak->HasClockConstraints()) || ((cmnew.ExistTimeouts()))) cmnew.GetTimeouts(&timeout); // timeout can be empty if !ExistScheduled
	  
	  
	  if (c1==0 && c2==0 && c3==0) continue; // no change is not interesting 	
	  
	  // compute the valuations of the properties
	  
	  
	
	  List <PropVal *> pl; // the new proplist
	  pl=epl; // initialise with external props ...
	  if (only_relevant){
	    List<Prop *> eplist; // the set of external properties; add properties in eplist but not in ep to ep.
	    h->GetExtPropList(eplist);
	    for (eplist.first();!eplist.done();eplist.next()){
	      if (!ep.contains(eplist.cur())){
		PropVal *pv=new PropVal(eplist.cur(),False);
		pl.add(pv);
	      }
	    }
	  }
	  for (ipl.first();!ipl.done();ipl.next()){
	    pl.add(ipl.cur()); // ... and add internal props
	  }
	  
	  ADSValuation *klnew= new ADSValuation(*ak,unstable); // use old config only
	  klnew->SetPropList(pl);   
	  klnew->AddTerminated(al);
	  klnew->SetClockConstraints(timeout);
	  klnew->SetClockManager(cmnew);
	  if (c3 && (!c1) && (!c2) && (!cmnew.ExistTimeouts())) // there has only been a tick and this tick did not trigger any events
	    klnew->makeStable();
	  eadkl->add(klnew);
	  //	  teller++;
	}
      }
    } 
  }  
}

// Compute all the possible next unstable states in eadkl, given stable valuation ak
// only_relevant is true <-> irrelevant events are not considered
void ADSSem::InterleavedEvent(ADSHyperGraph *h, ADSValuation *ak,List <ADSValuation *> *eadkl, bool only_relevant){

  Bag <Subject *> cfg; // the current configuration bag
  ak->GetConfig(&cfg);
  List <Subject *> cfgl; // the current configuration set
  cfg.GetSet(&cfgl);   


  Bag <ATDActionStateNode *> term; // the terminated action state nodes
  ak->GetTerminated(&term);
  
  // define ep
  List<Prop *> ep; // the set of external properties
  //h->GetExtPropList(ep);
  
  if (only_relevant){ 
    List <ADSHyperEdge *> rel;   // the list of relevant hyperedges
    h->GetHyperEdgesFrom((List <HyperEdge *> *)&rel,&cfgl); // the SET of relevant hyperedges
    for (rel.first();!rel.done();rel.next()){
      List <Prop *> proplist;
      rel.cur()->GetPropList(proplist);
      for (proplist.first();!proplist.done();proplist.next()){
	if (proplist.cur()->isInternal()) continue;
	if (!ep.contains(proplist.cur())) ep.add(proplist.cur());
      }
    }
  }
  else{
    h->GetExtPropList(ep);
  }

  // define ip
  List<Prop *> ip; // the set of internal properties
  h->GetIntPropList(ip);

  // define a. a's is used to generate activity termination events.
  List<ATDActionStateNode *> a; // bag of running activities 

  // fill a & check whether cfgl!= FINAL
  bool final=True;
  for (cfgl.first();!cfgl.done();cfgl.next()){
    if (cfgl.cur()->GetClassType()!=Code::ATD_FINAL_STATE_NODE) final=False;
    if (cfgl.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	int i;
	int l=cfg.count(cfgl.cur()) - term.count((ATDActionStateNode *)cfgl.cur()); // only activities that have not yet terminated can terminate!
	for (i=0;i<l;i++){
	  	a.add((ATDActionStateNode *)cfgl.cur());
	}
    }
  }

  if (final) { // final state is reached, so no event possible
    return;
  }  



  // compute proper subsets of a and p and        
  int epcount = ep.count(); // number of external properties
//  int ipcount = ip.count(); // number of internal properties : unused
  int acount = a.count(); // number of running activity instances
  int ccount=0;
  if ((ak->GetClockManager().ExistScheduled())&&(!(ak->GetClockManager().ExistTimeouts()))) ccount=1;

  
  //  unsigned long int subsetsep = 1<< epcount; 
  // unsigned long int subsetsip = 1<< ipcount; 
  //  unsigned long int subsetsa = 1<< acount;
  //  unsigned long int subsetsc = 1<< ccount;


 

  //  int teller=0;

  unsigned long int c1; // counter on subsets of ep
  for (c1=0;c1<static_cast<unsigned>(epcount);c1++){ // for all possibe subsets of ep

    List <PropVal *> epl; // the valuation of properties
    int ctemp;
    for (ctemp=0;ctemp<epcount;ctemp++){
      if (static_cast <unsigned> (ctemp) == c1){
	PropVal *pv=new PropVal(ep[ctemp],True);
	epl.add(pv);
      }
      else{
	PropVal *pv=new PropVal(ep[ctemp],False);
	epl.add(pv);
      }
    } 

    List <PropVal *> pl; // the new proplist
    pl=epl; // initialise with external props ...
    if (only_relevant){
      List<Prop *> eplist; // the set of external properties; add properties in eplist but not in ep to ep.
      h->GetExtPropList(eplist);
      for (eplist.first();!eplist.done();eplist.next()){
	if (!ep.contains(eplist.cur())){
	  PropVal *pv=new PropVal(eplist.cur(),False);
	  pl.add(pv);
	}
      }
    }

    List <PropVal *> oldproplist;
    ak->GetPropList(&oldproplist);
    for (ip.first();!ip.done();ip.next()){
      PropVal *pv=getPropVal(&oldproplist,ip.cur()); // take old value
      if (pv!=NULL) pl.add(pv);
    }

    
    ADSValuation *klnew= new ADSValuation(*ak,unstable); // use old config only
    klnew->SetPropList(pl);   
    //    klnew->AddTerminated(al);
    // klnew->SetClockConstraints(timeout);
    // klnew->SetClockManager(cmnew);
    //   if (c3 && (!c1) && (!c2) && (!cmnew.ExistTimeouts())) // there has only been a tick and this tick did not trigger any events
    //      klnew->makeStable();
    eadkl->add(klnew);
    //	  teller++;

  }



	  
  unsigned long int c2;
  for (c2=0;c2<static_cast<unsigned>(acount);c2++){ // for all possibe subsets of a
  
    // compute the terminated activity instances
    Bag <ATDActionStateNode *> al; 
    List <ADSVar *> varl; // list of variables that are updated in terminating activities

    int ctemp;
    for (ctemp=0;ctemp<acount;ctemp++){
      if (static_cast<unsigned>(ctemp) == c2) {
	al.add(a[ctemp]);
	ADSActivity *act=a[ctemp]->GetActivity();
	List <ADSVar *> vartemp;
	act->GetUpdateList(vartemp);
	for (vartemp.first();!vartemp.done();vartemp.next()){
	  if (!varl.contains(vartemp.cur())) // update varl
	    varl.add(vartemp.cur());	  
	}
      }
    }

    List <Prop *> updatedpropl; // list of properties that are updated in terminating activities
    for (ip.first();!ip.done();ip.next()){
      if (varl.contains(ip.cur()->GetVar())){
	updatedpropl.add(ip.cur());
      }	
    }


    unsigned long int c4;  // depending upon c2 (computing al) !!!!!
    //   unsigned long int subsetsvarl = 1 << varl.count();
    int upcount= updatedpropl.count();
    unsigned long int subsetsup =1 << upcount;

    for (c4=0; c4<subsetsup;c4++) {      
      List <PropVal *> ipl;
  
      for (ctemp=0;ctemp<upcount;ctemp++){
	if ((1<< ctemp)&c4) {
	  //	  for (ip.first();!ip.done();ip.next()){
	  //	    if (ip.cur()->GetVar()==varl[ctemp]){
	      PropVal *pv=new PropVal(updatedpropl[ctemp],True);
	      ipl.add(pv);
	      //	    }
	      //}	    
	}
	else{
	  //	  for (ip.first();!ip.done();ip.next()){
	  //	    if (ip.cur()->GetVar()==varl[ctemp]){
	      PropVal *pv=new PropVal(updatedpropl[ctemp],False);
	      ipl.add(pv);
	      //	    }
	      // }
	} 
      }


      ///
      int iplcount=ipl.count();
      int xx,yy;
      bool found=False;
    
      for (xx=0;xx<iplcount;xx++){
	//	ip[xx]->Write();
	for (yy=xx+1;yy<iplcount;yy++){
	  if ((ipl[xx]->GetProp()->GetVar()==ipl[yy]->GetProp()->GetVar()) && (!(ipl[xx]->GetProp()==ipl[yy]->GetProp()))&& (ipl[xx]->GetBool()&&ipl[yy]->GetBool())){
	    found=True;
	  }
	} 
      }
      

      if (found) continue; // two assignments to same string variable is impossible, so skip this valuation

	///
      
      List <PropVal *> oldproplist;
      ak->GetPropList(&oldproplist);
      
      for (ip.first();!ip.done();ip.next()){
	if (!varl.contains(ip.cur()->GetVar())){ 
	  // retrieve old value
	  PropVal *pv=getPropVal(&oldproplist,ip.cur()); // take old value
	  if (pv!=NULL) ipl.add(pv);
	}
      }
    
      List <PropVal *> pl; // the new proplist

      //     List <PropVal *> oldproplist;
      //      ak->GetPropList(&oldproplist);
      for (ep.first();!ep.done();ep.next()){
	PropVal *pv=getPropVal(&oldproplist,ep.cur()); // take old value
	if (pv!=NULL) pl.add(pv);
      }

      if (only_relevant){
	List<Prop *> eplist; // the set of external properties; add properties in eplist but not in ep to ep.
	h->GetExtPropList(eplist);
	for (eplist.first();!eplist.done();eplist.next()){
	  if (!ep.contains(eplist.cur())){
	    PropVal *pv=new PropVal(eplist.cur(),False);
	    pl.add(pv);
	  }
	}
      }
      for (ipl.first();!ipl.done();ipl.next()){
	pl.add(ipl.cur()); // ... and add internal props
      }

      ADSValuation *klnew= new ADSValuation(*ak,unstable); // use old config only
      klnew->SetPropList(pl);   
      klnew->AddTerminated(al);
      //   klnew->SetClockConstraints(timeout);
      //      klnew->SetClockManager(cmnew);
      //     if (c3 && (!c1) && (!c2) && (!cmnew.ExistTimeouts())) // there has only been a tick and this tick did not trigger any events
      //	klnew->makeStable();
      eadkl->add(klnew);
    //	  teller++;


    }

  }




  unsigned long int c3;
  ClockManager cmnew=ak->GetClockManager();
  for (c3=0;c3<static_cast <unsigned>(ccount);c3++){ // for all possibe subsets of c (1)
    //if (c3){
      if (!cmnew.Tick()) std::cout << "I cannot tick in state " << ak->GetId() << "\n";;
   // }
    
    List <ClockConstraint *> timeout;
    if ((ak->HasClockConstraints()) || ((cmnew.ExistTimeouts()))) cmnew.GetTimeouts(&timeout); // timeout can be empty if !ExistScheduled
    

    ADSValuation *klnew= new ADSValuation(*ak,unstable); // use old config only

    klnew->SetClockConstraints(timeout);
    klnew->SetClockManager(cmnew);
    if ((!cmnew.ExistTimeouts())){ // there has only been a tick and this tick did not trigger any events
      klnew->makeStable();
    }
    eadkl->add(klnew);
    //	  teller++;
  }
}






void ADSSem::Step(
		  ADSHyperGraph *h, 
		     ADSValuation *ak, 
		     Bag<ADSHyperEdge *> *step,
		     List<Bag<ADSHyperEdge *> *> *steplist){ 


  // compute maximal, consistent sublists

  Bag <Subject *> cfg;
  ak->GetConfig(&cfg);    // the configuration

  if (Consistent(h,cfg,*step)) { // step is consistent... 
    Bag<ADSHyperEdge *> *newstep=new Bag<ADSHyperEdge *>(*step);
    steplist->add(newstep); // ... so add it to steplist
  }
  else{    //  Step is INconsistent
    List <ADSHyperEdge *> l; // set of hyperedges in bag.
    step->GetSet(&l);
    for (l.first();!l.done();l.next()) {
      if (h->isConflicting(step,l.cur())){
	step->remove(l.cur()); // for each elementtype remove one instance
	Step(h,ak,step,steplist ); // Try this reduced step
	step->add(l.cur());	
      }            
    }
  }
}


ADSValuation *ADSSem::TakeStep(ADSHyperGraph *ah,
			 ADSCks *c,
			 ADSValuation *from,
			 Bag <ADSHyperEdge *> *step){
  Bag <Subject *> cfg;
  from->GetConfig(&cfg);    // the configuration

  Bag <Subject *> *newcfg= new Bag<Subject *>;  // the new configuration
  Bag <ATDActionStateNode *> *termresp= new Bag <ATDActionStateNode *>; //the terminated action state nodes responded to
  List <ClockConstraint *> *zero=new List <ClockConstraint *>;
  List <ClockConstraint *> *off=new List <ClockConstraint *>;
  List <Prop *> generated; // list of events generated in the step

  if (NextStateAfterStep(ah,cfg,*step,newcfg,termresp,zero,off,&generated)) { // compute the next valuation of the variables

    ADSValuation *knew = new ADSValuation(c,unstable);  // compute the new location

    // update config
    knew->SetConfig(*newcfg);  // the new configuration

    // update terminated action state nodes
    Bag <ATDActionStateNode *> termnotresp;
    from->GetTerminated(&termnotresp);
    if (!termnotresp.diff(*termresp)) {
      error("Error in computing bag difference");
      return False;
    }
    knew->AddTerminated(termnotresp); // the new bag of terminated action state nodes
    
    // update properties
    List <PropVal *> p;
    from->GetPropList(&p);
    List <PropVal *> pnew;
    for (p.first();!p.done();p.next()){ // reset the events
      PropVal *pv=new PropVal(*p.cur());
      if (pv->GetProp()->GetType()==EVENT){
	pv->SetBool(False);
	  /*
	bool Found=False;
	for (generated.first();!generated.done();generated.next()){
 	  if (*generated.cur()==(*(pv->GetProp()))){
 	    pv->SetBool(True);
 	    Found=True;
	    break; // jump out of for-loop
 	  }
 	}
	if (!Found) pv->SetBool(False);
	  */
      }
      if (pv->GetProp()->GetType()!=SENDEVENT) pnew.add(pv); // do not add old send events
    }
    for (generated.first();!generated.done();generated.next()){
      PropVal *pv=new PropVal(generated.cur(),True);
      pnew.add(pv);
    }
    knew->SetPropList(pnew); // the new list of properties

    // Update timers
    ClockManager cmnew=from->GetClockManager();
    if (!cmnew.Update(zero,off)){
      std::cout << "loc " << knew->GetId()  << " causes the problem\n"; //
      std::cout << "from\n";
      from->WriteScreen();
      std::cout << "to\n";
      knew->WriteScreen();
      abort();
    } 
    knew->SetClockManager(cmnew);
    List <ClockConstraint *> notrespondedto;
    knew->GetClockConstraints(&notrespondedto);
    for (off->first();!off->done();off->next()){
      if (notrespondedto.find(off->cur())>-1){
	notrespondedto.remove(off->cur());
      }
    }
    knew->SetClockConstraints(notrespondedto); // the new clock constraints

 
    Bag <ADSHyperEdge *> enab;
    ComputeEnabled(ah,knew,&enab); // compute the bag of enabled hyperedges in the new state
    if ((enab.length()==0)&&(generated.count()==0)){ // this new state is stable, so stop superstep
      //  Transforming unstable state into stable state
      knew->makeStable();
    }
    return knew;
  }
  else{
    error("The step is inconsistent!\n"); // can never occur, if Consistent(..) is true
    return NULL;
  }
}


void ADSSem::ComputeEnabled(ADSHyperGraph *h, ADSValuation *ak, 
			       Bag <ADSHyperEdge *> *enab){
  Bag <Subject *> relcfg;
  ak->GetConfig(&relcfg);    // the RELEVANT configuration: C with all action state nodes removed, joined with the terminated action state nodes
  // reason: a hyperedge having an action state node as source is only enabled if the corresponding activity has terminated
  Bag <Subject *> term;
  ak->GetTerminated((Bag <ATDActionStateNode *> *)&term);  // terminated action state nodes

  // remove action state nodes from rel
  List <Subject *> relcfgset;
  relcfg.GetSet(&relcfgset);
  for (relcfgset.first();!relcfgset.done();relcfgset.next()){
    if (relcfgset.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      relcfg.add(relcfgset.cur(),-(relcfg.count(relcfgset.cur()))); // rel-AS
    }
  }
  relcfg.join(term); // add term to rel


  Bag <ATDActionStateNode *> running; // the bag of activities now executing
  Bag <Subject *> cfg; // the configuration bag
  ak->GetConfig(&cfg);  
  List <Subject *> cfgset; // the configuration set
  cfg.GetSet(&cfgset);    
  for (cfgset.first();!cfgset.done();cfgset.next()){
    if (cfgset.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      int l=cfg.count(cfgset.cur());
      int m=relcfg.count(cfgset.cur());
      if ((l-m) < 0 ) { // more activity instances are terminated than there are in the configuration: this is impossible
	  error ("More activities terminate than are running: I am confused!\n");
	  ak->WriteScreen();
	  return;
      };
      running.add((ATDActionStateNode *)cfgset.cur(),(l-m));	  
    }
  }
  
  relcfgset.empty();
  relcfg.GetSet(&relcfgset);
 


  List <ADSHyperEdge *> rel;   // the list of relevant hyperedges
  h->GetHyperEdgesFrom((List <HyperEdge *> *)&rel,&relcfgset); // the SET of relevant hyperedges
  List <PropVal *> p;
  ak->GetPropList(&p); // the set of relevant properties



  List <ATDActionStateNode *> runningset;
  running.GetSet(&runningset);  

  // compute enab by 
  for (rel.first();!rel.done();rel.next()){  // for each relevant hyperedge
    bool eval=True; // false if the guard of rel.cur() cannot be evaluated
    List <Prop *> ptemp;
    rel.cur()->GetPropList(ptemp); // the properties of rel.cur()

    List <ADSVar *> evalnow;  // variables that need to be evalatued for the guard of rel.cur()
    for (ptemp.first();!ptemp.done();ptemp.next()){
      if (ptemp.cur()->isInternal()){	 
	List <ADSVar *> vtemp;
	rel.cur()->GetVarList(vtemp);
	for (vtemp.first();!vtemp.done();vtemp.next()){
	  if (evalnow.find(vtemp.cur())<0) evalnow.add(vtemp.cur());	    
	}
      }
    }


    for (runningset.first();!runningset.done();runningset.next()){
      //      string s=*runningset.cur()->GetName();
      //      ADSActivity *a=h->FindAct(s);
      ADSActivity *a=runningset.cur()->GetActivity();
      for (evalnow.first();!evalnow.done();evalnow.next()){
	if (a->isUpdated(evalnow.cur())){ // a updates some variable in rel.cur()'s guard, so the rel.cur() cannot be taken	
	  eval=False; // guard cannot be evaluated!
	  break;
	}
      }
      if (!eval) break; // guard cannot be evaluated!
    }     

    // check in predicate
    List <Subject *> inlist;
    rel.cur()->GetInNodes(&inlist);
    Bag <Subject *> inbag(inlist,1);
    if (!cfg.contains(inbag)) eval=False;

    // check not in predicate
    List <Subject *> notinlist;
    rel.cur()->GetNotInNodes(&notinlist);
    for (notinlist.first();!notinlist.done();notinlist.next()){
      if (cfg.count(notinlist.cur())>0){
	eval=False;
	break;
      }
    }    

    string s=rel.cur()->GetLabel();
    if ( (eval) && ParseLabel(&s,&p) ){ // guard can be evaluated and parsed
      bool b=True; // bool to test whether edge is not disabled by clock constraint
      if (rel.cur()->hasClockConstraint()){
	List <ClockConstraint *> currentTimeouts;
	ak->GetClockConstraints(&currentTimeouts);
	if (currentTimeouts.find(rel.cur()->GetClockConstraint())<0) {
	  b=False; // rel.cur() cannot be taken since its clock constraint is not true
	}
      }
      if (b){ // rel.cur() is enabled 
	// compute how many instances n of rel.cur() are enabled
	int n=relcfg.length(); // guaranteed upperbound on maximal number of instances of one edge
	List <Subject *> *source=rel.cur()->GetSubject1();
	for (source->first();!source->done(); source->next()){
	  int i=relcfg.count(source->cur());       // 
	  if (i<n)  n=i; // possibly new lower upperbound		 
	};
	enab->add(rel.cur(),n); // how many times?
      }  
    }
  }

}



// return true if an action state node in b1 interferes (has conflict) with an action state node in b2
// assumption: source and target are sets rather than multisets
// if bool same is true then b1==b2, otherwise not.
bool interfering1(ADSHyperGraph *ah, Bag <Subject *> *b1, Bag <Subject *> *b2, bool same) {
  List <ATDActionStateNode *> al1;  // al1 contains all action state nodes of b1
  List <Subject *>  b1set;
  b1->GetSet(&b1set);
  for (b1set.first();!b1set.done();b1set.next()){
    if (b1set.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      al1.add((ATDActionStateNode *)b1set.cur());
    }
  } 


  List <ATDActionStateNode *> al2;  // al2 contains all action state nodes of b2
  List <Subject *> b2set;
  b2->GetSet(&b2set);
  for (b2set.first();!b2set.done();b2set.next()){
    if (b2set.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      al2.add((ATDActionStateNode *)b2set.cur());
    }
  } 

  int a1len=al1.count();
  int a2len=al2.count();
  for (int i=0;i<a1len;i++){
    for (int j=0;j<a2len;j++){
      if ((same) && (i==j)) continue;  // if b1==b2 then node interferes by definition by itself, so skip this case
      if (ah->GetInterference(al1[i],al2[j])) return True; // conflict found
    }
  }
  return False; // no conflict found
}






// Test whether the step is consistent
bool ADSSem::Consistent(ADSHyperGraph *ah, 
			   Bag <Subject *> cfg, 
			   Bag <ADSHyperEdge *> step){
  Bag <Subject *> left; // the bag of states that are left
  Bag <Subject *> newconfig; // the new config
  List <ADSHyperEdge *> stepset;
  step.GetSet(&stepset);
  for (stepset.first();!stepset.done();stepset.next()){
    int number = step.count(stepset.cur());
    List <Subject *> *ltemp=stepset.cur()->GetSubject1();
    for (ltemp->first();!ltemp->done();ltemp->next()){
      left.add(ltemp->cur(),number);
    }
  }
  newconfig.join(cfg); // initialize newconfig with cfg
  bool result= (newconfig.diff(left));  // can states be left?
  if (!result) 
    return False;
  else // states can be left, now check for interference
    {       
      for (stepset.first();!stepset.done();stepset.next()){
	List <Subject *> *ltemp=stepset.cur()->GetSubject2(); // get target
	Bag <Subject *> target(*ltemp, step.count(stepset.cur()));  
	if (interfering1(ah,&target,&target,True)) return False; // interfering target
      	if (interfering1(ah,&newconfig,&target,False)) return False;// interfering old config
      }
      return True;
    }
}


// if consistent, newconfig contains the next configuration
// termresp is the set of terminated action states nodes that is reacted upon
bool ADSSem::NextStateAfterStep(ADSHyperGraph *ah, 
			   Bag <Subject *> cfg, 
			   Bag <ADSHyperEdge *> step, 
			   Bag <Subject *> *newconfig, 
			   Bag <ATDActionStateNode *> *termresp,
			   List <ClockConstraint *> *zero,
			   List <ClockConstraint *> *off,
			   List <Prop *> *generated){

  if (!Consistent(ah,cfg,step)) {
    error("Trying to take a non-step step!\n");
    return False;
  }
  Bag <Subject *> left; // the bag of states that are left
  List <ADSHyperEdge *> stepset;
  step.GetSet(&stepset);
  for (stepset.first();!stepset.done();stepset.next()){
    int number = step.count(stepset.cur());
    List <Subject *> *ltemp=stepset.cur()->GetSubject1();
    for (ltemp->first();!ltemp->done();ltemp->next()){
      left.add(ltemp->cur(),number);
    }
  }
  newconfig->join(cfg); // initialize newconfig with cfg
  newconfig->diff(left);  // can states be left?
 
  // compute termresp
  List <Subject *> leftcfg;
  left.GetSet(&leftcfg);
  for (leftcfg.first();!leftcfg.done();leftcfg.next()){
    if (leftcfg.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      termresp->add((ATDActionStateNode *)leftcfg.cur(),left.count(leftcfg.cur()));
    }
  }
      
  // compute entered states
  Bag <Subject *> entered;
  for (stepset.first();!stepset.done();stepset.next()){
    List <Subject *> *ltemp=stepset.cur()->GetSubject2(); // get target
    int number = step.count(stepset.cur());
    for (ltemp->first();!ltemp->done();ltemp->next()){
      entered.add(ltemp->cur(),number);
    }
    // update generated
    Prop *p=stepset.cur()->GetSendEvent();
    if ((p) &&(!generated->contains(p))) generated->add(p);
  }

  // compute zero
  List <Subject *> elist;
  List <ADSHyperEdge *> rel;
  entered.GetSet(&elist);
  ah->GetHyperEdgesFrom((List <HyperEdge *> *)&rel, &elist);
  for (rel.first();!rel.done();rel.next()){
    if (rel.cur()->hasClockConstraint()){
      if (!zero->contains(rel.cur()->GetClockConstraint())){ // may go wrong incase of unsafe activity diagram
	zero->add(rel.cur()->GetClockConstraint());
      }
    }
  }

  // compute off
  List <ADSHyperEdge *> oldrel;
  List <Subject *> oldcfg;
  cfg.GetSet(&oldcfg);
  ah->GetHyperEdgesFrom((List <HyperEdge *> *)&oldrel, &oldcfg);
  




  List <ADSHyperEdge *> stillrel;
  List <Subject *> stillcfg;
  newconfig->GetSet(&stillcfg);
  ah->GetHyperEdgesFrom((List <HyperEdge *> *)&stillrel, &stillcfg);
  for (oldrel.first();!oldrel.done();oldrel.next()){
    if (stillrel.find(oldrel.cur())<0){ // oldrel.cur becomes disabled
      if (oldrel.cur()->hasClockConstraint())
	off->add(oldrel.cur()->GetClockConstraint());
    }
  }
  newconfig->join(entered);
  return True;
}


// parse the label to evaluate it
bool ADSSem::ParseLabel(const string *str, List <PropVal *> *p) {
  unsigned i;
  unsigned c=p->count();
  for (i=0;i<c;i++){ // initialise the parser
    ::propname[i]= (char *) malloc (1+strlen((*p)[i]->GetProp()->GetName().getstr()));
    strcpy(::propname[i],(*p)[i]->GetProp()->GetName().getstr());
    ::proptype[i]=(int)(*p)[i]->GetProp()->GetType();
    ::boollist[i]=(int)(*p)[i]->GetBool();   
  }
  ::count=p->count();
  YY_BUFFER_STATE y = ::adsedgelabelevaluation_scan_string(str->getstr());
  strcpy(::adsedgelabelevaluation_constraint, "");
  (::outcome)=0;
  ::isin=0;
  adsedgelabelevaluationparse();
  bool b =(bool) ::outcome;
  adsedgelabelevaluation_delete_buffer(y);
  return b;
}





//---------
// Asumption: hyperedges that leave no action state node
// cannot have a guard label
// In other words, the only data that is used is updated by activities


// if step is finished in current state, next step is started in next state

// void ADSSem::ComputeImpCKS(ADSHyperGraph *h, ADSCks *c){

  /*
  List <ADSValuation *> unprocessed; // valuations to be processed


  // define ip
  List<Prop *> ip; // the set of internal properties (only data)
  h->GetIntPropList(ip);
  int ipcount = ip.count(); // number of internal properties
  unsigned long int subsetsip = 1<< ipcount; 

  // compute the initial valuation
  ADSValuation *knew=new ADSValuation(c,unstable); // the initial valuation
  List <Subject *> initStates; // the list of initial states (if correct will contain a single element only) 
  h->GetNodes(&initStates, Code::ATD_INITIAL_STATE_NODE);
  if (initStates.count()==1){ // there can be only one initial state
    Bag <Subject *> b(initStates,1); // the initial configuration
    knew->SetConfig(b);
    List <PropVal *> pl;
    List <Prop *> extproplist;
    h->GetPropList(extproplist);
    for (extproplist.first();!extproplist.done();extproplist.next()){
      PropVal *pv=new PropVal(extproplist.cur(),False); // initially every external property (including events) is false (WHAT ABOUT INTERNAL PROPERTIES??)
      pl.add(pv);
    }
    knew->SetPropList(pl);
    knew->SetQueue(pl);
    c->AddNode(knew); // add the initial valuation to c
    
    unprocessed.add(knew); // add the initial valuation to unprocessed
    while (unprocessed.count()>0) { // while some valuations need to be processed
      // pick the first valuation in unprocessed
      unprocessed.first(); 
      ADSValuation *adk=unprocessed.cur(); 
      
      // compute running activity instances
      
      Bag <Subject *> cfg; // the current configuration bag
      adk->GetConfig(&cfg);
      List <Subject *> cfgl; // the current configuration set
      cfg.GetSet(&cfgl);   
      
      
      Bag <ATDActionStateNode *> term,qterm; // the terminated action state nodes
      adk->GetTerminated(&term);
      adk->GetQTerminated(&qterm);
      term.join(qterm); // term now contains all terminated activity instances
  
      // define a. a's is used to generate activity termination events.
      List<ATDActionStateNode *> a; // bag of running activities 

      // fill a & check whether cfgl!= FINAL
      bool final=True;
      for (cfgl.first();!cfgl.done();cfgl.next()){
	if (cfgl.cur()->GetClassType()!=Code::ATD_FINAL_STATE_NODE) final=False;
	if (cfgl.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
	  //	std::cout <<"Action state" << cfgl.cur()->GetId() << "\n";
	  int i;
	  int l=cfg.count(cfgl.cur()) - term.count((ATDActionStateNode *)cfgl.cur()); // only activities that have not yet terminated can terminate!
	  for (i=0;i<l;i++){
	    a.add((ATDActionStateNode *)cfgl.cur());
	  }
	}
      }
      
      if (final) { // final state is reached, so no event possible
	// skip this unprocessed loop
	// ....
	unprocessed.remove(adk);
	continue;
      }  
      
      int acount = a.count();
      unsigned long int subsetsa = 1<<acount;
      
      int ccount=0;
      if ((adk->GetClockManager().ExistScheduled())&&(!(adk->GetClockManager().ExistTimeouts()))) ccount=1;
      unsigned long int subsetsc = 1<<ccount;

      // PLEASE NOTE: I ASSUME THAT THERE ARE NO CHANGE EVENTS 
      List <Prop *> notinq=extproplist; // the set of properties not in queue
      List <PropVal *> q; // existing q, it can only contain events
      adk->GetQueue(&q);
      for (q.first();!q.done();q.next()){
	if (q.cur()->GetBool()) notinq.remove(q.cur()->GetProp()); // remove properties that are in queue
	
      }
      for (notinq.first();!notinq.done();){
	if (notinq.cur()->GetType()!=EVENT){
	  notinq.removecur();
	}
	else
	  notinq.next();
      }
      // notinq now only contains events not in q
      int pnotinq_len=notinq.count(); // 
      
      unsigned long int subsets_pnotinq_len = 1 << pnotinq_len;
      
      



      // fill newq
      int index;
      for ( index=0;index<subsets_pnotinq_len;index++){
	List <PropVal *> newq; // the new queue
	
	for (q.first();!q.done();q.next()){
	  if (q.cur()->GetBool()) newq.add(q.cur()); // put old events in new queue
	}

	 
	for (int j=0;j<pnotinq_len;j++){
	  if ((1<<j) & index){
	    PropVal *pvt=new PropVal(notinq[j],True); // only for events	    
	    newq.add(pvt);
	  }
	  else{
	    PropVal *pvf=new PropVal(notinq[j],False);
	    newq.add(pvf);
	  }
	}



	// NOTE
	// assumption: now every event has valuation true or false in newq
	// END OF NOTE

	unsigned long int c2;
	for (c2=0;c2<subsetsa;c2++){ // for all possibe subsets of a
	  

	  // compute the terminated queue activity instances
	  Bag <ATDActionStateNode *> newqterm;
	  // 	  newqterm.join(qterm); niet nodig vanwege AddQTerminated procedure
	  for (int ctemp=0;ctemp<acount;ctemp++){
	    if ((1<<ctemp) &  c2) {
	      newqterm.add(a[ctemp]);
	    }
	  }  


	  unsigned long int c3;
	  ClockManager cmnew=adk->GetClockManager();
	  for (c3=0;c3<subsetsc;c3++){ // for all possibe subsets of c (1)
	    if (c3){
	      if (!cmnew.Tick()) std::cout << "I cannot tick in state " << adk->GetId() << "\n";;
	    }
	    
	    List <ClockConstraint *> timeout;
	    if ((adk->HasClockConstraints()) || ((cmnew.ExistTimeouts()))) cmnew.GetTimeouts(&timeout); // timeout can be empty if !ExistScheduled
	    
	    if ((index==0) && (c2==0) && (c3==0) && (adk->isStable())) continue; // no change is no change

	    
	




	    if (adk->isStable()){ // router is not busy processing any event

	      // either (a) an external event from newq or (b) a termination event from newqterm is processed or (c) a temporal event is processed
	      
	      // case (a)
	      for (newq.first();!newq.done();newq.next()){
		if (!newq.cur()->GetBool()) continue;
		List <PropVal *> newproplist;
		newproplist.add(newq.cur());  // pick a random event if event is true
		// preserve the old internal properties (data).
		List <PropVal *> oldpropvallist;
		adk->GetPropList(&oldpropvallist);
		for (oldpropvallist.first();!oldpropvallist.done();oldpropvallist.next()){
		  if (oldpropvallist.cur()->GetProp()->isInternal()) 
		    newproplist.add(oldpropvallist.cur());
		}


		List <PropVal *> newnewq;
		newnewq=newq;
		newnewq.remove(newq.cur());
		PropVal *pvf=new PropVal(newq.cur()->GetProp(),False);
		newnewq.add(pvf);
		
		ADSValuation *adknew=new ADSValuation(*adk,unstable); // make new state	     
		adknew->SetQueue(newnewq);	      
		adknew->AddQTerminated(newqterm);
		adknew->SetPropList(newproplist);
		adknew->SetQClockConstraints(timeout);
		adknew->SetClockManager(cmnew);
	      

		ADSValuation *oldadk=c->FindSimilarNode(adknew);
		if (!oldadk){ // adknew does not yet exist in c
		  // if (!c->ExistsSimilarNode(adknew)){ // adknew does not yet exist in c
		  c->AddNode(adknew); // so add it to c
		  unprocessed.add(adknew); // and to unprocessed
		  ADSTransition *ktnew = new ADSTransition(c,adk,adknew); // make a new transition
		  c->AddEdge(ktnew);
		  
		  string str;
		  if (c->GrowsInfinite(adknew,str)){
		    string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
		    char s1[100];
		    strcpy(s1,s.getstr());
		    error(s1);
		    return;
		  }
		  //	    std::cout << "\nAFDDSF";
		  //	      eadkl.next(); // next in list
		}
		else{
		  //		ADSValuation *old=c->FindSimilarNode(adknew); // adknew exists already, so find this old copy
		  ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
		  if (!c->ExistsSimilarEdge(ktnew)){
		    c->AddEdge(ktnew);
		  }	    
		  else delete ktnew;
		}    
		
	      }


	      // case (b)
	      List <ATDActionStateNode *> qtermlist;
	      qterm.GetSet(&qtermlist);
	      if (qtermlist.count()==0){
		newqterm.GetSet(&qtermlist);
	      }
	      
	      for (qtermlist.first();!qtermlist.done();qtermlist.next()) {
		Bag <ATDActionStateNode *> newterm;
		adk->GetTerminated(&newterm);
		newterm.add(qtermlist.cur());  // pick a random event, insert into newterm
		newqterm.add(qtermlist.cur(),-1); // and remove from qterm
		
		
		term.add(qtermlist.cur()); // only needed for inspection of `canbeupdated'

		ADSActivity *act=qtermlist.cur()->GetActivity();
		List <ADSVar *> varl;
		act->GetUpdateList(varl);

		unsigned long int c4;  // depending upon c2 (computing al) !!!!!
		unsigned long int subsetsvarl = 1 << varl.count();
		for (c4=0; c4<subsetsvarl;c4++) {
		

		  List <PropVal *> ipl;
		  int ctemp;
		  for (ctemp=0;ctemp<varl.count();ctemp++){
		    if ((1<<ctemp) &  c4) {
		      for (ip.first();!ip.done();ip.next()){
			if (ip.cur()->GetVar()==varl[ctemp]){
			  PropVal *pv=new PropVal(ip.cur(),True);
			  ipl.add(pv);
			}
		      }	    
		    }
		    else{
		      for (ip.first();!ip.done();ip.next()){
			if (ip.cur()->GetVar()==varl[ctemp]){
			  PropVal *pv=new PropVal(ip.cur(),False);
			  ipl.add(pv);
			}
		      }
		    } 
		  }
		  
		  List <PropVal *> oldproplist;
		  adk->GetPropList(&oldproplist);
	
		  for (ip.first();!ip.done();ip.next()){
		    if (!varl.contains(ip.cur()->GetVar())){ 
		      // retrieve old value
		      PropVal *pv=getPropVal(&oldproplist,ip.cur()); // take old value
		      if (pv!=NULL) ipl.add(pv);
		    }
		  }
		



		  
		  ADSValuation *adknew=new ADSValuation(*adk,unstable); // make new state
		  
		  adknew->SetPropList(ipl);
		  adknew->SetQueue(newq);
		  adknew->AddQTerminated(newqterm);
		  adknew->AddTerminated(newterm);
		  
		  adknew->SetQClockConstraints(timeout);
		  adknew->SetClockManager(cmnew);


		  
		  ADSValuation *oldadk=c->FindSimilarNode(adknew);
		  if (!oldadk){ // adknew does not yet exist in c

		    //	if (!c->ExistsSimilarNode(adknew)){ // adknew does not yet exist in c
		    c->AddNode(adknew); // so add it to c
		    unprocessed.add(adknew); // and to unprocessed
		    ADSTransition *ktnew = new ADSTransition(c,adk,adknew); // make a new transition
		    if (!c->ExistsSimilarEdge(ktnew)){ // if the transition did not yet exist
		      c->AddEdge(ktnew);
		    }
		    else delete ktnew; // else delete the transition
		    string str;
		    if (c->GrowsInfinite(adknew,str)){
		      string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
		      char s1[100];
		      strcpy(s1,s.getstr());
		      error(s1);
		      return;
		    }
		    //	    std::cout << "\nAFDDSF";
		    //	      eadkl.next(); // next in list
		  }
		  else{
		    //	  ADSValuation *old=c->FindSimilarNode(adknew); // adknew exists already, so find this old copy
		    ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
		    if (!c->ExistsSimilarEdge(ktnew)){
		      c->AddEdge(ktnew);
		    }	    
		    else delete ktnew;
		  }    
		  
		}
		
	      }


	      // case (c) temporal event
	      
	      for (timeout.first();!timeout.done();timeout.next()){

		
		ADSValuation *adknew=new ADSValuation(*adk,unstable); // make new state

	
		List <ClockConstraint *> newtimeout;
		newtimeout.add(timeout.cur());

		List <ClockConstraint *> newqtimeout;
		newqtimeout=timeout;
		newqtimeout.remove(timeout.cur());

		adknew->SetQueue(newq);
		adknew->AddQTerminated(newqterm);
		adknew->SetQClockConstraints(newqtimeout);
		adknew->SetClockConstraints(newtimeout);
		adknew->SetClockManager(cmnew);

		ADSValuation *oldadk=c->FindSimilarNode(adknew);
		if (!oldadk){ // adknew does not yet exist in c

		  //	if (!c->ExistsSimilarNode(adknew)){ // adknew does not yet exist in c
		  c->AddNode(adknew); // so add it to c
		  unprocessed.add(adknew); // and to unprocessed
		  ADSTransition *ktnew = new ADSTransition(c,adk,adknew); // make a new transition
		  if (!c->ExistsSimilarEdge(ktnew)){ // if the transition did not yet exist
		    c->AddEdge(ktnew);
		  }
		  else delete ktnew; // else delete the transition
		  string str;
		  if (c->GrowsInfinite(adknew,str)){
		    string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
		    char s1[100];
		    strcpy(s1,s.getstr());
		    error(s1);
		    return;
		  }
		  //	    std::cout << "\nAFDDSF";
		  //	      eadkl.next(); // next in list
		}
		else{
		  //	  ADSValuation *old=c->FindSimilarNode(adknew); // adknew exists already, so find this old copy
		  ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
		  if (!c->ExistsSimilarEdge(ktnew)){
		    c->AddEdge(ktnew);
		  }	    
		  else delete ktnew;
		}  
		
	      }
	      


	    }
	    else if (!adk->isStable()){
	      // HET GAAT MIS OMDAT terminated BIJ BEREKENEN STAP. MOET TERMINATED ALS F BESCHOUWEN
	      // gerepareerd
	    
	      //  if (!adk->isStable()){ 
	      // adk is unstable, but step is not yet finished
	      // only set the new queue
	      // CASE 1


	      if (!((index==0) && (c2==0))){ // only if there is some change 
		ADSValuation *adknew=new ADSValuation(*adk,unstable);
		adknew->SetQueue(newq);
		adknew->AddQTerminated(newqterm);
		adknew->SetQClockConstraints(timeout);
		
		ADSValuation *oldadk=c->FindSimilarNode(adknew);
		if (!oldadk){ // adknew does not yet exist in c
	      
		  // code repeated , make separate procedure someday
		  //     if (!c->ExistsSimilarNode(adknew)){ // adknew does not yet exist in c
		  c->AddNode(adknew); // so add it to c
		  unprocessed.add(adknew); // and to unprocessed
		  ADSTransition *ktnew = new ADSTransition(c,adk,adknew); // make a new transition	       
		  c->AddEdge(ktnew);		
		  string str;
		  if (c->GrowsInfinite(adknew,str)){
		    string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
		    char s1[100];
		    strcpy(s1,s.getstr());
		    error(s1);
		    return;
		  }
		  //	    std::cout << "\nAFDDSF";
		  //	      eadkl.next(); // next in list
		}
		else{
		  //		ADSValuation *old=c->FindSimilarNode(adknew); // adknew exists already, so find this old copy
		  ADSTransition *ktnew = new ADSTransition(c,adk,oldadk); // make a transition
		  if (!c->ExistsSimilarEdge(ktnew)){
		    c->AddEdge(ktnew);
		  }	    
		  else delete ktnew;
		}   
	      }
	    
	      // CASE 2
	      // adk is unstable, hence a reaction (step) can be taken

	    
	      

	      Bag <ADSHyperEdge *> enab; // the bag of enabled hyperedges
	      ComputeEnabled(h,adk,&enab); // fill enab with enabled hyperedges
	      List<Bag<ADSHyperEdge *> *> steplist; // the list of all possible steps
	      Step(h,adk,&enab,&steplist); // compute steplist (list of steps)
	      
	      // not every step in the steplist is maximal
	      // therefore the maximal steps are filtered out next
	      
	      int slength=steplist.count();	      
	      
	      for (int ii=0;ii<slength;ii++){

	
		ADSValuation *klnew=TakeStep(h,c,adk,steplist[ii]); // take the step. This results in a unique next valuation, could be stable or unstable.
		
	      



		// TODO 
		// 
		// make this next valuation unstable
		// DO NOT DO




		ADSValuation *oldadk=c->FindSimilarNode(klnew);
		if (!oldadk){ 
		  
		  //	      if (!c->ExistsSimilarNode(klnew)){
		  c->AddNode(klnew);
		  unprocessed.add(klnew);
		  ADSTransition *ktnew = new ADSTransition(c,adk,klnew,steplist[ii]); // make a transition in which a step is taken
		  c->AddEdge(ktnew);		
		  string str;
		  if (c->GrowsInfinite(klnew,str)){
		    string s="The activity diagram is infinite (state "+ str + " is unbounded)!\n";
		    char s1[100];
		    strcpy(s1,s.getstr());
		    error(s1);
		    return;
		  }
		}
		else{  // there exists already a similar node
		  //	ADSValuation *old=c->FindSimilarNode(klnew);
		  delete klnew;
		  ADSTransition *ktnew = new ADSTransition(c,adk,oldadk,steplist[ii]); 
		  if (!c->ExistsSimilarEdge(ktnew)){
		    c->AddEdge(ktnew);
		  }	 
		  else delete ktnew;
		}
	      }
	    } // end else
	  }
	}
      }
      unprocessed.remove(adk); // adk is processed so remove it	      
    }
  }

*/

// }
