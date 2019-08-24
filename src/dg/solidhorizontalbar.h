//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
// Author: Frank Dehne (frank@cs.vu.nl) 
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
#ifndef _SOLIDHORIZONTALBAR_H
#define _SOLIDHORIZONTALBAR_H

#include "nodeshape.h"
 
/// A solid horizontal bar with fixed height 1
class SolidHorizontalBar: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	SolidHorizontalBar(ShapeView *v, Grafport *g, double x, double y);
	///
	SolidHorizontalBar(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new SolidHorizontalBar(*this);}
	///
	bool ReadMembers(InputFile *ifile, double format);
protected:

private:
	static const PolyPoint p0, p1, p2, p3;
	static const Polygon exterior;
	static const ShapeType shType;
};
#endif
