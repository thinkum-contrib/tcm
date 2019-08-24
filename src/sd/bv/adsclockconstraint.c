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
#include "adsclockconstraint.h"
#include "adsclock.h"
#include "stdio.h"
#include "outputfile.h"
#include "node.h"
#include "error.h"

ClockConstraint::ClockConstraint(Clock *c, PropType p,int n): Prop("",p){
  limit=n;
  SetVar(c);
}

ClockConstraint::ClockConstraint(){}


ClockConstraint::~ClockConstraint(){
}

bool ClockConstraint::operator==(const ClockConstraint &comp) const {
  if ((Prop::GetVar()==comp.Prop::GetVar()) &&(Prop::GetType()==comp.Prop::GetType()) && (comp.limit==limit)) return True; else return False;
}


ClockConstraint::ClockConstraint(const ClockConstraint &copy): Prop(copy){
  limit=copy.limit;
}  

Clock *ClockConstraint::GetClock(){
  Clock *ctemp=(Clock*)GetVar();
  if (ctemp==0) error ("There is clock constraint with a lost clock!\n");
  return ctemp;
}	

void ClockConstraint::Write(OutputFile *o){
  (*o) << "Clock constraint:\t" << GetId() << "\n" ;
  if (GetType()==AFTER) (*o) << "AFTER\t";
  else
    if (GetType()==WHEN) (*o) << "WHEN\t";
    else (*o) << "ERROR!\t";
  (*o) << "\tlimit:\t" << limit << "\n";
}

void ClockConstraint::Write(){
  std::cout << "Clock constraint:";
  if (GetType()==AFTER) std::cout << "AFTER\t";
  else
    if (GetType()==WHEN) std::cout << "WHEN\t";
    else std::cout << "ERROR!\t";
  std::cout << "\tlimit:\t" << limit << "\n";
}


int ClockConstraint::GetLimit(){
  return limit;
}
