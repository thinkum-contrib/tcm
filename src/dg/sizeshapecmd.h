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
#ifndef _SIZESHAPECMD_H
#define _SIZESHAPECMD_H

#include "command.h"
#include "polypoint.h"
#include "dpoint.h"
class NodeShape;
class GShape;

/// abstract command class for resizing a shape.
class SizeShapeCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	SizeShapeCmd(GShape *shape, int direction);
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	void Execute();
	///
	void UnExecute();
protected:
	///
	NodeShape *shape;
	/// coordinates of the fix point of the figure.
	DPoint fixpoint;
	/// coordinates of the position of the shape.
	PolyPoint centre;
	/// coordinates of the moving corner of the shape.
	PolyPoint corner;
	///
	DPoint newCentre;
	///
	double newWidth;
	///
	double newHeight;
	///
	DPoint oldCentre;
	///
	double oldWidth;
	///
	double oldHeight;
	///
	int direction;
	///
	bool constrainX;
	///
	bool constrainY;
	///
	void CalcSize(const Point *p);
	///
	void Draw();
	///
	void Undraw() {
		Draw();
	}
};
#endif
