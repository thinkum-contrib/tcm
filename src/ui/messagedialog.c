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
#include "messagedialog.h"
#include "util.h"
#include "mstring.h"
#include <Xm/XmAll.h>

MessageDialog::MessageDialog(Widget w): Dialog(w) {
	dialogType = MESSAGE;
	SetAutoUnmanage(True);
}

MessageDialog::MessageDialog(Widget w, DialogType t): Dialog(w) {
	dialogType = t;
}

void MessageDialog::SetMessageString(const string *s) {
	SetMessageString(s->getstr());
}

void MessageDialog::SetMessageString(const char *s) {
	XmString msg = CreateXmString(s);
	XtVaSetValues(GetWidget(), XmNmessageString, msg, 0);
	XmStringFree(msg);
}

void MessageDialog::Show(const char *title, const char *msg) {
	Initialize();
        SetTitle(title);
        SetMessageString(msg);
        Popup();
}

void MessageDialog::Show(const char *title, const string *msg) {
	Show(title, msg->getstr());
}

void MessageDialog::Popup() {
	Dialog::Popup();
	if (dialogType == ERROR) 
		XBell(XtDisplay(GetWidget()), 100);
	else if (dialogType == WARNING)
		XBell(XtDisplay(GetWidget()), 25);
}

void MessageDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	char wname[8] = "Dialog";
	switch (dialogType) {
	case INFORMATION:
		SetWidget(XmCreateInformationDialog(GetParent(), wname, args, i));
		break;
	case ERROR:
		SetWidget(XmCreateErrorDialog(GetParent(), wname, args, i));
		break;
	case WARNING:
		SetWidget(XmCreateWarningDialog(GetParent(), wname, args, i));
		break;
	case MESSAGE:
		SetWidget(XmCreateMessageDialog(GetParent(), wname, args, i));
		break;
	case QUESTION:
		SetWidget(XmCreateQuestionDialog(GetParent(), wname, args, i));
		break;
	case WORKING:
		SetWidget(XmCreateWorkingDialog(GetParent(), wname, args, i));
		break;
	default:
		error("%s, line %d: wrong case in switch statement\n", 
			__FILE__, __LINE__);
		return;
	}
}

void MessageDialog::Configure() {
	// remove the cancel and help button
	ManageCancelButton(False);
	ManageHelpButton(False);
	// if ok is pressed then dialog object is deleted.
	SetAutoDestroy(True);
}
