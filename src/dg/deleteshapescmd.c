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
#include "gshape.h"
#include "subject.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "shapeview.h"
#include "deleteshapescmd.h"

DeleteShapesCmd::DeleteShapesCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(),v->GetViewer()) {
	shapes = new List<GShape *>(*v->GetSelection());
	deleteSubjects = new List<Subject *>;
	updateSubjects = new List<Subject *>;
	diagram = v->GetViewer()->GetDiagram();
	dviewer = v->GetViewer();
	view = v;
	// add the lines connected to the shapes.
	v->CompleteShapes(shapes);
	List<Subject *> tmpsubjects;
	List<GShape *> tmpshapes;
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Subject *subject = shapes->cur()->GetSubject();
		if (check(subject) && tmpsubjects.find(subject) == -1)
			tmpsubjects.add(subject);
	}
	for (tmpsubjects.first(); !tmpsubjects.done(); tmpsubjects.next()) {
		Subject *subject = tmpsubjects.cur();
		tmpshapes.empty();
		dviewer->GetShapes(subject, &tmpshapes);
		int n = tmpshapes.count();
		if (!check (n != 0))
			return;
		if (n == 1)
			// there is one shape for subject-> delete the subject.
			deleteSubjects->add(subject);
		else if (n >= 2) {
			// look if all those shapes are in 'shapes'.
			bool rmSubject = True;
			for (tmpshapes.first(); !tmpshapes.done(); 
					tmpshapes.next()) {
				GShape *shape = tmpshapes.cur();
				if (shapes->find(shape) == -1) {
					rmSubject = False;
					break;
				}
			}
			// all shapes of subject deleted -> delete the subject.
			if (rmSubject)
				deleteSubjects->add(subject);
			// one of the two representing shapes are deleted->
			// update duplication mark of the other.
			else if (n == 2 && !rmSubject)
				updateSubjects->add(subject);
		}
		tmpshapes.empty();
	}
}

DeleteShapesCmd::~DeleteShapesCmd() {
	if (CmdDone()) {
		shapes->clear();
		deleteSubjects->clear();
		updateSubjects->empty();
	}
	delete shapes;
	delete deleteSubjects;
	delete updateSubjects;
}

void DeleteShapesCmd::Execute() {
	view->RemoveShapes(shapes);
	diagram->RemoveSubjects(deleteSubjects);
	dviewer->UpdateDuplicationMarks(updateSubjects);
	Command::Execute();
}

void DeleteShapesCmd::UnExecute() {
	view->AddShapes(shapes);
	diagram->AddSubjects(deleteSubjects);
	dviewer->UpdateDuplicationMarks(updateSubjects);
	Command::UnExecute();
}
