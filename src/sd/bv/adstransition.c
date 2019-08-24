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
#include "adstransition.h"
#include "adsvaluation.h"
#include "adsclockconstraint.h"
#include "adsclock.h"
#include <ctype.h>
#include "adspropertyvaluation.h"


ADSTransition::ADSTransition(ADSCks *c, ADSValuation *from, ADSValuation *to): Edge (c,from,to){
  SetDirected(True);
  key=0 ;
}

ADSTransition::ADSTransition(ADSCks *c, ADSValuation *from, ADSValuation *to,Bag <ADSHyperEdge *> * st): Edge (c,from,to){
  SetDirected(True);
  step=*st;
  key=0;
}



bool ADSTransition::operator== ( ADSTransition &comp)  {
  if  ((comp.GetSubject1()==GetSubject1()) && (comp.GetSubject2()==GetSubject2()) && (comp.GetGraph()==GetGraph())){	
      return True;
  }
  else
    return False;
   
}



void ADSTransition::Write(OutputFile *f){
  (*f) << "AdKtransition:\t" << GetId() <<"\n";
  (*f) << "Subject 1:\t " << GetSubject1()->GetId() << ( ( ((ADSValuation*)(GetSubject1()))->isStable() ?" stable":" unstable ")) <<  "\n";
  (*f) << "Subject 2:\t " << GetSubject2()->GetId() << ( ( ((ADSValuation*)(GetSubject2()))->isStable() ?" stable":" unstable ")) <<  "\n"; 
}

void ADSTransition:: WriteScreen(){
  std::cout << "AdKtransition:\t" << GetId() <<"\n";
  std::cout << "Key\t" << key << "\n";
  std::cout << "Subject 1:\t " << GetSubject1()->GetId() << ( ( ((ADSValuation*)(GetSubject1()))->isStable() ?" stable":" unstable ")) <<  "\n";
  std::cout << "Subject 2:\t " << GetSubject2()->GetId() << ( ( ((ADSValuation*)(GetSubject2()))->isStable() ?" stable":" unstable ")) <<  "\n"; 
}


int ADSTransition::ComputeKey(){
  key=1;
  if (!key) {
    key=((GetSubject1()->GetId()) + (GetSubject2()->GetId()));
  }
  return key;
}
