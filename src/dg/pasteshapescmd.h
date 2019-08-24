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
#ifndef _PASTESHAPESCMD_H
#define _PASTESHAPESCMD_H

#include "command.h"
class Subject;
class GShape;
class ShapeView;
class Diagram;

/// command class for pasting shapes.
class PasteShapesCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	PasteShapesCmd(ShapeView *v);
	///
	PasteShapesCmd(ShapeView *v, bool);
	///
	virtual ~PasteShapesCmd();
	///
	void MakeBox();
	///
	void Execute();
	///
	void UnExecute();
	///
	void Abort();
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	void DrawOutLine(const Point *center);
	///
	const char *GetName() const {return "paste";}
protected:
	///
	ShapeView *GetView() const {return view;}
	///
	List<Subject *> *GetSubjects() const {return subjects;}
	///
	void SetSubjects(List<Subject *> *s) {subjects=s;}
	///
	List<GShape *> *GetShapes() {return shapes;}
	///
	void SetShapes(List<GShape *> *s) {shapes=s;}
	///
	const Point *GetDelta() {return &delta;}
private:
	///
	List<Subject *> *subjects;
	///
	List<GShape *> *shapes;
	///
	Point delta;
	///
	Point center;
	///
	Point anchor;
	///
	int width; 
	///
	int height;
	///
	ShapeView *view;
	///
	Diagram *diagram;
};
#endif
