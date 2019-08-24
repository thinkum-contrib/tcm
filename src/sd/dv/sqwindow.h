//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SQWINDOW_H
#define _SQWINDOW_H

#include "erwindow.h"

/// class-relationship edit window class.
class SQWindow: public ERWindow {
/*@Doc: {\large {\bf scope:} TSQD} */
public:
	///
	SQWindow(const char *name);
	///
	virtual ~SQWindow();
private:
	///
	int GetTool() {return Toolkit::SQD;}
	///
	DiagramViewer *CreateViewer(Config *config);
	///
	Graph *CreateGraph();
	///
	Diagram *CreateDiagram(Config *c, DiagramViewer *v, Graph *g);
	///
	void DetermineIcons();
	///
	MenuItem *diagramSQActorItems;
	///
	MenuItem *diagramSQClassStereotypeItems;
	///
	MenuItem *diagramSQClassPropertiesItems;
	///
	void InitMenuItems();
	///
	static const char *SQ_NODE_NAMES[];
	///
	static const Bitmap SQ_NODE_ICONS[];
	///
	static const char *SQ_EDGE_NAMES[];
	///
	static const Bitmap SQ_EDGE_ICONS[];
};
#endif
