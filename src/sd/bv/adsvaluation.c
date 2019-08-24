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
#include "adsvaluation.h"
#include "adspropertyvaluation.h"
#include <string.h>
#include <ctype.h>
#include "outputfile.h"
#include "adshypergraph.h"
#include "adsclock.h"
#include "adsclockconstraint.h"
#include "code.h"

ADSValuation::ADSValuation(ADSCks *c, StateType s): Node(c){
  index=0;
  st=s;
  cm.SetInterval(c->GetADSHyperGraph()->GetNrTimeouts()+1);
  key =0;
}

ADSValuation::~ADSValuation(){
}


ADSValuation::ADSValuation(const ADSValuation &copy): Node (copy.GetGraph()) {
  cfg=copy.cfg;
  tlist =copy.tlist;
  plist = copy.plist;
  clist = copy.clist;

  /*
  qclist = copy.qclist;
  qtermlist=copy.qtermlist;
  queue = copy.queue;
  */

  cm = copy.cm;
  st = copy.st;
  index= 0;
}

ADSValuation::ADSValuation(const ADSValuation &copy, StateType s) : Node(copy.GetGraph()) {
  cfg=copy.cfg;
  tlist =copy.tlist;
  plist = copy.plist;
  clist = copy.clist;


  /*
  qclist = copy.qclist;
  qtermlist=copy.qtermlist;
  queue = copy.queue;
  */

  cm = copy.cm;
  st = s;
  index=0;
}

bool ADSValuation::operator==( ADSValuation &comp) {
  if (st!=comp.st) return False;
  if (cfg.length()!= comp.cfg.length()) return False;

  // compare the configurations
  if (!cfg.contains(comp.cfg)) return False;
  if (!comp.cfg.contains(cfg)) return False;

  // compare the terminated list nodes 
  if (tlist.length()!= comp.tlist.length()) return False;
  if (!tlist.contains(comp.tlist)) return False;
  if (!comp.tlist.contains(tlist)) return False;

  // compare the property valuations
  int plistlen=plist.count();
  int compplistlen=comp.plist.count();
  int i,j;
  for (i=0;i<plistlen;i++){
    bool found=False;
    for (j=0;j<compplistlen;j++){  
       if ( (* (plist[i])) == (* ( comp.plist[j])) ){
	found=True;
	break;
      }
    }
    if (!found) return False;
  }
  for (j=0;j<compplistlen;j++){   
    bool found=False;       
    for (i=0;i<plistlen;i++){
       if ( (* (plist[i])) == (* ( comp.plist[j])) ) {
	found=True;
	break;
      }
    }
    if (!found) return False;
  }

  // compare the clock constraints
  int clistlen=clist.count();
  int compclistlen=comp.clist.count();
  for (i=0;i<clistlen;i++){
    bool found=False;
    for (j=0;j<compclistlen;j++){
       if ( (* (clist[i] ) ) == (* ( comp.clist[j]) )) {
        found=True;
        break;
      }
    }
    if (!found) return False;
  }
  for (j=0;j<compclistlen;j++){
    bool found=False;
    for (i=0;i<clistlen;i++){
       if ( (* (clist[i] ) ) == (* ( comp.clist[j])) ){
        found=True;
        break;
      }
    }
    if (!found) return False;
  }

  // compare the clock manager
  if (!(cm==comp.cm)) return False; // check is needed to ensure that all clock constraints are eventually met

  // ADDD CHECKS FOR ILS!!!!!

  
  /*
  // compare the queue clock constraints
  int qclistlen=qclist.count();
  int compqclistlen=comp.qclist.count();
  for (i=0;i<qclistlen;i++){
    bool found=False;
    for (j=0;j<compqclistlen;j++){
       if ( (* (qclist[i] ) ) == (* ( comp.qclist[j]) )) {
        found=True;
        break;
      }
    }
    if (!found) return False;
  }
  for (j=0;j<compqclistlen;j++){
    bool found=False;
    for (i=0;i<qclistlen;i++){
       if ( (* (qclist[i] ) ) == (* ( comp.qclist[j])) ){
        found=True;
        break;
      }
    }
    if (!found) return False;
  }

  // compare the queue
  plistlen=queue.count();
  compplistlen=comp.queue.count();
  // int i,j;
  for (i=0;i<plistlen;i++){
    bool found=False;
    for (j=0;j<compplistlen;j++){  
       if ( (* (queue[i])) == (* ( comp.queue[j])) ){
	found=True;
	break;
      }
    }
    if (!found) return False;
  }
  for (j=0;j<compplistlen;j++){   
    bool found=False;       
    for (i=0;i<plistlen;i++){
       if ( (* (queue[i])) == (* ( comp.queue[j])) ) {
	found=True;
	break;
      }
    }
    if (!found) return False;
  }

  if (!qtermlist.contains(comp.qtermlist)) return False;
  if (!comp.qtermlist.contains(qtermlist)) return False;

  */  
  return True;
}










void ADSValuation::GetConfig(Bag <Subject *> *b){
  b->join(cfg);
}

void ADSValuation::SetConfig(Bag <Subject *> c){
  List <Subject *> l;
  c.GetList(l);
  for (l.first();!l.done();l.next()){
    cfg.add(l.cur(),c.count(l.cur()));
  }
}

void ADSValuation::GetPropList(List <PropVal *> *pl){
  *pl=plist;
}

void ADSValuation::SetPropList(List <PropVal *> p){
  plist=p;
}




void ADSValuation::GetTerminated(Bag <ATDActionStateNode *> *tl){
  tl->join(tlist);
}

void ADSValuation::AddTerminated(Bag <ATDActionStateNode *>  t){
  List <ATDActionStateNode *> l;
  t.GetList(l);
  for (l.first();!l.done();l.next()){
    tlist.add(l.cur(),t.count(l.cur()));
  }
}



void ADSValuation::GetClockConstraints(List <ClockConstraint *> *cl){
  *cl=clist;
}

void ADSValuation::SetClockConstraints(List <ClockConstraint *> c){
  clist=c;
}



ClockManager ADSValuation::GetClockManager(){
       return cm;
}

void ADSValuation::SetClockManager(ClockManager &c){
  cm=c;
}



void ADSValuation::Write(OutputFile *ofile) {
  (*ofile) << "location ID:\t"<< GetId() <<"\t";
  if (st==stable) {(*ofile) << "stable\n";}
  else {(*ofile) << "unstable\n";}
  List <Subject *> l;
  cfg.GetList(l);
  for (l.first();!l.done();l.next()){
    (*ofile) << "cfg element =\n" ;  
    (*ofile) << (*(l.cur()->GetName()));
	(*ofile) << "\t:\t count = " << cfg.count(l.cur()) << "\n";
  }
  //
  
  (*ofile) << "TermList:\n";
  List <ATDActionStateNode *> l2;
  tlist.GetList(l2);
  for (l2.first();!l2.done();l2.next()){
    (*ofile) << "term el:" <<l2.cur()->GetId() <<":\t" << tlist.count(l2.cur()) <<"\n";
  }
  //
  (*ofile) << "PropValList:\n";
  for (plist.first();!plist.done();plist.next()){
	plist.cur()->Write(ofile);
  }
  (*ofile) <<"Time outs:\n";
  for (clist.first();!clist.done();clist.next()){
	clist.cur()->Write(ofile);
  }
  cm.Write(ofile);

  
  (*ofile) << "END of valuation\n";
}


void ADSValuation:: WriteScreen() {
  
  (std::cout) << "location ID:\t"<< GetId() <<"\t";
  std::cout << "\t\tkey\t" << ComputeKey() << "\n";
  if (st==stable) {(std::cout) << "stable\n";}
  else {(std::cout) << "unstable\n";}
  List <Subject *> l;
  cfg.GetList(l);
  for (l.first();!l.done();l.next()){
    (std::cout) << "cfg element =\n" ;  
    (std::cout) << (*(l.cur()->GetName()));
	(std::cout) << "\t:\t count = " << cfg.count(l.cur()) << "\n";
  }
  //
  (std::cout) << "TermList:\n";
  List <ATDActionStateNode *> l2;
  tlist.GetList(l2);
  for (l2.first();!l2.done();l2.next()){
    (std::cout) << "term el:" <<l2.cur()->GetId() <<":\t" << tlist.count(l2.cur()) <<"\n";
  }
  //
  (std::cout) << "PropValList:\n";
  for (plist.first();!plist.done();plist.next()){
	plist.cur()->Write();
  }
  cm.Write();
  (std::cout) << "END of valuation\n";
}



void ADSValuation::SetNumber(int i){
  index=i;
}

int ADSValuation::GetNumber(){
  return index;
}


int ADSValuation::ComputeKey(){
  if (!key){
    key=1;
    List <Subject *> l;
    cfg.GetList(l);
    for (l.first();!l.done();l.next()){
      key = key * (7*(l.cur()->GetId()) * (cfg.count(l.cur())));
    }
    List <ATDActionStateNode *> l2;
    tlist.GetList(l2);
    for (l2.first();!l2.done();l2.next()){
      key = key + (1 * (l2.cur()->GetId()) * (tlist.count(l2.cur()) ))  ;
    }    
    for (plist.first();!plist.done();plist.next()){
      if (plist.cur()->GetBool())
		key=key + ((1) * (plist.cur()->GetProp()->GetId()));
    }   
    if (st!=stable) key=key+1;
  }
  return key;
}

bool ADSValuation::hassameconfig( ADSValuation &comp){
  Bag <Subject *> sb;
  sb.join(cfg);
  sb.join(comp.cfg);
  List <Subject *> sl;
  sb.GetList(sl);
  for (sl.first();!sl.done();sl.next()){
    if (cfg.count(sl.cur())!=comp.cfg.count(sl.cur()))
      return False;
     }   
  return true;
}



/*


void ADSValuation::GetQueue(List <PropVal *> *q){
  *q=queue;
}

void ADSValuation::SetQueue(List <PropVal *> q){
  queue=q;
}

void ADSValuation::GetQClockConstraints(List <ClockConstraint *> *cl){
  *cl=qclist;
}

void ADSValuation::SetQClockConstraints(List <ClockConstraint *> c){
  qclist=c;
}

void ADSValuation::GetQTerminated(Bag <ATDActionStateNode *> *tl){
  tl->join(qtermlist);
}

void ADSValuation::AddQTerminated(Bag <ATDActionStateNode *>  t){
  List <ATDActionStateNode *> l;
  t.GetList(l);
  for (l.first();!l.done();l.next()){
    qtermlist.add(l.cur(),t.count(l.cur()));
  }
}
*/


