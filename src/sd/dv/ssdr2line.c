//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "inputfile.h"
#include "outputfile.h"
#include "grafport.h"
#include "ssdobjectlinkedge.h"
#include "ssdr2line.h"
#include "lstring.h"
#include <math.h>
#include "erviewer.h"
#include "updatereaddirectioncmd.h"

SSDR2Line::SSDR2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
			T2Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
	CalcPositionTextShapes();
}

SSDR2Line::SSDR2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): T2Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

void SSDR2Line::InitTextShapes() {
	// names are always underlined.
	GetName()->SetUnderlined(True);
	GetTextShape1()->SetDescription("Role Name");
	GetTextShape2()->SetDescription("Role Name");
	SetT1Position(TL);
	SetT2Position(TR);
}

bool SSDR2Line::SetAssocSubject(AssocList *al) {
	if (!T2Line::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
	    GetSubject()->GetClassType()==Code::SSD_OBJECT_LINK_EDGE)) 
		return True;
	SetSubject(0);
	return False;
}

void SSDR2Line::SetTextShape() {
	T2Line::SetTextShape();
	if (check(GetSubject() && 
	    GetSubject()->GetClassType()==Code::SSD_OBJECT_LINK_EDGE)) {
		GetTextShape1()->SetString(((SSDObjectLinkEdge *)GetSubject())->
				GetRoleName1());
		GetTextShape2()->SetString(((SSDObjectLinkEdge *)GetSubject())->
				GetRoleName2());
	}
}

TextShape *SSDR2Line::ChooseTextShape(int x, int y) {
	Rectangle rect2(GetName()->GetRightMost(), 
			GetName()->GetTopMost(),
			16,
			GetName()->GetHeight());
	if (rect2.Inside(x, y)) {
		if (GetName()->GetStringWidth() > 0) {	// toggle OK
			int newDir = ((int) GetNameDirection() + 1) % 3;
			ERViewer *erviewer = dynamic_cast<ERViewer *>(GetViewer());
			if (erviewer)
				erviewer->UpdateReadDirection((ReadDirection::Type) newDir);
		}	//toggle OK
		return GetName();
	}
	return T2Line::ChooseTextShape(x, y);
}

TextShape *SSDR2Line::HitTextShape(int x, int y) {
	Rectangle rect2(GetName()->GetRightMost(), 
			GetName()->GetTopMost(),
			16,
			GetName()->GetHeight());
	if (GetNameDirection() != ReadDirection::NONE && rect2.Inside(x, y)) {
		return GetName();
	}
	return T2Line::HitTextShape(x, y);
}

void SSDR2Line::DrawShape() {
	T2Line::DrawShape();
	DrawDirection();
}

void SSDR2Line::WriteMembers(OutputFile *ofile) {
	T2Line::WriteMembers(ofile);
	string s;
	ReadDirection::Type2String(GetNameDirection(), &s);
	(*ofile) << "\t{ NameDirection " << s << " }\n";
}

bool SSDR2Line::ReadMembers(InputFile *ifile, double format) {
	if (!T2Line::ReadMembers(ifile, format))
		return False;
        if (format >= 1.31) {
                string val;
		if (!ifile->ReadAttribute("NameDirection", &val))
			return False;
		SetNameDirection(ReadDirection::String2Type(&val));
	}
        else 
                SetNameDirection(ReadDirection::NONE);
	return True;
}
