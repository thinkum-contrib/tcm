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
#include "tuwindow.h"
#include "tuviewer.h"
#include "tutable.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "cell.h"

TUTable::TUTable(Config *c, TUWindow *t, TUViewer *v): Matrix(c, t, v) { }

bool TUTable::CheckTextString(Cell *c, const string *text) {
	return Matrix::CheckTextString(c, text);
}

void TUTable::CheckDocument() {
	chkbuf = "";
	int total = 0;
	// Check row 0: create, read, update, delete.
	if (GetTableViewer()->GetNumberOfColumns() != 5 ||
	    !(*GetTableViewer()->GiveColumn(1)->FirstCell()->GetText() 
		%= "Create") ||
	    !(*GetTableViewer()->GiveColumn(2)->FirstCell()->GetText() 
		%= "Read") ||
	    !(*GetTableViewer()->GiveColumn(3)->FirstCell()->GetText() 
		%= "Update") ||
	    !(*GetTableViewer()->GiveColumn(4)->FirstCell()->GetText() 
		%= "Delete")) {
		chkbuf += "* Error: row 0 is seriously messed up, ";
		chkbuf += "it should contain: \n";
		chkbuf += "(empty) | Create | Read | Update | Delete \n";
		total += 1;
	}
	// Check missing function names in the columns.
	int n = CheckEmptyRowEntries(0);
	if (n > 0) {
		chkbuf += "* Error: ";
		chkbuf += n;
		chkbuf += " transaction";
		if (n!=1)
			chkbuf += "s";
		chkbuf += " in column 0 ";
		(n == 1) ? (chkbuf += "is"): (chkbuf += "are");
		chkbuf += " still empty\n";
		total += n;
	}
	// Check for transactions not using any entity types.
	for (unsigned i=1; i<GetTableViewer()->GetNumberOfRows(); i++) {
		CellRow *row = GetTableViewer()->GiveRow(i);
		if (row && *row->FirstCell()->GetText() != "") {
			unsigned j = CheckEmptyColumnEntries(i);
			if (j == GetTableViewer()->GetNumberOfColumns()-1) {
				chkbuf += "* Warning: the transaction in row ";
				chkbuf += i;
				chkbuf += " does not use any entity type\n";
				GetTableViewer()->SelectCell(row->FirstCell());
				total += 1;
			}
		}
	}
	ReportCheck(total, &chkbuf);
}
