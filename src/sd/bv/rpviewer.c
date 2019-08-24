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
#include "rpviewer.h"
#include "rpwindow.h"
#include "shapeview.h"
#include "gshape.h"
#include "rpupdatenodeshapetypecmd.h"

RPViewer::RPViewer(Config *c, RPWindow *d): DiagramViewer(c, d) { }

void RPViewer::UpdateNodeShapeType(int boxType) {
        SetStatus("action: Update node shape type");
        List<int *> types;
        types.add(new int(Code::MINI_ELLIPSE));
        types.add(new int(Code::ROUNDED_BOX));
        if (GetCurView()->NrSelected() > 0) {
                NewCommand(new RPUpdateNodeShapeTypeCmd(
                        GetCurView(), &types, boxType));
                ExecuteCommand();
        }
        else
                EmptySelectionMessage();
        types.clear();
}

void RPViewer::UnlabelNodeShapes() {
	string empty;
	List<ShapeView *> *v = GetViews();
	for (v->first(); !v->done(); v->next()) {
                ShapeView *view = v->cur();
        	List<GShape *> *shapes = view->GetShapes();
		for (shapes->first(); !shapes->done(); shapes->next()) {
			GShape *shape = shapes->cur();
			if (shape->GetClassType() == Code::MINI_ELLIPSE)
				shape->UpdateNameString(&empty);
		}
	}

}
