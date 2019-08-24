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
#include "table.h"
#include "updatecelltextcmd.h"

UpdateCellTextCmd::UpdateCellTextCmd(Table *t, TableViewer *v, Cell *c, 
		const string *n): Command(t, v) {
	cell = c;
	newText = new string(*n);
	oldText = new string(*(c->GetText()));
}

UpdateCellTextCmd::~UpdateCellTextCmd() {
	delete newText;
	delete oldText;
}

void UpdateCellTextCmd::Execute() {
	if (!cell) {
		GetMainWindow()->SetStatus("aborted: cell does not exist");
		Abort();
		return;
	}
	if (((Table *)GetDocument())->UpdateText(cell, newText)) {
		SetCmdDone(True);
		GetDocument()->IncChanges();
		if (GetViewer()->IsAutoResize())
			((TableViewer *)GetViewer())->RecomputeSizeCell(cell);
		SayCommited();
	}
	else {
		GetMainWindow()->SetStatus("aborted: text is refused");
		Abort();
	}
}

void UpdateCellTextCmd::UnExecute() {
	if (!cell) {
		GetMainWindow()->SetStatus("aborted: cell does not exist");
		return;
	}
	SetCmdDone(False);
	GetDocument()->DecChanges();
	cell->UpdateText(oldText);
	if (GetViewer()->IsAutoResize())
		((TableViewer *)GetViewer())->RecomputeSizeCell(cell);
	SayUndone();
}
