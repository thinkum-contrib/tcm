//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _MINIARROWELLIPSE_H
#define _MINIARROWELLIPSE_H

#include "nodeshape.h"

/// small circle having small arrow and label on top.
class MiniArrowEllipse: public NodeShape {
/*@Doc: {\large {\bf scope:} Diagram} */
public:
	///
	MiniArrowEllipse(ShapeView *v, Grafport *g, double x, double y);
	///
	MiniArrowEllipse(const NodeShape &c);
	/// 
	Shape *Clone() {return new MiniArrowEllipse(*this);}
private:
	static const PolyPoint p0, p1, p2, p3, i0, i1, i2, i3, i4,
		t0, t1, t2, t3, duplpoint, multipoint;
	static const Polygon exterior, interior, namearea;
	static const ShapeType maType;
};
#endif
