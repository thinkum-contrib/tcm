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
#include "temporalpropertydialog.h"
#include "mstring.h"
#include <Xm/XmAll.h>

TPDialog::TPDialog(Widget w): SelectionDialog(w) { 
	SetAutoUnmanage(False);
}

bool TPDialog::SensitiveOn() {
	return XmToggleButtonGetState(sensitiveToggle);
}

bool TPDialog::SubstringOn() {
	return XmToggleButtonGetState(substringToggle);
}

bool TPDialog::NameOnlyOn() {
	return XmToggleButtonGetState(nameOnlyToggle);
}

void TPDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void TPDialog::Configure() {
	SelectionDialog::Configure();
	SetCancelCallback(TPDialog::UnmanageCB, this);
	//	SetCancelButtonLabel("Dismiss");
	ManageHelpButton(True);
	SetHelpButtonLabel("Clear");
	SetHelpCallback(TPDialog::ClearCB, this);
	//	SetOKButtonLabel("Find\nNext");
		ManageApplyButton(False);
	//	SetApplyButtonLabel("Find\nAll");

	ManageTextString(False);
      	ManageSelectionLabel(False);
	//ManageSensitiveToggle(False);

	form = XtVaCreateWidget("form",
		xmFormWidgetClass, GetWidget(), 0);
	SetSelectionLabel(XtVaCreateManagedWidget("LTL property",
		xmLabelWidgetClass, form, 
		XmNleftAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_FORM, 0));
	SetText(XtVaCreateManagedWidget("find_text",
		xmTextFieldWidgetClass, form,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetSelectionLabel(), 0));
	toggleRC = XtVaCreateManagedWidget("toggleRC",
		xmRowColumnWidgetClass, form,
		XmNorientation, XmHORIZONTAL, 
		XmNleftAttachment, XmATTACH_FORM, 0);
	sensitiveToggle = XtVaCreateManagedWidget("syntactic encoding", 
		xmToggleButtonWidgetClass, toggleRC, 
		XmNset, False, 0);
	substringToggle = XtVaCreateWidget("reduction", 
		xmToggleButtonWidgetClass, toggleRC,
		XmNset, False, 0);
	nameOnlyToggle = XtVaCreateWidget("strong fairness", 
		xmToggleButtonWidgetClass, toggleRC,
		XmNset, True, 0);
	AttachToggles();

	XtManageChild(form);

}

void TPDialog::AttachToggles() {
	XtVaSetValues(toggleRC, 
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetText(), 0);
}

void TPDialog::ManageSensitiveToggle(bool b) {
	b ? XtManageChild(sensitiveToggle) :
	    XtUnmanageChild(sensitiveToggle);
}

void TPDialog::ManageSubstringToggle(bool b) {
	b ? XtManageChild(substringToggle) :
	    XtUnmanageChild(substringToggle);
}

void TPDialog::ManageNameOnlyToggle(bool b) {
	b ? XtManageChild(nameOnlyToggle) :
	    XtUnmanageChild(nameOnlyToggle);
}
