////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "leftlinecircle.h"

// 1/sqrt(8.0) and 1/sqrt(16.0)
#define SQRT_1_8  0.3535533905932737622
#define SQRT_1_16 0.1767766952966368811

const PolyPoint LeftLineCircle::i0(0, -SQRT_1_16, -SQRT_1_16, 0,
					  0, -SQRT_1_16, -SQRT_1_16, 0, true);
const PolyPoint LeftLineCircle::i1(0, -SQRT_1_16, -SQRT_1_16, 0,
					  0,  SQRT_1_16,  SQRT_1_16, 0);

const PolyPoint LeftLineCircle::n0(0,  SQRT_1_16,  SQRT_1_16, 0,
					  0,  SQRT_1_16,  SQRT_1_16, 0, true);
const PolyPoint LeftLineCircle::n1(0,  SQRT_1_16,  SQRT_1_16, 0,
					  0, -SQRT_1_16, -SQRT_1_16, 0);

const Polygon LeftLineCircle::interior((new List<const PolyPoint *>)
	->add(&i0)->add(&i1));
// The name area and the left half of the child area aren't modelled very
// exactly; they are just hexagons.
const Polygon LeftLineCircle::namearea((new List<const PolyPoint *>)
	->add(&i0)->add(&i1)->add(&PolyPoint::BottomSq)
	->add(&n0)->add(&n1)->add(&PolyPoint::TopSq));

const Polygon LeftLineCircle::childarea((new List<const PolyPoint *>)
	->add(&i0)->add(&i1)->add(&PolyPoint::BottomSqArc)
	->add(&PolyPoint::RightSqArc)->add(&PolyPoint::TopSq));

const ShapeType LeftLineCircle::lcType(Code::LEFT_LINE_CIRCLE,
	60.0, 60.0, 1.0, 1.0, &namearea, &childarea, &PolyPoint::IndexSq,
	&PolyPoint::DupliSq, &PolyPoint::MultiSq, &Polygon::Circle, &interior);

LeftLineCircle::LeftLineCircle(ShapeView *v, Grafport *g,  double x, double y)
	:NodeShape(v, g, x, y, &lcType)
{
}

LeftLineCircle::LeftLineCircle(const NodeShape &c)
	:NodeShape(c, &lcType)
{
}
