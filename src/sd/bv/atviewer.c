////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "atviewer.h"
#include "atwindow.h"
#include "atupdatenodeshapetypecmd.h"

ATViewer::ATViewer(Config *c, ATWindow *w): DiagramViewer(c, w) {
	SetShowIndexes(False);
}

void ATViewer::UpdateNodeShapeType(int toType) {
	SetStatus("action: Update node shape type");
	List<int *> types;
        types.add(new int(Code::SOLID_HORIZONTAL_BAR));
        types.add(new int(Code::SOLID_VERTICAL_BAR));
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new ATUpdateNodeShapeTypeCmd(
			GetCurView(), &types, toType));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
	types.clear();
}
