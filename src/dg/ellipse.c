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
#include "ellipse.h"

const Polygon Ellipse::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::LeftArc)->add(&PolyPoint::BottomArc)
	->add(&PolyPoint::RightArc)->add(&PolyPoint::TopArc),
	Polygon::ON_DEMAND);

const Polygon Ellipse::childarea((new List<const PolyPoint *>)
	->add(&PolyPoint::LeftArc1)->add(&PolyPoint::BottomArc1)
	->add(&PolyPoint::RightArc1)->add(&PolyPoint::TopArc1));

const ShapeType Ellipse::elType(Code::ELLIPSE, 80.0, 40.0, 0.0, 0.0,
	&exterior, &childarea, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &exterior);

Ellipse::Ellipse(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &elType)
{
}

Ellipse::Ellipse(const NodeShape &c)
	:NodeShape(c, &elType)
{
}
