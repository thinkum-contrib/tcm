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
#include "celltext.h"
#include "cellrow.h"
#include "sortrowscmd.h"

SortRowsCmd::SortRowsCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	column = tviewer->GetLeftSelectionColumn();
	if (column == -1)
		column = 0;
	int n = tviewer->GetNumberOfRows();
	for (int i=0; i<n; i++) {
		CellRow *row = tviewer->GiveRow(i);
		originals.add(row);
		Cell *cell = row->NthCell(column);
		if (check(cell))
			texts.add(cell->GetCellText());
	}
	texts.sort(Compare);
}

void SortRowsCmd::Execute() {
	int i = 0;
	if (texts.first()) {
		do {
			CellText *text = texts.cur();
			CellRow *row = text->GetParent()->GetRow();
			if (row)
				tviewer->MoveRow(row, i);
			i++;
		} while (texts.next());
		Command::Execute();
	}
}

void SortRowsCmd::UnExecute() {
	SayUndone();
	int n = tviewer->GetNumberOfRows();
	if (n > 0) {
		for (int i=0; i<n; i++)
			tviewer->MoveRow(originals[i], i);
		Command::UnExecute();
	}
}
