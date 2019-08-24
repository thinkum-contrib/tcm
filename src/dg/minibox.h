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
#ifndef _MINIBOX_H
#define _MINIBOX_H

#include "box.h"

/// small box class, having fixed min. width and height.
class MiniBox: public Box {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	MiniBox(ShapeView *v, Grafport *g, int x, int y, 
		int w = MIN_WIDTH, int h = MIN_HEIGHT);
	///
	MiniBox(const NodeShape &c);
	///
	Shape *Clone() {return new MiniBox(*this);}
	///
	int GetClassType() const {return Code::MINI_BOX;}
private:
	///
	void Init();
	///
        bool HasMinSize() {return True;}
};
#endif
