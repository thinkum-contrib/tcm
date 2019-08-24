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
#include "grafport.h"
#include "dragrowcmd.h"
 
DragRowCmd::DragRowCmd(Table *t, TableViewer *v, LinePiece *l): DragCmd(t, v) {
	GetMainWindow()->SetCursor(MouseCursor::V_DOUBLE_ARROW);
	SetOldPosition(l->GetBegin());
	// find the row to be resized.
	Point tmp = *GetOldPosition();
	int f = v->HitRow(tmp.x+1, tmp.y-1);
	if (f >= 0)
		row = v->GiveRow(f);
	else {
		row = 0;
		return;
	}
	if (!check(row))
		return;
	oldSize = row->GetHeight();
}
 
void DragRowCmd::Execute() {
	if (row) {
		int newSize = oldSize + GetDelta()->y;
		GetTableViewer()->ResizeRow(row, newSize);
		DragCmd::Execute();
	}
	else {
		GetMainWindow()->SetStatus("aborted: drag row");
		Abort();
	}
}
 
void DragRowCmd::UnExecute() {
	if (check(row)) {
		GetTableViewer()->ResizeRow(row, oldSize);
		DragCmd::UnExecute();
	}
	else
		GetMainWindow()->SetStatus("aborted: undo drag row");
}
 
void DragRowCmd::DrawOutLine(const Point *d) {
	Point p = ScaleCorrect(d);
	Point pt1 = *GetOldPosition() + p;
	Point pt2 = pt1;
	pt1.x = GetTableViewer()->GetTopLeft()->x;
	pt2.x = GetTableViewer()->GetTopLeft()->x + 
		GetTableViewer()->GetWidth();
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawLine(pt1.x, pt1.y, pt2.x, pt2.y);
}
