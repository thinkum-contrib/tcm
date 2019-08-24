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
#include "lineend.h"
#include "lstring.h"
#include "util.h"
#include "grafport.h"
#include <math.h>
#include <stdlib.h>

const int LineEnd::CIRCLE_WIDTH = 12;
const int LineEnd::TRIANGLE_LENGTH = 14;
const int LineEnd::TRIANGLE_WIDTH = 14;
const int LineEnd::DIAMOND_LENGTH = 20;
const int LineEnd::DIAMOND_WIDTH = 14;
const int LineEnd::OPEN_ARROW_LENGTH = 8;
const int LineEnd::OPEN_ARROW_WIDTH = 10;
const int LineEnd::FILLED_ARROW_LENGTH = 10;
const int LineEnd::FILLED_ARROW_ANGLE = 90;
const double LineEnd::FILLED_ARROW_INSET = 0.60;

const TypeName LineEnd::typeNames[] = {
	{EMPTY, "Empty"},
	{OPEN_ARROW, "OpenArrow"},
	{FILLED_ARROW, "FilledArrow"},
	{DOUBLE_OPEN_ARROW, "DoubleOpenArrow"},
	{DOUBLE_FILLED_ARROW, "DoubleFilledArrow"},
	{WHITE_CIRCLE, "WhiteCircle"},
	{BLACK_CIRCLE, "BlackCircle"},
	{WHITE_DIAMOND, "WhiteDiamond"},
	{BLACK_DIAMOND, "BlackDiamond"},
	{WHITE_TRIANGLE, "WhiteTriangle"},
	{BLACK_TRIANGLE, "BlackTriangle"},
	{0, ""}
};

LineEnd::LineEnd() {
	type = EMPTY;
	length = 0;
	width = 0;
}

LineEnd::LineEnd(Type t) {
	SetType(t);
}

void LineEnd::SetType(Type t) {
	type = t;
	SetSizes();
}

void LineEnd::SetSizes() {
	if (type == WHITE_CIRCLE || type == BLACK_CIRCLE)
		length = width = CIRCLE_WIDTH;
	else if (type == WHITE_TRIANGLE || type == BLACK_TRIANGLE) {
		length = TRIANGLE_LENGTH;
		width = TRIANGLE_WIDTH;
	}
	else if (type == WHITE_DIAMOND || type == BLACK_DIAMOND) {
		length = DIAMOND_LENGTH;
		width = DIAMOND_WIDTH;
	}
	else if (type == OPEN_ARROW || type == DOUBLE_OPEN_ARROW) {
		length = OPEN_ARROW_LENGTH;
		width = OPEN_ARROW_WIDTH;
	}
	else if (type == FILLED_ARROW || type == DOUBLE_FILLED_ARROW) {
		length = width = FILLED_ARROW_LENGTH;
	}
	else {
		length = 0;
		width = 0;
	}
}

void LineEnd::SetLength(int l) {
	length=l;
	if (type==WHITE_CIRCLE || type == BLACK_CIRCLE)
		width = l;
}
		
void LineEnd::SetWidth(int w) {
	width = w;
}

void LineEnd::Type2String(LineEnd::Type l, string *s) {
	if (1 <= (int)l && (int)l <= NUMTYPES)
		*s = typeNames[l-1].name;
	else
		*s = "Empty";
}
 
LineEnd::Type LineEnd::String2Type(const string *s) {
	const TypeName *n = &typeNames[0];
        while (n->code != 0) {
                if (*s %= n->name)
                        return (Type) n->code;
                n++;
        }
        return EMPTY;
}

void LineEnd::Draw(Grafport *g, const DPoint *from, 
		const DPoint *to, DPoint *newEnd) {
	*newEnd = *to;
	if (type == EMPTY)
		;
	else if (type == WHITE_CIRCLE)
		DrawCircle(g, from, to, False, newEnd);
	else if (type == BLACK_CIRCLE)
		DrawCircle(g, from, to, True, newEnd);
	else if (type == WHITE_TRIANGLE)
		DrawTriangle(g, from, to, False, newEnd);
	else if (type == BLACK_TRIANGLE)
		DrawTriangle(g, from, to, True, newEnd);
	else if (type == WHITE_DIAMOND)
		DrawDiamond(g, from, to, False, newEnd);
	else if (type == BLACK_DIAMOND)
		DrawDiamond(g, from, to, True, newEnd);
	else if (type == OPEN_ARROW)
		DrawArrowHead(g, from, to, False, 1, newEnd);
	else if (type == DOUBLE_OPEN_ARROW)
		DrawArrowHead(g, from, to, False, 2, newEnd);
	else if (type == FILLED_ARROW)
		DrawArrowHead(g, from, to, True, 1, newEnd);
	else if (type == DOUBLE_FILLED_ARROW)
		DrawArrowHead(g, from, to, True, 2, newEnd);
	else {
		error("%s, line %d: this end type is forgotten\n",
			__FILE__, __LINE__);
	}
}

void LineEnd::DrawArrowHead(Grafport *g, const DPoint *from, 
		const DPoint *to, bool filled, int count,
		DPoint *newEnd) {
	if (filled)
		DrawFilledArrowHead(g, from, to, newEnd);
	else
		DrawOpenArrowHead(g, from, to, newEnd);
	if (count > 1)
		DrawExtraArrowHead(g, from, to, filled, newEnd);
}

void LineEnd::DrawOpenArrowHead(Grafport *g, 
		const DPoint *from, const DPoint *to, DPoint *newEnd) {
	DPoint *points = new DPoint[4];
	CalcDiamond(from, to, length, width, points);
	g->DrawLine(points[0].x, points[0].y, points[1].x, points[1].y);
	g->DrawLine(points[2].x, points[2].y, points[1].x, points[1].y);
	*newEnd = points[1];
	delete points;
}

void LineEnd::DrawFilledArrowHead(Grafport *g, 
		const DPoint *from, const DPoint *to, DPoint *newEnd) {
	DPoint *points = new DPoint[4];
	CalcFilledArrowHead(from, to, length, points);

	g->FillPolygon(points, 4);
//	if (!g->DrawsXor())						
//		g->DrawPolygon(points, 4);				
	*newEnd = points[2];
	delete points;
}


void LineEnd::CalcFilledArrowHead(const DPoint *from, const DPoint *to,
				int ln, DPoint *points) {
	// length of the target line we are drawing arrowhead over.
	double dx, dy, len; 

	// values for rotation needed to get from canonical line to target.
	double sin_theta, cos_theta;
	
	// coordinates and values for canonical arrowhead placed on x axis
	double pt1_x, pt1_y, pt2_x, pt2_y, pt3_x, pt3_y;

	double ah_len = (double)ln;
	double ah_angle = M_PI_4 * ((double)FILLED_ARROW_ANGLE)/180.0; // == 22.5 degrees
	// cos 22.5° = 1.0 / sqrt((4.0 - 2.0 * M_SQRT2))
	// == 0.92387953251128675612818319

	// final arrowhead points transformed to match the line
	double result1_x, result1_y, result2_x, result2_y, result3_x, result3_y;

	// figure out the length of the target line
	dx = to->x - from->x;
	dy = to->y - from->y;
	len = sqrt(dx*dx+dy*dy);

	// bail out now if its zero length (since direction is not determined)
	if (len == 0) 
		return;

	// compute canonical arrow head points (as if on a line on x axis)  //
	//                                                                  //
	//             1                                                    // 
	//              \                                                   //
	//   +-----------2-------0----- x axis --->                         //
	//              /                                                   //
	//             3                                                    //
	//                                                                  //
	// arrowhead is draw as a 4 point polygon (with pt0 at the tip)     //

	pt1_x = len - ah_len*cos(ah_angle);
	pt1_y = ah_len*sin(ah_angle);
	pt2_x = len - (len-pt1_x)*FILLED_ARROW_INSET;
	pt2_y = 0;
	pt3_x = pt1_x;
	pt3_y = -pt1_y;
	
	// sin and cos of rotation to get canonical from x axis to target
	sin_theta = dy / len;
	cos_theta = dx / len;
	
	// rotate and translate to get our final points
	result1_x = pt1_x*cos_theta - pt1_y*sin_theta + from->x;
	result1_y = pt1_x*sin_theta + pt1_y*cos_theta + from->y;
	result2_x = pt2_x*cos_theta - pt2_y*sin_theta + from->x;
	result2_y = pt2_x*sin_theta + pt2_y*cos_theta + from->y;
	result3_x = pt3_x*cos_theta - pt3_y*sin_theta + from->x;
	result3_y = pt3_x*sin_theta + pt3_y*cos_theta + from->y;

	// set the arrow head polygon
	points[0] = *to;
	points[1] = DPoint(result1_x, result1_y);
	points[2] = DPoint(result2_x, result2_y);
	points[3] = DPoint(result3_x, result3_y);
}


void LineEnd::DrawExtraArrowHead(Grafport *g, 
		const DPoint *from, const DPoint *to,
			bool filled, DPoint *newEnd) {
	DPoint pt1 = *from, pt2 = *to;
	double dx = to->x - from->x;
	double dy = to->y - from->y;
	double len = sqrt(dx * dx + dy * dy);
	if ( len ) {
		len = length / len;
		dx *= len;
		dy *= len;
		pt1.x -= dx; pt1.y -= dy;
		pt2.x -= dx; pt2.y -= dy;
	}
	if (filled)
		DrawFilledArrowHead(g, &pt1, &pt2, newEnd);
	else
		DrawOpenArrowHead(g, &pt1, &pt2, newEnd);
}


void LineEnd::DrawTriangle(Grafport *g,
		const DPoint *from, const DPoint *to,
		bool filled, DPoint *newEnd) {
	DPoint *points = new DPoint[4];
	CalcDiamond(from, to, length, width, points);
	*newEnd = points[3];
	if (filled)
		g->FillPolygon(points, 3);
	else {
		points[3] = points[0];
		g->DrawOpenPolygon(points, 4);
	}
	double dx = (points[1].x - newEnd->x) * 0.5;
	double dy = (points[1].y - newEnd->y) * 0.5;
	newEnd->x += dx;
	newEnd->y += dy;
	delete points;
}

void LineEnd::DrawDiamond(Grafport *g,
		const DPoint *from, const DPoint *to, bool filled,
		DPoint *newEnd) {
	DPoint *points = new DPoint[5];
	int l = length;
	length = length/2;
	CalcDiamond(from, to, length, width, points);
	length = l;
	if (filled)
		g->FillPolygon(points, 4);
	else {
		points[4] = points[0];
		g->DrawOpenPolygon(points, 4);
	}
	*newEnd = points[3];
	delete points;
}

void LineEnd::DrawCircle(Grafport *g, const DPoint *from,
		const DPoint *to, bool filled, DPoint *newEnd) {
	DPoint pt2 = *to;
	double dx = fabs(to->x - from->x);
	double dy = fabs(to->y - from->y);
	double alpha;
	if (dx != 0)
		alpha = atan(double(dy)/double(dx));
	else
		alpha = M_PI_2;
	dx = width * cos(alpha) * 0.5;
	dy = width * sin(alpha) * 0.5;
	DPoint p = pt2;
	*newEnd = pt2;
	p.x += (from->x < to->x) ? -dx : dx;
	p.y += (from->y < to->y) ? -dy : dy;
	newEnd->x += (from->x < to->x) ? -2*dx : 2*dx;
	newEnd->y += (from->y < to->y) ? -2*dy : 2*dy;
	if (filled)
		g->FillEllipse(p.x-width/2, p.y-width/2,
			width, width);
	if (!filled || !g->DrawsXor())
		g->DrawEllipse(p.x-width/2, p.y-width/2,
			width, width);
}


void LineEnd::CalcDiamond(const DPoint *from, const DPoint *to,
				int len, int wd, DPoint *points) {
	double alpha, beta;
	double x, y, dx, dy;
	DPoint too;
	dx = fabs(to->x - from->x);
	dy = fabs(to->y - from->y);
	if (dx != 0) {
		alpha = atan(dy / dx);
		beta = M_PI_2 - alpha;
	} else {
		alpha = M_PI_2;
		beta = 0;
	}
	// determine length of side
	dx = len * cos(alpha); 
	dy = len * sin(alpha);
	// calculation for corner point of diamond
	x = wd * cos(beta) * 0.5;
	y = wd * sin(beta) * 0.5;
	// for different orientations
	x = (from->x < to->x) ? x : -x;
	y = (from->y < to->y) ? y : -y;
	// midpoint of arrow
	too.x = (from->x < to->x) ? to->x - dx : to->x + dx;
	too.y = (from->y < to->y) ? to->y - dy : to->y + dy;
	points[0].x = too.x + x;
	points[0].y = too.y - y;
	points[1].x = to->x;
	points[1].y = to->y;
	points[2].x = too.x - x,
	points[2].y = too.y + y;
	points[3].x = (from->x < to->x) ? too.x - dx : too.x + dx;
	points[3].y = (from->y < to->y) ? too.y - dy : too.y + dy;
}


void LineEnd::CalcDirectionDiamond(const DPoint *from, const DPoint *to,
				const DPoint *apos,
				int len, int wd, DPoint *points) {
	double alpha, beta;
	double x, y, dx, dy;
	DPoint too;

	dx = fabs(to->x - from->x);
	dy = fabs(to->y - from->y);
	if (dx != 0) {
		alpha = atan(dy / dx);
		beta = M_PI_2 - alpha;
	} else {
		alpha = M_PI_2;
		beta = 0;
	}
	// determine length of side
	dx = len * cos(alpha);
	dy = len * sin(alpha);
	// calculation for corner point of diamond
	x = wd * cos(beta) * 0.5;
	y = wd * sin(beta) * 0.5;
	// for different orientations
	x = (from->x < to->x) ? x : -x;
	y = (from->y < to->y) ? y : -y;
	// midpoint of arrow
	too.x = (from->x < to->x) ? to->x - dx : to->x + dx;
	too.y = (from->y < to->y) ? to->y - dy : to->y + dy;


	too.x = (from->x < to->x) ? apos->x + dx : apos->x + dx;
	too.y = (from->y < to->y) ? apos->y + dy : apos->y + dy;

	too.x = (from->x < to->x) ? apos->x + x : apos->x + x;
	too.y = (from->y < to->y) ? apos->y + y : apos->y + y;

	if (from->x == to->x) {
		too.x = apos->x;
		too.y = (from->y < to->y) ? apos->y + y : apos->y + y;
	} else
		too.x = (from->x < to->x) ? apos->x + x : apos->x + dx;

	if (from->y == to->y)
		too.y = apos->y;
	else
		too.y = (from->y < to->y) ? apos->y + y : apos->y - y;

	points[0].x = too.x + x;
	points[0].y = too.y - y;

	points[1].x = (from->x < to->x) ? too.x + dx : too.x - dx;
	points[1].y = (from->y < to->y) ? too.y + dy : too.y - dy;

	points[2].x = too.x - x,
	points[2].y = too.y + y;
	points[3].x = (from->x < to->x) ? too.x - dx : too.x + dx;
	points[3].y = (from->y < to->y) ? too.y - dy : too.y + dy;
}
