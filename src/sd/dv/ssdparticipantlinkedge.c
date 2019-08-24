////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam
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
#include "ssdgraph.h"
#include "ssdparticipantlinkedge.h"

SSDParticipantLinkEdge::SSDParticipantLinkEdge(
	SSDGraph *g, Subject *n1, Subject *n2): C1Edge(g, n1, n2) {
	roleName = "";
	SetDirected(True);
}

SSDParticipantLinkEdge::SSDParticipantLinkEdge(
		const SSDParticipantLinkEdge &bin): C1Edge(bin) {
	roleName = bin.roleName;
}

bool SSDParticipantLinkEdge::SetConstraint(const string *s) {
	// here parsing
	C1Edge::SetConstraint(s);
	return True;
}

bool SSDParticipantLinkEdge::SetRoleName(const string *s) {
	// here parsing
	roleName = *s;
	return True;
}

void SSDParticipantLinkEdge::WriteMembers(OutputFile *ofile) {
	C1Edge::WriteMembers(ofile);
	(*ofile) << "\t{ RoleName " << '"' << roleName << '"' << " }\n";
}

bool SSDParticipantLinkEdge::ReadMembers(InputFile *ifile, double format) {
	if (!C1Edge::ReadMembers(ifile, format))
		return False;
	if (format <= 1.29) {	// for upward compatibility
		if (!ifile->ReadAttribute("RoleName", &roleName))
			return False;
	} else {
		if (!ifile->ReadStringAttribute("RoleName", &roleName))
			return False;
	}
	return True;
}
