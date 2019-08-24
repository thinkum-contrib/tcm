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
#include "findallcellscmd.h"

FindAllCellsCmd::FindAllCellsCmd(Table *t, TableViewer *v, const string *s, 
	bool c1, bool c2): SelectAllCellsCmd(t, v) {
	findString = *s;
	caseSensitive = c1;
	substring = c2;
}

void FindAllCellsCmd::Execute() {
	GetTableViewer()->DeselectAll();
	List<Cell *> cells;
	GetTableViewer()->GetCells(&cells, &findString, 
				   caseSensitive, substring);
	SetCmdDone(True);
	for (cells.first(); !cells.done(); cells.next())
		GetTableViewer()->SelectCell(cells.cur());
	int count = cells.count();
	string txt = "find all: ";
	if (count > 0) {
		txt += "found ";
		txt += count;
		txt += " cell";
		txt += ((count==1)?"":"s");
	}
	else
		txt += "Pattern not found";
	GetMainWindow()->SetStatus(&txt);
}

Cell *FindAllCellsCmd::GetNextCell() {
	return GetTableViewer()->GetNextCell(
		&findString, caseSensitive, substring);
}
