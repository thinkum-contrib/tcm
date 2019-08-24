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
#include "ssdrcline.h"
#include "ssdparticipantlinkedge.h"

SSDRCLine::SSDRCLine(ShapeView *v, Grafport *g, GShape *n1, 
		GShape *n2, List<Point *> *aline, bool Curved): 
			T2Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
	CalcPositionTextShapes();
}

SSDRCLine::SSDRCLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): T2Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

void SSDRCLine::InitTextShapes() {
	GetTextShape1()->SetDescription("Cardinality Constraint");
	GetTextShape2()->SetDescription("Role Name");
	GetTextShape1()->SetOneLine(True);
	SetT1Position(BR);
	SetT2Position(TR);
}

bool SSDRCLine::SetAssocSubject(AssocList *al) {
	if (!T2Line::SetAssocSubject(al))
		return False;
	if (check(GetSubject() &&
	    GetSubject()->GetClassType()==Code::SSD_PARTICIPANT_LINK_EDGE)) 
		return True;
	SetSubject(0);
	return False;
}

void SSDRCLine::SetTextShape() {
	T2Line::SetTextShape();
	if (check(GetSubject() && 
	    GetSubject()->GetClassType()==Code::SSD_PARTICIPANT_LINK_EDGE)) {
		GetTextShape1()->SetString(
			((SSDParticipantLinkEdge *)GetSubject())->GetConstraint());
		GetTextShape2()->SetString(
			((SSDParticipantLinkEdge *)GetSubject())->GetRoleName());
	}
}
