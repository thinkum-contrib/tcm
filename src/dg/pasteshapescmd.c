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
#include "grafport.h"
#include "subject.h"
#include "gshape.h"
#include "shapeview.h"
#include "subjects.h"
#include "shapes.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "buffer.h"
#include "drawwindow.h"
#include "assoclist.h"
#include "pasteshapescmd.h"

PasteShapesCmd::PasteShapesCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(),v->GetViewer()) {
	view = v;
	diagram = v->GetViewer()->GetDiagram();
	// empty dictionary.
	diagram->GetAssocList()->clear();
	// get copy of buffer contents.
	subjects = v->GetViewer()->GetBuffer()->GetSubjectsCopy();
	shapes = v->GetViewer()->GetBuffer()->GetShapesCopy();
	for (shapes->first(); !shapes->done(); shapes->next()) {
		// shapes might come from other view.
		Shape *shape = shapes->cur();
		shape->SetView(view);
		shape->SetVisible(True);
	}
	MakeBox();
}

PasteShapesCmd::PasteShapesCmd(ShapeView *v, bool): 
		Command(v->GetViewer()->GetDiagram(),v->GetViewer()) {
	diagram = v->GetViewer()->GetDiagram();;
	view = v;
}

void PasteShapesCmd::MakeBox() {
	Point topLeft, bottomRight;
	view->CalcSizeShapes(shapes, topLeft, bottomRight);
	width = bottomRight.x - topLeft.x;
	if (width == 0)
		width = 10;
	height = bottomRight.y - topLeft.y;
	if (height == 0)
		height = 10;
	center.x = topLeft.x + width/2;
	center.y = topLeft.y + height/2;
	GetViewer()->SetPasting(True);
	Point pt;
	pt.x = int(0.5 + Scale(topLeft.x));
	pt.y = int(0.5 + Scale(topLeft.y));
	// Start mouse operation
	TrackMouse(TRACK_PRESS, &pt, &pt, &pt);
}

void PasteShapesCmd::Execute() {
	view->AddShapes(shapes);
	diagram->AddSubjects(subjects);
	view->GetViewer()->UpdateDuplicationMarks(subjects);
	GetMainWindow()->FitDocument();
	Command::Execute();
}

void PasteShapesCmd::UnExecute() {
	view->RemoveShapes(shapes);
	diagram->RemoveSubjects(subjects);
	Command::UnExecute();
}

PasteShapesCmd::~PasteShapesCmd() {
	if (!CmdDone()) {
		shapes->clear();
		subjects->clear();
	}
	delete subjects;
	delete shapes;
}

void PasteShapesCmd::TrackMouse(TrackType aPhase, Point *anchorPoint,
	Point*, Point *nextPoint) {

	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetCursor(MouseCursor::FLEUR);
			// draw
			delta = *nextPoint - *anchorPoint;
			DrawOutLine(&delta);
			// save
			anchor = *anchorPoint;
			break;
		case TRACK_DRAG:
			// erase
			DrawOutLine(&delta);
			// draw
			delta = *nextPoint - anchor;
			DrawOutLine(&delta);
			break;
		case TRACK_UP:
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			// erase
			DrawOutLine(&delta);
			delta = ScaleCorrect(&delta);
			view->DeselectAll();
			view->GetViewer()->MoveShapes(shapes, &delta);
			GetViewer()->SetPasting(False);
			GetViewer()->ExecuteCommand();
			break;
		case TRACK_RELEASE:
			break;
		default:
			error("unknown track type\n");
			break;
	}
}

void PasteShapesCmd::DrawOutLine(const Point *d) {
	Point p1 = center;
	Point p2 = ScaleCorrect(d);
	Point pt = p1 + p2;
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black");
	GetGrafport()->DrawRectangle(pt.x-width/2, pt.y-height/2, 
		width, height);
}

void PasteShapesCmd::Abort() {
	DrawOutLine(&delta);
	shapes->clear();
	subjects->clear();
	GetViewer()->SetPasting(False);
	SayAborted();
	Command::Abort();
}
