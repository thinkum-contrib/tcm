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
#include "textviewdialog.h"
#include "fileutils.h"
#include "fileselectiondialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "messagedialog.h"
#include "mstring.h"
#include "menu.h"
#include "printeroptions.h"
#include "application.h"
#include <Xm/XmAll.h>
#if defined(LINUX)
#include <stdio.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

TextViewDialog::TextViewDialog(Widget w): Dialog(w) {
	fileItems = 0;
	editItems = 0;
	textWidget = 0;
	saveFile = "";
	loadFile = "";
	printerOptions = theApplication->GetPrinterOptions();
	fileSelector = 0;
	findDialog = 0;
	replaceDialog = 0;
	maxRows = 250;
	maxColumns = 250;
	SetAutoUnmanage(True);
}

TextViewDialog::~TextViewDialog() {
	if (fileItems)
		delete fileItems;
	if (editItems)
		delete editItems;
	if (searchItems)
		delete searchItems;
	if (fileSelector)
		delete fileSelector;
	if (findDialog)
		delete findDialog;
	if (replaceDialog)
		delete replaceDialog;
}

void TextViewDialog::CreateWidget() {
	Arg args[24]; int i = 0;
	XtSetArg(args[i], XmNautoUnmanage, GetAutoUnmanage()); i++;
	SetWidget(XmCreateMessageDialog(GetParent(), (char *)GetClassName(), args, i));
	XtVaSetValues(XtParent(GetWidget()), XmNallowShellResize, True, NULL);
}

void TextViewDialog::Configure() {
	Arg args[24]; int i = 0;
	InitMenuItems();
	XtUnmanageChild(XmMessageBoxGetChild(GetWidget(), 
					XmDIALOG_MESSAGE_LABEL));
	ManageHelpButton(False);
	ManageCancelButton(False);
	SetOKButtonLabel("Dismiss");
	// create menu bar.
	i = 0;
	char wname[MAXNAME] = "MenuBar";
	menuBar = XmCreateMenuBar(GetWidget(), wname, args, i);
	XtVaSetValues(menuBar,
	 	XmNtopAttachment, XmATTACH_FORM,
	 	XmNleftAttachment, XmATTACH_FORM,
	 	XmNrightAttachment, XmATTACH_FORM, NULL);
	fileMenu = new Menu(menuBar, Menu::PULLDOWN, "File", 0, fileItems);
	editMenu = new Menu(menuBar, Menu::PULLDOWN, "Edit", 0, editItems);
	searchMenu = new Menu(menuBar, Menu::PULLDOWN, "Search", 0, 
		searchItems);
	// create a manager widget as a child of the dialog, to be used
	// as the work area of the dialog, replacing the label and the icon.
	Widget form = XtVaCreateWidget("form1", xmFormWidgetClass, 
					GetWidget(), NULL);
	XtVaSetValues(form, 
		XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, menuBar,
		XmNleftAttachment, XmATTACH_FORM,
		XmNbottomAttachment, XmATTACH_WIDGET,
		XmNbottomWidget, XmMessageBoxGetChild(GetWidget(), 
			XmDIALOG_SEPARATOR),
		XmNrightAttachment, XmATTACH_FORM, NULL);
	// create text field.
	i = 0;
	XtSetArg(args[i], XmNeditable, False); i++;
	XtSetArg(args[i], XmNcursorPositionVisible, False); i++;
	XtSetArg(args[i], XmNshadowThickness, 0); i++;
	strcpy(wname, "StatusText");
	textStatus = XmCreateTextField(form, wname, args, i); 
	XtVaSetValues(textStatus,
	 	XmNtopAttachment, XmATTACH_FORM,
	 	XmNleftAttachment, XmATTACH_FORM,
	 	XmNrightAttachment, XmATTACH_FORM, NULL);
	i = 0;
	XtSetArg(args[i], XmNscrollVertical, True); i++;
	XtSetArg(args[i], XmNrows, 6); i++;
	XtSetArg(args[i], XmNcolumns, 60); i++;
	XtSetArg(args[i], XmNscrollHorizontal, True); i++;
	XtSetArg(args[i], XmNeditMode, XmMULTI_LINE_EDIT); i++;
	XtSetArg(args[i], XmNeditable, False); i++;
	XtSetArg(args[i], XmNcursorPositionVisible, False); i++;
	XtSetArg(args[i], XmNwordWrap, True); i++;
	strcpy(wname, "Text");
	textWidget = XmCreateScrolledText(form, wname, args, i);
	// attachment values must be set on the text widget's parent,
	// the scrolled window. This is the object that is positioned
	XtVaSetValues(XtParent(textWidget),
	 	XmNtopAttachment, XmATTACH_WIDGET,
		XmNtopWidget, textStatus,
	 	XmNrightAttachment, XmATTACH_FORM,
	 	XmNbottomAttachment, XmATTACH_FORM,
	 	XmNleftAttachment, XmATTACH_FORM, NULL);
	XtManageChild(menuBar);
	XtManageChild(textStatus);
	XtManageChild(textWidget);
	XtManageChild(form);
	// make file selection dialog.
	fileSelector = new FileSelectionDialog(GetWidget());
	fileSelector->Initialize();
	fileSelector->SetExtension("");
	// make text find and text replace dialog.
	findDialog = new FindDialog(GetWidget());
	findDialog->Initialize();
	findDialog->SetTitle("Find text in dialog");
	findDialog->SetOKCallback(FindNextCB, this);
	findDialog->SetHelpCallback(ClearFindCB, this);
	findDialog->SetApplyCallback(FindAllCB, this);
	replaceDialog = new ReplaceDialog(GetWidget());
	replaceDialog->Initialize();
	replaceDialog->SetTitle("Replace text in dialog");
}

void TextViewDialog::SetDirectory(const char *d) {
	directory = d;
	fileSelector->SetDirectory(&directory);
}

void TextViewDialog::SetDirectory(const string *d) {
	SetDirectory(d->getstr());
}

void TextViewDialog::GetTextString(string *t) {
	if (!check(textWidget))
		return;
	char *s = XmTextGetString(textWidget);
	*t = s;
	t->replace('\n', '\r');
	XtFree(s);
}

void TextViewDialog::SetStatus(const char *s) {
	XmTextSetString(textStatus, (char *)s);
}

void TextViewDialog::SetStatus(const string *s) {
	SetStatus(s->getstr());
}

void TextViewDialog::DeleteAll() {
	SetStatus("action: Delete all");
	char empty[2] = "";
	XmTextSetString(textWidget, empty);
}

void TextViewDialog::Cut() {
	SetStatus("action: Cut");
	if (!XmTextCut(textWidget, CurrentTime))
		SetStatus("There is no selection");
}

void TextViewDialog::Copy() {
	SetStatus("action: Copy");
	if (!XmTextCopy(textWidget, CurrentTime))
		SetStatus("There is no selection");
}

void TextViewDialog::Paste() {
	SetStatus("action: Paste");
	if (!XmTextPaste(textWidget))
		SetStatus("There is no selection");
}

void TextViewDialog::ClearSelection() {
	SetStatus("action: Clear selection");
	XmTextSetHighlight(textWidget, 0, 
		XmTextGetLastPosition(textWidget), XmHIGHLIGHT_NORMAL);
	XmTextClearSelection(textWidget, CurrentTime);
	(void)XmTextCopy(textWidget, CurrentTime);
}

void TextViewDialog::Find() {
	SetStatus("action: Find");
	findDialog->Popup();
}

void TextViewDialog::DoFind(int n) {
	XmTextPosition pos = 0;
	char *text;
	char findText[MAXNAME];
	char replaceText[MAXNAME];
	char buf[MAXNAME];
	enum {FIND_NEXT, FIND_ALL, REPLACE_NEXT, REPLACE_ALL, REPLACE_FIND};
	if (!(text = XmTextGetString(textWidget)) || !*text) {
		XtFree(text);
		SetStatus("No text to search");
		return;
	}
	bool sense;
	if (n == FIND_NEXT || n == FIND_ALL) {
		sense = findDialog->SensitiveOn();
		findDialog->GetTextString(findText);
	}
	else { // REPLACE...
		sense = replaceDialog->SensitiveOn();
		replaceDialog->GetTextString(findText);
	}
	if (equal(findText, "")) {
		SetStatus("Specify a search pattern");
		XtFree(text);
		return;
	}
	if (!sense) {
		char *p;
		for (p=findText; *p; p++)
			*p = tolower(*p);
		for (p=text; *p; p++)
			*p = tolower(*p);
	}
	// std::cout << "findtext " << findText << std::endl;
	int nFound = 0;
	int findTextLen = strlen(findText);
	XmTextSetHighlight(textWidget, 0, 
		XmTextGetLastPosition(textWidget), XmHIGHLIGHT_NORMAL);
	if (n == FIND_NEXT || n == REPLACE_FIND)
		pos = XmTextGetInsertionPosition(textWidget)+1;
	if (n == REPLACE_NEXT)
		pos = XmTextGetInsertionPosition(textWidget);
	if (n == REPLACE_NEXT || n == REPLACE_ALL) {
		replaceDialog->GetReplaceText(replaceText);
		if (equal(findText, replaceText)) {
			SetStatus("Find text and replace texts are identical");
			XtFree(text);
			return;
		}
	}
	char *p;
	for (p = &text[pos]; (p = strchr(p, findText[0])); p++) {
		if ((sense && !strncmp(p, findText, findTextLen)) ||
		    (!sense && !strncasecmp(p, findText, findTextLen))) {
			nFound++;
			pos = (XmTextPosition)(p-text);
			if (n == REPLACE_NEXT || n == REPLACE_ALL) {
				XmTextReplace(textWidget, pos, 
					pos+findTextLen, replaceText);
				XtFree(text);
				text = XmTextGetString(textWidget);
				p = &text[pos + strlen(replaceText)];
				if (n == REPLACE_NEXT)
					break;
			}
			else if (n == FIND_ALL)
				XmTextSetHighlight(textWidget, pos, 
					pos+findTextLen,
					XmHIGHLIGHT_SELECTED);
			else
				break;
		}
	}
	if ((n==FIND_NEXT||n==REPLACE_NEXT||n==REPLACE_FIND) && nFound == 0) {
		// search from beginning.
		for (p = text; (p = strchr(p, findText[0])) && 
				p-text<=pos; p++) {
			if ((sense && !strncmp(p, findText, findTextLen)) ||
			     !sense && !strncasecmp(p, findText, findTextLen)) {
				nFound++;
				if (n == REPLACE_NEXT) {
					pos = (XmTextPosition)(p-text);
					XmTextReplace(textWidget, pos, 
						pos+findTextLen, replaceText);
					p = &text[pos + strlen(replaceText)];
				}
				break;
			}
		}
	}
	if (nFound == 0)
		SetStatus("Pattern not found");
	else {
		pos = (XmTextPosition)(p - text);
		if (n==FIND_NEXT||n==REPLACE_FIND) {
			sprintf(buf, "Pattern found at position %ld.", pos);
			XmTextSetInsertionPosition(textWidget, pos);
			if (!XmTextGetEditable(textWidget)) {
				XmTextSetHighlight(textWidget, pos, 
					pos+findTextLen,
					XmHIGHLIGHT_SELECTED);
			}
		}
		else if (n == REPLACE_NEXT) {
			sprintf(buf, "Pattern replaced at position %ld.", pos);
			XmTextSetInsertionPosition(textWidget, pos);
		}
		else if (n == FIND_ALL)
			sprintf(buf, "Found %d occurrences", nFound);
		else if (n == REPLACE_ALL)
			sprintf(buf, "Made %d replacements", nFound);
		SetStatus(buf);
	}
	XtFree(text);
}

void TextViewDialog::ClearFind() {
	XmTextSetHighlight(textWidget, 0, 
		XmTextGetLastPosition(textWidget), XmHIGHLIGHT_NORMAL);
	findDialog->SetTextString("");
	SetStatus("action: Clear ");
}

void TextViewDialog::Popup() {
	Dialog::Popup();
	XmProcessTraversal(textWidget, XmTRAVERSE_CURRENT);
	SetStatus("");
}

void TextViewDialog::SetTextString(const string *text) {
	if (!check(textWidget))
		return;
	// make sure that there are no disturbing carriage returns.
	string text2 = *text;
	text2.replace('\r', '\n');
	XmTextSetString(textWidget, (char *)text2.getstr());
}

void TextViewDialog::SetTextRows(int nrOfRows) {
	if (!check(textWidget))
		return;
	if (nrOfRows <= maxRows)
		XtVaSetValues(textWidget, XmNrows, nrOfRows, NULL);
}

void TextViewDialog::SetTextColumns(int nrOfColumns) {
	if (!check(textWidget))
		return;
	if (nrOfColumns <= maxColumns)
		XtVaSetValues(textWidget, XmNcolumns, nrOfColumns, NULL);
}

void TextViewDialog::SetTextSize(int nrOfRows, int nrOfColumns) {
	SetTextRows(nrOfRows);
	SetTextColumns(nrOfColumns);
}

void TextViewDialog::SetTextMaxSize(int nrOfRows, int nrOfColumns) {
	maxRows = nrOfRows;
	maxColumns = nrOfColumns;
	if (!check(textWidget))
		return;
	short rows, columns;
	XtVaGetValues(textWidget, XmNrows, &rows, XmNcolumns, &columns, NULL);
	if (rows > maxRows)
		XtVaSetValues(textWidget, XmNrows, &maxRows, NULL);
	if (columns > maxColumns)
		XtVaSetValues(textWidget, XmNcolumns, &maxColumns, NULL);
}

void TextViewDialog::Print() {
	char title[MAXNAME];
	GetTitle(title);
	string t = '"';
	t += title;
	t += '"';
	if (!FileUtils::PrintingOK(GetWidget(), t.getstr()))
		return;
	char fileName[MAXNAME];
	strcpy(fileName, printerOptions->GetTmpFile()->getstr());
	(void)mkstemp(fileName);
	if (SaveFile(fileName)) {
		char filter[MAXNAME];
		strcpy(filter, printerOptions->
				GetTextFilterCommand()->getstr());
		if (!equal(filter, "")) {
			strcat(filter, "-T ");
			strcat(filter, t.getstr());
		}
		if (FileUtils::Print(GetWidget(), fileName, 
					t.getstr(), filter)) {
			SetStatus("Printing succeeded");
			return;
		}
	}
	error("Printing from text view dialog failed\n");
	SetStatus("Printing failed");
}

void TextViewDialog::Save() {
	fileSelector->SetTitle("Save text from dialog to file");
	fileSelector->SetDefaultFile("");
	fileSelector->SetOKCallback(SaveOKCB, this);
	fileSelector->Popup();
}

void TextViewDialog::SaveAsCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->Save();
}

void TextViewDialog::PrintCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->Print();
}

void TextViewDialog::SaveOKCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	char fname[MAXNAME];
	t->GetFileSelectionDialog()->GetFileName(fname);
	t->SaveFile(fname);
}

bool TextViewDialog::SaveFile(const string *file) {
	return SaveFile(file->getstr());
}

bool TextViewDialog::SaveFile(const char *file) {
	saveFile = file;
	char *t = XmTextGetString(textWidget);
	string text = t;
	if (FileUtils::Save(GetWidget(), file, &text)) {
		SetStatus("Save succeeded");
		XtFree(t);
		return True;
	}
	else {
		SetStatus("Save failed");
		XtFree(t);
		return False;
	}
}

bool TextViewDialog::LoadFile(const char *file) {
	string text;
	loadFile = file;
	if (FileUtils::Load(GetWidget(), file, &text)) {
		char *s = (char *)text.getstr();
		XmTextSetString(textWidget, s);
		short c;
		XtVaGetValues(textWidget, XmNcolumns, &c, NULL);
		SetStatus("Load succeeded");
		return True;
	}
	SetStatus("Load failed");
	return False;
}

bool TextViewDialog::LoadFile(const string *file) {
	return LoadFile(file->getstr());
}

void TextViewDialog::CopyCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->Copy();
}

void TextViewDialog::ClearSelectionCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->ClearSelection();
}

void TextViewDialog::ClearFindCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->ClearFind();
}

void TextViewDialog::FindCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->Find();
}

void TextViewDialog::FindNextCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->DoFind(0);
}

void TextViewDialog::FindAllCB(Widget, XtPointer cd, XtPointer) {
	TextViewDialog *t = (TextViewDialog *)cd;
	t->DoFind(1);
}

void TextViewDialog::InitMenuItems() {
	int i = 0;
	fileItems = new MenuItem[24]; i = 0;
	fileItems[i] = MenuItem(
		"Save As...", MenuItem::PUSHBUTTON, 'S', "Ctrl<Key>S", "Ctrl-S",
		TextViewDialog::SaveAsCB, (XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Print...", MenuItem::PUSHBUTTON, 'P', "Ctrl<Key>P", "Ctrl-P",
		TextViewDialog::PrintCB, (XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem::NUL;
	editItems = new MenuItem[24]; i = 0;
	editItems[i] = MenuItem(
		"Copy", MenuItem::PUSHBUTTON, 'C', "Ctrl<Key>C", "Ctrl-C",
		TextViewDialog::CopyCB, (XtPointer)this, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		"Clear Selection", MenuItem::PUSHBUTTON, 'S', "Ctrl<Key>B", 
		"Ctrl-B", TextViewDialog::ClearSelectionCB, (XtPointer)this, 
		0, 0, 1); i++;
	editItems[i] = MenuItem::NUL;
	searchItems = new MenuItem[24]; i = 0;
	searchItems[i] = MenuItem(
		"Find...", MenuItem::PUSHBUTTON, 'F', "Ctrl<Key>F", "Ctrl-F",
		TextViewDialog::FindCB, (XtPointer)this, 0, 0, 1); i++;
	searchItems[i] = MenuItem::NUL;
}
