////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "diagramviewer.h"
#include "diagram.h"
#include "updatefontcmd.h"

UpdateFontCmd::UpdateFontCmd(ShapeView *v, int f, int s, int p): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	family = f;
	style = s;
	size = p;
	shapes = new List<GShape *>;
	oldSizes = new List<Point *>;
	oldFonts = new List<XFont *>;
	GetUpdateShapes();
}

UpdateFontCmd::~UpdateFontCmd() {
	oldSizes->clear();
	delete shapes;
	delete oldSizes;
	delete oldFonts;
}

void UpdateFontCmd::GetUpdateShapes() {
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		XFont *ft = shape->GetFont();
		// negative family/style/size means no update necessary.
		if (family >= 0 && family != ft->GetFamily())
			SaveShape(shape);
		else if (style >= 0 && style != ft->GetStyle())
			SaveShape(shape);
		else if (size >= 0 && style != ft->GetSize())
			SaveShape(shape);
	}
}

void UpdateFontCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no fonts need to be changed");
		Abort();
		return;
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		XFont *newFt = GetNewFont(shape);
		shape->UpdateFont(newFt);
		if (GetViewer()->IsAutoResize())
			shape->AdjustSize();
	}
	Command::Execute();
}

void UpdateFontCmd::UnExecute() {
	for (unsigned i=0; i<shapes->count(); i++) {
		GShape *shape = (*shapes)[i];
		shape->UpdateFont((*oldFonts)[i]);
		if (GetViewer()->IsAutoResize()) {
			int oldWidth = (*oldSizes)[i]->x;
			int oldHeight = (*oldSizes)[i]->y;
			if (shape->GetWidth() != oldWidth ||
			    shape->GetHeight() != oldHeight) {
				shape->UpdateSize(oldWidth, oldHeight);
				view->GetViewer()-> ShapePositionUpdate(shape);
			}
		}
	}
	Command::UnExecute();
}

void UpdateFontCmd::SaveShape(GShape *shape) {
	shapes->add(shape);
	oldFonts->add(shape->GetFont());
	Point *pt = new Point(shape->GetWidth(), shape->GetHeight());
	oldSizes->add(pt);
}

XFont *UpdateFontCmd::GetNewFont(GShape *shape) {
	XFont *ft = shape->GetFont();
	int f = (family < 0) ?  ft->GetFamily() : family;
	int s = (style < 0) ?  ft->GetStyle() : style;
	int p = (size < 0) ?  ft->GetSize() : size;
	return GetViewer()->GetFont(f, s, p);
}
