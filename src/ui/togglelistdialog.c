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
#include "togglelistdialog.h"
#include "util.h"
#include "mstring.h"
#include "bitmap.h"
#include <Xm/XmAll.h>

ToggleListDialog::ToggleListDialog(Widget w, bool b): PromptDialog(w) { 
	toggleFun = 0;
	promptVisible = b;
	numToggles = 0;
	toggleList = 0;
	clientData = 0;
}

ToggleListDialog::~ToggleListDialog() {
	if (toggleList)
		delete[] toggleList;
}

void ToggleListDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void ToggleListDialog::Configure() {
	PromptDialog::Configure();
	ManageHelpButton(False);
	if (!promptVisible) {
		ManageSelectionLabel(False);
		ManageTextString(False);
	}
}

void ToggleListDialog::SetToggleChangedCallback(XtCallbackProc fun, 
		XtPointer cd) {
	toggleFun = fun;
	clientData = cd;
	for (unsigned i=0; i<numToggles; i++)
		XtAddCallback(toggleList[i], XmNvalueChangedCallback, 
				toggleFun, clientData);
}

void ToggleListDialog::CreateToggles(const string *label, 
		List<string *> *items) {
	char wname[12] = "toggle_box";
	Widget toggleBox = XmCreateRadioBox(GetWidget(), wname, 0, 0);
	int i = 0;
	numToggles = 0;
	toggleList = new Widget[items->count()];
	if (*label != "") {
		Widget frame = XtVaCreateManagedWidget("frame",
			xmFrameWidgetClass, toggleBox, NULL);
		XtVaCreateManagedWidget(label->getstr(),
			xmLabelWidgetClass, frame,
			XmNchildType, XmFRAME_TITLE_CHILD, NULL);
	}
	for (items->first(); !items->done(); items->next()) {
		const char *s = items->cur()->getstr();
		XmString btn = CreateXmString(s);
		Widget w = XtVaCreateManagedWidget(s,
				xmToggleButtonWidgetClass, toggleBox,
				XmNuserData, i,
				XmNhighlightThickness, 0,
				XmNset, i==0, NULL);
		toggleList[numToggles] = w;
		numToggles++;
		i++;
		if (toggleFun)
			XtAddCallback(w, XmNvalueChangedCallback, toggleFun, 
				clientData);
		XmStringFree(btn);
	}
	XtManageChild(toggleBox);
}

void ToggleListDialog::CreateToggles(List<string *> *items) {
	string empty = "";
	CreateToggles(&empty, items);
}

void ToggleListDialog::SetToggleBitmap(unsigned i, Bitmap *bitmap) {
	if (check(i < numToggles)) {
		Widget tb = toggleList[i];
		Pixmap pixmap = bitmap->CreatePixmap(tb, GetDisplay());
		XtVaSetValues(tb, 
			XmNlabelType, XmPIXMAP,
                        XmNlabelPixmap, pixmap, NULL);
	}
}

void ToggleListDialog::SetToggleText(unsigned i, const string *txt) {
 	if (check(i < numToggles)) {
		XmString s = CreateXmString(txt->getstr());
		XtVaSetValues(toggleList[i], XmNlabelString, s, NULL);
		XmStringFree(s);
	}
}

void ToggleListDialog::GetToggleText(unsigned i, string *txt) {
	if (check(i < numToggles)) {
		XmString s = CreateXmString("");
		XtVaGetValues(toggleList[i], XmNlabelString, &s, NULL);
		char *str;
		if (XmStringGetLtoR(s, XmFONTLIST_DEFAULT_TAG, &str)) {
			*txt = str;
			XtFree(str);
		}
		XmStringFree(s);
	}
}

unsigned ToggleListDialog::NumToggles() {
	return numToggles;
}

void ToggleListDialog::SetValue(unsigned n) {
	if (check(n < numToggles))
		XmToggleButtonSetState(toggleList[n], True, True);
}

int ToggleListDialog::GetValue() {
	for (unsigned i=0; i<numToggles; i++) {
		if (XmToggleButtonGetState(toggleList[i]))
			return i;
	}
	return -1;
}
