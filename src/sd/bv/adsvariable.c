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
#include "adsvariable.h"
#include "stdio.h"
#include "outputfile.h"

ADSVar::ADSVar(const char *str, PropType p){
  name=str;
  ptype=p;
}

ADSVar::~ADSVar(){}

bool ADSVar::operator==(const ADSVar &comp) const {
  if ((comp.name==name)&&(comp.ptype==ptype)) return True; else return False;
}

ADSVar::ADSVar(const ADSVar &copy){
  name=copy.name;
  ptype=copy.ptype;
}  

string ADSVar::GetName(void) const {
  return name;
}
	

PropType ADSVar::GetType(void){
  return ptype;
}

void ADSVar::Write(OutputFile *ofile){
  string d="ERROR";
  if (ptype==::PROP) d="property" ;
  if (ptype==::INT)  d="integer" ;
  if (ptype==::STRING) d="string" ;
  (* ofile)<< "\t{ Variable " << name << ": " << d << " }\n";
}


void ADSVar::WriteScreen(){
  string d="ERROR";
  if (ptype==::PROP) d="property" ;
  if (ptype==::INT)  d="integer" ;
  if (ptype==::STRING) d="string" ;
  std::cout << "\t{ Variable " << name << ": " << d << " }\n";
}

