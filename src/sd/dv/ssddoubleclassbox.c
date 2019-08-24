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
#include "ssdsingleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdtripleclassbox.h"
#include "ssdclassnode.h"
#include "diagramviewer.h"
#include "inputfile.h"
#include "outputfile.h"
#include "grafport.h"

SSDDoubleClassBox::SSDDoubleClassBox(ShapeView *v, Grafport *g, int x, int y, 
		int w, int h): DoubleClassBox(v, g, x, y, w, h) {
        stereotypeLabel = new TextShape(v, g, this);
        stereotypeLabel->SetOneLine(True);
        stereotypeLabel->SetDescription("Stereotype");
	string my_stereo = "<<SSDDoubleClassBox>>";
        stereotypeLabel->SetString(&my_stereo);
        propertiesLabel = new TextShape(v, g, this);
        propertiesLabel->SetOneLine(False);
        propertiesLabel->SetDescription("Properties");
        string my_props = "{ SSDDoubleClassBox }";
        propertiesLabel->SetString(&my_props);
	showStereotype = False;
        showProperties = False;
	SetSize(w, RequiredHeight());
}

SSDDoubleClassBox::~SSDDoubleClassBox() {
        delete stereotypeLabel;
        delete propertiesLabel;
}

SSDDoubleClassBox::SSDDoubleClassBox(const SSDDoubleClassBox &s): DoubleClassBox(s) {
	showStereotype = s.showStereotype;
        showProperties = s.showProperties;
        stereotypeLabel = new TextShape(*s.stereotypeLabel);
        propertiesLabel = new TextShape(*s.propertiesLabel);
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
        SetSize(s.GetWidth(), s.GetHeight());
}

SSDDoubleClassBox::SSDDoubleClassBox(const SSDSingleClassBox &s): DoubleClassBox(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
        stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
        propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
	SetTextShape();
        AdjustSizes(GetName()->GetString());
}

SSDDoubleClassBox::SSDDoubleClassBox(const SSDTripleClassBox &s): DoubleClassBox(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
        stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
        propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
	propertiesLabel->SetParent(this);
	SetTextShape();
        AdjustSizes(GetName()->GetString());
}

void SSDDoubleClassBox::SetGrafport(Grafport *g) {
        DoubleClassBox::SetGrafport(g);
        stereotypeLabel->SetGrafport(g);
        propertiesLabel->SetGrafport(g);
}

void SSDDoubleClassBox::SetView(ShapeView *v) {
        DoubleClassBox::SetView(v);
        stereotypeLabel->SetView(v);
        propertiesLabel->SetView(v);
}

bool SSDDoubleClassBox::HasTextShape(TextShape *t) const {
        if (DoubleClassBox::HasTextShape(t))
                return True;
	if (GetStereotypeLabel() == t)
                return True;
        if (GetPropertiesLabel() == t)
                return True;
        return False;
}

bool SSDDoubleClassBox::HasString(const string *s, bool sens, bool sub) const {
        if (DoubleClassBox::HasString(s, sens, sub))
                return True;
        if (showStereotype && stereotypeLabel->HasString(s, sens, sub))
                return True;
        if (showProperties && propertiesLabel->HasString(s, sens, sub))
                return True;
        return False;
}
 
bool SSDDoubleClassBox::HasString(const string *s, bool sens, bool sub,
                        List<TextShape *> *list) {
        bool b = DoubleClassBox::HasString(s, sens, sub, list);
        if (showStereotype && stereotypeLabel->HasString(s, sens, sub, list))
                b = True;
        if (showProperties && propertiesLabel->HasString(s, sens, sub, list))
                b = True;
        return b;
}

void SSDDoubleClassBox::SetTextShape() {
	DoubleClassBox::SetTextShape();
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
 
void SSDDoubleClassBox::SetFont(XFont *ft) {
        DoubleClassBox::SetFont(ft);
        stereotypeLabel->SetFont(ft);
        propertiesLabel->SetFont(ft);
//	CalcPositionLabels();
}
 
void SSDDoubleClassBox::SetTextColor(const string *c) {
        DoubleClassBox::SetTextColor(c);
        stereotypeLabel->SetColor(c);
        propertiesLabel->SetColor(c);
}

void SSDDoubleClassBox::UpdateShowStereotype(bool b) {
        if (b == showStereotype)
                return;
        if (IsVisible())
                Undraw();
        showStereotype = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}
 
void SSDDoubleClassBox::UpdateShowProperties(bool b) {
        if (b == showProperties)
                return;
        if (IsVisible())
                Undraw();
        showProperties = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}

void SSDDoubleClassBox::DrawTextShapes() {
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
        if (snpHeight < GetHeight()) {
                g->SetLineStyle(GetSeparatorLineStyle());
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

        if (GetFillStyle() != FillStyle::UNFILLED)
                g->SetBackgroundColor(oldBackground.getstr());
	if (showStereotype)
		stereotypeLabel->Draw();
	if (showProperties)
		propertiesLabel->Draw();
}

void SSDDoubleClassBox::AdjustSize() {
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

void SSDDoubleClassBox::AdjustSizes(const string *) {
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

void SSDDoubleClassBox::CalcPositionLabels() {
	DoubleClassBox::CalcPositionLabels();

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

        // set index label position.
        pt.x = GetName()->GetPosition()->x + GetWidth()*5/12;
        pt.y = GetName()->GetPosition()->y - nameHeight/4;
        GetIndexLabel()->SetPosition(&pt);

	if (showStereotype)
		CalcPositionStereotypeLabel();
        if (showProperties)
                CalcPositionPropertiesLabel();
}


void SSDDoubleClassBox::CalcPositionStereotypeLabel() {
        int textHeight = GetName()->GetFontHeight();
        Point pt;
        pt.x = GetPosition()->x;
        pt.y = GetTopMost() + textHeight/2;
        stereotypeLabel->SetPosition(&pt);
}


void SSDDoubleClassBox::CalcPositionPropertiesLabel() {
	// calculate labelnameHeight first
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


int SSDDoubleClassBox::RequiredHeight() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        int ht = (snpHeight + textHeight + GetLabels()->count()*textHeight);
//	return max(ht, GetInitialHeight());
        return ht;
}

int SSDDoubleClassBox::RequiredWidth() {
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
        return twidth;
}


TextShape *SSDDoubleClassBox::ChooseTextShape(int x, int y) {
        // in first part (of the class name) ?
	// calculate #labelnameLines first
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
        int pos_y = GetTopMost() + snpHeight;
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
        // in labels part ??
        pos_y += textHeight/2;
        for (GetLabels()->first(); !GetLabels()->done(); GetLabels()->next()) {
                pos_y += textHeight;
                if (pos_y >= GetTopMost() + GetHeight())
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
//	CalcPositionLabels();
        // move text shape to a better position.
        Point pt = *t->GetPosition();
        pt.x += GetWidth()/2 - TEXTMARGIN;
        t->SetPosition(&pt);
        Draw();
        return t;
}

void SSDDoubleClassBox::UpdateStereotypeLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetStereotypeLabelString(s);
        if (IsVisible())
                Draw();
}
 
void SSDDoubleClassBox::UpdatePropertiesLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetPropertiesLabelString(s);
        if (IsVisible())
                Draw();
}

bool SSDDoubleClassBox::ReadMembers(InputFile *ifile, double format) {
        if (!DoubleClassBox::ReadMembers(ifile, format))
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
 
void SSDDoubleClassBox::WriteMembers(OutputFile *ofile) {
        DoubleClassBox::WriteMembers(ofile);
        (*ofile) << "\t{ ShowStereotype " << (showStereotype?"True":"False") << " }\n";
        (*ofile) << "\t{ ShowProperties " << (showProperties?"True":"False") << " }\n";
}
