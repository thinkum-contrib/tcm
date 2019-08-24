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
#include "c1edge.h"

C1Edge::C1Edge(Graph *g, Subject *n1, Subject *n2): Edge(g, n1, n2) {
	constraint = "";
	SetDirected(True);
}

bool C1Edge::SetConstraint(const string *s) {
	constraint = *s;
	return True;
}

void C1Edge::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ Constraint " << '"' << constraint << '"' << " }\n";
}

bool C1Edge::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
	if (!ifile->ReadStringAttribute("Constraint", &constraint))
		return False;
	return True;
}
