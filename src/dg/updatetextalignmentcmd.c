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
#include "updatetextalignmentcmd.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> void List<TextAlign::Type>::clear() { empty(); }
#else
void List<TextAlign::Type>::clear() { empty(); }
#endif
#endif

UpdateTextAlignmentCmd::UpdateTextAlignmentCmd(
		ShapeView *v, TextAlign::Type a): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	alignment = a;
	shapes = new List<GShape *>;
	oldAlignments = new List<TextAlign::Type>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		TextAlign::Type sal = shape->GetAlignment();
		if (sal != alignment) {
			shapes->add(shape);
			oldAlignments->add(sal);
		}
	}
}

UpdateTextAlignmentCmd::~UpdateTextAlignmentCmd() {
	delete shapes;
	delete oldAlignments;
}

void UpdateTextAlignmentCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be realigned");
		Abort();
		return;
	}
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		shape->UpdateAlignment(alignment);
	}
	Command::Execute();
}

void UpdateTextAlignmentCmd::UnExecute() {
	for (unsigned i=0; i<shapes->count(); i++) {
		GShape *shape = (*shapes)[i];
		shape->UpdateAlignment((*oldAlignments)[i]);
	}
	Command::UnExecute();
}
