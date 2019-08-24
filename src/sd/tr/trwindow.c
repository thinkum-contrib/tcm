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
#include "trwindow.h"
#include "trdiagram.h"
#include "trviewer.h"
#include "trgraph.h"
#include "menu.h"
#include "mstring.h"
#include "liteclue.h"
#include <Xm/XmAll.h>

#include "TextNode.xbm"
#include "TextRoot.xbm"
#include "Comment.xbm"
#include "Line.xbm"
 
const char *TRWindow::TR_NODE_NAMES[] =  { "Text root", "Text node", "Comment"};

const Bitmap TRWindow::TR_NODE_ICONS [] = { 
	{TextRoot_width, TextRoot_height, TextRoot_bits},
	{TextNode_width, TextNode_height, TextNode_bits},
	{Comment_width, Comment_height, Comment_bits}};
 
const char *TRWindow::TR_EDGE_NAMES[] = {"Line"};
const Bitmap TRWindow::TR_EDGE_ICONS [] = {
	{Line_width, Line_height, Line_bits}};

TRWindow::TRWindow(const char *n): DiagramWindow(n) {}

DiagramViewer *TRWindow::CreateViewer(Config *cfg) {
	return new TRViewer(cfg, this);
}

Graph *TRWindow::CreateGraph() {
	return new TRGraph();
}

Diagram *TRWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new TRDiagram(c, this, (TRViewer *)v, (TRGraph *)g);
}

void TRWindow::DetermineIcons() {
	 nodeNames = TR_NODE_NAMES;
	 nodeIcons = TR_NODE_ICONS;
	 edgeNames = TR_EDGE_NAMES;
	 edgeIcons = TR_EDGE_ICONS;
	 nrNodes = XtNumber(TR_NODE_NAMES);
	 nrEdges = XtNumber(TR_EDGE_NAMES);
}

Widget TRWindow::CreateMenuBar(Widget parent) {
	Widget bar = DiagramWindow::CreateMenuBar(parent);
	// make the duplicate item insensitive.
	Widget w1 = editMenu->GetMenuItem("Duplicate");
	if (w1)
		XtVaSetValues(w1, XmNsensitive, False, NULL);
	return bar;
}

Widget TRWindow::CreateTiles(Widget parent) {
	Widget t = DiagramWindow::CreateTiles(parent);
	(void)CreateLayoutTiles(t);
	XtManageChild(t);
	return t;
}

Widget TRWindow::CreateLayoutTiles(Widget parent) {
	Arg args[9];
	int i = 0;
	// create a frame
	Widget frame = XtVaCreateManagedWidget("layout_tiles_frame1",
		xmFrameWidgetClass, parent,
		XmNshadowType, XmSHADOW_ETCHED_IN, NULL);
	// create the label
	XtVaCreateManagedWidget("Layout",
                        xmLabelWidgetClass, frame,
                        XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	// create a rowcolumn
	Widget rc = XtVaCreateWidget("rc1", xmRowColumnWidgetClass, frame,
		XmNentryAlignment, XmALIGNMENT_CENTER, NULL);
	// create a radiobox for the tiles
	XtSetArg(args[i], XmNradioAlwaysOne, True); i++;
	char wname[8] = "Layout";
	Widget rb = XmCreateRadioBox(rc, wname, args, i);
	// create all layout tiles
	XmString lb1, lb2;
	lb1 = CreateXmString("Editable\nGraph");
	lb2 = CreateXmString("Forked\nTree");
	editButton = XtVaCreateManagedWidget("EditableGraph",
			xmToggleButtonWidgetClass, rb,
			XmNset, True,
			XmNhighlightThickness, 0,
			XmNlabelType, XmSTRING,
			XmNlabelString, lb1,
			XmNuserData, (XtPointer)0,
			XmNalignment, XmALIGNMENT_CENTER, NULL);
	XtAddCallback(editButton, XmNvalueChangedCallback,
			TRWindow::LayoutCB, (XtPointer)this);
	AddLiteClue(editButton, "Edit mode in which document is drawn as a graph");
	treeButton = XtVaCreateManagedWidget("ForkedTree",
			xmToggleButtonWidgetClass, rb,
			XmNset, False,
			XmNlabelString, lb2,
			XmNlabelType, XmSTRING,
			XmNhighlightThickness, 0,
			XmNuserData, (XtPointer)1,
			XmNalignment, XmALIGNMENT_CENTER, NULL);
	XtAddCallback(treeButton, XmNvalueChangedCallback,
			TRWindow::LayoutCB, (XtPointer)this);
	AddLiteClue(treeButton, "View mode in which document has a forked tree layout");
	XtManageChild(rb);
	XtManageChild(rc);
	XmStringFree(lb1);
	XmStringFree(lb2);
	return frame;
}

void TRWindow::SetLayout(bool b) {
	TRViewer *v = (TRViewer *)GetDiagramViewer();
	if (!v->IsPasting() && !v->IsZigZag()) {
		SetStatus("action: set layout");
		v->UpdateTreeMode(b);
	}
	else if (b != v->IsTreeMode()) {
		SetStatus("I'm busy with something else");
		XmToggleButtonSetState(editButton, b, False);
		XmToggleButtonSetState(treeButton, !b, False);
	}
	SetSensitive(editMenu, "Cut", !b);
	SetSensitive(editMenu, "Copy", !b);
	SetSensitive(editMenu, "Paste", !b);
	SetSensitive(editMenu, "Delete", !b);
	SetSensitive(editMenu, "Delete All", !b);
	SetSensitive(editMenu, "Select All", !b);
	SetSensitive(editMenu, "Same Size", !b);
	SetSensitive(editMenu, "Align Nodes", !b);
	GetDrawingArea()->Enable("Cut", !b);
	GetDrawingArea()->Enable("Copy", !b);
	GetDrawingArea()->Enable("Paste", !b);
	GetDrawingArea()->Enable("Delete", !b);
	GetDrawingArea()->Enable("Delete All", !b);
	GetDrawingArea()->Enable("Select All", !b);
	GetDrawingArea()->Enable("Same Size", !b);
	GetDrawingArea()->Enable("Align Nodes", !b);
	SetSensitive(fileMenu, "Append", !b);
	SetSensitive(fileMenu, "Save Selection As", !b);
	SetSensitive(searchMenu, "Replace", !b);
	SetSensitive(propertiesMenu, "Node/Edge Annotation", !b);
	SetSensitive(propertiesMenu, "Update Text Font", !b);
	SetSensitive(propertiesMenu, "Update Line Width", !b);
	SetSensitive(propertiesMenu, "Update Line Style", !b);
	SetSensitive(propertiesMenu, "Update Line Ends", !b);
	SetSensitive(propertiesMenu, "Set/Unset Text Underlining", !b);
	SetSensitive(propertiesMenu, "Update Text Alignment", !b);
	SetSensitive(propertiesMenu, "Update Line Color", !b);
	SetSensitive(propertiesMenu, "Update Text Color", !b);
	SetSensitive(propertiesMenu, "Update Fill Color", !b);
}

void TRWindow::SetSensitive(Menu *menu, const char *label, bool b) {
	Widget w = menu->GetMenuItem(label);
	if (w)
		XtVaSetValues(w, XmNsensitive, b, NULL);
}

void TRWindow::LayoutCB(Widget w, XtPointer cd, XtPointer) {
	if (XmToggleButtonGetState(w)) {
		int num;
		XtVaGetValues(w, XmNuserData, &num, NULL);
		((TRWindow *)cd)->SetLayout(num);
	}
}

