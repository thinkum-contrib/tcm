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
#ifndef _DFWINDOW_H
#define _DFWINDOW_H

#include "diagramwindow.h"

/// data flow edit window class.
class DFWindow: public DiagramWindow {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DFWindow(const char *name);
	///
	virtual ~DFWindow();

	/// dataflow diagrams: set diagram field.
	void SetDiagram(const char *s);
	///
	void SetDiagram(const string *s);
protected:
	///
	MenuItem *dfdItems;
private:
	///
	int GetTool() {return Toolkit::DFD;}
	///
	bool ShowIndexToggle() {return True;}
	///
	Widget CreateMenuBar(Widget);
	///
	DiagramViewer *CreateViewer(Config *config);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	Widget CreateTiles(Widget parent);
	///
	void CreateDiagramField(Widget parent);

	/// Motif TextField for data flow diagram.
	Widget dfDiagram;
	///
	Menu *dfdMenu;
	///
	void InitMenuItems();
	///
	static const char *DF_NODE_NAMES[];
	///
	static const Bitmap DF_NODE_ICONS[];
	///
	static const char *DF_EDGE_NAMES[];
	///
	static const Bitmap DF_EDGE_ICONS[];
	///
	static const char *DF_INDEX_NAME;
	///
	static const Bitmap DF_INDEX_ICON;
};
#endif
