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
#ifndef _RPWINDOW_H
#define _RPWINDOW_H

#include "diagramwindow.h"

/// recursive process graph edit window class.
class RPWindow: public DiagramWindow {
/*@Doc: {\large {\bf scope:} TRPG} */
public:
	///
	RPWindow(const char *name);
private:
	///
	int GetTool() {return Toolkit::RPG;}
	///
	DiagramViewer *CreateViewer(Config *config);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	static const char *RP_NODE_NAMES[];
	///
	static const Bitmap RP_NODE_ICONS[];
	///
	static const char *RP_EDGE_NAMES[];
	///
	static const Bitmap RP_EDGE_ICONS[];
private:
	/// 
	void InitMenuItems();
	///
        MenuItem *convertItems;
};
#endif
