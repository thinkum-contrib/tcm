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
#include "diagramviewer.h"
#include "shapeview.h"
#include "diagram.h"
#include "gshape.h"
#include "selectallcmd.h"

SelectAllCmd::SelectAllCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	oldSelection = new List<GShape *>(*view->GetSelection());
}

SelectAllCmd::~SelectAllCmd() {
	delete oldSelection;
}

void SelectAllCmd::Execute() {
	List<GShape *> *shapes = view->GetShapes();
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if (!shape->IsSelected() && shape->IsVisible())
			view->SelectShape(shape);
	} 
	SetCmdDone(True);
	SayCommited();
}

void SelectAllCmd::UnExecute() {
	view->DeselectAll();
	for (oldSelection->first(); !oldSelection->done(); 
	     oldSelection->next()) {
		GShape *shape = oldSelection->cur();
		view->SelectShape(shape);
	}
	SetCmdDone(False);
	SayUndone();
}
