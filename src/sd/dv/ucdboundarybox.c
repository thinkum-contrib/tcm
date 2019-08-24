//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "ucdboundarybox.h"

const PolyPoint UCDBoundaryBox::t0(0, 0.5, 0, -1,   0, 0, -0.5, 0);
const PolyPoint UCDBoundaryBox::t1(0, 0.5, 0, -1,   0, 0, -0.5, 1);
const PolyPoint UCDBoundaryBox::t2(0, 0.5, 0,  0,   0, 0, -0.5, 1);

const Polygon UCDBoundaryBox::namearea((new List<const PolyPoint *>)
	->add(&t0)->add(&t1)->add(&t2)->add(&PolyPoint::TopRight));

const ShapeType UCDBoundaryBox::bbType(Code::UCD_BOUNDARY_BOX, 240.0, 480.0,
	0.0, 0.0, &namearea, &Polygon::Box1, &PolyPoint::Index,
	&PolyPoint::Dupli, &PolyPoint::Multi, &Polygon::Box);

UCDBoundaryBox::UCDBoundaryBox(ShapeView *v, Grafport *g, 
		double x, double y)
	:NodeShape(v, g, x, y, &bbType)
{
}

UCDBoundaryBox::UCDBoundaryBox(const NodeShape &c)
	:NodeShape(c, &bbType)
{
}
