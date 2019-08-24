////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "gshape.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "drawwindow.h"
#include "dragshapecmd.h"

DragShapeCmd::DragShapeCmd(Shape *s): 
	Command(s->GetView()->GetViewer()->GetDiagram(), 
	s->GetView()->GetViewer()) {

	view = s->GetView();
	shape = s;
	oldPosition = *shape->GetPosition();
}

void DragShapeCmd::TrackMouse(TrackType aPhase,
		Point *anchorPoint, Point *previousPoint, Point *nextPoint) {
	Point d;
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetCursor(MouseCursor::FLEUR);
			d = *nextPoint - *anchorPoint;
			DrawOutLine(&d);
			break;
		case TRACK_DRAG:
			d = *previousPoint - *anchorPoint;
			DrawOutLine(&d);
			d = *nextPoint - *anchorPoint;
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

void DragShapeCmd::DrawOutLine(const Point *d) {
	Point p1 = *(shape->GetPosition());
	Point p2 = ScaleCorrect(d);
	Point pt = p1 + p2;
	shape->DrawOutLine(&pt);
}

void DragShapeCmd::Execute() {
	Point p = oldPosition + delta;
	view->GetViewer()->Snap(&p);
	p = p - oldPosition;
	if (p == Point::ZERO) {
		SayAborted();
		Abort();
		return;
	}
	Command::Execute();
	Executable();
}

void DragShapeCmd::UnExecute() {
	Command::UnExecute();
	// set to virtual moved position (probably off screen).
	Point virtualPt = Point (oldPosition + delta);
	Point virtualDelta = *shape->GetPosition() - virtualPt; 
	delta = delta + virtualDelta;
	delta.x = -delta.x;
	delta.y = -delta.y;
	Executable();
}

void DragShapeCmd::ReExecute() {
	delta.x = -delta.x;
	delta.y = -delta.y;
	Command::Execute();
	Executable();
}

void DragShapeCmd::Executable() {
	shape->UpdateMove(&delta);
	if (!shape->IsTextShape())
		view->GetViewer()->ShapePositionUpdate((GShape *)shape);
	GetMainWindow()->FitDocument();
}
