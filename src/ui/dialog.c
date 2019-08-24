////////////////////////////////////////////////////////////////////////////////
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
#include "dialog.h"
#include "util.h"
#include "mstring.h"
#include <Xm/XmAll.h>

const unsigned Dialog::MAXTITLE = 64;

Dialog::Dialog(Widget w): MWidget("Dialog") {
	parent = w;
	autoDestroy = False;
	autoUnmanage = True;
	centeredOnPointer = True;
}

Dialog::~Dialog() { 
}

void Dialog::Initialize() {
	CreateWidget();
	CreateLiteClue();
	Configure();
}

void Dialog::SetTitle(const char *title) {
	if (!check(GetWidget()))
		return;
	char t[MAXTITLE];
	strncpy(t, title, MAXTITLE-1);
	t[MAXTITLE-1] = '\0';
	XmString s = CreateXmString(t);
	XtVaSetValues(GetWidget(), XmNdialogTitle, s, NULL);
	XmStringFree(s);
}

void Dialog::SetTitle(const string *title) {
	SetTitle(title->getstr());
}

void Dialog::GetTitle(char *title) {
	if (!check(GetWidget()))
		return;
	XmString s = CreateXmString("");
	XtVaGetValues(GetWidget(), XmNdialogTitle, &s, NULL);
	char *str;
	if (XmStringGetLtoR(s, XmFONTLIST_DEFAULT_TAG, &str)) {
		strncpy(title, str, MAXTITLE-1);
		if (strlen(title) >= MAXTITLE)
			title[MAXTITLE-1] = '\0';
		XtFree(str);
	}
	XmStringFree(s);
}

void Dialog::GetTitle(string *title) {
	char t[MAXTITLE];
	GetTitle(t);
	*title = t;
}

void Dialog::SetModal(bool b) {
	if (!check(GetWidget()))
		return;
	XtVaSetValues(GetWidget(), 
		XmNdialogStyle, 
		(b?XmDIALOG_FULL_APPLICATION_MODAL:XmDIALOG_MODELESS), 
		NULL);
}

void Dialog::SetAutoUnmanage(bool b) {
	autoUnmanage = b;
	if (GetWidget())
		XtVaSetValues(GetWidget(), XmNautoUnmanage, b, NULL);
}

void Dialog::SetOKCallback(XtCallbackProc fun, XtPointer clientData) {
	if (!check(GetWidget()))
		return;
	XtRemoveAllCallbacks(GetWidget(), XmNokCallback);
	if (fun)
		XtAddCallback(GetWidget(), XmNokCallback, fun, clientData);
	if (autoDestroy)
		XtAddCallback(GetWidget(), XmNokCallback,
			&Dialog::DestroyWidgetCB, 0);
}

void Dialog::SetCancelCallback(XtCallbackProc fun, XtPointer clientData) {
	if (!check(GetWidget()))
		return;
	XtRemoveAllCallbacks(GetWidget(), XmNcancelCallback);
	if (fun)
		XtAddCallback(GetWidget(), XmNcancelCallback, fun, clientData);
	if (autoDestroy)
		XtAddCallback(GetWidget(), XmNcancelCallback,
			&Dialog::DestroyWidgetCB, 0);
}

void Dialog::SetHelpCallback(XtCallbackProc fun, XtPointer clientData) {
	if (!check(GetWidget()))
		return;
	XtRemoveAllCallbacks(GetWidget(), XmNhelpCallback);
	if (fun)
		XtAddCallback(GetWidget(), XmNhelpCallback, fun, clientData);
}

void Dialog::SetOKButtonLabel(const char *txt) {
	if (!check(GetWidget()))
		return;
	XmString t = CreateXmString(txt);
	XtVaSetValues(GetWidget(), XmNokLabelString, t, NULL);
	XmStringFree(t);
}

void Dialog::SetCancelButtonLabel(const char *txt) {
	if (!check(GetWidget()))
		return;
	XmString t = CreateXmString(txt);
	XtVaSetValues(GetWidget(), XmNcancelLabelString, t, NULL);
	XmStringFree(t);
}

void Dialog::SetHelpButtonLabel(const char *txt) {
	if (!check(GetWidget()))
		return;
	XmString t = CreateXmString(txt);
	XtVaSetValues(GetWidget(), XmNhelpLabelString, t, NULL);
	XmStringFree(t);
}

void Dialog::ManageWidget(Widget w, bool b) {
	if (b)
		XtManageChild(w);
	else
		XtUnmanageChild(w);
}

void Dialog::ManageOKButton(bool b) {
	Widget button;
	if (XmIsMessageBox(GetWidget()))
		button = XmMessageBoxGetChild(GetWidget(), XmDIALOG_OK_BUTTON);
	else
		button = XmSelectionBoxGetChild(GetWidget(), 
					XmDIALOG_OK_BUTTON);
	ManageWidget(button, b);
}

void Dialog::ManageCancelButton(bool b) {
	Widget button;
	if (XmIsMessageBox(GetWidget()))
		button = XmMessageBoxGetChild(GetWidget(), 
					XmDIALOG_CANCEL_BUTTON);
	else
		button = XmSelectionBoxGetChild(GetWidget(), 
					XmDIALOG_CANCEL_BUTTON);
	ManageWidget(button, b);
}

void Dialog::ManageHelpButton(bool b) {
	Widget button;
	if (XmIsMessageBox(GetWidget()))
		button = XmMessageBoxGetChild(GetWidget(), 
					XmDIALOG_HELP_BUTTON);
	else
		button = XmSelectionBoxGetChild(GetWidget(), 
					XmDIALOG_HELP_BUTTON);
	ManageWidget(button, b);
}

void Dialog::Popup() {
	if (!check(GetWidget()))
		return;
	if (centeredOnPointer)
		ManageCenteredOnPointer();
	else
		Manage();
	XtPopup(XtParent(GetWidget()), XtGrabNone);
	XMapRaised(GetDisplay(), XtWindow(XtParent(GetWidget())));
}

void Dialog::Popdown() {
	if (!check(GetWidget()))
		return;
	XtPopdown(XtParent(GetWidget()));
}

void Dialog::SetAutoDestroy(bool b) {
	if (!check(GetWidget()))
		return;
	autoDestroy = b;
	if (b) {
		XtAddCallback(GetWidget(), XmNokCallback,
			&Dialog::DestroyWidgetCB, 0);
		XtAddCallback(GetWidget(), XmNcancelCallback,
			&Dialog::DestroyWidgetCB, 0);
		XtAddCallback(GetWidget(), XmNdestroyCallback,
			&Dialog::DestroyCB, (XtPointer)this);
		XtVaSetValues(GetWidget(), XmNdeleteResponse, XmDESTROY, NULL);
	}
	else {
		XtRemoveCallback(GetWidget(), XmNokCallback,
			&Dialog::DestroyWidgetCB, 0);
		XtRemoveCallback(GetWidget(), XmNcancelCallback,
			&Dialog::DestroyWidgetCB, 0);
		XtRemoveCallback(GetWidget(), XmNdestroyCallback,
			&Dialog::DestroyCB, (XtPointer)this);
		XtVaSetValues(GetWidget(), XmNdeleteResponse, XmUNMAP, NULL);
	}
}

void Dialog::UnmanageCB(Widget w, XtPointer, XtPointer) {
	if (check(w))
		XtUnmanageChild(w);
}

void Dialog::DestroyWidgetCB(Widget w, XtPointer, XtPointer) {
	if (check(w))
		XtDestroyWidget(w);
	w = 0;
}

void Dialog::TraverseNextCB(Widget w, XtPointer, XtPointer) {
	XmProcessTraversal(w, XmTRAVERSE_NEXT);
}

void Dialog::TraverseNextGroupCB(Widget w, XtPointer, XtPointer) {
	XmProcessTraversal(w, XmTRAVERSE_NEXT_TAB_GROUP);
}

void Dialog::DestroyCB(Widget, XtPointer cd, XtPointer) {
	Dialog *d = (Dialog *)cd;
	if (check(d))
		delete d;
}

// ManageDialogCenteredOnPointer is used in place of XtManageChild for
// popping up a dialog to enable the dialog to be centered under the
// mouse pointer.  Whether it pops up the dialog centered under the pointer
// or in its default position centered over the parent widget, depends on
// the value set in the SetPointerCenteredDialogs call.
void Dialog::ManageCenteredOnPointer() {
	if (!check(GetWidget()))
		return;
	Widget shell = XtParent(GetWidget());
    	// If this feature is not enabled, just manage the dialog.
	if (!centeredOnPointer) {
		Manage();
		return;
	}
	// Temporarily set value of XmNmappedWhenManaged
	//   to stop the dialog from popping up right away
	bool mappedWhenManaged = False;
	XtVaGetValues(shell, XmNmappedWhenManaged, &mappedWhenManaged, NULL);
	XtVaSetValues(shell, XmNmappedWhenManaged, False, NULL);
	// Manage the dialog
	XtManageChild(GetWidget());
	// Get the pointer position (x, y)
	Window root, child;
	unsigned int mask;
	unsigned int width, height, borderWidth, depth;
	int x, y, winX, winY, maxX, maxY;
	XQueryPointer(XtDisplay(shell), XtWindow(shell), &root, &child,
			&x, &y, &winX, &winY, &mask);
	// Translate the pointer position (x, y) into a position for the new
	// window that will place the pointer at its center.
	XGetGeometry(XtDisplay(shell), XtWindow(shell), &root, &winX, &winY,
			&width, &height, &borderWidth, &depth);
	width += 2 * borderWidth;
	height += 2 * borderWidth;
	x -= width/2;
	y -= height/2;
	// Ensure that the dialog remains on screen
	maxX = XtScreen(shell)->width - width;
	maxY = XtScreen(shell)->height - height;
	if (x < 0) 
		x = 0;
	if (x > maxX) 
		x = maxX;
	if (y < 0) 
		y = 0;
	if (y > maxY) 
		y = maxY;
	// Set desired window position in the DialogShell.
	XtVaSetValues(shell, XmNx, x, XmNy, y, NULL);
	// Map the widget
	XtMapWidget(shell);
	// Restore the value of XmNmappedWhenManaged
	XtVaSetValues(shell, XmNmappedWhenManaged, mappedWhenManaged, NULL);
}
