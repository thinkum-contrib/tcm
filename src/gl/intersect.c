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
#include "intersect.h"
#include <stdlib.h>
#include <math.h>
#include "util.h"

Point Intersect::BoxIntersects(Point from, Point to, int width, int height) {
	Point snp;
	int x = from.x;
	int y = from.y;
	int a = width  / 2;
	int b = height / 2;
	// for calculating rc
	int dx = abs(to.x - x);
	int dy = abs(to.y - y);
	if (dx == 0) {
		snp.x = x;
		snp.y = (y < to.y) ? y + b : y - b;
		return snp;
	}
	if (dy == 0) {
		snp.y = y;
		snp.x = (x < to.x) ? x + a : x - a;
		return snp;
	}
	// dx > 0, dy > 0.
	double rc1 = double(dy) / double(dx);
	double rc2 = 1 / rc1;
	double alpha = double(height) / double(width);
	if (rc1<alpha) {
		// crossing the vertical sides
		dy = int(a * rc1);
		snp.x = (x < to.x) ? x + a : x - a;
		snp.y = (y < to.y) ? y + dy : y - dy;
	} else {
		// crossing the horizontal sides
		dx = int(b * rc2);
		snp.x = (x < to.x) ? x + dx : x - dx;
		snp.y = (y < to.y) ? y + b : y - b;
	}
	return snp;
}

Point Intersect::BoxIntersects(Point from, Point to, int width, int height, 
		int order, int count, int &code) {
	double rc = 0;
	Point snp;
	int x = from.x;
	int y = from.y;
	int a = width / 2;
	int b = height / 2;
	// for calculating rc
	int dx = abs(to.x - x);
	int dy = abs(to.y - y);
	// intervals of crossing points on sides
	// int delta_x = (width  / (count+1)) * order;
	// int delta_y = (height / (count+1)) * order;
	// (now keeping right distance between the lines).
	int delta_x = int(((double)width/count) * (order - 0.5) + 0.5);
	int delta_y = int(((double)height/count) * (order - 0.5) + 0.5);
	// code tells where to cross the sides:
	// when code=0 then alpha(rc) decides
	// when code=1 then horizontal
	// when code>1 then vertical
	if (code == 0 && dx != 0)
		rc = double(dy) / double(dx);
	if ((code==0 && dx!=0 && rc<1) || (code>1)) {
		// crossing the vertical side
		snp.x = (x < to.x) ? x + a : x - a;
		snp.y = (y - b) + delta_y;
		code = 2;
	}
	else if ((code==0 && (dx==0 || rc>=1)) || (code==1)) {
		// crossing the horizontal side
		snp.x = (x - a) + delta_x;
		snp.y = (y < to.y) ? y + b : y - b;
		code = 1;
	}
	return snp;
}

Point Intersect::EllipseIntersects(Point from, Point to, 
				   int width, int height) {
	double alpha, a, b, r;
	Point snp;
	int x = from.x;
	int y = from.y;
	double dx = to.x - x;
	double dy = to.y - y;
	if (dx != 0) {
		alpha = atan(fabs(dy/dx));
		dx = cos(alpha);
		dy = sin(alpha);
		a = width / 2;
		b = height / 2;
		r =  ((dx * dx) / (a * a)) + ((dy * dy) / (b * b));
		r = sqrt( 1 / r);
		dx = r * dx;
		dy = r * dy;
	} else
		dy = height / 2;
	snp.x = (x < to.x) ? x + int(dx) : x - int(dx);
	snp.y = (y < to.y) ? y + int(dy) : y - int(dy);
	return snp;
}
 
Point Intersect::EllipseIntersects(Point from, Point to, int width, int height, 
		int order, int count, int &code) {
	double alpha = 0;
	double x2, y2;
	Point snp;
	int x = from.x;
	int y = from.y;
	double dx = to.x - x;
	double dy = to.y - y;
	// int delta_x = (width  / (count+1)) * order;
	// int delta_y = (height / (count+1)) * order;
	// keeping the right distance between the lines.
	int delta_x = int(((double)width/count) * (order - 0.5) + 0.5);
	int delta_y = int(((double)height/count) * (order - 0.5) + 0.5);
	double a2 = width*width/4;
	double b2 = height*height/4;
	// code tells where to cross the ellipse
	// when code=0 then alpha decides
	// when code=1 then left/right
	// when code>1 then top/bottom
	if (code==0) {
		if (dx != 0)
			alpha = dy/dx;
		else
			alpha = 10;
	}
	if ((code==0&&fabs(alpha)<1) || (code>1)) {
		// distribute over y-axis
		dy = height/2 - delta_y;
		y2 = double(dy*dy);
		dx = sqrt((1.0 - y2/b2)*a2);
		snp.x = (x < to.x) ? x + int(dx) : x - int(dx);
		snp.y = y - int(dy);
		code = 2;
	}
	else if ((code==0 && fabs(alpha)>=1) || (code==1)) {
		// distribute over x-axis
		dx = width/2 - delta_x;
		x2 = double(dx*dx);
		dy = sqrt((1.0 - x2/a2)*b2);
		snp.x = x - int(dx);
		snp.y = (y < to.y) ? y + int(dy) : y - int(dy);
		code = 1;
	}
	return snp;
}

Point Intersect::DiamondIntersects(Point from, Point to, int width, 
		int height) {
	int x1, y1, x2, y2;
	Point snp;
	int x = from.x;
	int y = from.y;
	int dx = to.x - x;
	int dy = to.y - y;
	// special cases are simple
	if (dx == 0) {
		snp.x = to.x;
		snp.y = (y < to.y) ? y + height / 2 : y - height / 2;
		return snp;
	}
	if (dy == 0) {
		snp.y = to.y;
		snp.x = (x < to.x) ? x + width / 2 : x - width / 2;
		return snp;
	}
	// which side of the diamond
	WhichLine(from, width, height, dx, dy, x1, y1, x2, y2);
	return DiamondSnp(to, dx, dy, x1, y1, x2, y2);
}
 
Point Intersect::DiamondIntersects(Point from, Point to, int width, int height, 
		int order, int count, int &code) {
	int x1, y1, x2, y2;
	double rc = 0;
	int x = from.x;
	int y = from.y;
	int a = width/2;
	int b = height/2;
	int dx = to.x - x;
	int dy = to.y - y;
	// int delta_x = (width  / (count+1)) * order;
	// int delta_y = (height / (count+1)) * order;
	// keeping the right distance between the lines.
	int delta_x = int(((double)width / count) * (order - 0.5) + 0.5);
	int delta_y = int(((double)height/ count) * (order - 0.5) + 0.5);
	if (code == 0 && dx != 0)
		rc = double(dy)/double(dx);

	if ((code == 0 && dx != 0 && fabs(rc) < 1) || (code > 1)) {
		y = y - b + delta_y;
		to.y = to.y - b + delta_y;
		dx = to.x - x;
		dy = to.y - y;
		WhichLine3(from, width, height, dx, dy, 
				delta_y, x1, y1, x2, y2);
		count = 2;
	}
	else if ((code==0 && (dx==0 || fabs(rc) >= 1)) || (code==1)) {
		x = x - a + delta_x;
		to.x = to.x - a + delta_x;
		dx = to.x - x;
		dy = to.y - y;
		WhichLine2(from, width, height, dx, dy, 
				delta_x, x1, y1, x2, y2);
		count = 1;
	}
	return DiamondSnp(to, dx, dy, x1, y1, x2, y2);
}

void Intersect::WhichLine(Point from, int width, int height, int dx, int dy, 
		int &x1, int &y1, int &x2, int &y2) {
	if (dx>=0 && dy<=0) {
		x1 = from.x;
		y1 = from.y - height / 2;
		x2 = from.x + width / 2;
		y2 = from.y;
		return;
	}
	if (dx>=0 && dy>=0) {
		x1 = from.x + width / 2;
		y1 = from.y;
		x2 = from.x;
		y2 = from.y + height / 2;
		return;
	}
	if (dx<=0 && dy>=0) {
		x1 = from.x;
		y1 = from.y + height / 2;
		x2 = from.x - width / 2;
		y2 = from.y;
		return;
	}
	if (dx<=0 && dy<=0) {
		x1 = from.x - width / 2;
		y1 = from.y;
		x2 = from.x;
		y2 = from.y - height / 2;
		return;
	}
}

void Intersect::WhichLine2(Point from, int width, int height, int dx, int dy,
		int delta_x, int &x1, int &y1, int &x2, int &y2) {
	double alpha;
	double pi = 4*atan(1);
	double a;
	// calculate alpha
	if (dx != 0)
		alpha = double(abs(dy))/double(dx);
	else 
		alpha = double(abs(dy))/0.00001;
	// calculate a
	int x = -width/2+delta_x;
	int y = height/2;
	if (x != 0)
		a = double(y)/double(-x);
	else
		a = double(y)/0.00001;
	// get angle in radians
	a = atan(a);
	alpha = atan(alpha);
	if (a<0)
		a = pi - fabs(a);
	if (alpha<0)
		alpha = pi - fabs(alpha);
	if ( alpha < a)
		if (dy<0)
			WhichLine(from, width, height, 1,-1, x1, y1, x2, y2);
		else
			WhichLine(from, width, height, 1,1, x1, y1, x2, y2);
	else
		if (dy<0)
			WhichLine(from, width, height, -1,-1, x1, y1, x2, y2);
		else
			WhichLine(from, width, height, -1,1, x1, y1, x2, y2);
}

void Intersect::WhichLine3(Point from, int width, int height, int dx, int dy, 
		int delta_y, int &x1, int &y1, int &x2, int &y2){
	double alpha;
	double a;
	double pi = 4*atan(1);
	// calculate alpha
	if (dy != 0)
		alpha = double(abs(dx))/double(dy);
	else
		alpha = double(abs(dx))/0.01;
	// calculate a
	int x = width/2;
	int y = -height/2+delta_y;
	if (y != 0)
		a = double(x)/double(-y);
	else
		a = double(x)/-0.00001;
	a = atan(a);
	alpha = atan(alpha);
	if (a<0)
		a = pi - fabs(a);
	if (alpha < 0)
		alpha = pi - fabs(alpha);
	if ( alpha < a)
		if (dx<0)
			WhichLine(from, width, height, -1,1, x1, y1, x2, y2);
		else
			WhichLine(from, width, height, 1,1, x1, y1, x2, y2);
	else
		if (dx<0)
			WhichLine(from, width, height, -1,-1, x1, y1, x2, y2);
		else
			WhichLine(from, width, height, 1,-1, x1, y1, x2, y2);
}
 
Point Intersect::DiamondSnp(Point to, int dx, int dy, int x1, int y1, 
			int x2, int y2){
	Point snp;
	double a1, c1;
	// calculate line equation of side of diamond
	double a2;
	if (x2 - x1 != 0) {
		a2 = double(y2-y1)/double(x2-x1);
	}
	else {
		a2 = double(y2-y1)/0.00001;
	}
	double c2 = a2 * x1 - y1;
	// calculate line equation of crossing line
	if (dx != 0) {
		a1 = double(dy)/double(dx);
		c1 = a1 * to.x - to.y;
	} else {
		// calculate crossing point
		snp.x = to.x;
		snp.y = int(a2 * snp.x - c2);
		return snp;
	}
	// calculate crossing point
	double D = -a1 + a2;
	double Dx = -c1 + c2;
	double Dy = a1*c2 - a2*c1;
	snp.x = int(Dx/D);
	snp.y = int(Dy/D);
	return snp;
}

Point Intersect::TriangleIntersects(Point from, Point to, int width, 
		int height) {
	Point snp;
	double w = (double)(width)/2;
	double h = (double)(height)/2;
	double xA = to.x - from.x;
	double yA = to.y - from.y;
	int x = from.x;
	int y = from.y;
	// special cases are simple
	if (xA == 0) {
		snp.x = to.x;
		snp.y = (y < to.y) ? y + (int)h : y - (int)h;
		return snp;
	}
	double D = yA / xA;
	// line 1: y = h
	// line 2: y = -2hx/w - h
	// line 3: y = 2hx/w - h
	// snp 1st line.
	double x1 = 0, y1 = 0;
	if (D != 0) {
		x1 = h / D;
		y1 = h;
	}
	// snp 2nd line.
	double x2 = 0, y2 = 0;
	if (D != -2*h/w) {
		x2 = -h / (D + 2*h/w);
		y2 = D * x2;
	}
	// snp 3th line.
	double x3 = 0, y3 = 0;
	if (D != 2*h/w) {
		x3 = -h / (D - 2*h/w);
		y3 = D * x3;
	}
	bool First = (x1 >= -w && x1 <= w && y1 >= -h && y1 <= h);
	bool Second = (x2 >= -w && x2 <= w && y2 >= -h && y2 <= h);
	bool Third = (x3 >= -w && x3 <= w && y3 >= -h && y3 <= h);
	double d1 = sqrt ( (x1-xA)*(x1-xA) + (y1-yA)*(y1-yA));
	double d2 = sqrt ( (x2-xA)*(x2-xA) + (y2-yA)*(y2-yA));
	double d3 = sqrt ( (x3-xA)*(x3-xA) + (y3-yA)*(y3-yA));
	if (d1 <= d2 && d1 <= d3 && First) {
		snp.x = x + int(x1);
		snp.y = y + int(y1);
	}
	else if (d2 <= d3 && Second) {
		snp.x = x + int(x2);
		snp.y = y + int(y2);
	}
	else if (d1 <= d3 && First) {
		snp.x = x + int(x1);
		snp.y = y + int(y1);
	}
	else if (Third) {
		snp.x = x + int(x3);
		snp.y = y + int(y3);
	}
	else if (d1 <= d2 && First) {
		snp.x = x + int(x1);
		snp.y = y + int(y1);
	}
	else if (Second) {
		snp.x = x + int(x2);
		snp.y = y + int(y2);
	}
	else if (First) {
		snp.x = x + int(x1);
		snp.y = y + int(y1);
	}
	else {
		snp.x = from.x;
		snp.y = from.y;
	}
	return snp;
}
 
Point Intersect::TriangleIntersects(Point from, Point to, int width, 
		int height, int order, int count, int &code) {
	Point pos = from;
        Point p = BoxIntersects(pos, to, width, height, order, count, code);
        if (p.y >= pos.y + height/2)
                // bottom side: a box like distribution.
                return p;
        else {
                // top sides: see it as a halve of a diamond.
                pos.y += height/2;
                Point pt = DiamondIntersects(pos, to, width, 
			height*2, order, count, code);
		if (pt.y > pos.y) {
			pt.y = pos.y;
			if (pt.x > pos.x)
				pt.x = pos.x+width/2;
			else
				pt.x = pos.x-width/2;
		} 
		return pt;
        }
}

Point Intersect::NoteBoxIntersects(Point from, Point to, int width,
                int height) {
        Point snp;
        double x1 = (double) from.x;
        double y1 = (double) from.y;
        double x2 = (double) to.x;
        double y2 = (double) to.y;
        double rico = (y1 - y2) / (x2 - x1);
        double snapx = ((double) width/2 + (double) height/6) / (1.0 + rico);

        snp.x = (int) (x1 + snapx);
        snp.y = (int) (y1 - (rico * snapx));
        return snp;
}
