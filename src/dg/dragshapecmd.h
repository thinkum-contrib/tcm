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
#ifndef _DRAGSHAPECMD_H
#define _DRAGSHAPECMD_H

#include "command.h"
class Shape;
class ShapeView;

/// command class for dragging a shape.
class DragShapeCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DragShapeCmd(Shape *shape);
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
	virtual void Executable();
	///
	const char *GetName() const {return "move shape";}
protected:
	///
	virtual void DrawOutLine(const Point *delta);
	///
	Shape *GetShape() const {return shape;}
	///
	ShapeView *GetView() const {return view;}
	///
	const Point *GetDelta() const {return &delta;}
	///
	void SetDelta(const Point *p) {delta=*p;}
	///
	const Point *GetOldPosition() const {return &oldPosition;}
	///
	void SetOldPosition(const Point *p) {oldPosition=*p;}
private:
	///
	Shape *shape;
	///
	ShapeView *view;
	///
	Point oldPosition;
	///
	Point delta;
};
#endif
