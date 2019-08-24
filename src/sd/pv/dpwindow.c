////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "dpwindow.h"
#include "dpdiagram.h"
#include "cpviewer.h"
#include "cpgraph.h"
#include "menu.h"
#include "diagramstubs.h"

// X bitmap data for the tiled buttons
#include "BuildingBlock.xbm"
#include "Comment.xbm"
#include "Cube.xbm"
#include "Dot.xbm"
#include "NoteBox.xbm"
#include "EmptyLine.xbm"
#include "DashedArrow.xbm"
#include "DottedLine.xbm"
 
const char *DPWindow::DP_NODE_NAMES[] =  
	{"Component", 
	 "Resource Node",
	 "Comment",
	 "Interface", 
	 "Note"};

const Bitmap DPWindow::DP_NODE_ICONS [] =
	{{BuildingBlock_width, BuildingBlock_height, BuildingBlock_bits},
	 {Cube_width, Cube_height, Cube_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {Dot_width, Dot_height, Dot_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits}};
 
const char *DPWindow::DP_EDGE_NAMES[] = 
	{"Realization or Communication",
	 "Dependency",
	 "Note connector"};
const Bitmap DPWindow::DP_EDGE_ICONS [] =
	{{EmptyLine_width, EmptyLine_height, EmptyLine_bits},
	 {DashedArrow_width, DashedArrow_height, DashedArrow_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits}};

DPWindow::DPWindow(const char *n): CPWindow(n) {}

Diagram *DPWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new DPDiagram(c, this, (CPViewer *)v, (CPGraph *)g);
}

void DPWindow::DetermineIcons() {
	 nodeNames = DP_NODE_NAMES;
	 nodeIcons = DP_NODE_ICONS;
	 edgeNames = DP_EDGE_NAMES;
	 edgeIcons = DP_EDGE_ICONS;
	 nrNodes = XtNumber(DP_NODE_NAMES);
	 nrEdges = XtNumber(DP_EDGE_NAMES);
}
