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
#include "scaledialog.h"
#include "util.h"
#include "mstring.h"
#include <Xm/XmAll.h>

ScaleDialog::ScaleDialog(Widget w): MessageDialog(w) {
	initValue = 1;
	defaultValue = 1;
	valueChangeFun = 0;
}

void ScaleDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateMessageDialog(GetParent(), (char *)GetClassName(), args, i));
	scale = XtVaCreateManagedWidget("scale",
			xmScaleWidgetClass, GetWidget(),
			XmNorientation, XmHORIZONTAL,
			XmNshowValue, True, 0);
}

void ScaleDialog::Configure() {
	SetHelpButtonLabel("Default");
	SetHelpCallback(SetDefaultCB, this);
	SetCancelCallback(SetInitCB, this);
}

void ScaleDialog::SetScaleValues(int min, int max, int init, int decimal, 
		int def) {
	if (!check(scale))
		return;
	XtVaSetValues(scale, 
		XmNmaximum, max,
		XmNminimum, min,
		XmNvalue, init,
		XmNdecimalPoints, decimal, 0);
	initValue = init;
	defaultValue = def;
}

void ScaleDialog::SetScaleLabel(const char *text) {
	if (!check(scale))
		return;
	XmString text_string = CreateXmString(text);
	// XtVaTypedArg, XmNtitleString, XmRString, text, strlen(text),
	XtVaSetValues(scale, XmNtitleString, text_string, 0);
	XmStringFree(text_string);
}

void ScaleDialog::SetValueChangedCallback(XtCallbackProc fun, XtPointer cd) {
	if (!check(scale))
		return;
	XtRemoveAllCallbacks(scale, XmNvalueChangedCallback);
	if (fun) {
		XtAddCallback(scale, XmNvalueChangedCallback, fun, cd);
		valueChangeFun = fun;
		clientData = cd;
	}
	else
		valueChangeFun = 0;
}

void ScaleDialog::SetDefaultCB(Widget, XtPointer cd, XtPointer) {
	ScaleDialog *d = (ScaleDialog *)cd;
	d->SetScaleValue(d->GetDefaultValue());
}
 
void ScaleDialog::SetInitCB(Widget, XtPointer cd, XtPointer) {
	ScaleDialog *d = (ScaleDialog *)cd;
	d->SetScaleValue(d->GetInitValue());
}
 
void ScaleDialog::SetScaleValue(int val) {
	if (!check(scale))
		return;
	int oldval = GetScaleValue();
	if (oldval != val) {
		XmScaleSetValue(scale, val);
		if (valueChangeFun) {
			XmScaleCallbackStruct cbs;
			cbs.value = val;
			cbs.event = 0;
			cbs.reason = XmCR_VALUE_CHANGED;
			(*valueChangeFun)(scale, clientData, (XtPointer) &cbs);
		}
	}
}
 
int ScaleDialog::GetScaleValue() {
	if (!check(scale))
		return 1; 
	int val;
	XmScaleGetValue(scale, &val);
	return val;
}
