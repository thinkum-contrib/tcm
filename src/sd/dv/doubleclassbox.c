////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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

#include "doubleclassbox.h"
#include "stringlistnode.h"

const int DoubleClassBox::DOUBLECLASSBOX_WIDTH = 76;
const int DoubleClassBox::DOUBLECLASSBOX_HEIGHT = 46;

DoubleClassBox::DoubleClassBox(ShapeView *v, Grafport *g, int x, int y, 
		int w, int h): DoubleBox(v, g, x, y, w, h) {
	labelDescription = "Attribute";
	SetSeparatorLineStyle(LineStyle::SOLID);
}

DoubleClassBox::DoubleClassBox(const Box &s): DoubleBox(s) {
	labelDescription = "Attribute";
	SetSeparatorLineStyle(LineStyle::SOLID);
	SetTextShape();
	AdjustSizes(GetName()->GetString());
}

bool DoubleClassBox::SetAssocSubject(AssocList *al) {
	if (!DoubleBox::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
	    (GetSubject()->GetClassType()==Code::CLASS_NODE ||
	    GetSubject()->GetClassType()==Code::SSD_CLASS_NODE || 
	    GetSubject()->GetClassType()==Code::SSD_OBJECT_NODE))) 
		return True;
	SetSubject(0);
	return False;
}

void DoubleClassBox::SetTextShape() {
	DoubleBox::SetTextShape();
	GetLabels()->clear();
	if (!check(GetSubject() && 
	    (GetSubject()->GetClassType() == Code::CLASS_NODE ||
	     GetSubject()->GetClassType() == Code::SSD_CLASS_NODE ||
	     GetSubject()->GetClassType() == Code::SSD_OBJECT_NODE)))
		return;
	// create the attribute labels.
	StringListNode *sln = (StringListNode *)GetSubject();
	unsigned numItems = sln->NrStrings();
	for (unsigned i=0; i<numItems; i++) {
		TextShape *at = new TextShape(
				GetView(), GetGrafport(), this);
		at->SetSequence(i);
		at->SetAlignment(TextAlign::LEFT);
		at->SetDescription(&labelDescription);
		at->SetString(sln->GetString(i));
		at->SetParent(this);
		at->SetFont(GetName()->GetFont());
		at->SetColor(GetName()->GetColor());
		GetLabels()->add(at);
	}
//	CalcPositionLabels();
}
