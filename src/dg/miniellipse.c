////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "miniellipse.h"

MiniEllipse::MiniEllipse(ShapeView *v, Grafport *g, double x, double y)
	:Ellipse(v, g, x, y)
{
	Init();
}

MiniEllipse::MiniEllipse(const MiniEllipse &c): Ellipse(c) {
	namePosition = c.namePosition;
	CalcPositionName();
}

MiniEllipse::MiniEllipse(const NodeShape &c): Ellipse(c) {
        Init();
}
 
void MiniEllipse::Init() {
	SetSize(MIN_WIDTH, MIN_HEIGHT);
	namePosition = CENTER;
        NodeShape::SetResizable(False);
        SetHandles(MIN_HANDLES);
        SetFixedName(True);
        SetFixedIndexLabel(True);
        Point pt(*GetPosition());
        Ellipse::SetPosition(&pt);
}

void MiniEllipse::CalcPositionName() {
        Point pt;
	int th = GetName()->GetHeight();
	int tw = GetName()->GetWidth();
	if (namePosition == TOP) {
        	pt.x = GetPosition()->x;
		pt.y = GetTopLeft()->y - th/2;
	}
	else if (namePosition == BOTTOM) {
        	pt.x = GetPosition()->x;
		pt.y = GetTopLeft()->y + GetHeight() + th/2;
	}
	else if (namePosition == LEFT) {
        	pt.x = GetTopLeft()->x - tw/2 - 2;
		pt.y = GetPosition()->y;
	}
	else if (namePosition == RIGHT) {
        	pt.x = GetTopLeft()->x + GetWidth() + tw/2 + 2;
		pt.y = GetPosition()->y;
	}
	else {
		pt.x = GetPosition()->x;
		pt.y = GetPosition()->y;
	}
        GetName()->SetPosition(&pt);
}

void MiniEllipse::SetPosition(const Point *p, bool snap) {
        Ellipse::SetPosition(p, snap);
        CalcPositionName();
}

void MiniEllipse::SetFont(XFont *ft) {
        Ellipse::SetFont(ft);
        CalcPositionName();
}
 
void MiniEllipse::SetAlignment(TextAlign::Type al) {
        Ellipse::SetAlignment(al);
        CalcPositionName();
}
 
void MiniEllipse::SetName(const string *s) {
        GetName()->SetString(s);
        CalcPositionName();
}

void MiniEllipse::SetTextShape() {
        Ellipse::SetTextShape();
        CalcPositionName();
}

void MiniEllipse::SetSize(int w, int h) {
        Ellipse::SetSize(w, h);
        CalcPositionName();
}
