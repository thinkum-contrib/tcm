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
#include "tripleclassbox.h"
#include "stringlistnode2.h"

const int TripleClassBox::TRIPLECLASSBOX_WIDTH = 76;
const int TripleClassBox::TRIPLECLASSBOX_HEIGHT = 66;

TripleClassBox::TripleClassBox(ShapeView *v, Grafport *g, 
	int x, int y, int w, int h): TripleBox(v, g, x, y, w, h) {
	SetSeparatorLineStyle(LineStyle::SOLID);
	SetSeparator2LineStyle(LineStyle::SOLID);
	labelDescription = "Attribute";
	label2Description = "Operation";
}

TripleClassBox::TripleClassBox(const Box &s): TripleBox(s) {
	labelDescription = "Attribute";
	label2Description = "Operation";
	SetSeparatorLineStyle(LineStyle::SOLID);
	SetSeparator2LineStyle(LineStyle::SOLID);
	SetTextShape();
	AdjustSizes(GetName()->GetString());
}

TripleClassBox::TripleClassBox(const TripleBox &s): TripleBox(s) {
	labelDescription = "Attribute";
	label2Description = "Operation";
	SetTextShape();
	AdjustSizes(GetName()->GetString());
}

bool TripleClassBox::SetAssocSubject(AssocList *al) {
	if (!TripleBox::SetAssocSubject(al))
		return False;
	if (check(GetSubject() &&
	    (GetSubject()->GetClassType()==Code::CLASS_NODE ||
	     GetSubject()->GetClassType()==Code::SSD_CLASS_NODE)))
		return True;
	SetSubject(0);
	return False;
}

void TripleClassBox::SetTextShape() {
	TripleBox::SetTextShape();
	GetLabels()->clear();
	GetLabels2()->clear();
	if (!check(GetSubject()) || 
	    (GetSubject()->GetClassType() != Code::CLASS_NODE &&
	     GetSubject()->GetClassType() != Code::SSD_CLASS_NODE))
		return;
	StringListNode2 *node = (StringListNode2 *)GetSubject();
	unsigned numItems = node->NrStrings();
	for (unsigned i=0; i<numItems; i++) {
		TextShape *et = new TextShape(GetView(), GetGrafport(), this);
		et->SetSequence(i);
		et->SetAlignment(TextAlign::LEFT);
		et->SetDescription(&labelDescription);
		et->SetString(node->GetString(i));
		et->SetParent(this);
		et->SetFont(GetName()->GetFont());
		et->SetColor(GetName()->GetColor());
		GetLabels()->add(et);
	}
	numItems = node->NrStrings2();
	for (unsigned j=0; j<numItems; j++) {
		TextShape *et = new TextShape(GetView(), GetGrafport(), this);
		et->SetSequence(j);
		et->SetAlignment(TextAlign::LEFT);
		et->SetDescription(&label2Description);
		et->SetString(node->GetString2(j));
		et->SetParent(this);
		et->SetFont(GetName()->GetFont());
		et->SetColor(GetName()->GetColor());
		GetLabels2()->add(et);
	}
//	CalcPositionLabels();
}
