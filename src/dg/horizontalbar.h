//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _HORIZONTALBAR_H
#define _HORIZONTALBAR_H

#include "nodeshape.h"

/// box class with undrawn left and right sides.
class HorizontalBar: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	HorizontalBar(ShapeView *v, Grafport *g, double x, double y);
	///
	HorizontalBar(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new HorizontalBar(*this);}
protected:

private:
	static const Polygon exterior;
	static const ShapeType hbType;
};
#endif
