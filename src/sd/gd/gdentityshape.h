//-----------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2003, Universiteit Twente.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
#ifndef _GD_ENTITY_SHAPE_H
#define _GD_ENTITY_SHAPE_H

#include "nodeshape.h"

/// shape for boundary class.
class GDEntityShape: public NodeShape {
/*@Doc: {\large {\bf scope:} TGD} */
public:
	///
	GDEntityShape(ShapeView *v, Grafport *g, double x, double y);
	///
	GDEntityShape(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new GDEntityShape(*this);}
protected:

private:
	static const Polygon boundary;
	static const ShapeType esType;
};
#endif
