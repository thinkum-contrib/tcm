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
#include "dcfwindow.h"
#include "dcfdiagram.h"
#include "dcfviewer.h"
#include "dcfgraph.h"
#include "dcfstubs.h"
#include "menu.h"

// X bitmap data for the tiled buttons
#include "Arrow.xbm"
#include "HorizontalBar.xbm"
#include "TopLabeledCircle.xbm"
#include "DashedTopLabeledCircle.xbm"
#include "DashedHorizontalBar.xbm"
#include "DoubleArrow.xbm"
#include "DashedArrow.xbm"
#include "DoubleHeadedArrow.xbm"
#include "DashedDoubleHeadedArrow.xbm"
#include "Comment.xbm"
#include "Square.xbm"
#include "BlackDot.xbm"
 
const char *DCFWindow::DCF_NODE_NAMES[] =  
	{"Data process", "Control process",
	 "External entity", "Data store", 
	 "Event Store", "Split/merge node", "Comment"};
const Bitmap DCFWindow::DCF_NODE_ICONS [] =
	{{TopLabeledCircle_width, TopLabeledCircle_height, TopLabeledCircle_bits},
	{DashedTopLabeledCircle_width, DashedTopLabeledCircle_height, 
	 DashedTopLabeledCircle_bits},
	{Square_width, Square_height, Square_bits},
	{HorizontalBar_width, HorizontalBar_height, HorizontalBar_bits},
	{DashedHorizontalBar_width, DashedHorizontalBar_height, 
	 DashedHorizontalBar_bits},
	{BlackDot_width, BlackDot_height, BlackDot_bits},
	{Comment_width, Comment_height, Comment_bits}};
 
const char *DCFWindow::DCF_EDGE_NAMES[] =  
	{"Discrete data flow", "Discrete Event flow", 
	 "Bidirectional discrete data flow", "Continuous data flow",
	 "Continuous event flow" };
const Bitmap DCFWindow::DCF_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits},
	 {DashedArrow_width, DashedArrow_height, DashedArrow_bits},
	 {DoubleArrow_width, DoubleArrow_height, DoubleArrow_bits},
	 {DoubleHeadedArrow_width, DoubleHeadedArrow_height, 
	  DoubleHeadedArrow_bits},
	 {DashedDoubleHeadedArrow_width, DashedDoubleHeadedArrow_height, 
	  DashedDoubleHeadedArrow_bits}};
 
DCFWindow::DCFWindow(const char *n): DFWindow(n) { }

DiagramViewer *DCFWindow::CreateViewer(Config *cfg) {
	return new DCFViewer(cfg, this);
}

Graph *DCFWindow::CreateGraph() {
	return new DCFGraph();
}

Diagram *DCFWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new DCFDiagram(c, this, (DCFViewer *)v, (DCFGraph *)g);
}

void DCFWindow::DetermineIcons() {
	 nodeNames = DCF_NODE_NAMES;
	 nodeIcons = DCF_NODE_ICONS;
	 edgeNames = DCF_EDGE_NAMES;
	 edgeIcons = DCF_EDGE_ICONS;
	 nrNodes = XtNumber(DCF_NODE_NAMES);
	 nrEdges = XtNumber(DCF_EDGE_NAMES);
}

void DCFWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
	int i=0;
	dfdItems = new MenuItem[25]; i=0;
	dfdItems[i] = MenuItem(
		"Minispec...", MenuItem::PUSHBUTTON, 'M', 0, 0,
		DCFStubs::MinispecCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); i++;
	dfdItems[i] = MenuItem(
		"Persistence...", MenuItem::PUSHBUTTON, 'P', 0, 0,
		DCFStubs::PersistenceCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); i++;
	dfdItems[i] = MenuItem(
		"Activation mechanism...", MenuItem::PUSHBUTTON, 'A', 0, 0,
		DCFStubs::ActivationCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); i++;
	dfdItems[i] = MenuItem::NUL;
}
