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
#include "doublebox.h"

//const PolyPoint DoubleBox::t0(0.0, -0.5, 0.0, 0.0,   0.0, 0.0, -0.5, 1.0);
//const PolyPoint DoubleBox::t1(0.0,  0.5, 0.0, 0.0,   0.0, 0.0, -0.5, 1.0);

//const Polygon DoubleBox::namearea((new List<const PolyPoint *>)
//	->add(&PolyPoint::TopLeft)->add(&t0)
//	->add(&t1)->add(&PolyPoint::TopRight));

//const ShapeType DoubleBox::dbType(Code::DOUBLE_BOX, 80.0, 40.0, 0.0, 0.0,
//	&namearea, NULL, &PolyPoint::Index, &PolyPoint::Dupli,
//	&PolyPoint::Multi, &Polygon::Box);

const int DoubleBox::TEXTMARGIN = 4;

DoubleBox::DoubleBox(ShapeView *v, Grafport *g, double x, double y,
	double w, double h)
	:Box(v, g, x, y)
{
	initialHeight = int(0.5 + h);
	labels = new List<TextShape *>;
	SetSize(static_cast<int>(0.5 + w), RequiredHeight());
	labelDescription = "Label";
	separatorLineStyle = GetLineStyle();
}

DoubleBox::DoubleBox(const DoubleBox &s): Box(s) {
	labelDescription = s.labelDescription;
	initialHeight = s.initialHeight;
	separatorLineStyle = s.separatorLineStyle;
	labels = new List<TextShape *>;
	for (s.labels->first(); !s.labels->done(); s.labels->next()) {
		TextShape *a1 = s.labels->cur();
		TextShape *at = new TextShape(*a1);
		at->SetParent(this);
		labels->add(at);
	}
	SetSize(s.GetWidth(), s.GetHeight());
}

DoubleBox::DoubleBox(const NodeShape &s): Box(s) {
	Init();
}

void DoubleBox::Init() {
	labelDescription = "Label";
	separatorLineStyle = GetLineStyle();
	initialHeight = 40;
	labels = new List<TextShape *>;
	SetTextShape();
	AdjustSizes(GetName()->GetString());
}

DoubleBox::~DoubleBox() {
	labels->clear();
	delete labels;
}

void DoubleBox::DrawTextShapes() {
	string oldBackground; 
	Grafport *g = GetGrafport();
	if (GetFillStyle() != FillStyle::UNFILLED) {
		oldBackground = *g->GetBackgroundColor();
		g->SetBackgroundColor(GetFillColor());
	}
	Box::DrawTextShapes();
	int textHeight = GetName()->GetFontHeight();
	int nameHeight = max(GetName()->GetString()->lines(), 2) * textHeight;
	if (nameHeight < GetHeight()) {
		g->SetLineStyle(separatorLineStyle);
		g->DrawLine(GetLeftMost()+1, GetTopMost()+nameHeight, 
			GetRightMost()-1,
			GetTopMost()+nameHeight);
		g->SetLineStyle(GetLineStyle());
	}
	int i = nameHeight;
	for (labels->first(); !labels->done(); labels->next()) {
		i += textHeight;
		if (i < GetHeight())
			labels->cur()->Draw();
	}
	if (GetFillStyle() != FillStyle::UNFILLED)
		g->SetBackgroundColor(&oldBackground);
}

//void DoubleBox::DrawShape() {
//	Box::DrawShape();
//}

//void DoubleBox::SetSize(int w, int h) {
//	Box::SetSize(w, h);
//	CalcPositionLabels();
//}

//void DoubleBox::SetPosition(const Point *pos, bool snap) {
//	Box::SetPosition(pos, snap);
//	CalcPositionLabels();
//}

void DoubleBox::SetFont(XFont *ft) {
	Box::SetFont(ft);
	for (labels->first(); !labels->done(); labels->next())
		labels->cur()->SetFont(ft);
//	CalcPositionLabels();
}

void DoubleBox::SetTextColor(const string *c) {
	Box::SetTextColor(c);
	for (labels->first(); !labels->done(); labels->next())
		labels->cur()->SetColor(c);
}

int DoubleBox::RequiredHeight() {
	int textHeight = GetName()->GetFontHeight();
	int nameHeight = max(GetName()->GetString()->lines(), 2) * textHeight;
	int ht = (nameHeight + textHeight + labels->count()*textHeight);
	return max(ht, initialHeight);
}

void DoubleBox::AdjustSize() {
	int twidth = GetName()->GetWidth();
	for (labels->first(); !labels->done(); labels->next()) {
		int wd = labels->cur()->GetStringWidth();
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

void DoubleBox::CalcPositionLabels() {
	Box::CalcPositionLabels();

	Point pt = *GetPosition();
	int textHeight = GetName()->GetFontHeight();
	// the part for the name is at least two text lines high.
	int nameHeight = max(GetName()->GetString()->lines(), 2) * textHeight;
	pt.y = GetTopMost() + nameHeight/2;
	GetName()->SetPosition(&pt);
	pt.y += nameHeight/2;
	pt.y += (3*textHeight)/4;
	for (labels->first(); !labels->done(); labels->next()) {
		TextShape *t = labels->cur();
		// position and left adjust textshape
		int w = t->GetStringWidth();
		pt.x = GetLeftMost() + w/2 + TEXTMARGIN;
		t->SetPosition(&pt);
		pt.y += textHeight;
	}
	// set index label position.
	pt.x = GetName()->GetPosition()->x + GetWidth() * 5 / 12;
	pt.y = GetName()->GetPosition()->y - nameHeight / 4;
	GetIndexLabel()->SetPosition(&pt);
}

TextShape *DoubleBox::ChooseTextShape(int x, int y) {
	// in first part (of the class name) ?
	int textHeight = GetName()->GetFontHeight();
	int nameHeight = max(GetName()->GetString()->lines(), 2) * textHeight;
	int pos_y = GetTopMost() + nameHeight;
	if (y <= pos_y) {
		if (GetViewer()->IsShowIndexes() && !IsFixedIndexLabel()) {
			if (y <= GetName()->GetPosition()->y &&
		    	    x >= GetName()->GetPosition()->x + GetWidth()/3)
				return GetIndexLabel();
		}
		if (!IsFixedName())
			return GetName();
	}
	// in labels part ??
	pos_y += textHeight/2;
	for (labels->first(); !labels->done(); labels->next()) {
		pos_y += textHeight;
		if ( pos_y >= GetBottomMost() )
			return 0;
		else if (y <= pos_y)
			return labels->cur();
	} 
	if (GetViewer()->IsEditing())
		return 0;
	// somewhere down the list; create a new label.
	TextShape *t = new TextShape(GetView(), GetGrafport(), this);
	t->SetAlignment(TextAlign::LEFT);
	t->SetSequence(labels->count());
	t->SetDescription(&labelDescription);
	t->SetFont(GetName()->GetFont());
	t->SetColor(GetName()->GetColor());
	Undraw();
	labels->add(t);
//	CalcPositionLabels();
	// move text shape to a better position.
	Point pt = *t->GetPosition();
	pt.x += GetWidth()/2 - TEXTMARGIN;
	t->SetPosition(&pt);
	Draw();
	return t;
}

bool DoubleBox::HasTextShape(TextShape *t) const {
	if (Box::HasTextShape(t))
		return True;
	for (labels->first(); !labels->done(); labels->next())
		if (labels->cur() == t)
			return True;
	return False;
}

void DoubleBox::UpdateLabel(const string *s, unsigned n, bool update) {
	if (IsVisible())
		Undraw();
	if (update) {
		if (n > labels->count())
			error("%s, line %d: impl error: "
			  "illegal label nr %d\n", __FILE__, __LINE__, n);
		else if (n == labels->count()) {
			// insert new textshape.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this);
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(n);
			t->SetDescription(&labelDescription);
			t->SetFont(GetName()->GetFont());
			t->SetColor(GetName()->GetColor());
			labels->add(t);
//			CalcPositionLabels();
		}
		if (*s != "")
			// update existing label
			(*labels)[n]->SetString(s);
		else {
			// delete existing label
			unsigned i = labels->count() -1;
			for (unsigned j = n; j < i; j++) {
				const string *nm = (*labels)[j+1]->GetString();
				(*labels)[j]->SetString(nm);
			}
			TextShape *x = (*labels)[i];
			labels->removei(i);
			delete x;
		}
	}
	else {
		if (n > labels->count())
			error("%s, line %d: impl error: "
			  "illegal label nr %d\n", __FILE__, __LINE__, n);
		else if (*s != "") {  
			// insert new label.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this);
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(n);
			t->SetDescription(&labelDescription);
			t->SetFont(GetName()->GetFont());
			t->SetColor(GetName()->GetColor());
			t->SetString(s);
			labels->insert(t, n);
//			CalcPositionLabels();
			for (unsigned i=n+1; i<labels->count(); i++)
				(*labels)[i]->SetSequence(i);
		}
		// ignore empty strings;
	}
	AdjustSizes(s);
	if (IsVisible())
		Draw();
}

void DoubleBox::AdjustSizes(const string *s) {
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

bool DoubleBox::SetAssocSubject(AssocList *al) {
	if ( ! Box::SetAssocSubject(al) )
		return False;
	if (check(GetSubject())) 
		return True;
	SetSubject(0);
	return False;
}

void DoubleBox::SetTextShape() {
	Box::SetTextShape();
	labels->clear();
}

void DoubleBox::SetGrafport(Grafport *g) {
	Box::SetGrafport(g);
	for (labels->first(); !labels->done(); labels->next())
		labels->cur()->SetGrafport(g);
}

void DoubleBox::SetView(ShapeView *v) {
	Box::SetView(v);
	for (labels->first(); !labels->done(); labels->next())
		labels->cur()->SetView(v);
}

bool DoubleBox::HasString(const string *s, bool sens, bool sub) const {
	if (GetName()->HasString(s, sens, sub))
		return True;
	for (labels->first(); !labels->done(); labels->next()) {
		if (labels->cur()->HasString(s, sens, sub))
			return True;
	}
	return False;
}

bool DoubleBox::HasString(const string *s, bool sens, bool sub, 
			List<TextShape *> *list) {
	bool b = GetName()->HasString(s, sens, sub, list);
	List<TextShape *> tmplabels(*labels);
	for (tmplabels.first(); !tmplabels.done(); tmplabels.next())
		b += tmplabels.cur()->HasString(s, sens, sub, list);
	return b;
}

TextShape *DoubleBox::GetLabel(unsigned n) {
        if (check(n < labels->count()))
		return (*labels)[n];
	else
		return 0;
}
