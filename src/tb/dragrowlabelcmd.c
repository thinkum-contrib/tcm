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
#include "rowcolumnlabel.h"
#include "dragrowlabelcmd.h"
 
DragRowLabelCmd::DragRowLabelCmd(Table *t, TableViewer *v, RowColumnLabel *rc): 
				DragCmd(t, v) {
	int nr = rc->GetVector()->GetNumber();
	row = v->GiveRow(nr);
	oldNr = nr;
	label = rc;
	SetOldPosition((label->GetPosition()));
	GetMainWindow()->SetCursor(MouseCursor::FLEUR);
}
 
void DragRowLabelCmd::DrawOutLine(const Point *d) {
	Point p1 = ScaleCorrect(d);
	Point p2 = *GetOldPosition() + p1; 
	label->DrawOutLine(&p2);
}
 
void DragRowLabelCmd::Execute() {
	Point newPosition = *GetOldPosition() + *GetDelta();
	newNr = GetTableViewer()->HitRow(newPosition.x, newPosition.y);
	if (newNr == oldNr) {
		GetMainWindow()->SetStatus("aborted: drag row label");
		Abort();
	}
	else if (newNr >= 0) {
		GetTableViewer()->MoveRow(row, newNr);
		DragCmd::Execute();
	}
	else {
		GetMainWindow()->SetStatus("aborted: drag row label");
		Abort();
	}
}

void DragRowLabelCmd::UnExecute() {
	if (newNr >= 0 && newNr != oldNr)
		GetTableViewer()->MoveRow(row, oldNr);
	DragCmd::UnExecute();
}
