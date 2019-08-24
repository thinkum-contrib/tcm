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
#include "dfwindow.h"
#include "dfdiagram.h"
#include "dfviewer.h"
#include "dfstubs.h"
#include "dfgraph.h"
#include "menu.h"
#include "mstring.h"
#include "liteclue.h"
#include <Xm/XmAll.h>
// X bitmap data for the tiled buttons
#include "Arrow.xbm"
#include "HorizontalBar.xbm"
#include "TopLabeledCircle.xbm"
#include "DoubleArrow.xbm"
#include "Comment.xbm"
#include "Square.xbm"
#include "BlackDot.xbm"
 
const char *DFWindow::DF_NODE_NAMES[] =  
	{"Data process", "Data store", "External entity", 
	 "Split/merge node", "Comment"};
const Bitmap DFWindow::DF_NODE_ICONS [] =
	{{TopLabeledCircle_width, TopLabeledCircle_height, TopLabeledCircle_bits},
	{HorizontalBar_width, HorizontalBar_height, HorizontalBar_bits},
	{Square_width, Square_height, Square_bits},
	{BlackDot_width, BlackDot_height, BlackDot_bits},
	{Comment_width, Comment_height, Comment_bits}};
 
const char *DFWindow::DF_EDGE_NAMES[] =  
	{"Data flow", "Bidirectional data flow"};
const Bitmap DFWindow::DF_EDGE_ICONS [] =
	{{Arrow_width, Arrow_height, Arrow_bits},
	 {DoubleArrow_width, DoubleArrow_height, 
	  DoubleArrow_bits}};

DFWindow::DFWindow(const char *n): DiagramWindow(n) {
	dfDiagram = 0;
	dfdItems = 0;
}

DFWindow::~DFWindow() {
	if (dfdItems)
		delete dfdItems;
}

DiagramViewer *DFWindow::CreateViewer(Config *cfg) {
	return new DFViewer(cfg, this);
}

Graph *DFWindow::CreateGraph() {
	return new DFGraph();
}

Diagram *DFWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	return new DFDiagram(c, this, (DFViewer *)v, (DFGraph *)g);
}

void DFWindow::DetermineIcons() {
	nodeNames = DF_NODE_NAMES;
	nodeIcons = DF_NODE_ICONS;
	edgeNames = DF_EDGE_NAMES;
	edgeIcons = DF_EDGE_ICONS;
	nrNodes = XtNumber(DF_NODE_NAMES);
	nrEdges = XtNumber(DF_EDGE_NAMES);
}

void DFWindow::SetDiagram(const char *s) {
	if (dfDiagram)
		XtVaSetValues(dfDiagram, XmNvalue, s, 0); 
}
 
void DFWindow::SetDiagram(const string *s) {
	SetDiagram(s->getstr());
}

Widget DFWindow::CreateMenuBar(Widget parent) {
	Widget bar = DiagramWindow::CreateMenuBar(parent);
	dfdMenu = new Menu(bar, Menu::PULLDOWN, "DFD", 0, dfdItems);
	XtManageChild(bar);
	return bar;
}

Widget DFWindow::CreateTiles(Widget parent) {
	DetermineIcons();
	Widget t = XtVaCreateWidget("Tiles",
		xmRowColumnWidgetClass, parent,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetDocumentArea(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNorientation, XmVERTICAL, 0);
	Widget t1 = XtVaCreateWidget("tiles1", xmRowColumnWidgetClass, t, 0);
	Widget t2 = XtVaCreateWidget("tiles2", xmRowColumnWidgetClass, t, 0);
	CreateNodeIcons(t1);
	CreateEdgeIcons(t1);
	CreateDiagramField(t2);
	CreateIndexToggle(GetNodeIconsRC());
	XtManageChild(t1);
	XtManageChild(t2);
	XtManageChild(t);
	return t;
}

void DFWindow::CreateDiagramField(Widget parent) {
	Widget frame = XtVaCreateManagedWidget("tiles_frame3",
		xmFrameWidgetClass, parent,
		XmNshadowType, XmSHADOW_ETCHED_IN, 0);
	Widget rc = XtVaCreateWidget("rc3", xmRowColumnWidgetClass, frame,
			XmNentryAlignment, XmALIGNMENT_CENTER, 0);
	XtVaCreateManagedWidget("Diagram", xmLabelWidgetClass, rc, 0);
	dfDiagram = XtVaCreateManagedWidget("DFDiagram",
			xmTextFieldWidgetClass, rc,
			XmNcolumns, 5,
			XmNeditable, True,
			XmNcursorPositionVisible, True, 0);
	XtAddCallback(dfDiagram, XmNactivateCallback, 
	 		DFStubs::ChangeDiagramCB, (XtPointer)GetDocument());
	AddLiteClue(dfDiagram, "Set diagram index (apply with <return>)");
	SetDiagram("");
	XtManageChild(rc);
}

void DFWindow::InitMenuItems() {
	DiagramWindow::InitMenuItems();
	int i=0;
	dfdItems = new MenuItem[25]; i=0;
	dfdItems[i] = MenuItem(
		"Minispec...", MenuItem::PUSHBUTTON, 'M', 0, 0,
		DFStubs::MinispecCB, (XtPointer)GetDiagramViewer(), 0, 0, 1); i++;
	dfdItems[i] = MenuItem::NUL;
}
