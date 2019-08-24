////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl)
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
#include "ellipsedbox.h"
#include "code.h"

const PolyPoint EllipsedBox::p1(0,-0.5, 0.5, 0,   0, 0, 0.5, 0, true);
const PolyPoint EllipsedBox::p2(0, 0.5,-0.5, 0,   0, 0, 0.5, 0, true, true);
const PolyPoint EllipsedBox::p4(0, 0.5,-0.5, 0,   0, 0,-0.5, 0, true);
const PolyPoint EllipsedBox::p5(0,-0.5, 0.5, 0,   0, 0,-0.5, 0, true, true);

const PolyPoint EllipsedBox::c0(0,-0.5, 0.5, 0,  -1, 0, 0.5, 0);
const PolyPoint EllipsedBox::c1(0, 0.5,-0.5, 0,  -1, 0, 0.5, 0, false, true);
const PolyPoint EllipsedBox::c2(0, 0.5,-0.5, 0,   1, 0,-0.5, 0);
const PolyPoint EllipsedBox::c3(0,-0.5, 0.5, 0,   1, 0,-0.5, 0, false, true);

const Polygon EllipsedBox::exterior((new List<const PolyPoint *>)
	->add(&p5)->add(&PolyPoint::LeftArc)->add(&p1)
	->add(&p2)->add(&PolyPoint::RightArc)->add(&p4),
	Polygon::ON_DEMAND);

const Polygon EllipsedBox::childarea((new List<const PolyPoint *>)
	->add(&c3)->add(&PolyPoint::LeftArc1)->add(&c0)
	->add(&c1)->add(&PolyPoint::RightArc1)->add(&c2));

const ShapeType EllipsedBox::ebType(Code::ELLIPSED_BOX, 80.0, 40.0, 1.0, 0.0,
	&exterior, &childarea, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &exterior);

EllipsedBox::EllipsedBox(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &ebType)
{
}

EllipsedBox::EllipsedBox(const NodeShape &c)
	:NodeShape(c, &ebType)
{
}

