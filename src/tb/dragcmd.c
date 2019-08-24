////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "tableviewer.h"
#include "table.h"
#include "dragcmd.h"
 
DragCmd::DragCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	delta = Point(0,0);
	oldPosition = Point(0,0);
}
 
void DragCmd::Execute() {
	Command::Execute();
	GetMainWindow()->FitDocument();
}
 
void DragCmd::UnExecute() {
	Command::UnExecute();
}
 
void DragCmd::TrackMouse(TrackType phase, Point *anchorPoint, 
			Point *previousPoint, Point *nextPoint) {
	Point d;
	switch(phase) {
		case TRACK_PRESS:
			d = *nextPoint - *anchorPoint;
			DrawOutLine(&d);
			break;
		case TRACK_DRAG:
			d = *previousPoint - *anchorPoint;
			DrawOutLine(&d);
			d = *nextPoint - *anchorPoint;
			delta = ScaleCorrect(&d);
			DrawOutLine(&d);
			break;
		case TRACK_RELEASE:
			d = *previousPoint - *anchorPoint;
			DrawOutLine(&d);
			d = *nextPoint - *anchorPoint;
			delta = ScaleCorrect(&d);
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}
