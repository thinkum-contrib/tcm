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
#ifndef _INTERSECT_H
#define _INTERSECT_H

#include "point.h"
 
/// Functions for intersection point computation.
class Intersect {
/*@Doc: {\large {\bf scope:} global} */
public:
/// Return intersection from point 'from' to box at 'to' having width and height
	static Point BoxIntersects(Point from, Point to, int width, int height);

/// See above, intersecting line is order-th of count lines. code is not used.
	static Point BoxIntersects(Point position, Point to, 
		int width, int height, int order, int count, int &code);

/// Return intersect from point 'from' to ellipse at 'to' having wd and ht.
	static Point EllipseIntersects(Point from, Point to, int width, 
		int height);

/// See above, intersecting line is order-th of count lines. code is not used.
	static Point EllipseIntersects(Point position, Point to, 
		int width, int height, int order, int count, int &code);

/// Return intersect from point 'from' to diamond at 'to' having wd and ht
	static Point DiamondIntersects(Point from, Point to, int width, 
		int height);

/// See above, intersecting line is order-th of count lines. code is not used.
	static Point DiamondIntersects(Point position, Point to, 
		int width, int height, int order, int count, int &code);

/// Return intersect from point 'from' to triangle at 'to' having wd and ht
	static Point TriangleIntersects(Point from, Point to, int width, 
		int height);

/// See above, intersecting line is order-th of count lines. code is not used.
	static Point TriangleIntersects(Point position, Point to, int width,
		int height, int order, int count, int &code);

/// Return intersect from point 'from' to notebox at 'to' having wd and ht
        static Point NoteBoxIntersects(Point from, Point to, int width,
                int height);
protected:
	///	 
	static Point DiamondSnp(Point to, int dx, int dy,
		int x1, int y1, int x2, int y2);
	///
	static void WhichLine(Point p, int w, int h, int dx, int dy,
		int &x1, int &y1, int &x2, int &y2);
	///
	static void WhichLine2(Point p, int w, int h, int dx, int dy, 
		int deltaY, int &x1, int &y1, int &x2, int &y2);
	///
	static void WhichLine3(Point p, int w, int h, int dx, int dy, 
		int deltaY, int &x1, int &y1, int &x2, int &y2);
};
#endif
