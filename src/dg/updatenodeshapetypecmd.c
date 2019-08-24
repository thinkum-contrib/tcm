////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
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
#include "updatenodeshapetypecmd.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "shapeview.h"
#include "line.h"
#include "nodeshape.h"

UpdateNodeShapeTypeCmd::UpdateNodeShapeTypeCmd(ShapeView *v, 
		List<int *> *l, int n): UpdateTypeCmd(v, l, n) {
	List<GShape *> *selection = v->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		int type = shape->GetClassType();
		if (n != type) {
			for (l->first(); !l->done(); l->next()) {
                                if (*l->cur() == type) {
					oldThings->add(shape);
				}
			}
		}
	}
}

void UpdateNodeShapeTypeCmd::Reverse(Thing *oldThing, Thing *newThing) {
	GShape *oldShape = (GShape *)oldThing;
	GShape *newShape = (GShape *)newThing;
	UpdateLines(oldShape, newShape);
	view->AddShape(newShape);
	view->RemoveShape(oldShape);
	newShape->AdjustSize();
	view->GetViewer()->ShapePositionUpdate(newShape);
}

void UpdateNodeShapeTypeCmd::UpdateLines(GShape *oldshape, GShape *newshape) {
	List<GShape *> *shapes = view->GetShapes();
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if (shape->IsLine()) {
			Line *line = (Line *)shape;
			if (line->GetFromShape() == oldshape)
				line->SetFromShape(newshape);
			if (line->GetToShape() == oldshape)
				line->SetToShape(newshape);
		}
	}
}
