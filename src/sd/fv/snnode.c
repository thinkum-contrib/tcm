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
#include "snnode.h"
#include "sngraph.h"
#include "lstring.h"

SNNode::SNNode(SNGraph *g): Node(g) {}

Subject::NameErrType SNNode::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s != *GetName() && *s != "" && 
		(GetGraph()->CountNodes(s, Code::STATE_VECTOR)+
		 GetGraph()->CountNodes(s, Code::DATA_STREAM)+
		 GetGraph()->CountNodes(s, Code::SN_PROCESS)+
		 GetGraph()->CountNodes(s, Code::CONTROLLED_DATA_STREAM) > 0))

		return Subject::DOUBLE_NODE;
	else
		return Node::SetName(s);
}
