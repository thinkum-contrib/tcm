////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "application.h"
#include <math.h>

#define square(x) ((x)*(x))
#define round(x) ((int)((x)+0.5))

Grafport::Grafport() {
	zoomValue = 1.0;
	int f = XFont::HELVETICA;
	int s = XFont::PLAIN;
	int p = 12;
	string foundry = "Adobe";
	defaultFont = new XFont(&foundry, f, s, p, False);
	font = defaultFont;
	backgroundColor = "white";
	foregroundColor = "black";
	lineWidth = 1;
	lineStyle = LineStyle::SOLID;
	fillStyle = FillStyle::UNFILLED;
	colors = new List<Color *>;
}

Grafport::~Grafport () {
	delete defaultFont;
	colors->clear();
	delete colors;
}

void Grafport::InitColors() {
	List<Color *> *appColors = theApplication->GetColors();
        for (appColors->first(); !appColors->done(); appColors->next()) {
                Color *color = new Color(*appColors->cur());
		color->pixel = 0;
		color->allocated = False;
		colors->add(color);
	}
}

unsigned Grafport::CursorPosition(double x, double y,
	const string *str, double hit_x, double hit_y)
{
	int j = 0; // index in string.
	unsigned n = 1; // number of lines processed.
	unsigned nLines = str->lines();
	// the cursor position, closest to hit_x, hit_y.
	unsigned cursor = 0;
	int fontHeight = font->GetHeight();
	double offset = y - (nLines) * fontHeight/2;
	buf = "";
	const char *s = str->getstr();
	// string is non-zero.
	while (n <= nLines) {
		char c = s[j];
		buf.add(c);
		// end of line ?
		if (c == '\n' || c == '\r' || c == '\0') {
			buf.remove();
			double y1 = offset + (n-1) * fontHeight;
			double y2 = offset + n * fontHeight;
			if (y1 <= hit_y && hit_y <= y2) {
				// found right line, look at hit_x;
				Point p1 = CursorPosition(x,y,&buf,0);
				for (unsigned k = 1; k <= buf.length(); k++) {
					Point p2 = CursorPosition(x,y,&buf,k);
					int mid = (p1.x + p2.x)/2;
					if (hit_x <= mid)
						return min(cursor,
							   str->length());
					else {
						p1 = p2;
						cursor++;
					}
				}
				return min(cursor, str->length());
			}
			else
				cursor += buf.length()+1;
			buf = ""; // another line
			n++;
		}
		j++;
	}
	return min(cursor, str->length());
}

Point Grafport::DrawStringsCentered(double x, double y, const string *str,
		bool ul, int cursor) {
	int j = 0; // index in string.
	unsigned n = 1; // number of lines processed.
	unsigned nLines = str->lines();
	Point p = Point(static_cast<int>(0.5 + x),
					static_cast<int>(0.5 + y));   // cursor position.
	int fontHeight = font->GetHeight();
	double offset = y - (nLines-1) * fontHeight/2;
	buf = "";
	const char *s = str->getstr();
	// string is non-zero.
	while (n <= nLines) {
		char c = s[j];
		buf.add(c);
		// end of line ?
		if (c == '\n' || c == '\r' || c == '\0') {
			buf.remove();
			// draw string in buf
			y = offset + (n-1) * fontHeight;
			if (ul)
				DrawStringCenteredUnderlined(x, y, buf.getstr());
			else
				DrawStringCentered(x, y, buf.getstr());
			// look for cursor position.
			if (cursor <= j && cursor >= (int)(j - buf.length()))
				p = CursorPosition(x, y, &buf,
						cursor-j+buf.length());
			buf = ""; // another line
			n++;
		}
		j++;
	}
	return p;
}

Point Grafport::DrawStringsLeft(double topLeftx, double topLefty,
		const string *str, bool ul, int cursor) {
	int j = 0; // index in string.
	unsigned n = 1; // number of lines processed.
	unsigned nLines = str->lines();
	topLefty += font->GetAscent();
	Point p = Point(static_cast<int>(0.5 + topLeftx),
					static_cast<int>(0.5 + topLefty));   // cursor position.
	int fontHeight = font->GetHeight();
	buf = "";
	const char *s = str->getstr();
	// string is non-zero.
	while (n <= nLines) {
		char c = s[j];
		buf.add(c);
		// end of line ?
		if (c == '\n' || c == '\r' || c == '\0') {
			buf.remove();
			// draw string in buf
			if (ul)
				DrawStringLeftUnderlined(
					topLeftx, topLefty, buf.getstr());
			else
				DrawStringLeft(
					topLeftx, topLefty, buf.getstr());
			// look for cursor position.
			if (cursor <= j && cursor >= (int)(j - buf.length()))
				p = CursorPosition(
					topLeftx+font->StringWidth(&buf)/2,
					topLefty-font->GetDescent(), &buf,
					cursor-j+buf.length());
			topLefty += fontHeight;
			buf = ""; 	// another line
			n++;
		}
		j++;
	}
	return p;
}

Point Grafport::DrawStringsRight(double topRightx, double topRighty,
		const string *str, bool ul, int cursor) {
	int j = 0; // index in string.
	unsigned n = 1; // number of lines processed.
	unsigned nLines = str->lines();
	topRighty += font->GetAscent();
	Point p = Point(static_cast<int>(0.5 + topRightx),
					static_cast<int>(0.5 + topRighty));   // cursor position.
	int fontHeight = font->GetHeight();
	buf = "";
	const char *s = str->getstr();
	// string is non-zero.
	while (n <= nLines) {
		char c = s[j];
		buf.add(c);
		// end of line ?
		if (c == '\n' || c == '\r' || c == '\0') {
			buf.remove();
			// int x = topRightx - font->StringWidth(&buf);
			// draw string in buf
			if (ul)
				DrawStringRightUnderlined(
					topRightx, topRighty, buf.getstr());
			else
				DrawStringRight(
					topRightx, topRighty, buf.getstr());
			// look for cursor position.
			if (cursor <= j && cursor >= (int)(j - buf.length()))
				p = CursorPosition(
					topRightx-font->StringWidth(&buf)/2,
					topRighty-font->GetDescent(), &buf,
					cursor-j+buf.length());
			topRighty += fontHeight;
			buf = ""; 	// another line
			n++;
		}
		j++;
	}
	return p;
}

Point Grafport::CursorPosition(double x, double y, const string *text, int cursor) {
	string str;
	for(int i=0; i<cursor; i++)
		str.add((*text)[i]);
	int width = font->StringWidth(&str);
	int base = font->GetHeight()/2 - font->GetDescent();
	double str_x;
	if (font->IsScalable())
		str_x = x - font->StringWidth(text)/2 + width;
	else
		str_x = x - ZoomCorrect(font->StringWidth(text)/2 - width);
	return Point(static_cast<int>(0.5 + str_x),
				 static_cast<int>(0.5 + y+base));
}


void Grafport::DrawRectangles(const Rectangle *rects, int n){
	for (int i=0; i<n; i++)
		DrawRectangle(rects[i].x,rects[i].y,
				rects[i].width,rects[i].height);
}


void Grafport::FillRectangles(const Rectangle *rects, int n){
	for (int i=0; i<n; i++)
		FillRectangle(rects[i].x,rects[i].y,
				rects[i].width,rects[i].height);
}


Color *Grafport::LookupColor(const string *colorName) {
        for (colors->first(); !colors->done(); colors->next()) {
                Color *color = colors->cur();
                if (color->name %= *colorName)
                        return color;
        }
        return 0;
}

Color *Grafport::LookupColor(const char *colorName) {
	string x = colorName;
	return LookupColor(&x);
}

void Grafport::AddColor(Color *c) {
	colors->add(new Color(*c));
}

void Grafport::AddColor(const string *name, unsigned long pixel) {
	Color *color = new Color(*name, pixel);
        colors->add(color);
}

void Grafport::AddColor(const char *name, unsigned long pixel) {
	string x = name;
	AddColor(&x, pixel);
}


void Grafport::RecalcPolygon(const Point *points, int nrPoints, Point *newPoints, int d) {
	// it is a regular polygon.
	Point p0 = points[0];
	Point pN;
	if (nrPoints % 2 == 0)
		pN = points[nrPoints/2];
	else {
		Point pN1 = points[nrPoints/2];
		Point pN2 = points[1+nrPoints/2];
		pN.x = (pN1.x + pN2.x) / 2;
		pN.y = (pN1.y + pN2.y) / 2;
	}
	Point pM;
	pM.x = (p0.x + pN.x) / 2;
	pM.y = (p0.y + pN.y) / 2;
	for (int i = 0; i < nrPoints; i++) {
		Point p = points[i];
		if (p.x < pM.x)
			p.x += d;
		else if (p.x > pM.x)
			p.x -= d;
		if (p.y < pM.y)
			p.y += d;
		else if (p.y > pM.y)
			p.y -= d;
		newPoints[i] = p;
	}
}


void Grafport::DrawArc(double x, double y, double w, double h,
	int arc1, int arc2)
{
	if ( GetLineStyle() != LineStyle::DUAL ) {
		DrawSimpleArc(x, y, w, h, arc1, arc2);
		return;
	}
	double delta = ZoomCorrect(GetLineWidth());
	double delta2 = 2.0 * delta;
	DrawSimpleArc(x - delta, y - delta, w + delta2, h + delta2,
		arc1, arc2);
	if ( w > delta2 && h > delta2 )
		DrawSimpleArc(x + delta, y + delta,
			w - delta2, h - delta2, arc1, arc2);
}


void Grafport::DrawLine(double x1, double y1,
	double x2, double y2)
{
	DPoint points[2];
	points[0].x = x1;
	points[0].y = y1;
	points[1].x = x2;
	points[1].y = y2;
	DrawOpenPolygon(points, 2);
}


static void RecalcPolygon(const DPoint *points, DPoint *right,
	DPoint *left, double delta, int n)
{
	if ( n < 2 )
		return;
	--n;
	bool closed = points[0] == points[n];
	double dx1 = points[1].x - points[0].x;
	double dy1 = points[1].y - points[0].y;
	double d1 = ! dx1 && ! dy1 ? 0.0
		: delta / sqrt(square(dx1) + square(dy1));
	if ( ! closed ) {
		right[0].x = points[0].x - dy1 * d1;
		left[0].x = points[0].x + dy1 * d1;
		right[0].y = points[0].y + dx1 * d1;
		left[0].y = points[0].y - dx1 * d1;
	}
	int i = 1;
	for ( ;; ) {
		right[i].x = points[i].x - dy1 * d1;
		left[i].x = points[i].x + dy1 * d1;
		right[i].y = points[i].y + dx1 * d1;
		left[i].y = points[i].y - dx1 * d1;
		double dx2, dy2;
		if ( i >= n ) {
			if ( ! closed )
				break;
			dx2 = points[1].x - points[0].x;
			dy2 = points[1].y - points[0].y;
		} else {
			dx2 = points[i+1].x - points[i].x;
			dy2 = points[i+1].y - points[i].y;
		}
		double d2 = ! dx2 && ! dy2 ? 0.0
			: delta / sqrt(square(dx2) + square(dy2));
		//     ( dx1   dx2 )
		// A = (           )
		//     ( dy1   dy2 )
		double det = dx1 * dy2 - dx2 * dy1;
		if ( det ) {
			double b1 = dy2 * d2 - dy1 * d1;
			double b2 = dx1 * d1 - dx2 * d2;
			double t = (b1 * dy2 - b2 * dx2) / det;
			right[i].x -= dx1 * t;
			left[i].x += dx1 * t;
			right[i].y -= dy1 * t;
			left[i].y += dy1 * t;
		}
		if ( i >= n ) {
			right[0] = right[i];
			left[0] = left[i];
			break;
		}
		dx1 = dx2;
		dy1 = dy2;
		d1 = d2;
		i++;
	}
}


void Grafport::DrawOpenPolygon(const DPoint *points, int n) {
	if ( n < 2 )
		return;
	if ( GetLineStyle() != LineStyle::DUAL) {
		DrawSimplePolygon(points, n);
		return;
	}
	DPoint *p1 = new DPoint[n], *p2 = new DPoint[n];
	::RecalcPolygon(points, p1, p2, ZoomCorrect(GetLineWidth()), n);
	DrawSimplePolygon(p1, n);
	DrawSimplePolygon(p2, n);
	delete[/* n */] p1;
	delete[/* n */] p2;
}


void Grafport::DrawCurve(const DPoint *p)
{
	if ( GetLineStyle() != LineStyle::DUAL) {
		DrawSimpleCurve(p);
		return;
	}
	DPoint p1[4], p2[4];
	::RecalcPolygon(p, p1, p2, ZoomCorrect(GetLineWidth()), 4);
	DrawSimpleCurve(p1);
	DrawSimpleCurve(p2);
}


// This function is incorrect because it assumes that DrawSimpleCurve draws
// a spline that contains points[0], points[1], points[2] and points[3].
///* virtual */ void Grafport::DrawSimpleArc(
//	double x, double y,
//	double w, double h, int arc1, int arc2)
//{
//	w *= 0.5;
//	h *= 0.5;
//	x += w;
//	y += h;
//	DPoint points[4];
//	double a1 = arc1 * (PI / 180);
//	double a2 = arc2 * (PI / 180);
//	points[0].Set(x + w * cos(a1), y - h * sin(a1));
//	points[1].Set(x + w * cos((a1 * 2.0 + a2) / 3.0),
//		y - h * sin((a1 * 2.0 + a2) / 3.0));
//	points[2].Set(x + w * cos((a1 + a2 * 2.0) / 3.0),
//		y - h * sin(a1 + a2 * 2.0) / 3.0));
//	points[3].Set(x + w * cos(a2), y - h * sin(a2));
//	DrawSimpleCurve(points);
//}
