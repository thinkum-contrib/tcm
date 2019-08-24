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
#include "dfedge.h"
#include "inputfile.h"
#include "outputfile.h"
#include "assoclist.h"
#include "dfgraph.h"
#include "util.h"

DFEdge::DFEdge(DFGraph *g, Subject *n1, Subject *n2): Edge(g, n1, n2) {
	components = new List<DFEdge *>;
}

DFEdge::DFEdge(const DFEdge &e): Edge(e) {
	components = new List<DFEdge *>(*e.components);
}

DFEdge::~DFEdge() {
	delete components;
}

void DFEdge::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ Components " << components->count() << " }\n";
	for(components->first(); !components->done(); components->next()) {
		DFEdge *e = components->cur();
		(*ofile) << "\t{ Component " << (check(e)?e->GetId():0) << " }\n";
	}
}
 
bool DFEdge::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
	if (format >= 1.13) {
		string val;
		if (!ifile->ReadAttribute("Components", &val))
			return False;
		unsigned numItems = val.toint();
		for (unsigned i=0; i<numItems; i++) {
			if (!ifile->ReadAttribute("Component", &val))
				return False;
			unsigned long v = val.toulong();
			DFEdge *e = (DFEdge *)v;
			components->add(e);
		}
	}
	return True;
}

bool DFEdge::SetReferences(AssocList *al) {
	if (!Edge::SetReferences(al))
		return False;
	// set child references.
	Assoc *find, *assoc;
	// set component references
	for (components->first(); !components->done(); components->next()) {
		find = new Assoc(components->cur());
		assoc = al->Get(find);
		if (check(assoc))
			components->cur() = (DFEdge *)assoc->copy;
		else {
			delete find;
			return False;
		}
		delete find;
	}
	return True;
}

