////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "tableviewer.h"
#include "table.h"
#include "cell.h"
#include "findnextcellcmd.h"
 
FindNextCellCmd::FindNextCellCmd(Table *t, TableViewer *v, const string *s,
	bool sens, bool substr): FindAllCellsCmd(t, v, s, sens, substr) {
}

void FindNextCellCmd::Execute() {
	GetTableViewer()->DeselectAll();
	SetCmdDone(True);
	Cell *cell = GetNextCell();
	if (cell) {
		GetTableViewer()->SelectCell(cell);
		GetMainWindow()->SetStatus(
			"find next: pattern found (cell is selected)");
		Point pt = *cell->GetPosition();
		double x = Scale(pt.x);
		double y = Scale(pt.y);
		GetMainWindow()->ShowPosition(static_cast<int>(0.5 + x),
									  static_cast<int>(0.5 + y));
	}
	else
		GetMainWindow()->SetStatus("find next: pattern not found");
}
