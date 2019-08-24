////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
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
#include "updatefillcolorcmd.h"
#include "nodeshape.h"
#include "shapeview.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> void List<FillStyle::Type>::clear() { empty(); }
#else
void List<FillStyle::Type>::clear() { empty(); }
#endif
#endif

UpdateFillColorCmd::UpdateFillColorCmd(ShapeView *v, const string *c,
		FillStyle::Type f):
	UpdateColorCmd(v, c, UpdateColorCmd::FILL) {
	fillStyle = f;
	oldFillStyles = new List<FillStyle::Type>;
	List<GShape *> *s = GetShapes();
	
	List<GShape *> *selection = v->GetSelection();
        for (selection->first(); !selection->done(); selection->next()) {
                GShape *shape = selection->cur();
                if ( ! shape->IsNodeShape() || s->contains(shape)) 
                        continue;
		NodeShape *nshape = ((NodeShape *)shape);
		if (nshape->GetFillStyle() != fillStyle) {
                        string *nc = new string(*nshape->GetFillColor());
                        s->add(shape);
                        GetOldColors()->add(nc);
                }
        }

	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		FillStyle::Type nf = ((NodeShape *)shape)->GetFillStyle();
		oldFillStyles->add(nf);
	}
}

UpdateFillColorCmd::~UpdateFillColorCmd() {
	delete oldFillStyles;
}

void UpdateFillColorCmd::Execute() {
	List<GShape *> *s = GetShapes();
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		((NodeShape *)shape)->UpdateFillStyle(fillStyle);
	}
	UpdateColorCmd::Execute();
}

void UpdateFillColorCmd::UnExecute() {
	List<GShape *> *s = GetShapes();
	for (unsigned i=0; i<s->count(); i++) {
		FillStyle::Type f = (*oldFillStyles)[i];
		GShape *shape = (*s)[i];
		((NodeShape *)shape)->UpdateFillStyle(f);
	}
	UpdateColorCmd::UnExecute();
}
