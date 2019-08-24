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
#include "drawwindow.h"
#include "drawingarea.h"
#include "mstring.h"
#include "menu.h"
#include "config.h"
#include "editstubs.h"
#include "helper.h"
#include "document.h"
#include "viewer.h"
#include "system.h"
#include "liteclue.h"
#include <stdlib.h>
#include <Xm/XmAll.h>

const int DrawWindow::MIN_DRAWING_SIZE = 200;

DrawWindow::DrawWindow(const char *n): EditWindow(n) {
	drawingArea = 0;
	scrolledWindow = 0;
	verticalScrollBar = 0;
	horizontalScrollBar = 0;
	scaleValue = 0;
	documentItems = 0;
	documentInfoItems = 0;
}

DrawWindow::~DrawWindow() {
	if (documentItems)
		delete documentItems;
	if (documentInfoItems)
		delete documentInfoItems;
	if (scaleItems)
		delete scaleItems;
}

void DrawWindow::ParseUserOptions(int argc, char **argv) {
	int n;
	SetArgsLeft(argc-1);
	EditWindow::ParseUserOptions(argc, argv);
	DetermineScrollSize(GetScreenType());
	initDrawingWidth = GetConfig()->GetDrawingWidth();
	initDrawingHeight = GetConfig()->GetDrawingHeight();
	maxDrawingWidth = GetConfig()->GetDrawingMaxWidth();
	maxDrawingHeight = GetConfig()->GetDrawingMaxHeight();
	// look for -drawing option to set initial drawing area size.
	if (System::FindArg(argv, argc, "-drawing", n)) {
		if (n < argc-1 && 
		    System::NxnParse(argv[n+1], initDrawingWidth, 
			    initDrawingHeight))
			SetArgsLeft(GetArgsLeft() - 2);
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	// look for -maxdrawing option to set maximal drawing area size.
	if (System::FindArg(argv, argc, "-maxdrawing", n)) {
		if (n < argc-1 && 
		    System::NxnParse(argv[n+1], maxDrawingWidth, 
				maxDrawingHeight))
			SetArgsLeft(GetArgsLeft() - 2);
		else {
			WriteUsage(argv[0]);
			exit(1);
		}
	}
	initDrawingWidth = max(initDrawingWidth, MIN_DRAWING_SIZE);
	initDrawingHeight = max(initDrawingHeight, MIN_DRAWING_SIZE);
	maxDrawingWidth = max(initDrawingWidth, maxDrawingWidth);
	maxDrawingHeight = max(initDrawingHeight, maxDrawingHeight);
}

void DrawWindow::WriteUsage(const char *prog) {
	EditWindow::WriteUsage(prog);
}

void DrawWindow::FitDocument() {
	if (drawingArea)
		drawingArea->FitDocument();
}

void DrawWindow::FitDocument(int wd, int ht) {
	if (drawingArea)
		drawingArea->FitDocument(wd, ht);
}
 
Widget DrawWindow::CreateScrolledWindow(Widget parent) {
	// create an automatic scrolling window of N by N cm.
	// (the clipped drawing area is M by M cm.). The window
	// is so attached that when the main window is resized the
	// scrolled window is also resized
	if (!check(parent))
		return 0;
	Widget sw = XtVaCreateManagedWidget("ScrolledWindow",
		xmScrolledWindowWidgetClass, parent,
		XmNheight, scrollHeight,
		XmNwidth, scrollWidth,
		XmNscrollingPolicy, XmAUTOMATIC,
		XmNscrollBarDisplayPolicy, XmAS_NEEDED,
		XmNrightAttachment, XmATTACH_FORM, NULL);
	if (GetDocumentArea())
		XtVaSetValues(sw, 
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, GetDocumentArea(), NULL);
	if (GetLogo())
		XtVaSetValues(sw, 
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, GetLogo(), NULL);
	if (GetStatusArea())
		XtVaSetValues(GetStatusArea(),
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopWidget, sw, NULL);
	else if (GetControlArea())
		XtVaSetValues(sw, 
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, GetControlArea(), NULL);
	else
		XtVaSetValues(sw, 
			XmNbottomAttachment, XmATTACH_FORM, NULL);
	XtVaGetValues(sw, XmNverticalScrollBar, &verticalScrollBar, NULL);
	XtVaGetValues(sw, XmNhorizontalScrollBar, &horizontalScrollBar, NULL);
	return sw;
}

void DrawWindow::ShowPosition(int x, int y) {
	if (!check(verticalScrollBar) || !check(horizontalScrollBar))
		return;
	int vincrement=0, vmaximum=0, vminimum=0, vpage_incr=0,
	    vslider_size=0, vvalue=0;
	int hincrement=0, hmaximum=0, hminimum=0, hpage_incr=0,
	    hslider_size=0, hvalue=0;
	XtVaGetValues(verticalScrollBar,
		XmNincrement, &vincrement,
		XmNmaximum, &vmaximum,
		XmNminimum, &vminimum,
		XmNpageIncrement, &vpage_incr,
		XmNsliderSize, &vslider_size,
		XmNvalue, &vvalue, NULL);
	XtVaGetValues(horizontalScrollBar,
		XmNincrement, &hincrement,
		XmNmaximum, &hmaximum,
		XmNminimum, &hminimum,
		XmNpageIncrement, &hpage_incr,
		XmNsliderSize, &hslider_size,
		XmNvalue, &hvalue, NULL);
	hvalue = min(hmaximum-hslider_size, max(0, (x - hslider_size/2)));
	XmScrollBarSetValues(horizontalScrollBar, hvalue, hslider_size,
			hincrement, hpage_incr, True);
	vvalue = min(vmaximum - vslider_size, max(0, (y - vslider_size/2)));
	XmScrollBarSetValues(verticalScrollBar, vvalue, vslider_size,
			vincrement, vpage_incr, True);
}

//
//static void get_sb(Widget w, XtPointer cd, XtPointer) {
//	int increment=0, maximum=0, minimum=0,page_incr=0,
//	    slider_size=0, value=0;
//	XtVaGetValues((Widget)cd,
//		XmNincrement, &increment,
//		XmNmaximum, &maximum,
//		XmNminimum, &minimum,
//		XmNpageIncrement, &page_incr,
//		XmNsliderSize, &slider_size,
//		XmNvalue, &value, NULL);
//}
//

Widget DrawWindow::CreateScaleValue(Widget parent) {
	if (!check(parent))
		return 0; 
	Widget z = XtVaCreateManagedWidget("ScaleValue",
		xmLabelWidgetClass, parent,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, scrolledWindow,
		XmNrightAttachment, XmATTACH_FORM, NULL);
	// XtAddCallback(z, XmNactivateCallback, get_sb, verticalScrollBar);
	AddLiteClue(z, 
		"Current scale percentage (Alt+L = larger, Alt+S = smaller)");
	return z;
}

void DrawWindow::SetScaleValue(const char *s) {
	if (scaleValue) {
		string text = "Scale: ";
		text += s;
		XmString label = CreateXmString(text.getstr());
		XtVaSetValues(scaleValue, XmNlabelString, label, NULL);
		XmStringFree(label);
	}
}

Widget DrawWindow::CreateControlArea(Widget parent) {
	Widget rc = EditWindow::CreateControlArea(parent);
	if (!(rc))
		return 0;
	if (arrowButtons)
		XtVaSetValues(rc, XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 20,
			XmNleftWidget, arrowButtons, NULL);
	autoResizeToggle = CreateToggle(rc, "autoresizing", 
			GetConfig()->GetAutoResizing(), 
			EditStubs::SetAutoResizeCB, 
			(XtPointer)GetDocument()->GetViewer());
	AddLiteClue(autoResizeToggle, 
		"When set, shapes resize themselves after text editing");
	inlineEditToggle = CreateToggle(rc, "in-line editor", 
		GetConfig()->GetInlineEditor(), EditStubs::SetInlineEditCB, 
		(XtPointer)GetDocument()->GetViewer());
	AddLiteClue(inlineEditToggle, 
		"When set, text is edited directly in the drawing area"
		" (in a separate window otherwise)");
	if ( Toolkit::HierarchicEditor(GetTool()) ) {
		hierarchicToggle = CreateToggle(rc, "hierarchic document",
			False,
			EditStubs::SetHierarchicCB, (XtPointer)GetDocument());
		AddLiteClue(hierarchicToggle,
			"When set, document may contain "
			"hierarchically related nodes");
	} else
		hierarchicToggle = 0;
	XtVaCreateManagedWidget("   Directory: ",
		xmLabelWidgetClass, rc,
		XmNalignment, XmALIGNMENT_BEGINNING, NULL);
	Widget dn = XtVaCreateManagedWidget("DirectoryName",
		xmTextFieldWidgetClass, rc,
		XmNeditable, True,
		XmNcursorPositionVisible, True, NULL);
	SetDirName(dn);
	AddLiteClue(dn, "Current project directory. Can be changed "
		"(apply with <enter>)");
	if (GetScreenType() <= SVGA)
		XtVaSetValues(dn, XmNcolumns, 28, NULL);
	else if (GetScreenType() == XVGA)
		XtVaSetValues(dn, XmNcolumns, 34, NULL);
	else
		XtVaSetValues(dn, XmNcolumns, 40, NULL);
	XtAddCallback(dn, XmNactivateCallback,
		EditStubs::ChangeDirCB, (XtPointer)GetDocument());
	XtManageChild(rc);
	return rc;
}

Widget DrawWindow::CreateArrowButtonSquare(Widget parent) {
	Widget frame = XtVaCreateManagedWidget("ArrowsFrame",
		xmFrameWidgetClass, parent, 
		XmNbottomAttachment, XmATTACH_FORM,
		XmNleftAttachment, XmATTACH_FORM, NULL);
	Widget form = XtVaCreateManagedWidget("ArrowsForm", 
		xmFormWidgetClass, frame, 
		XmNfractionBase, 3, NULL);
	Widget a1 = XtVaCreateManagedWidget(
		"arrow1", xmArrowButtonWidgetClass, form,
		XmNtopPosition, 0,
		XmNbottomPosition, 1,
		XmNleftPosition, 1,
		XmNrightPosition, 2,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNarrowDirection, XmARROW_UP,
		XmNuserData, Document::UP, NULL);
	Widget a2 = XtVaCreateManagedWidget(
		"arrow2", xmArrowButtonWidgetClass, form,
		XmNtopPosition, 1,
		XmNbottomPosition, 2,
		XmNleftPosition, 0,
		XmNrightPosition, 1,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNarrowDirection, XmARROW_LEFT,
		XmNuserData, (XtPointer)Document::LEFT, NULL);
	Widget a3 = XtVaCreateManagedWidget(
		"arrow3", xmArrowButtonWidgetClass, form,
		XmNtopPosition, 1,
		XmNbottomPosition, 2,
		XmNleftPosition, 2,
		XmNrightPosition, 3,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNarrowDirection, XmARROW_RIGHT,
		XmNuserData, (XtPointer)Document::RIGHT, NULL);
	Widget a4 = XtVaCreateManagedWidget(
		"arrow4", xmArrowButtonWidgetClass, form,
		XmNtopPosition, 2,
		XmNbottomPosition, 3,
		XmNleftPosition, 1,
		XmNrightPosition, 2,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNarrowDirection, XmARROW_DOWN,
		XmNuserData, (XtPointer)Document::DOWN, NULL);
	XmString c = CreateXmString("C");
	Widget a5 = XtVaCreateManagedWidget(
		"arrow5", xmPushButtonWidgetClass, form,
		XmNlabelString, c,
		XmNtopPosition, 1,
		XmNbottomPosition, 2,
		XmNleftPosition, 1,
		XmNrightPosition, 2,
		XmNtopAttachment, XmATTACH_POSITION,
		XmNbottomAttachment, XmATTACH_POSITION,
		XmNrightAttachment, XmATTACH_POSITION,
		XmNleftAttachment, XmATTACH_POSITION,
		XmNuserData, (XtPointer)Document::CENTER, NULL);
	XmStringFree(c);
	AddLiteClue(a1, "Move the document one step up");
	AddLiteClue(a2, "Move the document one step left");
	AddLiteClue(a3, "Move the document one step right");
	AddLiteClue(a4, "Move the document one step down");
	AddLiteClue(a5, "Center the document on the page");
	if (check(GetDocument())) {
		XtAddCallback(a1, XmNactivateCallback, 
			EditStubs::MoveCB, (XtPointer)GetDocument());
		XtAddCallback(a2, XmNactivateCallback, 
			EditStubs::MoveCB, (XtPointer)GetDocument());
		XtAddCallback(a3, XmNactivateCallback, 
			EditStubs::MoveCB, (XtPointer)GetDocument());
		XtAddCallback(a4, XmNactivateCallback, 
			EditStubs::MoveCB, (XtPointer)GetDocument());
		XtAddCallback(a5, XmNactivateCallback, 
			EditStubs::MoveCB, (XtPointer)GetDocument());
	}
	return frame;
}

void DrawWindow::EnableUndo(bool flag) {
	EditWindow::EnableUndo(flag);
	if (drawingArea)
		drawingArea->EnableUndo(flag);
}

void DrawWindow::EnableRedo(bool flag) {
	EditWindow::EnableRedo(flag);
	if (drawingArea)
		drawingArea->EnableRedo(flag);
}

void DrawWindow::SetUndoName(const char *uname) {
	EditWindow::SetUndoName(uname);
	if (drawingArea)
		drawingArea->SetUndoName(uname);
}

void DrawWindow::SetRedoName(const char *uname) {
	EditWindow::SetRedoName(uname);
	if (drawingArea)
		drawingArea->SetRedoName(uname);
}

void DrawWindow::DetermineScrollSize(ScreenType s) {
	if (s == HP19) {
		scrollWidth = 816;
		scrollHeight = 680;
	}
	else if (s == NCD16) {
		scrollWidth = 724;
		scrollHeight = 680;
	}
	else if (s == SUN17) {
		scrollWidth = 724;
		scrollHeight = 660;
	}
	else if (s == NCD19B) {
		scrollWidth = 624;
		scrollHeight = 580;
	}
	else if (s == XVGA) {
		scrollWidth = 624;
		scrollHeight = 550;
	}
	else if (s == SVGA) {
		scrollWidth = 510;
		scrollHeight = 403;
	}
	else if (s == VGA) {
		scrollWidth = 418;
		scrollHeight = 306;
	}
	else if (s == EGA) {
		scrollWidth = 300;
		scrollHeight = 200;
	}
#ifdef DEBUG
	error("scroll wxh = %dx%d\n", scrollWidth, scrollHeight);
#endif
}

void DrawWindow::SetAutoResize(bool set) {
	if (autoResizeToggle)
		XtVaSetValues(autoResizeToggle, XmNset, set, NULL);
}

void DrawWindow::SetInlineEdit(bool set) {
	if (inlineEditToggle)
		XtVaSetValues(inlineEditToggle, XmNset, set, NULL); 
}


/* virtual */ void DrawWindow::SetHierarchic(bool set) {
	if ( hierarchicToggle )
		XtVaSetValues(hierarchicToggle, XmNset, set, NULL);
}


void DrawWindow::CreateDrawingArea() {
	drawingArea = new DrawingArea(
			GetConfig(), scrolledWindow, "DrawingArea", this);
}

void DrawWindow::Finalize() {
	EditWindow::Finalize();
	SetScaleValue("100%");
}

void DrawWindow::InitMenuItems() {
	// All menu-items of the application and their stub functions
	int i = 0;
	fileItems = new MenuItem[25]; i = 0;
	fileItems[i] = MenuItem( 
		"New", MenuItem::PUSHBUTTON, 'N', "Ctrl<Key>N", "Ctrl+N", 
		EditStubs::NewCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Load...", MenuItem::PUSHBUTTON, 'L', "Ctrl<Key>L", "Ctrl+L", 
		EditStubs::LoadCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Append...", MenuItem::PUSHBUTTON, 'A', "Ctrl<Key>A", "Ctrl+A", 
		EditStubs::AppendCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	fileItems[i] = MenuItem(
		"Save", MenuItem::PUSHBUTTON, 'v', 0, 0, 
		EditStubs::SaveCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Save As...", MenuItem::PUSHBUTTON, 'S', 
		"Ctrl<Key>S", "Ctrl+S", EditStubs::SaveAsCB, 
		(XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Save Selection As...", MenuItem::PUSHBUTTON, 'e', 0,0,
		EditStubs::SaveSelectionAsCB, (XtPointer)GetDocument(), 
		0, 0, 1); i++;
	fileItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	fileItems[i] = MenuItem(
	 	"Quit", MenuItem::PUSHBUTTON, 'Q', "Ctrl<Key>Q", "Ctrl+Q", 
		EditStubs::QuitCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	fileItems[i] = MenuItem::NUL;

	pageSizeItems = new MenuItem[10]; i = 0;
	pageSizeItems[i] = MenuItem(
		"A3 (297 x 420 mm)", MenuItem::RADIOBUTTON, '3', 0, 0, 
		EditStubs::PageSizeCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPageSize()==PageSize::A3), 0, 1); i++;
	pageSizeItems[i] = MenuItem(
		"A4 (210 x 297 mm)", MenuItem::RADIOBUTTON, 'A', 0, 0, 
		EditStubs::PageSizeCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPageSize()==PageSize::A4), 0, 1); i++;
	pageSizeItems[i] = MenuItem(
		"Letter (8 1/2 x 11 in.)", MenuItem::RADIOBUTTON, 'L', 0, 0, 
		EditStubs::PageSizeCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPageSize()==PageSize::LETTER), 0, 1); i++;
	pageSizeItems[i] = MenuItem(
		"Legal (8 1/2 x 14 in.)", MenuItem::RADIOBUTTON, 'g', 0, 0, 
		EditStubs::PageSizeCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPageSize()==PageSize::LEGAL), 0, 1); i++;
	pageSizeItems[i] = MenuItem(
		"Executive (7 1/2 x 10 in.)", MenuItem::RADIOBUTTON, 'E', 0, 0, 
		EditStubs::PageSizeCB, (XtPointer)GetPrinter(),
		(XtPointer)(GetConfig()->GetPageSize()==PageSize::EXECUTIVE), 0, 1); i++;
	pageSizeItems[i] = MenuItem::NUL;

	bannerPageItems = new MenuItem[10]; i = 0;
	bannerPageItems[i] = MenuItem(
		"Print Default Banner Page", MenuItem::RADIOBUTTON, 'D', 0, 0, 
		EditStubs::BannerPageCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i+(GetConfig()->GetBannerPage()==Config::DEF_BANNER)), 
		0, 1); i++;
	bannerPageItems[i] = MenuItem(
		"Print No Banner Page", MenuItem::RADIOBUTTON, 'N', 0, 0, 
		EditStubs::BannerPageCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i+(GetConfig()->GetBannerPage()==Config::NO_BANNER)), 
		0, 1); i++;
	bannerPageItems[i] = MenuItem(
		"Print TCM Banner Page", MenuItem::RADIOBUTTON, 'T', 0, 0, 
		EditStubs::BannerPageCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i+(GetConfig()->GetBannerPage()==Config::TCM_BANNER)), 
		0, 1); i++;
	bannerPageItems[i] = MenuItem::NUL;

	printerOptionsItems = new MenuItem[25]; i=0;
	printerOptionsItems[i] = MenuItem(
		"Printer Name...", MenuItem::PUSHBUTTON, 'N', 0, 0, 
		EditStubs::PrinterNameCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Number of Copies...", MenuItem::PUSHBUTTON, 'o', 0, 0, 
		EditStubs::PrinterCopiesCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printerOptionsItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	printerOptionsItems[i] = MenuItem(
		"Print Command...", MenuItem::PUSHBUTTON, 'P', 0, 0, 
		EditStubs::PrintCommandCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Printer Queue Command...", MenuItem::PUSHBUTTON, 'Q', 0, 0, 
		EditStubs::PrinterQueueCommandCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Printer Remove Command...", MenuItem::PUSHBUTTON, 'R', 0, 0, 
		EditStubs::PrinterRemoveCommandCB, (XtPointer)GetPrinter(), 
		0, 0, 1);
		i++;
	printerOptionsItems[i] = MenuItem(
		"Preview Command...", MenuItem::PUSHBUTTON, 'v', 0, 0, 
		EditStubs::PreviewCommandCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printerOptionsItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	printerOptionsItems[i] = MenuItem(
		"Print Colors", MenuItem::CHECKBUTTON, 'C', 0, 0, 
		EditStubs::SetPrintColorsCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPrintColors()), 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Print Duplex Pages", MenuItem::CHECKBUTTON, 'D', 0, 0, 
		EditStubs::SetDuplexCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPrintDuplexPages()), 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Print Tumbled Pages", MenuItem::CHECKBUTTON, 'T', 0, 0, 
		EditStubs::SetTumbleCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetPrintTumbledPages()), 0, 1); i++;
	printerOptionsItems[i] = MenuItem(
		"Print Banner Page Options", MenuItem::SUBMENU, 'B', 0, 0, 
		0, 0, 0, bannerPageItems, 1); i++;
	printerOptionsItems[i] = MenuItem::NUL;

	printItems = new MenuItem[25]; i=0;
	printItems[i] = MenuItem(
		"Print", MenuItem::PUSHBUTTON, 'P', "Ctrl<Key>P", "Ctrl+P", 
		EditStubs::PrintCB, (XtPointer)GetPrinter(), 0, 0, 1); i++;
	printItems[i] = MenuItem(
		"Export...", MenuItem::PUSHBUTTON, 'E', "Ctrl<Key>E", "Ctrl+E",
		EditStubs::ExportAsCB, (XtPointer)GetPrinter(), 0, 0, 1); i++;
	printItems[i] = MenuItem(
		"Show Preview...", MenuItem::PUSHBUTTON, 'S', 0, 0,
		EditStubs::ShowPrintPreviewCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printItems[i] = MenuItem(
		"Printer Queue...", MenuItem::PUSHBUTTON, 'Q', 0, 0, 
		EditStubs::ShowPrinterQueueCB, (XtPointer)GetPrinter(), 
		0, 0, 1); i++;
	printItems[i] = MenuItem(
		"Printer Properties", MenuItem::SUBMENU, 'O', 0, 0, 
		0, 0, 0, printerOptionsItems, 1); i++;
	printItems[i] = MenuItem::NUL;

	searchItems = new MenuItem[25]; i=0;
	searchItems[i] = MenuItem(
		"Find...", MenuItem::PUSHBUTTON, 'F', "Ctrl<Key>F", "Ctrl+F",
		EditStubs::FindCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	searchItems[i] = MenuItem(
		"Replace...", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>Z", "Ctrl+Z",
		EditStubs::ReplaceCB, (XtPointer)GetDocument(), 0, 0, 1); i++;
	searchItems[i] = MenuItem::NUL;

	toolIntroMenuLabel = "Introduction to ";
	toolIntroMenuLabel += Toolkit::TOOL_NAMES[GetTool()];
	
	helpItems = new MenuItem[25]; i=0;
	helpItems[i] = MenuItem(
		"Getting Started", MenuItem::PUSHBUTTON, 'G', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(), 
		(XtPointer)Helper::GETTING_STARTED, 0, 1); i++;
	helpItems[i] = MenuItem(
		(char *)toolIntroMenuLabel.getstr(), MenuItem::PUSHBUTTON, 
		'T', 0, 0, EditStubs::HelpCB, (XtPointer)GetHelper(), 
		(XtPointer)Helper::TOOL_INTRO, 0, 1); i++;
	helpItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	helpItems[i] = MenuItem(
		"Main Window", MenuItem::PUSHBUTTON, 'W', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::THE_MAIN_WINDOW, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Mouse Commands", MenuItem::PUSHBUTTON, 'M', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::MOUSE_COMMANDS, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Edit Menu Commands", MenuItem::PUSHBUTTON, 'E', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::EDIT_COMMANDS, 0, 1); i++;
	helpItems[i] = MenuItem(
		"File Menu Commands", MenuItem::PUSHBUTTON, 'F', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::FILE_COMMANDS, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Print & Page Commands", MenuItem::PUSHBUTTON, 'P', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::PRINT_PAGE_COMMANDS, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Miscellaneous Commands", MenuItem::PUSHBUTTON, 'i', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::MISC_COMMANDS, 0, 1); i++;
	helpItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	helpItems[i] = MenuItem(
		"Version", MenuItem::PUSHBUTTON, 'V', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(), 
		(XtPointer)Helper::VERSION, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Copying", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::COPYING, 0, 1); i++;
	helpItems[i] = MenuItem(
		"Change Log", MenuItem::PUSHBUTTON, 'L', 0, 0, 
		EditStubs::HelpCB, (XtPointer)GetHelper(),
		(XtPointer)Helper::CHANGELOG, 0, 1); i++;
	helpItems[i] = MenuItem::NUL;

	pageOrientationItems = new MenuItem[10]; i=0;
	pageOrientationItems[i] = MenuItem(
		"Portrait", MenuItem::RADIOBUTTON, 'P', 0, 0, 
		EditStubs::PageOrientationCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i+(GetConfig()->GetPageOrientation()==
		Config::PORTRAIT)), 0, 1); i++;
	pageOrientationItems[i] = MenuItem(
		"Landscape", MenuItem::RADIOBUTTON, 'L', 0, 0, 
		EditStubs::PageOrientationCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i+(GetConfig()->GetPageOrientation()==
		Config::LANDSCAPE)), 0, 1); i++;
	pageOrientationItems[i] = MenuItem::NUL;

	documentInfoItems = new MenuItem[10]; i=0;
	documentInfoItems[i] = MenuItem(
		"None", MenuItem::RADIOBUTTON, 'N', 0, 0, 
		EditStubs::ShowDocumentInfoCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i + (!GetConfig()->GetShowDocumentInfoAsHeader() && 
		!GetConfig()->GetShowDocumentInfoAsFooter())), 0, 1); i++;
	documentInfoItems[i] = MenuItem(
		"As Header", MenuItem::RADIOBUTTON, 'H', 0, 0, 
		EditStubs::ShowDocumentInfoCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i + GetConfig()->GetShowDocumentInfoAsHeader()), 
		0, 1); i++;
	documentInfoItems[i] = MenuItem(
		"As Footer", MenuItem::RADIOBUTTON, 'F', 0, 0, 
		EditStubs::ShowDocumentInfoCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i + GetConfig()->GetShowDocumentInfoAsFooter()), 
		0, 1); i++;
	documentInfoItems[i] = MenuItem(
		"Both Header & Footer", MenuItem::RADIOBUTTON, 'B', 0, 0, 
		EditStubs::ShowDocumentInfoCB, (XtPointer)GetPrinter(), 
		(XtPointer)(2*i + (GetConfig()->GetShowDocumentInfoAsHeader() && 
		GetConfig()->GetShowDocumentInfoAsFooter())), 0, 1); i++;
	documentInfoItems[i] = MenuItem::NUL;

	pageItems = new MenuItem[10]; i=0;
	pageItems[i] = MenuItem(
		"Show Page Boundary", MenuItem::CHECKBUTTON, 'B', 0, 0, 
		EditStubs::ShowPageBoundaryCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetShowPageBoundary()), 0, 1); i++;
	pageItems[i] = MenuItem(
		"Page Orientation", MenuItem::SUBMENU, 'O', 0, 0, 
		0, 0, 0, pageOrientationItems, 1); i++;
	pageItems[i] = MenuItem(
		"Page Size", MenuItem::SUBMENU, 'S', 0, 0, 
		0, 0, 0, pageSizeItems, 1); i++;
	pageItems[i] = MenuItem("", MenuItem::SEPARATOR);
	pageItems[i] = MenuItem(
		"Include Page Numbers", MenuItem::CHECKBUTTON, 'P', 0, 0, 
		EditStubs::ShowPageNumbersCB, (XtPointer)GetPrinter(), 
		(XtPointer)(GetConfig()->GetIncludePageNumbers()), 0, 1); i++;
	pageItems[i] = MenuItem(
		"Include Document Info", MenuItem::SUBMENU, 'D', 0, 0, 
		0, 0, 0, documentInfoItems, 1); i++;
	pageItems[i] = MenuItem::NUL;

	documentItems = new MenuItem[25]; i=0;
	documentItems[i] = MenuItem(
		"Document Info...", MenuItem::PUSHBUTTON, 'I', 0, 0, 
		EditStubs::DocumentInfoCB, (XtPointer)GetDocument(), 
		0, 0, 1); i++;
	documentItems[i] = MenuItem(
		"Document Source...", MenuItem::PUSHBUTTON, 'S', 0, 0,
		EditStubs::DocumentSourceCB, (XtPointer)GetDocument(),
		0, 0, 0); i++;
	documentItems[i] = MenuItem(
		"Document Annotation ...", MenuItem::PUSHBUTTON, 'A', 0, 0,
		EditStubs::AnnotateDocumentCB, (XtPointer)GetDocument(),
		0, 0, 1); i++;
	if (!Toolkit::GenericEditor(GetTool())) {
		documentItems[i] = MenuItem(
		"Check Document Syntax...", MenuItem::PUSHBUTTON, 'C', 0, 0, 
		EditStubs::CheckDocumentCB, (XtPointer)GetDocument(), 
		0, 0, 1); i++;

		if ( Toolkit::EditorWithModelChecker(GetTool()) ) {
			documentItems[i] = MenuItem(
			"Model Check Property...",
			MenuItem::PUSHBUTTON, 'M', 0, 0,           
			EditStubs::ModelCheckPropertyCB,
			(XtPointer)GetDocument(), 0, 0, 1); i++;
                        documentItems[i] = MenuItem(
                        "Clear Trace",
                        MenuItem::PUSHBUTTON, 'C', 0, 0,
                        EditStubs::ClearTraceCB,
                        (XtPointer)GetDocument(), 0, 0, 1); i++;

		}
	}
	if ( Toolkit::HierarchicEditor(GetTool()) ) {
		documentItems[i] = MenuItem(
			"Hierarchic Document", MenuItem::CHECKBUTTON, 'H', 0, 0,
			EditStubs::SetHierarchicCB, (XtPointer)GetDocument(), 
			(XtPointer) False, 0, 1); i++;
	}
	documentItems[i] = MenuItem::NUL;

	scaleItems = new MenuItem[10]; i=0;
	scaleItems[i] = MenuItem(
		"Make Larger", MenuItem::PUSHBUTTON, 'L', "Alt<Key>L", "Alt+L", 
		EditStubs::MakeLargerCB, 
		(XtPointer)GetDocument()->GetViewer()->GetScaler(), 
		0, 0, 1); i++;
	scaleItems[i] = MenuItem(
		"Make Smaller", MenuItem::PUSHBUTTON, 'S', "Alt<Key>S", "Alt+S",
		EditStubs::MakeSmallerCB, 
		(XtPointer)GetDocument()->GetViewer()->GetScaler(), 
		0, 0, 1); i++;
	scaleItems[i] = MenuItem(
		"Normal Scale", MenuItem::PUSHBUTTON, 'N', "Alt<Key>N", "Alt+N",
		EditStubs::NormalScaleCB, 
		(XtPointer)GetDocument()->GetViewer()->GetScaler(), 
		0, 0, 1); i++;
	scaleItems[i] = MenuItem(
		"Whole Drawing", MenuItem::PUSHBUTTON, 'W', 
		"Alt<Key>W", "Alt+W", EditStubs::WholeDrawingCB, 
		(XtPointer)GetDocument()->GetViewer()->GetScaler(), 
		0, 0, 1); i++;
	scaleItems[i] = MenuItem("", MenuItem::SEPARATOR);
	scaleItems[i] = MenuItem(
		"Scale Factor...", MenuItem::PUSHBUTTON, 'F', 
		"Alt<Key>F", "Alt+F", EditStubs::ScaleFactorCB, 
		(XtPointer)GetDocument()->GetViewer()->GetScaler(), 
		0, 0, 1); i++;
	scaleItems[i] = MenuItem::NUL;
}

void DrawWindow::EnableDocumentSource(bool flag) {
        if (!documentMenu)
                return;
        Widget docMenuItem = documentMenu->GetMenuItem("Document Source...");
        if (docMenuItem)
                XtVaSetValues(docMenuItem, XmNsensitive, flag, NULL);
}
