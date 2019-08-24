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
#include "sqdiagram.h"
#include "sqviewer.h"
#include "sqgraph.h"
#include "sqstubs.h"
#include "sqwindow.h"
#include "menu.h"
#include "diagramstubs.h"

// X bitmap data for the tiled buttons
#include "Arrow.xbm"
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
#include "FOCBox.xbm"

const char *SQWindow::SQ_NODE_NAMES[] =
	{"LifeLine (StickMan)",
	 "Note",
	 "LifeLine (ObjectBox)",
	 "Comment"};
const Bitmap SQWindow::SQ_NODE_ICONS[] =
	{{StickMan_width, StickMan_height, StickMan_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {ObjectBox_width, ObjectBox_height, ObjectBox_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char* SQWindow::SQ_EDGE_NAMES[] =
	{"AnchorPoint link",
	 "Note connector",
	 "Focus Of Control Box"};

const Bitmap SQWindow::SQ_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits},
	 {FOCBox_width, FOCBox_height, FOCBox_bits}};

SQWindow::SQWindow(const char *n) : ERWindow(n) {
	diagramSQActorItems = 0;
	diagramSQClassStereotypeItems = 0;
	diagramSQClassPropertiesItems = 0;
}

SQWindow::~SQWindow() {
	if (diagramSQActorItems) {
		delete diagramSQActorItems;
		delete diagramSQClassStereotypeItems;
		delete diagramSQClassPropertiesItems;
	}
}

DiagramViewer *SQWindow::CreateViewer(Config *cfg) {
	return new SQViewer(cfg, this);
}

Graph *SQWindow::CreateGraph() {
	return new SQGraph();
}

Diagram *SQWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new SQDiagram(c, this, (SQViewer *)v, (SQGraph *)g);
}

void SQWindow::DetermineIcons() {
	 nodeNames = SQ_NODE_NAMES;
	 nodeIcons = SQ_NODE_ICONS;
	 edgeNames = SQ_EDGE_NAMES;
	 edgeIcons = SQ_EDGE_ICONS;
	 nrNodes = XtNumber(SQ_NODE_NAMES);
	 nrEdges = XtNumber(SQ_EDGE_NAMES);
}

void SQWindow::InitMenuItems() {
	ERWindow::InitMenuItems();
	int i = 0;

	diagramSQActorItems = new MenuItem[10]; i=0;
	diagramSQActorItems[i] = MenuItem(
		"to Actor Box", MenuItem::PUSHBUTTON, 'B', 0, 0,
		DiagramStubs::UpdateNodeShapeTypeCB,
		(XtPointer)GetDiagramViewer(),
		(XtPointer)Code::UCD_SINGLE_CLASS_BOX, 0, 1); i++;
	diagramSQActorItems[i] = MenuItem(
		"to StickMan", MenuItem::PUSHBUTTON, 'S', 0, 0,
		DiagramStubs::UpdateNodeShapeTypeCB,
		(XtPointer)GetDiagramViewer(),
		(XtPointer)Code::STICKMAN, 0, 1); i++;
	diagramSQActorItems[i] = MenuItem::NUL;

	diagramSQClassStereotypeItems = new MenuItem[10]; i=0;
	diagramSQClassStereotypeItems[i] = MenuItem(
		"Show Stereotype", MenuItem::PUSHBUTTON, 'S', 0, 0,
		SQStubs::ShowStereotypeCB, (XtPointer)GetDiagramViewer(),
		0, 0, 1); i++;
	diagramSQClassStereotypeItems[i] = MenuItem(
		"Hide Stereotype", MenuItem::PUSHBUTTON, 'H', 0, 0,
		SQStubs::HideStereotypeCB, (XtPointer)GetDiagramViewer(),
		0, 0, 1); i++;
	diagramSQClassStereotypeItems[i] = MenuItem::NUL;

	diagramSQClassPropertiesItems = new MenuItem[10]; i=0;
	diagramSQClassPropertiesItems[i] = MenuItem(
		"Show Properties", MenuItem::PUSHBUTTON, 'S', 0, 0,
		SQStubs::ShowPropertiesCB, (XtPointer)GetDiagramViewer(),
		0, 0, 1); i++;
	diagramSQClassPropertiesItems[i] = MenuItem(
		"Hide Properties", MenuItem::PUSHBUTTON, 'H', 0, 0,
		SQStubs::HidePropertiesCB, (XtPointer)GetDiagramViewer(),
		0, 0, 1); i++;
	diagramSQClassPropertiesItems[i] = MenuItem::NUL;

	// delete last menu item: hide value types.
	int n = 0;
	while (viewItems[n++].label != 0)
		;
	viewItems[n-2] = MenuItem::NUL;

	int j = 0;
	while (editItems[j++].label != 0)
		;
std::cout << " j===================" << j << std::endl << std::flush;
	editItems[--j] = MenuItem("", MenuItem::SEPARATOR); j++;

	/*editItems[j] = MenuItem(
		"Add Focus Of Control", MenuItem::PUSHBUTTON, 'F', 0, 0,
		SQStubs::AddFOCCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); j++;*/
	/*editItems[j] = MenuItem(
		"Delete Focus Of Control", MenuItem::PUSHBUTTON, 'G', 0, 0,
		SQStubs::DeleteFOCCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); j++;*/

	//editItems[j] = MenuItem::NUL;		// TMP



	//editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;

/*	editItems[j] = MenuItem(
		"Change Actor Type", MenuItem::SUBMENU, 'C', 0, 0,
		0, 0, 0, diagramSQActorItems, 1); j++;
	editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;*/
	editItems[j] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, 'h', 0, 0,
		0, 0, 0, diagramSQClassStereotypeItems, 1); j++;
	editItems[j] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, 'a', 0, 0,
		0, 0, 0, diagramSQClassPropertiesItems, 1); j++;
	editItems[j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Change Read Direction", MenuItem::SUBMENU, 'R', 0, 0,
		0, 0, 0, ERReadDirectionItems, 1); j++;
	editItems[j] = MenuItem::NUL;

//std::cout << " j===================" << j << std::endl << std::flush;
	int k = 0;
	 while (popupEditItems[k++].label != 0)
		;
	popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;



/*	popupEditItems[k] = MenuItem(
		"Add Focus Of Control", MenuItem::PUSHBUTTON, 'F', 0, 0,
		SQStubs::AddFOCCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); k++;*/


	popupEditItems[k] = MenuItem(
		"Delete Focus Of Control", MenuItem::PUSHBUTTON, 'G', 0, 0,
		SQStubs::DeleteFOCCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); k++;
	//popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;

/*
	popupEditItems[k] = MenuItem(
		"Change Actor Type", MenuItem::SUBMENU, '\0', 0, 0,
		0, 0, 0, diagramSQActorItems, 1); k++;

*/

	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Change Stereotype", MenuItem::SUBMENU, '\0', 0, 0,
		0, 0, 0, diagramSQClassStereotypeItems, 1); k++;

	popupEditItems[k] = MenuItem(
		"Change Properties", MenuItem::SUBMENU, '\0', 0, 0,
		0, 0, 0, diagramSQClassPropertiesItems, 1); k++;
	popupEditItems[k] = MenuItem("", MenuItem::SEPARATOR); k++;
//popupEditItems[k] = MenuItem::NUL;

	popupEditItems[k] = MenuItem(
		"Change Read Direction", MenuItem::SUBMENU, '\0', 0, 0,
		0, 0, 0, ERReadDirectionItems, 1); k++;
//	popupEditItems[k] = MenuItem::NUL;
}
