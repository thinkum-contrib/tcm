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
#include "cutcelltextscmd.h"
 
CutCellTextsCmd::CutCellTextsCmd(Table *t, TableViewer *v): 
			CopyCellTextsCmd(t, v) {
	selection = new List<Cell *> (*v->GetSelection());
	oldStrings = new List<string *>;
	for (selection->first(); !selection->done(); selection->next()) {
		string *s = new string(*selection->cur()->GetText());
		oldStrings->add(s);
	}
}

CutCellTextsCmd::~CutCellTextsCmd(){
	oldStrings->clear();
	delete oldStrings;
	delete selection;
}

void CutCellTextsCmd::Execute() {
	List<CellText *> *texts = GetCellTexts();
	if (texts->count() == 0) {
		GetMainWindow()->SetStatus("aborted: no texts need to be cut");
		Abort();
		return;
	}
	CopyCellTextsCmd::Execute();
	string empty("");
	for (selection->first(); !selection->done(); selection->next()) {
		selection->cur()->UpdateText(&empty);
		if (GetViewer()->IsAutoResize())
			GetTableViewer()->RecomputeSizeCell(selection->cur());
	}
	Command::Execute();
}

void CutCellTextsCmd::UnExecute() {
	CopyCellTextsCmd::UnExecute();
	if (selection->first() && oldStrings->first()) {
		do {
			selection->cur()->UpdateText(oldStrings->cur());
			if (GetViewer()->IsAutoResize())
				GetTableViewer()->
					RecomputeSizeCell(selection->cur());
		} while (selection->next() && oldStrings->next());
	}
	Command::UnExecute();
}
