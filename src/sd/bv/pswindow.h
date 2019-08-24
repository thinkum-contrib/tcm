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
#ifndef _PSWINDOW_H
#define _PSWINDOW_H

#include "diagramwindow.h"

/// process structure edit window class.
class PSWindow: public DiagramWindow {
/*@Doc: {\large {\bf scope:} TPSD} */
public:
	///
	PSWindow(const char *name);
	///
	virtual ~PSWindow();
private:
	///
	int GetTool() {return Toolkit::PSD;}
	///
	DiagramViewer *CreateViewer(Config *config);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
//	Widget CreateMenuBar(Widget parent);
	///
	MenuItem *diagramPSShowSequenceItems;
	///
	void InitMenuItems();
	///
	static const char *PS_NODE_NAMES[];
	///
	static const Bitmap PS_NODE_ICONS[];
	///
	static const char *PS_EDGE_NAMES[];
	///
	static const Bitmap PS_EDGE_ICONS[];
};
#endif
