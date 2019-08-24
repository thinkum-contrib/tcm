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
#include "hexagon.h"

#include "code.h"

const PolyPoint Hexagon::p1(0, -0.25, 0, 0,    0, 0,  0.5, 0, true);
const PolyPoint Hexagon::p2(0,  0.25, 0, 0,    0, 0,  0.5, 0, true);
const PolyPoint Hexagon::p4(0,  0.25, 0, 0,    0, 0, -0.5, 0, true);
const PolyPoint Hexagon::p5(0, -0.25, 0, 0,    0, 0, -0.5, 0, true);

const PolyPoint Hexagon::c0(0, -0.25, 0, 0,   -1, 0,  0.5, 0);
const PolyPoint Hexagon::c1(0,  0.25, 0, 0,   -1, 0,  0.5, 0);
const PolyPoint Hexagon::c2(0,  0.25, 0, 0,    1, 0, -0.5, 0);
const PolyPoint Hexagon::c3(0, -0.25, 0, 0,    1, 0, -0.5, 0);

const Polygon Hexagon::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::Left)->add(&p1)->add(&p2)
	->add(&PolyPoint::Right)->add(&p4)->add(&p5), Polygon::ON_DEMAND);

const Polygon Hexagon::childarea((new List<const PolyPoint *>)
	->add(&PolyPoint::Left1)->add(&c0)->add(&c1)
	->add(&PolyPoint::Right1)->add(&c2)->add(&c3));

const ShapeType Hexagon::hgType(Code::HEXAGON, 80.0, 40.0, 0.0, 0.0,
	&exterior, &childarea, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &exterior);

Hexagon::Hexagon(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &hgType)
{
}

Hexagon::Hexagon(const NodeShape &h)
	:NodeShape(h, &hgType)
{
}
