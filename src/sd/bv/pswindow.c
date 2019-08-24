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
#include "pswindow.h"
#include "psdiagram.h"
#include "psviewer.h"
#include "psstubs.h"
#include "psgraph.h"
#include "menu.h"
#include <Xm/XmAll.h>
// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "EmptyLine.xbm"
#include "Comment.xbm"
 
const char *PSWindow::PS_NODE_NAMES[] = {"Process", "Comment"};
const Bitmap PSWindow::PS_NODE_ICONS[] =
	{{Box_width, Box_height, Box_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char *PSWindow::PS_EDGE_NAMES[] = {"Empty edge"};
const Bitmap PSWindow::PS_EDGE_ICONS [] =
	 {{EmptyLine_width, EmptyLine_height, EmptyLine_bits}};
 
PSWindow::PSWindow(const char *n): DiagramWindow(n) { 
	diagramPSShowSequenceItems = 0;
}

PSWindow::~PSWindow(){ 
	if (diagramPSShowSequenceItems)
		delete diagramPSShowSequenceItems;
}

DiagramViewer *PSWindow::CreateViewer(Config *cfg) {
	return new PSViewer(cfg, this);
}

Graph *PSWindow::CreateGraph() {
	return new PSGraph();
}

Diagram *PSWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new PSDiagram(c, this, (PSViewer *)v, (PSGraph *)g);
}

void PSWindow::DetermineIcons() {
	 nodeNames = PS_NODE_NAMES;
	 nodeIcons = PS_NODE_ICONS;
	 edgeNames = PS_EDGE_NAMES;
	 edgeIcons = PS_EDGE_ICONS;
	 nrNodes = XtNumber(PS_NODE_NAMES);
	 nrEdges = XtNumber(PS_EDGE_NAMES);
}

//Widget PSWindow::CreateMenuBar(Widget parent) {
//	Widget bar = DiagramWindow::CreateMenuBar(parent);
//	// make the duplicate item insensitive.
//	Widget w1 = editMenu->GetMenuItem("Duplicate");
//	if (w1)
//		XtVaSetValues(w1, XmNsensitive, False, NULL);
//	return bar;
//}

void PSWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
	int i=0;
	diagramPSShowSequenceItems = new MenuItem[10]; i=0;
	diagramPSShowSequenceItems[i] = MenuItem(
		"Show no sequence labels", MenuItem::PUSHBUTTON, 'n', 0, 0, 
		PSStubs::ShowSequenceCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)0, 0, 1); i++;
	diagramPSShowSequenceItems[i] = MenuItem(
		"Update action sequences", MenuItem::PUSHBUTTON, 'a', 0, 0, 
		PSStubs::ShowSequenceCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)1, 0, 1); i++;
	diagramPSShowSequenceItems[i] = MenuItem(
		"Update process sequences", MenuItem::PUSHBUTTON, 'p', 0, 0, 
		PSStubs::ShowSequenceCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)2, 0, 1); i++;
	diagramPSShowSequenceItems[i] = MenuItem();

	delete viewItems;
	viewItems = new MenuItem[25]; i=0;
	viewItems[i] = MenuItem(
		"Refresh", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>V", "Ctrl+V", 
		PSStubs::RefreshCB, (XtPointer)GetDiagramViewer(), 
		0, 0, 1); i++;
	viewItems[i] = MenuItem(
		"Grid", MenuItem::SUBMENU, 'G', 0, 0, 
		0, 0, 0, gridItems, 1); i++;
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Autoresizing", MenuItem::CHECKBUTTON, 'A', 0, 0, 
		PSStubs::SetAutoResizeCB, (XtPointer)GetDocument(), 
		(XtPointer)1, 0, 1); i++;
	viewItems[i] = MenuItem(
		"In-line Editor", MenuItem::CHECKBUTTON, 'E', 0, 0, 
		PSStubs::SetInlineEditCB, (XtPointer)GetDocument(), 
		(XtPointer)1, 0, 1); i++;
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Update Sequence Labels", MenuItem::SUBMENU, 'O', 0, 0, 
		0, 0, 0, diagramPSShowSequenceItems, 1); i++;
	viewItems[i] = MenuItem();
}
