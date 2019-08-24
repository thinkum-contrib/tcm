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
#include "drawwindow.h"
#include "messagedialog.h"
#include "alignnodeshapescmd.h"
#include "diagramviewer.h"

AlignNodeShapesCmd::AlignNodeShapesCmd(ShapeView *v, List<GShape *> *s, 
		NodeAlign::Type t): MoveShapesCmd(v, s) {
	alignType = t;
}

void AlignNodeShapesCmd::Execute() {
	int value = 0;
	List<GShape *> *s = GetShapes(); 
	if (!s->first())
		return;
	GShape *shape = s->cur();
	if ( ! shape->IsNodeShape() ) {
		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::ERROR))->Show("Error",
			"The first selected shape should not be a line");
		GetMainWindow()->SetStatus("aborted: first shape is a line");
		Abort();
		return;
	}
	switch(alignType) {
		case NodeAlign::TOP:
			value = shape->GetTopMost();
			break;
		case NodeAlign::LEFT:
			value = shape->GetLeftMost();
			break;
		case NodeAlign::BOTTOM:
			value = shape->GetBottomMost();
			break;
		case NodeAlign::RIGHT:
			value = shape->GetRightMost();
			break;
		case NodeAlign::HORIZONTAL:
			value = shape->GetPosition()->y;
			break;
		case NodeAlign::VERTICAL:
			value = shape->GetPosition()->x;
			break;
		default:
			error("unknown align type\n");
			break;
	}
	bool nodesFound = False;
	while (s->next()) {
		shape = s->cur();
		if ( shape->IsNodeShape() ) {
			nodesFound = True;
			Point pos = *shape->GetPosition();
			// align to this value
			switch(alignType) {
				case NodeAlign::TOP:
					pos.y += value - shape->GetTopMost();
					break;
				case NodeAlign::LEFT:
					pos.x += value - shape->GetLeftMost();
					break;
				case NodeAlign::BOTTOM:
					pos.y += value - shape->GetBottomMost();
					break;
				case NodeAlign::RIGHT:
					pos.x += value - shape->GetRightMost();
					break;
				case NodeAlign::HORIZONTAL:
					pos.y = value;
					break;
				case NodeAlign::VERTICAL:
					pos.x = value;
					break;
				default:
					break;
			}
			// shape->UpdatePosition(&pos);
			shape->UpdatePosition(&pos, False);
			GetView()->GetViewer()->ShapePositionUpdate(shape);
		}
	}
	if ( ! nodesFound ) {
		(new MessageDialog(GetMainWindow()->GetWidget(), 
		     MessageDialog::ERROR))->Show("Error",
		     "you need at least two node shapes for alignment");
		GetMainWindow()->SetStatus(
			"aborted: less than two nodes selected");
		Abort();
		return;
	}
	Command::Execute();
}
