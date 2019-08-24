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
//------------------------------------------------------------------------------
#ifndef _DRAGHANDLE_H
#define _DRAGHANDLE_H

#include "dragshapecmd.h"
class Line;

/// command class for dragging line handles.
class DragHandleCmd: public DragShapeCmd {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DragHandleCmd(Line *line, unsigned which);
	///
	void Execute();
	///
	void UnExecute();
	///
	void Executable();
	///
	void DrawOutLine(const Point *delta);
	///
	const char *GetName() const {return "move handle";}
protected:
	///
	void Erase();
	///
	void Redraw();
	///
	void ReverseDelta();
	///
	Point *GetOldPt() {return &oldPt;}
	///
	Point *GetNewPt() {return &newPt;}
	///
	Line *GetLine() {return line;}
	///
	void DrawLines(const Point *p1, const Point *p2, const Point *p3);
	///
	unsigned GetHandleNr() {return handleNr;}
	///
	virtual void CalcPoints();
private:
	///
	Point oldPt;
	///
	Point newPt;
	///
	Line *line;
	///
	unsigned handleNr;
};
#endif
