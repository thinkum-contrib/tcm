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
#ifndef _ELLIPSIS_H
#define _ELLIPSIS_H

#include "box.h"

/// invisible box class, having three black dots.
class Ellipsis: public Box {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	static const int DOT_WIDTH;
	///
	static const int DOT_HEIGHT;
	///
	static const int ELLIPSIS_WIDTH;
	///
	static const int ELLIPSIS_HEIGHT;
	///
	Ellipsis(ShapeView *v, Grafport *g, int x, int y, 
		int w = ELLIPSIS_WIDTH, int h = ELLIPSIS_HEIGHT);
	///
	Ellipsis(const NodeShape &c);
	///
	Shape *Clone() {return new Ellipsis(*this);}
	///
	int GetClassType() const {return Code::ELLIPSIS;}
protected:
	/// draws no box only the three black dots.
	void DrawShape(); 		
};
#endif
