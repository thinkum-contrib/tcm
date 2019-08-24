//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
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
#include "cbdiagram.h"
#include "cbviewer.h"
#include "cbgraph.h"
#include "cbstubs.h"
#include "cbwindow.h"
#include "menu.h"
#include "diagramstubs.h"
 
// X bitmap data for the tiled buttons
#include "C2Line.xbm"
#include "Comment.xbm"
#include "DottedLine.xbm"
#include "NoteBox.xbm"
#include "ActorBox.xbm"
#include "ActorObjectBox.xbm"
#include "Box.xbm"
#include "ObjectBox.xbm"
#include "R2Line.xbm"
#include "StickMan.xbm"
#include "StickManObject.xbm"
 
const char *CBWindow::CB_NODE_NAMES[] = 
	{"Actor (StickMan/Class)",
	 "Actor (ClassBox)", 
	 "Class",
	 "Comment",
	 "Actor (StickMan/Object)",
	 "Actor (ObjectBox)", 
	 "Object",
	 "Note"};
const Bitmap CBWindow::CB_NODE_ICONS[] = 
	{{StickMan_width, StickMan_height, StickMan_bits},
	 {ActorBox_width, ActorBox_height, ActorBox_bits},
	 {Box_width, Box_height, Box_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {StickManObject_width, StickManObject_height, StickManObject_bits},
	 {ActorObjectBox_width, ActorObjectBox_height, ActorObjectBox_bits},
	 {ObjectBox_width, ObjectBox_height, ObjectBox_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits}};

const char* CBWindow::CB_EDGE_NAMES[] = 
	{"Class link",
	 "Note connector",
	 "Object link"};

const Bitmap CBWindow::CB_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits},
	 {R2Line_width, R2Line_height, R2Line_bits}};
 
CBWindow::CBWindow(const char *n) : ERWindow(n) {
	diagramCBActorItems = 0;
	diagramCBClassStereotypeItems = 0;
	diagramCBClassPropertiesItems = 0;
}

CBWindow::~CBWindow() {
	if (diagramCBActorItems) {
		delete diagramCBActorItems;
		delete diagramCBClassStereotypeItems;
		delete diagramCBClassPropertiesItems;
	}
}

DiagramViewer *CBWindow::CreateViewer(Config *cfg) {
	return new CBViewer(cfg, this);
}

Graph *CBWindow::CreateGraph() {
	return new CBGraph();
}

Diagram *CBWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new CBDiagram(c, this, (CBViewer *)v, (CBGraph *)g);
}
 
void CBWindow::DetermineIcons() {
	 nodeNames = CB_NODE_NAMES;
	 nodeIcons = CB_NODE_ICONS;
	 edgeNames = CB_EDGE_NAMES;
	 edgeIcons = CB_EDGE_ICONS;
	 nrNodes = XtNumber(CB_NODE_NAMES);
	 nrEdges = XtNumber(CB_EDGE_NAMES);
}
 
void CBWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;
	diagramCBActorItems = new MenuItem[10]; i=0;
	diagramCBActorItems[i] = MenuItem(
		"to Actor Box", MenuItem::PUSHBUTTON, 'B', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::UCD_SINGLE_CLASS_BOX, 0, 1); i++;
	diagramCBActorItems[i] = MenuItem(
		"to StickMan", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::STICKMAN, 0, 1); i++;
	diagramCBActorItems[i] = MenuItem::NUL;
 
	diagramCBClassStereotypeItems = new MenuItem[10]; i=0;
	diagramCBClassStereotypeItems[i] = MenuItem(
		"Show Stereotype", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		CBStubs::ShowStereotypeCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramCBClassStereotypeItems[i] = MenuItem(
		"Hide Stereotype", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		CBStubs::HideStereotypeCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramCBClassStereotypeItems[i] = MenuItem::NUL;

	diagramCBClassPropertiesItems = new MenuItem[10]; i=0;
	diagramCBClassPropertiesItems[i] = MenuItem(
		"Show Properties", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		CBStubs::ShowPropertiesCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramCBClassPropertiesItems[i] = MenuItem(
		"Hide Properties", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		CBStubs::HidePropertiesCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	diagramCBClassPropertiesItems[i] = MenuItem::NUL;

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
		0, 0, 0, diagramCBActorItems, 1); j++;

	editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, 'h', 0, 0, 
		0, 0, 0, diagramCBClassStereotypeItems, 1); j++;
	editItems[j] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, 'a', 0, 0, 
		0, 0, 0, diagramCBClassPropertiesItems, 1); j++;
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
		0, 0, 0, diagramCBActorItems, 1); k++;
	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramCBClassStereotypeItems, 1); k++;
	popupEditItems[k] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, diagramCBClassPropertiesItems, 1); k++;
	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Read Direction", MenuItem::SUBMENU, '\0', 0, 0, 
		0, 0, 0, ERReadDirectionItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;
}
