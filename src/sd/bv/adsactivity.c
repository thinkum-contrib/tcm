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
#include "outputfile.h"
#include "adsvariable.h"

ADSActivity::ADSActivity(string str){
  s=str;
  s.replace("-\r","");
  s.replace('\r','_');
}

	
ADSActivity::ADSActivity(const ADSActivity &copy){
  s=copy.s;
  ul=copy.ul;
}



ADSActivity::~ADSActivity(){}

bool ADSActivity::operator==(const ADSActivity &comp) const{
  return (comp.s==s);
}


string  ADSActivity::GetName(void){
  return s;
}


void ADSActivity::AddUpdate(ADSVar *v){
  bool b=True;
  for (ul.first();!ul.done();ul.next()){
    if (*ul.cur()==*v) {b=False;break;}
  }
  if (b) ul.add(v);
}


void ADSActivity::RemoveUpdate(ADSVar *v){
  ul.remove(v);
}


void ADSActivity::Write(OutputFile *ofile){

  (* ofile)<< "\t{ Basic activity : " << s  << " }\n";
}

void ADSActivity::Write(){

  std::cout<< "\t{ Basic activity : " << s  << " }\n";
  for (ul.first();!ul.done();ul.next()){
    ul.cur()->WriteScreen();
  }
}






