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
#include "grafport.h"
#include "ssdobjectnode.h"
#include "ssddoubleobjectbox.h"

SSDDoubleObjectBox::SSDDoubleObjectBox(ShapeView *v, Grafport *g,
		int x, int y, int w, int h): DoubleClassBox(v, g, x, y, w, h) {
        GetName()->SetUnderlined(True);
}

SSDDoubleObjectBox::SSDDoubleObjectBox(const Box &s): DoubleClassBox(s) {
        GetName()->SetUnderlined(True);
	SetTextShape();
}

bool SSDDoubleObjectBox::SetAssocSubject(AssocList *al) {
	if (!DoubleBox::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
	    (GetSubject()->GetClassType()==Code::SSD_OBJECT_NODE))) 
		return True;
	SetSubject(0);
	return False;
}

void SSDDoubleObjectBox::SetTextShape() {
	DoubleBox::SetTextShape();
	GetLabels()->clear();
	// create the attribute labels.
	if (!check(GetSubject() && 
	    (GetSubject()->GetClassType() == Code::SSD_OBJECT_NODE)))
		return;
	SSDObjectNode *obj = (SSDObjectNode *)GetSubject();
	unsigned numItems = obj->NrStrings();
	for (unsigned i=0; i<numItems; i++) {
		TextShape *at = new TextShape(
				GetView(), GetGrafport(), this);
		at->SetSequence(i);
		at->SetAlignment(TextAlign::LEFT);
		at->SetDescription(&labelDescription);
		at->SetString(obj->GetString(i));
		at->SetParent(this);
		at->SetFont(GetName()->GetFont());
		at->SetColor(GetName()->GetColor());
		GetLabels()->add(at);
	}
//	CalcPositionLabels();
}

void SSDDoubleObjectBox::DrawTextShapes() {
	string oldBackground; 
	Grafport *g = GetGrafport();
	if (GetFillStyle() != FillStyle::UNFILLED) {
		oldBackground = *g->GetBackgroundColor();
		g->SetBackgroundColor(GetFillColor());
	}
	NodeShape::DrawTextShapes();
	int textHeight = GetName()->GetFontHeight();
	int nameHeight = max(GetName()->GetString()->lines(), 2) * textHeight;
	if (nameHeight < GetHeight()) {
                g->SetLineStyle(GetSeparatorLineStyle());
		g->DrawLine(GetLeftMost()+1, GetTopMost()+nameHeight+1, 
			GetRightMost()-1, 
			GetTopMost()+nameHeight+1);
		g->SetLineStyle(GetLineStyle());
	}
	int i = nameHeight;
	for (GetLabels()->first(); !GetLabels()->done(); GetLabels()->next()) {
		i += textHeight;
		if (i < GetHeight())
			GetLabels()->cur()->Draw();
	}
	if (GetFillStyle() != FillStyle::UNFILLED)
		g->SetBackgroundColor(&oldBackground);
}
