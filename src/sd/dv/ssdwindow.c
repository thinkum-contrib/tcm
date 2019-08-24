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
#include "ssddiagram.h"
#include "ssdviewer.h"
#include "ssdgraph.h"
#include "ssdwindow.h"
#include "menu.h"
 
// X bitmap data for the tiled buttons
#include "Aggregation.xbm"
#include "Box.xbm"
#include "BlackDot.xbm"
#include "C2Line.xbm"
#include "Comment.xbm"
#include "Composition.xbm"
#include "DashedLine.xbm"
#include "Diamond.xbm"
#include "DottedLine.xbm"
#include "DoubleBox.xbm"
#include "EmptyOpenArrow.xbm"
#include "WhiteDot.xbm"
#include "NoteBox.xbm"
#include "ObjectBox.xbm"
#include "ObjectDoubleBox.xbm"
#include "R2Line.xbm"
#include "TripleBox.xbm"
#include "CXRelationshipLine.xbm"
 
const char *SSDWindow::SSD_NODE_NAMES[] = 
	{"Class" , "Class + attributes", 
	 "Class + attributes + operations", 
	 "N-ary association",
	 "Comment",
	 "Object" , "Object + attribute values", 
	 "Note",
	 "Generalization junction",
	 "Aggregation junction"};
const Bitmap SSDWindow::SSD_NODE_ICONS[] = 
	{{Box_width, Box_height, Box_bits},
	 {DoubleBox_width, DoubleBox_height, DoubleBox_bits},
	 {TripleBox_width, TripleBox_height, TripleBox_bits},
	 {Diamond_width, Diamond_height, Diamond_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {ObjectBox_width, ObjectBox_height, ObjectBox_bits},
	 {ObjectDoubleBox_width, ObjectDoubleBox_height, ObjectDoubleBox_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {WhiteDot_width, WhiteDot_height, WhiteDot_bits},
	 {BlackDot_width, BlackDot_height, BlackDot_bits}};

const char* SSDWindow::SSD_EDGE_NAMES[] = 
	{"Binary association",
	 "Participant link (in N-ary association)",
	 "Association class link",
	 "Note connector",
	 "Object link",
	 "Generalization",
	 "Aggregation",
	 "Composition"};

const Bitmap SSDWindow::SSD_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {CXRelationshipLine_width, CXRelationshipLine_height, 
	  CXRelationshipLine_bits},
	 {DashedLine_width, DashedLine_height, DashedLine_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits},
	 {R2Line_width, R2Line_height, R2Line_bits},
	 {EmptyOpenArrow_width, EmptyOpenArrow_height, EmptyOpenArrow_bits},
	 {Aggregation_width, Aggregation_height, Aggregation_bits},
	 {Composition_width, Composition_height, Composition_bits}};
 
SSDWindow::SSDWindow(const char *n) : ERWindow(n) {
	diagramSSDBoxItems = 0;
	diagramSSDClassStereotypeItems = 0;
	diagramSSDClassPropertiesItems = 0;
}

SSDWindow::~SSDWindow() {
	if (diagramSSDBoxItems) {
		delete diagramSSDBoxItems;
		delete diagramSSDClassStereotypeItems;
		delete diagramSSDClassPropertiesItems;
	}
}

DiagramViewer *SSDWindow::CreateViewer(Config *cfg) {
	return new SSDViewer(cfg, this);
}

Graph *SSDWindow::CreateGraph() {
	return new SSDGraph();
}

Diagram *SSDWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new SSDDiagram(c, this, (SSDViewer *)v, (SSDGraph *)g);
}
 
void SSDWindow::DetermineIcons() {
	 nodeNames = SSD_NODE_NAMES;
	 nodeIcons = SSD_NODE_ICONS;
	 edgeNames = SSD_EDGE_NAMES;
	 edgeIcons = SSD_EDGE_ICONS;
	 nrNodes = XtNumber(SSD_NODE_NAMES);
	 nrEdges = XtNumber(SSD_EDGE_NAMES);
}
 
void SSDWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;
	diagramSSDBoxItems = new MenuItem[10]; i=0;
	diagramSSDBoxItems[i] = MenuItem(
		"to Single Class Boxes", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_SINGLE_CLASS_BOX, 0, 1); i++;
	diagramSSDBoxItems[i] = MenuItem(
		"to Double Class Boxes", MenuItem::PUSHBUTTON, 'D', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_DOUBLE_CLASS_BOX, 0, 1); i++;
	diagramSSDBoxItems[i] = MenuItem(
		"to Triple Class Boxes", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_TRIPLE_CLASS_BOX, 0, 1); i++;

	diagramSSDBoxItems[i] = MenuItem(
		"to Single Object Boxes", MenuItem::PUSHBUTTON, 'O', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_SINGLE_OBJECT_BOX, 0, 1); i++;
	diagramSSDBoxItems[i] = MenuItem(
		"to Double Object Boxes", MenuItem::PUSHBUTTON, 'B', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SSD_DOUBLE_OBJECT_BOX, 0, 1); i++;
	diagramSSDBoxItems[i] = MenuItem::NUL;
 

	diagramSSDClassStereotypeItems = new MenuItem[10]; i=0;
	diagramSSDClassStereotypeItems[i] = MenuItem(
		"Show Stereotype", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		SSDStubs::ShowStereotypeCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramSSDClassStereotypeItems[i] = MenuItem(
		"Hide Stereotype", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		SSDStubs::HideStereotypeCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramSSDClassStereotypeItems[i] = MenuItem::NUL;

	diagramSSDClassPropertiesItems = new MenuItem[10]; i=0;
	diagramSSDClassPropertiesItems[i] = MenuItem(
		"Show Properties", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		SSDStubs::ShowPropertiesCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramSSDClassPropertiesItems[i] = MenuItem(
		"Hide Properties", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		SSDStubs::HidePropertiesCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramSSDClassPropertiesItems[i] = MenuItem::NUL;

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
		0, 0, 0, diagramSSDBoxItems, 1); j++;
	editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, 'h', 0, 0, 
		0, 0, 0, diagramSSDClassStereotypeItems, 1); j++;
	editItems[j] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, 'a', 0, 0, 
		0, 0, 0, diagramSSDClassPropertiesItems, 1); j++;
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
		0, 0, 0, diagramSSDBoxItems, 1); k++;
	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramSSDClassStereotypeItems, 1); k++;
	popupEditItems[k] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramSSDClassPropertiesItems, 1); k++;
	popupEditItems[j] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[j] = MenuItem(
		"Change Read Direction", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, ERReadDirectionItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;

}
