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
#include "updatelinestyletablecmd.h"
#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> inline void List<LineStyle::Type>::clear() { empty(); }
#else
inline void List<LineStyle::Type>::clear() { empty(); }
#endif
#endif

UpdateLineStyleTableCmd::UpdateLineStyleTableCmd(Table *t, TableViewer *v, 
		Side::Type d, LineStyle::Type s): 
			UpdateLineTableCmd(t, v, d) {
	style = s;
	oldStyles = new List<LineStyle::Type>;
	for (GetLines()->first(); !GetLines()->done(); GetLines()->next())
		oldStyles->add(GetLines()->cur()->GetLineStyle());
}

UpdateLineStyleTableCmd::~UpdateLineStyleTableCmd() {
	delete oldStyles;
}

void UpdateLineStyleTableCmd::Execute() {
	if (!GetLines()->first()) {
		GetMainWindow()->SetStatus(
			"aborted: lines need not be changed");
		Abort();
		return;
	}
	for (GetLines()->first(); !GetLines()->done(); GetLines()->next())
		GetLines()->cur()->UpdateLineStyle(style);
	UpdateLineTableCmd::Execute();
}

void UpdateLineStyleTableCmd::UnExecute() {
	for (unsigned i=0; i<GetLines()->count(); i++) {
		LinePiece *line = (*GetLines())[i];
		line->UpdateLineStyle((*oldStyles)[i]);
	}
	UpdateLineTableCmd::UnExecute();
}
