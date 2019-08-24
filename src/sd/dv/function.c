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
#include "function.h"
#include "erparse.h"
#include "ergraph.h"
#include <strings.h>
#if defined(LINUX)
#include <string.h>
#endif

Function::Function(ERGraph *g, Subject *n1, Subject *n2): C1Edge(g, n1, n2) { }
 
bool Function::SetConstraint(const string *s) {
	// empty constraint is allowed
	if (*s == "" || ParseCardConstraint(s)) {
		string cons = ::cardconstraint_constraint;
		C1Edge::SetConstraint(&cons);
		// is 1-1 function then it is undirected (symmetric).
		if (cons == "1")
			SetDirected(False);
		return True;
	}
	else
		return False;
}

Subject::NameErrType Function::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (*s == "is_a")
		return Subject::WRONG_NAME;
	else if (*s != *GetName() && *s != "") {
		if (GetGraph()->CountEdges(GetSubject1(), GetSubject2(), 
					   s, Code::FUNCTION) + 
		    GetGraph()->CountEdges(GetSubject1(), GetSubject2(), 
					   s, Code::COMPONENT_FUNCTION) > 0)
			return Subject::DOUBLE_EDGE;
	}
	return C1Edge::SetName(s);
}

bool Function::ParseCardConstraint(const string *str) {
        YY_BUFFER_STATE y = ::cardconstraint_scan_string(str->getstr());
        strcpy(::cardconstraint_constraint, "");
        bool b = !cardconstraintparse();
        cardconstraint_delete_buffer(y);
        return b;
}

