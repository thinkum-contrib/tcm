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
#include "shapes.h"
#include "gshape.h"
#include "subjects.h"
#include "subject.h"
#include "buffer.h"

Buffer::Buffer() {
	subjects = 0;
	shapes = 0;
	user = 0;
}

Buffer::~Buffer() {
	// subjects and shapes should be deleted from the command class.
	if (subjects) {
		if (!user)
			subjects->clear();
	 	delete subjects;
	}
	if (shapes) {
		if (!user)
			shapes->clear();
		delete shapes;
	}
}

void Buffer::Put(Subjects *subj, Shapes *shap) {
	if (subjects) {
		if (!user)
			subjects->clear();
	 	delete subjects;
	}
	if (shapes) {
		if (!user)
			shapes->clear();
		delete shapes;
	}
	if (subj != 0) {
		subjects = new Subjects(subj->GetAssocList());
		*subjects = *subj;
	}
	else
		subjects = 0;
	if (shap != 0) {
		shapes = new Shapes(shap->GetAssocList());
		*shapes = *shap;
	}
	else
		shapes = 0;
}

Subjects *Buffer::GetSubjectsCopy() {
	if (subjects)
		return new Subjects(*subjects);
	else 
		return 0;
}

Shapes *Buffer::GetShapesCopy() {
	if (shapes) {
		Shapes *shap = new Shapes(*shapes);
		for (shap->first(); !shap->done(); shap->next()) {
			GShape *shape = shap->cur();
			if (!shape->SetAssocSubject(shapes->GetAssocList()))
				return 0;
		}
		return shap;
	}
	else 
		return 0;
}
