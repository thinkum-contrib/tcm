////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "updatelinewidthtablecmd.h"

UpdateLineWidthTableCmd::UpdateLineWidthTableCmd(Table *t, TableViewer *v, 
		Side::Type d, unsigned w): 
			UpdateLineTableCmd(t, v, d) {
	width = w;
	oldWidths = new List<unsigned>;
	for (GetLines()->first(); !GetLines()->done(); GetLines()->next())
		oldWidths->add(GetLines()->cur()->GetLineWidth());
}

UpdateLineWidthTableCmd::~UpdateLineWidthTableCmd() {
	delete oldWidths;
}

void UpdateLineWidthTableCmd::Execute() {
	if (!GetLines()->first()) {
		GetMainWindow()->SetStatus(
			"aborted: lines need not be changed");
		Abort();
		return;
	}
	for (GetLines()->first(); !GetLines()->done(); GetLines()->next())
		GetLines()->cur()->UpdateLineWidth(width);
	GetViewer()->Refresh();
	UpdateLineTableCmd::Execute();
}

void UpdateLineWidthTableCmd::UnExecute() {
	for (unsigned i=0; i<GetLines()->count(); i++) {
		LinePiece *line = (*GetLines())[i];
		line->UpdateLineWidth((*oldWidths)[i]);
	}
	UpdateLineTableCmd::UnExecute();
}
