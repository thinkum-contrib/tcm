////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "updatereaddirectioncmd.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> void List<ReadDirection::Type>::clear() { empty(); }
#else
void List<ReadDirection::Type>::clear() { empty(); }
#endif
#endif

UpdateReadDirectionCmd::UpdateReadDirectionCmd(ShapeView *v, 
		ReadDirection::Type dir): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	direction = dir;
	lines = new List<Line *>;
	oldDirections = new List<ReadDirection::Type>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (shape->GetClassType()==Code::C2R2_LINE || 
	            shape->GetClassType()==Code::SSD_R2LINE ||
	            shape->GetClassType()==Code::C2R2_MLIST_LINE) {
			lines->add((Line*)shape);
			oldDirections->add(((Line*)shape)->GetNameDirection());
		}
	}
}

UpdateReadDirectionCmd::~UpdateReadDirectionCmd() {
	delete lines;
	delete oldDirections;
}

void UpdateReadDirectionCmd::Execute() {
	if (!lines->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be updated");
		Abort();
		return;
	}
	for (lines->first(); !lines->done(); lines->next()) {
		Line *line = lines->cur();
		line->UpdateNameDirection(direction);
	}
	Command::Execute();
}

void UpdateReadDirectionCmd::UnExecute() {
	for (unsigned i=0; i<lines->count(); i++) {
                ReadDirection::Type od = (*oldDirections)[i];
                Line *line = (*lines)[i];
		line->UpdateNameDirection(od);
	}
	Command::UnExecute();
}
