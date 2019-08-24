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
#include "fileselectiondialog.h"
#include "application.h"
#include "mstring.h"
#include "util.h"
#include "menu.h"
#include "system.h"
#include <string.h>
#include <Xm/XmAll.h>

FileSelectionDialog::FileSelectionDialog(Widget w): SelectionDialog(w) { 
	pane = 0;
	menu = 0;
	menuFrame = 0;
	defaultFile = "";
	SetAutoUnmanage(True);
}

void FileSelectionDialog::CreateWidget() {
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateFileSelectionDialog(GetParent(), 
			(char *)GetClassName(), args, i));
}

void FileSelectionDialog::Configure() {
	SelectionDialog::Configure();
	ManageHelpButton(False);
}

void FileSelectionDialog::SetExtension(const char *extension) {
	if (!check(GetWidget()))
		return;
	XmString pattern;
	XmString dirLabel;
	XmString fileLabel;
	unsigned char fileTypeMask;
	if (equal(extension, ".")) {
		fileTypeMask = XmFILE_DIRECTORY;
		dirLabel = CreateXmString("Browse");
		fileLabel = CreateXmString("Directory");
		pattern = CreateXmString("");
	}
	else {
		fileTypeMask = XmFILE_REGULAR;
		dirLabel = CreateXmString("Directory");
		fileLabel = CreateXmString("File");
		pattern = CreateXmString(extension);
	}
	XtVaSetValues(GetWidget(),
		XmNfileTypeMask, fileTypeMask,
		XmNdirListLabelString, dirLabel,
		XmNfileListLabelString, fileLabel,
		XmNpattern, pattern, NULL);
	if (fileLabel)
		XmStringFree(fileLabel);
	if (dirLabel)
		XmStringFree(dirLabel);
	XmStringFree(pattern);
}

void FileSelectionDialog::SetExtension(const string *extension) {
	SetExtension(extension->getstr());
}

void FileSelectionDialog::SetDirectory(const char *d) {
	if (!check(GetWidget()))
		return;
	XmString dir = CreateXmString(d);
	XtVaSetValues(GetWidget(), XmNdirectory, dir, NULL);
	XmStringFree(dir);
}

void FileSelectionDialog::SetDirectory(const string *d) {
	SetDirectory(d->getstr());
}

void FileSelectionDialog::SetDefaultFile(const char *f) {
	if (!check(GetWidget()))
		return;
	XmString dirSpec;
	// Update the file list in the dialog
	XmString pattern = CreateXmString("");
	XmString dir = CreateXmString("");
	XtVaGetValues(GetWidget(), XmNpattern, &pattern, NULL);
	XtVaGetValues(GetWidget(), XmNdirectory, &dir, NULL);
	char *str1, *str2;
	XmStringGetLtoR(dir, XmFONTLIST_DEFAULT_TAG, &str1);
	XmStringGetLtoR(pattern, XmFONTLIST_DEFAULT_TAG, &str2);
	string msk = str1;
	msk += "/";
	msk += str2;
	// std::cout << "pattern = " << msk << std::endl;
	XmString mask = CreateXmString(msk.getstr());
	XmFileSelectionDoSearch(GetWidget(), mask);
#if defined(LESSTIF_VERSION) && LESSTIF_VERSION==0 && LESSTIF_REVISION<=93
	// do nothing since XmFileSelectionDoSearch frees mask erroneously
#else	
 	XmStringFree(mask);
#endif	
	XmStringFree(pattern);
	XmStringFree(dir);
	XtFree(str1);
	XtFree(str2);
	// This method worked for Motif but not for Lesstif
	// XtRemoveCallback(GetWidget(), XmNapplyCallback, 
	// 	SetDefaultFileCB, this);
	// SetApplyCallback(SetDefaultFileCB, this);

	// Force the default name in the text entry field.
	dirSpec = CreateXmString(f);
	XtVaSetValues(GetWidget(), XmNtextString, dirSpec, NULL);
	string f1 = f;
	System::GiveFile(&f1, &defaultFile);
	if (dirSpec)
		XmStringFree(dirSpec);
}

void FileSelectionDialog::SetDefaultFile(const string *f) {
	SetDefaultFile(f->getstr());
}

void FileSelectionDialog::Popup() {
	// deselect files.
	DeselectAllItems();
	// make sure file selection box has an acceptable minimal width.
	short w;
	XtVaGetValues(GetText(), XmNcolumns, &w, NULL);
	if (w < 40)
		XtVaSetValues(GetText(), XmNcolumns, 40, NULL);
	Dialog::Popup();
}

void FileSelectionDialog::GetFileName(char *n) {
	if (!check(GetWidget()))
		return;
	char *s = XmTextGetString(GetText());
	strcpy(n, s);
	XtFree(s);
}

void FileSelectionDialog::GetFileName(string *n) {
	char f[MAXNAME];
	GetFileName(f);
	*n = f;
}

void FileSelectionDialog::GetDirectory(char *dir) {
	if (!check(GetWidget()))
		return;
	XmString d = CreateXmString("");
	char *str;
	XtVaGetValues(GetWidget(), XmNdirectory, &d, NULL);
	if (XmStringGetLtoR(d, XmFONTLIST_DEFAULT_TAG, &str)) {
		strcpy(dir, str);
		XtFree(str);
	}
	XmStringFree(d);
}

void FileSelectionDialog::GetDirectory(string *n) {
	char f[MAXNAME];
	GetDirectory(f);
	*n = f;
}

void FileSelectionDialog::CreateOptionMenu(string *l, List<string *> *items) {
	if (pane) {
		XtDestroyWidget(pane);
		pane = 0;
		menu = 0;
	}
	XmString ls = CreateXmString(l->getstr());
	Arg args[9]; int i = 0;
	XtSetArg(args[i], XmNleftAttachment, XmATTACH_FORM); i++;
	XtSetArg(args[i], XmNrightAttachment, XmATTACH_FORM); i++;
	XtSetArg(args[i], XmNtopAttachment, XmATTACH_WIDGET); i++;
	XtSetArg(args[i], XmNbottomAttachment, XmATTACH_WIDGET); i++;
	XtSetArg(args[i], XmNtopWidget, GetList()); i++;
	XtSetArg(args[i], XmNbottomWidget, GetText());
	char wname[MAXNAME] = "frame";
	menuFrame = XmCreateFrame(GetWidget(), wname, args, i);
	Widget rc = XtVaCreateWidget("rc", xmRowColumnWidgetClass, menuFrame, 
			XmNorientation, XmHORIZONTAL, NULL);
	XtVaCreateManagedWidget("label", xmLabelWidgetClass, 
		rc, XmNlabelString, ls, NULL);
	strcpy(wname, "menu");
	menu = XmCreateOptionMenu(rc, wname, 0, 0);
	strcpy(wname, "pane");
	pane = XmCreatePulldownMenu(rc, wname, 0, 0);
	XtVaSetValues(menu, XmNsubMenuId, pane, NULL);
	XtAddCallback(pane, XmNentryCallback, OptionChangedCB, this);
	for (items->first(); !items->done(); items->next()) {
		XtCreateManagedWidget(items->cur()->getstr(),
			xmPushButtonWidgetClass, pane, 0, 0);
	}
	if (items->first())
		SetOption(items->cur());
	XmStringFree(ls);
	XtManageChild(menu);
	XtManageChild(rc);
	XtManageChild(menuFrame);
}

void FileSelectionDialog::ManageOptionMenu(bool b) {
	if (!menuFrame)
		return;
	if (b)
		XtManageChild(menuFrame);
	else
		XtUnmanageChild(menuFrame);
}

void FileSelectionDialog::OptionChangedCB(Widget, XtPointer cd, XtPointer cbs) {
	FileSelectionDialog *f = (FileSelectionDialog *)cd;
	XmRowColumnCallbackStruct *c = (XmRowColumnCallbackStruct *)cbs;
	string s = XtName(c->widget);
	f->SetOption(&s);
}

void FileSelectionDialog::SetDefaultFileCB(Widget, XtPointer cd, XtPointer) {
	FileSelectionDialog *f = (FileSelectionDialog *)cd;
	string file;
	f->GetDirectory(&file);
	file += *f->GetDefaultFile();
	f->SetDefaultFile(&file);
}

void FileSelectionDialog::SetOptionChangedCallback(XtCallbackProc fun, 
		XtPointer cd) {
	XtAddCallback(pane, XmNentryCallback, fun, cd);
}

void FileSelectionDialog::SetOption(const string *s) { 
	// only setting the label of option button does not work.
	Widget *wlist;
	int numc;
	XtVaGetValues(pane, XmNchildren, &wlist, NULL);
	XtVaGetValues(pane, XmNnumChildren, &numc, NULL);
	XmString s1 = CreateXmString(s->getstr());
	for (int i=0; i<numc; i++) {
		XmString s2 = CreateXmString("");
		XtVaGetValues(wlist[i], XmNlabelString, &s2, NULL);
		char *str;
		if (XmStringGetLtoR(s2, XmFONTLIST_DEFAULT_TAG, &str)) {
			if (strstr(str, s->getstr())) {
				XtVaSetValues(pane, XmNmenuHistory, wlist[i], NULL);
				Widget l = XmOptionButtonGadget(menu);
				XtVaSetValues(l, XmNlabelString, s1, NULL);
				XmStringFree(s1);
				XmStringFree(s2);
				XtFree(str);
				return;
			}
			XtFree(str);
		}
		XmStringFree(s2);
	}
	XmStringFree(s1);
}

void FileSelectionDialog::GetOption(string *item) { 
	*item = "";
	if (menu) {
		char *str;
		XmString xs = CreateXmString("");
		Widget l = XmOptionButtonGadget(menu);
		XtVaGetValues(l, XmNlabelString, &xs, NULL);
		if (XmStringGetLtoR(xs, XmFONTLIST_DEFAULT_TAG, &str)) {
			*item = str;
			XtFree(str);
		}
		XmStringFree(xs);
	}
}
