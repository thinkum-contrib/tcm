///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#include "triangle.h"
#include "code.h"

// square root of 3:
#define SQRT_3 1.732050807568877293527446
// regular triangle height = SQRT_3 / 2 * triangle width

/* Points:	 p3
		/c2\
	d      / in \      m
	      /      \
	    t5 _ _ _ _t4
	    /	       \
	   /		\
	  /		 \
	t0		  t3
	/		   \
       /		    \
      /			     \
     p1_c0__t1________t2__c1_p2    */

const PolyPoint Triangle::p1(0, -0.5, 0, 0,    0, 0,  1.0/3, 0, true);
const PolyPoint Triangle::p2(0,  0.5, 0, 0,    0, 0,  1.0/3, 0, true);
const PolyPoint Triangle::p3(0,  0.0, 0, 0,    0, 0, -2.0/3, 0, true);
const Polygon Triangle::exterior((new List<const PolyPoint *>)
	->add(&p1)->add(&p2)->add(&p3), Polygon::ON_DEMAND);

const PolyPoint Triangle::c0( 1, -0.5, 0, 0,    0, 0,  1.0/3, 0);
const PolyPoint Triangle::c1(-1,  0.5, 0, 0,    0, 0,  1.0/3, 0);
const PolyPoint Triangle::c2( 0,  0.0, 0, 0,    1, 0, -2.0/3, 0);
const Polygon Triangle::childarea((new List<const PolyPoint *>)
	->add(&c0)->add(&c1)->add(&c2));

const PolyPoint Triangle::indexpoint(0.0,   0.0,  0.0, 0.0,
				     0.0,   0.0, -0.5, 0.0);
const PolyPoint Triangle::duplpoint(0.0,  -0.4,  0.0, 0.0,
				    0.0,    0.0, -0.5, 0.0);
const PolyPoint Triangle::multipoint(0.0,  0.4,  0.0, 0.0,
				     0.0,   0.0, -0.5, 0.0);

const PolyPoint Triangle::t0(0.0, -1.0/3,    0.0, 0.0,
			     0.0,    0.0,    0.0, 0.0);
const PolyPoint Triangle::t1(0.0, -0.5/3,    0.0, 0.0,
			     0.0,    0.0,  1.0/3, 0.0);
const PolyPoint Triangle::t2(0.0,  0.5/3,    0.0, 0.0,
			     0.0,    0.0,  1.0/3, 0.0);
const PolyPoint Triangle::t3(0.0,  1.0/3,    0.0, 0.0,
			     0.0,    0.0,    0.0, 0.0);
const PolyPoint Triangle::t4(0.0,  0.5/3,    0.0, 0.0,
			     0.0,    0.0, -1.0/3, 0.0);
const PolyPoint Triangle::t5(0.0, -0.5/3,    0.0, 0.0,
			     0.0,    0.0, -1.0/3, 0.0);
const Polygon Triangle::namearea((new List<const PolyPoint *>)->add(&t0)->add(&t1)->add(&t2)->add(&t3)->add(&t4)->add(&t5));

const ShapeType Triangle::trType(Code::TRIANGLE, 60.0, 30.0 * SQRT_3, 0.0, 0.0,
	&namearea, &childarea, &indexpoint, &duplpoint, &multipoint, &exterior);

Triangle::Triangle(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &trType)
{
}


Triangle::Triangle(const NodeShape &t)
	:NodeShape(t, &trType)
{
}
