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
#include "subjects.h"
#include "subject.h"
#include "assoclist.h"
#include "util.h"

Subjects::Subjects(AssocList *al) {
	assocList = al;
}

Subjects::Subjects(const Subjects &subjects) {
	unsigned s = subjects.count();
	assocList = subjects.assocList;
	unsigned i;
	for (i=0; i<s; i++) {
		Subject *subject = CloneSubject(subjects[i]);
		if (subject)
			add(subject);
	}
	for (first(); !done(); next())
		cur()->SetReferences(assocList);
} 

Subject *Subjects::CloneSubject(Subject *s) {
	if (!check(s))
		return 0;
	Subject *subject = s->Clone();
	Assoc *assoc = new Assoc(s, subject, Thing::SUBJECT);
	assocList->Put(assoc);
	return subject;
}
