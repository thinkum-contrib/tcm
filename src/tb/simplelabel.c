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
#include "rectangle.h"
#include "grafport.h"
#include "simplelabel.h"

const int SimpleLabel::MIN_TEXT_WIDTH = 20;
const int SimpleLabel::MIN_TEXT_HEIGHT = 20;

SimpleLabel::SimpleLabel(Grafport *g, XFont *ft) {
	text = "";
	width = 0;
	height = 0;
	grafport = g;
	font = ft;
}

SimpleLabel::SimpleLabel(const SimpleLabel &t) {
	width = t.width;
	height = t.height;
	position = t.position;
	topLeft = t.topLeft;
	text = t.text;
	grafport = t.grafport;
	font = t.font;
}

SimpleLabel::~SimpleLabel() { }

int operator==(const SimpleLabel &t1, const SimpleLabel &t2) {
	return strcmp((t1.text).getstr(),(t2.text).getstr());
}

void SimpleLabel::Undraw() {
	Draw();
}

void SimpleLabel::DrawOutLine(const Point *center) {
	int x = center->x - width / 2;
	int y = center->y - height / 2;
	int wd = max(width, MIN_TEXT_WIDTH);
	int ht = max(height, MIN_TEXT_HEIGHT);
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	grafport->DrawRectangle(x, y, wd, ht);
}


void SimpleLabel::UpdatePosition(const Point *pt) {
	Undraw();
	SetPosition(pt);
	Draw();
}

void SimpleLabel::UpdateText(const string *s) {
	Undraw();
	SetText(s);
	Draw();
}

void SimpleLabel::UpdateFont(XFont *ft) {
	Undraw();
	SetFont(ft);
	Draw();
}

void SimpleLabel::SetPosition(const Point *pos) {
	position.x = pos->x;
	position.y = pos->y;
	topLeft.x = position.x - width / 2;
	topLeft.y = position.y - height / 2;
	PositiveCoord();
}

void SimpleLabel::SetFont(XFont *ft) {
	font = ft;
	CalcSize();
}

void SimpleLabel::SetText(const string *s) {
	text = *s;
	CalcSize();
}

void SimpleLabel::CalcSize() {
	int w, h;
	font->Box(&text, w, h);
	SetSize(w, h);
}

bool SimpleLabel::HitText(int x, int y) {
	if (text.length() == 0)
		return False;
	else {
		int dist = 5;
		int tx = topLeft.x - dist;
		int ty = topLeft.y - dist;
		int w = max(width, MIN_TEXT_WIDTH) + 2*dist;
		int h = max(height, MIN_TEXT_HEIGHT) + 2*dist;
		Rectangle rect(tx, ty, w, h);
		return rect.Inside(x, y);
	}
}

void SimpleLabel::SetSize(int w, int h) {
	width = w;
	height = h;
	PositiveCoord();
	topLeft.x = position.x - width/2;
	topLeft.y = position.y - height/2;
}
 
void SimpleLabel::PositiveCoord() {
	int delta;
	delta = topLeft.x;
	if (delta < 0) {
		Point pt = position;
		pt.x += -delta;
		SetPosition(&pt);
	}
	delta = topLeft.y;
	if (delta < 0) {
		Point pt = position;
		pt.y += -delta;
		SetPosition(&pt);
	}
}
