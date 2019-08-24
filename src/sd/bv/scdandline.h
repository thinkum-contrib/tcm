//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _SCDANDLINE_H
#define _SCDANDLINE_H

#include "line.h"

/// and line where begin and end point are the same, and where all intermediary
/// points are inside the corresponding node shape.
class SCDAndLine: public Line {
/*@Doc: {\large {\bf scope:} TSCD} */
public:
	///
	SCDAndLine(ShapeView *v, Grafport *g, GShape *n1, List<Point *> *line,
		bool Curved);
	///
	SCDAndLine(ShapeView *v, Grafport *g, GShape *n1, bool Curved);
	///
	virtual ~SCDAndLine();
	///
	Shape *Clone() {return new SCDAndLine(*this);}
	///
	int GetClassType() const {return Code::SCD_AND_LINE;}
	/// puts the end points on the inner border of the shape.
	virtual void CalcEndPoints();
	/// also checks that the points are inside the shape.
	virtual void CalcPosition();
};
#endif
