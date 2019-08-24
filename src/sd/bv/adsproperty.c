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
#include "adsproperty.h"
#include "adsvariable.h"
#include "outputfile.h"


Prop::Prop(const char *str,PropType p){
  s=str;
  stype=p;
  v=0;
}

	
Prop::Prop(const Prop &copy){
  s=copy.s;
  stype =copy.stype;
}



Prop::~Prop(){}


int Prop::GetId(){
  return s.length();
}


bool Prop::operator==(const Prop &comp) const{
  if (comp.s==s) return True; else return False;
}



string  Prop::GetName(void){
  return s;
}

PropType Prop::GetType(void) const{
	return stype;
}

void Prop::SetType(PropType p){
  stype=p;
}


void Prop::SetVar(ADSVar *var){
  v=var;
}

ADSVar *Prop::GetVar(void) const {
  return v;
}

bool Prop::isInternal(){
  return ((stype==::INTERNAL_PROP)||(stype==::INTERNAL_INT)||(stype==::INTERNAL_STRING)||(stype==::SENDEVENT));
}


void Prop::Write(OutputFile *ofile){
  string d;
  switch (stype) {
  case ::PROP :    d="property" ;break;
  case ::INT :     d="integer" ;break;
  case ::STRING :  d="string" ;break;
  case ::EVENT :   d="event" ;break;
  case ::SENDEVENT :   d="SENDevent" ;break;
  case ::INTERNAL_PROP :    d="internal property" ;break;
  case ::INTERNAL_INT :     d="internal integer" ;break;
  case ::INTERNAL_STRING :  d="internal string" ;break; 
  default: d="ERROR";
  }
  (* ofile)<< "\t{ Basic proposition : " << s << ": " << d << " }\n";
  if (v==0){
   (*ofile) << "NO var referenced\n";
  }
  else{
    (*ofile) << "Var ";
    v->Write(ofile);
    (*ofile) << "is referenced \n";
  }
}


void Prop::Write(){
  string d;
  switch (stype) {
  case ::PROP :    d="property" ;break;
  case ::INT :     d="integer" ;break;
  case ::STRING :  d="string" ;break;
  case ::EVENT :   d="event" ;break;
  case ::SENDEVENT :   d="SENDevent" ;break;
  case ::INTERNAL_PROP :    d="internal property" ;break;
  case ::INTERNAL_INT :     d="internal integer" ;break;
  case ::INTERNAL_STRING :  d="internal string" ;break; 
  default: d="ERROR";
  }
  std::cout<< "\t{ Basic proposition : " << s << ": " << d << " }\n";
  if (v==0){
   std::cout << "NO var referenced\n";
  }
  else{
    std::cout << "Var ";
    v->WriteScreen();
    std::cout << "is referenced \n";
  }
}

