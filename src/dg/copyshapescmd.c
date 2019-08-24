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
#include "shapes.h"
#include "subjects.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "buffer.h"
#include "assoclist.h"
#include "copyshapescmd.h"

CopyShapesCmd::CopyShapesCmd(ShapeView *v):
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	diagram = v->GetViewer()->GetDiagram();
	buffer = v->GetViewer()->GetBuffer();
	Copy(v->GetSelection());
	bufferShapes = 0;
	bufferSubjects = 0;
}

void CopyShapesCmd::Copy(List<GShape *> *selection) {
	// create temporary subjects and shapes lists.
	AssocList *assocList = diagram->GetAssocList();
	Subjects temp_subj(assocList);
	Shapes temp_shap(assocList);
	// fill temp_shape and temp_subjects from selection.
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		temp_shap.add(shape);
		Subject *subject = shape->GetSubject();
		if (check(subject) && temp_subj.find(subject) == -1)
			temp_subj.add(subject);
	}
	// select subjects connected by the edges in temp_subj
	diagram->CompleteEdges(&temp_subj);
	// fill temp_shapes with shapes by the lines in temp_shap
	view->CompleteLines(&temp_shap);
	// empty dictionary.
	assocList->clear();
	// create temporary list of copy subjects.
	subjects = new Subjects(temp_subj);
	// create temporary list of copy shapes.
	shapes = new Shapes(temp_shap);
	// set subjects 
	for (shapes->first(); !shapes->done(); shapes->next()) {
		Shape *shape = shapes->cur();
		if (!shape->SetAssocSubject(assocList)) {
			GetMainWindow()->SetStatus(
				"aborted: inconsistency detected");
			return;
		}
	}
}

void CopyShapesCmd::Execute() {
	SetCmdDone(True);
	if (bufferShapes)
		delete bufferShapes;
	if (bufferSubjects)
		delete bufferSubjects;
	bufferShapes = 0;
	bufferSubjects = 0;
	if (buffer->GetShapes()) {
		bufferShapes = new Shapes(shapes->GetAssocList());
                *bufferShapes = *buffer->GetShapes();
	}
	if (buffer->GetSubjects()) {
		bufferSubjects = new Subjects(subjects->GetAssocList());
                *bufferSubjects = *buffer->GetSubjects();
	}
	buffer->Put(subjects, shapes);
	buffer->SetUser(this);
	SayCommited();
}

void CopyShapesCmd::UnExecute() {
	SetCmdDone(False);
	buffer->Put(bufferSubjects, bufferShapes);
	buffer->SetUser(this);
	SayUndone();
}

CopyShapesCmd::~CopyShapesCmd() {
	if (bufferShapes)
		delete bufferShapes;
	if (bufferSubjects)
		delete bufferSubjects;
	subjects->clear();
	shapes->clear();
	delete subjects;
	delete shapes;
}
