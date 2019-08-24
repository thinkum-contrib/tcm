////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "stchecks.h"
#include "graph.h"
#include "node.h"
#include "transition.h"
#include "diagram.h"
#include "initialstate.h"

STChecks::STChecks(Diagram *d, Graph *g): DiagramChecks(d,g) { }

unsigned STChecks::CheckUnreachableStates(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> initStates, States;
	Subject *initState;
	GetGraph()->GetNodes(&initStates, Code::INITIAL_STATE);
	GetGraph()->GetNodes(&States, Code::STATE);
	GetGraph()->GetNodes(&States, Code::DECISION_POINT);
	if (initStates.count() == 0)
		return 0;
	else
		initState = initStates[0];
	for (States.first(); !States.done(); States.next()) {
		Subject *state = States.cur();
		if (!GetGraph()->PathExists(initState, state)) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(state->GetClassType());
			chkbuf += " '";
			chkbuf += *state->GetName();
			chkbuf += "' ";
			chkbuf += "is not reachable from the initial state\n";
			GetDiagram()->SelectSubject(state);
			total++;
		}
	} 
	return total;
}

unsigned STChecks::CheckNoActions(string &chkbuf) {
	List<Subject *> transitions;
	GetGraph()->GetEdges(&transitions, Code::TRANSITION);
	for (transitions.first(); !transitions.done(); transitions.next()) {
		Transition *transition = (Transition *)transitions.cur();
		if (transition->NrActions() > 0)
			// ok there is an action in a transition.
			return 0;
	}
	List<Subject *> initStates;
	GetGraph()->GetNodes(&initStates, Code::INITIAL_STATE);
	for (initStates.first(); !initStates.done(); initStates.next()) {
		InitialState *initState = (InitialState *)initStates.cur();
		if (initState->NrActions() > 0)
			// ok there is an action in an initial state.
			return 0;
	}
	// there is no action.
	chkbuf += "* Error: the diagram does not contain any action\n";
	return 1;
}

unsigned STChecks::CheckEmptyActions(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> transitions;
	GetGraph()->GetEdges(&transitions, Code::TRANSITION);
	for (transitions.first(); !transitions.done(); transitions.next()) {
		Transition *transition = (Transition *)transitions.cur();
		// transitions from and to the same node should have
		// an action.
		if (transition->GetSubject1() == transition->GetSubject2()) {
			if (transition->NrActions() > 0)
				continue;
			chkbuf += "* Error: the transition from and to ";
			Subject *n = transition->GetSubject1();
			chkbuf += Code::GetName(n->GetClassType());
			chkbuf += " '";
			chkbuf += *n->GetName();
			chkbuf += "' should have actions\n";
			GetDiagram()->SelectSubject(transition);
			total++;
		}
	}
	return total;
}

unsigned STChecks::CheckEmptyEvents(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> transitions;
	GetGraph()->GetEdges(&transitions, Code::TRANSITION);
	for (transitions.first(); !transitions.done(); transitions.next()) {
		Transition *transition = (Transition *)transitions.cur();
		const string *event = transition->GetEvent();
		if (*event == "") {
			GetDiagram()->SelectSubject(transition);		
			total++;
		}
	}
	if (total > 0) {
		chkbuf += "* Error: there ";
		if (total == 1)
			chkbuf += "is a Transition";
		else {
			chkbuf += "are ";
			chkbuf += total;
			chkbuf += " Transitions";
		}
		chkbuf += " without an event\n";
	} 
	return total; 
}

unsigned STChecks::CheckDoubleEvents(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> transitions;  // all transitions.
	List<Subject *> transitions2; // transitions between same states.
	List<Subject *> transitions3; // already checked transitions.
	GetGraph()->GetEdges(&transitions, Code::TRANSITION);
	for (transitions.first(); !transitions.done(); transitions.next()) {
		Transition *transition = (Transition *)transitions.cur();
		if (transitions3.find(transition) == -1) {
			const string *event = transition->GetEvent();
			if (*event == "")
				continue;
			transitions2.empty();
			GetGraph()->GetEdges(&transitions2, 
						transition->GetSubject1(), 
						transition->GetSubject2(), 
						Code::TRANSITION);
			int card = 0;
			for (transitions2.first(); !transitions2.done(); 
					transitions2.next()) {
				Transition *transition2 = 
					(Transition *)transitions2.cur();
				if (transition2 != transition && 
					*event == *transition2->GetEvent()) {
					transitions3.add(transition2);
					GetDiagram()->SelectSubject(transition);
					GetDiagram()->SelectSubject(transition2);
					card++;
				}

			}
			if (card > 0) {
				chkbuf += "* Error: there are ";
				chkbuf += card+1;
				chkbuf += " transitions between node '";
				chkbuf += *transition->GetSubject1()->GetName();
				chkbuf += "' and node '";
				chkbuf += *transition->GetSubject2()->GetName();
				chkbuf += "' having event ";
				chkbuf += *event;
				chkbuf += " \n";
			}
		}
		transitions3.add(transition);
	}
	return total;
}
