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
#ifndef _CREATEL2LEDGECMD_H
#define _CREATEL2LEDGECMD_H


#include "command.h"
#include "point.h"
#include "llist.h"
class Edge;
class Line;
class GShape;
class ShapeView;
class Diagram;

/// command class for creating edges between LifeLines
class CreateL2LEdgeCmd: public Command {
/*@Doc: {\large {\bf scope:} TSQD} */
public:
	///
	CreateL2LEdgeCmd(GShape *from);
	///
	virtual ~CreateL2LEdgeCmd();
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint, 
		Point *previousPoint, Point *nextPoint);
	///
	void Execute();
	///
	void UnExecute();
	///
	void ReExecute();
	///
	void Abort();
	///
	const char *GetName() const {return "create l2l edge";}

protected:
	///
	void AddPoint(Point *pt) {points->add(new Point(pt->x, pt->y));}
	///
	void EraseLines();
private:
	///
	Diagram *diagram;
	///
	ShapeView *view;
	///
	Edge *edge;
	///
	Line *line;
	///
	GShape *fromShape;
	///
	GShape *toShape;
	///
	List<Point *> *points;
	///
	Point abortPoint;
	///
	bool connectEdges;
};
#endif
