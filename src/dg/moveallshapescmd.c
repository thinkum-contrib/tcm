////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "drawwindow.h"
#include "diagramviewer.h"
#include "shapeview.h"
#include "line.h"
#include "moveallshapescmd.h"

#define max(a,b) ((a)>(b)?(a):(b))

const int MoveAllShapesCmd::MOVE_DISTANCE = 20;

MoveAllShapesCmd::MoveAllShapesCmd(ShapeView *v, Document::MoveType t): 
		MoveShapesCmd(v,v->GetShapes()) {
	moveType = t;
}

void MoveAllShapesCmd::UnExecute() {
	Point p = -delta;
	UpdateMoveShapes(GetShapes(), &p);
	Command::UnExecute();
}

void MoveAllShapesCmd::Execute() {
	List<GShape *> *mshapes = GetShapes();
	if (!mshapes->first())
		return;
	if (moveType == Document::UP)
		delta = Point(0, -MOVE_DISTANCE);
	else if (moveType == Document::DOWN)
		delta = Point(0, MOVE_DISTANCE);
	else if (moveType == Document::LEFT)
		delta = Point(-MOVE_DISTANCE, 0);
	else if (moveType == Document::RIGHT)
		delta = Point(MOVE_DISTANCE, 0);
	else if (moveType == Document::CENTER) {
		Point center, newCenter;
		Point tl, br;
		double elWidth, elHeight;
		double w, h;
		GetViewer()->GetPageSize(w, h);
		GetView()->CalcSizeShapes(mshapes, tl, br);
		elWidth = Scale(br.x - tl.x);
		elHeight = Scale(br.y - tl.y);
		tl = Scale(&tl);
		br = Scale(&br);
		center.x = (br.x + tl.x)/2;
		center.y = (br.y + tl.y)/2;
		// fit it to the first page.
		newCenter.x = int(0.5 + max(w, elWidth) * 0.5);
		newCenter.y = int(0.5 + max(h, elHeight) * 0.5);
		// distance to move to new center point.
		GetView()->Snap(&newCenter);
		GetView()->Snap(&center);
		delta = newCenter - center;
	}
	delta = ScaleCorrect(&delta);
	// correction for moving off screen and making mess of diagram.
	if (moveType == Document::UP || moveType == Document::LEFT) {
		Point tl, br;
		GetView()->CalcSizeShapes(mshapes, tl, br);
		GetView()->Snap(&tl);
		if (moveType == Document::LEFT) {
			if (-delta.x > tl.x)
				delta.x = -tl.x;
		}
		else {  // Up 
			if (-delta.y > tl.y)
				delta.y = -tl.y;
		}
	}
	// move the shapes
	if (delta.x != 0 || delta.y != 0) {
		UpdateMoveShapes(mshapes, &delta);
		GetViewer()->Refresh();
		GetMainWindow()->FitDocument();
		Command::Execute();
	}
}

void MoveAllShapesCmd::UpdateMoveShapes(List<GShape *> *s, const Point *d){
	// move all shapes
	for (s->first(); !s->done(); s->next()) {
		Shape *shape = s->cur();
		shape->Undraw();
		shape->MoveRaw(d);
		shape->Draw();
	}
}
