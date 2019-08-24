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
#include "verticalbar.h"

const Polygon VerticalBar::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&PolyPoint::BottomLeftInv)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::TopRightInv));

const ShapeType VerticalBar::vbType(Code::VERTICAL_BAR, 30.0, 80.0, 0.0, 0.0,
	&Polygon::Box, &Polygon::Box1, &PolyPoint::Index, &PolyPoint::Dupli,
	&PolyPoint::Multi, &exterior);

VerticalBar::VerticalBar(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &vbType)
{
}

VerticalBar::VerticalBar(const NodeShape &c)
	:NodeShape(c, &vbType)
{
}
