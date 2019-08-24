////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "cellrow.h"
#include "cellcolumn.h"
#include "updatelinetablecmd.h"

UpdateLineTableCmd::UpdateLineTableCmd(Table *t, TableViewer *v, 
		Side::Type d): Command(t, v) {
	int side = d;
	lines = new List<LinePiece *>;
	List<Cell *> *selection = v->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		Cell *cell = selection->cur();
		LinePiece *line;
		CellRow *row = cell->GetRow();
		CellColumn *column = cell->GetColumn();
		unsigned columnNr = column->GetNumber();
		unsigned rowNr = row->GetNumber();
		if (side == Side::TOP || side ==  Side::ALL) { 
			line = column->NthLine(rowNr); 
			AddLine(line);
		}
		if (side == Side::BOTTOM || side ==  Side::ALL) { 
			line = column->NthLine(rowNr + 1);
			AddLine(line);
		}
		if (side == Side::LEFT || side ==  Side::ALL) { 
			line = row->NthLine(columnNr);
			AddLine(line);
		}
		if (side == Side::RIGHT || side ==  Side::ALL) { 
			line = row->NthLine(columnNr + 1);
			AddLine(line);
		}
		if (side == Side::SURROUNDING) {
			Cell *topCell = column->NthCell(rowNr - 1);
			Cell *bottomCell = column->NthCell(rowNr + 1);
			Cell *leftCell = row->NthCell(columnNr - 1);
			Cell *rightCell = row->NthCell(columnNr + 1);
			if (!topCell || !topCell->IsSelected()) {
				line = column->NthLine(rowNr);
				AddLine(line);
			}
			if (!bottomCell || !bottomCell->IsSelected()) {
				line = column->NthLine(rowNr + 1);
				AddLine(line);
			}
			if (!leftCell || !leftCell->IsSelected()) {
				line = row->NthLine(columnNr);
				AddLine(line);
			}
			if (!rightCell || !rightCell->IsSelected()) {
				line = row->NthLine(columnNr +1);
				AddLine(line);
			}
		}
	}
}

UpdateLineTableCmd::~UpdateLineTableCmd() {
	delete lines;
}

 
void UpdateLineTableCmd::AddLine(LinePiece *line) {
	if (line && lines->find(line) == -1)
		lines->add(line);
}
