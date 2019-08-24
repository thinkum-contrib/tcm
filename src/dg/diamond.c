///////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
#include "diamond.h"
#include "code.h"

//const PolyPoint Diamond::indexpoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.25, 0.0);

const Polygon Diamond::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::Left)->add(&PolyPoint::Bottom)
	->add(&PolyPoint::Right)->add(&PolyPoint::Top), Polygon::ON_DEMAND);

// the exact offset would be: sqrt((w*w)/(h*h) + 1), but it's simplified to 1.
const Polygon Diamond::childarea((new List<const PolyPoint *>)
	->add(&PolyPoint::Left1)->add(&PolyPoint::Bottom1)
	->add(&PolyPoint::Right1)->add(&PolyPoint::Top1));

const ShapeType Diamond::diType(Code::DIAMOND, 80.0, 40.0, 0.0, 0.0,
	&exterior, &childarea, &PolyPoint::Index, &PolyPoint::Dupli, &PolyPoint::Multi, &exterior);

Diamond::Diamond(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &diType)
{
}


Diamond::Diamond(const NodeShape &t)
	:NodeShape(t, &diType)
{
}
