////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "shapeview.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "deletehandlecmd.h"

DeleteHandleCmd::DeleteHandleCmd(Line *s, unsigned n): 
		Command(s->GetView()->GetViewer()->GetDiagram(),
        	        s->GetView()->GetViewer()) {
	line = s;
	oldPoint = *(*(line->GetLine()))[n];
	whichHandle = n;
}

void DeleteHandleCmd::Execute() {
	Command::Execute();
	line->Undraw();
	line->RemovePoint(whichHandle);
	// recalculate Name Position
	if (line->NrPoints() > 2)
		line->SetLineNumber(line->NrPoints()/2);
	else
		line->SetLineNumber(1);
	line->CalcPosition();
	line->Draw();
	if (line->NrPoints() == 2) {
                line->GetView()->MultipleLines(line);
                line->GetView()->MultipleLinesPosUpdate(line);
	}
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
                line->GetView()->GetViewer()->ShapePositionUpdate(line);
}

void DeleteHandleCmd::UnExecute() {
	Command::UnExecute();
	line->Undraw();
	line->AddPoint(&oldPoint, whichHandle);
	line->Draw();
	// line was straight?
	if (line->NrPoints() == 3) {
		// update order+count of remaining straight lines
                // between end1 and end2.
                List<GShape *> lines;
                line->GetView()->CompleteShapes(&lines,
				line->GetFromShape(), line->GetToShape());
                for (lines.first(); !lines.done(); lines.next()) {
                        Line *line2 = (Line *)lines.cur();
                        if (line2->NrPoints() == 2) {
                                line->GetView()->MultipleLines(line2);
                                line->GetView()->MultipleLinesPosUpdate(line2);
				return;
                        }
                }
	}
	if (Toolkit::EditorWithInterEdgeConnections(GetMainWindow()->GetTool()))
                line->GetView()->GetViewer()->ShapePositionUpdate(line);
}
