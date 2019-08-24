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
#include "diagramviewer.h"
#include "diagram.h"
#include "updatelinestylecmd.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> void List<LineStyle::Type>::clear() { empty(); }
#else
void List<LineStyle::Type>::clear() { empty(); }
#endif
#endif

UpdateLineStyleCmd::UpdateLineStyleCmd(ShapeView *v, LineStyle::Type s): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	style = s;
	shapes = new List<GShape *>;
	oldStyles = new List<LineStyle::Type>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		LineStyle::Type sls = shape->GetLineStyle();
		if (sls != style) {
			shapes->add(shape);
			oldStyles->add(sls);
		}
	}
}

UpdateLineStyleCmd::~UpdateLineStyleCmd() {
	delete shapes;
	delete oldStyles;
}

void UpdateLineStyleCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be updated");
		Abort();
		return;
	}
	for (shapes->first(); !shapes->done(); shapes->next()) 
		shapes->cur()->UpdateLineStyle(style);
	Command::Execute();
}

void UpdateLineStyleCmd::UnExecute() {
	for (unsigned i=0; i<shapes->count(); i++)
		(*shapes)[i]->UpdateLineStyle((*oldStyles)[i]);
	Command::UnExecute();
}
