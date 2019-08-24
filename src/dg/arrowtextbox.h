//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _ARROWTEXTBOX_H
#define _ARROWTEXTBOX_H

#include "nodeshape.h"
class TRViewer;

/// text box class having a small downwards pointing arrow on top.
class ArrowTextBox: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ArrowTextBox(ShapeView *v, Grafport *g, double x, double y);
	///
	ArrowTextBox(const NodeShape &c);
	///
	/* virtual */ Shape *Clone() {return new ArrowTextBox(*this);}
	///
	virtual int GetTopMost() const;

protected:

private:
	static const PolyPoint i0, i1, i2, i3, i4;
	static const Polygon interior, exterior;
	static const ShapeType atType;
	static const int ARROWLEN;
};
#endif
