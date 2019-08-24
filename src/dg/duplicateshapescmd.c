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
#include "subject.h"
#include "gshape.h"
#include "shapeview.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "drawwindow.h"
#include "mousecursor.h"
#include "duplicateshapescmd.h"

DuplicateShapesCmd::DuplicateShapesCmd(ShapeView *v): PasteShapesCmd(v, False) {
	SetShapes(new List<GShape *>);
	SetSubjects(new List<Subject *>);
	// fill shapes from selection (only node shapes).
	List<GShape *> *selection = v->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if ( shape->IsNodeShape() ) {
			// we do not use paste buffer but we make here a copy.
			GShape *sh = (GShape *)shape->Clone();
			Subject *subj = shape->GetSubject();
			if (check(subj)) {
				sh->SetSubject(subj);
				GetShapes()->add(sh);
				GetSubjects()->add(subj);
			}
		}
	}
	if (GetShapes()->count() == 0) {
		(new MessageDialog(GetMainWindow()->GetWidget(),
			MessageDialog::ERROR))->Show("Error",
			"You should select one or more nodes to duplicate");
		GetMainWindow()->SetStatus("aborted: no nodes are selected");
		return;
	}
	MakeBox();
}

DuplicateShapesCmd::~DuplicateShapesCmd() {
	if (!CmdDone()) {
		// delete copied shapes
		GetShapes()->clear();
		GetSubjects()->empty();
	}
}

void DuplicateShapesCmd::Execute() {
	GetView()->AddShapes(GetShapes());
	GetView()->GetViewer()->UpdateDuplicationMarks(GetSubjects());
	Command::Execute();
	GetMainWindow()->FitDocument();
}

void DuplicateShapesCmd::UnExecute() {
	GetView()->RemoveShapes(GetShapes());
	GetView()->GetViewer()->UpdateDuplicationMarks(GetSubjects());
	Command::UnExecute();
}

void DuplicateShapesCmd::Abort() {
	DrawOutLine(GetDelta());
	GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
	GetViewer()->SetPasting(False);
	SayAborted();
	Command::Abort();
}
