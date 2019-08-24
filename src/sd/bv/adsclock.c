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
#include "adsclock.h"
#include "stdio.h"
#include "outputfile.h"
#include "adshyperedge.h"
#include "error.h"

Clock::Clock(ADSHyperEdge *he): ADSVar("lc",AFTER){
  hedge=he;
}

Clock::Clock(Edge *he): ADSVar("lc",AFTER){
  edge=he;
}

Clock::Clock(): ADSVar("gc",WHEN){
  hedge=0;
}

Clock::~Clock(){}

bool Clock::operator==(const Clock &comp) const {
  if ((GetName()==comp.GetName()) &&(comp.hedge==hedge) ) 
    return True; 
  else return False;
}


Clock::Clock(const Clock &copy): ADSVar(copy){
  hedge=copy.hedge;
}  

string Clock::GetName() const{
  if (hedge==0){
    error("hedge is null\n");
    return "";
  }
  string s="t_";
  string t= int(hedge->GetId());
  return s+t;
}



ADSHyperEdge  *Clock::GetHyperEdge(void){
  return hedge;
}


Edge  *Clock::GetEdge(void){
  return edge;
}
