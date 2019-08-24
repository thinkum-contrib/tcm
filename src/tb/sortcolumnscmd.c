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
#include "cellcolumn.h"
#include "sortcolumnscmd.h"

SortColumnsCmd::SortColumnsCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	row = tviewer->GetTopSelectionRow();
	if (row == -1)
		row = 0;
	int n = tviewer->GetNumberOfColumns();
	for (int i=0; i<n; i++) {
		CellColumn *column = tviewer->GiveColumn(i);
		originals.add(column);
		Cell *cell = column->NthCell(row);
		if (check(cell))
			texts.add(cell->GetCellText());
	}
	texts.sort(Compare);
}

void SortColumnsCmd::Execute() {
	int i = 0;
	if (texts.first()) {
		do {
			CellText *text = texts.cur();
			CellColumn *column = text->GetParent()->GetColumn();
			if (column)
				tviewer->MoveColumn(column, i);
			i++;
		} while (texts.next());
		Command::Execute();
	}
}

void SortColumnsCmd::UnExecute() {
	int n = tviewer->GetNumberOfColumns();
	if (n > 0) {
		for (int i=0; i<n; i++)
			tviewer->MoveColumn(originals[i], i);
		Command::UnExecute();
	}
}
