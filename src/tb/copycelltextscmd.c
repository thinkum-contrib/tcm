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
#include "copycelltextscmd.h"
#include "tableviewer.h"
#include "table.h"
#include "cell.h"
#include "celltext.h"
#include "celltextbuffer.h"
#include "cellrow.h"
#include "cellcolumn.h"
 
CopyCellTextsCmd::CopyCellTextsCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	cellTexts = new List<CellText *>;
	rcPositions = new List<Point *>;
	buffer = v->GetBuffer();
	List<Cell *> *selection = v->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		Cell *cell = selection->cur();
		if (*cell->GetText() != "") {
			CellText *text = new CellText(*cell->GetCellText());
			cellTexts->add(text);
			Point *pt = new Point;
			pt->x = cell->GetRow()->GetNumber();
			pt->y = cell->GetColumn()->GetNumber();
			rcPositions->add(pt);
		}
	}
}

CopyCellTextsCmd::~CopyCellTextsCmd() {
	cellTexts->clear();
	delete cellTexts;
	rcPositions->clear();
	delete rcPositions;
}
 
void CopyCellTextsCmd::Execute() {
	if (cellTexts->count() == 0) {
		GetMainWindow()->SetStatus(
			"aborted: no texts need to be copied");
		Abort();
		return;
	}
	buffer->PutTexts(cellTexts);
	buffer->PutPositions(rcPositions);
	SetCmdDone(True);
	SayCommited();
}

void CopyCellTextsCmd::UnExecute() {
	buffer->UndoPut();
	SetCmdDone(False);
	SayUndone();
}
