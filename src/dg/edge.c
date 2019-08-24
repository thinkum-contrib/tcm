////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "inputfile.h"
#include "outputfile.h"
#include "util.h"
#include "assoclist.h"
#include "graph.h"
#include "edge.h"

Edge::Edge(Graph *g, Subject *n1, Subject *n2): Subject(g) {
	subject1 = n1; 
	subject2 = n2;
	directed = False;
}

Edge::~Edge() { }

bool Edge::InGraph() const {
	return GetGraph()->HasEdge((Edge *)this);
}
 
void Edge::WriteMembers(OutputFile *ofile) {
	Subject::WriteMembers(ofile);
	(*ofile) << "\t{ Subject1 " << (check(subject1)? 
		subject1->GetId():0) << " }\n";
	(*ofile) << "\t{ Subject2 " << (check(subject2)? 
		subject2->GetId():0) << " }\n";
}

bool Edge::ReadMembers(InputFile *ifile, double format) {
	if (!Subject::ReadMembers(ifile, format))
		return False;
	string val;
	if (format <= 1.24) {
		if (!ifile->ReadAttribute("Node1", &val))
			return False;
		subject1 = (Subject *)(val.toulong());
		if (!ifile->ReadAttribute("Node2", &val))
			return False;
	}
	else {
		if (!ifile->ReadAttribute("Subject1", &val))
			return False;
		subject1 = (Subject *)(val.toulong());
		if (!ifile->ReadAttribute("Subject2", &val))
			return False;
	}
	subject2 = (Subject *)(val.toulong());
	return True;
}

bool Edge::SetReferences(AssocList *al) {
	if (!Subject::SetReferences(al))
		return False;
	return (SetSubjectReference(al, &subject1, 1) && 
		SetSubjectReference(al, &subject2, 2));
}

bool Edge::SetSubjectReference(AssocList* al, Subject** subject, int which) {
	// find and set subject.
	Assoc *find, *assoc;
	find = new Assoc(*subject);
	assoc = al->Get(find);
	if (check(assoc))
		*subject = (Subject *)assoc->copy;
	else {
		error("edge %ld has no existing Subject%d\n", GetId(), which);
		*subject = 0;
		delete find;
		return False;
	}
	// Check that subject is a real Subject.
	if (!*subject || !(*subject)->IsSubject()) {
		error("edge %ld has a Subject%d which is not a real subject\n",
			GetId(), which);
		*subject = 0;
		delete find;
		return False;
	}
	delete find;
	return True;
}

bool Edge::CheckReferences() {
	if (!Subject::CheckReferences())
		return False;
	return (check(subject1) && check(subject2) &&
		check(subject1->InGraph()) && check(subject2->InGraph()));
}
