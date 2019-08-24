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
#include "diagram.h"
#include "diagramviewer.h"
#include "drawwindow.h"
#include "messagedialog.h"
#include "samesizecmd.h"

SameSizeCmd::SameSizeCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	diagram = v->GetViewer()->GetDiagram();
	shapes = new List<GShape *>(*v->GetSelection());
	oldSizes = new List<Point *>;
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Shape *shape = shapes->cur();
		Point *pt = new Point(shape->GetWidth(), shape->GetHeight());
		oldSizes->add(pt);
	}
}

SameSizeCmd::~SameSizeCmd() {
	delete shapes;
	oldSizes->clear();
	delete oldSizes;
}

void SameSizeCmd::Execute() {
	if (!shapes->first())
		return;
	// the first shape determines the size.
	GShape *shape = shapes->cur();
	int w = shape->GetWidth();
	int h = shape->GetHeight();
	if ( ! shape->IsNodeShape() ) {
		(new MessageDialog(GetMainWindow()->GetWidget(),
			MessageDialog::ERROR))->Show("Error", 
			"The first selected shape should not be a line");
		GetMainWindow()->SetStatus("aborted: first selected is a line");
		Abort();
		return;
	}
	bool nodesFound = False;
	while(shapes->next()) {
		shape = shapes->cur();
		if ( shape->IsNodeShape() ) {
			nodesFound = True;
			shape->UpdateSize(w, h);
			shape->GetView()->GetViewer()->
				ShapePositionUpdate(shape);
		}
	}
	if ( ! nodesFound ) {
		(new MessageDialog(GetMainWindow()->GetWidget(),
		     MessageDialog::ERROR))->Show("Error", 
		     "The selection should contain at least two node shapes");
		GetMainWindow()->SetStatus(
			"aborted: too few nodes are selected");
		Abort();
		return;
	}
	Command::Execute();
	GetMainWindow()->FitDocument();
}

void SameSizeCmd::UnExecute() {
	// restore old positions.
	if (shapes->first() && oldSizes->first()) {
		do {
			GShape *shape = shapes->cur();
			Point *pt = oldSizes->cur();
			shape->UpdateSize(pt->x, pt->y);
			if ( shape->IsNodeShape() )
				shape->GetView()->GetViewer()->
					ShapePositionUpdate(shape);
		} while (shapes->next() && oldSizes->next());
	}
	Command::UnExecute();
}
