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
#include "line.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "draghandlecmd.h"

DragHandleCmd::DragHandleCmd(Line *l, unsigned n): DragShapeCmd(l) {
	line = l;
	handleNr = n;
	oldPt = *(*line->GetLine())[handleNr];
}

void DragHandleCmd::CalcPoints() {
	oldPt = *(*line->GetLine())[handleNr];
	Point pt = oldPt;
	pt = pt + *GetDelta();
	if (pt.x <= 0)
		pt.x = Shape::HANDLE_WIDTH/2;
	if (pt.y <= 0)
		pt.y = Shape::HANDLE_WIDTH/2;
	GetView()->Snap(&pt);
	newPt = pt;
}

void DragHandleCmd::Erase() {
	line->Undraw();
	CalcPoints();
}

void DragHandleCmd::Redraw() {
	line->CalcPosition();
	line->Draw();
}

void DragHandleCmd::Execute() {
	CalcPoints();
	if (newPt == oldPt) {
		SayAborted();
		Abort();
		return;
	}
	Command::Execute();
	Executable();
}

void DragHandleCmd::Executable() {
	line->Undraw();
	line->SetPoint(&newPt, handleNr);
	line->CalcEndPoint(&newPt, handleNr);
	Redraw();
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
                line->GetView()->GetViewer()->ShapePositionUpdate(line);
}

void DragHandleCmd::UnExecute() {
	Command::UnExecute();
	ReverseDelta();
	line->Undraw();
	line->SetPoint(&oldPt, handleNr);
	line->CalcEndPoint(&oldPt, handleNr);
	Redraw();
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
                line->GetView()->GetViewer()->ShapePositionUpdate(line);
}

void DragHandleCmd::ReverseDelta() {
	Point virtualPt = Point (oldPt + *GetDelta());
	Point virtualDelta = newPt - virtualPt; 
	Point d = *GetDelta() + virtualDelta;
	d = -d;
	SetDelta(&d);
}

void DragHandleCmd::DrawLines(const Point *p1, const Point *p2, 
				const Point *p3) {
	// feedback of handle
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black");
	GetGrafport()->DrawRectangle(p1->x - Shape::HANDLE_WIDTH/2, 
		p1->y - Shape::HANDLE_WIDTH/2, 
		Shape::HANDLE_WIDTH, Shape::HANDLE_WIDTH);
	// feedback of lines
	GetGrafport()->DrawLine(p1->x, p1->y, p2->x, p2->y);
	GetGrafport()->DrawLine(p1->x, p1->y, p3->x, p3->y);
}

void DragHandleCmd::DrawOutLine(const Point *d) {
	Point p1 = oldPt + ScaleCorrect(d);
	GetView()->Snap(&p1);
	Point p2, p3;
	// get left and right line segments
	if (check(line->GetSegments(oldPt, &p2, &p3)))
		DrawLines(&p1, &p2, &p3);
}
