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
#include "addrowscmd.h"
#include "tableviewer.h"
#include "table.h"
#include "cellrow.h"
#include "cell.h"
 
AddRowsCmd::AddRowsCmd(Table *t, TableViewer *v, int n, int p): Command(t, v) {
	// add n rows to end of table.
	rows = new List<CellRow *>;	   // rows to be added.
	numberOfRows = n;		   // nr. of rows to be added.
	tviewer = v;
	rowPosition = p;		   // position in table where rows.
					   // have to be added.
	int tcolumns = tviewer->GetNumberOfColumns(); // current nr. of columns.
	int trows = tviewer->GetNumberOfRows(); // current nr. of rows.
	int height = tviewer->GetDefaultRowHeight(); // height of new rows.
	if (rowPosition >= trows) 		    // add to end of table.
		rowPosition = trows;
	int x, y;   		// coordinates of each new cell.
	if (trows == 0) {	// empty table
		y = tviewer->GetTopLeft()->y + height/2;
		tcolumns = tviewer->GetDefaultNumberOfColumns();
	}
	else if (rowPosition < trows) { // insert in table: look at row 
					//  at this position.
		Point pt = tviewer->GetRowTopLeft(rowPosition);
		y = pt.y + height/2;
	}
	else {				// add down to table: look at row above.
		Point pt = tviewer->GetRowTopLeft(rowPosition-1);
		y = pt.y + tviewer->GetRowHeight(rowPosition-1) + height/2;
	}
	for (int i = 0; i < numberOfRows; i++) { 
		// create a new row
		int rownr = rowPosition + i;
		CellRow *row = new CellRow(tviewer, rownr, height);
		rows->add(row);
		row->SetLabelsVisible(tviewer->IsShowRowColumnLabels());
		for (int j = 0; j < tcolumns; j++) {  
			// fill each row with new cells
			int width = tviewer->GetColumnWidth(j);
			Point pt = tviewer->GetColumnTopLeft(j);
			x = pt.x + width/2;
			Cell *c = new Cell(GetGrafport(), 
					tviewer->GetDefaultFont(),
					row, tviewer->GiveColumn(j), 
					   x, y, width, height);
#ifdef DEBUG
			string s = rownr;
			s += ","; s += j;
			c->UpdateText(&s);
#endif
			row->AddCell(c);
		}
		y += height;
	}
}

AddRowsCmd::~AddRowsCmd() {
	if (!CmdDone())
		rows->clear();
	delete rows;
}

void AddRowsCmd::Execute() {
	// add rows to viewer.
	for (rows->first(); !rows->done(); rows->next())
		tviewer->InsertRow(rows->cur());
	if (rows->count() > 0) {
		GetMainWindow()->FitDocument();
		Command::Execute();
	}
	else {
		GetMainWindow()->SetStatus("aborted: no rows need to be added");
		Abort();
	}
}

void AddRowsCmd::UnExecute() {
	// delete rows in reversed order
	for (rows->last(); !rows->done(); rows->prev())
		tviewer->DeleteRow(rows->cur());
	if (check(rows->count() > 0))
		Command::UnExecute();
	else
		GetMainWindow()->SetStatus(
			"aborted: no rows need to be removed");
}

void AddRowsCmd::ReExecute() {
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->Draw();
	Execute();
}
