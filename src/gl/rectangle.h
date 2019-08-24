//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#include "point.h"

/// rectangle ADT, defined by x, y, width and height.
class Rectangle {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	static const Rectangle ZERO;

	/// Construct and initialize new rectangle.
	Rectangle(int a = 0, int b = 0, int w = 0, int h=0) 
		{x = a; y = b; width = w; height = h;}

	/// Construct and initialize new rectangle.
	Rectangle(int w, int h) 
		{x = 0; y = 0; width = w; height = h;}

	/// Construct and initialize new rectangle.
	Rectangle(int d) 
		{x = 0; y = 0; width = d; height = d;}

	/// Construct and initialize new rectangle.
	Rectangle(Point origin, Point extent) 
		{x = origin.x; y = origin.y; 
		 width = extent.x-origin.x; height = extent.y-origin.y;}

	/// Reshape rectangle.
	void Set(int a, int b, int w, int h)
		{x = a; y = b; width = w; height = h;}

	/// Set rectangle position.
	void SetPosition(int a, int b)
		{x = a; y = b;}

	/// Move rectangle position.
	void Move(int a, int b)
		{x += a; y += b;}

	/// Return if point (a,b) is inside rectangle.
	bool Inside(Point p) const
		{return Inside(p.x, p.y); }
	/// Return if point (a,b) is inside rectangle.
	bool Inside(int a, int b) const;

	/// Return if rectangle r intersects with 'this'.
	bool Intersects(Rectangle* r) const
		{ return r->x < x + width &&
		r->y < y + height &&
		x < r->x+r->width &&
		y < r->y+r->height;}

	/// Return whether rectangles are equal.
	friend bool operator==(const Rectangle &x, const Rectangle &y);

	/// Return whether rectangles are unequal.
	friend bool operator!=(const Rectangle &x, const Rectangle &y);

	/// Write string representation to ostream.
	friend std::ostream &operator<<(std::ostream &s, const Rectangle r);

	/// Read string representation from istream.
	friend std::istream &operator>>(std::istream &s, Rectangle &r);

	/// the left x-coordinate of the rectangle
	int x;

	/// the top y coordinate of the rectangle
	int y;

	/// the width of the rectangle
	int width;

	/// the height of the rectangle
	int height;
};
#endif
