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
#include "lstring.h"
#include "diagramviewer.h"
#include "ucdsingleclassbox.h"
#include "inputfile.h"
#include "outputfile.h"
#include "subject.h"

const int UCDSingleClassBox::TEXTMARGIN = 4;

UCDSingleClassBox::UCDSingleClassBox(ShapeView *v, Grafport *g,
	double x, double y)
	:Box(v, g, x, y)
{
        stereotypeLabel = new TextShape(v, g, this);
        stereotypeLabel->SetOneLine(True);
        stereotypeLabel->SetDescription("Stereotype");
        string my_stereo = "<<actor>>";
        stereotypeLabel->SetString(&my_stereo);
	SetSize(GetWidth(), RequiredHeight());
}

UCDSingleClassBox::~UCDSingleClassBox() {
	delete stereotypeLabel;
}

UCDSingleClassBox::UCDSingleClassBox(const UCDSingleClassBox &s): Box(s) {
	stereotypeLabel = new TextShape(*s.stereotypeLabel);
	stereotypeLabel->SetParent(this);
	SetSize(s.GetWidth(), s.GetHeight());
}

UCDSingleClassBox::UCDSingleClassBox(const StickMan &s): Box(s) {
        stereotypeLabel = new TextShape(GetView(), GetGrafport(), this);
        stereotypeLabel->SetOneLine(True);
        stereotypeLabel->SetDescription("Stereotype");
        string my_stereo = "<<actor>>";
        stereotypeLabel->SetString(&my_stereo);
	stereotypeLabel->SetParent(this);
	SetSize(s.GetWidth(), RequiredHeight());
}

void UCDSingleClassBox::SetGrafport(Grafport *g) {
	Box::SetGrafport(g);
        stereotypeLabel->SetGrafport(g);
}

void UCDSingleClassBox::SetView(ShapeView *v) {
	Box::SetView(v);
        stereotypeLabel->SetView(v);
}

bool UCDSingleClassBox::SetAssocSubject(AssocList *al) {
        if (!Box::SetAssocSubject(al))
                return False;
        if (check(GetSubject()) && 
		    ((GetSubject()->GetClassType()==Code::UCD_ACTOR_NODE) || //compat.
		     (GetSubject()->GetClassType()==Code::CBD_ACTOR_NODE)))
                return True;
        SetSubject(0);
        return False;
}
 
//void UCDSingleClassBox::SetSize(int w, int h) {
//        Box::SetSize(w, h);
//	CalcPositionLabels();
//}
 
//void UCDSingleClassBox::SetPosition(const Point *pos, bool snap) {
//        Box::SetPosition(pos, snap);
//	CalcPositionLabels();
//}
 
void UCDSingleClassBox::SetFont(XFont *ft) {
        Box::SetFont(ft);
	stereotypeLabel->SetFont(ft);
//	CalcPositionLabels();
}

void UCDSingleClassBox::SetTextColor(const string *c) {
        Box::SetTextColor(c);
	stereotypeLabel->SetColor(c);
}

void UCDSingleClassBox::DrawTextShapes() {
	Box::DrawTextShapes();
        stereotypeLabel->Draw();
}

void UCDSingleClassBox::AdjustSize() {
        int twd = RequiredWidth();
        int ht = RequiredHeight();
        if (twd > GetWidth() || ht != GetHeight()) {
                int wd = max((twd+2*TEXTMARGIN), GetWidth());
                UpdateSize(wd, ht);
                GetViewer()->ShapePositionUpdate(this);
        }
//	else
//		CalcPositionLabels();
}

void UCDSingleClassBox::CalcPositionLabels() {
	Box::CalcPositionLabels();

        Point pt = *GetPosition();
        int textHeight = GetName()->GetFontHeight();
	int min_firstboxlines = 1;	// <<actor>>
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	int nameHeight = labelLines * textHeight;
	pt.y = GetTopMost() + textHeight/4 + textHeight + nameHeight/2;
        GetName()->SetPosition(&pt);
        // set index label position.
        pt.x = GetName()->GetPosition()->x + GetWidth()*5/12;
        pt.y = GetName()->GetPosition()->y - nameHeight/4;
        GetIndexLabel()->SetPosition(&pt);
	CalcPositionStereotypeLabel();
}

int UCDSingleClassBox::RequiredHeight() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = 1;	// <<actor>>
	int min_firstboxlines = 1;
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        int snHeight = (addLines+labelLines) * textHeight;
        int ht = (snHeight + textHeight);
        return ht;
}

int UCDSingleClassBox::RequiredWidth() {
        int twidth = max(GetName()->GetWidth(),stereotypeLabel->GetWidth());
        return twidth;
}

TextShape *UCDSingleClassBox::ChooseTextShape(int x, int y) {
        // in first part (of the class name) ?
        int textHeight = GetName()->GetFontHeight();
	int addLines = 1;		// for <<actor>>
	int min_firstboxlines = 1;
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
        int snHeight = (addLines+labelLines) * textHeight;
        int pos_y = GetTopMost() + snHeight;
        if (y <= pos_y) {
		if (y <= GetTopMost() + textHeight)
			return 0;	// <<actor>> stereotype
                if (GetViewer()->IsShowIndexes() && !IsFixedIndexLabel()) {
                        if (y <= GetName()->GetPosition()->y &&
                            x >= GetName()->GetPosition()->x + GetWidth()/3)
                                return GetIndexLabel();
                }
                if (!IsFixedName())
                        return GetName();
        }
	if (!IsFixedName())
		return GetName();
	return 0;	// dummy statement shuts up compiler
}

void UCDSingleClassBox::CalcPositionStereotypeLabel() {
        int textHeight = GetName()->GetFontHeight();
        Point pt;
        pt.x = GetPosition()->x;
        pt.y = GetTopMost() + textHeight/2;
        stereotypeLabel->SetPosition(&pt);
}

