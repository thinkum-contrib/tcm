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
#include "shapeview.h"
#include "util.h"
#include "assoclist.h"

Shapes::Shapes(AssocList *al) {
	assocList = al;
}

Shapes::Shapes(const Shapes &shapes) {
	unsigned s = shapes.count();
	unsigned i;
	assocList = shapes.assocList;
	for (i=0; i<s; i++) {
		GShape *shape = CloneShape(shapes[i]);
		if (shape)
			add(shape);
	}
	for (first(); !done(); next())
		cur()->SetReferences(assocList);
}

GShape *Shapes::CloneShape(GShape *s) {
	if (!check(s))
		return 0;
	GShape *shape = (GShape *)s->Clone();
	Assoc *assoc = new Assoc(s, shape, Thing::SHAPE);
	assocList->Put(assoc);
	return shape;
}
