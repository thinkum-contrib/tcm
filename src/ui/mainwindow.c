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
#include "application.h"
#include "mainwindow.h"
#include "util.h"
#include "config.h"
#include "dumpwidgettree.h"
#include <Xm/XmAll.h>

MainWindow::MainWindow(const char *n): MWidget(n) {
	// Application object must exist before any MainWindow object
	if (check(theApplication)) 
		theApplication->RegisterWindow(this);
	config = 0;
	cursor = 0;
}

void MainWindow::Initialize(int argc, char **argv, Config *c) {
	// All toplevel windows in the MotifApp framework are 
	// implemented as popup shells 
	SetWidget(XtCreatePopupShell(GetName()->getstr(), 
	 	topLevelShellWidgetClass, theApplication->GetWidget(), 0, 0));
	XtVaSetValues(GetWidget(), XmNkeyboardFocusPolicy, XmPOINTER, 
		XmNmappedWhenManaged, False, 0);
	InstallDestroyHandler();
	// Use a Motif XmMainWindow widget to handle window layout
	main = XtCreateManagedWidget(GetName()->getstr(), xmMainWindowWidgetClass, 
			GetWidget(), 0, 0);
	cursor = new MouseCursor(main);
	CreateLiteClue();
	config = c;
	workarea = CreateWorkArea(main, argc, argv);  
	if(check(workarea)) {
		XtVaSetValues(main, XmNworkWindow, workarea, 0);
		if(!XtIsManaged(workarea))
			XtManageChild(workarea);
	}
#ifdef DUMPWIDGETTREE
	DumpWidgetTree::Dump(GetWidget());
#endif
}

MainWindow::~MainWindow() {
	// Unregister this window with the Application object
	theApplication->UnregisterWindow(this);
	if (cursor)
		delete cursor;
}

void MainWindow::Manage() {
	if (check(GetWidget()))
		XtPopup(GetWidget(), XtGrabNone);
	// Map the window, in case the window is iconified
	if (XtIsRealized(GetWidget()))
	 	XMapRaised(GetDisplay(), GetWindow());
	// set cursor shape.
	SetCursor(MouseCursor::LEFT_PTR);
}

void MainWindow::Unmanage() {
	if (check(GetWidget()))
		XtPopdown(GetWidget());
}

void MainWindow::ManageUnmapped() {
	XtVaSetValues(GetWidget(), XmNmappedWhenManaged, False, 0);
	MWidget::Manage();
}

void MainWindow::Iconify() {
	if (!check(GetWidget()))
		return;
	// Set the widget to have an initial iconic state
	// in case the base widget has not yet been realized
	XtVaSetValues(GetWidget(), XmNiconic, TRUE, 0);
	// If the widget has already been realized, iconify the window
	if (XtIsRealized(GetWidget()))
		XIconifyWindow(GetDisplay(), GetWindow(), 0);
}

void MainWindow::Close() {
	theApplication->CloseWindow(this);
}

void MainWindow::SetTitle(const char *title) {
	if (check(GetWidget()))
		XtVaSetValues(GetWidget(), XmNtitle, title, 0);
}

void MainWindow::SetTitle(const string *title) {
	SetTitle(title->getstr());
}

void MainWindow::SetIconName(const char *iconname) {
	if (check(GetWidget()))
		XtVaSetValues(GetWidget(), XmNiconName, iconname, 0);
}

void MainWindow::SetIconPixmap(Pixmap px) {
	if (!check(GetWidget()))
		return;
	XtVaSetValues(GetWidget(), XmNiconPixmap, px, 0);
}

PrinterOptions *MainWindow::GetPrinterOptions() {
	return theApplication->GetPrinterOptions();
}

void MainWindow::WidgetDestroyed() {
	Close();
}

