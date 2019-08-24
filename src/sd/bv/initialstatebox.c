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
#include "inputfile.h"
#include "outputfile.h"
#include "initialstatebox.h"
#include "initialstate.h"
 
const int InitialStateBox::ARROWLEN = 36;
const int InitialStateBox::HLINELEN = 20;
const int InitialStateBox::HLINEXOFFSET = 4;
const int InitialStateBox::HLINEYOFFSET = 0;

InitialStateBox::InitialStateBox(ShapeView *v, Grafport *g, double x, double y)
	:Box(v, g, x, y)
{
	actions = new List<TextShape *>;
	end.SetType(LineEnd::FILLED_ARROW);
	CalcHLinePart();
}

InitialStateBox::InitialStateBox(const InitialStateBox &a): Box(a) {
	hlineFrom = a.hlineFrom;
	hlineTo = a.hlineTo;
	end = a.end;
	anchorPoint = a.anchorPoint;
	actions = new List<TextShape *>;
	for (a.actions->first(); !a.actions->done(); a.actions->next()) {
		TextShape *a1 = a.actions->cur();
		TextShape *at = new TextShape(*a1);
		at->SetParent(this);
		actions->add(at);
	} 
}

InitialStateBox::~InitialStateBox() {
	actions->clear();
	delete actions;
}
 
void InitialStateBox::DrawShape() {
	Box::DrawShape();
	int textHeight = GetName()->GetFontHeight();
	int len = max(ARROWLEN, 2*textHeight*actions->count());
	DPoint from(GetPosition()->x, GetTopLeft()->y-len);
	DPoint to(GetPosition()->x, GetTopLeft()->y);
	SetDrawAttributes();
	DPoint newPt;
	end.Draw(GetGrafport(), &from, &to, &newPt);
	GetGrafport()->DrawLine(from.x, from.y, newPt.x, newPt.y);
	if (actions->count() > 0 && *(*actions)[0]->GetString() != "") {
		GetGrafport()->DrawLine(hlineFrom.x, hlineFrom.y, hlineTo.x, hlineTo.y);
	}
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->Draw();
}

void InitialStateBox::SetSize(int w, int h) {
	Box::SetSize(w, h);
	CalcHLinePart();
}
 
void InitialStateBox::SetPosition(const Point *pos, bool b) {
	Box::SetPosition(pos, b);
	CalcHLinePart();
}

void InitialStateBox::SetFont(XFont *ft) {
	Box::SetFont(ft);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetFont(ft);
	CalcHLinePart();
}

void InitialStateBox::SetTextColor(const string *c) {
	Box::SetTextColor(c);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetColor(c);
}

TextShape *InitialStateBox::ChooseTextShape(int x, int y) {
	// hit action string?
	for (actions->first(); !actions->done(); actions->next()) {
		if (actions->cur()->ContainsPt(x,y)) {
			TextShape *t = actions->cur();
			return t;
		}
	}
	// hit hline part ?
	if (HitHLine(x, y) || HitVLine(x, y)) {
		if (actions->count() > 0)
			return (*actions)[0];
		else {
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this); 
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(0);
			t->SetDescription("Action");
			t->SetFont(GetName()->GetFont());
			actions->add(t);
			CalcHLinePart();
			// undo adjustment
			Point pt = *t->GetPosition();
			pt.x = (hlineFrom.x + hlineTo.x)/2;
			t->SetPosition(&pt);
			return t;
		}
	}
	// hit name in the box.
	return GetName();
}

bool InitialStateBox::HasTextShape(TextShape *t) const {
	if (Box::HasTextShape(t))
		return True;
	for (actions->first(); !actions->done(); actions->next())
		if (actions->cur() == t)
			return True;
	return False;
}

bool InitialStateBox::ContainsPt(int x, int y) {
	if (Box::ContainsPt(x,y))
		return True;
	if (HitVLine(x, y))
		return True;
	if (HitHLine(x, y))
		return True;
	return False;
}

bool InitialStateBox::HitHLine(int x, int y) {
	// point near horizontal line ?
	int textHeight = GetName()->GetFontHeight();
	return (x >= hlineFrom.x && x <= hlineTo.x &&
		y >= hlineFrom.y - textHeight &&
		y <= hlineFrom.y + textHeight);
}


bool InitialStateBox::HitVLine(int x, int y) {
	// point near vertical arrow or near a textshape?
	int textHeight = GetName()->GetFontHeight();
	int len = max(ARROWLEN, 2*textHeight*actions->count());
	int linewd = GetWidth()/10;
	if ((GetPosition()->x-linewd<= x) && (x <= GetPosition()->x+linewd) &&
		GetTopLeft()->y >= y && y >= GetTopLeft()->y-len)
			return True;
	for (actions->first(); !actions->done(); actions->next()) {
		if (actions->cur()->ContainsPt(x,y))
			return True;
	}
	return False;
}

void InitialStateBox::CalcHLinePart() {
	CalcPositionHLine();
	CalcPositionActions();
}

void InitialStateBox::CalcPositionHLine() {
	int d1 = HLineLength();
	int textHeight = GetName()->GetFontHeight();
	anchorPoint.x = GetPosition()->x;
	if (actions->count() == 0 || *(*actions)[0]->GetString() == "")
		anchorPoint.y = GetTopLeft()->y-ARROWLEN;
	else {
		int len = max(ARROWLEN, 2*textHeight*actions->count());
		anchorPoint.y = GetTopLeft()->y-3*len/4;
	}
	hlineFrom = anchorPoint;
	hlineTo = Point(hlineFrom.x + d1, hlineFrom.y);
	hlineFrom = Point(max(3,hlineFrom.x), max(3,hlineFrom.y)); 
	hlineTo = Point(max(3,hlineTo.x), max(3,hlineTo.y)); 
}

int InitialStateBox::HLineLength() {
	int max = HLINELEN;
	for (actions->first(); !actions->done(); actions->next()) {
		int n = actions->cur()->GetWidth()+HLINEXOFFSET;
		if (n > max)
			max = n;
	}
	return max;
}

void InitialStateBox::CalcPositionActions() {
	Point pt; int w, h;
	pt = hlineFrom;
	int textHeight = GetName()->GetFontHeight();
	pt.y += 2*HLINEYOFFSET + textHeight/2;
	for (actions->first(); !actions->done(); actions->next()) {
		w = actions->cur()->GetWidth();
		h = actions->cur()->GetHeight();
		pt.x = hlineFrom.x + w/2 + HLINEXOFFSET;
		actions->cur()->SetPosition(&pt);
		pt.y += textHeight;
	}
}

void InitialStateBox::UpdateAction(const string *s, unsigned n, bool update) {
	if (IsVisible())
		Undraw();
	SetAction(s, n, update);
	CalcHLinePart();
	if (IsVisible())
		Draw();
}

void InitialStateBox::UpdateAnchor(const Point *delta, const Point *) {
	Point pt = anchorPoint;
	pt.y += delta->y;
	if (!ContainsPt(pt.x, pt.y))
		return;
	Undraw();
	anchorPoint = pt;
	CalcHLinePart();
	Draw();
}

int InitialStateBox::GetLeftMost() const {
	int a = Box::GetLeftMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int b = actions->cur()->GetLeftMost();
		a = min(a, b);
	} 
	return a;
}

int InitialStateBox::GetTopMost() const {
	int a = Box::GetTopMost();
	int textHeight = GetName()->GetFontHeight();
	int len = max(ARROWLEN, 2*textHeight*actions->count());
	return a - len;
}

int InitialStateBox::GetRightMost() const {
	int a = Box::GetRightMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int b = actions->cur()->GetRightMost();
		a = max(a, b);
	} 
	return a;
}

bool InitialStateBox::SetAssocSubject(AssocList *al) {
	if (!Box::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && GetSubject()->GetClassType() == Code::INITIAL_STATE))
		return True;
	SetSubject(0);
	return False;
}

void InitialStateBox::SetTextShape() {
	Box::SetTextShape();
	// create the textshape actions.
	actions->clear();
	if (!check(GetSubject() && GetSubject()->GetClassType() == Code::INITIAL_STATE))
		return;
	unsigned numItems = ((InitialState *)GetSubject())->NrActions();
	for (unsigned i=0; i<numItems; i++) {
		TextShape *at = new TextShape(
				GetView(), GetGrafport(), this);
		at->SetDescription("Action");
		at->SetAlignment(TextAlign::LEFT);
		at->SetSequence(i);
		at->SetString(((InitialState *)GetSubject())->GetAction(i));
		at->SetParent(this);
		at->SetFont(GetName()->GetFont());
		actions->add(at);
	}
	CalcHLinePart();
}

void InitialStateBox::WriteMembers(OutputFile *ofile) {
	Box::WriteMembers(ofile);
}

bool InitialStateBox::ReadMembers(InputFile *ifile, double format) {
	string val1, val2;
	if (!Box::ReadMembers(ifile, format))
		return False;
	if (format <= 1.10) {
		if (!ifile->ReadAttribute2("HLineFrom", &val1, &val2))
			return False;
		hlineFrom = Point(val1.toint(), val2.toint());
		if (!ifile->ReadAttribute2("HLineTo", &val1, &val2))
			return False;
		hlineTo = Point(val1.toint(), val2.toint());
	}
	return True;
}

void InitialStateBox::SetGrafport(Grafport *g) {
	Box::SetGrafport(g);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetGrafport(g);
}

void InitialStateBox::SetView(ShapeView *v) {
	Box::SetView(v);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetView(v);
}

void InitialStateBox::SetAction(const string *s, unsigned n, bool update) {
	if (update) {
		if (n > actions->count())
			error("%s, line %d: impl error: "
			  "illegal action nr %d\n", __FILE__, __LINE__, n);
		else if (n == actions->count()) {
			// insert new action.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this);
			t->SetDescription("Action");
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(n);
			t->SetFont(GetName()->GetFont());
			actions->add(t);
		}
		if (*s != "")
			// update existing action
			(*actions)[n]->SetString(s);
		else {
			// delete existing action
			unsigned i = actions->count() -1;
			for (unsigned j = n; j < i; j++) {
				const string *nm = (*actions)[j+1]->GetString();
				(*actions)[j]->SetString(nm);
			}
			TextShape *x = (*actions)[i];
			actions->removei(i);
			delete x;
		}
	}
	else {
		if (n > actions->count())
			error("%s, line %d: impl error: "
			   "illegal action nr %d\n", __FILE__, __LINE__, n);
		else if (*s != "") {
			// insert new action.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this);
			t->SetDescription("Action");
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(n);
			t->SetString(s);
			t->SetFont(GetName()->GetFont());
			actions->insert(t, n);
			for (unsigned i=n+1; i<actions->count(); i++)
				(*actions)[i]->SetSequence(i);
		}
		// ignore empty strings;
	}
}

bool InitialStateBox::HasString(const string *s, bool sens, bool sub) const {
	if (Box::HasString(s, sens, sub))
		return True;
	for (actions->first(); !actions->done(); actions->next()) {
		if (actions->cur()->HasString(s, sens, sub))
			return True;
	}
	return False;
}

bool InitialStateBox::HasString(const string *s, bool sens, bool sub, List<TextShape *> *list) {
	bool b = Box::HasString(s, sens, sub, list);
	List<TextShape *> actions2 (*actions);
	for (actions2.first(); !actions2.done(); actions2.next())
		b += actions2.cur()->HasString(s, sens, sub, list);
	return b;
}
