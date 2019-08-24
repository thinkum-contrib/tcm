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
#include "fewindow.h"
#include "feviewer.h"
#include "fetable.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "cell.h"
#include "messagedialog.h"

FETable::FETable(Config *c, FEWindow *t, FEViewer *v): Matrix(c, t, v) { }

bool FETable::CheckTextString(Cell *c, const string *text) {
	if (!Matrix::CheckTextString(c, text))
		return False;
	// Check for crud entries.
	if (c->GetRow()->GetNumber() >=1 && c->GetColumn()->GetNumber() >= 1) {
		if (IsCRUD(text))
			return True;
		ShowDialog(MessageDialog::ERROR, "Error", 
				"A `CRUD' string is expected here");
		return False;
	}
	return True;
}

bool FETable::IsCRUD(const string *text) {
	bool C=False, D=False, U=False, R=False;
	for (unsigned i=0;i<text->length();i++) {
		switch((*text)[i]) {
		case 'C': if (C) return False; C=True; break;
		case 'D': if (D) return False; D=True; break;
		case 'U': if (U) return False; U=True; break;
		case 'R': if (R) return False; R=True; break;
		default: return False;
		}
	}
	return True;
}

unsigned FETable::CountCEntries(unsigned n) {
	unsigned total = 0;
	CellRow *row = GetTableViewer()->GiveRow(n);
	Cell *cell;
	if (row && (cell=row->FirstCell())) {
		while ((cell=row->NextCell())) {
			const string *s = cell->GetText();
			for (unsigned i=0; i<s->length(); i++) {
				if ((*s)[i] == 'C')
					total++;
			}
		}
	}
	return total;
}

void FETable::CheckDocument() {
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
	// Check missing function names.
	n = CheckEmptyColumnEntries(0);
	if (n > 0) {
		chkbuf += "* Error: ";
		chkbuf += n;
		chkbuf += " function";
		if (n!=1)
			chkbuf += "s";
		chkbuf += " in row 0 ";
		(n == 1) ? (chkbuf += "is"): (chkbuf += "are");
		chkbuf += " still empty\n";
		total += n;
	}
	// Check for functions without entries (warning).
	unsigned i;
	for (i=1; i<GetTableViewer()->GetNumberOfColumns(); i++) {
		CellColumn *column = GetTableViewer()->GiveColumn(i);
		if (column && *column->FirstCell()->GetText() != "") {
			unsigned j = CheckEmptyRowEntries(i);
			if (j == GetTableViewer()->GetNumberOfRows()-1) {
				chkbuf += "* Warning: the function in column ";
				chkbuf += i;
				chkbuf += " does not do anything\n";
				GetTableViewer()->SelectCell(column->FirstCell());
				total += 1;
			}
		}
	}
	// Check for entity types without a C.
	for (i=1; i<GetTableViewer()->GetNumberOfRows(); i++) {
		CellRow *row = GetTableViewer()->GiveRow(i);
		if (row && *row->FirstCell()->GetText() != "") {
			unsigned j = CountCEntries(i);
			if (j == 0) {
				chkbuf += "* Warning: the entity type in row ";
				chkbuf += i;
				chkbuf += " does not have a creation\n";
				GetTableViewer()->SelectCell(row->FirstCell());
				total += 1;
			}
		}
	}
	// Check for entries that are no CRUD strings.
	for (i=1; i<GetTableViewer()->GetNumberOfRows(); i++) {
		CellRow *row = GetTableViewer()->GiveRow(i);
		for (unsigned j=1; 
				j<GetTableViewer()->GetNumberOfColumns(); j++) {
			if (check(row)) {
				Cell *cell = row->NthCell(j);
				if (check(cell)) {
					const string *s = cell->GetText();
					if (!IsCRUD(s)) {
						chkbuf += "* Error: cell ";
						chkbuf += i;
						chkbuf += ",";
						chkbuf += j;
						chkbuf += " does not contain";
						chkbuf += " a CRUD string\n";
						GetTableViewer()->SelectCell(cell);
						total += 1;
					}
				}
			}
			
		}
	}
	ReportCheck(total, &chkbuf);
}
