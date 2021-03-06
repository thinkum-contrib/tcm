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
#include "point.h"

const Point Point::ZERO = Point(0,0);

Point operator-(const Point p1, const Point p2)
	{return Point(p1.x - p2.x, p1.y - p2.y);}
 
Point operator+(const Point p1, const Point p2)
	{return Point(p1.x + p2.x, p1.y + p2.y);}

Point operator*(const Point p1, const Point p2)
	{return Point(p1.x * p2.x, p1.y * p2.y);}

Point operator/(const Point p1, const Point p2)
	{return Point(p1.x / p2.x, p1.y / p2.y);}

bool operator==(const Point &p1, const Point &p2) {
	return (p1.x == p2.x && p1.y == p2.y); }
 
bool operator!=(const Point &p1, const Point &p2) {
	return (p1.x != p2.x || p1.y != p2.y); }

std::ostream &operator<<(std::ostream &o, const Point p)
	{o << p.x << " "; o << p.y; return o;}
 
std::istream &operator>>(std::istream &i, Point &p)
	{i >> p.x; i >> p.y; return i;}
