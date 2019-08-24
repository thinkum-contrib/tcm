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
#include "square.h"
#include "code.h"

const PolyPoint Square::c0( 1, -0.25, -0.25, 0,    1, -0.25, -0.25, 0);
const PolyPoint Square::c1( 1, -0.25, -0.25, 0,   -1,  0.25,  0.25, 0);
const PolyPoint Square::c2(-1,  0.25,  0.25, 0,   -1,  0.25,  0.25, 0);
const PolyPoint Square::c3(-1,  0.25,  0.25, 0,    1, -0.25, -0.25, 0);

const Polygon Square::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeftSq)->add(&PolyPoint::BottomLeftSq)
	->add(&PolyPoint::BottomRightSq)->add(&PolyPoint::TopRightSq),
	Polygon::ON_DEMAND);

const Polygon Square::childarea((new List<const PolyPoint *>)
	->add(&c0)->add(&c1)->add(&c2)->add(&c3));

const ShapeType Square::sqType(Code::SQUARE, 60.0, 60.0, 1.0, 1.0,
	&exterior, &childarea, &PolyPoint::IndexSq, &PolyPoint::DupliSq,
	&PolyPoint::MultiSq, &exterior);


Square::Square(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &sqType)
{
}


Square::Square(const NodeShape &s)
	:NodeShape(s, &sqType)
{
}
