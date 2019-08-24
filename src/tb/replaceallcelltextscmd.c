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
#include "celltext.h"
#include "cell.h"
#include "cellrow.h"
#include "tableviewer.h"
#include "table.h"
#include "messagedialog.h"
#include "replaceallcelltextscmd.h"

ReplaceAllCellTextsCmd::ReplaceAllCellTextsCmd(Table *t, TableViewer *v, 
	const string *p, const string *o, bool c, bool s): 
	ReplaceCellTextCmd(t, v, p, o, c, s) {}

void ReplaceAllCellTextsCmd::Execute() {
	if (*GetReplace() == *GetPattern()) {
		GetMainWindow()->SetStatus(
			"replace next: find and replace texts are identical");
		return;
	}
	int count = 0;
	int replaces = 0;
	bool error = False;
	TableViewer *v = GetTableViewer();
	v->DeselectAll();
	int rows = v->GetNumberOfRows();
	int columns = v->GetNumberOfColumns();
	for (int i=0; i<rows; i++) {
		CellRow *row = v->GiveRow(i);
		for (int j=0; j<columns; j++) {
			Cell *cell = row->NthCell(j);
			string copy = *cell->GetText();
			string oldString = *cell->GetText();
			if (!error && (IsSubstring()||*GetPattern() == copy)) {
				int r = copy.replace(*GetPattern(), 
							*GetReplace(), 
							IsCaseSensitive());
				if (copy != oldString) {
					if (((Table *)GetDocument())->
						UpdateText(cell, &copy)) {
						GetCells()->add(cell);
						GetOldStrings()->add(
							new string(oldString));
						v->SelectCell(cell);
						if (v->IsAutoResize())
							v->
							RecomputeSizeCell(cell);
						count++;
						replaces += r;
					}
					else
						error = True;
				}
			}
		}
	}
	if (error) {
		MessageDialog *d = new MessageDialog(
			GetMainWindow()->GetWidget(), MessageDialog::WARNING);
		d->SetCenteredOnPointer(False);
		d->Show("Warning", 
			"Replace all is aborted after the first"
			  " encountered error");
	}
	if (count == 0)
		GetMainWindow()->SetStatus("replace all: pattern not found");
	else {
		string txt = "replace all: ";
		txt += count;
		txt += " found, made ";
		txt += replaces;
		txt += " replacement";
		txt += ((count==1)?"":"s");
		GetMainWindow()->SetStatus(&txt);
	}
	GetDocument()->IncChanges();
	SetCmdDone(True);
}
