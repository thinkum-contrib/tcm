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
#ifndef _TRWINDOW_H
#define _TRWINDOW_H

#include "diagramwindow.h"

/// generic textual tree edit window class.
class TRWindow: public DiagramWindow {
/*@Doc: {\large {\bf scope:} TGTT} */
public:
	///
	TRWindow(const char *name);
	///
	void SetLayout(bool b);
private:
	///
	int GetTool() {return Toolkit::GTT;}
	///
	DiagramViewer *CreateViewer(Config *c);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	Widget editButton;
	///
	Widget treeButton;
	///
	Widget CreateTiles(Widget parent);
	///
	Widget CreateLayoutTiles(Widget parent);
	///
	Widget CreateMenuBar(Widget parent);
	///
	static const char *TR_NODE_NAMES[];
	///
	static const Bitmap TR_NODE_ICONS[];
	///
	static const char *TR_EDGE_NAMES[];
	///
	static const Bitmap TR_EDGE_ICONS[];
	///
	void SetSensitive(Menu *menu, const char *label, bool b);
	///
	static void LayoutCB(Widget w, XtPointer num, XtPointer);
};
#endif
