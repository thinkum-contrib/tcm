////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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

#include "lifeline.h"

const int LifeLine::LIFELINE_WIDTH = 80;
const int LifeLine::LIFELINE_HEIGHT = 40;

const ShapeType Box::bxType(Code::BOX, BOX_WIDTH, BOX_HEIGHT, 0.0, 0.0,
	&Polygon::Box, &Polygon::Box1, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &Polygon::Box);

Box::Box(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &bxType)
{
}

Box::Box(const NodeShape &c)
	:NodeShape(c, &bxType)
{
}
