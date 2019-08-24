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
#include "addcolumnscmd.h"
#include "tableviewer.h"
#include "table.h"
#include "cellcolumn.h"
#include "cell.h"
 
AddColumnsCmd::AddColumnsCmd(Table *t, TableViewer *v, int n, int p): 
		Command(t, v) {
	// add n columns to end of table.
	columnPosition = p;
	numberOfColumns = n;		  // nr. of columns to be added.
	columns = new List<CellColumn *>; // columns to be added.
	tviewer = v;
	int tcolumns = tviewer->GetNumberOfColumns();	// current nr of columns
	int trows = tviewer->GetNumberOfRows();		// current nr of rows
	int width = tviewer->GetDefaultColumnWidth();	// width of new columns
	if (columnPosition >= tcolumns)
		columnPosition = tcolumns;
	int x, y;	// coordinates of each new cell.
	if (tcolumns == 0) {  // empty table.
		x = tviewer->GetTopLeft()->x + width/2;
		trows = tviewer->GetDefaultNumberOfRows();
	}
	else if (columnPosition < tcolumns) { 	// insert in table: 
						// look at column left.
		Point pt = tviewer->GetColumnTopLeft(columnPosition);
		x = pt.x + width/2;
	}
	else {	// add to the left of table: look at leftmost column.
		Point pt = tviewer->GetColumnTopLeft(columnPosition-1);
		x = pt.x + tviewer->GetColumnWidth(columnPosition-1) + width/2;
	}
	for (int i = 0; i < n; i++) {
		// create a new column
		int colnr = columnPosition + i;
		CellColumn *column = new CellColumn(tviewer, colnr, width);
		columns->add(column);
		column->SetLabelsVisible(tviewer->IsShowRowColumnLabels());
		for (int j = 0; j < trows; j++) {
			// fill column with new cells.
			int height = tviewer->GetRowHeight(j);
			Point pt = tviewer->GetRowTopLeft(j);
			y = pt.y + height/2;
			Cell *c = new Cell(GetGrafport(), 
				tviewer->GetDefaultFont(),
				tviewer->GiveRow(j), column, x, y, 
				width, height);
#ifdef DEBUG
			string s = j;
			s += ","; s+= colnr;
			c->UpdateText(&s);
#endif
			column->AddCell(c);
		}
		x += width;
	}
}

AddColumnsCmd::~AddColumnsCmd() {
	if (!CmdDone())
		columns->clear();
	delete columns;
}

void AddColumnsCmd::Execute() {
	// add columns to viewer
	for (columns->first(); !columns->done(); columns->next())
		tviewer->InsertColumn(columns->cur());
	if (columns->count() > 0) {
		Command::Execute();
		GetMainWindow()->FitDocument();
	}
	else {
		GetMainWindow()->SetStatus(
			"aborted: no columns are to be added");
		Abort();
	}
}

void AddColumnsCmd::UnExecute() {
	for (columns->last(); !columns->done(); columns->prev())
		tviewer->DeleteColumn(columns->cur());
	if (check(columns->count() > 0))
		Command::UnExecute();
	else
		GetMainWindow()->SetStatus(
			"aborted: no columns are to be removed");
}

void AddColumnsCmd::ReExecute() {
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->Draw();
	Execute();
}
