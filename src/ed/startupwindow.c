//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995,1999 
// Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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
#include "startupwindow.h"
#include "printeroptions.h"
#include "fileselectiondialog.h"
#include "textfieldlistdialog.h"
#include "messagedialog.h"
#include "config.h"
#include "helper.h"
#include "toolkit.h"
#include "mstring.h"
#include "application.h"
#include "mousecursor.h"
#include "menu.h"
#include "bitmap.h"
#include "system.h"
#include "version.h"
#include "liteclue.h"
#include "grafport.h"
#include "Teapot2a.xbm"
#if defined(LINUX)
#include <stdio.h>
#endif
#include <stdlib.h>
#include <Xm/XmAll.h>

const int StartupWindow::MIN_DRAWING_SIZE = 200;

StartupWindow::StartupWindow(const char *n): MainWindow(n) {
	// create configuration object.
	config = new Config("");
	// find current working directory.
	(void)System::GetCwd(&projDir);
	// find the directory with the executables of the tools.
	System::GetToolkitHome(&binDir);
	binDir += "/bin";
	// init text fields
	InitTextFields();
	welcomeLabel = "Welcome to ";
        welcomeLabel += Toolkit::STARTUP_TOOL_NAME;
}

StartupWindow::~StartupWindow() {
	tableFields.clear();
	drawingFields.clear();
	drawingDefaults.clear();
	tableDefaults.clear();
	tutDefaults.clear();
	fetDefaults.clear();
	if (helper)
		delete helper;
	if (config)
		delete config;
	if (fileSelectionDialog)
		delete fileSelectionDialog;
	if (dirSelectionDialog)
		delete dirSelectionDialog;
	if (tableOptionsDialog)
		delete tableOptionsDialog;
	if (drawingOptionsDialog)
		delete drawingOptionsDialog;
	if (fileItems)
		delete fileItems;
	if (viewItems)
		delete viewItems;
	if (helpItems)
		delete helpItems;
}

Widget StartupWindow::CreateWorkArea(Widget parent, int ac, char **av) {
	if (!check(parent))
		return 0;
	Widget startupForm = XtVaCreateWidget("StartupWindow", xmFormWidgetClass,
		parent, NULL);
	initDrawingWidth = config->GetDrawingWidth();
	initDrawingHeight = config->GetDrawingHeight();
	maxDrawingWidth = max(initDrawingWidth, config->GetDrawingMaxWidth());
	maxDrawingHeight = max(initDrawingHeight, config->GetDrawingMaxHeight());
	// create project directory selector dialog.
	dirSelectionDialog = new FileSelectionDialog(GetWidget());
	dirSelectionDialog->Initialize();
	dirSelectionDialog->SetDirectory(&projDir);
	dirSelectionDialog->SetTitle("Project Directory");
	dirSelectionDialog->SetExtension(".");
	dirSelectionDialog->SetDefaultFile("");
	dirSelectionDialog->SetOKCallback(SetProjectCB, this);
	// create file selector dialog.
	fileSelectionDialog = new FileSelectionDialog(GetWidget());
	fileSelectionDialog->Initialize();
	fileSelectionDialog->SetDirectory(&projDir);
	fileSelectionDialog->SetTitle("Open Document");
	fileSelectionDialog->SetExtension("*.*[dtg]");
	fileSelectionDialog->SetDefaultFile("");
	fileSelectionDialog->SetOKCallback(OpenDocumentCB, this);
	// set printer options.
	PrinterOptions *op = GetPrinterOptions();
	op->SetPrinterName(config->GetPrinterName());
	op->SetPrintCopies(1);
	op->SetPrintCommand(config->GetPrintCommand());
	op->SetTmpFile(config->GetTmpFile());
	op->SetTextFilterCommand(config->GetText2PSFilterCommand());
	// create text field list dialog for table options.
	tableOptionsDialog = new TextFieldListDialog(GetWidget());
	tableOptionsDialog->Initialize();
	tableOptionsDialog->SetTitle("Table Editor Startup");
	tableOptionsDialog->SetOKCallback(StartTableEditorCB, (XtPointer)this);
	tableOptionsDialog->CreateFields(&tableFields, &tableDefaults); 
	tableOptionsDialog->SetFieldWidth(5);
	// create text field list dialog for drawing area options.
	drawingOptionsDialog = new TextFieldListDialog(GetWidget());
	drawingOptionsDialog->Initialize();
	drawingOptionsDialog->SetTitle("Drawing Area Size");
	drawingOptionsDialog->SetOKCallback(SetDrawingAreaCB, (XtPointer)this);
	drawingOptionsDialog->CreateFields(&drawingFields, &drawingDefaults); 
	drawingOptionsDialog->SetFieldWidth(5);
	// create helper object.
	helper = new Helper(config, this);
	// parse user (command line) options
	ParseUserOptions(ac, av);
	CreateComponents(startupForm); // create the components of the document window.
	string txt = Toolkit::STARTUP_TOOL_NAME; 
	txt += " version ";
	txt += Version::TOOLKIT_VERSION;
	SetTitle(&txt);
	// set name and pixmap of the icon.
	SetIconName(Toolkit::STARTUP_TOOL_NAME);
	Bitmap bm;
	bm.xbm_width = Teapot2a_width;
        bm.xbm_height = Teapot2a_height;
        bm.xbm_bits = (unsigned char *)Teapot2a_bits;
        Pixmap px = bm.CreatePixmap(parent, GetDisplay());
	SetIconPixmap(px);
	return startupForm;
}

void StartupWindow::ParseUserOptions(int argc, char **argv) {
	// look for help option.
	int n;
	bool doExit = False;
	if (System::FindArg(argv, argc, "-help", n) ||
	    System::FindArg(argv, argc, "-h", n)) {
		const char *OPTIONS =
        	"-h[elp]\t\t\tShow this message and quit\n"
        	"-priv_cmap\t\tStart the tool with a private colormap\n"
        	"-v[ersion]\t\tShow the TCM version and quit\n";
        	std::cerr << "Usage: " << argv[0] << " [options]\nOptions:\n"
			<< OPTIONS << std::endl;
		doExit = True;
	}
	if (System::FindArg(argv, argc, "-version", n) ||
	    System::FindArg(argv, argc, "-v", n)) {
		std::cerr << argv[0] << ": " << Version::TOOLKIT_VERSION << std::endl;
		doExit = True;
	}
	if (doExit)
		exit(0);
}

void StartupWindow::CreateComponents(Widget parent) {
	Widget menuBar = CreateMenuBar(parent);
	scrolledWindow = XtVaCreateManagedWidget("ScrolledWindow",
                xmScrolledWindowWidgetClass, parent,
		XmNwidth, 200, // arbitrary values, resize in Finalize::
		XmNheight, 400,
                XmNscrollingPolicy, XmAUTOMATIC,
                XmNscrollBarDisplayPolicy, XmAS_NEEDED,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, menuBar,
		XmNleftAttachment, XmATTACH_FORM, 
		XmNbottomAttachment, XmATTACH_FORM, 
		XmNrightAttachment, XmATTACH_FORM, NULL);
	mainForm = XtVaCreateWidget("form",
		xmFormWidgetClass, scrolledWindow, NULL);
	// *** GEN *** //
	Widget frameGEN = XtVaCreateManagedWidget("frameGEN", 
				xmFrameWidgetClass, mainForm,
				XmNleftAttachment, XmATTACH_FORM, 
				XmNrightAttachment, XmATTACH_FORM,
				NULL);
	XtVaCreateManagedWidget("Generic Editors", 
			xmLabelWidgetClass, frameGEN,
			XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	Widget rowcolGEN = XtVaCreateManagedWidget("rowcolGEN", 
				xmRowColumnWidgetClass, frameGEN, NULL);
	AddToolEntry(rowcolGEN, 0); // TGD. 
	AddToolEntry(rowcolGEN, 9); // TGT. 
	AddToolEntry(rowcolGEN, 13); // TGTT. 
	XtVaCreateManagedWidget("separator", 
			xmSeparatorWidgetClass, mainForm,
			XmNmargin, 8, 
			XmNseparatorType, XmNO_LINE, NULL);
	// *** SA (YSM) *** //
	Widget frameSA = XtVaCreateManagedWidget("frameSA", 
				xmFrameWidgetClass, mainForm,
				XmNtopAttachment, XmATTACH_WIDGET,
				XmNtopWidget, frameGEN,
				XmNleftAttachment, XmATTACH_FORM, 
				XmNrightAttachment, XmATTACH_FORM,
				NULL);
	XtVaCreateManagedWidget("Structured Analysis Editors", 
			xmLabelWidgetClass, frameSA, 
			XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	Widget rowcolSA = XtVaCreateManagedWidget("rowcolSA", 
			xmRowColumnWidgetClass, frameSA, 
			XmNspacing, 4, NULL);
	AddToolEntry(rowcolSA, 26);	// ERD. 
	AddToolEntry(rowcolSA, 7);	// EFD
	AddToolEntry(rowcolSA, 3);	// MST. 
	AddToolEntry(rowcolSA, 11); 	// TUT
	AddToolEntry(rowcolSA, 12); 	// FET
	AddToolEntry(rowcolSA, 14); 	// FRT
	XtVaCreateManagedWidget("separator", 
			xmSeparatorWidgetClass, mainForm,
 			XmNmargin, 8, 
			XmNseparatorType, XmNO_LINE, NULL);
	// *** UML *** //
	Widget frameUML = XtVaCreateManagedWidget("frameUML", 
				xmFrameWidgetClass, mainForm,
				XmNtopAttachment, XmATTACH_WIDGET,
				XmNtopWidget, frameSA,
				XmNleftAttachment, XmATTACH_FORM, 
				XmNrightAttachment, XmATTACH_FORM,
				NULL);
	XtVaCreateManagedWidget("UML Editors", 
			xmLabelWidgetClass, frameUML, 
			XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	Widget rowcolUML = XtVaCreateManagedWidget("rowcolUML", 
			xmRowColumnWidgetClass, frameUML, 
			XmNspacing, 4, NULL);
	AddToolEntry(rowcolUML, 23);	// TUCD. 
	AddToolEntry(rowcolUML, 18);	// TSSD. 
	AddToolEntry(rowcolUML, 25);	// TATD. 
	AddToolEntry(rowcolUML, 24);	// TSCD. 
	AddToolEntry(rowcolUML, 20);	// TSQD. 
	AddToolEntry(rowcolUML, 19);	// TCBD. 
	AddToolEntry(rowcolUML, 21);	// TCPD. 
	AddToolEntry(rowcolUML, 22);	// TDPD. 
	XtVaCreateManagedWidget("separator", 
			xmSeparatorWidgetClass, mainForm,
			XmNmargin, 8, 
			XmNseparatorType, XmNO_LINE, NULL);
	// *** MISC *** //
	Widget frameMISC = XtVaCreateManagedWidget("frameMISC", 
				xmFrameWidgetClass, mainForm,
				XmNtopAttachment, XmATTACH_WIDGET,
				XmNtopWidget, frameUML,
				XmNleftAttachment, XmATTACH_FORM, 
				XmNrightAttachment, XmATTACH_FORM,
				NULL);
	XtVaCreateManagedWidget("Miscellaneous Editors", 
			xmLabelWidgetClass, frameMISC,
			XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	Widget rowcolMISC = XtVaCreateManagedWidget("rowcolMISC", 
			xmRowColumnWidgetClass, frameMISC, NULL);
	AddToolEntry(rowcolMISC, 1);	// ERD 
	AddToolEntry(rowcolMISC, 2);	// CRD 
	AddToolEntry(rowcolMISC, 6);	// DFD
	AddToolEntry(rowcolMISC, 4);	// PSD
	AddToolEntry(rowcolMISC, 8);	// SND
	AddToolEntry(rowcolMISC, 5);	// RPG
	AddToolEntry(rowcolMISC, 10);	// TDT
	XtVaCreateManagedWidget("separator", 
			xmSeparatorWidgetClass, mainForm,
			XmNmargin, 8, 
			XmNseparatorType, XmNO_LINE, NULL);
	Widget formSTATUS =  XtVaCreateManagedWidget("formSTATUS",
				xmFormWidgetClass, mainForm,
				XmNtopAttachment, XmATTACH_WIDGET,
				XmNtopWidget, frameMISC,
				XmNleftAttachment, XmATTACH_FORM,
				XmNrightAttachment, XmATTACH_FORM,
				NULL);
	int stColumns = 42;
	if (WidthOfScreen(XtScreen(parent)) <= 1024)
		// <= SVGA
		stColumns = 36;
	statusBar = XtVaCreateManagedWidget("statusBar", 
			xmTextFieldWidgetClass, formSTATUS, 
			XmNeditable, False, 
			XmNcursorPositionVisible, False,
			XmNshadowThickness, 0,
			XmNcolumns, stColumns, 
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM, NULL);
	XtManageChild(mainForm);
	XtManageChild(scrolledWindow);
	XtManageChild(parent);
}

void StartupWindow::InitTextFields() {
	tableFields.empty();
	tableFields.add(new string("Number of rows"));
	tableFields.add(new string("Number of columns"));
	tableFields.add(new string("Min. cell width (mm)"));
	tableFields.add(new string("Min. cell height (mm)"));
	string nor = config->GetNumberOfRows();
	string noc = config->GetNumberOfColumns();
	string mcw = (int)(pixels2mm(config->GetDefaultColumnWidth())+0.5);
	string mch = (int)(pixels2mm(config->GetDefaultRowHeight())+0.5);
	string cwfet = (int)(pixels2mm(config->GetFETcolumnWidth())+0.5);
	string cwtut = (int)(pixels2mm(config->GetTUTcolumnWidth())+0.5);
	string noctut = config->GetTUTnumberOfColumns();
	tableDefaults.empty();
	tableDefaults.add(new string(nor)); tableDefaults.add(new string(noc));
	tableDefaults.add(new string(mcw)); tableDefaults.add(new string(mch));
	fetDefaults.empty();
	fetDefaults.add(new string(nor)); fetDefaults.add(new string(noc));
	fetDefaults.add(new string(cwfet)); fetDefaults.add(new string(mch));
	tutDefaults.empty();
	tutDefaults.add(new string(nor)); tutDefaults.add(new string(noctut));
	tutDefaults.add(new string(cwtut)); tutDefaults.add(new string(mch));
	drawingFields.empty();
	drawingFields.add(new string("Default width (mm)"));
	drawingFields.add(new string("Default height (mm)"));
	drawingFields.add(new string("Maximal width (mm)"));
	drawingFields.add(new string("Maximal height (mm)"));
	drawingDefaults.empty();
	drawingDefaults.add(new string("this"));
	drawingDefaults.add(new string("is"));
	drawingDefaults.add(new string("not"));
	drawingDefaults.add(new string("right"));
}

Widget StartupWindow::CreateMenuBar(Widget parent) {
	// create menubar at the top of the parent
	Arg  args[9];
	int i = 0;
	XtSetArg(args[i], XmNtopAttachment, XmATTACH_FORM); i++;
	XtSetArg(args[i], XmNleftAttachment, XmATTACH_FORM); i++;
	XtSetArg(args[i], XmNrightAttachment, XmATTACH_FORM); i++;
	// create a menubar that contains the following menus:
	char wname[10] = "MenuBar";
	Widget bar = XmCreateMenuBar(parent, wname, args, i);
	InitMenuItems();
	fileMenu = new Menu(bar, Menu::PULLDOWN, "File", 0, fileItems);
	viewMenu = new Menu(bar, Menu::PULLDOWN, "View", 0, viewItems);
	helpMenu = new Menu(bar, Menu::PULLDOWN, "Help", 0, helpItems);
	// tell bar which bar which button is the help menu
	XtVaSetValues(bar, XmNmenuHelpWidget, helpMenu->GetWidget(), NULL);
	// Bar is done -- manage it
	XtManageChild(bar);
	return bar;
}

void StartupWindow::AddToolEntry(Widget parent, int i) {
	XmString xmtt; char tt[MAXNAME]; char ttinfo[MAXNAME];
	Widget form = XtVaCreateWidget("form", 
		xmFormWidgetClass, parent, NULL);
	Widget button = XtVaCreateManagedWidget(Toolkit::TOOL_NAMES[i], 
		xmPushButtonWidgetClass, form, XmNwidth, 50, 
		XmNheight, 22,
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM, 
		XmNuserData, i,
		NULL);
	strcpy(tt, Toolkit::DOCUMENT_TYPES[i]);
	xmtt = CreateXmString(tt);
	strcpy(ttinfo, Toolkit::DOCUMENT_TYPES_INFO[i]);
	AddLiteClue(button, ttinfo) ;
	XtVaCreateManagedWidget(Toolkit::DOCUMENT_TYPES[i],
		xmLabelWidgetClass, form, XmNlabelString, xmtt,
		XmNleftAttachment, XmATTACH_WIDGET,
		XmNleftWidget, button, 
		XmNtopAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftOffset, 6,
		NULL);
	XtAddCallback(button, XmNactivateCallback, StartEditorCB, 
			(XtPointer *)this);
	XmStringFree(xmtt);
	XtManageChild(form);
}

void StartupWindow::StartEditor(int editor, const string *filename) {
	GetCursor()->Set(MouseCursor::WATCH);
	string file = binDir + "/"; 
	file += Toolkit::EXECUTABLE_NAMES[editor];
	if (editor >= 0
#if !defined(__CYGWIN__)
// sorry, but I can't get it running on cygwin otherwise (daniel)
		&& System::FileExecutable(file.getstr())
#endif
	) {		
		if (strstr(Toolkit::TOOL_TITLES[editor], "Table"))
			if (!filename)
				ShowTableDialog(editor);
			else
				StartDocumentEditor(editor, filename);
		else
			StartDocumentEditor(editor, filename);
	}
	else {
		string txt;
		if (System::FileExists(file.getstr()))
			txt = "The selected tool " + file + " is not executable";
		else
			txt = "The selected tool " + file + " does not exist yet";
		(new MessageDialog(GetWidget(), MessageDialog::INFORMATION))->
			Show("Warning", &txt); 
	}
	GetCursor()->Set(MouseCursor::LEFT_PTR);
}

void StartupWindow::AppendExec(string *command, int editor) {
	*command = binDir + "/";
	*command += Toolkit::EXECUTABLE_NAMES[editor];
}

void StartupWindow::AppendProjDir(string *command) {
	*command += " -projdir \"" + projDir + "\"";
}

void StartupWindow::AppendDrawingArea(string *command) {
	*command += " -drawing ";
	string txt = initDrawingWidth;
	txt += "x";
	txt += initDrawingHeight;
	*command += txt;
	*command += " -maxdrawing ";
	txt = maxDrawingWidth;
	txt += "x";
	txt += maxDrawingHeight;
	*command += txt.getstr();
}

void StartupWindow::ExecCommand(string *command) {
	*command += " &";
	SetStatus(command);
	system(command->getstr());
#ifdef DEBUG
	error("executing %s\n", command->getstr());
#endif
}

void StartupWindow::StartDocumentEditor(int editor, const string *filename) {
	string command;	// the Unix command that will execute.
	AppendExec(&command, editor);
	AppendProjDir(&command);
	AppendDrawingArea(&command);
	if (filename) {
		command += " ";
		command += *filename;
	}
	ExecCommand(&command);
}

void StartupWindow::ShowTableDialog(int editor) {
	tmpEditor = editor;
	List<string *> *defaults;
	if (equal(Toolkit::TOOL_NAMES[editor], "TFET")) {
		defaults = &fetDefaults;
	}
	else if (equal(Toolkit::TOOL_NAMES[editor], "TTUT")) {
		defaults = &tutDefaults;
	}
	else
		defaults = &tableDefaults;
	int i = 0;
	for (defaults->first(); !defaults->done(); defaults->next()) {
		tableOptionsDialog->SetField(i, defaults->cur()); 
		i++;
	}
	string txt = "Initial ";
	txt += Toolkit::TOOL_NAMES[editor];
	txt += " options"; 
	tableOptionsDialog->SetTitle(&txt);
	tableOptionsDialog->Popup();
}

void StartupWindow::StartTableEditor(unsigned rows, unsigned columns, 
		unsigned cellwidth, unsigned cellheight) {
	string command;
	int editor = tmpEditor;
	AppendExec(&command, editor);
	AppendProjDir(&command);
	AppendDrawingArea(&command);
	char taboptions[MAXNAME];
	rows = max(rows, 1);
	columns = max(columns, 1);
	cellwidth = max(cellwidth, 1);
	cellheight = max(cellheight, 1);
	sprintf(taboptions, " -table %dx%d -cell %dx%d", rows, columns, 
			(int)mm2pixels(cellwidth), (int)mm2pixels(cellheight));
	command += taboptions;
	ExecCommand(&command);
}

void StartupWindow::DrawingArea() {
	char s0[10],s1[10],s2[10],s3[10];
	sprintf(s0, "%d", (int)(pixels2mm(initDrawingWidth)+0.5));
	sprintf(s1, "%d", (int)(pixels2mm(initDrawingHeight)+0.5));
	sprintf(s2, "%d", (int)(pixels2mm(maxDrawingWidth)+0.5));
	sprintf(s3, "%d", (int)(pixels2mm(maxDrawingHeight)+0.5));
	*drawingDefaults[0] = s0;
	*drawingDefaults[1] = s1;
	*drawingDefaults[2] = s2;
	*drawingDefaults[3] = s3;
	SetStatus("set drawing area size");
	int i = 0;
	for (drawingDefaults.first(); !drawingDefaults.done(); 
	     drawingDefaults.next()) {
		drawingOptionsDialog->SetField(i, drawingDefaults.cur()); 
		i++;
	}
	drawingOptionsDialog->Popup();
}

void StartupWindow::SetDrawingArea(unsigned idw, unsigned idh, 
				   unsigned mdw, unsigned mdh) {
	initDrawingWidth = (unsigned)(mm2pixels(idw)+0.5);
	initDrawingHeight = (unsigned)(mm2pixels(idh)+0.5);
	initDrawingWidth = max(MIN_DRAWING_SIZE, initDrawingWidth);
	initDrawingHeight = max(MIN_DRAWING_SIZE, initDrawingHeight);
	maxDrawingWidth = (unsigned)(mm2pixels(mdw)+0.5);
	maxDrawingHeight = (unsigned)(mm2pixels(mdh)+0.5);
	maxDrawingWidth = max(initDrawingWidth, maxDrawingWidth);
	maxDrawingHeight = max(initDrawingHeight, maxDrawingHeight);
	string txt = "initial area ";
	txt += initDrawingWidth;
	txt += "x";
	txt += initDrawingHeight;
	txt += " mm, maximum area ";
	txt += maxDrawingWidth;
	txt += "x";
	txt += maxDrawingHeight;
	txt += " mm";
	SetStatus(&txt);
}

void StartupWindow::Quit() {
	Close();
}

void StartupWindow::Project() {
	SetStatus("set project directory");
	dirSelectionDialog->Popup();
}

void StartupWindow::OpenDocument() {
	SetStatus("open document");
	fileSelectionDialog->Popup();
}

void StartupWindow::SetProject(const string *p) {
	string txt;
	if (System::DirExists(p->getstr())) {
		projDir = *p;
		txt = "new proj.dir " + projDir;
	}
	else {
		txt = *p;
		txt += ": \nno such directory";
		(new MessageDialog(GetWidget(), MessageDialog::ERROR))->
			Show("No directory", &txt);
		txt = "Set proj.dir failed";
	}
	SetStatus(&txt);
}

void StartupWindow::OpenDocument(const string *filename) {
	string suffix;
	filename->getSuffix(suffix, '.'); 
	int editor = -1;
	const char **p = Toolkit::DOCUMENT_SUFFIXES;
	while (*p != 0) {
		editor++;
		if (suffix == *p) {  
			StartEditor(editor, filename);
			return;
		}
		p++;
	}
	string txt = *filename + ": not a TCM document";
	(new MessageDialog(GetWidget(), MessageDialog::ERROR))->
		Show("No TCM document", &txt);
	SetStatus("open document failed");
}

void StartupWindow::SetStatus(const char *s) {
	if (statusBar)
		XtVaSetValues(statusBar, XmNvalue, s, NULL);
}

void StartupWindow::SetStatus(const string *s) {
	SetStatus(s->getstr());
}

void StartupWindow::InitMenuItems() {
	int i = 0;
	fileItems = new MenuItem[10]; i=0;
	fileItems[i] = MenuItem(
		"Open Document...", MenuItem::PUSHBUTTON, 
		'O', "Ctrl<Key>O", "Ctrl+O", StartupWindow::DocumentCB, 
		(XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Project Directory...", MenuItem::PUSHBUTTON, 
		'P', "Ctrl<Key>P", "Ctrl+P", StartupWindow::ProjectCB, 
		(XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem("",MenuItem::SEPARATOR); i++;
	fileItems[i] = MenuItem( 
		"Quit", MenuItem::PUSHBUTTON, 
		'Q', "Ctrl<Key>Q", "Ctrl+Q", StartupWindow::QuitCB, 
		(XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem::NUL;

	viewItems = new MenuItem[10]; i=0;
	viewItems[i] = MenuItem(
		"Drawing Area Size...", MenuItem::PUSHBUTTON, 
		'D', 0, 0, StartupWindow::DrawingAreaCB, 
		(XtPointer)this, 0, 0, 1), i++;
	viewItems[i] = MenuItem::NUL;
 
	helpItems = new MenuItem[10]; i=0;
	helpItems[i] = MenuItem(
		(char *)welcomeLabel.getstr(), MenuItem::PUSHBUTTON,
		'W', 0, 0, StartupWindow::HelpCB, 
		(XtPointer)helper, (XtPointer)Helper::WELCOME, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Starting editors", MenuItem::PUSHBUTTON,
		'S', 0, 0, StartupWindow::HelpCB, 
		(XtPointer)helper, (XtPointer)Helper::STARTING_EDITORS, 0, 1); 
		i++;
	helpItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	helpItems[i] = MenuItem(
		"Version", MenuItem::PUSHBUTTON, 
		'V', 0, 0, StartupWindow::HelpCB, 
		(XtPointer)helper, (XtPointer)Helper::VERSION, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Copying", MenuItem::PUSHBUTTON, 
		'C', 0, 0, StartupWindow::HelpCB, 
		(XtPointer)helper, (XtPointer)Helper::COPYING, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Change Log", MenuItem::PUSHBUTTON, 
		'L', 0, 0, StartupWindow::HelpCB, 
		(XtPointer)helper, (XtPointer)Helper::CHANGELOG, 0, 1); i++;
	helpItems[i] = MenuItem::NUL;
}

void StartupWindow::StartEditorCB(Widget w, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;
	int num;
	XtVaGetValues(w, XmNuserData, &num, NULL);
	s->StartEditor(num);
}

void StartupWindow::SetDrawingAreaCB(Widget, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;
	TextFieldListDialog *t = s->GetDrawingOptionsDialog();
	string v;
	t->GetField(0, &v);
	unsigned idw = v.toint();
	t->GetField(1, &v);
	unsigned idh = v.toint();
	t->GetField(2, &v);
	unsigned mdw = v.toint();
	t->GetField(3, &v);
	unsigned mdh = v.toint();
	s->SetDrawingArea(idw, idh, mdw, mdh);
}

void StartupWindow::StartTableEditorCB(Widget, XtPointer clientData, XtPointer){
	StartupWindow *s = (StartupWindow *)clientData;
	TextFieldListDialog *t = s->GetTableOptionsDialog();
	string v;
	t->GetField(0, &v);
	int rows = v.toint();
	t->GetField(1, &v);
	int columns = v.toint();
	t->GetField(2, &v);
	int cellwidth = v.toint();
	t->GetField(3, &v);
	int cellheight = v.toint();
	s->StartTableEditor(rows, columns, cellwidth, cellheight);
}

void StartupWindow::SetProjectCB(Widget, XtPointer cd, XtPointer) {
	string name;
	StartupWindow *sw = (StartupWindow *)cd;
	sw->GetDirSelectionDialog()->GetFileName(&name);
	sw->SetProject(&name);
}

void StartupWindow::OpenDocumentCB(Widget, XtPointer cd, XtPointer) {
	string file, dir;
	StartupWindow *sw = (StartupWindow *)cd;
	sw->GetFileSelectionDialog()->GetDirectory(&dir);
	sw->GetFileSelectionDialog()->GetFileName(&file);
	sw->SetProject(&dir);
	sw->OpenDocument(&file);
}

void StartupWindow::QuitCB(Widget, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;	
	s->Quit();
}

void StartupWindow::ProjectCB(Widget, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;	
	s->Project();
}

void StartupWindow::DocumentCB(Widget, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;	
	s->OpenDocument();
}

void StartupWindow::DrawingAreaCB(Widget, XtPointer clientData, XtPointer) {
	StartupWindow *s = (StartupWindow *)clientData;
	s->DrawingArea();
}

void StartupWindow::HelpCB(Widget w, XtPointer cd, XtPointer) {
	Helper *hp = (Helper *)cd;
	hp->SetStatus("action: help");
	Helper::HelpTopicType tp;
	XtVaGetValues(w, XmNuserData, &tp, NULL);
	hp->Help(tp);
}

void StartupWindow::Finalize() {
	Dimension fwd, fht;
	XtVaGetValues(mainForm, XmNwidth, &fwd, XmNheight, &fht, NULL);
	// std::cout << "mainForm width = " << fwd << std::endl;
	// std::cout << "mainForm height = " << fht << std::endl;
	Screen *screen = XtScreen(GetWidget());
	Dimension swd = WidthOfScreen(screen);
	Dimension sht = HeightOfScreen(screen);
	// std::cout << swd << "x" << sht << std::endl;
	Dimension wd = min(swd/3, fwd+11);     // this 11 and 39 are found
	Dimension ht = min(sht*9/10, fht+39);  // experimentally
	// std::cout << "win width = " << wd << std::endl;
	// std::cout << "win height = " << ht << std::endl;
	XtVaSetValues(GetWidget(), XmNwidth, wd, NULL);
	XtVaSetValues(GetWidget(), XmNheight, ht, NULL);
}
