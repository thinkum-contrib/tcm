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
#include "scdandstatebox.h"

/*
   b0______b3
   |t0    t3|
   |t1    t2|
   b1______b2______TTR
  /                  \
TLL                  TRR
 |                    |
 |                    |
BLL                  BRR
  \__________________/
  BBL               BBR
*/




const PolyPoint SCDAndStateBox::t0(7,-0.48,0.02,0,  -2,0,-0.5 ,-1);
const PolyPoint SCDAndStateBox::t1(7,-0.48,0.02,0,  -2,0,-0.5 , 0);
const PolyPoint SCDAndStateBox::t2(7,-0.48,0.02,1,  -2,0,-0.5 , 0);
const PolyPoint SCDAndStateBox::t3(7,-0.48,0.02,1,  -2,0,-0.5 ,-1);

const PolyPoint SCDAndStateBox::b0(5,-0.48,0.02,0,  -4,0,-0.5 ,-1, true);
const PolyPoint SCDAndStateBox::b1(5,-0.48,0.02,0,   0,0,-0.5 , 0);
const PolyPoint SCDAndStateBox::b2(9,-0.48,0.02,1,   0,0,-0.5 , 0, true);
const PolyPoint SCDAndStateBox::b3(9,-0.48,0.02,1,  -4,0,-0.5 ,-1, true);

const Polygon SCDAndStateBox::boundary((new List<const PolyPoint *>)
	->add(&PolyPoint::RoundedBoxTTL)->add(&PolyPoint::RoundedBoxTLL)
	->add(&PolyPoint::RoundedBoxBLL)->add(&PolyPoint::RoundedBoxBBL)
	->add(&PolyPoint::RoundedBoxBBR)->add(&PolyPoint::RoundedBoxBRR)
	->add(&PolyPoint::RoundedBoxTRR)->add(&PolyPoint::RoundedBoxTTR)
	->add(&b2)->add(&b3)->add(&b0),
	Polygon::ON_DEMAND);

const Polygon SCDAndStateBox::interior((new List<const PolyPoint *>)
	->add(&b1)->add(&b2));

const Polygon SCDAndStateBox::textarea((new List<const PolyPoint *>)
	->add(&t0)->add(&t1)->add(&t2)->add(&t3));

const ShapeType SCDAndStateBox::abType(Code::SCD_AND_STATE_BOX, 160.0, 80.0,
	1/17.5, 17.5, &textarea, &Polygon::RoundedBox1, &PolyPoint::Index,
	&PolyPoint::Dupli, &PolyPoint::Multi, &boundary, &interior);

SCDAndStateBox::SCDAndStateBox(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &abType)
{
}

SCDAndStateBox::SCDAndStateBox(const NodeShape &c)
	:NodeShape(c, &abType)
{
}
