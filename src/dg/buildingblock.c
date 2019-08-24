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
#include "buildingblock.h"

//	 ____t0_________________________
//	|				|
// p1___p0___i1				|	i2 = p0
// |	     |				|
// p2___p3___i0				|
//	|				|
// p5___p4___i4				|	i5 = p4
// |	     |				|
// p6___p7___i3				|
//	|				|
//	|____t1_________________________|

const PolyPoint BuildingBlock::p0(0,-0.5  ,0,0,  0,0,-0.3,0, true);
const PolyPoint BuildingBlock::p1(0,-0.625,0,0,  0,0,-0.3,0, true);
const PolyPoint BuildingBlock::p2(0,-0.625,0,0,  0,0,-0.1,0, true);
const PolyPoint BuildingBlock::p3(0,-0.5  ,0,0,  0,0,-0.1,0, true);
const PolyPoint BuildingBlock::p4(0,-0.5  ,0,0,  0,0, 0.1,0, true);
const PolyPoint BuildingBlock::p5(0,-0.625,0,0,  0,0, 0.1,0, true);
const PolyPoint BuildingBlock::p6(0,-0.625,0,0,  0,0, 0.3,0, true);
const PolyPoint BuildingBlock::p7(0,-0.5  ,0,0,  0,0, 0.3,0, true);

const PolyPoint BuildingBlock::i0(0,-0.375,0,0,  0,0,-0.1,0, true);
const PolyPoint BuildingBlock::i1(0,-0.375,0,0,  0,0,-0.3,0, true);
const PolyPoint BuildingBlock::i2(0,-0.5  ,0,0,  0,0,-0.3,0);
const PolyPoint BuildingBlock::i3(0,-0.375,0,0,  0,0, 0.3,0, true);
const PolyPoint BuildingBlock::i4(0,-0.375,0,0,  0,0, 0.1,0, true);
const PolyPoint BuildingBlock::i5(0,-0.5  ,0,0,  0,0, 0.1,0);

const PolyPoint BuildingBlock::t0(0,-0.375,0,0,  0,0,-0.5,0);
const PolyPoint BuildingBlock::t1(0,-0.375,0,0,  0,0, 0.5,0);

const Polygon BuildingBlock::namearea((new List<const PolyPoint *>)
	->add(&t0)->add(&t1)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::TopRight));
const Polygon BuildingBlock::childarea((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&p0)->add(&i1)->add(&i0)->add(&p3)
	->add(&p4)->add(&i4)->add(&i3)->add(&p7)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::TopRight));
const Polygon BuildingBlock::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&p0)->add(&p1)->add(&p2)->add(&p3)
	->add(&p4)->add(&p5)->add(&p6)->add(&p7)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::TopRight),
	Polygon::ON_DEMAND);
const Polygon BuildingBlock::interior((new List<const PolyPoint *>)
	->add(&p3)->add(&i0)->add(&i1)->add(&i2)
	->add(&p7)->add(&i3)->add(&i4)->add(&i5));

const ShapeType BuildingBlock::bbType(Code::BUILDING_BLOCK, 80.0, 40.0,
	0.0, 0.0, &namearea, &childarea, &PolyPoint::Index,
	&PolyPoint::Dupli, &PolyPoint::Multi, &exterior, &interior);

BuildingBlock::BuildingBlock(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &bbType)
{
}

BuildingBlock::BuildingBlock(const NodeShape &d)
	:NodeShape(d, &bbType)
{
}
