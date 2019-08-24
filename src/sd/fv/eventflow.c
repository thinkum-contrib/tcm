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
#include "eventflow.h"
#include "dcfgraph.h"
#include "dataprocess.h"

EventFlow::EventFlow(DCFGraph *g, Subject *n1, Subject *n2): DFEdge(g, n1, n2) {
	SetDirected(True);
}

Subject::NameErrType EventFlow::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	if ((GetSubject1()->GetClassType() == Code::CONTROL_PROCESS) ||
	    (GetSubject1()->GetClassType() == Code::DATA_PROCESS)) {
		if ((GetSubject2()->GetClassType()!=Code::CONTROL_PROCESS) &&
		    (GetSubject2()->GetClassType()!=Code::DATA_PROCESS)) {
			// prompts nor triggers are allowed here.
			// NB : DATA/CONTROL PROCESS->DATA/CONTROL PROCESS : ALL allowed (990827)
			if (TriggerLabel(s) || E_D_Label(s))
				return Subject::WRONG_NAME_CONNECTION;
		}
	}
	else if ((GetSubject1()->GetClassType() == Code::EXTERNAL_ENTITY) &&
		 (GetSubject2()->GetClassType() == Code::CONTROL_PROCESS)) {
			// prompts but not triggers are allowed here.
			if (TriggerLabel(s))
				return Subject::WRONG_NAME_CONNECTION;
	}
	else if (TriggerLabel(s) || E_D_Label(s))
		// prompts nor triggers allowed.
		return Subject::WRONG_NAME_CONNECTION;
	if (*s != *GetName() && *s != "" &&
			GetGraph()->CountEdges(
				GetSubject1(), GetSubject2(), s) > 0)
		return Subject::DOUBLE_EDGE;
	DFEdge::SetName(s);
	if (TriggerLabel(s) && GetSubject2()->GetClassType() == Code::DATA_PROCESS)
		((DataProcess *)GetSubject2())->SetActivationMechanism(DataProcess::TRIGGER);
	return Subject::OK;
}
