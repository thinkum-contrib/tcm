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
#include "stickman.h"
#include "code.h"

/* p0         p3
        _i0_
       /    \ 
     i1     i3
       \_  _/
  	 i2
     i4--+--i5
         |
         |
         i6
    	/ \ 
       /   \ 
      /     \ 
     i7	    i8
   p1         p2 */

const PolyPoint StickMan::p1( 0.0,-0.5, 0.0 ,0,   0.0,0, 0.5 ,1);
const PolyPoint StickMan::p2( 0.0, 0.5, 0.0 ,0,   0.0,0, 0.5 ,1);
const PolyPoint StickMan::i0( 0.0, 0.0, 0.0 ,0,   6.0,0,-0.5 ,0,true, true);
const PolyPoint StickMan::i1( 1.8, 0.0,-0.15,0,   4.2,0,-0.35,0,true, true);
const PolyPoint StickMan::i2( 0.0, 0.0, 0.0 ,0,   2.4,0,-0.2 ,0,true, true);
const PolyPoint StickMan::i2_(0.0, 0.0, 0.0 ,0,   2.4,0,-0.2 ,0);
const PolyPoint StickMan::i3(-1.8, 0.0, 0.15,0,   4.2,0,-0.35,0,true, true);
const PolyPoint StickMan::i4( 6.0,-0.5, 0.0 ,0,   1.8,0,-0.15,0,true);
const PolyPoint StickMan::i5(-6.0, 0.5, 0.0 ,0,   1.8,0,-0.15,0);
const PolyPoint StickMan::i6( 0.0, 0.0, 0.0 ,0,  -2.4,0, 0.2 ,0,true);
const PolyPoint StickMan::i7( 6.0,-0.5, 0.0 ,0,  -6.0,0, 0.5 ,0,true);
const PolyPoint StickMan::i8(-6.0, 0.5, 0.0 ,0,  -6.0,0, 0.5 ,0);

const PolyPoint StickMan::t0( 0.0, 0.0, 0.0, -0.5, -3.0, 0.0, 0.5, 0.0);
const PolyPoint StickMan::t1( 0.0, 0.0, 0.0, -0.5, -3.0, 0.0, 0.5, 1.0);
const PolyPoint StickMan::t2( 0.0, 0.0, 0.0,  0.5, -3.0, 0.0, 0.5, 1.0);
const PolyPoint StickMan::t3( 0.0, 0.0, 0.0,  0.5, -3.0, 0.0, 0.5, 0.0);

const PolyPoint StickMan::indexpoint(0.0, 0.0, 0.0, 0.0, 6.0, 0.0, -0.375, 0.0);

const Polygon StickMan::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeftInv)->add(&p1)
	->add(&p2)->add(&PolyPoint::TopRightInv));
const Polygon StickMan::interior((new List<const PolyPoint *>)
	->add(&i6)->add(&i2)->add(&i3)->add(&i0)->add(&i1)->add(&i2_)
	->add(&i4)->add(&i5)
	->add(&i7)->add(&i6)->add(&i8), Polygon::ON_DEMAND);
const Polygon StickMan::namearea((new List<const PolyPoint *>)
	->add(&t0)->add(&t1)->add(&t2)->add(&t3));

const ShapeType StickMan::smType(Code::STICKMAN, 40.0, 70.0, 0.0, 0.0,
	&namearea, (const Polygon *) NULL, &indexpoint, &PolyPoint::Dupli,
	&PolyPoint::Multi, &exterior, &interior);

StickMan::StickMan(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &smType)
{
}


StickMan::StickMan(const NodeShape &s)
	:NodeShape(s, &smType)
{
}
