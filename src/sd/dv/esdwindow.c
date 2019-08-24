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
#include "ssdstubs.h"
#include "esddiagram.h"
#include "ssdviewer.h"
#include "ssdgraph.h"
#include "esdwindow.h"
#include "menu.h"
 
// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "C2Line.xbm"
#include "Comment.xbm"
#include "CXRelationshipLine.xbm"
#include "DashedLine.xbm"
#include "Diamond.xbm"
#include "DottedLine.xbm"
#include "DoubleBox.xbm"
#include "EmptyOpenArrow.xbm"
#include "WhiteDot.xbm"
#include "NoteBox.xbm"
 
const char *ESDWindow::ESD_NODE_NAMES[] = 
	{"Entity type",
	 "Entity type + attributes", 
	 "Note",
	 "N-ary relationship",
	 "Generalization junction",
	 "Comment"};
const Bitmap ESDWindow::ESD_NODE_ICONS[] = 
	{{Box_width, Box_height, Box_bits},
	 {DoubleBox_width, DoubleBox_height, DoubleBox_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {Diamond_width, Diamond_height, Diamond_bits},
	 {WhiteDot_width, WhiteDot_height, WhiteDot_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char* ESDWindow::ESD_EDGE_NAMES[] = 
	{"Binary relationship",
	 "Participant link (in N-ary relationship)",
	 "Note connector",
	 "Association entity type link",
	 "Generalization" };

const Bitmap ESDWindow::ESD_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {CXRelationshipLine_width, CXRelationshipLine_height, 
	  CXRelationshipLine_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits},
	 {DashedLine_width, DashedLine_height, DashedLine_bits},
	 {EmptyOpenArrow_width, EmptyOpenArrow_height, EmptyOpenArrow_bits}};
 
ESDWindow::ESDWindow(const char *n) : ERWindow(n) {
	diagramESDBoxItems = 0;
}

ESDWindow::~ESDWindow() {
	if (diagramESDBoxItems)
		delete diagramESDBoxItems;
}

DiagramViewer *ESDWindow::CreateViewer(Config *cfg) {
	return new SSDViewer(cfg, this);
}

Graph *ESDWindow::CreateGraph() {
	return new SSDGraph();
}

Diagram *ESDWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new ESDDiagram(c, this, (SSDViewer *)v, (SSDGraph *)g);
}
 
void ESDWindow::DetermineIcons() {
	 nodeNames = ESD_NODE_NAMES;
	 nodeIcons = ESD_NODE_ICONS;
	 edgeNames = ESD_EDGE_NAMES;
	 edgeIcons = ESD_EDGE_ICONS;
	 nrNodes = XtNumber(ESD_NODE_NAMES);
	 nrEdges = XtNumber(ESD_EDGE_NAMES);
}
 
void ESDWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;
	diagramESDBoxItems = new MenuItem[10]; i=0;
	diagramESDBoxItems[i] = MenuItem(
		"to Single Class Boxes", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_SINGLE_CLASS_BOX, 0, 1); i++;
	diagramESDBoxItems[i] = MenuItem(
		"to Double Class Boxes", MenuItem::PUSHBUTTON, 'D', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_DOUBLE_CLASS_BOX, 0, 1); i++;
	diagramESDBoxItems[i] = MenuItem::NUL;
 
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
		0, 0, 0, diagramESDBoxItems, 1); j++;
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
		"Change Box Type", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramESDBoxItems, 1); k++;
	popupEditItems[j] = MenuItem("", MenuItem::SEPARATOR); k++;
        popupEditItems[j] = MenuItem(
                "Change Read Direction", MenuItem::SUBMENU, '\0', 0, 0,
                0, 0, 0, ERReadDirectionItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;

}
