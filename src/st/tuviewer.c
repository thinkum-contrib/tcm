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
#include "tuviewer.h"
#include "tablewindow.h"
#include "cell.h"
#include "cellrow.h"
#include "config.h"

TUViewer::TUViewer(Config *c, TableWindow *t): MatrixViewer(c, t) { 
	SetDefaultColumnWidth(c->GetTUTcolumnWidth());
	SetDefaultNumberOfColumns(c->GetTUTnumberOfColumns());
}

void TUViewer::Initialize() {
	MatrixViewer::Initialize();
	CellRow *row = (*GetRows())[0];
	Cell *cell;
	if (row) {
		cell = row->NthCell(1);
		if (cell) {
			string s = "Create";
			cell->UpdateText(&s);
			cell->SetEditable(False);
		}
		cell = row->NthCell(2);
		if (cell) {
			string s = "Read";
			cell->UpdateText(&s);
			cell->SetEditable(False);
		}
		cell = row->NthCell(3);
		if (cell) {
			string s = "Update";
			cell->UpdateText(&s);
			cell->SetEditable(False);
		}
		cell = row->NthCell(4);
		if (cell) {
			string s = "Delete";
			cell->UpdateText(&s);
			cell->SetEditable(False);
		}
	}
	GetMainWindow()->SetStatus("");
}
