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
#include "gdupdatenodeshapetypecmd.h"
#include "square.h"
#include "box.h"
#include "circle.h"
#include "diamond.h"
#include "notebox.h"
#include "triangle.h"
#include "hexagon.h"
#include "roundedbox.h"
#include "ellipsedbox.h"
#include "horizontalbar.h"
#include "stickman.h"
#include "verticalbar.h"
#include "solidhorizontalbar.h"
#include "solidverticalbar.h"
#include "textbox.h"
#include "miniellipse.h"
#include "blackdot.h"
#include "bullseye.h"
#include "folder.h"
#include "subfolder.h"
#include "disk.h"
#include "cube.h"
#include "buildingblock.h"

#include "gdboundaryshape.h"
#include "gdcontrollershape.h"
#include "gdentityshape.h"

GDUpdateNodeShapeTypeCmd::GDUpdateNodeShapeTypeCmd(ShapeView *v, 
		List<int *> *l, int n): UpdateNodeShapeTypeCmd(v, l, n) {
	TransformAll();
}

Thing *GDUpdateNodeShapeTypeCmd::Transform(Thing *thing) {
        NodeShape *oldShape = (NodeShape *)thing;
	Thing *newShape;
	switch ( toType ) {
	case Code::BOX:
		newShape = new Box(*oldShape);
		break;
	case Code::ELLIPSE:
		newShape = new Ellipse(*oldShape);
		break;
	case Code::SQUARE:
		newShape = new Square(*oldShape);
		break;
	case Code::CIRCLE:
		newShape = new Circle(*oldShape);
		break;
	case Code::DIAMOND:
		newShape = new Diamond(*oldShape);
		break;
	case Code::HEXAGON:
		newShape = new Hexagon(*oldShape);
		break;
	case Code::TRIANGLE:
		newShape = new Triangle(*oldShape);
		break;
	case Code::HORIZONTAL_BAR:
		newShape = new HorizontalBar(*oldShape);
		break;
	case Code::VERTICAL_BAR:
		newShape = new VerticalBar(*oldShape);
		break;
	case Code::ROUNDED_BOX:
		newShape = new RoundedBox(*oldShape);
		break;
	case Code::ELLIPSED_BOX:
		newShape = new EllipsedBox(*oldShape);
		break;
	case Code::SOLID_HORIZONTAL_BAR:
		newShape = new SolidHorizontalBar(*oldShape);
		break;
	case Code::SOLID_VERTICAL_BAR:
		newShape = new SolidVerticalBar(*oldShape);
		break;
	case Code::BLACK_DOT:
		newShape = new BlackDot(*oldShape);
		break;
	case Code::BULLS_EYE:
		newShape = new BullsEye(*oldShape);
		break;
	case Code::TEXT_BOX:
		newShape = new TextBox(*oldShape);
		break;
	case Code::NOTE_BOX:
		newShape = new NoteBox(*oldShape);
		break;
	case Code::STICKMAN:
		newShape = new StickMan(*oldShape);
		break;
	case Code::CUBE:
		newShape = new Cube(*oldShape);
		break;
	case Code::FOLDER:
		newShape = new Folder(*oldShape);
		break;
	case Code::DISK:
		newShape = new Disk(*oldShape);
		break;
	case Code::SUB_FOLDER:
		newShape = new SubFolder(*oldShape);
		break;
	case Code::BUILDING_BLOCK:
		newShape = new BuildingBlock(*oldShape);
		break;
	case Code::GD_BOUNDARY_SHAPE:
		newShape = new GDBoundaryShape(*oldShape);
		break;
	case Code::GD_CONTROLLER_SHAPE:
		newShape = new GDControllerShape(*oldShape);
		break;
	case Code::GD_ENTITY_SHAPE:
		newShape = new GDEntityShape(*oldShape);
		break;
	default:
		error("%s, %d: cannot convert node shape type (%d -> %d)\n",
			__FILE__, __LINE__, oldShape->GetClassType(), toType);
		return 0;
	}
//	int oldType = oldShape->GetClassType();
//	int newType = newShape->GetClassType();
//	if (SolidShape(oldType) && !SolidShape(newType)) {
//		((NodeShape *)newShape)->SetFillStyle(FillStyle::UNFILLED);
//		((NodeShape *)newShape)->SetLineStyle(LineStyle::SOLID);
//	}
//	if (oldType == Code::TEXT_BOX) {
//		((NodeShape *)newShape)->SetLineStyle(LineStyle::SOLID);
//	}
	return newShape;
}

bool GDUpdateNodeShapeTypeCmd::SolidShape(int type) {
	return (type == Code::BLACK_DOT || type == Code::SOLID_VERTICAL_BAR ||
	        type == Code::SOLID_HORIZONTAL_BAR);
}
