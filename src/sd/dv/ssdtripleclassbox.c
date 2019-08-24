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
#include "grafport.h"
#include "ssdsingleclassbox.h"
#include "ssdtripleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdclassnode.h"
#include "diagramviewer.h"
#include "inputfile.h"
#include "outputfile.h"

SSDTripleClassBox::SSDTripleClassBox(ShapeView *v, Grafport *g, int x, int y, 
		int w, int h): TripleClassBox(v, g, x, y, w, h) {
        stereotypeLabel = new TextShape(v, g, this);
        stereotypeLabel->SetOneLine(True);
        stereotypeLabel->SetDescription("Stereotype");
	string my_stereo = "<<SSDTripleClassBox>>";
        stereotypeLabel->SetString(&my_stereo);
        propertiesLabel = new TextShape(v, g, this);
        propertiesLabel->SetOneLine(False);
        propertiesLabel->SetDescription("Properties");
        string my_props = "{ SSDTripleClassBox }";
        propertiesLabel->SetString(&my_props);
	showStereotype = False;
        showProperties = False;
	SetSize(w, RequiredHeight());
}

SSDTripleClassBox::~SSDTripleClassBox() {
        delete stereotypeLabel;
        delete propertiesLabel;
}

SSDTripleClassBox::SSDTripleClassBox(const SSDTripleClassBox &s): 
						TripleClassBox(s) {
	showStereotype = s.showStereotype;
        showProperties = s.showProperties;
        stereotypeLabel = new TextShape(*(s.stereotypeLabel));
        propertiesLabel = new TextShape(*(s.propertiesLabel));
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
        SetSize(s.GetWidth(), s.GetHeight());
}

SSDTripleClassBox::SSDTripleClassBox(const SSDDoubleClassBox &s): 
						TripleClassBox(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
        stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
        propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
        SetTextShape();
        AdjustSizes(GetName()->GetString());
}

SSDTripleClassBox::SSDTripleClassBox(const SSDSingleClassBox &s): 
						TripleClassBox(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
        stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
        propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
	SetTextShape();
        AdjustSizes(GetName()->GetString());
}

void SSDTripleClassBox::SetGrafport(Grafport *g) {
        TripleClassBox::SetGrafport(g);
        stereotypeLabel->SetGrafport(g);
        propertiesLabel->SetGrafport(g);
}

void SSDTripleClassBox::SetView(ShapeView *v) {
        TripleClassBox::SetView(v);
        stereotypeLabel->SetView(v);
        propertiesLabel->SetView(v);
}

bool SSDTripleClassBox::HasTextShape(TextShape *t) const {
        if (TripleClassBox::HasTextShape(t))
                return True;
	if (GetStereotypeLabel() == t)
                return True;
        if (GetPropertiesLabel() == t)
                return True;
        return False;
}

bool SSDTripleClassBox::HasString(const string *s, bool sens, bool sub) const {
        if (TripleClassBox::HasString(s, sens, sub))
                return True;
        if (showStereotype && stereotypeLabel->HasString(s, sens, sub))
                return True;
        if (showProperties && propertiesLabel->HasString(s, sens, sub))
                return True;
        return False;
}
 
bool SSDTripleClassBox::HasString(const string *s, bool sens, bool sub,
                        List<TextShape *> *list) {
        bool b = TripleClassBox::HasString(s, sens, sub, list);
        if (showStereotype && stereotypeLabel->HasString(s, sens, sub, list))
                b = True;
        if (showProperties && propertiesLabel->HasString(s, sens, sub, list))
                b = True;
        return b;
}

void SSDTripleClassBox::SetTextShape() {
	TripleClassBox::SetTextShape();

	if (!check(GetSubject() &&
             GetSubject()->GetClassType()==Code::SSD_CLASS_NODE))
                return;
        GetStereotypeLabel()->SetString(
                        ((SSDClassNode *)GetSubject())->GetStereotype());
        GetStereotypeLabel()->SetParent(this);
        GetPropertiesLabel()->SetString(
                        ((SSDClassNode *)GetSubject())->GetProperties());
        GetPropertiesLabel()->SetParent(this);
//	CalcPositionLabels();
}

void SSDTripleClassBox::SetFont(XFont *ft) {
        TripleClassBox::SetFont(ft);
        stereotypeLabel->SetFont(ft);
        propertiesLabel->SetFont(ft);
//	CalcPositionLabels();
}
 
void SSDTripleClassBox::SetTextColor(const string *c) {
        TripleClassBox::SetTextColor(c);
        stereotypeLabel->SetColor(c);
        propertiesLabel->SetColor(c);
}

void SSDTripleClassBox::UpdateShowStereotype(bool b) {
        if (b == showStereotype)
                return;
        if (IsVisible())
                Undraw();
        showStereotype = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}
 
void SSDTripleClassBox::UpdateShowProperties(bool b) {
        if (b == showProperties)
                return;
        if (IsVisible())
                Undraw();
        showProperties = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}

void SSDTripleClassBox::DrawTextShapes() {
        string oldBackground;
        Grafport *g = GetGrafport();
        if (GetFillStyle() != FillStyle::UNFILLED) {
                oldBackground = *g->GetBackgroundColor();
                g->SetBackgroundColor(GetFillColor()->getstr());
        }
	NodeShape::DrawTextShapes();
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        int dboxHeight = DoubleBoxHeight();
	if (snpHeight < GetHeight()) {
		g->DrawLine(GetLeftMost()+1, GetTopMost()+snpHeight+1,
			GetRightMost()-1,
			GetTopMost()+snpHeight+1);
		g->SetLineStyle(GetLineStyle());
	}
	int i = snpHeight;
	for (GetLabels()->first(); !GetLabels()->done(); GetLabels()->next()) {
		i += textHeight;
		if (i < GetHeight())
			GetLabels()->cur()->Draw();
	}
	if (dboxHeight < GetHeight()) {
		g->SetLineStyle(GetSeparatorLineStyle());
		g->DrawLine(GetLeftMost()+1, GetTopMost()+dboxHeight,
			GetRightMost()-1,
			GetTopMost()+dboxHeight);
		g->SetLineStyle(GetLineStyle());
	}
	i = dboxHeight;
	for (GetLabels2()->first(); !GetLabels2()->done(); GetLabels2()->next()) {
		i += textHeight;
		if (i < GetHeight())
			GetLabels2()->cur()->Draw();
	}
	if (GetFillStyle() != FillStyle::UNFILLED)
		g->SetBackgroundColor(oldBackground.getstr());
	if (showStereotype)
		stereotypeLabel->Draw();
	if (showProperties)
		propertiesLabel->Draw();
}

void SSDTripleClassBox::AdjustSize() {
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

void SSDTripleClassBox::AdjustSizes(const string *) {
        if (!GetViewer()->IsAutoResize()) {
//		CalcPositionLabels();
                return;
        }
        int twd = RequiredWidth();
        int ht = RequiredHeight();
        if (twd > GetWidth() || GetHeight() != ht) {
                int wd = max((twd+2*TEXTMARGIN), GetWidth());
                SetSize(wd, ht);
                GetViewer()->ShapePositionUpdate(this);
        }
//	else
//		CalcPositionLabels();
}

void SSDTripleClassBox::CalcPositionLabels() {
	TripleClassBox::CalcPositionLabels();

	Point pt = *GetPosition();
	// calculate labelnameHeight first
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	int nameHeight = labelLines * textHeight;
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;

        if (showStereotype)
                pt.y = GetTopMost() + textHeight + nameHeight/2;
        else
                pt.y = GetTopMost() + nameHeight/2;
        GetName()->SetPosition(&pt);

        pt.y = GetTopMost() + snpHeight;
        pt.y += (3*textHeight)/4;
        for (GetLabels()->first(); !GetLabels()->done(); GetLabels()->next()) {
                TextShape *t = GetLabels()->cur();
                // position and left adjust textshape
                int w = t->GetStringWidth();
                pt.x = GetLeftMost() + w/2 + TEXTMARGIN;
                t->SetPosition(&pt);
                pt.y += textHeight;
        }

	//  Operation part
	CalcPositionLabels2();

        // set index label position.
        pt.x = GetName()->GetPosition()->x + GetWidth()*5/12;
        pt.y = GetName()->GetPosition()->y - nameHeight/4;
        GetIndexLabel()->SetPosition(&pt);

	if (showStereotype)
		CalcPositionStereotypeLabel();
        if (showProperties)
                CalcPositionPropertiesLabel();
}

void SSDTripleClassBox::CalcPositionLabels2() {
        Point pt = *GetPosition();
        pt.y = GetTopMost() + DoubleBoxHeight();
        int textHeight = GetName()->GetFontHeight();
        pt.y += (3*textHeight)/4;
        for (GetLabels2()->first(); !GetLabels2()->done(); GetLabels2()->next()) {
                TextShape *t = GetLabels2()->cur();
                // position and left adjust textshape
                int w = t->GetStringWidth();
                // int h = t->GetHeight();
                pt.x = GetLeftMost() + w/2 + TEXTMARGIN;
                t->SetPosition(&pt);
                pt.y += textHeight;
        }
}

void SSDTripleClassBox::CalcPositionStereotypeLabel() {
        int textHeight = GetName()->GetFontHeight();
        Point pt;
        pt.x = GetPosition()->x;
        pt.y = GetTopMost() + textHeight/2;
        stereotypeLabel->SetPosition(&pt);
}

void SSDTripleClassBox::CalcPositionPropertiesLabel() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
        int snHeight = (addLines+labelLines) * textHeight;

        int propHeight = (showProperties ?
                        GetPropertiesLabelString()->lines()*textHeight : 0);
        Point pt;
        pt.x = GetPosition()->x;
        pt.y = GetTopMost() + snHeight + propHeight/2;
        propertiesLabel->SetPosition(&pt);
}

int SSDTripleClassBox::RequiredHeight() {
        // int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	// int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        // int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        // int snpHeight = (addLines+labelLines) * textHeight;
        // int propHeight = GetPropertiesLabelString()->lines() * textHeight;
 
        // int ht = (snpHeight + textHeight + GetLabels()->count()*textHeight);
        // int ht2 = (snpHeight + int(1.5*textHeight) + GetLabels()->count()*textHeight +
        //		textHeight + GetLabels2()->count()*textHeight);
	// int dboxHeight = DoubleBoxHeight();
	int tboxHeight = TripleBoxHeight();
        return max(tboxHeight, GetInitialHeight());
}

int SSDTripleClassBox::RequiredWidth() {
	int twidth = GetName()->GetWidth();
	if (showStereotype)
		twidth = max(twidth, GetStereotypeLabel()->GetWidth());
	if (showProperties)
		twidth = max(twidth, GetPropertiesLabel()->GetWidth());
	// Labels
	for (GetLabels()->first(); !GetLabels()->done(); GetLabels()->next()) {
		int wd = GetLabels()->cur()->GetStringWidth();
		twidth = max(twidth, wd);
	}
	for (GetLabels2()->first(); !GetLabels2()->done(); GetLabels2()->next()) {
		int wd = GetLabels2()->cur()->GetStringWidth();
		twidth = max(twidth, wd);
	}
        return twidth;
}

int SSDTripleClassBox::DoubleBoxHeight() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        if (NrLabels() == 0)
                return int(snpHeight + 1.5*textHeight);
        else
                return int(snpHeight + (1 + NrLabels())*textHeight);
}

int SSDTripleClassBox::TripleBoxHeight() {
        int rval1, rval2;
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        if (NrLabels() == 0)
                rval1 = int(snpHeight + 1.5*textHeight);
        else
                rval1 = int(snpHeight + (1 + NrLabels())*textHeight);
        if (NrLabels2() == 0)
                rval2 = int(1.0*textHeight);
        else
                rval2 = int((1 + NrLabels2())*textHeight);
	return (rval1+rval2);
}

TextShape *SSDTripleClassBox::ChooseTextShape(int x, int y) {
        // in first part (of the class name) ?
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
        int snHeight = (addLines+labelLines) * textHeight;
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        int dboxHeight = DoubleBoxHeight();
        int pos_y = GetTopMost() + snpHeight;
        int attr_y = GetTopMost() + dboxHeight;
        if (y <= pos_y) {
                if (showStereotype) {
                        if (y <= GetTopMost() + textHeight)
                                return GetStereotypeLabel();
                }
                if (GetViewer()->IsShowIndexes() && !IsFixedIndexLabel()) {
                        if (y <= GetName()->GetPosition()->y &&
                            x >= GetName()->GetPosition()->x + GetWidth()/3)
                                return GetIndexLabel();
                }
                if (y > GetTopMost() + snHeight)
                        return GetPropertiesLabel();
                if (!IsFixedName())
                        return GetName();
        }
	else if (y <= attr_y) {		// in attribute part
		pos_y += textHeight/2;
		for (GetLabels()->first(); !GetLabels()->done();
		     GetLabels()->next()) {
			pos_y += textHeight;
			if (pos_y >= GetBottomMost())
				return 0;
			else if (y <= pos_y)
				return GetLabels()->cur();
		}
		if (GetViewer()->IsEditing())
			return 0;
		// somewhere down the list; create a new label.
		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(GetLabels()->count());
		t->SetDescription(&labelDescription);
		t->SetFont(GetName()->GetFont());
		t->SetColor(GetName()->GetColor());
		Undraw();
		GetLabels()->add(t);
//		CalcPositionLabels();
		// move text shape to a better position.
		Point pt = *t->GetPosition();
		pt.x += GetWidth()/2 - TEXTMARGIN;
		t->SetPosition(&pt);
		Draw();
		return t;
        }
	else {	// in operation part
        	pos_y = GetTopMost() + dboxHeight;
		pos_y += textHeight/2;
		for (GetLabels2()->first(); !GetLabels2()->done();
		     GetLabels2()->next()) {
			pos_y += textHeight;
			if (pos_y >= GetBottomMost())
				return 0;
			else if (y <= pos_y)
				return GetLabels2()->cur();
		}
		if (GetViewer()->IsEditing())
			return 0;
		// somewhere down the list; create a new label.
		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(GetLabels2()->count());
		t->SetDescription(&label2Description);
		t->SetFont(GetName()->GetFont());
		t->SetColor(GetName()->GetColor());
		Undraw();
		GetLabels2()->add(t);
		CalcPositionLabels2();
		// move text shape to a better position.
		Point pt = *t->GetPosition();
		pt.x += GetWidth()/2 - TEXTMARGIN;
		t->SetPosition(&pt);
		Draw();
		return t;
	}
	return 0;	// dummy statement shuts up compiler
}

void SSDTripleClassBox::UpdateStereotypeLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetStereotypeLabelString(s);
        if (IsVisible())
                Draw();
}
 
void SSDTripleClassBox::UpdatePropertiesLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetPropertiesLabelString(s);
        if (IsVisible())
                Draw();
}
 
bool SSDTripleClassBox::ReadMembers(InputFile *ifile, double format) {
        if (!TripleClassBox::ReadMembers(ifile, format))
                return False;
        if (format >= 1.28) {
                string val;
                if (!ifile->ReadAttribute("ShowStereotype", &val))
                        return False;
                showStereotype = (val == "True");
                if (!ifile->ReadAttribute("ShowProperties", &val))
                        return False;
                showProperties = (val == "True");
        }
        else {
                showStereotype = False;
                showProperties = False;
        }
	return True;
}
 
void SSDTripleClassBox::WriteMembers(OutputFile *ofile) {
        TripleClassBox::WriteMembers(ofile);
        (*ofile) << "\t{ ShowStereotype " << (showStereotype?"True":"False") << " }\n";
        (*ofile) << "\t{ ShowProperties " << (showProperties?"True":"False") << " }\n";
}
