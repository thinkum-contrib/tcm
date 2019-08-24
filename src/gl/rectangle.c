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
#include "rectangle.h"

const Rectangle Rectangle::ZERO = Rectangle(0,0,0,0);

bool Rectangle::Inside(int a, int b) const
                {return (a>x && b>y && a<(x+width) && b<(y+height));}
 
std::ostream &operator<<(std::ostream &s, const Rectangle r)
	{s << r.x << " "; s << r.y << " ";
	 s << r.width << " "; s << r.height << " ";
	 return s;}
 
std::istream &operator>>(std::istream &s, Rectangle &r)
	{s >> r.x; s >> r.y;
	 s >> r.width; s >> r.height;
	 return s;}

bool operator==(const Rectangle &r1, const Rectangle &r2) {
	return (r1.x == r2.x && r1.y == r2.y &&
		r1.width == r2.width && r1.height == r2.height);
}
 
bool operator!=(const Rectangle &r1, const Rectangle &r2) {
	return (r1.x != r2.x || r1.y != r2.y ||
		r1.width != r2.width || r1.height != r2.height);
}
