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
#include "modelcheckdialog.h"
#include "mstring.h"
#include <Xm/XmAll.h>

ModelCheckDialog::ModelCheckDialog(Widget w): SelectionDialog(w) { 
//	SetAutoUnmanage(True);
}

void ModelCheckDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void ModelCheckDialog::Configure() {
	SelectionDialog::Configure();
	SetCancelCallback(ModelCheckDialog::UnmanageCB, this);
	SetCancelButtonLabel("Cancel");
	ManageHelpButton(False);
	SetOKButtonLabel("Check model");
	ManageApplyButton(False);

	ManageTextString(False);
	ManageSelectionLabel(False);

	form = XtVaCreateWidget("form",
		xmFormWidgetClass, GetWidget(), NULL);
	SetSelectionLabel(XtVaCreateManagedWidget("Kronos formula to be checked",
		xmLabelWidgetClass, form,
		XmNleftAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_FORM, NULL));
	SetText(XtVaCreateManagedWidget("formula",
		xmTextFieldWidgetClass, form,
		XmNleftAttachment, XmATTACH_FORM,
		XmNrightAttachment, XmATTACH_FORM,
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, GetSelectionLabel(), NULL));
	internLabel = XtVaCreateManagedWidget("Internal events",
		xmLabelWidgetClass, GetForm(),
		XmNleftAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, GetText(), NULL);
	internText = XtVaCreateManagedWidget("intern",
		xmTextFieldWidgetClass, GetForm(), 
		XmNleftAttachment, XmATTACH_FORM, 
		XmNrightAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, internLabel, NULL);
	clockLabel = XtVaCreateManagedWidget("Clocks",
		xmLabelWidgetClass, GetForm(),
		XmNleftAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, internText, NULL);
	clockText = XtVaCreateManagedWidget("clock",
		xmTextFieldWidgetClass, GetForm(), 
		XmNleftAttachment, XmATTACH_FORM, 
		XmNrightAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, clockLabel, NULL);
	XtManageChild(form);
}

void ModelCheckDialog::GetInternString(char *n) {
	if ( ! check(internText) )
		return;
	char *s = XmTextGetString(internText);
	strcpy(n, s);
	XtFree(s);
}

void ModelCheckDialog::GetInternString(string *n) {
	char tmp[MAXNAME];
	GetInternString(tmp);
	*n = tmp;
}

void ModelCheckDialog::GetClockString(char *n) {
	if ( ! check(clockText) )
		return;
	char *s = XmTextGetString(clockText);
	strcpy(n, s);
	XtFree(s);
}

void ModelCheckDialog::GetClockString(string *n) {
	char tmp[MAXNAME];
	GetClockString(tmp);
	*n = tmp;
}
