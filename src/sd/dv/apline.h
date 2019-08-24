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
#ifndef _APLINE_H
#define _APLINE_H

#include "line.h"
//#include "llist.h"
//#include "gshape.h"
//#include "lineend.h"

/// line class (abstract) having two extra text shape.
class APLine: public Line { 
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	APLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	APLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	APLine(const APLine &) ;
	///
	int GetClassType() const {return Code::T4_LINE;}

	/// Set also fromShape and toShape references.
	bool SetReferences(AssocList *);

	/// set anchors
	void SetAnchors();

	/// draw line+textshapes.
	void DrawShape(); 

	/// yep.
	bool IsLine() const {return True;}
	///
	virtual void DrawLine(const DPoint *ep1, const DPoint *ep2);

	/// Calculate begin and end-points (intersections with the shapes).
	virtual void CalcEndPoints();

	///
	bool CalcEndPoint(const Point *pt, unsigned int n);

	/// Calculate begin and end-points (intersections with the shapes).
	virtual void ReCalcEndPoints();

	/// ReCalculate begin and end-points (intersections with the shapes).
	virtual void ReCalcEndPoints(List<Point *> *orgline);

private:
	/// The points of the anchorpointline (aka handles).
	List<Point *> *apline;

	/// The anchorpointline (aka handles).
	Line *theline;

	///
	LineEnd apend1;
	///
	LineEnd apend2;

};
#endif
