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
#include "rpupdatenodeshapetypecmd.h"
#include "roundedbox.h"
#include "miniellipse.h"
#include "rpdiagram.h"

RPUpdateNodeShapeTypeCmd::RPUpdateNodeShapeTypeCmd(
		ShapeView *v, List<int *> *l, int n): 
			UpdateNodeShapeTypeCmd(v, l, n) {
	TransformAll();
}

Thing *RPUpdateNodeShapeTypeCmd::Transform(Thing *thing) {
        NodeShape *oldShape = (NodeShape *)thing;
	NodeShape *newShape;
        if (toType == Code::ROUNDED_BOX) {
		newShape = new RoundedBox(*oldShape);
		newShape->SetTextShape();
		newShape->SetSize(RPDiagram::BOX_WIDTH, RPDiagram::BOX_HEIGHT);
	}
        else if (toType == Code::MINI_ELLIPSE) {
		MiniEllipse *e = new MiniEllipse(*oldShape);
		e->SetResizable(True);
		e->SetSize(RPDiagram::CIRCLE_WIDTH, RPDiagram::CIRCLE_WIDTH);
		string empty = "";
		e->SetNameString(&empty);
		e->SetResizable(False);
		newShape = e;
	}
        else {
                error("%s, %d: cannot convert class box type %d\n",
                	__FILE__, __LINE__, oldShape->GetClassType());
                return 0;
        }
	return newShape;
}

