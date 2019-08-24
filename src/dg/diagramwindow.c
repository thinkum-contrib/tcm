////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "diagramwindow.h"
#include "assoclist.h"
#include "textalign.h"
#include "printer.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "diagramstubs.h"
#include "xgrafport.h"
#include "liteclue.h"
#include "graph.h"
#include "menu.h"
#include "config.h"
#include "mstring.h"
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <Xm/XmAll.h>
#include "Curve.xbm"
#include "LineStyleSolid.xbm"
#include "LineStyleDashed.xbm"
#include "LineStyleDotted.xbm"
const Bitmap DiagramWindow::CURVE_ICON = 
	{Curve_width, Curve_height, Curve_bits};
const Bitmap DiagramWindow::SOLID_LINE_ICON = 
	{LineStyleSolid_width, LineStyleSolid_height, LineStyleSolid_bits};
const Bitmap DiagramWindow::DASHED_LINE_ICON = 
	{LineStyleDashed_width, LineStyleDashed_height, LineStyleDashed_bits};
const Bitmap DiagramWindow::DOTTED_LINE_ICON = 
	{LineStyleDotted_width, LineStyleDotted_height, LineStyleDotted_bits};

DiagramWindow::DiagramWindow(const char *n): DrawWindow(n) {
	nodeLineStyleItems = 0;
	edgeLineStyleItems = 0;
	showLineStyleOptionMenu = False;
	diagramAlignItems = 0;
	defPropertiesItems = 0;
	gridItems = 0;
	updateNodeShapeTypeItems = 0;
	iconColumns = 2;
}

DiagramWindow::~DiagramWindow() {
	if (defPropertiesItems)
		delete defPropertiesItems;
	if (diagramAlignItems)
		delete diagramAlignItems;
	if (gridItems)
		delete gridItems;
	if (nodeLineStyleItems)
		delete nodeLineStyleItems;
	if (edgeLineStyleItems)
		delete edgeLineStyleItems;
	if (updateNodeShapeTypeItems)
		delete updateNodeShapeTypeItems;
}

void DiagramWindow::WriteUsage(const char *prog) {
	DrawWindow::WriteUsage(prog);
}

void DiagramWindow::ParseUserOptions(int argc, char **argv) {
	DrawWindow::ParseUserOptions(argc, argv);
	if (GetArgsLeft() == 1) {
		// for loading existing file or opening a new file
		const char* file = argv[argc-1];
		if (file[0] != '-') {
			SetDoLoad(True);
			SetLoadFile(file);
		}
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	else if (GetArgsLeft() != 0) {
		WriteUsage(argv[0]);
		exit(1);
	}
}

void DiagramWindow::CreateDocument() {
	// create new diagram, viewer and graph object (tool specific)
	DetermineIcons();
	Graph *graph = CreateGraph();
	viewer = CreateViewer(GetConfig());
	Diagram *d = CreateDiagram(GetConfig(), viewer, graph);
	viewer->SetDiagram(d);
	SetDocument(d);
	graph->InitConnections();
}

void DiagramWindow::Finalize() {
	CreateDrawingArea();
	viewer->SetPrinter(GetPrinter());
	GetPrinter()->SetViewer(viewer);
	GetDrawingArea()->SetViewer(viewer);	
	viewer->SetGrafport(GetDrawingArea()->GetGrafport());
	GetDocument()->Initialize();
	viewer->Redraw();
	DrawWindow::Finalize();
}

void DiagramWindow::CreateComponents(Widget parent) {
	if (!check(parent))
		return;
	SetLogo(CreateLogo(parent));
	SetArrowButtons(CreateArrowButtonSquare(parent));
	SetMenuBar(CreateMenuBar(parent));
	SetDocumentArea(CreateDocumentArea(parent));
	tiles = CreateTiles(parent);
	SetControlArea(CreateControlArea(parent));
	SetStatusArea(CreateStatusArea(parent));
	SetScrolledWindow(CreateScrolledWindow(parent));
	SetScaleValue(CreateScaleValue(parent));
	XtVaSetValues(GetStatusArea(),
		XmNleftAttachment, XmATTACH_OPPOSITE_WIDGET,
		XmNleftWidget, GetScrolledWindow(), NULL);
	XtVaSetValues(GetScrolledWindow(),
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, tiles,
		XmNbottomAttachment, XmATTACH_WIDGET,
		XmNbottomWidget, GetArrowButtons(), NULL);
	// XtVaSetValues(tiles,
	// 	XmNbottomAttachment, XmATTACH_WIDGET,
	// 	XmNbottomWidget, GetArrowButtons(), NULL);
}

Widget DiagramWindow::CreateTiles(Widget parent) {
	// the tile widget is a rowcolumn consisting of two
	// rowcolumns of radio-buttons (which are to be labeled
	// with drawn buttons): one for nodes and one for edges 
	// (the last including a toggle for curved or straight edges)
	Widget t = XtVaCreateWidget("Tiles",
		xmRowColumnWidgetClass, parent,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetDocumentArea(),
		XmNleftAttachment, XmATTACH_FORM,
		XmNadjustLast, True,
		NULL);
	CalcIconColumns();
	CreateNodeIcons(t);
	CreateEdgeIcons(t);
	XtManageChild(t);
	if (ShowIndexToggle())
		CreateIndexToggle(GetNodeIconsRC());
	if (showLineStyleOptionMenu) {
		CreateLineStyleOptionMenu(nodeIconsRC, True, iconColumns>2);
		XtManageChild(nodeIconsRC);
		CreateLineStyleOptionMenu(edgeIconsRC, False, iconColumns>2);
		XtManageChild(edgeIconsRC);
	}
	XtManageChild(t);
	return t;
}


void DiagramWindow::CalcIconColumns() {
	int icons = nrNodes + nrEdges;
	if (showLineStyleOptionMenu)
		icons += 4;
	if (ShowIndexToggle())
		icons += 2;
	if ((GetScreenType() <= VGA) || 
	    (GetScreenType() <= SVGA && icons > 7) ||
	    (GetScreenType() <= XVGA && icons > 10) || 
	    (icons >= 13))
		iconColumns = 2;
        if ((GetScreenType() > XVGA && icons < 7))
		iconColumns = 1;
	if (icons >= 20 || (GetScreenType() <= XVGA && icons > 18) ||
		(GetScreenType() <= SVGA && icons > 15))
		iconColumns = 3;
}

void DiagramWindow::CreateNodeIcons(Widget t) {
	Arg args[9];
	int i = 0;
	Widget pb;
	Widget scrolledWin = 0;
	Pixmap pixmap;
	// create a frame: for nodes
	Widget frame = XtVaCreateWidget("TilesFrame1",
		xmFrameWidgetClass, t,
		XmNshadowType, XmSHADOW_ETCHED_IN, NULL);

	// create a rowcolumn for nodes
	nodeIconsRC = XtVaCreateWidget("NodeIconsRC", xmRowColumnWidgetClass, 
		frame, XmNentryAlignment, 
		XmALIGNMENT_CENTER, NULL);

	// make scrollbars when there are many icons.
	if (iconColumns > 2) {
		scrolledWin = XtVaCreateManagedWidget("ScrolledWindow",
                	xmScrolledWindowWidgetClass, nodeIconsRC,
			XmNborderWidth, 0,
			XmNshadowThickness, 0,
			XmNspacing, 0,
                	XmNwidth, iconColumns*68, 
                	XmNheight, 
				GetIconsScrollHeight((nrNodes-1)/iconColumns + 1),
                	XmNscrollingPolicy, XmAUTOMATIC,
                	XmNscrollBarDisplayPolicy, XmAS_NEEDED, NULL);

		Widget clipWindow;
		XtVaGetValues(scrolledWin, XmNclipWindow, &clipWindow, NULL);
		XtVaSetValues(clipWindow, XmNborderWidth, NULL, NULL);
	}

        XtVaCreateManagedWidget("nodes",
                        xmLabelWidgetClass, frame,
                        XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	XtSetArg(args[i], XmNradioAlwaysOne, True); i++;
	XtSetArg(args[i], XmNnumColumns, iconColumns); i++;
        XtSetArg(args[i], XmNadjustLast, False); i++;

	// create a radiobox for the nodes
	char wname[8] = "Nodes";
	Widget rb = XmCreateRadioBox(
			scrolledWin?scrolledWin:nodeIconsRC, 
			wname, args, i);
	// create all node buttons and their pixmaps in a loop
	for (i=0; i < nrNodes; i++) {
		pb = XtVaCreateWidget(nodeNames[i],
			xmToggleButtonWidgetClass, rb,
			   // the first button is set by default
			XmNset, i == 0? True: False, 
			XmNhighlightThickness, 0,
			XmNalignment, XmALIGNMENT_CENTER, NULL);
		pixmap = nodeIcons[i].CreatePixmap(pb, GetDisplay());
		XtVaSetValues(pb,
			XmNlabelType, XmPIXMAP,
			XmNlabelPixmap, pixmap, 
			XmNuserData, (XtPointer)(i+1),
					// determines widget for which the
					// callback is involved.
			NULL);
		XtAddCallback(pb, XmNvalueChangedCallback, 
			DiagramStubs::SetNodeCB, (XtPointer)GetDocument());
		AddLiteClue(pb, (char *)nodeNames[i]);
		XtManageChild(pb);
	}
	XtManageChild(rb);
	XtManageChild(nodeIconsRC);
	if (scrolledWin)
		XtManageChild(scrolledWin);
	XtManageChild(frame);
}

void DiagramWindow::CreateEdgeIcons(Widget t) {
	Arg args[9];
	int i = 0;
	Widget pb;
	Pixmap pixmap;
	// create a frame: for edges
	Widget frame = XtVaCreateWidget("TilesFrame2",
		xmFrameWidgetClass, t,
		XmNshadowType, XmSHADOW_ETCHED_IN, NULL);
	// create a rowcolumn of edges
	edgeIconsRC = XtVaCreateWidget("EdgeIconsRC", xmRowColumnWidgetClass, 
		frame, XmNentryAlignment, XmALIGNMENT_CENTER,
		NULL);
	// create a label for edges
        XtVaCreateManagedWidget("edges",
                        xmLabelWidgetClass, frame,
                        XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	
	XtSetArg(args[i], XmNradioAlwaysOne, True); i++;
	XtSetArg(args[i], XmNnumColumns, iconColumns); i++;
	XtSetArg(args[i], XmNadjustLast, False); i++;

	// create a radiobox for the edges
	char wname[8] = "Edges";
	Widget rb = XmCreateRadioBox(edgeIconsRC, wname, args, i);
	// realize them in a loop ...
	for (i=0; i < nrEdges; i++) {
		pb = XtVaCreateWidget(edgeNames[i],
			xmToggleButtonWidgetClass, rb,
			XmNset, i == 0? True: False,
			XmNhighlightThickness, 0,
			XmNalignment, XmALIGNMENT_CENTER, NULL);
		pixmap = edgeIcons[i].CreatePixmap(pb, GetDisplay());
		XtVaSetValues(pb,
			XmNlabelType, XmPIXMAP,
			XmNlabelPixmap, pixmap, 
			XmNuserData, (XtPointer)(i+1),
			NULL);
		XtAddCallback(pb, XmNvalueChangedCallback, 
			DiagramStubs::SetEdgeCB, (XtPointer)GetDocument());
		AddLiteClue(pb, (char *)edgeNames[i]);
		XtManageChild(pb);
	}
	XtManageChild(rb);
	if (!Toolkit::EditorWithoutCurves(GetTool())) {
		i=0;
		strcpy(wname, "rb3");
		rb = XmCreateSimpleCheckBox(edgeIconsRC, wname, args, i);
		// create a button for the curve toggle
		pb = XtVaCreateWidget("create curve", xmToggleButtonWidgetClass, rb,
			XmNhighlightThickness, 0,
			XmNalignment, XmALIGNMENT_CENTER, NULL);
		XtAddCallback(pb, XmNvalueChangedCallback, 
			DiagramStubs::SetCurveCB, (XtPointer)GetDocument());
		AddLiteClue(pb, "When on, curved edges are created");
		XtManageChild(pb);
		XtManageChild(rb);
	}
	XtManageChild(edgeIconsRC);
	XtManageChild(frame);
}


void DiagramWindow::CreateLineStyleOptionMenu(Widget w, bool nodes, 
						bool minimize) {
	Widget frame1 = XtVaCreateManagedWidget("LineStyleFrame",
                        xmFrameWidgetClass, w, NULL);
	Menu *menu;
	string label;

	if (nodes) {
		if (minimize) {
			menu = new Menu(frame1, Menu::OPTION, 
					"line style", 0, nodeLineStyleItems);
		}
		else {
			menu = new Menu(frame1, Menu::OPTION, 
					"NodeLineStyleMenu", 0, nodeLineStyleItems);
			label = "line style";
			XtVaCreateManagedWidget(label.getstr(),
				xmLabelWidgetClass, frame1,
				XmNchildType, XmFRAME_TITLE_CHILD, NULL);
		}
	}
	else {	// edges
		if (minimize) {
			menu = new Menu(frame1, Menu::OPTION, 
					"line style", 0, edgeLineStyleItems);
		}
		else {
			menu = new Menu(frame1, Menu::OPTION, 
					"EdgeLineStyleMenu", 0, edgeLineStyleItems);
			label = "line style";
			XtVaCreateManagedWidget(label.getstr(),
				xmLabelWidgetClass, frame1,
				XmNchildType, XmFRAME_TITLE_CHILD, NULL);
		}
	}
	XtManageChild(menu->GetWidget());
	XtManageChild(w);
}

Widget DiagramWindow::CreateMenuBar(Widget parent) {
	// create the main menubar at the top of the parent
	Arg  args[9];
	int i = 0;
	XtSetArg(args[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(args[i], XmNleftAttachment, XmATTACH_FORM); i++;
	if (GetLogo()) {
		XtSetArg(args[i], XmNrightAttachment, XmATTACH_WIDGET); i++;
		XtSetArg(args[i], XmNrightWidget, GetLogo()); i++;
	}
	else {
		XtSetArg(args[i], XmNrightAttachment, XmATTACH_FORM); i++;
	}
	InitMenuItems();
	// create a menubar that contains the following menus:
	char wname[10] = "MenuBar";
	Widget bar = XmCreateMenuBar(parent, wname, args, i);
	fileMenu = new Menu(bar, Menu::PULLDOWN, "File", 0, fileItems);
	editMenu = new Menu(bar, Menu::PULLDOWN, "Edit", 0, editItems);
	viewMenu = BuildViewMenu(bar);
	printMenu = new Menu(bar, Menu::PULLDOWN, "Print", 0, printItems);
	scaleMenu = new Menu(bar, Menu::PULLDOWN, "Scale", 0, scaleItems);
	pageMenu = new Menu(bar, Menu::PULLDOWN, "Page", 0, pageItems);
	propertiesMenu = new Menu(bar, Menu::PULLDOWN, "Properties", 0, 
		propertiesItems);
	searchMenu = new Menu(bar, Menu::PULLDOWN, "Search", 0, searchItems);
	documentMenu = new Menu(bar, Menu::PULLDOWN, "Document", 0, 
		documentItems);
	helpMenu = new Menu(bar, Menu::PULLDOWN, "Help", 0, helpItems);
	// tell bar which bar which button is the help menu
	XtVaSetValues(bar, XmNmenuHelpWidget, helpMenu->GetWidget(), NULL);
	// Bar is done -- manage it
	XtManageChild(bar);
	return bar;
}

Menu *DiagramWindow::BuildViewMenu(Widget parent) {
	return new Menu(parent, Menu::PULLDOWN, "View", 0, viewItems);
}

void DiagramWindow::GetNodeName(int i, string *n) {
	if (i >= 0 && i < nrNodes)
		*n = nodeNames[i];
	else
		*n = "";
}

void DiagramWindow::GetEdgeName(int i, string *n) {
	if (i >= 0 && i < nrEdges)
		*n = edgeNames[i];
	else
		*n = "";
}

void DiagramWindow::SetNodeName(int n) {
	string status; 
	GetNodeName(n-1, &status);
	status += ": on";
	SetStatus(&status);
}

void DiagramWindow::SetEdgeName(int n) {
	string status;
	GetEdgeName(n-1, &status);
	status += ": on";
	SetStatus(&status);
}

void DiagramWindow::InitMenuItems() {
	int i;
	DrawWindow::InitMenuItems();

	diagramAlignItems = new MenuItem[10]; i=0;
	diagramAlignItems[i] = MenuItem(
		 "Align Top", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 
		(XtPointer)NodeAlign::TOP, 0, 1); i++;
	diagramAlignItems[i] = MenuItem(
		 "Align Bottom", MenuItem::PUSHBUTTON, 'B', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 
		(XtPointer)NodeAlign::BOTTOM, 0, 1); i++;
	diagramAlignItems[i] = MenuItem(
		 "Align Left", MenuItem::PUSHBUTTON, 'L', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 
		(XtPointer)NodeAlign::LEFT, 0, 1); i++;
	diagramAlignItems[i] = MenuItem(
		 "Align Right", MenuItem::PUSHBUTTON, 'R', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 
		(XtPointer)NodeAlign::RIGHT, 0, 1); i++;
	diagramAlignItems[i] = MenuItem(
		 "Align Horizontal", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 
		(XtPointer)NodeAlign::HORIZONTAL, 0, 1); i++;
	diagramAlignItems[i] = MenuItem(
		 "Align Vertical", MenuItem::PUSHBUTTON, 'V', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer,
		(XtPointer)NodeAlign::VERTICAL, 0, 1); i++;
	diagramAlignItems[i] = MenuItem::NUL;
	
	popupEditItems = new MenuItem[28]; i=0;
	popupEditItems[i] = MenuItem(
		 "Edit Commands", MenuItem::LABEL, 0, 0, 0, 
		0, 0, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	popupEditItems[i] = MenuItem(
		"Undo", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>U", "Ctrl+U", 
		DiagramStubs::UndoCB, (XtPointer)viewer, 
		(XtPointer)1, 0, 0); i++;
	popupEditItems[i] = MenuItem(
		"Redo", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>R", "Ctrl+R", 
		DiagramStubs::RedoCB, (XtPointer)viewer, 
		(XtPointer)1, 0, 0); i++;
	popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	popupEditItems[i] = MenuItem(
		 "Cut", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>X", "Ctrl+X",
		DiagramStubs::CutCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem(
		 "Copy", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>C", "Ctrl+C",
		DiagramStubs::CopyCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem(
		 "Paste", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>Y", "Ctrl+Y",
		DiagramStubs::PasteCB, (XtPointer)viewer, 0, 0, 1); i++;
	if ( ! Toolkit::EditorWithoutDuplicates(GetTool()) ) {
		popupEditItems[i] = MenuItem(
			"Duplicate", MenuItem::PUSHBUTTON, '\0', 0, 0, 
			DiagramStubs::DuplicateCB, (XtPointer)viewer, 0, 0, 1);
			i++;
	}
	popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	popupEditItems[i] = MenuItem(
		 "Delete", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>D", "Ctrl+D", 
		DiagramStubs::DeleteCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem(
		 "Delete All", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		DiagramStubs::DeleteAllCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	popupEditItems[i] = MenuItem(
		 "Select All", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		DiagramStubs::SelectAllCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem(
		 "Same Size", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		DiagramStubs::SameSizeCB, (XtPointer)viewer, 0, 0, 1); i++;
	popupEditItems[i] = MenuItem(
		 "Align Nodes...", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 0, 0, 1); i++;
	if (ShowIndexToggle()) {
		popupEditItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
		popupEditItems[i] = MenuItem(
		 "Renumber Indexes", MenuItem::PUSHBUTTON, '\0', 0, 0,
		 DiagramStubs::ReindexCB, 
		(XtPointer)GetDocument(), 0, 0, 1); i++;
	}
	if (!Toolkit::EditorWithoutCurves(GetTool())) {
		popupEditItems[i] = MenuItem(
		 	"Convert From/To Curves", MenuItem::PUSHBUTTON, '\0', 0, 0,
			DiagramStubs::UpdateCurveCB, (XtPointer)viewer, 0, 0, 1); i++;
	}
	popupEditItems[i] = MenuItem::NUL;

	editItems = new MenuItem[28]; i=0;
	editItems[i] = MenuItem(
		"Undo", MenuItem::PUSHBUTTON, 'U', "Ctrl<Key>U", "Ctrl+U", 
		DiagramStubs::UndoCB, (XtPointer)viewer, 
		(XtPointer)0, 0, 0); i++;
	editItems[i] = MenuItem(
		"Redo", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>R", "Ctrl+R", 
		DiagramStubs::RedoCB, (XtPointer)viewer, 
		(XtPointer)0, 0, 0); i++;
	editItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	editItems[i] = MenuItem(
		"Cut", MenuItem::PUSHBUTTON, 'C', "Ctrl<Key>X", "Ctrl+X", 
		DiagramStubs::CutCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		"Copy", MenuItem::PUSHBUTTON, 'o', "Ctrl<Key>C", "Ctrl+C", 
		DiagramStubs::CopyCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		 "Paste", MenuItem::PUSHBUTTON, 'P', "Ctrl<Key>Y", "Ctrl+Y", 
		DiagramStubs::PasteCB, (XtPointer)viewer, 0, 0, 1); i++;
	if ( ! Toolkit::EditorWithoutDuplicates(GetTool()) ) {
		editItems[i] = MenuItem(
			"Duplicate", MenuItem::PUSHBUTTON, 'l', 0, 0,
			DiagramStubs::DuplicateCB, (XtPointer)viewer, 0, 0, 1);
		i++;
	}
	editItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	editItems[i] = MenuItem(
		 "Delete", MenuItem::PUSHBUTTON, 'D', "Ctrl<Key>D", "Ctrl+D", 
		DiagramStubs::DeleteCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		 "Delete All", MenuItem::PUSHBUTTON, 'e', 0, 0, 
		DiagramStubs::DeleteAllCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	editItems[i] = MenuItem(
		 "Select All", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::SelectAllCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		 "Same Size", MenuItem::PUSHBUTTON, 'm', 0, 0, 
		DiagramStubs::SameSizeCB, (XtPointer)viewer, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		 "Align Nodes...", MenuItem::PUSHBUTTON, 'A', 0, 0,
		DiagramStubs::AlignNodeShapesCB, (XtPointer)viewer, 0, 0, 1); i++;
	if (ShowIndexToggle()) {
		editItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
		editItems[i] = MenuItem("Renumber Indexes", 
		MenuItem::PUSHBUTTON, 'i', 0, 0, DiagramStubs::ReindexCB, 
		(XtPointer)GetDocument(), 0, 0, 1); i++;
	}
	if (!Toolkit::EditorWithoutCurves(GetTool())) {
		editItems[i] = MenuItem(
		 	"Convert From/To Curves", MenuItem::PUSHBUTTON, 'o', 0, 0,
			DiagramStubs::UpdateCurveCB, (XtPointer)viewer, 0, 0, 1); i++;
	}
	editItems[i] = MenuItem::NUL;

	gridItems = new MenuItem[10]; i=0;
	gridItems[i] = MenuItem(
		"Show Grid", MenuItem::CHECKBUTTON, 'S', 0, 0, 
		DiagramStubs::ShowGridCB, (XtPointer)viewer->GetGrid(), 
		(XtPointer)(GetConfig()->GetShowGrid()), 0, 1); i++;
	gridItems[i] = MenuItem(
		"Grid Size ...", MenuItem::PUSHBUTTON, 'G', 0, 0, 
		DiagramStubs::GridSizeCB, 
		(XtPointer)viewer->GetGrid(), 0, 0, 1); i++;
	gridItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	gridItems[i] = MenuItem(
		"Point Snapping", MenuItem::CHECKBUTTON, 'P', 0, 0, 
		DiagramStubs::PointSnappingCB, (XtPointer)viewer->GetGrid(), 
		(XtPointer)(GetConfig()->GetPointSnapping()), 0, 1); i++;
	gridItems[i] = MenuItem(
		"Point Distance ...", MenuItem::PUSHBUTTON, 'D', 0, 0, 
		DiagramStubs::PointDistanceCB, 
		(XtPointer)viewer->GetGrid(), 0, 0, 1); i++;
	gridItems[i] = MenuItem::NUL;

	viewItems = new MenuItem[28]; i=0;
	viewItems[i] = MenuItem(
		"Refresh", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>V", "Ctrl+V", 
		DiagramStubs::RefreshCB, (XtPointer)viewer, 0, 0, 1); i++;
	viewItems[i] = MenuItem(
		 "Grid", MenuItem::SUBMENU, 'G', 0, 0, 0, 
		0, 0, gridItems, 1); i++;
	if (Toolkit::HierarchicEditor(GetTool())) {
		/* These commands are insensitive by now. When they are
		   eventually made sensitive, ensure that they become
		   insensitive for non-hierarchic documents again. */
		viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
		viewItems[i] = MenuItem(
			"Zoom In", MenuItem::PUSHBUTTON, 'I', 
			"Ctrl<Key>I", "Ctrl+I", 
			DiagramStubs::ZoomInCB, 
			(XtPointer)viewer, 0, 0, 0); i++;
		viewItems[i] = MenuItem(
			"Zoom Out", MenuItem::PUSHBUTTON, 'O', 
			"Ctrl<Key>O", "Ctrl+O", 
			DiagramStubs::ZoomOutCB, (XtPointer)viewer, 
			0, 0, 0); i++;
		viewItems[i] = MenuItem(
			"Top Level", MenuItem::PUSHBUTTON, 'T', 
			"Ctrl<Key>T", "Ctrl+T", 
			DiagramStubs::TopLevelCB, 
			(XtPointer)viewer, 0, 0, 0); i++;
	}
	viewItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	viewItems[i] = MenuItem(
		"Autoresizing", MenuItem::CHECKBUTTON, 'A', 0, 0, 
		DiagramStubs::SetAutoResizeCB, (XtPointer)viewer, 
		(XtPointer)(GetConfig()->GetAutoResizing()), 0, 1); i++;
	viewItems[i] = MenuItem(
		"In-line Editor", MenuItem::CHECKBUTTON, 'I', 0, 0, 
		DiagramStubs::SetInlineEditCB, (XtPointer)viewer, 
		(XtPointer)(GetConfig()->GetInlineEditor()), 0, 1); i++;
	viewItems[i] = MenuItem::NUL;

	defPropertiesItems = new MenuItem[25]; i=0;
	defPropertiesItems[i] = MenuItem(
		"Default Line Width...", MenuItem::PUSHBUTTON, 'W', 0, 0, 
		DiagramStubs::DefaultLineWidthCB, (XtPointer)viewer,
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem(
		"Default Text Font...", MenuItem::PUSHBUTTON, 'F', 0, 0, 
		DiagramStubs::DefaultFontCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem(
		"Default Text Alignment...", MenuItem::PUSHBUTTON, 'A', 0, 0, 
		DiagramStubs::DefaultTextAlignmentCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	defPropertiesItems[i] = MenuItem(
		"Default Line Color...", MenuItem::PUSHBUTTON, 'L', 0, 0, 
		DiagramStubs::DefaultLineColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem(
		"Default Text Color...", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		DiagramStubs::DefaultTextColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem(
		"Default Fill Color...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		DiagramStubs::DefaultFillColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	defPropertiesItems[i] = MenuItem::NUL;

	propertiesItems = new MenuItem[25]; i=0;
	if (Toolkit::GenericEditor(GetTool())) {
		propertiesItems[i] = MenuItem(
		"Update Line Style...", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		DiagramStubs::UpdateLineStyleCB, (XtPointer)viewer,
		0, 0, 1); i++;
	}
	propertiesItems[i] = MenuItem(
		"Update Line Width...", MenuItem::PUSHBUTTON, 'W', 0, 0, 
		DiagramStubs::UpdateLineWidthCB, (XtPointer)viewer,
		0, 0, 1); i++;
	if (Toolkit::GenericEditor(GetTool())) {
		propertiesItems[i] = MenuItem(
		"Update Line Ends...", MenuItem::PUSHBUTTON, 'E', 0, 0, 
		DiagramStubs::UpdateLineEndCB, (XtPointer)viewer,
		0, 0, 1); i++;
	}
	propertiesItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	propertiesItems[i] = MenuItem(
		"Update Text Font...", MenuItem::PUSHBUTTON, 'F', 0, 0, 
		DiagramStubs::UpdateFontCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem(
		"Update Text Alignment...", MenuItem::PUSHBUTTON, 'A', 0, 0, 
		DiagramStubs::UpdateTextAlignmentCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem(
		"Set/Unset Text Underlining", MenuItem::PUSHBUTTON, 'U', 0, 0, 
		DiagramStubs::UpdateTextUnderlineCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	propertiesItems[i] = MenuItem(
		"Update Line Color...", MenuItem::PUSHBUTTON, 'L', 0, 0, 
		DiagramStubs::UpdateLineColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem(
		"Update Text Color...", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		DiagramStubs::UpdateTextColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem(
		"Update Fill Color...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		DiagramStubs::UpdateFillColorCB, (XtPointer)viewer, 
		0, 0, 1); i++;
	propertiesItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	propertiesItems[i] = MenuItem(
		"Default Properties", MenuItem::SUBMENU, 'D', 0, 0, 
		0, 0, 0, defPropertiesItems, 1); i++;
	propertiesItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	propertiesItems[i] = MenuItem(
		"Node/Edge Annotation ...", MenuItem::PUSHBUTTON, 'N', 0,0,
		DiagramStubs::AnnotateCB, (XtPointer)viewer, 0, 0, 1); i++;
	propertiesItems[i] = MenuItem::NUL;

	nodeLineStyleItems = new MenuItem[25]; i=0;
	nodeLineStyleItems[i] = MenuItem(
		"Solid", &SOLID_LINE_ICON, MenuItem::RADIOBUTTON, 'S', 0, 0,
		DiagramStubs::DefaultNodeLineStyleCB, (XtPointer)viewer,
		(XtPointer)1, 0, 1); i++;
	nodeLineStyleItems[i] = MenuItem(
		"Dashed", &DASHED_LINE_ICON, MenuItem::RADIOBUTTON, 'D', 0, 0,
		DiagramStubs::DefaultNodeLineStyleCB, (XtPointer)viewer,
		(XtPointer)2, 0, 1); i++;
	nodeLineStyleItems[i] = MenuItem(
		"Dotted", &DOTTED_LINE_ICON, MenuItem::RADIOBUTTON, 'o', 0, 0,
		DiagramStubs::DefaultNodeLineStyleCB, (XtPointer)viewer,
		(XtPointer)4, 0, 1); i++;

	edgeLineStyleItems = new MenuItem[25]; i=0;
	edgeLineStyleItems[i] = MenuItem(
		"Solid", &SOLID_LINE_ICON, MenuItem::RADIOBUTTON, 'S', 0, 0,
		DiagramStubs::DefaultEdgeLineStyleCB, (XtPointer)viewer,
		(XtPointer)1, 0, 1); i++;
	edgeLineStyleItems[i] = MenuItem(
		"Dashed", &DASHED_LINE_ICON, MenuItem::RADIOBUTTON, 'D', 0, 0,
		DiagramStubs::DefaultEdgeLineStyleCB, (XtPointer)viewer,
		(XtPointer)2, 0, 1); i++;
	edgeLineStyleItems[i] = MenuItem(
		"Dotted", &DOTTED_LINE_ICON, MenuItem::RADIOBUTTON, 'o', 0, 0,
		DiagramStubs::DefaultEdgeLineStyleCB, (XtPointer)viewer,
		(XtPointer)4, 0, 1); i++;
}

void DiagramWindow::CreateIndexToggle(Widget parent) {
	char wname[10] = "Indexes";
	Widget rb = XmCreateSimpleCheckBox(parent, wname, 0, 0);
	Widget pb = XtVaCreateWidget("create/edit index", 
					xmToggleButtonWidgetClass, rb,
		XmNhighlightThickness, 0,
		XmNset, viewer->IsShowIndexes(),
		XmNalignment, XmALIGNMENT_CENTER, NULL);
	XtAddCallback(pb, XmNvalueChangedCallback,
			DiagramStubs::ShowIndexesCB, (XtPointer)viewer);
	AddLiteClue(pb, "When on, new nodes get an index");
	XtManageChild(pb);
	XtManageChild(rb);
}

int DiagramWindow::GetIconsScrollHeight(int rows) {
	ScreenType st = GetScreenType();
	int sr = rows;
	if (st == EGA)
		sr = 3;
	else if (st == VGA)
		sr = 3;
	else if (st == SVGA)
		sr = 4;
	else if (st == XVGA)
		sr = 5;
	else if (st == NCD19B)
		sr = 6;
	else if (st == SUN17)
		sr = 8;
	else if (st == NCD16)
		sr = 9;
	else if (st == HP19)
		sr = 9;
	return min(rows, sr)*40;
}


/* virtual */ void DiagramWindow::SetHierarchic(bool s) {
	DrawWindow::SetHierarchic(s);
	Widget w1 = editMenu->GetMenuItem("Duplicate");
	if ( w1 )
		XtVaSetValues(w1, XmNsensitive, ! s, NULL);
	GetDrawingArea()->Enable("Duplicate", ! s);
}
