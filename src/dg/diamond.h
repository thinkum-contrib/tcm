//------------------------------------------------------------------------------
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
#ifndef _DIAMOND_H
#define _DIAMOND_H

#include "nodeshape.h"

/// diamond shape class.
class Diamond: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Diamond(ShapeView *v, Grafport *g, double x, double y);
	///
        Diamond(const NodeShape &d);
	///
	/* virtual */ Shape *Clone() {return new Diamond(*this);}

protected:

private:
//	static const PolyPoint indexpoint;
	static const Polygon exterior, childarea;
	static const ShapeType diType;
};
#endif
