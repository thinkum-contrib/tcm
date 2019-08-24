////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
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

#include "cube.h"
#include "code.h"

const PolyPoint Cube::p0(0.0, -0.5  , 0.0, 0.0,   0.0, 0.0, -0.375, 0.0, true);
const PolyPoint Cube::p2(0.0,  0.375, 0.0, 0.0,   0.0, 0.0,  0.5  , 0.0, true);
const PolyPoint Cube::p3(0.0,  0.5  , 0.0, 0.0,   0.0, 0.0,  0.375, 0.0, true);
const PolyPoint Cube::p5(0.0, -0.375, 0.0, 0.0,   0.0, 0.0, -0.5  , 0.0, true);

const PolyPoint Cube::i0(0.0,  0.375, 0.0, 0.0,   0.0, 0.0, -0.375, 0.0, true);
const PolyPoint Cube::i1(0.0,  0.375, 0.0, 0.0,   0.0, 0.0,  0.5  , 0.0);
const PolyPoint Cube::i2(0.0,  0.5  , 0.0, 0.0,   0.0, 0.0, -0.5  , 0.0);

const PolyPoint Cube::indexpoint(0.0, -0.0625, 0.0, 0.0, 0.0, 0.0, -0.325, 0.0);
const PolyPoint Cube::multipoint(0.0, 0.325, 0.0, 0.0,  0.0, 0.0, -0.325, 0.0);

const Polygon Cube::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&PolyPoint::BottomLeft)->add(&p2)
	->add(&p3)->add(&PolyPoint::TopRight)->add(&p5), Polygon::ON_DEMAND);
const Polygon Cube::interior((new List<const PolyPoint *>)
	->add(&p0)->add(&i0)->add(&i1)->add(&i0)->add(&i2));
const Polygon Cube::namearea((new List<const PolyPoint *>)
	->add(&p0)->add(&PolyPoint::BottomLeft)->add(&p2)->add(&i1));

const ShapeType Cube::cuType(Code::CUBE, 80.0, 40.0, 0.0, 0.0,
	&namearea, &namearea, &indexpoint, &PolyPoint::Dupli, &multipoint,
	&exterior, &interior);


Cube::Cube(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &cuType)
{
}


Cube::Cube(const NodeShape &c)
	:NodeShape(c, &cuType)
{
}
