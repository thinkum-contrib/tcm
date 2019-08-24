////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "line.h"
#include "addhandlecmd.h"
#include "diagramviewer.h"
#include "shapeview.h"

AddHandleCmd::AddHandleCmd(Line *s, int x, int y, unsigned n): 
			DragHandleCmd(s, n) { 
	GetOldPt()->x = x;
	GetOldPt()->y = y;
	addPosition = n;
}

void AddHandleCmd::Executable() {
	Erase();
	GetLine()->AddPoint(GetNewPt(), addPosition);
	// reset Name Position
	GetLine()->SetLineNumber(GetLine()->NrPoints()/2);
	Redraw();
	// line was straight?
        if (GetLine()->NrPoints() == 3) {
                List<GShape *> lines;
                GetLine()->GetView()->CompleteShapes(&lines, 
			GetLine()->GetFromShape(), GetLine()->GetToShape());
                for (lines.first(); !lines.done(); lines.next()) {
                        Line *line2 = (Line *)lines.cur();
                        if (line2->NrPoints() == 2) {
                                GetLine()->GetView()->MultipleLines(line2);
                                GetLine()->GetView()->MultipleLinesPosUpdate(line2);
				return;
                        }
                }
        }
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
		GetLine()->GetView()->GetViewer()->ShapePositionUpdate(GetLine());
}

void AddHandleCmd::UnExecute() {
	Command::UnExecute();
	ReverseDelta();
	Erase();
	GetLine()->RemovePoint(addPosition);
	Redraw();
	if (GetLine()->NrPoints() == 2) {
                GetLine()->GetView()->MultipleLines(GetLine());
                GetLine()->GetView()->MultipleLinesPosUpdate(GetLine());
        }
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
		GetLine()->GetView()->GetViewer()->ShapePositionUpdate(GetLine());
}

void AddHandleCmd::DrawOutLine(const Point *d) {
        Point p1 = *GetOldPt() + ScaleCorrect(d);
        GetView()->Snap(&p1);
        // get left and rigth points.
	Point p2 = *(*GetLine()->GetLine())[addPosition-1];
	Point p3 = *(*GetLine()->GetLine())[addPosition];
        DrawLines(&p1, &p2, &p3);
}

void AddHandleCmd::CalcPoints() {
        Point pt = *GetOldPt();
        pt = pt + *GetDelta();
        if (pt.x <= 0)
                pt.x = Shape::HANDLE_WIDTH/2;
        if (pt.y <= 0)
                pt.y = Shape::HANDLE_WIDTH/2;
        GetView()->Snap(&pt);
        GetNewPt()->x = pt.x;
        GetNewPt()->y = pt.y;
}

