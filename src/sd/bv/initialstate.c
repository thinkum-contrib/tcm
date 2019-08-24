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
#include "initialstate.h"
#include "stgraph.h"
#include "lstring.h"
#include "stringlist.h"
#include "inputfile.h"
#include "outputfile.h"

InitialState::InitialState(STGraph *g): State(g) {
	controlProcess = "";
	actions = new List<string *>;
}

InitialState::InitialState(const InitialState &s): State(s) {
	actions = new List<string *>;
	for (s.actions->first(); !s.actions->done(); s.actions->next()) {
		string *a = s.actions->cur();
		string *b = new string(*a);
		actions->add(b);
	}
	controlProcess = s.controlProcess;
}

InitialState::~InitialState() {
	actions->clear();
	delete actions;
}

Subject::NameErrType InitialState::SetAction(const string *s, unsigned n, bool update) {
	if (*s != "" && s->letters()==0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double actions.
	if (HasAction(s)) {
		 if (n >= actions->count() || *(*actions)[n] != *s || !update)
			return Subject::HAS_ACTION;
	}
	StringList::Insert(actions, s, n, update);
	return Subject::OK;
}

const string *InitialState::GetAction(unsigned n) {
	if (n < actions->count())
		return (*actions)[n];
	return 0;
}

bool InitialState::HasAction(const string *s) {
	for (actions->first(); !actions->done(); actions->next()) {
		string *at = actions->cur();
		if (*at == *s)
			return True;
	}
	return False;
}
 
bool InitialState::ReadMembers(InputFile *ifile, double format) {
	if (!State::ReadMembers(ifile, format))
		return False;
	// read control process name.
	if (format >= 1.13) {
		if (!ifile->ReadStringAttribute("ControlProcess", &controlProcess))
			return False;
	}
	// read actions
	string val;
	if (!ifile->ReadAttribute("Actions", &val))
		return False;
	unsigned numItems = val.toint();
	for (unsigned i=0; i<numItems; i++) {
		string *at = new string;
		if (!ifile->ReadStringAttribute("Action", at)) {
			delete at;
			return False;
		}
		actions->add(at);
	}
	return True;
}

void InitialState::WriteMembers(OutputFile *ofile) {
	State::WriteMembers(ofile);
	// write name of control process.
	(*ofile) << "\t{ ControlProcess " << '"' << controlProcess << '"' << " }\n";
	// write actions
	unsigned numItems = actions->count();
	(*ofile) << "\t{ Actions " << numItems << " }\n";
	for (unsigned i=0; i<numItems; i++) {
		(*ofile) << "\t{ Action " << '"' 
			<< *(*actions)[i] << '"' << " } \n";
	}
}
