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
#include "endc1arrow.h"
#include "c1edge.h"

EndC1Arrow::EndC1Arrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
			T1Line(v, g, n1, n2, aline, Curved) {
	Initialize();
	CalcPositionTextShapes();
}

EndC1Arrow::EndC1Arrow(
		ShapeView *v, Grafport *g, GShape *n1, GShape *n2, bool Curved) 
		: T1Line(v, g, n1, n2, Curved) {
	Initialize();
}

void EndC1Arrow::Initialize() {
	SetFixedName(True);
	GetTextShape1()->SetOneLine(True);
	GetTextShape1()->SetDescription("Cardinality Constraint");
	SetT1Position(BR);
	SetEnd2(LineEnd::FILLED_ARROW);
}

bool EndC1Arrow::SetAssocSubject(AssocList *al) {
	if (!T1Line::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
		  GetSubject()->GetClassType()==Code::CONNECTION_END))
		return True;
	SetSubject(0);
	return False;
}

void EndC1Arrow::SetTextShape() {
	T1Line::SetTextShape();
	if (check(GetSubject()))
		GetTextShape1()->SetString(((C1Edge *)GetSubject())->
				GetConstraint());
}
