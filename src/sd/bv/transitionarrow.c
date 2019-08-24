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
#include <math.h>
#include <stdlib.h>
#include "transition.h"
#include "transitionarrow.h"
#include "diagramviewer.h"
 
const int TransitionArrow::HLINELEN = 20;
const int TransitionArrow::HLINEXOFFSET = 4;
const int TransitionArrow::HLINEYOFFSET = 2;
const int TransitionArrow::HLINEDIST = 10;

TransitionArrow::TransitionArrow(ShapeView *v, Grafport *g, 
		GShape *node1, GShape *node2, List<Point *> *aline, bool Curved): 
			Line(v, g, node1, node2, aline, Curved) {
	event = new TextShape(v, g, this);
	event->SetAlignment(TextAlign::LEFT);
	event->SetDescription("Event");
	actions = new List<TextShape *>;
	separator = RIGHT;
	CalcPosition();
	SetEnd2(LineEnd::FILLED_ARROW);
}

TransitionArrow::TransitionArrow(ShapeView *v, Grafport *g, GShape *node1, 
	GShape *node2, bool Curved): Line(v, g, node1, node2, Curved) {
	event = new TextShape(v, g, this);
	event->SetAlignment(TextAlign::LEFT);
	event->SetDescription("Event");
	actions = new List<TextShape *>;
	separator = RIGHT;
	SetEnd2(LineEnd::FILLED_ARROW);
}

TransitionArrow::TransitionArrow(const TransitionArrow &aline): Line(aline) {
	hlineFrom = aline.hlineFrom;
	hlineTo = aline.hlineTo;
	anchorPoint = aline.anchorPoint;
	separator = aline.separator;
	event = new TextShape(*(TextShape *)(aline.event));
	event->SetParent(this);
	actions = new List<TextShape *>;
	for (aline.actions->first(); !aline.actions->done(); aline.actions->next()) {
		TextShape *a = aline.actions->cur();
		TextShape *b = new TextShape (*a);
		b->SetParent(this);
		actions->add(b);
	}
}

TransitionArrow::~TransitionArrow() {
	delete event;
	actions->clear();
	delete actions;
}

void TransitionArrow::DrawShape() {
	Line::DrawShape();
	event->Draw();
	SetDrawAttributes();
	GetGrafport()->DrawLine(hlineFrom.x, hlineFrom.y, hlineTo.x, hlineTo.y);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->Draw();
}

void TransitionArrow::UpdateAnchor(const Point *p, const Point *t) {
	Point pt = anchorPoint;
	if (IsCurved()) {
		pt.y += p->y;
		pt.x += p->x;
	}
	else if (separator == LEFT || separator == RIGHT) {
		// find segment where the anchor point is located.
		// (void) GetLine(pt.x, pt.y);
		pt.y += p->y;
		// shift left <-> RIGHT ?
		Point dp = *t + *p;
		if (dp.x < anchorPoint.x)
			separator = LEFT;
		else
			separator = RIGHT;
	}
	else { 
		pt.x += p->x;
		// shift up <-> down ?
		Point dp = *t + *p;
		if (dp.y < anchorPoint.y)
			separator = UP;
		else
			separator = DOWN;
	}
	Undraw();
	if (IsCurved())
		anchorPoint = pt;
	else if (separator == LEFT || separator == RIGHT) {
		int cx, cy;
		// make anchorpoint a point on the line.
		(void) ContainsPtLine(pt.x, pt.y, 
			(*GetLine())[GetLineNumber()-1], 
			(*GetLine())[GetLineNumber()], cx, cy);
		anchorPoint = Point(cx, cy);
	}
	else
		anchorPoint = pt;
	CalcHLinePart();
	Draw();
}

void TransitionArrow::CalcPosition() {
	Line::CalcPosition();
	anchorPoint = *GetPosition();
	CalcSeparator();
	CalcHLinePart();
}

void TransitionArrow::CalcHLinePart() {
	CalcPositionHLine();
	CalcPositionEvent();
	CalcPositionActions();
}

void TransitionArrow::CalcSeparator() {
	double alpha;
	if (GetWidth() != 0)
		alpha = atan((double)GetHeight()/(double)GetWidth());
	else
		alpha = 2*atan(1);
	// estimation.
	// if (fabs(alpha) > 0.5*atan(1)) { 
	if (fabs(alpha) > atan(1)) { 
		if (separator == UP || separator == DOWN)
			separator = RIGHT;
	}
	else {
		if (separator == LEFT || separator == RIGHT)
			separator = UP;
	}
}


void TransitionArrow::CalcPositionHLine() {
	int d1 = HLineLength();
	if (separator == RIGHT) { // attach right to line.
		hlineFrom = anchorPoint;
		hlineTo = Point(hlineFrom.x + d1, hlineFrom.y);
	}
	else if (separator == LEFT) { // attach left to line.
		hlineTo = anchorPoint;
		hlineFrom = Point(hlineTo.x - d1, hlineTo.y);
	}
	else { // put above/below the line.
		double alpha = atan((double)GetHeight()/(double)GetWidth());

		if (separator == UP) {
			int d2 = (int)(cos(alpha)*max(HLINEDIST,
				 HLINEYOFFSET+actions->count()*GetName()->GetFontHeight()));
			d2 += HLINEYOFFSET;
			hlineFrom = Point(anchorPoint.x - d1/2, 
				anchorPoint.y - d2);
			hlineTo = Point(anchorPoint.x + d1/2, 
				anchorPoint.y - d2);
		}
		else { // separator == DOWN
			int textHeight = max(GetName()->GetFontHeight(), 
						event->GetStringHeight());
			int d2 = (int)(cos(alpha)*max(HLINEDIST,HLINEYOFFSET+
					textHeight));
			d2 += HLINEYOFFSET;
			hlineFrom = Point(anchorPoint.x - d1/2, 
				anchorPoint.y + d2);
			hlineTo = Point(anchorPoint.x + d1/2, 
				anchorPoint.y + d2);
		}
	}
	hlineFrom = Point(max(3,hlineFrom.x), max(3,hlineFrom.y)); 
	hlineTo = Point(max(3,hlineTo.x), max(3,hlineTo.y)); 
}

void TransitionArrow::CalcPositionEvent() {
	Point pt;
	const string *s = event->GetString();
	if (*s != "") {
		pt.x = hlineFrom.x + event->GetStringWidth()/2;
		pt.y = hlineFrom.y - event->GetStringHeight()/2;
		pt.y -= 2*HLINEYOFFSET;
	}
	else {
		pt.x = (hlineFrom.x + hlineTo.x)/2;
		pt.y = hlineFrom.y - event->GetFontHeight()/2;
	}
	pt.x += HLINEXOFFSET;
	event->SetPosition(&pt);
}

void TransitionArrow::CalcPositionActions() {
	Point pt; int w, h;
	int textHeight = GetName()->GetFontHeight();
	pt = hlineFrom;
	pt.y += HLINEYOFFSET + textHeight/2;
	for (actions->first(); !actions->done(); actions->next()) {
		w = actions->cur()->GetStringWidth();
		h = actions->cur()->GetStringHeight();
		pt.x = hlineFrom.x + w/2 + HLINEXOFFSET;
		actions->cur()->SetPosition(&pt);
		pt.y += textHeight;
	}
}

void TransitionArrow::UpdateEvent(const string *c) {
	if (IsVisible())
		Undraw();
	event->SetString(c);
	CalcHLinePart();
	if (IsVisible())
		Draw();
}

void TransitionArrow::UpdateAction(const string *s, unsigned n, bool update) {
	if (IsVisible())
		Undraw();
	SetAction(s, n, update);
	CalcHLinePart();
	if (IsVisible())
		Draw();
}

void TransitionArrow::SetSelect(bool set) {
	Line::SetSelect(set);
}

bool TransitionArrow::ContainsPt(int x, int y) {
	if (Line::ContainsPt(x,y))
		return True;
	else
		return HitHLine(x, y);
}

bool TransitionArrow::HitHLine(int x, int y) {
	// point near horizontal line ?
	int textHeight = GetName()->GetFontHeight();
	return (x >= hlineFrom.x && x <= hlineTo.x &&
		y >= hlineFrom.y - textHeight &&
		y <= hlineFrom.y + textHeight);
}

int TransitionArrow::HLineLength() {
	int max = HLINELEN;
	int n = event->GetStringWidth()+HLINEXOFFSET;
	if (n > max)
		max = n;
	for (actions->first(); !actions->done(); actions->next()) {
		n = actions->cur()->GetStringWidth()+HLINEXOFFSET;
		if (n > max)
			max = n;
	}
	return max;
}

bool TransitionArrow::InTextArea(int x, int y) {
	if (Line::InTextArea(x,y))
		return True;
	else if (event->ContainsPt(x, y))
		return True;
	for (actions->first(); !actions->done(); actions->next()) {
		if (actions->cur()->ContainsPt(x, y))
			return True;
	}
	return False;
}

TextShape *TransitionArrow::HitTextShape(int x, int y) {
	if (event->ContainsPt(x, y))
		return event;
	for (actions->first(); !actions->done(); actions->next()) {
		 if (actions->cur()->ContainsPt(x, y))
			return actions->cur();
	} 
	return 0;
}

TextShape *TransitionArrow::ChooseTextShape(int x, int y) {
	// This is the winner of the "clumsiest function award".
	int textHeight = GetName()->GetFontHeight();
	// hit event string.
	if (event->ContainsPt(x, y))
		return event;
	// hit action string.
	if (actions->first()) {
		// action text shapes can overlap
		// make sure that you choose the right one.
		do {
			int pt_y = actions->cur()->GetTopMost();
			pt_y += textHeight;
			if (actions->cur()->ContainsPt(x,y) && y <= pt_y) {
				// return the action.
				TextShape *t = actions->cur();
				return t;
			}
			// pt_y += textHeight;
		} while (actions->next());
		if (actions->last()) {
			if (actions->cur()->ContainsPt(x,y))
				return actions->cur();
		}
	}
	// hit hline part ?
	if (HitHLine(x, y)) {
		if (y <= hlineFrom.y) {
			// above line -> return event.
			Point pt = *event->GetPosition();
			pt.x -= HLINEXOFFSET;
			pt.y -= 2*HLINEYOFFSET;
			event->UpdatePosition(&pt);
			return event;
		}
		else {
			// if there are actions return the first one.
			if (actions->count() > 0) {
				// return the first action.
				TextShape *t = (*actions)[0];
				return t;
			}
			// create a new action.
			else {
				TextShape *t = new TextShape(
					GetView(), GetGrafport(), this);
				t->SetAlignment(TextAlign::LEFT);
				t->SetSequence(0);
				t->SetDescription("Action");
				t->SetFont(GetName()->GetFont());
				actions->add(t);
				CalcPositionActions();
				// move the action a bit up.
				Point pt = *t->GetPosition();
				pt.x = (hlineFrom.x + hlineTo.x)/2;
				pt.y -= HLINEYOFFSET;
				t->SetPosition(&pt);
				return t;
			}
		}
	}
	// hit some spot on line (but not the hline or a label).
	// Recalculate hline position.
	if (GetViewer()->IsEditing() && GetViewer()->IsInlineEdit())
		return 0;
	Point *pt1, *pt2;
	int xx, yy;
	if (!GetLine()->first())
		return 0;
	else
		pt1 = GetLine()->cur();
	SetLineNumber(1);
	while (GetLine()->next()) {
		pt2 = GetLine()->cur();
		if (ContainsPtLine(x, y, pt1, pt2, xx, yy))
			break; 
		pt1 = pt2;
		if (GetLineNumber() < GetLine()->count()-1)
			SetLineNumber(GetLineNumber()+1);
	}
	UpdatePosition();
	// hit (empty ?) event string.
	if (y <= hlineFrom.y) {
		return event;
	}
	else {
		if (actions->count() > 0) {
			// return last action.
			TextShape *t = (*actions)[actions->count()-1];
			return t;
		}
		else {
			// create new action.
			TextShape *t = new TextShape(
				GetView(), GetGrafport(), this);
			t->SetDescription("Action");
			t->SetAlignment(TextAlign::LEFT);
			t->SetSequence(0);
			t->SetFont(GetName()->GetFont());
			actions->add(t);
			CalcPositionActions();
			Point pt = *t->GetPosition();
			pt.x = (hlineFrom.x + hlineTo.x)/2;
			pt.y -= HLINEYOFFSET;
			t->SetPosition(&pt);
			return t;
		}
	}
}

bool TransitionArrow::HasTextShape(TextShape *t) const {
	if (Line::HasTextShape(t))
		return True;
	else if (event == t)
		return True;
	for (actions->first(); !actions->done(); actions->next())
		if (actions->cur() == t)
			return True;
	return False;
}


int TransitionArrow::GetLeftMost() const {
	int a = Line::GetLeftMost();
	int b = event->GetLeftMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int c = actions->cur()->GetLeftMost();
		if (c < b)
			b = c;
	}
	return min(a, b);
}

int TransitionArrow::GetTopMost() const {
	int a = Line::GetTopMost();
	int b = event->GetTopMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int c = actions->cur()->GetTopMost();
		if (c < b)
			b = c;
	}
	return min(a, b);
}

int TransitionArrow::GetRightMost() const {
	int a = Line::GetRightMost();
	int b = event->GetRightMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int c = actions->cur()->GetRightMost();
		if (c > b)
			b = c;
	} 
	return max(a, b);
}

int TransitionArrow::GetBottomMost() const {
	int a = Line::GetBottomMost();
	int b = event->GetBottomMost();
	for (actions->first(); !actions->done(); actions->next()) {
		int c = actions->cur()->GetBottomMost();
		if (c > b)
			b = c;
	} 
	return max(a, b);
}

const char *TransitionArrow::Sep2String(SepType sep) {
	if (sep == LEFT)
		return "Left";
	else if (sep == RIGHT)
		return "Right";
	else if (sep == UP)
		return "Up";
	else // (sep == DOWN)
		return "Down";
}

TransitionArrow::SepType TransitionArrow::String2Sep(const string *s) {
	if (*s %= "Left")
		return LEFT;
	else if (*s %= "Right")
		return RIGHT;
	else if (*s %= "Up")
		return UP;
	else // (*s %= "Down")
		return DOWN;
}

void TransitionArrow::WriteMembers(OutputFile *ofile) {
	Line::WriteMembers(ofile);
	(*ofile) << "\t{ AnchorPoint " << anchorPoint << " }\n";
	(*ofile) << "\t{ Separator " << Sep2String(separator) << " }\n";
	(*ofile) << "\t{ LineNumber " << GetLineNumber() << " }\n";
}

bool TransitionArrow::ReadMembers(InputFile *ifile, double format) {
	string val1, val2;
	if (!Line::ReadMembers(ifile, format))
		return False;
	if (format <= 1.10) {
		if (!ifile->ReadAttribute2("HLineFrom", &val1, &val2))
			return False;
		hlineFrom = Point(val1.toint(), val2.toint());
		if (!ifile->ReadAttribute2("HLineTo", &val1, &val2))
			return False;
		hlineTo = Point(val1.toint(), val2.toint());
	}
	else { // (format >= 1.11)
		if (!ifile->ReadAttribute2("AnchorPoint", &val1, &val2))
			return False;
		anchorPoint = Point(val1.toint(), val2.toint());
		if (!ifile->ReadAttribute("Separator", &val1))
			return False;
		separator = String2Sep(&val1);
		if (!ifile->ReadAttribute("LineNumber", &val1))
			return False;
		SetLineNumber(val1.toint());
	}
	return True;
}

bool TransitionArrow::SetAssocSubject(AssocList *al) {
	if (!Line::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
		  GetSubject()->GetClassType() == Code::TRANSITION))
		return True;
	SetSubject(0);
	return False;
}

void TransitionArrow::SetTextShape() {
	int n = GetLineNumber(); // line number has to stay unaltered.
	Line::SetTextShape();
	SetLineNumber(max(1, min(n, GetLine()->count()-1)));
	if (check(GetSubject() && GetSubject()->GetClassType() == Code::TRANSITION))
		event->SetString(((Transition *)GetSubject())->GetEvent());
	event->SetParent(this);
	actions->clear();
	if (!check(GetSubject()))
		return;
	unsigned numItems = ((Transition *)GetSubject())->NrActions();
	for (unsigned i=0; i<numItems; i++) {
		TextShape *t = new TextShape(GetView(), GetGrafport(), this);
		t->SetDescription("Action");
		t->SetFont(GetName()->GetFont());
		t->SetAlignment(TextAlign::LEFT);
		t->SetSequence(i);
		t->SetString(((Transition *)GetSubject())->GetAction(i));
		t->SetParent(this);
		actions->add(t);
	}
	CalcHLinePart();
}

void TransitionArrow::SetGrafport(Grafport *g) {
	Line::SetGrafport(g);
	for (actions->first(); !actions->done(); actions->next()) 
		actions->cur()->SetGrafport(g);
	event->SetGrafport(g);
}

void TransitionArrow::SetView(ShapeView *v) {
	Line::SetView(v);
	for (actions->first(); !actions->done(); actions->next()) 
		actions->cur()->SetView(v);
	event->SetView(v);
}

void TransitionArrow::SetFont(XFont *ft) {
	Line::SetFont(ft);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetFont(ft);
	event->SetFont(ft);
	CalcHLinePart();
}

void TransitionArrow::SetTextColor(const string *c) {
	Line::SetTextColor(c);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->SetColor(c);
	event->SetColor(c);
}

void TransitionArrow::SetAction(const string *s, unsigned n, bool update) {
	if (update) {
		if (n > actions->count())
			error("%s, line %d: impl error: "
			  "illegal action nr %d\n", __FILE__, __LINE__, n);
		else if (n == actions->count()) {
			// insert new action.
			TextShape *t = new TextShape(GetView(), GetGrafport(), this);
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
			TextShape *t = new TextShape(GetView(), GetGrafport(), this);
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

bool TransitionArrow::HasString(const string *s, bool sens, bool sub) const {
	if (*s != "" && event->HasString(s, sens, sub))
		return True;
	for (actions->first(); !actions->done(); actions->next()) {
		if (actions->cur()->HasString(s, sens, sub))
			return True;
	}
	return False;
}

bool TransitionArrow::HasString(const string *s, bool sens, bool sub, 
			List<TextShape *> *list) {
	if (*s == "")
		return 0;
	bool b = event->HasString(s, sens, sub, list);
	List<TextShape *> actions2 (*actions);
	for (actions2.first(); !actions2.done(); actions2.next())
		b += actions2.cur()->HasString(s, sens, sub, list);
	return b;
}

void TransitionArrow::MoveRaw(const Point *delta) {
	Line::MoveRaw(delta);
	for (actions->first(); !actions->done(); actions->next())
		actions->cur()->Move(delta);
	event->Move(delta);
	anchorPoint = anchorPoint+*delta;
	CalcPositionHLine();
}
