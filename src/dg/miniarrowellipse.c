////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "miniarrowellipse.h"

const PolyPoint MiniArrowEllipse::p0(-6, 0, 0, 0,   0, 0, 0, 0, true, true);
const PolyPoint MiniArrowEllipse::p1( 0, 0, 0, 0,   6, 0, 0, 0, true, true);
const PolyPoint MiniArrowEllipse::p2( 6, 0, 0, 0,   0, 0, 0, 0, true, true);
const PolyPoint MiniArrowEllipse::p3( 0, 0, 0, 0,  -6, 0, 0, 0, true, true);

#define SIN_225 0.38268343236508977
#define COS_225 0.92387953251128676

const PolyPoint MiniArrowEllipse::i0(0, 0, 0, 0,  -26, 0, 0, 0, true);
const PolyPoint MiniArrowEllipse::i1(0, 0, 0, 0,  -6 - 6 * COS_225, 0, 0, 0);
const PolyPoint MiniArrowEllipse::i2(-10 * SIN_225, 0, 0, 0,   -6 - 10 * COS_225, 0, 0, 0);
const PolyPoint MiniArrowEllipse::i3(0, 0, 0, 0,  -6, 0, 0, 0);
const PolyPoint MiniArrowEllipse::i4(10 * SIN_225, 0, 0, 0,  -6 - 10 * COS_225, 0, 0, 0);

const PolyPoint MiniArrowEllipse::t0(0, 0, 0, -0.5,  -26, 0, 0, -1);
const PolyPoint MiniArrowEllipse::t1(0, 0, 0, -0.5,  -26, 0, 0,  0);
const PolyPoint MiniArrowEllipse::t2(0, 0, 0,  0.5,  -26, 0, 0,  0);
const PolyPoint MiniArrowEllipse::t3(0, 0, 0,  0.5,  -26, 0, 0, -1);

const PolyPoint MiniArrowEllipse::duplpoint(-6, 0, 0, 0, -20, 0, 0, 0);
const PolyPoint MiniArrowEllipse::multipoint(6, 0, 0, 0, -20, 0, 0, 0);

const Polygon MiniArrowEllipse::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);

const Polygon MiniArrowEllipse::interior((new List<const PolyPoint *>)
	->add(&i0)->add(&i1)->add(&i2)->add(&i3)->add(&i4)->add(&i1),
	Polygon::ALWAYS);

const Polygon MiniArrowEllipse::namearea((new List<const PolyPoint *>)
	->add(&t0)->add(&t1)->add(&t2)->add(&t3));

const ShapeType MiniArrowEllipse::maType(Code::MINI_ARROW_ELLIPSE, 12.0, 32.0,
	0.0, 0.0, &namearea, (const Polygon *) NULL, (const PolyPoint *) NULL,
	&duplpoint, &multipoint, &exterior, &interior);

MiniArrowEllipse::MiniArrowEllipse(ShapeView *v, Grafport *g,
	double x, double y)
	:NodeShape(v, g, x, y, &maType)
{
}
 
MiniArrowEllipse::MiniArrowEllipse(const NodeShape &c)
	:NodeShape(c, &maType)
{
}
