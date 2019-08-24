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
#include "shapeview.h"
#include "diagram.h"
#include "subject.h"
#include "diagramviewer.h"
#include "deleteallsubjectscmd.h"

DeleteAllSubjectsCmd::DeleteAllSubjectsCmd(ShapeView *v): DeleteSubjectsCmd(v){
	// get all shapes in the current view.
	List<GShape *> *dshapes = GetShapes();
	List<Subject *> *dsubjects = GetSubjects();
	*dshapes = *GetView()->GetShapes();
	// get all subjects of these shapes.
	for (dshapes->first(); !dshapes->done(); dshapes->next()) {
		Subject *subject = dshapes->cur()->GetSubject();
		if (check(subject) && dsubjects->find(subject) == -1)
			dsubjects->add(subject);
	}
}
