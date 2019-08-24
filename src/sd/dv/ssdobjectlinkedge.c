//------------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "ssdobjectlinkedge.h"
#include "inputfile.h"
#include "outputfile.h"
#include "ssdgraph.h"
#include "ssddiagram.h"
#include "ssdviewer.h"

SSDObjectLinkEdge::SSDObjectLinkEdge(SSDGraph *g, Subject *n1, Subject *n2): 
		Edge(g, n1, n2) {
	roleName1 = "";
	roleName2 = "";
	SetDirected(False);
}

bool SSDObjectLinkEdge::SetRoleName1(const string *s) {
	return SetRoleName(&roleName1, s);
}

bool SSDObjectLinkEdge::SetRoleName2(const string *s) {
	return SetRoleName(&roleName2, s);
}

bool SSDObjectLinkEdge::SetRoleName(string *role, const string *nm) {
	if (*nm != "" && nm->letters() == 0)
		return False;
	*role = *nm;
	return True;
}

void SSDObjectLinkEdge::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ RoleName1 " << '"' << roleName1 << '"' << " }\n";
	(*ofile) << "\t{ RoleName2 " << '"' << roleName2 << '"' << " }\n";
}

bool SSDObjectLinkEdge::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
	if (!ifile->ReadStringAttribute("RoleName1", &roleName1))
		return False;
	if (!ifile->ReadStringAttribute("RoleName2", &roleName2))
		return False;
	return True;
}

Subject::NameErrType SSDObjectLinkEdge::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s == "is_a")
		return Subject::WRONG_NAME;

	return Edge::SetName(s);
}
