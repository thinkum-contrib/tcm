//-----------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl)
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
#ifndef _DISK_H
#define _DISK_H

#include "nodeshape.h"

/// Disk shape class.
class Disk: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Disk(ShapeView *v, Grafport *g, double x, double y);
	///
	Disk(const NodeShape &);
	///
	/* virtual */ Shape *Clone() {return new Disk(*this);}

protected:

private:
	static const PolyPoint p0, p1, p3, p4, i0, i1, i2, t0, t1, c0, c1;
	static const Polygon exterior, interior, namearea, childarea;
	static const ShapeType diskType;
};
#endif
