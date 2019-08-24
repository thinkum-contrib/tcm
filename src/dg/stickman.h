//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _STICKMAN_H
#define _STICKMAN_H

#include "nodeshape.h"


/// StickMan shape class.
class StickMan: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	StickMan(ShapeView *v, Grafport *g, double x, double y);
	///
	StickMan(const NodeShape &s);
	///
	/* virtual */ Shape *Clone() {return new StickMan(*this);}

protected:

private:
	static const PolyPoint p1, p2, i0, i1, i2, i3, i4, i5, i6, i7,
		i8, i2_, t0, t1, t2, t3, indexpoint;
	static const Polygon exterior, interior, namearea;	
	static const ShapeType smType;
};
#endif
