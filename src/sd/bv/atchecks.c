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
#include "atchecks.h"
#include "graph.h"
#include "node.h"
#include "transition.h"
#include "diagram.h"
#include "initialstate.h"

ATChecks::ATChecks(Diagram *d, Graph *g): DiagramChecks(d,g) { }

unsigned ATChecks::CheckUnreachableStates(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> initStates, States, finalStates;
	Subject *initState;
	Subject *finalState;

	GetGraph()->GetNodes(&initStates, Code::ATD_INITIAL_STATE_NODE);
	GetGraph()->GetNodes(&States, Code::ATD_ACTION_STATE_NODE);
	GetGraph()->GetNodes(&States, Code::ATD_DECISION_STATE_NODE);
	GetGraph()->GetNodes(&States, Code::ATD_SYNCHRONIZATION_NODE);
	GetGraph()->GetNodes(&States, Code::ATD_WAIT_STATE_NODE);
	GetGraph()->GetNodes(&finalStates, Code::ATD_FINAL_STATE_NODE);

	if (initStates.count() == 0)
		return 0;
	else
		initState = initStates[0];

	if (finalStates.count() == 0)
		return 0;
	else
		finalState = finalStates[0];

	if (!GetGraph()->PathExists(initState, finalState)) {
		chkbuf += "* Error: FinalState ";
		chkbuf += "is not reachable from the initial state\n";
		GetDiagram()->SelectSubject(initState);
		GetDiagram()->SelectSubject(finalState);
		total++;
	}

	// Check unreachable states
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
	// Check zombie states
	for (States.first(); !States.done(); States.next()) {
		Subject *state = States.cur();
		if (!GetGraph()->PathExists(state, finalState)) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(state->GetClassType());
			chkbuf += " '";
			chkbuf += *state->GetName();
			chkbuf += "' ";
			chkbuf += "can not reach the final state\n";
			GetDiagram()->SelectSubject(state);
			total++;
		}
	} 
	return total;
}

unsigned ATChecks::CheckNoActions(string & /* chkbuf */ ) {
	return 0;
}

unsigned ATChecks::CheckEmptyActions(string & /* chkbuf */ ) {
	unsigned total = 0;
	return total;
}

unsigned ATChecks::CheckEmptyEvents(string & /* chkbuf */ ) {
	unsigned total = 0;
	return total; 
}

unsigned ATChecks::CheckDoubleEvents(string & /* chkbuf */ ) {
	unsigned total = 0;
	return total;
}
