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
#include "cell.h"
#include "celltext.h"
#include "dragcelltextcmd.h"
 
DragCellTextCmd::DragCellTextCmd(Table *t, TableViewer *v, CellText *c): 
				DragCmd(t, v) {
	srcCellText = c;
	SetOldPosition((c->GetPosition()));
	copy = c->GetParent()->IsSelected();
	GetMainWindow()->SetCursor(MouseCursor::FLEUR);
}
 
void DragCellTextCmd::Execute() {
	Point pt = *GetOldPosition() + *GetDelta();
	destCellText = GetTableViewer()->HitCellText(pt.x, pt.y);
	if (destCellText && destCellText != srcCellText) {
		oldText = *destCellText->GetText();
		oldFont = destCellText->GetFont();
		string newText = *srcCellText->GetText();
		// if parent of src is selected do a move (otherwise a copy).
		if (!copy) {
			string empty("");
			srcCellText->GetParent()->UpdateText(&empty);
		}
		// give dest cell text the same font. 
		destCellText->UpdateFont(srcCellText->GetFont());
		// Check text and update
		if (!((Table *)GetDocument())->UpdateText(
					destCellText->GetParent(), &newText)) {
			// restore source text.
			srcCellText->GetParent()->UpdateText(&newText);
			GetMainWindow()->SetStatus(
				"aborted: text can not be updated");
			Abort();
			return;
		}
		if (GetTableViewer()->IsAutoResize()) {
			if (!copy) 
				GetTableViewer()->RecomputeSizeCell(
					srcCellText->GetParent());
			GetTableViewer()->RecomputeSizeCell(
				destCellText->GetParent());
		}
		DragCmd::Execute();
	}
	else {
		GetMainWindow()->SetStatus(
			"aborted: text is not moved into a different cell");
		Abort();
	}
}

void DragCellTextCmd::UnExecute() {
	// restore src cell.
	if (!copy)
		srcCellText->GetParent()->UpdateText(destCellText->GetText());
	// restore dest cell.
	destCellText->UpdateFont(oldFont);
	destCellText->GetParent()->UpdateText(&oldText);
	// resize restored cells.
	if (GetTableViewer()->IsAutoResize()) {
		if (!copy) {
			GetTableViewer()->RecomputeSizeCell(
				srcCellText->GetParent());
		}
		GetTableViewer()->RecomputeSizeCell(destCellText->GetParent());
	}
	DragCmd::UnExecute();
}
 
void DragCellTextCmd::DrawOutLine(const Point *d) {
	Point p1 = ScaleCorrect(d);
	Point p2 = *GetOldPosition() + p1;
	srcCellText->DrawOutLine(&p2);
}
