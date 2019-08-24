////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "cell.h"
#include "tableviewer.h"
#include "table.h"
#include "replacenextcelltextcmd.h"

ReplaceNextCellTextCmd::ReplaceNextCellTextCmd(Table *t, TableViewer *v, 
	const string *p, const string *o, bool c, bool s): 
	ReplaceCellTextCmd(t, v, p, o, c, s) {}

void ReplaceNextCellTextCmd::Execute() {
	TableViewer *v = GetTableViewer();
	int row = v->GetCurrentRow();
	int column = v->GetCurrentColumn();
	if (column == 0) {
		column = v->GetNumberOfColumns()-1;
		if (row == 0)
			row = v->GetNumberOfRows()-1;
		else
			row--;
	}
	else
		column--;
	v->SetCurrentRow(row);
	v->SetCurrentColumn(column);
	if (*GetReplace() == *GetPattern()) {
		GetMainWindow()->SetStatus(
			"replace next: find and replace texts are identical");
		return;
	}
	Cell *cell = v->GetNextCell(GetPattern(), IsCaseSensitive(), 
				    IsSubstring());
	if (cell) {
		v->DeselectAll();
		int n = 0;
		string copy = *cell->GetText();
		string oldString = *cell->GetText();
		if (IsSubstring() || *GetPattern() == copy) {
			n = copy.replace(*GetPattern(), *GetReplace(), 
					 IsCaseSensitive());
			if (copy != oldString) {
				if (((Table *)GetDocument())->
						UpdateText(cell, &copy)) {
					GetCells()->add(cell);
					GetOldStrings()->add(
						new string(oldString));
					v->SelectCell(cell);
					if (v->IsAutoResize())
						v->RecomputeSizeCell(cell);
					string txt = 
					   "replace next: pattern found, made ";
					txt += n;
					txt += " replacement";
					txt += ((n==1?"":"s"));
					GetMainWindow()->SetStatus(&txt);
				}
				else 
					GetMainWindow()->SetStatus(
					"Replace next: text is refused");
				Point pt = *cell->GetPosition();
				double x = Scale(pt.x);
				double y = Scale(pt.y);
				GetMainWindow()->ShowPosition(static_cast<int>(0.5 + x),
											  static_cast<int>(0.5 + y));
				GetDocument()->IncChanges();
				SetCmdDone(True);
			}
		}
	}
	else
		GetMainWindow()->SetStatus("replace next: pattern not found");
}
