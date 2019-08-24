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
#include "atwindow.h"
#include "atdiagram.h"
#include "atviewer.h"
#include "atgraph.h"
#include "menu.h"
#include "diagramstubs.h"

// X bitmap data for the tiled buttons
#include "MiniDiamond.xbm"
#include "NoteBox.xbm"
#include "SolidHorizontalBar.xbm"
#include "SolidVerticalBar.xbm"
#include "BlackDot.xbm"
#include "BullsEye.xbm"
#include "RoundedBox.xbm"
#include "EllipsedBox.xbm"
#include "Comment.xbm"
#include "Arrow.xbm"
#include "DottedLine.xbm"
 
const char *ATWindow::AT_NODE_NAMES[] =  
	{"Action state", 
	 "Decision", 
	 "Horizontal synchronization bar",
	 "Start state",
	 "Comment",
	 "Inactive state", 
	 "Note",
	 "Vertical synchronization bar",
	 "End state"};

const Bitmap ATWindow::AT_NODE_ICONS [] =
	{{EllipsedBox_width, EllipsedBox_height, EllipsedBox_bits},
	 {MiniDiamond_width, MiniDiamond_height, MiniDiamond_bits},
	 {SolidHorizontalBar_width, SolidHorizontalBar_height,
          SolidHorizontalBar_bits},
	 {BlackDot_width, BlackDot_height, BlackDot_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {RoundedBox_width, RoundedBox_height, RoundedBox_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {SolidVerticalBar_width, SolidVerticalBar_height,
          SolidVerticalBar_bits},
	 {BullsEye_width, BullsEye_height, BullsEye_bits}};
 
const char *ATWindow::AT_EDGE_NAMES[] = 
	{"Control flow",
	 "Note connector"};
const Bitmap ATWindow::AT_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits},
	 {DottedLine_width, DottedLine_height, DottedLine_bits}};

ATWindow::ATWindow(const char *n): DiagramWindow(n) {}

DiagramViewer *ATWindow::CreateViewer(Config *cfg) {
	return new ATViewer(cfg, this);
}

Graph *ATWindow::CreateGraph() {
	return new ATGraph();
}

Diagram *ATWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new ATDiagram(c, this, (ATViewer *)v, (ATGraph *)g);
}

void ATWindow::DetermineIcons() {
	 nodeNames = AT_NODE_NAMES;
	 nodeIcons = AT_NODE_ICONS;
	 edgeNames = AT_EDGE_NAMES;
	 edgeIcons = AT_EDGE_ICONS;
	 nrNodes = XtNumber(AT_NODE_NAMES);
	 nrEdges = XtNumber(AT_EDGE_NAMES);
}

void ATWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
	int i = 0;
	updateNodeShapeTypeItems = new MenuItem[10]; i=0;
	updateNodeShapeTypeItems[i] = MenuItem(
		"to Horizontal Synchronization Bars", 
		MenuItem::PUSHBUTTON, 'H', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SOLID_HORIZONTAL_BAR, 0, 1); i++;
	updateNodeShapeTypeItems[i] = MenuItem(
		"to Vertical Synchronization Bars", 
		MenuItem::PUSHBUTTON, 'V', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::SOLID_VERTICAL_BAR, 0, 1); i++;
	updateNodeShapeTypeItems[i] = MenuItem::NUL;
 
	int j = 0;
	while (editItems[j++].label != 0)
		;
	editItems[--j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Update Node Shape Type", MenuItem::SUBMENU, 'N', 0, 0, 
		0, 0, 0, updateNodeShapeTypeItems, 1); j++;
	editItems[j] = MenuItem::NUL;

	int k = 0;
	while (popupEditItems[k++].label != 0)
		;
	popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Update Node Shape Type", MenuItem::SUBMENU, 'N', 0, 0, 
		0, 0, 0, updateNodeShapeTypeItems, 1); k++;
	popupEditItems[k] = MenuItem::NUL;
}
