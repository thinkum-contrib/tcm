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
#include "transition.h"
#include "stgraph.h"
#include "inputfile.h"
#include "outputfile.h"
#include "stringlist.h"
#include "error.h"

Transition::Transition(STGraph *g, Subject *n1, Subject *n2): Edge(g, n1, n2) {
	SetDirected(True);
	event = "";
	actions = new List<string *>;
}

Transition::Transition(const Transition &t): Edge(t) {
	event = t.event;
	actions = new List<string *>;
	for (t.actions->first(); !t.actions->done(); t.actions->next()) {
		string *a = t.actions->cur();
		string *b = new string (*a);
		actions->add(b);
	}
}

Transition::~Transition() {
	actions->clear();
	delete actions;
}

Subject::NameErrType Transition::SetName(const string *) {
	error("transition label can't be edited\n");
	return Subject::WRONG_NAME;
}

Subject::NameErrType Transition::SetEvent(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double event strings between same pair of nodes.
	List<Subject *> edges;
	if (*s != "" && *s != event) {
		GetGraph()->GetEdges(&edges, GetSubject1(), 
					GetSubject2(), Code::TRANSITION);
		for (edges.first(); !edges.done(); edges.next()) {
			Transition *t = (Transition *)edges.cur();
			if (t != this && *t->GetEvent() == *s)
				return Subject::DOUBLE_EDGE;
		}
	}
	event = *s;
	return Subject::OK;
}

Subject::NameErrType Transition::SetAction(const string *s, unsigned n, bool update) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double actions.
	if (HasAction(s)) {
		if (n >= actions->count() || *(*actions)[n] != *s || !update)
			return Subject::HAS_ACTION;
	}
	StringList::Insert(actions, s, n, update);
	return Subject::OK;
}

const string *Transition::GetAction(unsigned n) {
	if (n < actions->count()) {
		return (*actions)[n];
	}
	return 0;
}

bool Transition::HasAction(const string *s) {
	for (actions->first(); !actions->done(); actions->next()) {
		string *at = actions->cur();
		if (*at == *s)
			return True;
	}
	return False;
}

void Transition::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ Event " << '"' << event << '"' << " }\n";

	unsigned num = actions->count();
	(*ofile) << "\t{ Actions " << num << " }\n";
	for (unsigned i=0; i<num; i++) 
		(*ofile) << "\t{ Action " << '"' 
			<< *(*actions)[i] << '"' << " }\n";
}

bool Transition::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
	if (!ifile->ReadStringAttribute("Event", &event))
		return False;
	string val;
	if (!ifile->ReadAttribute("Actions", &val))
		return False;
	unsigned numItems = val.toint();
	for (unsigned i=0; i<numItems; i++) {
		string *a = new string;
		if (!ifile->ReadStringAttribute("Action", a)) {
			delete a;
			return False;
		}
		actions->add(a);
	}
	return True;
}
