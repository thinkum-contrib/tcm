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
#include "crwindow.h"
#include "crdiagram.h"
#include "crviewer.h"
#include "crgraph.h"
#include "menu.h"
#include "diagramstubs.h"
 
// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "C1Arrow.xbm"
#include "C2Line.xbm"
#include "DashedC1Arrow.xbm"
#include "DashedDot.xbm"
#include "Dot.xbm"
#include "DoubleBox.xbm"
#include "EmptyLine.xbm"
#include "IsaArrow.xbm"
#include "TripleBox.xbm"
#include "Comment.xbm"
#include "DoubleArrow.xbm"
 
const char *CRWindow::CR_NODE_NAMES[] = 
	{"Object class", "Object class + Attributes", 
	 "Object class + Attributes + Operations", 
	 "Taxonomy junction", "Mode junction", "Comment"};
const Bitmap CRWindow::CR_NODE_ICONS[] = 
	{{Box_width, Box_height, Box_bits},
	 {DoubleBox_width, DoubleBox_height, DoubleBox_bits},
	 {TripleBox_width, TripleBox_height, TripleBox_bits},
	 {Dot_width, Dot_height, Dot_bits},
	 {DashedDot_width, DashedDot_height, DashedDot_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char *CRWindow::CR_EDGE_NAMES[] = 
	{"Binary relationship", "Function", "Component function", 
		"Is-a relationship", "Empty edge", "One-one function"};
const Bitmap CRWindow::CR_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {C1Arrow_width, C1Arrow_height, C1Arrow_bits},
	 {DashedC1Arrow_width, DashedC1Arrow_height, DashedC1Arrow_bits},
	 {IsaArrow_width, IsaArrow_height, IsaArrow_bits},
	 {EmptyLine_width, EmptyLine_height, EmptyLine_bits},
	 {DoubleArrow_width, DoubleArrow_height, DoubleArrow_bits}};
 
CRWindow::CRWindow(const char *n): ERWindow(n) {
	diagramCRBoxItems = 0;
}

CRWindow::~CRWindow() {
	if (diagramCRBoxItems)
		delete diagramCRBoxItems;
}

DiagramViewer *CRWindow::CreateViewer(Config *cfg) {
	return new CRViewer(cfg, this);
}

Graph *CRWindow::CreateGraph() {
	return new CRGraph();
}

Diagram *CRWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new CRDiagram(c, this, (CRViewer *)v, (CRGraph *)g);
}
 
void CRWindow::DetermineIcons() {
	 nodeNames = CR_NODE_NAMES;
	 nodeIcons = CR_NODE_ICONS;
	 edgeNames = CR_EDGE_NAMES;
	 edgeIcons = CR_EDGE_ICONS;
	 nrNodes = XtNumber(CR_NODE_NAMES);
	 nrEdges = XtNumber(CR_EDGE_NAMES);
}
 
void CRWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;
	diagramCRBoxItems = new MenuItem[10]; i=0;
	diagramCRBoxItems[i] = MenuItem(
		"to Single Boxes", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::BOX, 0, 1); i++;
	diagramCRBoxItems[i] = MenuItem(
		"to Double Boxes", MenuItem::PUSHBUTTON, 'D', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::DOUBLE_BOX, 0, 1); i++;
	diagramCRBoxItems[i] = MenuItem(
		"to Triple Boxes", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::TRIPLE_BOX, 0, 1); i++;
	diagramCRBoxItems[i] = MenuItem::NUL;
 
	// delete last menu item: hide value types.
	int n = 0;
	while (viewItems[n++].label != 0)
		;
	viewItems[n-2] = MenuItem::NUL;

	int j = 0;
	while (editItems[j++].label != 0)
		;
	editItems[--j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Change Box Type", MenuItem::SUBMENU, 'C', 0, 0, 
		0, 0, 0, diagramCRBoxItems, 1); j++;
	editItems[j] = MenuItem::NUL;

	int k = 0;
	while (popupEditItems[k++].label != 0)
		;
	popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Box Type", MenuItem::SUBMENU, 'C', 0, 0, 
		0, 0, 0, diagramCRBoxItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;
}
