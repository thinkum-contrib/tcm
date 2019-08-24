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
#include "binaryrelationship.h"
#include "inputfile.h"
#include "outputfile.h"
#include "erparse.h"
#include "graph.h"
#include <strings.h>
#if defined(LINUX)
#include <string.h>
#endif

BinaryRelationship::BinaryRelationship(Graph *g, Subject *n1, Subject *n2): 
		Edge(g, n1, n2) {
	constraint1 = "";
	constraint2 = "";
	roleName1 = "";
	roleName2 = "";
	SetDirected(False);
}

bool BinaryRelationship::SetConstraint1(const string *s) {
	return SetConstraint(&constraint1, s);
}

bool BinaryRelationship::SetConstraint2(const string *s) {
	return SetConstraint(&constraint2, s);
}

bool BinaryRelationship::SetRoleName1(const string *s) {
	return SetRoleName(&roleName1, s);
}

bool BinaryRelationship::SetRoleName2(const string *s) {
	return SetRoleName(&roleName2, s);
}

bool BinaryRelationship::SetRoleName(string *role, const string *nm) {
	if (*nm != "" && nm->letters() == 0)
		return False;
	*role = *nm;
	return True;
}

bool BinaryRelationship::SetConstraint(string *cons, const string *nm) {
	// empty constraint is allowed
	string t = *nm;
	if (*nm == "" || ParseCardConstraint(&t)) {
		*cons = ::cardconstraint_constraint;
		return True;
	}
	else
		return False;
}

void BinaryRelationship::WriteMembers(OutputFile *ofile) {
	Edge::WriteMembers(ofile);
	(*ofile) << "\t{ Constraint1 " << '"' << constraint1 << '"' << " }\n";
	(*ofile) << "\t{ Constraint2 " << '"' << constraint2 << '"' << " }\n";
	(*ofile) << "\t{ RoleName1 " << '"' << roleName1 << '"' << " }\n";
	(*ofile) << "\t{ RoleName2 " << '"' << roleName2 << '"' << " }\n";
}

bool BinaryRelationship::ReadMembers(InputFile *ifile, double format) {
	if (!Edge::ReadMembers(ifile, format))
		return False;
	if (!ifile->ReadStringAttribute("Constraint1", &constraint1)) 
		return False;
	if (!ifile->ReadStringAttribute("Constraint2", &constraint2))
		return False;
	if (!ifile->ReadStringAttribute("RoleName1", &roleName1))
		return False;
	if (!ifile->ReadStringAttribute("RoleName2", &roleName2))
		return False;
	return True;
}

Subject::NameErrType BinaryRelationship::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s == "is_a")
		return Subject::WRONG_NAME;
	else if (*s != *GetName() && *s != "") { 
		if (GetGraph()->CountEdges(GetSubject1(), GetSubject2(), 
					   s, Code::BINARY_RELATIONSHIP) > 0)
			return Subject::DOUBLE_EDGE;
	}
	return Edge::SetName(s);
}

bool BinaryRelationship::ParseCardConstraint(const string *str) {
        YY_BUFFER_STATE y = ::cardconstraint_scan_string(str->getstr());
        strcpy(::cardconstraint_constraint, "");
        bool b = !cardconstraintparse();
        cardconstraint_delete_buffer(y);
        return b;
}
