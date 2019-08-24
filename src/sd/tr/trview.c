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
#include "trview.h"
#include "trviewer.h"
#include "line.h"

TRView::TRView(TRViewer *t): ShapeView(t) { }

void TRView::AddShape(GShape *shape) {
	if (!check(shape))
		return;
	shape->SetView(this);
	GetShapes()->add(shape);
	if (shape->IsSelected()) {
		GetSelection()->add(shape);
		if (GetSelection()->count() == 1)
			shape->SetFirstSelect(True);
		else
			shape->SetSelect(True);
	}
	if (shape->IsLine()) {
		Line *line = (Line *)shape;
		MultipleLines(line);
		if (line->NrPoints() == 2)
			MultipleLinesPosUpdate(line);
	}
	if (shape->IsVisible()) {
		if (((TRViewer *)GetViewer())->IsTreeMode()) {
			// draw only name in tree mode.
			if (!shape->IsTextShape())
				((GShape *)shape)->DrawTextShapes();
			else
				shape->Draw();
		}
		else
			shape->Draw();
	}
}
 
void TRView::RemoveShape(GShape *shape) {
	ShapeView::RemoveShape(shape);
}
