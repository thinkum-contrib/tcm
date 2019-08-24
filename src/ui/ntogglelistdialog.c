////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "ntogglelistdialog.h"
#include "util.h"
#include "mstring.h"
#include "bitmap.h"
#include <Xm/XmAll.h>

NToggleListDialog::NToggleListDialog(Widget w, bool b): PromptDialog(w) { 
	promptVisible = b;
	optionsVisible = False;
}

NToggleListDialog::~NToggleListDialog() {
	for (toggleList.first(); !toggleList.done(); toggleList.next())
		delete toggleList.cur();
}

void NToggleListDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreatePromptDialog(GetParent(), (char *)GetClassName(), args, i));
}

void NToggleListDialog::Configure() {
	PromptDialog::Configure();
	if (!promptVisible) {
		ManageSelectionLabel(False);
		ManageTextString(False);
	}
	ManageCancelButton(True);
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	SetOKButtonLabel("Apply");
	SetCancelButtonLabel("Dismiss");
	SetCancelCallback(Dialog::UnmanageCB, this);
}

void NToggleListDialog::SetToggleChangedCallback(
		unsigned n, XtCallbackProc fun, XtPointer cd) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
		for (unsigned i=0; i<toggles->count(); i++)
			XtAddCallback((*toggles)[i], 
				XmNvalueChangedCallback, fun, cd);
	}
}

void NToggleListDialog::CreateToggleLists(
	List<string *> *labels, List<List<string *> *> *items,
	List<string *> *options) {
	if (!check(labels->count() == items->count()))
		return;
	if (options != 0) {
		if (!check(labels->count() == options->count()))
			return;
		optionsVisible = True;
	}
	Arg args[10];
	int n = 0;
	XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
	char wname[8] = "widget";
	Widget rc = XmCreateRowColumn(GetWidget(), wname, args, n);
	for (unsigned j=0; j<labels->count(); j++) {
		Widget rc2 = XmCreateRowColumn(rc, wname, 0, 0);
		Widget frame = XtVaCreateManagedWidget(wname,
			xmFrameWidgetClass, rc2, 0);
		XtVaCreateManagedWidget((*labels)[j]->getstr(),
			xmLabelWidgetClass, frame,
			XmNchildType, XmFRAME_TITLE_CHILD, 0);
		Widget box = XmCreateRadioBox(frame, wname, 0, 0);
		List<string *> *t = (*items)[j];
		int i = 0;
		List<Widget> *toggles = new List<Widget>;
		for (t->first(); !t->done(); t->next()) {
			i++;
		 	const char *s = t->cur()->getstr();
	 		Widget w = XtVaCreateManagedWidget(s,
	 			xmToggleButtonWidgetClass, box,
	 			XmNuserData, i,
	 			XmNhighlightThickness, 0,
	 			XmNset, i==0, 0);
	 		toggles->add(w);
		}
		toggleList.add(toggles);
		XtManageChild(box);
		if (options != 0) {
		 	const char *s = (*options)[j]->getstr();
			Widget w = XtVaCreateManagedWidget(s,
	 			xmToggleButtonWidgetClass, rc2,
	 			XmNhighlightThickness, 0,
	 			XmNset, 0, 0);
			optionList.add(w);
		}
		XtManageChild(rc2);
	}
	XtManageChild(rc);
}

void NToggleListDialog::SetItemBitmap(unsigned n, unsigned i, Bitmap *bitmap) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
        	if (check(i < toggles->count())) {
                	Widget tb = (*toggles)[i];
                	Pixmap pixmap = bitmap->CreatePixmap(tb, GetDisplay());
                	XtVaSetValues(tb,
                        	XmNlabelType, XmPIXMAP,
                        	XmNlabelPixmap, pixmap, 0);
		}
        }
}


void NToggleListDialog::SetItem(unsigned n, unsigned i, const string *txt) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
 		if (check(i < toggles->count())) {
			XmString s = CreateXmString(txt->getstr());
			XtVaSetValues((*toggles)[i], XmNlabelString, s, 0);
			XmStringFree(s);
		}
	}
}

void NToggleListDialog::GetItem(unsigned n, unsigned i, string *txt) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
		if (check(i < toggles->count())) {
			XmString s = CreateXmString("");
			XtVaGetValues((*toggles)[i], XmNlabelString, &s, 0);
			char *str;
			if (XmStringGetLtoR(s, XmFONTLIST_DEFAULT_TAG, &str)) {
				*txt = str;
				XtFree(str);
			}
			XmStringFree(s);
		}
	}
}

void NToggleListDialog::SetValue(unsigned n, unsigned i) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
		if (check(i < toggles->count()))
			XmToggleButtonSetState((*toggles)[i], True, True);
	}
}

void NToggleListDialog::SetValueOfText(unsigned n, const string *t) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
		for (unsigned i=0; i<toggles->count(); i++) {
			XmString s = CreateXmString("");
			XtVaGetValues((*toggles)[i], XmNlabelString, &s, 0);
			char *str;
			if (XmStringGetLtoR(s, XmFONTLIST_DEFAULT_TAG, &str)) {
				if (*t == str) {
					XmToggleButtonSetState((*toggles)[i], 
						True, True);
					XmStringFree(s);
					XtFree(str);
					return;
				}
				XtFree(str);
			}
			XmStringFree(s);
		}
	}
}

int NToggleListDialog::GetValue(unsigned n) {
	if (check(n < toggleList.count())) {
		List<Widget> *toggles = toggleList[n];
		for (unsigned i=0; i<toggles->count(); i++) {
			if (XmToggleButtonGetState((*toggles)[i]))
				return i;
		}
	}
	return -1;
}

int NToggleListDialog::GetOptionValue(unsigned n) {
	if (!optionsVisible)
		return -1;
	else if (!check(n < optionList.count()))
		return -1;
	else 
		return (XmToggleButtonGetState(optionList[n]));
}

void NToggleListDialog::SetOptionValue(unsigned n, bool b) {
	if (optionsVisible && check(n < optionList.count()))
		XmToggleButtonSetState(optionList[n], b, True);
}

void NToggleListDialog::SetPromptVisible(bool b) {
	if (promptVisible == b)
		return;
	promptVisible = b;
	ManageSelectionLabel(b);
	ManageTextString(b);
}

void NToggleListDialog::SetOptionsVisible(bool b) {
	if (optionsVisible == b)
		return;
	optionsVisible = b;
	for (optionList.first(); !optionList.done(); optionList.next()) {
		Widget w = optionList.cur();
		if (b)
			XtManageChild(w);
		else
			XtUnmanageChild(w);
	}
}
