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
#include "erwindow.h"
#include "erdiagram.h"
#include "erviewer.h"
#include "ergraph.h"
#include "erstubs.h"
#include "config.h"
#include "menu.h"
#include <Xm/XmAll.h>
 
// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "C1Arrow.xbm"
#include "C2Line.xbm"
#include "Dot.xbm"
#include "Diamond.xbm"
#include "Ellipse.xbm"
#include "EmptyLine.xbm"
#include "IsaArrow.xbm"
#include "Comment.xbm"
#include "DoubleArrow.xbm"
 
const char *ERWindow::ER_NODE_NAMES[] =
	{"Entity type", "Value type","Taxonomy junction", "Relationship", 
	 "Comment"};
const Bitmap ERWindow::ER_NODE_ICONS [] =
	{{Box_width, Box_height, Box_bits},
	 {Ellipse_width, Ellipse_height, Ellipse_bits},
	 {Dot_width, Dot_height, Dot_bits},
	 {Diamond_width, Diamond_height, Diamond_bits},
	 {Comment_width, Comment_height, Comment_bits}};
 
const char *ERWindow::ER_EDGE_NAMES[] = 
	{"Binary relationship", "Function","Is-a relationship", 
	 "Empty edge", "One-one function"};
const Bitmap ERWindow::ER_EDGE_ICONS [] =
	{{C2Line_width, C2Line_height, C2Line_bits},
	 {C1Arrow_width, C1Arrow_height, C1Arrow_bits},
	 {IsaArrow_width, IsaArrow_height, IsaArrow_bits},
	 {EmptyLine_width, EmptyLine_height, EmptyLine_bits},
	 {DoubleArrow_width, DoubleArrow_height, DoubleArrow_bits}};

ERWindow::ERWindow(const char *n): DiagramWindow(n) { 
        ERReadDirectionItems = 0;
}

ERWindow::~ERWindow() {
	if (ERReadDirectionItems)
                delete ERReadDirectionItems;
}

DiagramViewer *ERWindow::CreateViewer(Config *cfg) {
	return new ERViewer(cfg, this);
}

Graph *ERWindow::CreateGraph() {
	return new ERGraph();
}

Diagram *ERWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new ERDiagram(c, this, (ERViewer *)v, (ERGraph *)g);
}

void ERWindow::DetermineIcons() {
	 nodeNames = ER_NODE_NAMES;
	 nodeIcons = ER_NODE_ICONS;
	 edgeNames = ER_EDGE_NAMES;
	 edgeIcons = ER_EDGE_ICONS;
	 nrNodes = XtNumber(ER_NODE_NAMES);
	 nrEdges = XtNumber(ER_EDGE_NAMES);
}

void ERWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
	int i=0;
	delete viewItems;
	viewItems = new MenuItem[25]; i=0;
	viewItems[i] = MenuItem(
		"Refresh", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>V", "Ctrl+V", 
		ERStubs::RefreshCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); i++;
	viewItems[i] = MenuItem(
		"Grid", MenuItem::SUBMENU, 'G', 0, 0,
		0, 0, 0, gridItems, 1); i++;
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Zoom In", MenuItem::PUSHBUTTON, 'I', "Ctrl<Key>I", "Ctrl+I",
		DiagramStubs::ZoomInCB, (XtPointer)GetDiagramViewer(), 0, 0, 0); i++;
	viewItems[i] = MenuItem(
		"Zoom Out", MenuItem::PUSHBUTTON, 'O', "Ctrl<Key>O", "Ctrl+O",
		DiagramStubs::ZoomOutCB, (XtPointer)GetDiagramViewer(), 0, 0, 0); i++;
	viewItems[i] = MenuItem(
		"Top Level", MenuItem::PUSHBUTTON, 'T', "Ctrl<Key>T", "Ctrl+T",
		DiagramStubs::TopLevelCB, (XtPointer)GetDiagramViewer(), 0, 0, 0); i++;
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Autoresizing", MenuItem::CHECKBUTTON, 'A', 0, 0, 
		ERStubs::SetAutoResizeCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)(GetConfig()->GetAutoResizing()), 0, 1); i++;
	viewItems[i] = MenuItem(
		"In-line Editor", MenuItem::CHECKBUTTON, 'E', 0, 0, 
		ERStubs::SetInlineEditCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)(GetConfig()->GetInlineEditor()), 0, 1); i++;
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Show ISA hierarchy", MenuItem::CHECKBUTTON, 'I', 0, 0, 
		ERStubs::ShowISACB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)0, 0, 1); i++;
	viewItems[i] = MenuItem(
		"Hide Value types", MenuItem::CHECKBUTTON, 'V', 0, 0, 
		ERStubs::HideValueTypesCB, (XtPointer)GetDiagramViewer(), 
		(XtPointer)0, 0, 1); i++;
	viewItems[i] = MenuItem();

	ERReadDirectionItems = new MenuItem[10]; i=0;
        ERReadDirectionItems[i] = MenuItem(
                "ToShape", MenuItem::PUSHBUTTON, 'T', 0, 0,
                ERStubs::UpdateReadDirectionCB,
                (XtPointer)GetDiagramViewer(),
                0, 0, 1); i++;
        ERReadDirectionItems[i] = MenuItem(
                "None", MenuItem::PUSHBUTTON, 'N', 0, 0,
                ERStubs::UpdateReadDirectionCB,
                (XtPointer)GetDiagramViewer(),
                0, 0, 1); i++;
        ERReadDirectionItems[i] = MenuItem(
                "FromShape", MenuItem::PUSHBUTTON, 'F', 0, 0,
                ERStubs::UpdateReadDirectionCB,
                (XtPointer)GetDiagramViewer(),
                0, 0, 1); i++;
        ERReadDirectionItems[i] = MenuItem::NUL;
}
