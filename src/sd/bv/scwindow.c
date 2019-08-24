////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "scwindow.h"
#include "scviewer.h"
#include "scdiagram.h"
#include "scgraph.h"

// X bitmap data for the tiled buttons
#include "RoundedBox.xbm"
#include "AndStateBox.xbm"
#include "BlackDot.xbm"
#include "Comment.xbm"
#include "BullsEye.xbm"
#include "MiniDiamond.xbm"
#include "SolidHorizontalBar.xbm"
#include "SolidVerticalBar.xbm"
#include "NoteBox.xbm"
#include "Arrow.xbm"
#include "DashedEmptyLine.xbm"
#include "DottedLine.xbm"

const char *SCWindow::SC_NODE_NAMES[] =
	{"State", "And-state", "Default state", "Final state", "Comment",
	"Decision pseudostate", "Synchronization pseudostate", "Synchronization pseudostate",
	"Comment"};

const Bitmap SCWindow::SC_NODE_ICONS [] =
	{{RoundedBox_width, RoundedBox_height, RoundedBox_bits},
	 {AndStateBox_width, AndStateBox_height, AndStateBox_bits},
	 {BlackDot_width, BlackDot_height, BlackDot_bits},
	 {BullsEye_width, BullsEye_height, BullsEye_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {MiniDiamond_width, MiniDiamond_height, MiniDiamond_bits},
	 {SolidHorizontalBar_width, SolidHorizontalBar_height, SolidHorizontalBar_bits},
	 {SolidVerticalBar_width, SolidVerticalBar_height, SolidVerticalBar_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits}};
 
const char *SCWindow::SC_EDGE_NAMES[] = {"Transition", "Note connector", "And-line"};
const Bitmap SCWindow::SC_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits},
	 {DashedEmptyLine_width, DashedEmptyLine_height, DashedEmptyLine_bits}};


SCWindow::SCWindow(const char *n): DiagramWindow(n) {
}

DiagramViewer *SCWindow::CreateViewer(Config *cfg) {
	return new SCViewer(cfg, this);
}

Graph *SCWindow::CreateGraph() {
	return new SCGraph();
}

Diagram *SCWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	return new SCDiagram(c, this, (SCViewer *)v, (SCGraph *)g);
}

void SCWindow::DetermineIcons() {
	 nodeNames = SC_NODE_NAMES;
	 nodeIcons = SC_NODE_ICONS;
	 edgeNames = SC_EDGE_NAMES;
	 edgeIcons = SC_EDGE_ICONS;
	 nrNodes = XtNumber(SC_NODE_NAMES);
	 nrEdges = XtNumber(SC_EDGE_NAMES);
}
