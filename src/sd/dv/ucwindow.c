//------------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "ucdiagram.h"
#include "ucviewer.h"
#include "ucgraph.h"
#include "ucwindow.h"
#include "menu.h"
#include "diagramstubs.h"
 
// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "BoundaryBox.xbm"
#include "StickMan.xbm"
#include "C2Line.xbm"
#include "Comment.xbm"
#include "Ellipse.xbm"
#include "NoteBox.xbm"
#include "EmptyOpenArrow.xbm"
#include "DottedLine.xbm"
 
const char *UCWindow::UC_NODE_NAMES[] = 
	{"Actor (StickMan)",
	 "Actor (ClassBox)", 
	 "Use Case", 
	 "System",
	 "Note",
	 "Comment"};
const Bitmap UCWindow::UC_NODE_ICONS[] = 
	{{StickMan_width, StickMan_height, StickMan_bits},
	 {Box_width, Box_height, Box_bits},
	 {Ellipse_width, Ellipse_height, Ellipse_bits},
	 {BoundaryBox_width, BoundaryBox_height, BoundaryBox_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char* UCWindow::UC_EDGE_NAMES[] = 
	{"Binary association",
	 "Generalization",
	 "Note connector"};

const Bitmap UCWindow::UC_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {EmptyOpenArrow_width, EmptyOpenArrow_height, EmptyOpenArrow_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits}};
 
UCWindow::UCWindow(const char *n) : ERWindow(n) {
	diagramUCBoxItems = 0;
}

UCWindow::~UCWindow() {
	if (diagramUCBoxItems) {
		delete diagramUCBoxItems;
	}
}

DiagramViewer *UCWindow::CreateViewer(Config *cfg) {
	return new UCViewer(cfg, this);
}

Graph *UCWindow::CreateGraph() {
	return new UCGraph();
}

Diagram *UCWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new UCDiagram(c, this, (UCViewer *)v, (UCGraph *)g);
}
 
void UCWindow::DetermineIcons() {
	 nodeNames = UC_NODE_NAMES;
	 nodeIcons = UC_NODE_ICONS;
	 edgeNames = UC_EDGE_NAMES;
	 edgeIcons = UC_EDGE_ICONS;
	 nrNodes = XtNumber(UC_NODE_NAMES);
	 nrEdges = XtNumber(UC_EDGE_NAMES);
}
 
void UCWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;
	diagramUCBoxItems = new MenuItem[10]; i=0;
	diagramUCBoxItems[i] = MenuItem(
		"to Actor Class Boxes", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::UCD_SINGLE_CLASS_BOX, 0, 1); i++;
	diagramUCBoxItems[i] = MenuItem(
		"to StickMen", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::STICKMAN, 0, 1); i++;
	diagramUCBoxItems[i] = MenuItem::NUL;
 
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
		"Change Actor Type", MenuItem::SUBMENU, 'C', 0, 0, 
		0, 0, 0, diagramUCBoxItems, 1); j++;
	editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;
        editItems[j] = MenuItem(
                "Change Read Direction", MenuItem::SUBMENU, 'R', 0, 0,
                0, 0, 0, ERReadDirectionItems, 1); j++;
	editItems[j] = MenuItem::NUL;

	int k = 0;
	while (popupEditItems[k++].label != 0)
		;
	popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Actor Type", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramUCBoxItems, 1); k++;
	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
        popupEditItems[j] = MenuItem(
                "Change Read Direction", MenuItem::SUBMENU, '\0', 0, 0,
                0, 0, 0, ERReadDirectionItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;

}
