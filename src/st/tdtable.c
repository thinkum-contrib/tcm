////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam
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
#include "tdwindow.h"
#include "tdviewer.h"
#include "tdtable.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "cell.h"

TDTable::TDTable(Config *c, TDWindow *t, TDViewer *v): Matrix(c, t, v) { }

bool TDTable::CheckTextString(Cell *c, const string *text) {
	return (Matrix::CheckTextString(c, text));
}

void TDTable::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	// Check missing entity type names.
	unsigned n = CheckEmptyRowEntries(0);
	if (n > 0) {
		chkbuf += "* Error: ";
		chkbuf += n;
		chkbuf += " entity type";
		if (n!=1)
			chkbuf += "s"; 
		chkbuf += " in column 0 ";
		(n == 1) ? (chkbuf += "is"): (chkbuf += "are");
		chkbuf += " still empty\n";
		total += n;
	}
	// Check missing transaction names.
	n = CheckEmptyColumnEntries(0);
	if (n > 0) {
		chkbuf += "* Error: ";
		chkbuf += n;
		chkbuf += " transaction";
		if (n!=1)
			chkbuf += "s"; 
		chkbuf += " in row 0 ";
		(n == 1) ? (chkbuf += "is"): (chkbuf += "are");
		chkbuf += " still empty\n";
		total += n;
	}
	// Check for transactions without entries (warning).
	unsigned i;
	for (i=1; i<GetTableViewer()->GetNumberOfColumns(); i++) {
		CellColumn *column = GetTableViewer()->GiveColumn(i);
		if (column && *column->FirstCell()->GetText() != "") {
			unsigned j = CheckEmptyRowEntries(i);
			if (j == GetTableViewer()->GetNumberOfRows()-1) {
				chkbuf+="* Warning: the transaction in column ";
				chkbuf += i;
				chkbuf += " does not do anything\n";
				GetTableViewer()->SelectCell(column->FirstCell());
				total += 1;
			}
		}
	}
	// Check for entity types without entries(warning).
	for (i=1; i<GetTableViewer()->GetNumberOfRows(); i++) {
		CellRow *row = GetTableViewer()->GiveRow(i);
		if (row && *row->FirstCell()->GetText() != "") {
			unsigned j = CheckEmptyColumnEntries(i);
			if (j == GetTableViewer()->GetNumberOfColumns()-1) {
				chkbuf += "* Warning: the entity type in row ";
				chkbuf += i;
				chkbuf += " does not take part in anything\n";
				GetTableViewer()->SelectCell(row->FirstCell());
				total += 1;
			}
		}
	}
	ReportCheck(total, &chkbuf);
}
