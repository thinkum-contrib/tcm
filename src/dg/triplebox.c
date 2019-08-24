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
#include "grafport.h"
#include "diagramviewer.h"
#include "shapeview.h"
#include "triplebox.h"

TripleBox::TripleBox(ShapeView *v, Grafport *g, int x, int y, int w, int h): 
		DoubleBox(v, g, x, y, w, h) {
	labels2 = new List<TextShape *>;
	label2Description = "Label2";
	separator2LineStyle = GetLineStyle();
	SetSize(w, RequiredHeight());
}

TripleBox::TripleBox(const TripleBox &s): DoubleBox(s) {
	label2Description = s.label2Description;
	separator2LineStyle = s.separator2LineStyle;
	labels2 = new List<TextShape *>;
	for (s.labels2->first(); !s.labels2->done(); s.labels2->next()) {
		TextShape *a1 = s.labels2->cur();
		TextShape *at = new TextShape(*a1);
		at->SetParent(this);
		labels2->add(at);
	} 
	SetSize(s.GetWidth(), s.GetHeight());
}

TripleBox::TripleBox(const NodeShape &s): DoubleBox(s) {
	Init();
}

TripleBox::TripleBox(const Box &s): DoubleBox(s) {
	Init();
}

TripleBox::TripleBox(const DoubleBox &s): DoubleBox(s) {
	Init();
}

void TripleBox::Init() {
	label2Description = "Label2";
	labels2 = new List<TextShape *>;
	separator2LineStyle = GetLineStyle();
	SetTextShape();
	AdjustSizes(GetName()->GetString());
}

TripleBox::~TripleBox() {
	labels2->clear();
	delete labels2;
}

void TripleBox::DrawTextShapes() {
	string oldBackground;
	Grafport *g = GetGrafport();
	if (GetFillStyle() != FillStyle::UNFILLED) {
		oldBackground = *g->GetBackgroundColor();
		g->SetBackgroundColor(GetFillColor());
	}
	DoubleBox::DrawTextShapes();
	int textHeight = GetName()->GetFontHeight();
	int ht = DoubleBoxHeight();
	if (ht < GetHeight()) {
		SetDrawAttributes();
		g->SetLineStyle(separator2LineStyle);
		g->DrawLine(GetLeftMost()+1, GetTopMost()+ht, 
			GetRightMost()-1, GetTopMost()+ht);
		g->SetLineStyle(GetLineStyle());
	}
	int i = ht;
	for (labels2->first(); !labels2->done(); labels2->next()) {
		i += textHeight;
		if (i < GetHeight())
			labels2->cur()->Draw();
	} 
	if (GetFillStyle() != FillStyle::UNFILLED)
		g->SetBackgroundColor(&oldBackground);
}

void TripleBox::DrawShape() {
	DoubleBox::DrawShape();
}

int TripleBox::DoubleBoxHeight() {
	int textHeight = GetName()->GetFontHeight();
	int nameHeight = max(GetName()->GetString()->lines(), 2)  *textHeight;
	if (NrLabels() == 0)
		return int(nameHeight + 1.5*textHeight);
	else
		return int(nameHeight + (1 + NrLabels())*textHeight);
}

int TripleBox::RequiredHeight() {
	int textHeight = GetName()->GetFontHeight();
	int ht = DoubleBoxHeight();
	ht += (1 + labels2->count())*textHeight;
	return max(ht, initialHeight);
}

void TripleBox::AdjustSize() {
	int twidth = GetName()->GetWidth();
	List<TextShape *> *llist = GetLabels();
	for (llist->first(); !llist->done(); llist->next()) {
		int wd = llist->cur()->GetStringWidth();
		twidth = max(twidth, wd);
	} 
	for (labels2->first(); !labels2->done(); labels2->next()) {
		int wd = labels2->cur()->GetStringWidth();
		twidth = max(twidth, wd);
	}
	int ht = RequiredHeight();
	if (twidth > GetWidth() || ht != GetHeight()) {
		int wd = max((twidth+2*TEXTMARGIN), GetWidth());
		UpdateSize(wd, ht);
		GetViewer()->ShapePositionUpdate(this);
	}
//	else
//		CalcPositionLabels();
}

void TripleBox::CalcPositionLabels() {
	DoubleBox::CalcPositionLabels();
	CalcPositionLabels2();
}

void TripleBox::CalcPositionLabels2() {
	Point pt = *GetPosition();
	pt.y = GetTopMost() + DoubleBoxHeight();
	int textHeight = GetName()->GetFontHeight();
	pt.y += (3*textHeight)/4;
	for (labels2->first(); !labels2->done(); labels2->next()) {
		TextShape *t = labels2->cur();
		// position and left adjust textshape
		int w = t->GetStringWidth();
		// int h = t->GetHeight();
		pt.x = GetLeftMost() + w/2 + TEXTMARGIN;
		t->SetPosition(&pt);
		pt.y += textHeight;
	}
}

TextShape *TripleBox::ChooseTextShape(int x, int y) {
	int textHeight = GetName()->GetFontHeight();
	int pos_y = GetTopMost() + DoubleBoxHeight();
	if (y <= pos_y)
		return DoubleBox::ChooseTextShape(x, y);
	else {
		pos_y += textHeight/2;
		for (labels2->first(); !labels2->done(); labels2->next()) {
			pos_y += textHeight;
			if ( pos_y >= GetBottomMost() )
				return 0;
			else if (y <= pos_y)
				return labels2->cur();
		}
		if (GetViewer()->IsEditing())
			return 0;
		TextShape *t = new TextShape(GetView(), 
				GetGrafport(), this);
		t->SetSequence(labels2->count());
		t->SetAlignment(TextAlign::LEFT);
		t->SetDescription(&label2Description);
		t->SetFont(GetName()->GetFont());
		t->SetColor(GetName()->GetColor());
		Undraw();
		labels2->add(t);
		CalcPositionLabels2();
		// move the new label to a better position.
		Point pt = *t->GetPosition();
			pt.x += GetWidth()/2 - TEXTMARGIN;
			t->SetPosition(&pt);
			Draw();
			return t;
		}
	}

bool TripleBox::HasTextShape(TextShape *t) const {
	if (DoubleBox::HasTextShape(t))
		return True;
	for (labels2->first(); !labels2->done(); labels2->next())
		if (labels2->cur() == t)
			return True;
	return False;
}

void TripleBox::UpdateLabel2(const string *s, unsigned n, bool update) {
	if (IsVisible())
		Undraw();
	if (update) {
		if (n > labels2->count())
			error("%s, line %d: impl error: "
			   "illegal label2 nr %d\n", __FILE__, __LINE__, n);
		else if (n == labels2->count()) {
			// insert new label2.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this); 
			t->SetSequence(n);
			t->SetAlignment(TextAlign::LEFT);
			t->SetDescription(&label2Description);
			t->SetFont(GetName()->GetFont());
			t->SetColor(GetName()->GetColor());
			labels2->add(t);
			CalcPositionLabels2();
		}
		if (*s != "")
			(*labels2)[n]->SetString(s);
		else {
			// delete this label2
			unsigned i = labels2->count() -1;
			for (unsigned j = n; j < i; j++) {
				const string *nm = (*labels2)[j+1]->GetString();
				(*labels2)[j]->SetString(nm);
			}
			TextShape *x = (*labels2)[i];
			labels2->removei(i);
			delete x;
		}
	}
	else {
		if (n > labels2->count())
			error("%s, line %d: impl error: "
			   "illegal label2 nr %d\n", __FILE__, __LINE__, n);
		else if (*s != "") {  // insert new textshape.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this); 
			t->SetSequence(n);
			t->SetAlignment(TextAlign::LEFT);
			t->SetDescription(&label2Description);
			t->SetFont(GetName()->GetFont());
			t->SetColor(GetName()->GetColor());
			t->SetString(s);
			labels2->insert(t, n);
			CalcPositionLabels2();
			for (unsigned i=n+1; i<labels2->count(); i++)
				(*labels2)[i]->SetSequence(i);
		}
		// ignore empty strings;
	}
	AdjustSizes(s);
	if (IsVisible())
		Draw();
}
 
void TripleBox::AdjustSizes(const string *s) {
	if (!GetViewer()->IsAutoResize()) {
//		CalcPositionLabels();
		return;
	}
	int twidth = GetName()->GetFont()->StringWidth(s);
	twidth += TEXTMARGIN*2;
	int ht = RequiredHeight();
	if (twidth > GetWidth() || GetHeight() != ht) {
		int wd = max(twidth, GetWidth());
		SetSize(wd, ht);
		GetViewer()->ShapePositionUpdate(this);
	}
//	else
//		CalcPositionLabels();
}

void TripleBox::SetTextShape() {
	DoubleBox::SetTextShape();
	labels2->clear();
}

void TripleBox::SetFont(XFont *ft) {
	DoubleBox::SetFont(ft);
	for (labels2->first(); !labels2->done(); labels2->next())
		labels2->cur()->SetFont(ft);
}

void TripleBox::SetTextColor(const string *c) {
	DoubleBox::SetTextColor(c);
	for (labels2->first(); !labels2->done(); labels2->next())
		labels2->cur()->SetColor(c);
}

void TripleBox::SetGrafport(Grafport *g) {
	DoubleBox::SetGrafport(g);
	for (labels2->first(); !labels2->done(); labels2->next())
		labels2->cur()->SetGrafport(g);
}

void TripleBox::SetView(ShapeView *v) {
	DoubleBox::SetView(v);
	for (labels2->first(); !labels2->done(); labels2->next())
		labels2->cur()->SetView(v);
}

bool TripleBox::HasString(const string *s, bool sens, bool sub) const {
	if (DoubleBox::HasString(s, sens, sub))
		return True;
	for (labels2->first(); !labels2->done(); labels2->next()) {
		if (labels2->cur()->HasString(s, sens, sub))
			return True;
	}
	return False;
}

bool TripleBox::HasString(const string *s, bool sens, bool sub, 
		List<TextShape *> *list) {
	bool b = DoubleBox::HasString(s, sens, sub, list);
	List<TextShape *> tmplabels (*labels2);
	for (tmplabels.first(); !tmplabels.done(); tmplabels.next()) {
		b += tmplabels.cur()->HasString(s, sens, sub, list);
	}
	return b;
}

TextShape *TripleBox::GetLabel2(unsigned n) {
        if (check(n < labels2->count()))
                return (*labels2)[n];
        else
                return 0;
}
