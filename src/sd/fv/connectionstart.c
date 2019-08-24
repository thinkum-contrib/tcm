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
#include "connectionstart.h"
#include "sngraph.h"
#include "erparse.h"
#include <strings.h>
#if defined(LINUX)
#include <string.h>
#endif

ConnectionStart::ConnectionStart(SNGraph *g, Subject *n1, Subject *n2): 
		C1Edge(g, n1, n2) { }

bool ConnectionStart::SetConstraint(const string *s) {
	// empty constraint is allowed
	if (*s == "" || ParseCardConstraint(s)) {
		string cons = ::cardconstraint_constraint;
                return C1Edge::SetConstraint(&cons);
	}
	else
		return False;
}

bool ConnectionStart::ParseCardConstraint(const string *str) {
        YY_BUFFER_STATE y = ::cardconstraint_scan_string(str->getstr());
        strcpy(::cardconstraint_constraint, "");
        bool b = !cardconstraintparse();
        cardconstraint_delete_buffer(y);
        return b;
}
