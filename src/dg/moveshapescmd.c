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
#include "moveshapescmd.h"

MoveShapesCmd::MoveShapesCmd(ShapeView *v, List<GShape *> *s): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	shapes = new List<GShape *> (*s);
	oldPositions = new List<Point *>;
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Point *pt = new Point(*(shapes->cur()->GetPosition()));
		oldPositions->add(pt);
	}
}

MoveShapesCmd::~MoveShapesCmd() {
	oldPositions->clear();
	delete oldPositions;
	delete shapes;
}

void MoveShapesCmd::UnExecute() {
	if (shapes->first() && oldPositions->first()) {
		do {
			Shape *shape = shapes->cur();
			Point d = *oldPositions->cur() - *shape->GetPosition();
			shape->UpdateMove(&d);
		} while(shapes->next() && oldPositions->next());
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if ( shape->IsNodeShape() )
			view->GetViewer()->ShapePositionUpdate(shape);
	}
	Command::UnExecute();
}
