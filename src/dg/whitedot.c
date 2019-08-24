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
#include "whitedot.h"

const PolyPoint WhiteDot::p3( 0, 0, 0, 0, -4, 0, 0, 0, true, true);
const PolyPoint WhiteDot::p2( 4, 0, 0, 0,  0, 0, 0, 0, true, true);
const PolyPoint WhiteDot::p1( 0, 0, 0, 0,  4, 0, 0, 0, true, true);
const PolyPoint WhiteDot::p0(-4, 0, 0, 0,  0, 0, 0, 0, true, true);

const Polygon WhiteDot::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);
							// or NEVER?

const ShapeType WhiteDot::wdType(Code::WHITE_DOT, 8.0, 8.0, 1.0, 1.0,
	(const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, (const PolyPoint *) NULL,
	(const PolyPoint *) NULL, &exterior);

WhiteDot::WhiteDot(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &wdType)
{
}

WhiteDot::WhiteDot(const NodeShape &c)
	:NodeShape(c, &wdType)
{
}
