//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#ifndef _FLASHARROW_H
#define _FLASHARROW_H

#include "line.h"

/// An arrow with some kind of lightning flash.
class FlashArrow: public Line { 
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	FlashArrow(ShapeView *s, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	FlashArrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	Shape *Clone() {return new FlashArrow(*this);}
	///
	int GetClassType() const {return Code::FLASH_ARROW;}
protected:
	/// 
	void DrawLine(const DPoint *ep1, const DPoint *ep2, int b, int e);
	/// 
	void DrawBezier(const DPoint *ep1, const DPoint *ep2);
	/// 
	void DrawLinePart();  
};
#endif
