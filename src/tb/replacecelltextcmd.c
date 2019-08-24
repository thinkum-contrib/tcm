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
#include "tableviewer.h"
#include "table.h"
#include "cell.h"
#include "replacecelltextcmd.h"

ReplaceCellTextCmd::ReplaceCellTextCmd(Table *t, TableViewer *v, 
	const string *p, const string *o, bool c, bool s): Command(t, v) {
	tviewer = v;
	pattern = new string(*p);
	replace = new string(*o);
	caseSensitive = c;
	substring = s;
	cells = new List<Cell *>;
	oldStrings = new List<string *>;
	oldSelection = new List<Cell *> (*v->GetSelection());
}

ReplaceCellTextCmd::~ReplaceCellTextCmd() {
	oldStrings->clear();
	delete cells;
	delete oldStrings;
	delete oldSelection;
	delete pattern;
	delete replace;
}

void ReplaceCellTextCmd::UnExecute() {
	for (oldStrings->first(), cells->first(); 
	    !oldStrings->done() && !cells->done(); 
	    oldStrings->next(), cells->next()) {
		cells->cur()->UpdateText(oldStrings->cur());
		if (tviewer->IsAutoResize())
			tviewer->RecomputeSizeCell(cells->cur());
	}
	tviewer->DeselectAll();
	for (oldSelection->first(); !oldSelection->done(); oldSelection->next())
		tviewer->SelectCell(oldSelection->cur());

	Command::UnExecute();
}

void ReplaceCellTextCmd::ReExecute() {
	cells->empty();
	oldStrings->clear();
	Execute();
}
