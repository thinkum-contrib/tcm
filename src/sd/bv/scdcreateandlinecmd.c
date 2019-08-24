////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente, Enschede.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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

#include "scdcreateandlinecmd.h"
#include "grafport.h"
#include "shapeview.h"
#include "nodeshape.h"

SCDCreateAndLineCmd::SCDCreateAndLineCmd(GShape *from)
	: CreateEdgeCmd(from) {
}


/* virtual */ SCDCreateAndLineCmd::~SCDCreateAndLineCmd() {
}


void SCDCreateAndLineCmd::TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint) {
	int x,y;
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black");
	switch(aPhase) {
	    case TRACK_PRESS:
		GetMainWindow()->SetCursor(MouseCursor::PLUS);
		GetGrafport()->DrawEditLine(anchorPoint->x,
			anchorPoint->y, nextPoint->x, nextPoint->y);
		AddPoint(anchorPoint);
		break;
	    case TRACK_DRAG:
		GetGrafport()->DrawEditLine(
			anchorPoint->x, anchorPoint->y,
			previousPoint->x, previousPoint->y);
		GetGrafport()->DrawEditLine(anchorPoint->x,
			anchorPoint->y, nextPoint->x, nextPoint->y);
		abortPoint = *nextPoint;
		break;
	    case TRACK_UP:
		// erase old line
		GetGrafport()->DrawEditLine(
			anchorPoint->x, anchorPoint->y,
			previousPoint->x, previousPoint->y);
		// draw temporary
		GetGrafport()->DrawEditLine(anchorPoint->x,
			anchorPoint->y, nextPoint->x, nextPoint->y);
		AddPoint(nextPoint);
		// where was the mouse released
		x = int(0.5 + ScaleCorrect(nextPoint->x));
		y = int(0.5 + ScaleCorrect(nextPoint->y));
		if (connectEdges)
			toShape = view->HitShape(x, y);
		else
			toShape = view->HitNodeShape(x, y);
		if (toShape) 
			TrackMouse(TRACK_RELEASE, anchorPoint,
				previousPoint, nextPoint);
		break;
	    case TRACK_RELEASE:
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
		EraseLines();
		GetViewer()->SetZigZag(False);

		points->insert(new Point(*(points->elem(0))), 0);
		points->add(new Point(*(points->elem(points->count() - 1))));

		GetViewer()->ExecuteCommand();
		break;
	    default:
		error("unknown track type\n");
		break;
	}
}
