/////////////////////////////////////////////////////////////////////////////////
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
#include "adsclockmanager.h"
#include "adscks.h"
#include "util.h"
#include "outputfile.h"
#include "edge.h"
#include "adsvaluation.h"
#include "adstransition.h"
#include "adshypergraph.h"
#include "adspropertyvaluation.h"
#include "bag.h"

ADSCks::ADSCks(ADSHyperGraph *a) : Graph() {
  am=a;
}

ADSCks::~ADSCks() {
}

void ADSCks::AddNode(Node *n){
  Graph::AddNode(n);
  //    vhl.add((ADSValuation *)n,((ADSValuation *)n)->ComputeKey());
}

void ADSCks::AddEdge(Edge *e){
  Graph::AddEdge(e);
  //    thl.add((ADSTransition *)e,((ADSTransition *)e)->ComputeKey());
}


void ADSCks::WriteSubjects(OutputFile *f) {
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  (*f) << "# GRAPH NODES\n\n";
  for (cksnodes.first(); !cksnodes.done(); cksnodes.next()) {
    if (check(cksnodes.cur()))
      cksnodes.cur()->Write(f);
  }
  List <ADSTransition *> cksedges;
  GetEdges((List <Subject *> *)&cksedges);
  (*f) << "# GRAPH EDGES\n\n";
  for (cksedges.first(); !cksedges.done(); cksedges.next()) {
    if (check(cksedges.cur()))
      cksedges.cur()->Write(f);
  } 
}



bool ADSCks::ExistsSimilarEdge( ADSTransition *e){
  //    if (thl.isin(e,e->ComputeKey())==NULL) return False;
  //   return True;
                      
  List <ADSTransition *> cksedges;
  GetEdges((List <Subject *> *)&cksedges);
  for (cksedges.first(); !cksedges.done(); cksedges.next()){
    if ((*cksedges.cur())==*e) {
      return True;
    }
  }
  return False;
       
    
}

ADSValuation *ADSCks::FindSimilarNode( ADSValuation *s){
  //    return vhl.isin(s,s->ComputeKey());
  
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  for (cksnodes.first(); !cksnodes.done(); cksnodes.next()){
    if ((*cksnodes.cur())==*s) {
      return cksnodes.cur();
    }
  }
  return NULL;
  
}



// procedure to detect unbounded state nodes
// it is taken from the Karp-Miller algorithm
// if there exists another valuation s' such that s'->C' < s->C
// and there is a path from s to s' then
//  some state node is unbounded
bool ADSCks::GrowsInfinite(ADSValuation *s, string &str){
  Bag <Subject *> scfg;
  s->GetConfig(&scfg);
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  for (cksnodes.first(); !cksnodes.done(); cksnodes.next()){
    Bag <Subject *> cfg;
    cksnodes.cur()->GetConfig(&cfg);
    if ((scfg.contains(cfg)) && (!cfg.contains(scfg)) && (PathExists(cksnodes.cur(),s)) ){
      List <Subject *> l;
      scfg.GetList(l);
      for (l.first();!l.done();l.next()){
	if (scfg.count(l.cur())>cfg.count(l.cur())) str=*(l.cur()->GetName());
      }
      return True; // scfg strictly contains cfg and cksnodes.cur() leads to s
    }
  }
  return False;  
}

/////

string replace(string s){
  string t=s;
  t.replace("-\r","");
  t.replace('\r','_');
  t.replace(' ','_');
  t.replace('.','_');
  t.replace('/','_');
  //  t.replace('(','_');
  //  t.replace(')','_');
  t.replace('-','_');
  t.replace('=','_');
  t.replace("\"",'_');
  return t;
}






void ADSCks::WriteSMVFile(OutputFile *ofile, bool sf){
  (*ofile) <<  "MODULE main\n\nVAR\n";
  List <Subject *> amnodes;
  am->GetNodes((List <Subject *> *)&amnodes);
  AssignNumbers();   



  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  int nodescount=cksnodes.count();

  (*ofile) << "\tc____counter : 0.." << nodescount-1 << " ;  -- program counter  \n"; // putting the program counter first gives more efficient BDD ordering 

  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if ((amnodes.cur()->GetClassType()==Code::NOTE)||(amnodes.cur()->GetClassType()==Code::COMMENT)) continue; // skip these 
    string s=(*(amnodes.cur()->GetName()));
    s.replace("-\r","");
    s.replace('\r','_');
    s.replace(' ','_');
    if (amnodes.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE){ 
      s="I___INITIAL";amnodes.cur()->SetName(&s);
    }
    if (amnodes.cur()->GetClassType()==Code::ATD_FINAL_STATE_NODE){ 
      string t = (int)amnodes.cur()->GetId();
      s="F___FINAL"+t; amnodes.cur()->SetName(&s);
    }
    (*ofile ) << "\t"<< replace(s) << " : 0.."<< am->GetBound(amnodes.cur()) <<";\n";
    if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      (*ofile ) << "\tT_" << replace(s) << " : 0.."<< am->GetBound(amnodes.cur()) <<";\n";
    }
  }
  List <Prop *> pl;
  am->GetPropList(pl);
  for (pl.first();!pl.done();pl.next()){
     string s=pl.cur()->GetName(); 
     (*ofile ) << "\t" << replace(s) << " : boolean;\n";    
  }
  (*ofile) << "\tstable:boolean;\n";


  (*ofile) << "INIT\n";
  (*ofile) << "\tc____counter = 0 & \n "; // because of assign number
  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if ((amnodes.cur()->GetClassType()==Code::NOTE)||(amnodes.cur()->GetClassType()==Code::COMMENT)) continue; // skip these 
    string s=(*(amnodes.cur()->GetName()));
    (*ofile ) << "\t"<< replace(s) << " = " ;
    (amnodes.cur()->GetClassType()==Code::ATD_INITIAL_STATE_NODE)? (*ofile) << "1" : (*ofile) << "0" ;
    (*ofile) << " & \n";
    if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      (*ofile ) << "\tT_" << replace(s) << " = 0 & \n";
    }
  }
  for (pl.first();!pl.done();pl.next()){
    string s=pl.cur()->GetName();
   (*ofile ) << "\t" << replace(s) << "= 0 & \n";    
  }
  
  (*ofile) << "\tstable= 0 \n\n";

  (*ofile) << "TRANS\n";

  // print program counter
  (*ofile) << "\tnext(c____counter) in\n\t\tcase\n";     
  for (cksnodes.first();!cksnodes.done();cksnodes.next()){
    (*ofile) << "\t\t\t c____counter = " << cksnodes.cur()->GetNumber() << " : {";
    List <ADSTransition *> akl;
    GetEdgesFrom((List <Subject *> *)&akl,cksnodes.cur());
    akl.first();
    if (akl.count()==0){
      (*ofile) << cksnodes.cur()->GetNumber() << "};\n"; // final state is self loop
    }
    else{
      akl.first();
      (*ofile) << ((ADSValuation *)akl.cur()->GetSubject2())->GetNumber();
      if (akl.count()==1){
	(*ofile) << "};\n";
      }
      else{
	akl.next();
	for (;!akl.done();akl.next()){
	  (*ofile) << "," <<  ((ADSValuation *)akl.cur()->GetSubject2())->GetNumber() ;
	}
	(*ofile) << "};\n";
      }
    }
  }
  (*ofile) << "\t\tesac\n\t&\n";

  // print configuration variables
  for (amnodes.first();!amnodes.done();amnodes.next()){    
    if ((amnodes.cur()->GetClassType()==Code::NOTE)||(amnodes.cur()->GetClassType()==Code::COMMENT)) continue; // skip these 
    string s=(*(amnodes.cur()->GetName()));
    (*ofile ) << "\tnext("<< replace(s) << ") in\n\t\tcase\n";
 
    for (cksnodes.first();!cksnodes.done();cksnodes.next()){
      Bag <Subject *> currentcfg;
      cksnodes.cur()->GetConfig(&currentcfg);
      List <Subject *> currentcfgl;
      currentcfg.GetSet(&currentcfgl);
      if (currentcfgl.find(amnodes.cur())>-1){
	(*ofile) << "\t\t\tnext(c____counter) = " << cksnodes.cur()->GetNumber() << ": " << currentcfg.count(amnodes.cur()) << ";\n";
      }
      else{
	(*ofile) << "\t\t\tnext(c____counter) = " << cksnodes.cur()->GetNumber() << ": 0 ;\n";
      }
    }
    (*ofile) << "\t\tesac\n\t&\n";

    if (amnodes.cur()->GetClassType()==Code::ATD_ACTION_STATE_NODE){
      string str=(*(amnodes.cur()->GetName())); 
      (*ofile ) << "\tnext(T_"<< replace(str) << ") in\n\t\tcase\n";    
      for (cksnodes.first();!cksnodes.done();cksnodes.next()){
	Bag <ATDActionStateNode *> term;
	cksnodes.cur()->GetTerminated(&term);
	List <ATDActionStateNode *> terml;
	term.GetSet(&terml);
	if (terml.find((ATDActionStateNode *)amnodes.cur())>-1){
	  (*ofile) <<  "\t\t\tnext(c____counter) = " <<cksnodes.cur()->GetNumber() << ": "<< term.count((ATDActionStateNode *)amnodes.cur()) <<";\n";
	}
	else {
	  (*ofile) <<  "\t\t\tnext(c____counter) = " <<cksnodes.cur()->GetNumber() << ": 0;\n";
	}
      }
      (*ofile) << "\t\tesac\n\t&\n";
    }

  }
  //
  for (pl.first();!pl.done();pl.next()){
    string s=pl.cur()->GetName();
    (*ofile ) << "\tnext("<< replace(s) << ") in\n\t\tcase\n";
    PropVal pvt(pl.cur(),true);
    for (cksnodes.first();!cksnodes.done();cksnodes.next()){
      List <PropVal *> plcur;
      cksnodes.cur()->GetPropList(&plcur);
      bool Found=False;
      for (plcur.first();!plcur.done();plcur.next()){
	if (((*(plcur.cur()))==pvt)){
	  (*ofile) << "\t\t\tnext(c____counter) = "<< cksnodes.cur()->GetNumber() << ": 1; \n";
	  Found=True;
	  break;
	}
      }
      if (!Found){ // if not found, then false
	(*ofile) << "\t\t\tnext(c____counter) = "<< cksnodes.cur()->GetNumber() << ": 0; \n";             
      }
    }
    (*ofile) << "\t\tesac\n\t\t&\n";
  }

  (*ofile) << "\tnext(stable) in\n\t\tcase\n";
  for (cksnodes.first();!cksnodes.done();cksnodes.next()){
    (*ofile) << "\t\t\tnext(c____counter) = "<< cksnodes.cur()->GetNumber() << ": ";
    if (cksnodes.cur()->isStable()){
      (*ofile) << "1;\n";
    } 
    else{
      (*ofile) << "0;\n";
    }
  }
  (*ofile) << "\t\tesac\n";

  if (sf){
    List <ADSHyperEdge *> amedges;
    am->GetHyperEdges((List<Subject *> *)&amedges);
    for (amedges.first();!amedges.done();amedges.next()){
      List <Subject *> *source=amedges.cur()->GetSubject1();
      List <Subject *> *target=amedges.cur()->GetSubject2();
      (*ofile) << "\n";
      (*ofile) << "COMPASSION\n"; 
      (*ofile) << "(stable &";
      bool First=True;
      for (source->first();!source->done();source->next()){
	string s = *(source->cur()->GetName());
	if (!First){
	  (*ofile) << " & ";
	}
	else First=False;
	(*ofile) << replace(s) << " > 0 ";
      }
      (*ofile) << ", stable & ";
      First=True;
      for (target->first();!target->done();target->next()){
	string s = *(target->cur()->GetName());
	if (!First){
	  (*ofile) << " & ";
	}
	else First=False;
	(*ofile) << replace(s) << " > 0 ";
      }
      (*ofile) << " )\n";
    }
    (*ofile) << "\n\n";
  }
}




		 

	
void ADSCks::GetClocks(List <string> *l){
  List <ADSHyperEdge *> amedges;
  am->GetHyperEdges((List <Subject *> *)&amedges);
  for (amedges.first();!amedges.done();amedges.next()){
    if (amedges.cur()->hasClockConstraint()){
      string s=amedges.cur()->GetClockConstraint()->GetClock()->GetName();
      l->add(s);
    }
  }
}


void ADSCks::AssignNumbers(){
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  int i=0;
  for (cksnodes.first();!cksnodes.done();cksnodes.next()){
    cksnodes.cur()->SetNumber(i);
    i++;
  }
}


// the following procedure requires that AssignNumbers has been done before
ADSValuation *ADSCks::GetADSValuation(int i){
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  for (cksnodes.first();!cksnodes.done();cksnodes.next()){
    if (i==cksnodes.cur()->GetNumber()) return cksnodes.cur();
  }
  return NULL;
}

// count and print different configurations
int ADSCks::countconfigs(){
  List <ADSValuation *> configlist;
  int cfgcounter=0; 
  int stablecount=0;
  int prec=0;
  List <ADSValuation *> cksnodes;
  GetNodes((List <Subject *> *)&cksnodes);
  int ckscount=cksnodes.count();
  for (int i=0;i<ckscount;i++){
    if (!cksnodes[i]->isStable()) stablecount++;
    else{ if (CountEdgesTo(cksnodes[i])>1) prec++;}
    bool found=False;
    for (int j=i+1;j<ckscount;j++){
      if (cksnodes[i]->hassameconfig(*cksnodes[j])){ found=True;break;}
    }
    if (!found){
      cfgcounter++;
      configlist.add(cksnodes[i]);
    }
  }
  std::cout << "\nThere are "<< stablecount << " unstable states\n";
  std::cout << "\nThere are "<< prec << " states with more than one predecessor\n";
  List <ADSTransition *> cksedges;
  List <ADSValuation *> temp;
  GetEdges((List <Subject *> *)&cksedges);
  ckscount=cksedges.count();
  for (int i=0;i<ckscount;i++){
    if ((!((ADSValuation*)cksedges[i]->GetSubject1())->isStable()) &&
        (!((ADSValuation*)cksedges[i]->GetSubject2())->isStable()))
      if (temp.find((ADSValuation*)(cksedges[i]->GetSubject2()))<0)
        temp.add((ADSValuation*)(cksedges[i]->GetSubject2()));
  }
  std::cout << "\nThere are "<< temp.count() << " superstep states\n";
  std::cout << "\nThere are "<< cfgcounter << " different configruations!\n";

  return cfgcounter;
}

