////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "stwindow.h"
#include "stdiagram.h"
#include "stviewer.h"
#include "stgraph.h"

// X bitmap data for the tiled buttons
#include "LongBox.xbm"
#include "ArrowBox.xbm"
#include "TransitionArrow.xbm"
#include "Hexagon.xbm"
#include "Comment.xbm"
 
const char *STWindow::ST_NODE_NAMES[] =
	{"Initial state", "State", "Decision point", "Comment"};

const Bitmap STWindow::ST_NODE_ICONS [] =
	{{ArrowBox_width, ArrowBox_height, ArrowBox_bits},
	 {LongBox_width, LongBox_height, LongBox_bits},
	 {Hexagon_width, Hexagon_height, Hexagon_bits},
	 {Comment_width, Comment_height, Comment_bits}};
 
const char *STWindow::ST_EDGE_NAMES[] = {"Transition"};
const Bitmap STWindow::ST_EDGE_ICONS [] =
	{{TransitionArrow_width, TransitionArrow_height, TransitionArrow_bits}};


STWindow::STWindow(const char *n): DiagramWindow(n) {}

DiagramViewer *STWindow::CreateViewer(Config *cfg) {
	return new STViewer(cfg, this);
}

Graph *STWindow::CreateGraph() {
	return new STGraph();
}

Diagram *STWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new STDiagram(c, this, (STViewer *)v, (STGraph *)g);
}

void STWindow::DetermineIcons() {
	 nodeNames = ST_NODE_NAMES;
	 nodeIcons = ST_NODE_ICONS;
	 edgeNames = ST_EDGE_NAMES;
	 edgeIcons = ST_EDGE_ICONS;
	 nrNodes = XtNumber(ST_NODE_NAMES);
	 nrEdges = XtNumber(ST_EDGE_NAMES);
}
