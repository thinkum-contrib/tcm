////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996-2000, Vrije Universiteit Amsterdam and University of Twente
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "inputfile.h"
#include "outputfile.h"
#include "grafport.h"
#include <math.h>
#include "binaryrelationship.h"
#include "c2r2line.h"
#include "erviewer.h"
#include "updatereaddirectioncmd.h"

C2R2Line::C2R2Line(ShapeView *v, Grafport *g, GShape *node1, GShape *node2, 
		List<Point *> *aline, bool Curved): 
			T4Line(v, g, node1, node2, aline, Curved) {
	InitTextShapes();
}

C2R2Line::C2R2Line(ShapeView *v, Grafport *g, GShape *node1, GShape *node2, 
		bool Curved): T4Line(v, g, node1, node2, Curved) {
	InitTextShapes();
}

void C2R2Line::InitTextShapes() {
	GetTextShape1()->SetDescription("Cardinality Constraint");
	GetTextShape2()->SetDescription("Cardinality Constraint");
	GetTextShape3()->SetDescription("Role Name");
	GetTextShape4()->SetDescription("Role Name");
	GetTextShape1()->SetOneLine(True);
	GetTextShape2()->SetOneLine(True);
	SetNameDirection(ReadDirection::NONE);
}

bool C2R2Line::SetAssocSubject(AssocList *al) {
	if (!T4Line::SetAssocSubject(al))
		return False;
	int classType = GetSubject()->GetClassType();
	if (check(GetSubject() && 
	    (classType==Code::BINARY_RELATIONSHIP ||
	     classType==Code::SSD_BINARY_ASSOCIATION_EDGE ||
	     classType==Code::UCD_BINARY_ASSOCIATION_EDGE ||
	     classType==Code::SSD_AGGREGATION_EDGE ||
	     classType==Code::SSD_COMPOSITION_EDGE)))
		return True;
	SetSubject(0);
	return False;
}

void C2R2Line::SetTextShape() {
	T4Line::SetTextShape();
	int classType = GetSubject()->GetClassType();
	if (check(GetSubject() && 
	    (classType==Code::BINARY_RELATIONSHIP ||
	     classType==Code::SSD_BINARY_ASSOCIATION_EDGE ||
	     classType==Code::UCD_BINARY_ASSOCIATION_EDGE ||
	     classType==Code::SSD_AGGREGATION_EDGE ||
	     classType==Code::SSD_COMPOSITION_EDGE))) {
		GetTextShape1()->SetString(
			((BinaryRelationship *)GetSubject())->GetConstraint1());
		GetTextShape2()->SetString(
			((BinaryRelationship *)GetSubject())->GetConstraint2());
		GetTextShape3()->SetString(((BinaryRelationship *)GetSubject())->
				GetRoleName1());
		GetTextShape4()->SetString(((BinaryRelationship *)GetSubject())->
				GetRoleName2());
	}
}

TextShape *C2R2Line::ChooseTextShape(int x, int y) {
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
	return T4Line::ChooseTextShape(x, y);
}

TextShape *C2R2Line::HitTextShape(int x, int y) {
	Rectangle rect2(GetName()->GetRightMost(), 
			GetName()->GetTopMost(),
			16,
			GetName()->GetHeight());
	if (GetNameDirection() != ReadDirection::NONE && rect2.Inside(x, y)) {
		return GetName();
	}
	return T4Line::HitTextShape(x, y);
}

void C2R2Line::DrawShape() {
	T4Line::DrawShape();
	DrawDirection();
}
	
void C2R2Line::WriteMembers(OutputFile *ofile) {
	T4Line::WriteMembers(ofile);
	string s;
	ReadDirection::Type2String(GetNameDirection(), &s);
	(*ofile) << "\t{ NameDirection " << s << " }\n";
}

bool C2R2Line::ReadMembers(InputFile *ifile, double format) {
	if (!T4Line::ReadMembers(ifile, format))
		return False;
        if (format >= 1.31) {
			string val;
			if (!ifile->ReadAttribute("NameDirection", &val))
				return False;
			UpdateNameDirection(ReadDirection::String2Type(&val));
		}
        else
			SetNameDirection(ReadDirection::NONE);
	return True;
}

