//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _DCFWINDOW_H
#define _DCFWINDOW_H

#include "dfwindow.h"

/// data and event flow edit window class.
class DCFWindow: public DFWindow {
/*@Doc: {\large {\bf scope:} TEFD} */
public:
	///
	DCFWindow(const char *name);
private:
	///
	int GetTool() {return Toolkit::EFD;}
	///
	DiagramViewer *CreateViewer(Config *c);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	void InitMenuItems();
	///
	static const char *DCF_NODE_NAMES[];
	///
	static const Bitmap DCF_NODE_ICONS[];
	///
	static const char *DCF_EDGE_NAMES[];
	///
	static const Bitmap DCF_EDGE_ICONS[];
};
#endif
