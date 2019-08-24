////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "diagramviewer.h"
#include "diagram.h"
#include "updatelinewidthcmd.h"

UpdateLineWidthCmd::UpdateLineWidthCmd(ShapeView *v, unsigned n): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	lineWidth = n;
	shapes = new List<GShape *>;
	oldWidths = new List<unsigned>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (!shape->IsTextShape()) {
			unsigned i = ((GShape *)shape)->GetLineWidth();
			if (i != lineWidth) {
				shapes->add(shape);
				oldWidths->add(i);
			}
		}
	}
}

UpdateLineWidthCmd::~UpdateLineWidthCmd() {
	delete shapes;
	delete oldWidths;
}

void UpdateLineWidthCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be updated");
		Abort();
		return;
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = (GShape *)shapes->cur();
		shape->UpdateLineWidth(lineWidth);
	}
	GetViewer()->Refresh();
	Command::Execute();
}

void UpdateLineWidthCmd::UnExecute() {
	for (unsigned i=0; i<shapes->count(); i++) {
		GShape *shape = (GShape *)(*shapes)[i];
		shape->UpdateLineWidth((*oldWidths)[i]);
	}
	Command::UnExecute();
}
