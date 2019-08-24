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
#include "tablewindow.h"
#include "tableviewer.h"
#include "table.h"
#include "tablestubs.h"
#include "drawingarea.h"
#include "printer.h"
#include "system.h"
#include "menu.h"
#include "config.h"
#include "xgrafport.h"
#include <stdlib.h>
#include <Xm/XmAll.h>

TableWindow::TableWindow(const char *n): DrawWindow(n) {
	table = 0;
	initRows = 0;
	initColumns = 0;
	initCellHeight = 0;
	initCellWidth = 0;
	defaultPropertiesItems=0;
}

TableWindow::~TableWindow() { 
	if (defaultPropertiesItems)
		delete defaultPropertiesItems;
}

void TableWindow::WriteUsage(const char *prog) {
	const char *OPTIONS =
	"-cell <w>x<h>\t\tDefault cell size is <w>x<h> pixels\n"
        "-drawing <w>x<h>\tCreate drawing area of <w>x<h> pixels\n"
        "-h[elp]\t\t\tShow this message and quit\n"
        "-maxdrawing <w>x<h>\tSet maximum drawing area size to <w>x<h> pixels\n"
        "-projdir <dir>\t\tSet the project directory to <dir>\n"
        "-priv_cmap\t\tStart the editor with a private colormap\n"
	"-table <n>x<m>\t\tInitial table has <n> rows and <m> columns\n"
	"-toPS [<file>.ps]\tGenerate PostScript (to <file>.ps or else stdout) "
	 	"and quit\n"
        "-toEPS [<file>.eps]\tGenerate EPS (to <file>.eps or else stdout) " 
		"and quit\n"
	"-toFig [<file>.fig] [-latex]\tGenerate Fig format (to <file>.fig "
                "or else stdout)\n\t\t\tand quit. "
                "When the -latex option is given LaTeX fonts are\n\t\t\t"
                "generated, otherwise normal PostScript fonts are generated\n"
	"-toPNG <file>.png\tGenerate PNG format to <file>.png and quit\n"
        "-v[ersion]\t\tShow the TCM version and quit\n"
        "remark: the -toXXX options require an existing TCM document file\n";
        std::cerr << "Usage: " << prog << " [options] [file]\nOptions:\n" <<
		OPTIONS << std::endl;
}

void TableWindow::ParseUserOptions(int argc, char **argv) {
	DrawWindow::ParseUserOptions(argc, argv);
	int n;
	// look for -table option to set initial number of rows and columns.
	if (System::FindArg(argv, argc, "-table", n)) {
		if (n < argc-1 && 
		    System::NxnParse(argv[n+1], initRows, initColumns)) {
			SetArgsLeft(GetArgsLeft() - 2);
		}
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	// look for -cell option to set initial size of cells.
	if (System::FindArg(argv, argc, "-cell", n)) {
		if (n < argc-1 && 
		    System::NxnParse(argv[n+1], initCellWidth, initCellHeight)){
			SetArgsLeft(GetArgsLeft() - 2);
		}
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	if (GetArgsLeft() == 1) {
		// for loading existing file or opening a new file
		const char* file = argv[argc-1];
                if (file[0] != '-') {
			SetDoLoad(True);
			SetLoadFile(argv[argc-1]);
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

TableViewer *TableWindow::CreateViewer() {
	return new TableViewer(GetConfig(), this);
}

Table *TableWindow::CreateTable() {
	return new Table(GetConfig(), this, viewer);
}

void TableWindow::CreateDocument() {
	// create table viewer object.
	viewer = CreateViewer();
	// create table object.
	table = CreateTable();
	SetDocument(table);
	viewer->SetTable(table);
}

void TableWindow::Finalize() {
	CreateDrawingArea();
	viewer->SetPrinter(GetPrinter());
	GetPrinter()->SetViewer(viewer);
	GetDrawingArea()->SetViewer(viewer);
	viewer->SetGrafport(GetDrawingArea()->GetGrafport());
	viewer->Redraw();
	DrawWindow::Finalize();
	if (initRows != 0)
		viewer->SetDefaultNumberOfRows(initRows);
	if (initColumns != 0)
		viewer->SetDefaultNumberOfColumns(initColumns);
	if (initCellHeight != 0)
		viewer->UpdateDefaultRowHeight(initCellHeight);
	if (initCellWidth != 0)
		viewer->UpdateDefaultColumnWidth(initCellWidth);
	if (!IsDoLoad() || !table->IsLoaded())
		table->Initialize();
}

void TableWindow::CreateComponents(Widget parent) {
	const int MAX_SCROLL_WIDTH = 810;
	const int MAX_SCROLL_HEIGHT = 580;
	if (!check(parent))
		return;
	SetLogo(CreateLogo(parent));
	SetArrowButtons(CreateArrowButtonSquare(parent));
	SetMenuBar(CreateMenuBar(parent));
	SetDocumentArea(CreateDocumentArea(parent));
	SetControlArea(CreateControlArea(parent));
	SetStatusArea(CreateStatusArea(parent));
	SetScrolledWindowWidth(
		min(GetScrolledWindowWidth(), MAX_SCROLL_WIDTH));
	SetScrolledWindowHeight(
		min(GetScrolledWindowHeight(), MAX_SCROLL_HEIGHT));
	SetScrolledWindow(CreateScrolledWindow(parent));
	SetScaleValue(CreateScaleValue(parent));
	XtVaSetValues(GetStatusArea(), XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftOffset, 20,
		XmNleftWidget, GetArrowButtons(), 0);
	XtVaSetValues(GetScrolledWindow(), XmNleftAttachment, XmATTACH_FORM,
		XmNleftOffset, 20,
		XmNbottomAttachment, XmATTACH_WIDGET,
		XmNbottomWidget, GetArrowButtons(), 0);
}

Widget TableWindow::CreateMenuBar(Widget parent) {
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
	viewMenu = new Menu(bar, Menu::PULLDOWN, "View", 0, viewItems);
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
	XtVaSetValues(bar, XmNmenuHelpWidget, helpMenu->GetWidget(), 0);
	// Bar is done -- manage it
	XtManageChild(bar);
	return bar;
}

void TableWindow::InitMenuItems() {
	DrawWindow::InitMenuItems();
	int i = 0;

	popupEditItems = new MenuItem[28]; i=0;
	popupEditItems[i++] = MenuItem(
		"Edit Commands", MenuItem::LABEL, 0, 0, 0, 
		0, 0, 0, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		"Undo", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>U", "Ctrl+U", 
		TableStubs::UndoCB, (XtPointer)viewer, 
		(XtPointer)1, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Redo", MenuItem::PUSHBUTTON, '\0', "Ctrl<Key>R", "Ctrl+R", 
		TableStubs::RedoCB, (XtPointer)viewer, 
		(XtPointer)1, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		"Add Rows...", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::AddRowsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Add Columns...", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::AddColumnsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		"Delete Rows", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::DeleteRowsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Delete Columns", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::DeleteColumnsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Purge", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::PurgeCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Delete All", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::DeleteAllCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		 "Cut Texts", MenuItem::PUSHBUTTON,'\0',"Ctrl<Key>X", "Ctrl+X", 
		TableStubs::CutTextsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		 "Copy Texts", MenuItem::PUSHBUTTON,'\0',"Ctrl<Key>C","Ctrl+C", 
		TableStubs::CopyTextsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		"Paste Texts", MenuItem::PUSHBUTTON,'\0',
		"Ctrl<Key>Y","Ctrl+Y", 
		TableStubs::PasteTextsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		 "Select All", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::SelectAllCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	popupEditItems[i++] = MenuItem(
		 "Sort Rows (Alphabetical)", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::SortRowsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem(
		 "Sort Columns (Alphabetical)", MenuItem::PUSHBUTTON, '\0', 0, 0, 
		TableStubs::SortColumnsCB, (XtPointer)table, 0, 0, 1);
	popupEditItems[i++] = MenuItem();

	editItems = new MenuItem[25]; i=0;
	editItems[i++] = MenuItem(
		"Undo", MenuItem::PUSHBUTTON, 'U', "Ctrl<Key>U", "Ctrl+U", 
		TableStubs::UndoCB, (XtPointer)viewer, 
		(XtPointer)0, 0, 1);
	editItems[i++] = MenuItem(
		"Redo", MenuItem::PUSHBUTTON, 'e', "Ctrl<Key>R", "Ctrl+R", 
		TableStubs::RedoCB, (XtPointer)viewer, 
		(XtPointer)0, 0, 1);
	editItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	editItems[i++] = MenuItem(
		"Add Rows...", MenuItem::PUSHBUTTON, 'R', 0, 0, 
		TableStubs::AddRowsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Add Columns...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		TableStubs::AddColumnsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	editItems[i++] = MenuItem(
		"Delete Rows", MenuItem::PUSHBUTTON, 'w', 0, 0, 
		TableStubs::DeleteRowsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Delete Columns", MenuItem::PUSHBUTTON, 'l', 0, 0, 
		TableStubs::DeleteColumnsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Purge", MenuItem::PUSHBUTTON, 'P', 0, 0, 
		TableStubs::PurgeCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Delete All", MenuItem::PUSHBUTTON, 'D', 0, 0, 
		TableStubs::DeleteAllCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	editItems[i++] = MenuItem(
		"Cut Texts", MenuItem::PUSHBUTTON, 't', "Ctrl<Key>X", "Ctrl+X",
		TableStubs::CutTextsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Copy Texts", MenuItem::PUSHBUTTON, 'y', "Ctrl<Key>C", "Ctrl+C",
		TableStubs::CopyTextsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Paste Texts", MenuItem::PUSHBUTTON, 'T',"Ctrl<Key>Y", "Ctrl+Y",
		TableStubs::PasteTextsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	editItems[i++] = MenuItem(
		"Select All", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		TableStubs::SelectAllCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	editItems[i++] = MenuItem(
		"Sort Rows", MenuItem::PUSHBUTTON, 'o', 0, 0, 
		TableStubs::SortRowsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem(
		"Sort Columns", MenuItem::PUSHBUTTON, 'm', 0, 0, 
		TableStubs::SortColumnsCB, (XtPointer)table, 0, 0, 1);
	editItems[i++] = MenuItem();

	defaultPropertiesItems = new MenuItem[35]; i=0;
	defaultPropertiesItems[i++] = MenuItem(
		"Default Line Style...", MenuItem::PUSHBUTTON, 'S', 0, 0, 
		TableStubs::DefaultLineStyleCB, (XtPointer)viewer, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Line Width...", MenuItem::SUBMENU, 'W', 0, 0, 
		TableStubs::DefaultLineWidthCB, (XtPointer)viewer, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Text Font...", MenuItem::PUSHBUTTON, 'F', 0, 0, 
		TableStubs::DefaultFontCB, (XtPointer)viewer, 0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Row Alignment...", MenuItem::PUSHBUTTON, 'R', 0, 0, 
		TableStubs::DefaultRowAlignmentCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Column Alignment...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		TableStubs::DefaultColumnAlignmentCB, (XtPointer)table, 
		0, 0, 1);
	// defaultPropertiesItems[i++] = MenuItem(
	// 	"Default Line Color...", MenuItem::SUBMENU, 'L', 0, 0, 
	// 	TableStubs::DefaultLineColorCB, (XtPointer)viewer, 
	// 	0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	defaultPropertiesItems[i++] = MenuItem(
		"Text Margin Width...", MenuItem::PUSHBUTTON, 'T', 0, 0, 
		TableStubs::SetMarginWidthCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Text Margin Height...", MenuItem::PUSHBUTTON, 'M', 0, 0, 
		TableStubs::SetMarginHeightCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Row Height...", MenuItem::PUSHBUTTON, 'H', 0, 0, 
		TableStubs::SetDefaultRowHeightCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Column Width...", MenuItem::PUSHBUTTON, 'W', 0, 0, 
		TableStubs::SetDefaultColumnWidthCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Number of Rows...", MenuItem::PUSHBUTTON, 'N', 0, 0, 
		TableStubs::SetNumberOfRowsCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem(
		"Default Number of Columns...",MenuItem::PUSHBUTTON, 'f', 0, 0, 
		TableStubs::SetNumberOfColumnsCB, (XtPointer)table, 
		0, 0, 1);
	defaultPropertiesItems[i++] = MenuItem();

	propertiesItems = new MenuItem[35]; i=0;
	propertiesItems[i++] = MenuItem(
		"Update Line Style...", MenuItem::SUBMENU, 'L', 0, 0, 
		TableStubs::UpdateTableLineStyleCB, (XtPointer)table, 
		0, 0, 1);
	propertiesItems[i++] = MenuItem(
		"Update Line Width...", MenuItem::PUSHBUTTON, 'W', 0, 0, 
		TableStubs::UpdateTableLineWidthCB, (XtPointer)table,
		0, 0, 1);
	propertiesItems[i++] = MenuItem(
		"Update Text Font...", MenuItem::PUSHBUTTON, 'F', 0, 0, 
		TableStubs::UpdateFontCB, (XtPointer)viewer, 
		0, 0, 1);
	propertiesItems[i++] = MenuItem(
		"Update Row Alignment...", MenuItem::PUSHBUTTON, 'R', 0, 0, 
		TableStubs::UpdateRowAlignmentCB, (XtPointer)table, 
		0, 0, 1);
	propertiesItems[i++] = MenuItem(
		"Update Column Alignment...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		TableStubs::UpdateColumnAlignmentCB, (XtPointer)table, 
		0, 0, 1);
	propertiesItems[i++] = MenuItem(
		"Set/Unset Text Underlining", MenuItem::PUSHBUTTON, 'U', 0, 0, 
		TableStubs::UpdateCellTextUnderlineCB, (XtPointer)table, 
		0, 0, 1);
	propertiesItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	propertiesItems[i++] = MenuItem(
		"Default Properties", MenuItem::SUBMENU, 'P', 0, 0, 
		0, 0, 0, defaultPropertiesItems, 1);
	propertiesItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	propertiesItems[i] = MenuItem(
		"Cell Annotation ...", MenuItem::PUSHBUTTON, 'A', 0, 0,
		TableStubs::AnnotateCellCB, (XtPointer)table,
		0, 0, 1); i++;
	propertiesItems[i++] = MenuItem();

	viewItems = new MenuItem[25]; i=0;
	viewItems[i++] = MenuItem(
		"Refresh", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>V", "Ctrl+V", 
		TableStubs::RefreshCB, (XtPointer)viewer, 
		(XtPointer)0, 0, 1);
	viewItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	viewItems[i++] = MenuItem(
		"Autoresizing", MenuItem::CHECKBUTTON, 'A', 0, 0, 
		TableStubs::SetAutoResizeCB, (XtPointer)viewer, 
		(XtPointer)(GetConfig()->GetAutoResizing()), 0, 1);
	viewItems[i++] = MenuItem(
		"In-line Editor", MenuItem::CHECKBUTTON, 'I', 0, 0, 
		TableStubs::SetInlineEditCB, (XtPointer)viewer, 
		(XtPointer)(GetConfig()->GetInlineEditor()), 0, 1);
	viewItems[i++] = MenuItem("", MenuItem::SEPARATOR);
	viewItems[i++] = MenuItem(
		"Show Row/Column Labels", MenuItem::CHECKBUTTON, 'S', 0, 0, 
		TableStubs::ShowRowColumnLabelsCB, (XtPointer)table, 
		(XtPointer)(GetConfig()->GetShowRowColumnLabels()), 0, 1);
	viewItems[i++] = MenuItem();

	// extend printer options menu with extra item.
	int j = 0;
        while (printerOptionsItems[j++].label != 0)
                ;
        printerOptionsItems[--j] = MenuItem(
                "Print Row/Column Labels", MenuItem::CHECKBUTTON, 'R', 0, 0,
                TableStubs::PrintRowColumnLabelsCB, (XtPointer)table, 
		(XtPointer)(GetConfig()->GetPrintRowColumnLabels()), 0, 1); j++;
        printerOptionsItems[j] = MenuItem();
}
