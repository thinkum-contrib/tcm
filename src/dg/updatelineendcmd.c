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
#include "line.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "updatelineendcmd.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> void List<LineEnd::Type>::clear() { empty(); }
#else
void List<LineEnd::Type>::clear() { empty(); }
#endif
#endif

UpdateLineEndCmd::UpdateLineEndCmd(ShapeView *v, 
		LineEnd::Type e1, LineEnd::Type e2): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	end1 = e1;
	end2 = e2;
	lines = new List<Line *>;
	oldEnds1 = new List<LineEnd::Type>;
	oldEnds2 = new List<LineEnd::Type>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (shape->IsLine()) {
			Line *line = (Line *)shape;
			lines->add(line);
			oldEnds1->add(line->GetEnd1());
			oldEnds2->add(line->GetEnd2());
		}
	}
}

UpdateLineEndCmd::~UpdateLineEndCmd() {
	delete lines;
	delete oldEnds1;
	delete oldEnds2;
}

void UpdateLineEndCmd::Execute() {
	if (!lines->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no lines need to be updated");
		Abort();
		return;
	}
	for (lines->first(); !lines->done(); lines->next()) {
		lines->cur()->UpdateEnd1(end1);
		lines->cur()->UpdateEnd2(end2);
	}
	Command::Execute();
}

void UpdateLineEndCmd::UnExecute() {
	for (unsigned i=0; i<lines->count(); i++) {
		(*lines)[i]->UpdateEnd1((*oldEnds1)[i]);
		(*lines)[i]->UpdateEnd2((*oldEnds2)[i]);
	}
	Command::UnExecute();
}
