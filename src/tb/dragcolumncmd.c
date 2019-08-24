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
#include "grafport.h"
#include "dragcolumncmd.h"
 
DragColumnCmd::DragColumnCmd(Table *t, TableViewer *v, LinePiece *l): 
		DragCmd(t, v) {
	GetMainWindow()->SetCursor(MouseCursor::H_DOUBLE_ARROW);
	SetOldPosition(l->GetBegin());
	// find the column to be resized.
	Point tmp = *GetOldPosition();
	int f = v->HitColumn(tmp.x-1, tmp.y+1);
	if (f >= 0)
		column = v->GiveColumn(f);
	else {
		column = 0;
		return;
	}
	if (!check(column))
		return;
	oldSize = column->GetWidth();
}

void DragColumnCmd::Execute() {
	if (column) {
		int newSize = oldSize + GetDelta()->x;
		GetTableViewer()->ResizeColumn(column, newSize);
		DragCmd::Execute();
	}
	else {
		GetMainWindow()->SetStatus("aborted: drag column");
		Abort();
	}
}
 
void DragColumnCmd::UnExecute() {
	if (check(column)) {
		GetTableViewer()->ResizeColumn(column, oldSize);
		DragCmd::UnExecute();
	}
	else
		GetMainWindow()->SetStatus("aborted: undo drag column");
}
 
void DragColumnCmd::DrawOutLine(const Point *d) {
	Point pt1 = ScaleCorrect(d);
	Point pt2 = *GetOldPosition() + pt1;
	Point pt3 = pt2;
	pt2.y = GetTableViewer()->GetTopLeft()->y;
	pt3.y = GetTableViewer()->GetTopLeft()->y + 
		GetTableViewer()->GetHeight();
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawLine(pt2.x, pt2.y, pt3.x, pt3.y);
}
