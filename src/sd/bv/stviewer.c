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
#include "stwindow.h"
#include "diagram.h"
#include "stviewer.h"
#include "selectareacmd.h"
#include "sizeshapecmd.h"
#include "draghandlecmd.h"
#include "dragshapescmd.h"
#include "dragstlabelcmd.h"
#include "draghlinecmd.h"
#include "transitionarrow.h"
#include "nodeshape.h"

STViewer::STViewer(Config *c, STWindow *d): DiagramViewer(c, d) { }

TransitionArrow *STViewer::HitHLine(int x, int y) {
	List<GShape *> *shapes = GetCurView()->GetShapes();
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if (shape->GetClassType()==Code::TRANSITION_ARROW && 
		    shape->IsVisible()) {
			TransitionArrow *h = (TransitionArrow *)shape;
			if (h->HitHLine(x, y))
				return h;
		}
	}
	return 0;
}

Command *STViewer::Drag(int x, int y) {
	double x1 = GetScaler()->ScaleCorrect(x);
	double y1 = GetScaler()->ScaleCorrect(y);
	Line *line;
	int w;
	if ((line = GetCurView()->HitLineHandle(static_cast<int>(0.5 + x1), 
											static_cast<int>(0.5 + y1), w)))
		return new DragHandleCmd(line, w);
	TextShape *textShape;
	if ((textShape = GetCurView()->HitTextShape(static_cast<int>(0.5 + x1),
												static_cast<int>(0.5 + y1))))
		return new DragSTLabelCmd(textShape);
	// look for horizontal transition line to drag.
	GShape *shape;
	if ((shape = HitHLine(static_cast<int>(0.5 + x1), 
						  static_cast<int>(0.5 + y1))))
		return new DragHLineCmd((TransitionArrow *)shape);
	return DiagramViewer::Drag(x, y);
	//
	// look for nodes shapes.
        // else if ((shape = curView->HitNodeShape(x, y))) {
        //        if (shape->IsSelected() && (w = shape->HitHandles(x, y)) >= 0)
        //               return new SizeShapeCenterCmd(shape, w);
        //      else if (shape->IsSelected() && curView->NrSelected() > 1)
        //             return new DragShapesCmd(curView);
        //    else
        //           return new DragShapeCmd(shape);
        //}
	// else
	// 	return new SelectAreaCmd(GetCurView());
}
