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
#include "minidiamond.h"

const PolyPoint MiniDiamond::p0(-10, 0, 0, 0,    0, 0, 0, 0, true);
const PolyPoint MiniDiamond::p1(  0, 0, 0, 0,   10, 0, 0, 0, true);
const PolyPoint MiniDiamond::p2( 10, 0, 0, 0,    0, 0, 0, 0, true);
const PolyPoint MiniDiamond::p3(  0, 0, 0, 0,  -10, 0, 0, 0, true);

const PolyPoint MiniDiamond::duplpoint(-8, 0, 0, 0, -8, 0, 0, 0);
const PolyPoint MiniDiamond::multipoint(8, 0, 0, 0, -8, 0, 0, 0);

const Polygon MiniDiamond::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);

const ShapeType MiniDiamond::mdType(Code::MINI_DIAMOND, 20.0, 20.0, 1.0, 1.0,
	(const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, &duplpoint, &multipoint, &exterior);

MiniDiamond::MiniDiamond(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &mdType)
{
}


MiniDiamond::MiniDiamond(const NodeShape &t)
	:NodeShape(t, &mdType)
{
}
