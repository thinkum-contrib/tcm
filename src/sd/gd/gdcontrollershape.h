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
#ifndef _GD_CONTROLLER_SHAPE_H
#define _GD_CONTROLLER_SHAPE_H

#include "nodeshape.h"

/// shape for controller class.
class GDControllerShape: public NodeShape {
/*@Doc: {\large {\bf scope:} TGD} */
public:
	///
	GDControllerShape(ShapeView *v, Grafport *g, double x, double y);
	///
	GDControllerShape(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new GDControllerShape(*this);}
protected:

private:
	static const PolyPoint cs1, cs2;
	static const Polygon boundary;
	static const ShapeType csType;
};
#endif
