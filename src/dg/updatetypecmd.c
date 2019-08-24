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
#include "updatetypecmd.h"
#include "shapeview.h"
#include "diagram.h"

UpdateTypeCmd::UpdateTypeCmd(ShapeView *v, List<int *> *l, int n): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	toType = n;
	fromTypes = *l;
	diagram = v->GetViewer()->GetDiagram();
	oldThings = new List<Thing *>;
	newThings = new List<Thing *>;
}

UpdateTypeCmd::~UpdateTypeCmd() {
	if (CmdDone())
	 	oldThings->clear();
	else
		newThings->clear();
	delete newThings;
	delete oldThings;
}

void UpdateTypeCmd::TransformAll() {
	for (oldThings->first(); !oldThings->done(); oldThings->next()) {
                Thing *oldThing = oldThings->cur();
                Thing *newThing = Transform(oldThing);
                if (newThing)
                        newThings->add(newThing);
        }
}

void UpdateTypeCmd::Execute() {
	if (oldThings->count() == 0) {
		GetMainWindow()->SetStatus(
			"aborted: nothing has to be changed");
		Abort();
		return;
	}
	if (oldThings->count() != newThings->count()) {
		Abort();
		return;
	}
	for (unsigned i=0; i<oldThings->count(); i++) {
		Thing *oldThing = (*oldThings)[i];
		Thing *newThing = (*newThings)[i];
		Reverse(oldThing, newThing);
	}
	Command::Execute();
}

void UpdateTypeCmd::UnExecute() {
	for (unsigned i=0; i<oldThings->count(); i++) {
		Thing *oldThing = (*oldThings)[i];
		Thing *newThing = (*newThings)[i];
		Reverse(newThing, oldThing);
	}
	Command::UnExecute();
}
