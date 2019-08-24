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
#include "gdwindow.h"
#include "gddiagram.h"
#include "gdviewer.h"
#include "gdgraph.h"
#include "menu.h"
#include "diagramstubs.h"

// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "Square.xbm"
#include "Circle.xbm"
#include "StickMan.xbm"
#include "Ellipse.xbm"
#include "Triangle.xbm"
#include "Diamond.xbm"
#include "NoteBox.xbm"
#include "Hexagon.xbm"
#include "HorizontalBar.xbm"
#include "VerticalBar.xbm"
#include "SolidHorizontalBar.xbm"
#include "SolidVerticalBar.xbm"
#include "BlackDot.xbm"
#include "BullsEye.xbm"
#include "RoundedBox.xbm"
#include "EllipsedBox.xbm"
#include "Comment.xbm"
#include "BuildingBlock.xbm"
#include "Folder.xbm"
#include "SubFolder.xbm"
#include "Cube.xbm"
#include "Disk.xbm"
#include "Line.xbm"
#include "Arrow.xbm"
#include "OpenArrow.xbm"
#include "DoubleArrow.xbm"
#include "DoubleHeadedArrow.xbm"
#include "EmptyOpenArrow.xbm"

#include "GDBoundaryShape.xbm"
#include "GDControllerShape.xbm"
#include "GDEntityShape.xbm"
 
const char *GDWindow::GD_NODE_NAMES[] =  
	{"Box", 
	 "Circle", 
	 "Rounded box", 
	 "Triangle", 
	 "Bull's eye",
	 "Stick man",
	 "Cube",
	 "Boundary class",
	 "Text",
	 "Diamond", 
	 "Square",
	 "Vertical bar",
	 "Hexagon", 
	 "Solid vertical bar", 
	 "Folder",
	 "Building block",
	 "Controller class",
	 "Note box",
	 "Ellipse", 
	 "Black dot",
	 "Horizontal bar", 
	 "Ellipsed box", 
	 "Solid horizontal bar",
	 "SubFolder",
	 "Disk",
	 "Entity class"};

const Bitmap GDWindow::GD_NODE_ICONS [] =
	{{Box_width, Box_height, Box_bits},
	 {Circle_width, Circle_height, Circle_bits},
	 {RoundedBox_width, RoundedBox_height, RoundedBox_bits},
	 {Triangle_width, Triangle_height, Triangle_bits},
	 {BullsEye_width, BullsEye_height, BullsEye_bits},
	 {StickMan_width, StickMan_height, StickMan_bits},
	 {Cube_width, Cube_height, Cube_bits},
	 {GDBoundaryShape_width, GDBoundaryShape_height, GDBoundaryShape_bits},
	 {Comment_width, Comment_height, Comment_bits},
	 {Diamond_width, Diamond_height, Diamond_bits},
	 {Square_width, Square_height, Square_bits},
	 {VerticalBar_width, VerticalBar_height, VerticalBar_bits},
	 {Hexagon_width, Hexagon_height, Hexagon_bits},
	 {SolidVerticalBar_width, SolidVerticalBar_height,
          SolidVerticalBar_bits},
	 {Folder_width, Folder_height, Folder_bits},
	 {BuildingBlock_width, BuildingBlock_height, BuildingBlock_bits},
	 {GDControllerShape_width, GDControllerShape_height, GDControllerShape_bits},
	 {NoteBox_width, NoteBox_height, NoteBox_bits},
	 {Ellipse_width, Ellipse_height, Ellipse_bits},
	 {BlackDot_width, BlackDot_height, BlackDot_bits},
	 {HorizontalBar_width, HorizontalBar_height, HorizontalBar_bits},
	 {EllipsedBox_width, EllipsedBox_height, EllipsedBox_bits},
	 {SolidHorizontalBar_width, SolidHorizontalBar_height,
          SolidHorizontalBar_bits},
	 {SubFolder_width, SubFolder_height, SubFolder_bits},
	 {Disk_width, Disk_height, Disk_bits},
	 {GDEntityShape_width, GDEntityShape_height, GDEntityShape_bits}};
 
const char *GDWindow::GD_EDGE_NAMES[] = 
	{"Line", 
	 "Double arrow", 
	 "Arrow",
	 "Empty open arrow", 
	 "Double headed arrow",
	 "Open arrow"};
const Bitmap GDWindow::GD_EDGE_ICONS [] =
	{{Line_width, Line_height, Line_bits},
	 {DoubleArrow_width, DoubleArrow_height, DoubleArrow_bits},
	 {Arrow_width, Arrow_height, Arrow_bits},
	 {EmptyOpenArrow_width, EmptyOpenArrow_height, EmptyOpenArrow_bits},
	{DoubleHeadedArrow_width, DoubleHeadedArrow_height, 
	  DoubleHeadedArrow_bits},
	 {OpenArrow_width, OpenArrow_height, OpenArrow_bits}};


GDWindow::GDWindow(const char *n): DiagramWindow(n) {
	SetShowLineStyleOptionMenu(True);
}

DiagramViewer *GDWindow::CreateViewer(Config *cfg) {
	return new GDViewer(cfg, this);
}

Graph *GDWindow::CreateGraph() {
	return new GDGraph();
}

Diagram *GDWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new GDDiagram(c, this, (GDViewer *)v, (GDGraph *)g);
}

void GDWindow::DetermineIcons() {
	 nodeNames = GD_NODE_NAMES;
	 nodeIcons = GD_NODE_ICONS;
	 edgeNames = GD_EDGE_NAMES;
	 edgeIcons = GD_EDGE_ICONS;
	 nrNodes = XtNumber(GD_NODE_NAMES);
	 nrEdges = XtNumber(GD_EDGE_NAMES);
}

void GDWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
 
	int j = 0;
	while (editItems[j++].label != 0)
		;
	editItems[--j] = MenuItem("", MenuItem::SEPARATOR); j++;
	editItems[j] = MenuItem(
		"Convert Node Shape Type...", MenuItem::PUSHBUTTON, 'N', 0, 0, 
		DiagramStubs::ConvertNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 0, 0, 1); j++;
	editItems[j] = MenuItem::NUL;

	int k = 0;
	while (popupEditItems[k++].label != 0)
		;
	popupEditItems[--k] = MenuItem("", MenuItem::SEPARATOR); k++;
	popupEditItems[k] = MenuItem(
		"Convert Node Shape Type...", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		DiagramStubs::ConvertNodeShapeTypeCB, 
		(XtPointer)GetDiagramViewer(), 0, 0, 1); k++;
	popupEditItems[k] = MenuItem::NUL;
}
