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
#include "cutshapescmd.h"

CutShapesCmd::CutShapesCmd(ShapeView *v): CopyShapesCmd(v) {
	// add the lines connected to the shapes.
	List<GShape *> *sel = v->GetSelection();
	v->CompleteShapes(sel);
	// subjects to cut (remove from graph).
	cutSubjects = new List<Subject *>;
	// subjects only to update (delete dupl. mark). 
	updateSubjects = new List<Subject *>;
	// shapes to remove.
	cutShapes = new List<GShape *>;
	List<GShape *> tmpShapes;
	List<GShape *> selCopy(*sel);
	for (sel->first(); !sel->done(); sel->next()) {
		GShape *shape = sel->cur();
		Subject *subject = shape->GetSubject();
		check(subject);
		cutShapes->add(shape);
		if (shape->IsDuplicate()) {
			// look whether all duplicates are selected.
			// if so, subject should be cut too.
			v->GetViewer()->GetShapes(subject, &tmpShapes);
			if (check(tmpShapes.count() >= 2)) {
				bool rmSubject = True;
				for (tmpShapes.first(); !tmpShapes.done(); 
						tmpShapes.next()) {
					GShape *s = tmpShapes.cur();
					if (selCopy.find(s) == -1)
						rmSubject = False;
				}
				if (rmSubject) {
					if (cutSubjects->find(subject) == -1)
						cutSubjects->add(subject);
				}
				else {
					if (updateSubjects->find(subject) == -1)
						updateSubjects->add(subject);
				}
			}
		}
		else if (cutSubjects->find(subject) == -1)
			cutSubjects->add(subject);
	}
}

void CutShapesCmd::Execute() {
	GetView()->RemoveShapes(cutShapes);
	GetDiagram()->RemoveSubjects(cutSubjects);
	GetView()->GetViewer()->UpdateDuplicationMarks(updateSubjects);
	GetDiagram()->IncChanges();
	CopyShapesCmd::Execute();
}

void CutShapesCmd::UnExecute() {
	GetView()->AddShapes(cutShapes);
	GetDiagram()->AddSubjects(cutSubjects);
	GetView()->GetViewer()->UpdateDuplicationMarks(updateSubjects);
	GetDiagram()->DecChanges();
	CopyShapesCmd::UnExecute();
}

CutShapesCmd::~CutShapesCmd(){
	if (CmdDone()) {
		cutSubjects->clear();
		cutShapes->clear();
		updateSubjects->empty();
	}
	delete cutSubjects;
	delete cutShapes;
	delete updateSubjects;
}
