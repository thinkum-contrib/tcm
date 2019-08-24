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
#include "celltext.h"
#include "cell.h"
#include "grafport.h"
#include "inputfile.h"
#include "outputfile.h"

CellText::CellText(Grafport *g, XFont *ft, Cell *p): SimpleLabel(g, ft) {
	parent = p;
	underlined = False;
}

CellText::CellText(const CellText &t): SimpleLabel(t) {
	parent = 0;
	underlined = False;
}

void CellText::Draw() {
        DrawAligned(TextAlign::CENTER);
}

void CellText::DrawAligned(TextAlign::Type a) {
	if (parent && !parent->IsVisible())
		return;
	if (GetText()->length() > 0) {
		GetGrafport()->SetFont(GetFont());
		Point tl = *GetTopLeft();
		Point pos = *GetPosition();
		if (a == TextAlign::LEFT)
			GetGrafport()->DrawStringsLeft(tl.x, tl.y, 
							GetText(), IsUnderlined());
		else if (a == TextAlign::RIGHT)
			GetGrafport()->DrawStringsRight(tl.x+GetWidth(), tl.y, 
							GetText(), IsUnderlined());
		else
			GetGrafport()->DrawStringsCentered(pos.x, pos.y, 
							GetText(), IsUnderlined());
	}
}

void CellText::UndrawAligned(TextAlign::Type a) {
	DrawAligned(a);
}

void CellText::UpdatePosition(const Point *pt) {
	if (parent) {
		if (parent->IsVisible())
			UndrawAligned(parent->GetColumnAlignment());
	}
	else
		UndrawAligned(TextAlign::CENTER);
	SetPosition(pt);
	if (parent) {
		if (parent->IsVisible())
			DrawAligned(parent->GetColumnAlignment());
	}
	else
		DrawAligned(TextAlign::CENTER);
}

void CellText::UpdateText(const string *s) {
	if (parent)
		UndrawAligned(parent->GetColumnAlignment());
	else
		UndrawAligned(TextAlign::CENTER);
	SetText(s);
	if (parent)
		DrawAligned(parent->GetColumnAlignment());
	else
		DrawAligned(TextAlign::CENTER);
}

void CellText::UpdateFont(XFont *ft) {
	if (parent)
		UndrawAligned(parent->GetColumnAlignment());
	else
		UndrawAligned(TextAlign::CENTER);
	SetFont(ft);
	if (parent)
		DrawAligned(parent->GetColumnAlignment());
	else
		DrawAligned(TextAlign::CENTER);
}

void CellText::Write(OutputFile *ofile) {
	string fontString;
	GetFont()->GetXLFD(&fontString);
	(*ofile) << "\t{ Text \"" << *GetText() << "\"}\n";
	(*ofile) << "\t{ Font \"" << fontString << "\"}\n";
}

bool CellText::Read(InputFile *ifile, double format) {
	string s;
	if (!ifile->ReadStringAttribute("Text", &s))
		return False;
	if (s != "")
		SetText(&s);
	if (format >= 1.09) {
		if (!ifile->ReadStringAttribute("Font", &s))
			return False;
		parent->SetXLFD(s.getstr());
	}
	return True;
}

 
void CellText::UpdateUnderlined(bool b) {
        if (underlined != b) {
                Undraw();
                underlined = b;
                Draw();
        }
}
