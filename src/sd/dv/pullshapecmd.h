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
#ifndef _PULLSHAPECMD_H
#define _PULLSHAPECMD_H

#include "command.h"
#include "polypoint.h"
#include "dpoint.h"
class NodeShape;
class GShape;

/// abstract command class for pulling a shape's tail.
class PullShapeCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	PullShapeCmd(GShape *s, int dir);
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	const char *GetName() const {return "pull shape tail";}
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
	int newEndPositionY;
	///
	int oldEndPositionY;
	///
	int GetPdirection() const {return pdirection;}
	///
	void SetPdirection(int d) {pdirection=d;}
	///
	void CalcEndPoint(const Point *p);
	///
	void DrawTail(const Point *np);
	///
	void Draw();
	///
	void Undraw() {
		Draw();
	}
private:
	///
	int pdirection;
};
#endif
