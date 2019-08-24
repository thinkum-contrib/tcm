////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "atdwaitstatenode.h"
#include "atgraph.h"

ATDWaitStateNode::ATDWaitStateNode(ATGraph *g): Node(g) { }

Subject::NameErrType ATDWaitStateNode::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s == *GetName() || *s == "" || 
		(GetGraph()->CountNodes(s, Code::ATD_ACTION_STATE_NODE) + 
		GetGraph()->CountNodes(s, Code::ATD_WAIT_STATE_NODE) == 0)) {
		return Node::SetName(s);
	}
	else
		return Subject::DOUBLE_NODE;
}
