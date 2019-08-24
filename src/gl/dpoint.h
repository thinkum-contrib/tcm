//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
#ifndef _DPOINT_H
#define _DPOINT_H

#include <fstream>
#include "point.h"

/// 2-dimensional double point ADT
class DPoint {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	static const DPoint ZERO;

	///
	DPoint() { x = y = 0.0; }

	///
	DPoint(const Point &p) { x = p.x; y = p.y; }

	/// Construct and initialize point.
	DPoint(double a, double b) {x = a; y = b;}

	/// Copy constructor.
	DPoint(const DPoint &p) {x = p.x; y = p.y;}

	operator Point() const { return Point(int(0.5 + x), int(0.5 + y)); }

	/// Set point to (a,b).
	void Set(double a, double b) {x = a; y = b;}

	/// Add points.
	DPoint operator+(const DPoint &p2) const {
		return DPoint(x + p2.x, y + p2.y);
	}
	/// Subtract points.
	DPoint operator-(const DPoint &p2) const {
		return DPoint(x - p2.x, y - p2.y);
	}
	/// Multiply points.
	DPoint operator*(const DPoint &p2) const {
		return DPoint(x * p2.x, y * p2.y);
	}
	/// Devide points.
	DPoint operator/(const DPoint &p2) const {
		return DPoint(x / p2.x, y / p2.y);
	}

	/// Subtract point from point.
	DPoint operator-() const { return DPoint(-x,-y); }

	/// Return whether points are equal.
	bool operator==(const DPoint &p2) const {
		return x == p2.x && y == p2.y;
	}
	/// Return whether points are unequal.
	bool operator!=(const DPoint &p2) const {
		return x != p2.x || y != p2.y;
	}
	/// Translate the point.
	void operator+=(const DPoint &p1) { x += p1.x; y += p1.y; }
	/// Translate the point.
	void operator-=(const DPoint &p1) { x -= p1.x; y -= p1.y; }
	/// Translate the point.
	void operator*=(const DPoint &p1) { x *= p1.x; y *= p1.y; }
	/// Translate the point.
	void operator/=(const DPoint &p1) { x /= p1.x; y /= p1.y; }

	/// Multiply by constant.
	void operator*=(double c) { x *= c; y *= c; }

	void operator/=(double c) { x /= c; y /= c; }

	/// Write string representation to ostream.
	friend std::ostream &operator<<(std::ostream &o, const DPoint &p);

	/// Read string representation from istream.
	friend std::istream &operator>>(std::istream &i, DPoint &p);

	/// the x-coordinate.
	double x;

	/// the y-coordinate.
	double y;
};
#endif
