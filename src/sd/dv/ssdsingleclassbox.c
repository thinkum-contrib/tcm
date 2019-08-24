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
#include "ssdclassnode.h"
#include "cbclassnode.h"
#include "diagramviewer.h"
#include "ssdsingleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdtripleclassbox.h"
#include "stickman.h" 
#include "inputfile.h"
#include "outputfile.h"

const int SSDSingleClassBox::TEXTMARGIN = 4;

SSDSingleClassBox::SSDSingleClassBox(ShapeView *v, Grafport *g, 
		double x, double y): Box(v, g, x, y) {
        stereotypeLabel = new TextShape(v, g, this);
        stereotypeLabel->SetOneLine(True);
        stereotypeLabel->SetDescription("Stereotype");
        string my_stereo = "<<SSDSingleClassBox>>";
        stereotypeLabel->SetString(&my_stereo);
        propertiesLabel = new TextShape(v, g, this);
        propertiesLabel->SetOneLine(False);
        propertiesLabel->SetDescription("Properties");
        string my_props = "{ SSDSingleClassBox }";
        propertiesLabel->SetString(&my_props);
	showStereotype = False;
	showProperties = False;
	SetSize(GetWidth(), RequiredHeight());
}

SSDSingleClassBox::~SSDSingleClassBox() {
	delete stereotypeLabel;
	delete propertiesLabel;
}

SSDSingleClassBox::SSDSingleClassBox(const SSDSingleClassBox &s): Box(s) {
	showStereotype = s.showStereotype;
	showProperties = s.showProperties;
	stereotypeLabel = new TextShape(*s.stereotypeLabel);
	propertiesLabel = new TextShape(*s.propertiesLabel);
	stereotypeLabel->SetParent(this);
        propertiesLabel->SetParent(this);
	SetSize(s.GetWidth(), s.GetHeight());
}

SSDSingleClassBox::SSDSingleClassBox(const SSDDoubleClassBox &s): Box(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
	stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
	propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
        propertiesLabel->SetParent(this);
	SetSize(s.GetWidth(), RequiredHeight());
}

SSDSingleClassBox::SSDSingleClassBox(const SSDTripleClassBox &s): Box(s) {
	showStereotype = s.IsShowStereotype();
        showProperties = s.IsShowProperties();
	stereotypeLabel = new TextShape(*s.GetStereotypeLabel());
	propertiesLabel = new TextShape(*s.GetPropertiesLabel());
	stereotypeLabel->SetParent(this);
        propertiesLabel->SetParent(this);
	SetSize(s.GetWidth(), RequiredHeight());
}


SSDSingleClassBox::SSDSingleClassBox(const StickMan &s): Box(s) {
	showStereotype = True;
	stereotypeLabel = new TextShape(GetView(), GetGrafport(), this);
	stereotypeLabel->SetOneLine(True);
	stereotypeLabel->SetDescription("Stereotype");
	string my_stereo = "<<actor>>";
	stereotypeLabel->SetString(&my_stereo);
	stereotypeLabel->SetParent(this); 
	showProperties = False;
	propertiesLabel = new TextShape(GetView(), GetGrafport(), this);
	propertiesLabel->SetParent(this); 

	SetSize(s.GetWidth(), RequiredHeight());
}

void SSDSingleClassBox::SetGrafport(Grafport *g) {
	Box::SetGrafport(g);
        stereotypeLabel->SetGrafport(g);
        propertiesLabel->SetGrafport(g);
}

void SSDSingleClassBox::SetView(ShapeView *v) {
	Box::SetView(v);
        stereotypeLabel->SetView(v);
        propertiesLabel->SetView(v);
}

bool SSDSingleClassBox::HasTextShape(TextShape *t) const {
        if (Box::HasTextShape(t))
                return True;
        if (stereotypeLabel == t)
                return True;
        if (propertiesLabel == t)
                return True;
        return False;
}

bool SSDSingleClassBox::HasString(const string *s, bool sens, bool sub) const {
        if (GetName()->HasString(s, sens, sub))
                return True;
	if (showStereotype && stereotypeLabel->HasString(s, sens, sub))
                return True;
	if (showProperties && propertiesLabel->HasString(s, sens, sub))
                return True;
        return False;
}
 
bool SSDSingleClassBox::HasString(const string *s, bool sens, bool sub,
                        List<TextShape *> *list) {
        bool b = GetName()->HasString(s, sens, sub, list);
	if (showStereotype && stereotypeLabel->HasString(s, sens, sub, list))
                b = True;
	if (showProperties && propertiesLabel->HasString(s, sens, sub, list))
                b = True;
        return b;
}
 
void SSDSingleClassBox::SetTextShape() {
        Box::SetTextShape();
        if (!check(GetSubject() && 
	     	(GetSubject()->GetClassType()==Code::SSD_CLASS_NODE ||
	     	 GetSubject()->GetClassType()==Code::CBD_CLASS_NODE)))
			return;
		if (GetSubject()->GetClassType()==Code::SSD_CLASS_NODE) {
			stereotypeLabel->SetString(
					((SSDClassNode *)
					GetSubject())->GetStereotype());
			stereotypeLabel->SetParent(this);
			propertiesLabel->SetString(
					((SSDClassNode *)
					GetSubject())->GetProperties());
			propertiesLabel->SetParent(this);
//   			CalcPositionLabels();
		}

	     if	(GetSubject()->GetClassType()==Code::CBD_CLASS_NODE) {
			stereotypeLabel->SetString(
					((CBClassNode *)
					GetSubject())->GetStereotype());
			stereotypeLabel->SetParent(this);
			propertiesLabel->SetString(
					((CBClassNode *)
					GetSubject())->GetProperties());
			propertiesLabel->SetParent(this);
//			CalcPositionLabels();
		}

}


bool SSDSingleClassBox::SetAssocSubject(AssocList *al) {
        if (!Box::SetAssocSubject(al))
                return False;
        if (check(GetSubject()) && 
	    		  (GetSubject()->GetClassType()==Code::SSD_CLASS_NODE ||
	    	 	   GetSubject()->GetClassType()==Code::CBD_CLASS_NODE))
                return True;
        SetSubject(0);
        return False;
}
 
//void SSDSingleClassBox::SetSize(int w, int h) {
//        Box::SetSize(w, h);
//	CalcPositionLabels();
//}
 
//void SSDSingleClassBox::SetPosition(const Point *pos, bool snap) {
//        Box::SetPosition(pos, snap);
//	CalcPositionLabels();
//}
 
void SSDSingleClassBox::SetFont(XFont *ft) {
        Box::SetFont(ft);
	stereotypeLabel->SetFont(ft);
	propertiesLabel->SetFont(ft);
//	CalcPositionLabels();
}

void SSDSingleClassBox::SetTextColor(const string *c) {
        Box::SetTextColor(c);
	stereotypeLabel->SetColor(c);
	propertiesLabel->SetColor(c);
}

void SSDSingleClassBox::UpdateShowStereotype(bool b) {
	if (b == showStereotype)
		return;
	if (IsVisible())
                Undraw();
        showStereotype = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}

void SSDSingleClassBox::UpdateShowProperties(bool b) {
	if (b == showProperties)
		return;
	if (IsVisible())
                Undraw();
        showProperties = b;
//	CalcPositionLabels();
        if (IsVisible())
                Draw();
}

void SSDSingleClassBox::DrawTextShapes() {
	Box::DrawTextShapes();
        if (showStereotype)
                stereotypeLabel->Draw();
        if (showProperties)
                propertiesLabel->Draw();
}

void SSDSingleClassBox::AdjustSize() {
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

void SSDSingleClassBox::CalcPositionLabels() {
	Box::CalcPositionLabels();

        Point pt = *GetPosition();
        int textHeight = GetName()->GetFontHeight();
	// int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	int nameHeight = labelLines * textHeight;
        if (showStereotype)
                pt.y = GetTopMost() + textHeight/4 + 
			textHeight + nameHeight/2;
        else
                pt.y = GetTopMost() + textHeight/4 + nameHeight/2;
        GetName()->SetPosition(&pt);
        // set index label position.
        pt.x = GetName()->GetPosition()->x + GetWidth()*5/12;
        pt.y = GetName()->GetPosition()->y - nameHeight/4;
        GetIndexLabel()->SetPosition(&pt);
        if (showStereotype)
                CalcPositionStereotypeLabel();
        if (showProperties)
                CalcPositionPropertiesLabel();
}

int SSDSingleClassBox::RequiredHeight() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
	// calculate first_compartmentHeight
        if (showProperties)
                addLines += GetPropertiesLabelString()->lines();
        int snpHeight = (addLines+labelLines) * textHeight;
        int ht = (snpHeight + textHeight);
        return ht;
}

int SSDSingleClassBox::RequiredWidth() {
        int twidth = GetName()->GetWidth();
        if (showStereotype)
                twidth = max(twidth, stereotypeLabel->GetWidth());
        if (showProperties)
                twidth = max(twidth, propertiesLabel->GetWidth());
        return twidth;
}

TextShape *SSDSingleClassBox::ChooseTextShape(int x, int y) {
        // in first part (of the class name) ?
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
        int snHeight = (addLines+labelLines) * textHeight;
        int pos_y = GetTopMost() + snHeight;
        if (y <= pos_y) {
                if (showStereotype) {
                        if (y <= GetTopMost() + textHeight)
                                return stereotypeLabel;
                }
                if (GetViewer()->IsShowIndexes() && !IsFixedIndexLabel()) {
                        if (y <= GetName()->GetPosition()->y &&
                            x >= GetName()->GetPosition()->x + GetWidth()/3)
                                return GetIndexLabel();
                }
                if (!IsFixedName())
                        return GetName();
        } else
        	if (showProperties)
			return propertiesLabel;
	if (!IsFixedName())
		return GetName();
	return 0;	// dummy statement shuts up compiler
}

void SSDSingleClassBox::CalcPositionStereotypeLabel() {
        int textHeight = GetName()->GetFontHeight();
        Point pt;
        pt.x = GetPosition()->x;
        pt.y = GetTopMost() + textHeight/2;
        stereotypeLabel->SetPosition(&pt);
}

void SSDSingleClassBox::UpdateStereotypeLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetStereotypeLabelString(s);
        if (IsVisible())
                Draw();
}
 
void SSDSingleClassBox::CalcPositionPropertiesLabel() {
        int textHeight = GetName()->GetFontHeight();
	int addLines = (showStereotype ? 1 : 0);
	// min_firstboxlines : 2 when no <<stereotype>> / {props} shown
	int min_firstboxlines = ((showStereotype || showProperties) ? 1 : 2);
        int labelLines = max(GetName()->GetString()->lines(),min_firstboxlines);
        int snHeight = (addLines+labelLines) * textHeight;
        int pHeight = (showProperties ? 
			GetPropertiesLabelString()->lines()*textHeight : 0);
        Point pt;
	pt.x = GetPosition()->x;
	pt.y = GetTopMost() + textHeight/4 + snHeight + pHeight/2;
        propertiesLabel->SetPosition(&pt);
}

void SSDSingleClassBox::UpdatePropertiesLabelString(const string *s) {
        if (IsVisible())
                Undraw();
        SetPropertiesLabelString(s);
        if (IsVisible())
                Draw();
}

bool SSDSingleClassBox::ReadMembers(InputFile *ifile, double format) {
        if (!Box::ReadMembers(ifile, format))
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

void SSDSingleClassBox::WriteMembers(OutputFile *ofile) {
        Box::WriteMembers(ofile);
        (*ofile) << "\t{ ShowStereotype " << 
			(showStereotype?"True":"False") << " }\n";
        (*ofile) << "\t{ ShowProperties " << 
			(showProperties?"True":"False") << " }\n";
}

