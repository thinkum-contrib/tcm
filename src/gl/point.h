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
#ifndef _POINT_H
#define _POINT_H

#include <fstream>
#include "bool.h"

/// 2-dimensional integer point ADT
class Point {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	static const Point ZERO;

	/// Construct and initialize point.
	Point(int a = 0, int b = 0) {x = a; y = b;}

	/// Copy constructor.
	Point(const Point &p) {x = p.x; y = p.y;}

	/// Set point to (a,b).
	void Set(int a, int b) {x = a; y = b;}

	/// Add points.
	friend Point operator+(const Point p1, const Point p2);
	/// Subtract points.
	friend Point operator-(const Point p1, const Point p2);
	/// Multiply points.
	friend Point operator*(const Point p1, const Point p2);
	/// Devide points.
	friend Point operator/(const Point p1, const Point p2);

	/// Subtract point from point.
	Point operator-() { return Point(-x,-y);}

	/// Return whether points are equal.
	friend bool operator==(const Point &x, const Point &y);

	/// Return whether points are unequal.
	friend bool operator!=(const Point &x, const Point &y);

	/// Translate the point.
	void operator+=(const Point p1) {x += p1.x; y += p1.y;}
	/// Translate the point.
	void operator-=(const Point p1) {x -= p1.x; y -= p1.y;}
	/// Translate the point.
	void operator*=(const Point p1) {x *= p1.x; y *= p1.y;}
	/// Translate the point.
	void operator/=(const Point p1) {x /= p1.x; y /= p1.y;}

	/// Multiply by constant.
	void operator*(int c) {x *= c; y *= c;}
	/// Multiply by constant.
	void operator*(double c) {x = int(x*c); y = int(y*c);}

	/// Write string representation to ostream.
	friend std::ostream &operator<<(std::ostream &o, const Point p);

	/// Read string representation from istream.
	friend std::istream &operator>>(std::istream &i, Point &p);

	/// the x-coordinate.
	int x;

	/// the y-coordinate.
	int y;
};
#endif
