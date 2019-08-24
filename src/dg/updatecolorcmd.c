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
#include "nodeshape.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "updatecolorcmd.h"

UpdateColorCmd::UpdateColorCmd(ShapeView *v, const string *c, 
		UpdateColorCmd::Type t): 
			Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	color = *c;
	type = t;
	shapes = new List<GShape *>;
	oldColors = new List<string *>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (type == FILL && ! shape->IsNodeShape())
			continue;	// edges have no filling.
		const string *scolor;
		if (type == LINE)
			scolor = shape->GetColor();
		else if (type == TEXT)
			scolor = shape->GetTextColor();
		else // FILL
			scolor = ((NodeShape *)shape)->GetFillColor();
		if (*scolor != color) {
			string *nc = new string(*scolor);
			shapes->add(shape);
			oldColors->add(nc);
		}
	}
}

UpdateColorCmd::~UpdateColorCmd() {
	oldColors->clear();
	delete shapes;
	delete oldColors;
}

void UpdateColorCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be updated");
		Abort();
		return;
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if (type == LINE)
			shape->UpdateColor(&color);
		else if (type == TEXT)
			shape->UpdateTextColor(&color);
		else if (shape->IsNodeShape())
			((NodeShape *)shape)->UpdateFillColor(&color);
	}
	Command::Execute();
}

void UpdateColorCmd::UnExecute() {
	for (unsigned i=0; i<shapes->count(); i++) {
		string *s = (*oldColors)[i];
		GShape *shape = (*shapes)[i];
		if (type == LINE)
			shape->UpdateColor(s);
		else if (type == TEXT)
			shape->UpdateTextColor(s);
		else if (shape->IsNodeShape())
			((NodeShape *)shape)->UpdateFillColor(s);
	}
	Command::UnExecute();
}
