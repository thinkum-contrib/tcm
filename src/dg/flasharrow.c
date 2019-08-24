////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "flasharrow.h"
#include "grafport.h"
#include <math.h>

FlashArrow::FlashArrow(ShapeView *v, Grafport *g, 
		GShape *n1, GShape *n2, List<Point *> *aline, bool Curved): 
			Line(v, g, n1, n2, aline, Curved) {
	SetEnd2(LineEnd::FILLED_ARROW);
}

FlashArrow::FlashArrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): Line(v, g, n1, n2, Curved) {
	SetEnd2(LineEnd::FILLED_ARROW);
}

void FlashArrow::DrawLine(const DPoint *, const DPoint *, int, int) {
	int DISTX = 12;
	int DISTY = 12;
	int FRAC = 8;

	int n = GetLine()->count()/2;
	Point p1 = *(*GetLine())[n-1];
	Point p2 = *(*GetLine())[n];
	Point pos = Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);

	int w = (p2.x - p1.x)/FRAC;
        int h = (p2.y - p1.y)/FRAC;
	pos.x += w;
	pos.y += h;

	int wd = pos.x-p1.x;
	int ht = pos.y-p1.y;

	double alpha;
	if (wd != 0)
		alpha = -atan((double)ht/(double)wd);
	else
		alpha = -2*atan(1);
	double extrax = (DISTX * sin(alpha));
	double extray = (DISTY * cos(alpha));
	Point pt1, pt2, pt3, pt4;
	pt1.x = pos.x + (int)extrax;
	pt1.y = pos.y + (int)extray;
	pt2.x = pos.x - (int)extrax;
	pt2.y = pos.y - (int)extray;
	pt3.x = pos.x - (int)extray;
	pt3.y = pos.y + (int)extrax;
	pt4.x = pos.x + (int)extray;
	pt4.y = pos.y - (int)extrax;

	DrawLinePart();
	// draw the flash.
	GetGrafport()->DrawLine(pt1.x, pt1.y, pt2.x, pt2.y);
	GetGrafport()->DrawLine(pt1.x, pt1.y, pt3.x, pt3.y);
	GetGrafport()->DrawLine(pt2.x, pt2.y, pt4.x, pt4.y);
	GetGrafport()->DrawPoint(pt1.x, pt1.y);
	GetGrafport()->DrawPoint(pt2.x, pt2.y);
	GetGrafport()->DrawPoint(pt3.x, pt3.y);
	GetGrafport()->DrawPoint(pt4.x, pt4.y);
	int d1 = (p1.x-pt3.x)*(p1.x-pt3.x) + (p1.y-pt3.y)*(p1.y-pt3.y);
	int d2 = (p1.x-pt4.x)*(p1.x-pt4.x) + (p1.y-pt4.y)*(p1.y-pt4.y);
	if (d1<d2) {
		GetGrafport()->DrawLine(p1.x, p1.y, pt3.x, pt3.y);
		GetGrafport()->DrawLine(p2.x, p2.y, pt4.x, pt4.y);
	}
	else {
		GetGrafport()->DrawLine(p1.x, p1.y, pt4.x, pt4.y);
		GetGrafport()->DrawLine(p2.x, p2.y, pt3.x, pt3.y);
	}
}

void FlashArrow::DrawBezier(const DPoint *ep1, const DPoint *ep2) {
	DrawLine(ep1, ep2, 1, 0);
}
 
void FlashArrow::DrawLinePart() {
	unsigned n = GetLine()->count()/2 - 1;
	for (unsigned i=0;i<GetLine()->count()-1;i++) {
		if (i == n)
			continue;
		Point p1 = *(*GetLine())[i];
		Point p2 = *(*GetLine())[i+1];
		GetGrafport()->DrawLine(p1.x, p1.y, p2.x, p2.y);
		GetGrafport()->DrawPoint(p2.x, p2.y);
	}
}
