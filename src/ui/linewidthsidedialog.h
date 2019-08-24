//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
//-----------------------------------------------------------------------------
#ifndef _LINEWIDTHSIDEDIALOG_H
#define _LINEWIDTHSIDEDIALOG_H

#include "linewidthdialog.h"

/// line width chooser dialog class with extra option to choose a side
class LineWidthSideDialog: public LineWidthDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	LineWidthSideDialog(Widget parent);
	///
        const char *GetClassName() { return "LineWidthSideDialog";}
protected:
	///
	void MakeLabels(List<string *> *items);
	///
	void MakeItems(List<List<string *> *> *items);
	///
	void MakeBitmaps();
	///
	void MakeLiteClues();
private:
	///
	void Configure();
};
#endif
