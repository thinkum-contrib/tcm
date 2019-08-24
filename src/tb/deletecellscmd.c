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
#include "cellrow.h"
#include "cellcolumn.h"
#include "deletecellscmd.h"
 
DeleteCellsCmd::DeleteCellsCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	rows = new List<CellRow *>;
	columns = new List<CellColumn *>;
}

DeleteCellsCmd::~DeleteCellsCmd() {
	if (CmdDone()) {
		rows->clear();
		columns->clear();
	}
	else {
		rows->empty();
		columns->empty();
	}
	delete columns;
	delete rows;
}

void DeleteCellsCmd::Execute() {
	tviewer->DeselectAll();
	// delete rows from viewer, which also updates and redraws 
	// remaining table.
	for (rows->first(); !rows->done(); rows->next())
		tviewer->DeleteRow(rows->cur());
	// delete columns from viewer, which also updates and redraws 
	// remaining table.
	for (columns->first(); !columns->done(); columns->next())
		tviewer->DeleteColumn(columns->cur());
	if (rows->count()+columns->count() > 0)
		Command::Execute();
}

void DeleteCellsCmd::UnExecute() {
	// insert columns back in reversed order.
	columns->reverse();
	for (columns->first(); !columns->done(); columns->next()) {
		tviewer->InsertColumn(columns->cur());
		columns->cur()->Draw();
	}
	// insert rows back in reversed order.
	rows->reverse();
	for (rows->first(); !rows->done(); rows->next()) {
		tviewer->InsertRow(rows->cur());
		rows->cur()->Draw();
	}
	if (rows->count()+columns->count() > 0)
		Command::UnExecute();
}
