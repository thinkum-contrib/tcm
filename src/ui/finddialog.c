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
#include "finddialog.h"
#include "mstring.h"
#include <Xm/XmAll.h>

FindDialog::FindDialog(Widget w): SelectionDialog(w) { 
	SetAutoUnmanage(False);
}

bool FindDialog::SensitiveOn() {
	return XmToggleButtonGetState(sensitiveToggle);
}

bool FindDialog::SubstringOn() {
	return XmToggleButtonGetState(substringToggle);
}

bool FindDialog::NameOnlyOn() {
	return XmToggleButtonGetState(nameOnlyToggle);
}

void FindDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void FindDialog::Configure() {
	SelectionDialog::Configure();
	SetCancelCallback(FindDialog::UnmanageCB, this);
	SetCancelButtonLabel("Dismiss");
	ManageHelpButton(True);
	SetHelpButtonLabel("Clear");
	SetHelpCallback(FindDialog::ClearCB, this);
	SetOKButtonLabel("Find\nNext");
	ManageApplyButton(True);
	SetApplyButtonLabel("Find\nAll");

	ManageTextString(False);
	ManageSelectionLabel(False);

	form = XtVaCreateWidget("form",
		xmFormWidgetClass, GetWidget(), NULL);
	SetSelectionLabel(XtVaCreateManagedWidget("String to Find",
		xmLabelWidgetClass, form, 
		XmNleftAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_FORM, NULL));
	SetText(XtVaCreateManagedWidget("find_text",
		xmTextFieldWidgetClass, form,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetSelectionLabel(), NULL));
	toggleRC = XtVaCreateManagedWidget("toggleRC",
		xmRowColumnWidgetClass, form,
		XmNorientation, XmHORIZONTAL, 
		XmNleftAttachment, XmATTACH_FORM, NULL);
	sensitiveToggle = XtVaCreateManagedWidget("case sensitive", 
		xmToggleButtonWidgetClass, toggleRC, 
		XmNset, False, NULL);
	substringToggle = XtVaCreateWidget("substring", 
		xmToggleButtonWidgetClass, toggleRC,
		XmNset, True, NULL);
	nameOnlyToggle = XtVaCreateWidget("name only", 
		xmToggleButtonWidgetClass, toggleRC,
		XmNset, False, NULL);
	AttachToggles();
	XtManageChild(form);
}

void FindDialog::AttachToggles() {
	XtVaSetValues(toggleRC, 
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetText(), NULL);
}

void FindDialog::ManageSensitiveToggle(bool b) {
	b ? XtManageChild(sensitiveToggle) :
	    XtUnmanageChild(sensitiveToggle);
}

void FindDialog::ManageSubstringToggle(bool b) {
	b ? XtManageChild(substringToggle) :
	    XtUnmanageChild(substringToggle);
}

void FindDialog::ManageNameOnlyToggle(bool b) {
	b ? XtManageChild(nameOnlyToggle) :
	    XtUnmanageChild(nameOnlyToggle);
}
