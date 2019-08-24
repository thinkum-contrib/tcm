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
#include "gdviewer.h"
#include "gdwindow.h"
#include "gdupdatenodeshapetypecmd.h"

GDViewer::GDViewer(Config *c, GDWindow *w): DiagramViewer(c, w) {
	SetShowIndexes(False);
}

void GDViewer::UpdateNodeShapeType(int toType) {
	SetStatus("action: Update node shape type");
	List<int *> types;
        types.add(new int(Code::BOX));
        types.add(new int(Code::ELLIPSE));
        types.add(new int(Code::SQUARE));
        types.add(new int(Code::CIRCLE));
        types.add(new int(Code::HEXAGON));
        types.add(new int(Code::DIAMOND));
        types.add(new int(Code::TRIANGLE));
        types.add(new int(Code::ROUNDED_BOX));
        types.add(new int(Code::ELLIPSED_BOX));
        types.add(new int(Code::HORIZONTAL_BAR));
        types.add(new int(Code::VERTICAL_BAR));
        types.add(new int(Code::SOLID_HORIZONTAL_BAR));
        types.add(new int(Code::SOLID_VERTICAL_BAR));
        types.add(new int(Code::BLACK_DOT));
        types.add(new int(Code::BULLS_EYE));
        types.add(new int(Code::TEXT_BOX));
        types.add(new int(Code::NOTE_BOX));
        types.add(new int(Code::STICKMAN));
        types.add(new int(Code::CUBE));
        types.add(new int(Code::SUB_FOLDER));
        types.add(new int(Code::FOLDER));
        types.add(new int(Code::DISK));
        types.add(new int(Code::BUILDING_BLOCK));
        types.add(new int(Code::GD_BOUNDARY_SHAPE));
        types.add(new int(Code::GD_CONTROLLER_SHAPE));
        types.add(new int(Code::GD_ENTITY_SHAPE));
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new GDUpdateNodeShapeTypeCmd(
			GetCurView(), &types, toType));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
	types.clear();
}
