////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "bullseye.h"
#include "code.h"

const PolyPoint BullsEye::p0(-10.0, 0.0, 0.0, 0.0,     0.0, 0.0, 0.0, 0.0,
	true, true);
const PolyPoint BullsEye::p1(  0.0, 0.0, 0.0, 0.0,    10.0, 0.0, 0.0, 0.0,
	true, true);
const PolyPoint BullsEye::p2( 10.0, 0.0, 0.0, 0.0,     0.0, 0.0, 0.0, 0.0,
	true, true);
const PolyPoint BullsEye::p3(  0.0, 0.0, 0.0, 0.0,   -10.0, 0.0, 0.0, 0.0,
	true, true);

const Polygon BullsEye::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);
const ShapeType BullsEye::beType(Code::BULLS_EYE, 20.0, 20.0, 1.0, 1.0,
	(const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, (const PolyPoint *) NULL,
	(const PolyPoint *) NULL, &exterior, &Polygon::BlackDot);

BullsEye::BullsEye(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &beType)
{
}


BullsEye::BullsEye(const NodeShape &b)
	:NodeShape(b, &beType)
{
}
