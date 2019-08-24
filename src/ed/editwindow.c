///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "mstring.h"
#include "document.h"
#include "editstubs.h"
#include "printer.h"
#include "helper.h"
#include "bitmap.h"
#include "menu.h"
#include "system.h"
#include "version.h"
#include "liteclue.h"
#include "config.h"
#include <stdlib.h>
#include <Xm/XmAll.h>
#include "messagedialog.h"
#include "Teapot2a.xbm"

EditWindow::EditWindow(const char *n): MainWindow(n) {
	helper = 0;
	document = 0;
	printer = 0;
	logo = 0;
	menubar = 0;
	popupEditItems = 0;
	fileItems = 0;
	editItems = 0;
	printItems = 0;
	printerOptionsItems = 0;
	propertiesItems = 0;
	pageOrientationItems = 0;
	pageSizeItems = 0;
	bannerPageItems = 0;
	pageItems = 0;
	helpItems = 0;
	searchItems = 0;
	viewItems = 0;
	documentArea = 0;
	statusArea = 0;
	statusText = 0;
	dirName = 0;
	documentName = 0;
	documentLevel = 0;
	documentType = 0;
	modifiedToggle = 0;
	editMenu = 0;
	screenType = SUN17;
	doLoad = False;
	projDir = "";
	loadFile = "";
	generatePS = False;
	generateEPS = False;
	generateFig = False;
	generatePNG = False;
	generateLatexFonts = False;
	doMap = True;
}

EditWindow::~EditWindow() {
	if (helper)
		delete helper;
	if (printer)
		delete printer;
	if (document)
		delete document;
	if (popupEditItems)
		delete popupEditItems;
	if (fileItems)
		delete fileItems;
	if (editItems)
		delete editItems;
	if (printItems)
		delete printItems;
	if (printerOptionsItems)
		delete printerOptionsItems;
	if (bannerPageItems)
		delete bannerPageItems;
	if (helpItems)
		delete helpItems;
	if (viewItems)
		delete viewItems;
	if (searchItems)
		delete searchItems;
	if (propertiesItems)
		delete propertiesItems;
	if (pageOrientationItems)
		delete pageOrientationItems;
	if (pageSizeItems)
		delete pageSizeItems;
	if (pageItems)
		delete pageItems;
}

void EditWindow::Manage() {
	if (doMap)
		MainWindow::Manage();
	else
		MainWindow::ManageUnmapped();
}

Widget EditWindow::CreateWorkArea(Widget parent, int argc, char **argv) {
	if (!check(parent))
		return 0;
	logoBitmap.xbm_width = Teapot2a_width;
	logoBitmap.xbm_height = Teapot2a_height;
	logoBitmap.xbm_bits = (unsigned char *)Teapot2a_bits;
	logoPixmap = logoBitmap.CreatePixmap(parent, GetDisplay());
	Widget form = XtVaCreateManagedWidget(GetName()->getstr(), 
		xmFormWidgetClass, parent, NULL);
	// find type of document tool 
	int tool = GetTool();
	// parse command line options
	DetermineScreen(XtScreen(parent)); // determine screen sizes.
	ParseUserOptions(argc, argv);
	// Create application objects.
	CreateHelper();
	CreateDocument();
	CreatePrinter();
	CreateComponents(form); // create the UI components of the main window.
	string title = Toolkit::TOOLKIT_NAME;
	title += ": ";
	title += Toolkit::TOOL_TITLES[tool];
	title += " - ";
	title += Version::TOOLKIT_VERSION;
	SetTitle(&title);
	// set name and pixmap of the icon.
	SetIconName(Toolkit::TOOL_NAMES[tool]); 
	SetIconPixmap(logoPixmap);
	return form;
}

void EditWindow::ParseUserOptions(int argc, char **argv) {
	int n;
	argsLeft = argc-1;
	bool doExit = False;
	// look for help option.
	if (System::FindArg(argv, argc, "-help", n) || 
	    System::FindArg(argv, argc, "-h", n)) {
		WriteUsage(argv[0]);
		doExit = True;
	}
	// look for version option.
	if (System::FindArg(argv, argc, "-version", n) ||
	    System::FindArg(argv, argc, "-v", n)) {
		std::cerr << argv[0] << ": " << Version::TOOLKIT_VERSION << std::endl;
		doExit = True;
	}
	if (doExit)
		exit(0);
	// find but ignore priv_cmap option here.
	if (System::FindArg(argv, argc, "-priv_cmap", n)) {
		argsLeft -= 1;
	}
	// look for -project option to set working directory.
	if (System::FindArg(argv, argc, "-projdir", n)) {
		if (n < argc-1) {
			projDir = argv[n+1]; 
			argsLeft -= 2;
		}
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	// look for -toPS option to generate PS.
	if (System::FindArg(argv, argc, "-toPS", n)) {
		argsLeft -= 1;
		psFile = "";
		generatePS = True;
		doMap = False;
		if (n < argc-1) {
			char *c = strrchr(argv[n+1], '.');
        		if (c && equal(c, ".ps")) {
				argsLeft -= 1;
				psFile = argv[n+1];
			}
		}
	}
	// look for -toEPS option to generate EPS.
	if (System::FindArg(argv, argc, "-toEPS", n)) {
		argsLeft -= 1;
		epsFile = "";
		generateEPS = True;
		doMap = False;
		if (n < argc-1) {
			char *c = strrchr(argv[n+1], '.');
        		if (c && equal(c, ".eps")) {
				argsLeft -= 1;
				epsFile = argv[n+1];
			}
		}
	}
	// look for -toPNG option to generate PNG.
	if (System::FindArg(argv, argc, "-toPNG", n)) {
		argsLeft -= 1;
		pngFile = "";
		generatePNG = True;
		doMap = False;
		if (n < argc-1) {
			char *c = strrchr(argv[n+1], '.');
        		if (c && equal(c, ".png")) {
				argsLeft -= 1;
				pngFile = argv[n+1];
			}
		}
	}
	// look for -toFig option to generate Fig.
	if (System::FindArg(argv, argc, "-toFig", n) ||
	    System::FindArg(argv, argc, "-toFIG", n)) {
		argsLeft -= 1;
		figFile = "";
		generateFig = True;
		doMap = False;
		if (n < argc-1) {
			char *c = strrchr(argv[n+1], '.');
        		if (c && equal(c, ".fig")) {
				argsLeft -= 1;
				figFile = argv[n+1];
			}
		}
		if (System::FindArg(argv, argc, "-latex", n)) {
			argsLeft -= 1;
			generateLatexFonts = True;
		}
	}
}

void EditWindow::WriteUsage(const char *prog) {
	const char *OPTIONS = 
	"-drawing <w>x<h>\tCreate drawing area of <w>x<h> pixels\n"
	"-h[elp]\t\t\tShow this message and quit\n"
	"-maxdrawing <w>x<h>\tSet maximum drawing area size to <w>x<h> pixels\n"
	"-projdir <dir>\t\tSet the project directory to <dir>\n"
	"-priv_cmap\t\tStart the editor with a private colormap\n"
	"-toPS [<file>.ps]\tGenerate PostScript (to <file>.ps or else stdout) "             
		"and quit\n"
	"-toEPS [<file>.eps]\tGenerate EPS (to <file>.eps or else stdout) "
	       "and quit\n"
	"-toFig [<file>.fig] [-latex]\tGenerate Fig format (to <file>.fig "
		"or else\n\t\t\tstdout) and quit. "
		"When the -latex option is given\n\t\t\tLaTeX fonts are "
		"generated, otherwise normal PostScript\n\t\t\t fonts"
		"are generated\n"
	"-toPNG <file>.png\tGenerate PNG format to <file>.png and quit\n"
	"-v[ersion]\t\tShow the TCM version and quit\n"
	"remark: the -toXXX options require an existing TCM document file\n";
	std::cerr << "Usage: " << prog << " [options] [document]\nOptions:\n"
	     << OPTIONS << std::endl;
}


Widget EditWindow::CreateLogo(Widget parent) {
	// draws a little picture in the top right corner of parent. 
	if (!check(parent))
		return 0;
	Pixel fg, bg;
	// get the foreground and background colors of the parent
	// to make the pixmaps appear using a consistent color
	XtVaGetValues(parent, XmNforeground, &fg, XmNbackground, &bg, NULL);
	// the pixmap is loaded from a X11 bitmap, called DEFAULT_ICON.
	Pixmap px = logoBitmap.CreatePixmap(parent, GetDisplay()); 
	Widget button = XtVaCreateManagedWidget(
			"logo", xmPushButtonWidgetClass, parent,
			XmNlabelPixmap, px,
			XmNlabelType, XmPIXMAP,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM, NULL);
	XtAddCallback(button, XmNactivateCallback, AboutCB, (XtPointer)this);
	AddLiteClue(button, "TCM logo");
	return button;
}

Widget EditWindow::CreateDocumentArea(Widget parent) {
	// draws a label and a text-field which is intended to contain the
	// name and type of document that is being edited
	if (!check(parent))
		return 0;
	Widget rc = XtVaCreateWidget("DocumentArea", 
		xmRowColumnWidgetClass, parent, 
		XmNadjustLast, True,
		XmNorientation, XmHORIZONTAL,
		XmNleftAttachment, XmATTACH_FORM, NULL);
	if (menubar)
		XtVaSetValues(rc, XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, menubar, NULL);
	if (logo)
		XtVaSetValues(rc, XmNrightAttachment, XmATTACH_WIDGET,
			XmNrightWidget, logo, NULL);
	XtVaCreateManagedWidget("Document Type: ",
		xmLabelWidgetClass, rc,
		XmNalignment, XmALIGNMENT_BEGINNING, NULL);
	documentType = XtVaCreateManagedWidget("DocumentType",
		xmTextFieldWidgetClass, rc, 
		XmNcolumns, 15,
		XmNeditable, False,
		XmNcursorPositionVisible, False, NULL);
	AddLiteClue(documentType, 
		"The type of document that is edited by this editor (fixed)");
	XtVaCreateManagedWidget("Name: ",
		xmLabelWidgetClass, rc, 
		XmNalignment, XmALIGNMENT_BEGINNING, NULL);
	documentName = XtVaCreateManagedWidget("DocumentName",
		xmTextFieldWidgetClass, rc, 
		XmNeditable, True,
		XmNcolumns, 10,
		XmNcursorPositionVisible, True, NULL);
	AddLiteClue(documentName, 
	 	"The document name. Can be changed (apply with <enter>)");
	if (check(document))
		XtAddCallback(documentName, XmNactivateCallback, 
			EditStubs::ChangeNameCB, (XtPointer)document);
	if (Toolkit::HierarchicEditor(GetTool())) {
//		XtVaCreateManagedWidget("Level: ",
//			xmLabelWidgetClass, rc,
//			XmNalignment, XmALIGNMENT_BEGINNING, NULL);
//		documentLevel = XtVaCreateManagedWidget("DocumentLevel",
//			xmTextFieldWidgetClass, rc,
//			XmNeditable, False,
//			XmNcursorPositionVisible, False, NULL);
//		AddLiteClue(documentLevel,
//			"The current level in the document (fixed)");
	}
	modifiedToggle = CreateToggle(rc, "modified", False, 
			EditStubs::SetModifiedCB, (XtPointer)document);
	AddLiteClue(modifiedToggle, "Indicates document modification");
	XtUninstallTranslations(modifiedToggle); 
	XtManageChild(rc);
	return rc;
}

Widget EditWindow::CreateControlArea(Widget parent) {
	if (!check(parent))
		return 0;
	Widget rc = XtVaCreateWidget("ControlArea", 
		xmRowColumnWidgetClass, parent, 
		XmNorientation, XmHORIZONTAL, NULL);
	if (statusArea) 
		XtVaSetValues(rc, XmNtopWidget, statusArea, 
			XmNtopAttachment, XmATTACH_WIDGET, NULL);
	XtVaSetValues(rc, XmNbottomAttachment, XmATTACH_FORM, NULL);
	XtManageChild(rc);
	return rc;
}

Widget EditWindow::CreateStatusArea(Widget parent) {
	// create a single line uneditable text field. This is the area 
	// intended for (status) text output of the application.
	if (!check(parent))
		return 0;
	Widget rc = XtVaCreateWidget("StatusArea", 
		xmRowColumnWidgetClass, parent, 
		XmNorientation, XmHORIZONTAL, NULL);
	if (controlArea) 
		XtVaSetValues(rc, XmNbottomWidget, controlArea, 
			XmNbottomAttachment, XmATTACH_WIDGET, NULL);
	statusText = XtVaCreateManagedWidget("StatusText",
		xmTextFieldWidgetClass, rc, 
		XmNeditable, False,
		XmNcursorPositionVisible, False,
		XmNshadowThickness, 0,
		XmNvalue, "...", NULL);
	if (screenType <= SVGA)
		XtVaSetValues(statusText, XmNcolumns, 40, NULL);
	else
		XtVaSetValues(statusText, XmNcolumns, 50, NULL);
	XtManageChild(rc);
	return rc;
}

Widget EditWindow::CreateToggle(Widget parent, const char *label, bool Init, 
			XtCallbackProc fun, XtPointer clientData) {
	if (!check(parent))
		return 0;
	XmString text = CreateXmString(label);
	Widget toggle = XtVaCreateManagedWidget(label, 
		xmToggleButtonWidgetClass, parent,
		XmNlabelString, text,
		XmNset, Init, NULL);
	XtAddCallback(toggle, XmNvalueChangedCallback, fun, clientData);
	XmStringFree(text);
	return toggle;
}

void EditWindow::EnableUndo(bool flag) {
	// change edit pulldown menu undo sensitiveness.
	if (!editMenu)
		return;
	Widget undoMenuItem = editMenu->GetMenuItem("Undo");
	if (undoMenuItem) {
		XtVaSetValues(undoMenuItem, XmNsensitive, flag, NULL);
	}
}

void EditWindow::EnableRedo(bool flag) {
	// change edit pulldown menu redo sensitiveness.
	if (!editMenu)
		return;
	Widget redoMenuItem = editMenu->GetMenuItem("Redo");
	if (redoMenuItem)
		XtVaSetValues(redoMenuItem, XmNsensitive, flag, NULL);
}

void EditWindow::SetUndoName(const char *uname) {
	// change edit pulldown menu undo label.
	if (!editMenu)
		return;
	XmString s = CreateXmString(uname);
	Widget undoMenuItem = editMenu->GetMenuItem("Undo");
	if (undoMenuItem)
		XtVaSetValues(undoMenuItem, XmNlabelString, s, NULL);
	XmStringFree(s);
}

void EditWindow::SetRedoName(const char *uname) {
	// change edit pulldown menu redo label.
	if (!editMenu)
		return;
	XmString s = CreateXmString(uname);
	Widget redoMenuItem = editMenu->GetMenuItem("Redo");
	if (redoMenuItem)
		XtVaSetValues(redoMenuItem, XmNlabelString, s, NULL);
	XmStringFree(s);
}

void EditWindow::DetermineScreen(Screen *s) {
	int width = WidthOfScreen(s);
	int height = HeightOfScreen(s);
#ifdef DEBUG
	error("screen wxh = %dx%d\n", width, height);
#endif
	// Find out what popular resolution the screen has.
	if (width >= 1280 && height >= 1024)
		screenType = HP19;
	else if (width >= 1024 && height >= 1024)
		screenType = NCD16;
	else if (width >= 1152 && height >= 900)
		screenType = SUN17;
	else if (width >= 1024 && height >= 800)
		screenType = NCD19B;
	else if (width >= 1024 && height >= 768)
		screenType = XVGA;
	else if (width >= 800 && height >= 600)
		screenType = SVGA;
	else if (width >= 640 && height >= 480)
		screenType = VGA;
	else
		screenType = VGA;
}

void EditWindow::CreatePrinter() {
	if (check(document) && check(GetConfig()))
		printer = new Printer(GetConfig(), document);
}

void EditWindow::CreateHelper() {
	helper = new Helper(GetConfig(), this);
}

void EditWindow::Finalize() {
	document->UpdateWindow();
	if (projDir != "")
		document->NewDir(&projDir);
	SetStatus("");
	// if a file is given as command line option, try to load it.
	if (doLoad) {
		loadFile.setSuffix(*document->GetSuffix());
		if (System::FileExists(loadFile.getstr()))
			document->DoLoad(&loadFile);
		else {
			if (doMap)
				document->NewFile(&loadFile);
		}
	}
	// "send email on startup?"
	if (GetConfig()->GetSendEmailOnStartup()) {
		System::SendEmail(System::emailAddress, 
		    System::TOOLKIT_STAT_HEADER, Toolkit::TOOL_NAMES[GetTool()], 
		    Version::TOOLKIT_VERSION, "");
	}
	// generate PS, EPS, PNG or Fig??
	if (!doMap) {
		if (!doLoad) {
			std::cerr << "error: no document file name given" << std::endl;
			WriteUsage(Toolkit::EXECUTABLE_NAMES[GetTool()]);
		}
		else if (!document->IsLoaded()) {
			std::cerr << "error: incorrect or non-existent document " 
			        "file given" << std::endl;
			WriteUsage(Toolkit::EXECUTABLE_NAMES[GetTool()]);
		}
		else {
			if (generatePS)
				printer->SavePostScript(&psFile, False);
			if (generateEPS)
				printer->SaveEPS(&epsFile);
			if (generatePNG)
				printer->SavePNG(&pngFile);
			if (generateFig)
				printer->SaveFig(&figFile, generateLatexFonts);
		}
		Close();
	}
}

void EditWindow::SetStatus(const char *message) {
	if (statusText)
		XtVaSetValues(statusText, XmNvalue, message, NULL); 
}

void EditWindow::SetStatus(const string *message) {
	SetStatus(message->getstr());
}

void EditWindow::SetDocumentName(const char *s) {
	if (documentName) {
		int columns = min(30, max(10, strlen(s)+2));
		XtVaSetValues(documentName, XmNvalue, s, 
                              XmNcolumns, columns, NULL); 
		// show document name also in the icon.
		SetIconName(s); 
	}
}

void EditWindow::SetDocumentName(const string *s) {
	SetDocumentName(s->getstr());
}

void EditWindow::SetDocumentType(const char *s) {
	if (documentType) {
		int columns = min(30, max(10, strlen(s)+2));
		XtVaSetValues(documentType, XmNvalue, s,
				    XmNcolumns, columns, NULL); 
	}
}

void EditWindow::SetDocumentType(const string *s) {
	SetDocumentType(s->getstr());
}

void EditWindow::SetDirName(const char *s) {
	if (dirName) {
		int columns = min(30, max(10, strlen(s)+4));
		XtVaSetValues(dirName, XmNvalue, s,
				XmNcolumns, columns, NULL); 
	}
}

void EditWindow::SetDirName(const string *s) {
	SetDirName(s->getstr());
}

void EditWindow::SetModified(bool set) {
	if (modifiedToggle)
		XtVaSetValues(modifiedToggle, XmNset, set, NULL); 
}

void EditWindow::AboutCB(Widget w, XtPointer, XtPointer) {
	MessageDialog *t = new MessageDialog(w, MessageDialog::MESSAGE);
	t->Show("About TCM", Version::ABOUT_TEXT);
}

void EditWindow::SetDocumentLevel(const char *s) {
	if (documentLevel)
		XtVaSetValues(documentLevel, XmNvalue, s,
					    XmNcolumns, strlen(s)+1, NULL);
}

void EditWindow::SetDocumentLevel(const string *s) {
	SetDocumentLevel(s->getstr());
}

void EditWindow::SetPageSubMenuItem(const char *text, int n) {
	if (!pageMenu)
		return;
	Widget item = pageMenu->GetMenuItem(text);
	if (check(item))
		Menu::SetNthChildToggleState(
			item, Menu::PULLDOWN, n+1, True, True);
}

void EditWindow::SetPageMenuItem(const char *text, bool b) {
	if (!pageMenu)
		return;
	Menu::SetChildToggleState(pageMenu->GetWidget(), 
		Menu::PULLDOWN, text, b);
}
