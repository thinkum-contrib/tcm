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
#include "matrix.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "cell.h"
#include "messagedialog.h"
#include <stdio.h>

Matrix::Matrix(Config *c, TableWindow *t, TableViewer *v): Table(c, t, v) { }

bool Matrix::UpdateText(Cell *c, const string *t) {
	if (CheckTextString(c, t)) {
		c->UpdateText(t);
		return True;
	}
	return False;
}

bool Matrix::CheckTextString(Cell *c, const string *t) {
	// text string should contain at least some letters.
	if (*t != "" && t->letters()==0) {
		string txt = *t + ": not a legal text string\n";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	// the entries in row and column 0 should be unique.
	CellRow *row = c->GetRow();
	CellColumn *column = c->GetColumn();
	if (*t != "" && !c->HasText(t)) {
		if (row->GetNumber()==0 && row->HasText(t)) {
			string txt = *t + ": already exists in row 0\n";
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			return False;
		}
		else if (column->GetNumber()==0 && column->HasText(t)) {
			string txt = *t + ": already exists in column 0\n";
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			return False;
		}
	}
	return True;
}

unsigned Matrix::CheckEmptyColumnEntries(unsigned n) {
	// count empty column entries at row n.
	string empty("");
	CellRow *row = GetTableViewer()->GiveRow(n);
	unsigned total = row->HasEmptyText();
	// the first entry does not count.
	if (row->FirstCell()->HasText(&empty))
		return total-1;
	else
		return total;
}

unsigned Matrix::CheckEmptyRowEntries(unsigned n) {
	// Check empty row entries at column n.
	string empty("");
	CellColumn *column = GetTableViewer()->GiveColumn(n);
	unsigned total = column->HasEmptyText();
	// the first entry does not count.
	if (column->FirstCell()->HasText(&empty))
		return total-1;
	else
		return total;
}

void Matrix::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	unsigned n = CheckEmptyColumnEntries(0);
	if (n > 0) {
		chkbuf += "* Error: ";
		chkbuf += n;
		chkbuf += " column entries in row 0 are empty\n";
		total += n;
	}
	unsigned m = CheckEmptyRowEntries(0);
	if (m > 0) {
		chkbuf += "* Error: ";
		chkbuf += m;
		chkbuf += " row entries in column 0 are empty\n";
		total += n;
	}
	ReportCheck(total, &chkbuf);
}
