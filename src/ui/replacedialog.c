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
#include "replacedialog.h"
#include "mstring.h"
#include <Xm/XmAll.h>

ReplaceDialog::ReplaceDialog(Widget w): FindDialog(w) { 
}

void ReplaceDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void ReplaceDialog::Configure() {
	FindDialog::Configure();
	SetOKButtonLabel("Find\nNext");
	SetApplyButtonLabel("Replace\nAll");
	replaceButton = XtVaCreateManagedWidget("Replace",
		xmPushButtonWidgetClass, GetWidget(), NULL);
	XmString t = CreateXmString("Replace\nNext");
	XtVaSetValues(replaceButton, XmNlabelString, t, NULL);
	SetHelpCallback(ReplaceClearCB, this);
	replaceLabel = XtVaCreateManagedWidget("Replace with",
		xmLabelWidgetClass, GetForm(),
		XmNleftAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, GetText(), NULL);
	replaceText = XtVaCreateManagedWidget("replace_text",
		xmTextFieldWidgetClass, GetForm(), 
		XmNleftAttachment, XmATTACH_FORM, 
		XmNrightAttachment, XmATTACH_FORM, 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, replaceLabel, NULL);
	XtVaSetValues(GetToggleRC(), 
		XmNtopAttachment, XmATTACH_WIDGET, 
		XmNtopWidget, replaceText, NULL);
	XmStringFree(t);
}

void ReplaceDialog::AttachToggles() {}

void ReplaceDialog::SetReplaceText(const string *v) {
	SetReplaceText(v->getstr());
}

void ReplaceDialog::SetReplaceText(const char *v) {
	if (!check(replaceText))
		return;
	XmTextSetString(replaceText, (char *)v);
}

void ReplaceDialog::GetReplaceText(char *n) {
	if (!check(replaceText))
		return;
	char *s = XmTextGetString(replaceText);
	strcpy(n, s);
	XtFree(s);
}

void ReplaceDialog::GetReplaceText(string *n) {
	char tmp[MAXNAME];
	GetReplaceText(tmp);
	*n = tmp;
}

void ReplaceDialog::SetReplaceCallback(XtCallbackProc fun, 
		XtPointer clientData) {
	if (!check(replaceButton))
		    return;
	XtAddCallback(replaceButton, XmNactivateCallback, fun, clientData);
}

void ReplaceDialog::ReplaceClearCB(Widget, XtPointer clientData, XtPointer) {
	ReplaceDialog *d = (ReplaceDialog *)clientData;
	d->SetTextString("");
	d->SetReplaceText("");
}
