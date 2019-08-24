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
#include "diagramviewer.h"
#include "diagram.h"
#include "updatecurvecmd.h"

UpdateCurveCmd::UpdateCurveCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	lines = new List<Line *>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (shape->IsLine()) {
			Line *line = (Line *)shape;
			if (line->IsCurved() || line->NrPoints()==4) {
				lines->add(line);
			}
		}
	}
}

UpdateCurveCmd::~UpdateCurveCmd() {
	delete lines;
}

void UpdateCurveCmd::Execute() {
	if (!lines->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no lines need to be converted");
		Abort();
		return;
	}
	for (lines->first(); !lines->done(); lines->next()) 
		lines->cur()->UpdateCurve(!lines->cur()->IsCurved());
	Command::Execute();
}

void UpdateCurveCmd::UnExecute() {
	for (lines->first(); !lines->done(); lines->next()) 
		lines->cur()->UpdateCurve(!lines->cur()->IsCurved());
	Command::UnExecute();
}
