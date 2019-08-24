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
#include "disk.h"
#include "code.h"

/*           _p5_               p5=TopArc
      __,---'    `---.__
   ,-'                  `-.
  p0                      p4    p0=i0, p4=i2
   |-.__              __,-|
  c0    `---._i1_,---'    c1
   |                      |
  t0                      t1
   |                      |
  p1                      p3
   `-.__              __,-'
        `---._p2_,---'          p2=BottomArc */

const PolyPoint Disk::p0(0, -0.5, 0, 0,   0, 0, -0.35, 0, true);
const PolyPoint Disk::p1(0, -0.5, 0, 0,   0, 0,  0.35, 0, true, true);
const PolyPoint Disk::p3(0,  0.5, 0, 0,   0, 0,  0.35, 0, true);
const PolyPoint Disk::p4(0,  0.5, 0, 0,   0, 0, -0.35, 0, true, true);
const PolyPoint Disk::i0(0, -0.5, 0, 0,   0, 0, -0.35, 0, true, true);
const PolyPoint Disk::i1(0,  0.0, 0, 0,   0, 0, -0.2 , 0, true, true);
const PolyPoint Disk::i2(0,  0.5, 0, 0,   0, 0, -0.35, 0);
const PolyPoint Disk::t0(0, -0.5, 0, 0,   0, 0, -0.05, 0);
const PolyPoint Disk::t1(0,  0.5, 0, 0,   0, 0, -0.05, 0, false, true);
const PolyPoint Disk::c0(0, -0.5, 0, 0,   0, 0, -0.2 , 0);
const PolyPoint Disk::c1(0,  0.5, 0, 0,   0, 0, -0.2 , 0);

const Polygon Disk::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&PolyPoint::BottomArc)
	->add(&p3)->add(&p4)->add(&PolyPoint::TopArc), Polygon::ON_DEMAND);
const Polygon Disk::interior((new List<const PolyPoint *>)
	->add(&i0)->add(&i1)->add(&i2));
const Polygon Disk::namearea((new List<const PolyPoint *>)
	->add(&t0)->add(&p1)->add(&PolyPoint::BottomArc)
	->add(&p3)->add(&t1)->add(&i1));
const Polygon Disk::childarea((new List<const PolyPoint *>)
	->add(&c0)->add(&p1)->add(&PolyPoint::BottomArc)->add(&p3)->add(&c1));

const ShapeType Disk::diskType(Code::DISK, 80.0, 48.0, 0.0, 0.0, &namearea,
	&childarea, &PolyPoint::Index, &PolyPoint::Dupli, &PolyPoint::Multi,
	&exterior, &interior);

Disk::Disk(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &diskType)
{
}


Disk::Disk(const NodeShape &c)
	:NodeShape(c, &diskType)
{
}

