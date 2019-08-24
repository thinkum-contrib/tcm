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
#ifndef _FDWINDOW_H
#define _FDWINDOW_H

#include "trwindow.h"

/// function refinement tree edit window class.
class FDWindow: public TRWindow {
/*@Doc: {\large {\bf scope:} TFRT} */
public:
	///
	FDWindow(const char *name);
private:
	///
	int GetTool() {return Toolkit::FDT;}
	///
	DiagramViewer *CreateViewer(Config *c);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	static const char *FD_NODE_NAMES[];
	///
	static const Bitmap FD_NODE_ICONS[];
	///
	static const char *FD_EDGE_NAMES[];
	///
	static const Bitmap FD_EDGE_ICONS[];
};
#endif
