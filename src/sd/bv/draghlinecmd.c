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
#include "diagram.h"
#include "grafport.h"
#include "transitionarrow.h"
#include "stviewer.h"
#include "draghlinecmd.h"

DragHLineCmd::DragHLineCmd(TransitionArrow *s): DragShapeCmd(s) {
	Point p1 = *s->GetHLineFrom();
	Point p2 = *s->GetHLineTo();
	Point pt((p1.x+p2.x)/2, (p1.y+p2.y)/2);
	SetOldPosition(&pt);
}

void DragHLineCmd::Executable() {
	((TransitionArrow *)GetShape())->
		UpdateAnchor(GetDelta(), GetOldPosition());
}

void DragHLineCmd::UnExecute() {
	SetCmdDone(False);
	GetDocument()->DecChanges();
	// set to virtual moved position (probably off screen).
	Point virtualPt = Point (*GetOldPosition() + *GetDelta());
	Point p1 = *((TransitionArrow *)GetShape())->GetHLineFrom();
	Point p2 = *((TransitionArrow *)GetShape())->GetHLineTo();
	Point newPosition = Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);
	Point virtualDelta = newPosition - virtualPt;
	Point newDelta = *GetDelta() + virtualDelta;
	newDelta = -newDelta;
	SetDelta(&newDelta);
	Executable();
	GetMainWindow()->SetStatus("undo: move shape");
}

void DragHLineCmd::DrawOutLine(const Point *d) {
	Point p1 = *((TransitionArrow *)GetShape())->GetHLineFrom();
	Point p2 = *((TransitionArrow *)GetShape())->GetHLineTo();
	Point p3 = ScaleCorrect(d);
	p1 += p3;
	p2 += p3;
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black");
	GetGrafport()->DrawLine(p1.x, p1.y, p2.x, p2.y);
}
