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
#include "minitriangle.h"

const PolyPoint MiniTriangle::p1(-10, 0, 0, 0,   10/3.0, 0, 0, 0, true);
const PolyPoint MiniTriangle::p2( 10, 0, 0, 0,   10/3.0, 0, 0, 0, true);
const PolyPoint MiniTriangle::p3(  0, 0, 0, 0,  -20/3.0, 0, 0, 0, true);

const Polygon MiniTriangle::exterior((new List<const PolyPoint *>)->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);

const PolyPoint MiniTriangle::duplpoint(-8, 0, 0, 0,    -10, 0, 0, 0);
const PolyPoint MiniTriangle::multipoint(8, 0, 0, 0,    -10, 0, 0, 0);

const ShapeType MiniTriangle::mtType(Code::MINI_TRIANGLE, 20.0, 20.0, 1.0, 1.0,
	(const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, &duplpoint, &multipoint, &exterior);

MiniTriangle::MiniTriangle(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &mtType)
{
}


MiniTriangle::MiniTriangle(const NodeShape &t)
	:NodeShape(t, &mtType)
{
}
