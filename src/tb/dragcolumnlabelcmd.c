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
#include "cellcolumn.h"
#include "rowcolumnlabel.h"
#include "dragcolumnlabelcmd.h"
 
DragColumnLabelCmd::DragColumnLabelCmd(Table *t, TableViewer *v, 					RowColumnLabel *rc): DragCmd(t, v) {
	int nr = rc->GetVector()->GetNumber();
	column = v->GiveColumn(nr);
	label = rc;
	oldNr = nr;
	SetOldPosition(label->GetPosition());
	GetMainWindow()->SetCursor(MouseCursor::FLEUR);
}
 
void DragColumnLabelCmd::DrawOutLine(const Point *d) {
	Point p1 = ScaleCorrect(d);
	Point p2 = *GetOldPosition() + p1;
	label->DrawOutLine(&p2);
}
 
void DragColumnLabelCmd::Execute() {
	Point newPosition = *GetOldPosition() + *GetDelta();
	newNr = GetTableViewer()->HitColumn(newPosition.x, newPosition.y);
	if (newNr == oldNr) {
		GetMainWindow()->SetStatus("aborted: drag column label");
		Abort();
	}
	else if (newNr >= 0) {
		GetTableViewer()->MoveColumn(column, newNr);
		DragCmd::Execute();
	}
	else {
		GetMainWindow()->SetStatus("aborted: drag column label");
		Abort();
	}
}

void DragColumnLabelCmd::UnExecute() {
	if (newNr >= 0 && newNr != oldNr)
		GetTableViewer()->MoveColumn(column, oldNr);
	DragCmd::UnExecute();
}
