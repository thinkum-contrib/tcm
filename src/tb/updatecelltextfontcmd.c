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
#include "table.h"
#include "tableviewer.h"
#include "updatecelltextfontcmd.h"

UpdateCellTextFontCmd::UpdateCellTextFontCmd(Table *t, TableViewer *v,
		int f, int s, int p): Command(t, v) {
	family = f;
	style = s;
	size = p;
	tviewer = v;
	cells = new List<Cell *>;
	oldFonts = new List<XFont *>;
	GetUpdateCells();
}

UpdateCellTextFontCmd::~UpdateCellTextFontCmd() {
	delete cells;
	delete oldFonts;
}

void UpdateCellTextFontCmd::GetUpdateCells() {
	List<Cell *> *selection = tviewer->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		Cell *cell = selection->cur();
		XFont *ft = cell->GetFont();
		if (family >= 0 && family != ft->GetFamily())
			SaveCell(cell);
		else if (style >= 0 && style != ft->GetStyle())
			SaveCell(cell);
		else if (size > 0 && size != ft->GetSize())
			SaveCell(cell);
	}
}

void UpdateCellTextFontCmd::Execute() {
	if (!cells->first()) {
		GetMainWindow()->SetStatus(
			"aborted: fonts need not be changed");
		Abort();
		return;
	}
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		XFont *newFt = GetNewFont(cell);
		cell->UpdateFont(newFt);
		if (tviewer->IsAutoResize())
			tviewer->RecomputeSizeCell(cell); 
	}
	Command::Execute();
}

void UpdateCellTextFontCmd::UnExecute() {
	for (unsigned i=0; i<cells->count(); i++) {
		Cell *cell = (*cells)[i];
		cell->UpdateFont((*oldFonts)[i]);
		if (tviewer->IsAutoResize())
			tviewer->RecomputeSizeCell(cell); 
	}
	Command::UnExecute();
}

void UpdateCellTextFontCmd::SaveCell(Cell *cell) {
	cells->add(cell);
	oldFonts->add(cell->GetFont());
}

XFont *UpdateCellTextFontCmd::GetNewFont(Cell *cell) {
	XFont *ft = cell->GetFont();
	int f = (family >= 0) ? family : ft->GetFamily();
	int s = (style >= 0) ? style : ft->GetStyle();
	int p = (size >= 0) ? size : ft->GetSize();
	return GetViewer()->GetFont(f, s, p);
}
