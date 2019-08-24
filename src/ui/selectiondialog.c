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
#include "selectiondialog.h"
#include "mstring.h"
#include <Xm/XmAll.h>

SelectionDialog::SelectionDialog(Widget w): Dialog(w) {
	defaultValue = "";
	text = list = selectionLabel = 0;
}

void SelectionDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateSelectionDialog(GetParent(), (char *)GetClassName(), args, i));
}

void SelectionDialog::Configure() {
	text = XmSelectionBoxGetChild(GetWidget(), XmDIALOG_TEXT);
	list = XmSelectionBoxGetChild(GetWidget(), XmDIALOG_LIST);
	selectionLabel = XmSelectionBoxGetChild(GetWidget(), 
		XmDIALOG_SELECTION_LABEL);
}

void SelectionDialog::SetTextString(const char *v) {
	if (!check(text))
		return;
	XmTextSetString(text, (char *)v);
}

void SelectionDialog::SetTextString(const string *v) {
	SetTextString(v->getstr());
}

void SelectionDialog::GetTextString(char *n) {
	if (!check(text))
		return;
	char *s = XmTextGetString(text);
	strcpy(n, s);
	XtFree(s);
}

void SelectionDialog::GetTextString(string *n) {
	char t[MAXNAME];
	GetTextString(t);
	*n = t;
}

void SelectionDialog::ManageTextString(bool b) {
	if (b)
		XtManageChild(text);
	else
		XtUnmanageChild(text);
}

void SelectionDialog::SetSelectionLabel(const char *v) {
	if (!check(GetWidget()))
		return;
	XmString t = CreateXmString(v);
	XtVaSetValues(GetWidget(), XmNselectionLabelString, t, 0);
	XmStringFree(t);
}

void SelectionDialog::ManageSelectionLabel(bool b) {
	if (b)
		XtManageChild(selectionLabel);
	else
		XtUnmanageChild(selectionLabel);
}

void SelectionDialog::SetDefaultValue(const char *s) {
	defaultValue = s;
}

void SelectionDialog::SetDefaultValue(const string *s) {
	SetDefaultValue(s->getstr());
}

void SelectionDialog::SetApplyCallback(XtCallbackProc fun, 
		XtPointer clientData) {
	if (!check(GetWidget()))
		return;
	XtAddCallback(GetWidget(), XmNapplyCallback, fun, clientData);
}

void SelectionDialog::SetApplyButtonLabel(const char *txt) {
	if (!check(GetWidget()))
		return;
	XmString t = CreateXmString(txt);
	XtVaSetValues(GetWidget(), XmNapplyLabelString, t, 0);
	XmStringFree(t);
}

void SelectionDialog::ManageApplyButton(bool b) {
	Widget button = XmSelectionBoxGetChild(GetWidget(), 
						XmDIALOG_APPLY_BUTTON);
	ManageWidget(button, b);
}

void SelectionDialog::ClearCB(Widget, XtPointer cd, XtPointer) {
	SelectionDialog *s = (SelectionDialog *)cd;
	s->SetTextString("");
}

void SelectionDialog::SetDefaultCB(Widget, XtPointer cd, XtPointer) {
	SelectionDialog *s = (SelectionDialog *)cd;
	s->SetTextString(s->GetDefaultValue());
}

void SelectionDialog::DeselectAllItems() {
	XmListDeselectAllItems(list);
}

void SelectionDialog::DeleteAllItems() {
	XmListDeleteAllItems(list);
}

void SelectionDialog::SelectItem(const string *s) {
	XmString xs = CreateXmString(s->getstr());
	XmListSelectItem(GetList(), xs, False);
        XmStringFree(xs);
}

void SelectionDialog::AddItem(const char *s, int pos) {
	XmString xs = CreateXmString(s);
        XmListAddItem(GetList(), xs, pos);
        XmStringFree(xs);
}

void SelectionDialog::AddItem(const string *s, int pos) {
	AddItem(s->getstr(), pos);
}

void SelectionDialog::SetEditable(bool b) {
	XmTextFieldSetEditable(GetText(), b);
}
