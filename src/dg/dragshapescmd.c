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
#include "dragshapescmd.h"

DragShapesCmd::DragShapesCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	shapes = new List<GShape *>(*view->GetSelection());
	oldPositions = new List<Point *>;
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Point *pt = new Point(*(shapes->cur()->GetPosition()));
		oldPositions->add(pt);
	}
}

DragShapesCmd::~DragShapesCmd() {
	oldPositions->clear();
	delete oldPositions;
	delete shapes;
}

void DragShapesCmd::TrackMouse(TrackType aPhase,
		Point *anchorPoint, Point *previousPoint, Point *nextPoint) {
	Point d;
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetCursor(MouseCursor::FLEUR);
			d = *nextPoint - *anchorPoint;
			DrawOutLines(d);
			break;
		case TRACK_DRAG:
			d = *previousPoint - *anchorPoint;
			DrawOutLines(d);
			d = *nextPoint - *anchorPoint;
			DrawOutLines(d);
			break;
		case TRACK_RELEASE:
			d = *previousPoint - *anchorPoint;
			DrawOutLines(d);
			d = *nextPoint - *anchorPoint;
			delta = ScaleCorrect(&d);
			// correction for bumping up near the edge.
			if (delta.x < 0 || delta.y < 0) {
				Point tl, br;
				view->CalcSizeShapes(shapes, tl, br);
				view->Snap(&tl);
				if (-delta.x > tl.x)
					delta.x = -tl.x;
				if (-delta.y > tl.y)
				delta.y = -tl.y;
			}
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}

void DragShapesCmd::Execute() {
	Point oldPosition = *(*oldPositions)[0];
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

void DragShapesCmd::UnExecute() {
	if (shapes->first() && oldPositions->first()) {
		do {
			Shape *shape = shapes->cur();
			Point d = *oldPositions->cur() - *shape->GetPosition();
			shape->UpdateMove(&d);
		} while(shapes->next() && oldPositions->next());
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		if ( shapes->cur()->IsNodeShape() )
			view->GetViewer()->ShapePositionUpdate(shapes->cur());
	}
	Command::UnExecute();
}

void DragShapesCmd::ReExecute() {
	Command::Execute();
	Executable();
}

void DragShapesCmd::Executable() {
	view->GetViewer()->UpdateMoveShapes(shapes, &delta);
	GetMainWindow()->FitDocument();
}

void DragShapesCmd::DrawOutLines(Point &d) {
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Shape *shape = shapes->cur();
		Point p1 = *(shape->GetPosition());
		Point p2 = ScaleCorrect(&d);
		Point pt = p1 + p2;
		shape->DrawOutLine(&pt);
	}
}
