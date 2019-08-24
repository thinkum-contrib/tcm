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
#include "grafport.h"
#include "gshape.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "selectareacmd.h"
#include <stdlib.h>

SelectAreaCmd::SelectAreaCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	oldSelection = new List<GShape *>(*(view->GetSelection()));
}

SelectAreaCmd::~SelectAreaCmd() {
	delete oldSelection;
}

void SelectAreaCmd::TrackMouse(TrackType aPhase,
		Point *anchorPoint, Point *previousPoint, Point *nextPoint) {
	int x, y, w, h, xx, yy;
	x = anchorPoint->x;
	y = anchorPoint->y;
	GetGrafport()->SetLineWidth(1);
        GetGrafport()->SetForegroundColor("black");
	switch(aPhase) {
		case TRACK_PRESS:
			w = nextPoint->x - x;
			h = nextPoint->y - y;
			xx = min(x, nextPoint->x);
			yy = min(y, nextPoint->y);
			GetGrafport()->DrawEditDashedRectangle(
					xx, yy, abs(w), abs(h));
			break;
		case TRACK_DRAG:
			w = previousPoint->x - x;
			h = previousPoint->y - y;
			xx = min(x, previousPoint->x);
			yy = min(y, previousPoint->y);
			GetGrafport()->DrawEditDashedRectangle(
					xx, yy, abs(w), abs(h));
			w = nextPoint->x - x;
			h = nextPoint->y - y;
			xx = min(x, nextPoint->x);
			yy = min(y, nextPoint->y);
			GetGrafport()->DrawEditDashedRectangle(
					xx, yy, abs(w), abs(h));
			break;
		case TRACK_RELEASE:
			w = previousPoint->x - x;
			h = previousPoint->y - y;
			xx = min(x, previousPoint->x);
			yy = min(y, previousPoint->y);
			GetGrafport()->DrawEditDashedRectangle(
					xx, yy, abs(w), abs(h));
			area.x = min(x, previousPoint->x);
			area.y = min(y, previousPoint->y);
			area.width  = abs(w);
			area.height = abs(h);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}

bool SelectAreaCmd::InArea(Shape *s) {
	int x = s->GetLeftMost();
	int y = s->GetTopMost();
	int w = s->GetRightMost() - x;
	int h = s->GetBottomMost() - y;
	Rectangle a(int(0.5 + Scale(x)), int(0.5 + Scale(y)),
		int(0.5 + Scale(w)), int(0.5 + Scale(h)));
	return area.Intersects(&a);
}

void SelectAreaCmd::Execute() {
	// destroy old selection
	view->DeselectAll();
	List<GShape *> *shapes = view->GetShapes();
	for ( int i = 0 ; i < (int) shapes->count() ; i++ ) {
		GShape *s = (*shapes)[i];
		if (s->IsVisible() && InArea(s))
			view->SelectShape(s);
	}
	SetCmdDone(True);
	SayCommited();
}

void SelectAreaCmd::UnExecute() {
	view->DeselectAll();
	for (oldSelection->first(); !oldSelection->done(); 
			oldSelection->next()) {
		GShape *s = oldSelection->cur();
		view->SelectShape(s);
	}
	SetCmdDone(False);
	SayUndone();
}
