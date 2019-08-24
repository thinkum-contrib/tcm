////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#include "scdorstate.h"
#include "scgraph.h"

SCDOrState::SCDOrState(SCGraph *g): SCNode(g) { }


bool SCDOrState::isbasic() const { 
  List <SCNode *> sclist;
  GetGraph()->GetNodes((List <Subject *> *)&sclist);
  for (sclist.first();!sclist.done();sclist.next()){
	if (dynamic_cast<SCDOrState *>(sclist.cur()->GetParent())==this){
      return False;
    }
  }
  return True;
}

		       
bool SCDOrState::isina()const {
  if (!isbasic()) return False; 
  if (!GetParent()) return True; // parent is root
  if (GetParent()->GetClassType()==Code::SCD_OR_STATE) return True; 
  return False;
}


bool SCDOrState::isino() const {  
  if (!GetParent()) return False; 
  if (isbasic()) return False;
  return GetParent()->GetClassType()==Code::SCD_AND_STATE;
} 
