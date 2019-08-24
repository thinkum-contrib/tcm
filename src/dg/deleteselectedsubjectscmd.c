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
#include "shapeview.h"
#include "diagram.h"
#include "subject.h"
#include "gshape.h"
#include "diagramviewer.h"
#include "deleteselectedsubjectscmd.h"

DeleteSelectedSubjectsCmd::DeleteSelectedSubjectsCmd(ShapeView *v): 
					DeleteSubjectsCmd(v) {
	// get all subjects of selected shapes.
	List<GShape *> *s = v->GetSelection();
	List<Subject *> *dsubjects = GetSubjects();
	for (s->first(); !s->done(); s->next()) {
		Subject *subject = s->cur()->GetSubject();
		if (check(subject) && dsubjects->find(subject) == -1)
			dsubjects->add(subject);
	}
	// add all connected edges.
	GetDiagram()->CompleteSubjects(dsubjects);
	// get all shapes that have to be deleted.
	for (dsubjects->first(); !dsubjects->done(); dsubjects->next())
		v->GetShapes(dsubjects->cur(), GetShapes());
}
