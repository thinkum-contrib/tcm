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
#include "scnode.h"
#include "scgraph.h"
#include "lstring.h"

SCNode::SCNode(SCGraph *g): Node(g) {}

Subject::NameErrType SCNode::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s == *GetName() || *s == "" || 
			(GetGraph()->CountNodes(s, Code::SCD_OR_STATE) + 
			GetGraph()->CountNodes(s, Code::SCD_AND_STATE) == 0))
		return Node::SetName(s);
	else
		return Subject::DOUBLE_NODE;
}


	
SCNode *SCNode::leader(){
  if (!GetParent()) return 0;
  // if (!isina()) return 0; //leader is not defined
  SCNode *answer;
  if (((SCNode *)GetParent())->isino()) 
    answer= ((SCNode *)GetParent());
  else 
    answer= ((SCNode *)GetParent())->leader();
  //if (!answer) std::cout << "answer \t" << answer->GetId() << "\n";
  return answer;
}


void SCNode::GetFollowers(List <SCNode *> &scl){
  List <SCNode *> amnodes;
  GetGraph()->GetNodes((List <Subject *> *)&amnodes);
  for (amnodes.first();!amnodes.done();amnodes.next()){
    if ((amnodes.cur()->leader()==this) && (amnodes.cur()->isina())){
      scl.add(amnodes.cur());
    }
  }
}

void SCNode::GetChildren(List <SCNode *> &scl){
  List <SCNode *> amnodes;
  GetGraph()->GetNodes((List <Subject *> *)&amnodes);
  for (amnodes.first();!amnodes.done();amnodes.next()){
    if (amnodes.cur()->GetParent()==this){
      scl.add(amnodes.cur());
    }
  }
}


bool SCNode::isancestor(SCNode *ancestor){
  if (ancestor==this) return True;
  if (!GetParent()) return False;
  return (((SCNode *)GetParent())->isancestor(ancestor));
}
