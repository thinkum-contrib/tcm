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
#include "deleterowscmd.h"
 
DeleteRowsCmd::DeleteRowsCmd(Table *t, TableViewer *v): DeleteCellsCmd(t, v) {
	DetermineRows();
}

void DeleteRowsCmd::DetermineRows() {
	// find the rows that have to be deleted.
	GetTableViewer()->GetSelectedRows(GetRows());
	// rows should be deleted in increasing order.
	GetRows()->sort(Compare);
}

void DeleteRowsCmd::Execute() {
	if (GetRows()->count() > 0)
		DeleteCellsCmd::Execute();
	else {
		GetMainWindow()->SetStatus(
			"aborted: no rows need to be deleted");
		Abort();
	}
}

void DeleteRowsCmd::UnExecute() {
	if (check(GetRows()->count() > 0))
		DeleteCellsCmd::UnExecute();
	else 
		GetMainWindow()->SetStatus("aborted: no rows need to be added");
}
