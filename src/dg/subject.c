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
#include "subject.h"
#include "graph.h"
#include "node.h"
#include "assoclist.h"
#include "inputfile.h"
#include "outputfile.h"
#include "util.h"

Subject::Subject(Graph *g): Thing() {
	graph = g;
	name = "";
	annotation = "";
	parent = 0;
}

Subject::Subject(HyperGraph *g): Thing() {
        hgraph = g;
        name = "";
        annotation = "";
        parent = 0;
}


bool Subject::SetReferences(AssocList *al) {
	// set parent reference (parent is 0 or an existing node).
	Assoc *find, *assoc;
	find = new Assoc(parent);
	assoc = al->Get(find);
	if (assoc)
		parent = (Node *)assoc->copy;
	else
		parent = 0;
	delete find;
	if (parent) {
		// when a parent is found it should be a node.
		if (parent->IsSubject() && !parent->IsEdge())
			return True;
		else {
			error("subject %d has no exising parent node %d\n",
				GetId(), parent->GetId());
			parent = 0;
			return False;
		}
	}
	return True;
}
 
void Subject::WriteMembers(OutputFile *ofile) {
	(*ofile) << "\t{ Name " << '"' << name << '"' << " }\n";
	(*ofile) << "\t{ Annotation " << '"' << annotation << '"' << " }\n";
	(*ofile) << "\t{ Parent " << (parent?parent->GetId():0) << " }\n";
}

bool Subject::ReadMembers(InputFile *ifile, double format) {
	if (!ifile->ReadStringAttribute("Name", &name))
		return False;
	if (format >= 1.13) {
		if (!ifile->ReadStringAttribute("Annotation", &annotation))
			return False;
		string val;
		if (!ifile->ReadAttribute("Parent", &val))
			return False;
		unsigned long value = val.toulong();
		parent = (Node *)value;
	}
	return True;
}

bool Subject::CheckReferences() {
	// this should be part of the graph.
	if (!check(InGraph()))
		return False;
	// if parent exists, it should exist as a graph node.
	if (parent) 
		return parent->InGraph();
	return True;
}
