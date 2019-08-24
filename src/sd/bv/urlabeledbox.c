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
#include "urlabeledbox.h"
#include "grafport.h"
#include "psprocess.h"

URLabeledBox::URLabeledBox(ShapeView *v, Grafport *g, 
		double x, double y): Box(v, g, x, y) {
	urLabel = new TextShape(v, g, this);
	urLabel->SetDescription("Process Operator");
	urLabel->SetOneLine(True);
//	CalcPositionLabels();
}
 
URLabeledBox::URLabeledBox(const URLabeledBox &c): Box(c) {
	urLabel = new TextShape(*(c.urLabel));
	urLabel->SetParent(this);
//	CalcPositionLabels();
}
 
URLabeledBox::~URLabeledBox() {
	delete urLabel;
}
 
//void URLabeledBox::SetPosition(const Point *p, bool b) {
//	Box::SetPosition(p, b);
//	CalcPositionLabels();
//}
 
//void URLabeledBox::SetSize(int w, int h) {
//	Box::SetSize(w, h);
//	CalcPositionLabels();
//}

void URLabeledBox::SetFont(XFont *ft) {
	Box::SetFont(ft);
	urLabel->SetFont(ft);
//	CalcPositionLabels();
}
 
void URLabeledBox::SetTextColor(const string *c) {
	Box::SetTextColor(c);
	urLabel->SetColor(c);
}
 
void URLabeledBox::CalcPositionLabels() {
	Box::CalcPositionLabels();

	Point pt;
	pt.x = static_cast <int> (0.5 + GetPosition()->x + GetWidth()*(5/12.0));
	pt.y = static_cast <int> (0.5 + GetPosition()->y - GetHeight()*(1/3.0));
	urLabel->SetPosition(&pt);
	pt.y = static_cast <int> (0.5 + GetPosition()->y + GetHeight()*(1/3.0));
	GetIndexLabel()->SetPosition(&pt);
}
 
TextShape *URLabeledBox::ChooseTextShape(int x, int y) {
	if (x >= GetPosition()->x + GetWidth()*(5/12.0) - 5 && 
	    y <= GetPosition()->y - GetHeight()*(1/3.0) + 5)
		return urLabel;
	else
		return GetName();
}
 
bool URLabeledBox::HasTextShape(TextShape *t) const {
	return (t == GetName() || t == urLabel);
}

void URLabeledBox::UpdateURLabel(const string *s) {
	if (IsVisible())
		Undraw();
	char c = (*s)[0];
	if (s->length() <= 1) {
		// remove single space.
		string empty("");
		if (c == ' ')
			urLabel->SetString(&empty);
		else
			urLabel->SetString(s);
	}
	else
	{	// chop off.
		string l;
		if (c != ' ')
			l.add(c);
		urLabel->SetString(&l);
	}
	if (IsVisible())
		Draw();
}
 
void URLabeledBox::DrawShape() {
	Box::DrawShape();
	const Point *pt = urLabel->GetPosition();
	char c = (*urLabel->GetString())[0];
	if (c == 'o' || c == '0' || c == 'O')
		GetGrafport()->DrawEllipse(pt->x-3, pt->y-3, 6, 6);
	else if (c == '*') {
		GetGrafport()->DrawLine(pt->x-3, pt->y, pt->x+3, pt->y);
		GetGrafport()->DrawLine(pt->x, pt->y-3, pt->x, pt->y+3);
		GetGrafport()->DrawLine(pt->x-2, pt->y-2, pt->x+2, pt->y+2);
		GetGrafport()->DrawLine(pt->x-2, pt->y+2, pt->x+2, pt->y-2);
	}
	else
		urLabel->Draw();
}

 
bool URLabeledBox::SetAssocSubject(AssocList *al) {
	if (!Box::SetAssocSubject(al))
		return False;
	if (check(GetSubject() && 
		  GetSubject()->GetClassType() == Code::PS_PROCESS))
		return True;
	SetSubject(0);
	return False;
}

void URLabeledBox::SetTextShape() {
	Box::SetTextShape();
	// set position of top label.
	char c = ' ';
	if (check(GetSubject() && 
		  GetSubject()->GetClassType() == Code::PS_PROCESS))
		c = ((PSProcess *)GetSubject())->GetOperator();
	string s;
	if (c != ' ')
		s.add(c);
	urLabel->SetString(&s);
	urLabel->SetParent(this);
//	CalcPositionLabels();
//	CalcPositionLabels();
}

void URLabeledBox::SetGrafport(Grafport *g) {
	Box::SetGrafport(g);
	urLabel->SetGrafport(g);
}

void URLabeledBox::SetView(ShapeView *v) {
	Box::SetView(v);
	urLabel->SetView(v);
}
