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
#include "rpwindow.h"
#include "rpdiagram.h"
#include "rpviewer.h"
#include "rpgraph.h"
#include "menu.h"
#include "diagramstubs.h"

// X bitmap data for the tiled buttons
#include "Dot.xbm"
#include "MiniArrowEllipse.xbm"
#include "Arrow.xbm"
#include "Comment.xbm"
#include "RoundedBox.xbm"
 
const char *RPWindow::RP_NODE_NAMES[] =
	{"Root node", "Unlabeled node", "Labeled Node", "Comment"};

const Bitmap RPWindow::RP_NODE_ICONS [] =
	{{MiniArrowEllipse_width, MiniArrowEllipse_height, MiniArrowEllipse_bits},
	 {Dot_width, Dot_height, Dot_bits},
	 {RoundedBox_width, RoundedBox_height, RoundedBox_bits},
	 {Comment_width, Comment_height, Comment_bits}};
 
const char *RPWindow::RP_EDGE_NAMES[] = {"Event"};
const Bitmap RPWindow::RP_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits}};

RPWindow::RPWindow(const char *n): DiagramWindow(n) {
}

DiagramViewer *RPWindow::CreateViewer(Config *cfg) {
	return new RPViewer(cfg, this);
}

Graph *RPWindow::CreateGraph() {
	return new RPGraph();
}

Diagram *RPWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new RPDiagram(c, this, (RPViewer *)v, (RPGraph *)g);
}

void RPWindow::DetermineIcons() {
	 nodeNames = RP_NODE_NAMES;
	 nodeIcons = RP_NODE_ICONS;
	 edgeNames = RP_EDGE_NAMES;
	 edgeIcons = RP_EDGE_ICONS;
	 nrNodes = XtNumber(RP_NODE_NAMES);
	 nrEdges = XtNumber(RP_EDGE_NAMES);
}

 
void RPWindow::InitMenuItems() {
        DiagramWindow::InitMenuItems();
        int i = 0;
        convertItems = new MenuItem[10]; i=0;
        convertItems[i] = MenuItem("to Labeled Nodes", 
		MenuItem::PUSHBUTTON, 'L', 0, 0, 
		DiagramStubs::UpdateNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 
		(XtPointer)Code::ROUNDED_BOX, 0, 1); i++;
        convertItems[i] = MenuItem("to Unlabeled Nodes", 
		MenuItem::PUSHBUTTON, 'U', 0, 0,
                DiagramStubs::UpdateNodeShapeTypeCB,
		(XtPointer)GetDiagramViewer(),
                (XtPointer)Code::MINI_ELLIPSE, 0, 1); i++;
	convertItems[i] = MenuItem::NUL;

	// add menu for converting node shapes.
	int j = 0;
        while (editItems[j++].label != 0)
                ;
        editItems[--j] = MenuItem("", MenuItem::SEPARATOR); j++;
        editItems[j] = MenuItem(
                "Change Node Shape Type", MenuItem::SUBMENU, 'C', 0, 0,
                0, 0, 0, convertItems, 1); j++;
        editItems[j] = MenuItem::NUL;
        int k = 0;
        while (popupEditItems[k++].label != 0)
                ;
        popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;
        popupEditItems[k] = MenuItem(
                "Change Node Shape Type", MenuItem::SUBMENU, 'C', 0, 0,
                0, 0, 0, convertItems, 1); k++;
        popupEditItems[k] = MenuItem::NUL;
}
