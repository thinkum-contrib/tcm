//-----------------------------------------------------------------------------
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
#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "nodeshape.h"

/// ellipse class always having equal width and height.
class Circle: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Circle(ShapeView *v, Grafport *g, double x, double y);
	///
        Circle(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new Circle(*this);}
protected:

private:
	static const PolyPoint c0, c1, c2, c3;
	static const Polygon ChildCircle;
	static const ShapeType ciType;
};
#endif
