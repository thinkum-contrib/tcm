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
#include "texteditdialog.h"
#include "fileselectiondialog.h"
#include "replacedialog.h"
#include "menu.h"
#include "system.h"
#include <Xm/XmAll.h>

TextEditDialog::TextEditDialog(Widget w): TextViewDialog(w) {
	SetReplaceDialog(0);
}

void TextEditDialog::Configure() {
	TextViewDialog::Configure();
	if (check(GetWidget())) {
		XtVaSetValues(GetTextWidget(), 
			XmNeditable, True,
			XmNcursorPositionVisible, True, NULL);
		ManageCancelButton(True);
		SetOKButtonLabel("Ok");
		XtManageChild(GetTextWidget());
		ReplaceDialog *r = new ReplaceDialog(GetWidget());
		r->Initialize();
		r->SetTitle("Replace text in dialog");
		r->SetOKCallback(ReplaceFindCB, this);
		r->SetReplaceCallback(ReplaceNextCB, this);
		r->SetApplyCallback(ReplaceAllCB, this);
		r->SetHelpCallback(ClearReplaceCB, this);
		SetReplaceDialog(r);
	}
}

void TextEditDialog::Replace() {
	GetReplaceDialog()->Popup();
}

void TextEditDialog::ClearReplace() {
	int pos = XmTextGetLastPosition(GetTextWidget());
	XmTextSetHighlight(GetTextWidget(), 0, pos, XmHIGHLIGHT_NORMAL);
	GetReplaceDialog()->SetTextString("");
	GetReplaceDialog()->SetReplaceText("");
	SetStatus("action: Clear highlight");
}

void TextEditDialog::CutCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->Cut();
}

void TextEditDialog::PasteCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->Paste();
}

void TextEditDialog::DeleteAllCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->DeleteAll();
}

void TextEditDialog::ReplaceCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->Replace();
}

void TextEditDialog::ReplaceNextCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->DoFind(2);
}

void TextEditDialog::ReplaceAllCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->DoFind(3);
}

void TextEditDialog::ReplaceFindCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->DoFind(4);
}

void TextEditDialog::ClearReplaceCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->ClearReplace();
}

void TextEditDialog::Load() {
	FileSelectionDialog *fs = GetFileSelectionDialog();
	fs->SetTitle("Load text from file into dialog");
	fs->SetDefaultFile("");
	fs->SetOKCallback(LoadOKCB, this);
	fs->Popup();
}

void TextEditDialog::LoadCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	t->Load();
}

void TextEditDialog::LoadOKCB(Widget, XtPointer cd, XtPointer) {
	TextEditDialog *t = (TextEditDialog *)cd;
	char fname[MAXNAME];
	t->GetFileSelectionDialog()->GetFileName(fname);
	(void) t->LoadFile(fname);
}

void TextEditDialog::InitMenuItems() {
	int i = 0;
	fileItems = new MenuItem[24]; i = 0;
	fileItems[i] = MenuItem(
		"Load...", MenuItem::PUSHBUTTON, 'L', "Ctrl<Key>L", "Ctrl-L",
		TextEditDialog::LoadCB, (XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Save As...", MenuItem::PUSHBUTTON, 'S', "Ctrl<Key>S", "Ctrl-S",
		TextViewDialog::SaveAsCB, (XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem(
		"Print...", MenuItem::PUSHBUTTON, 'P', "Ctrl<Key>P", "Ctrl-P",
		TextViewDialog::PrintCB, (XtPointer)this, 0, 0, 1); i++;
	fileItems[i] = MenuItem::NUL;

	editItems = new MenuItem[24]; i = 0;
	editItems[i] = MenuItem(
		"Cut", MenuItem::PUSHBUTTON, 'C', "Ctrl<Key>X", "Ctrl-X",
		TextEditDialog::CutCB, (XtPointer)this, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		"Copy", MenuItem::PUSHBUTTON, 'o', "Ctrl<Key>C", "Ctrl-C",
		TextEditDialog::CopyCB, (XtPointer)this, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		"Paste", MenuItem::PUSHBUTTON, 'P', "Ctrl<Key>Y", "Ctrl-Y",
		TextEditDialog::PasteCB, (XtPointer)this, 0, 0, 1); i++;
	editItems[i] = MenuItem(
		"Clear Selection", MenuItem::PUSHBUTTON, 'S', "Ctrl<Key>B", 
		"Ctrl-B", TextEditDialog::ClearSelectionCB, (XtPointer)this, 
		0, 0, 1); i++;
	editItems[i] = MenuItem("", MenuItem::SEPARATOR); i++;
	editItems[i] = MenuItem(
		"Delete All", MenuItem::PUSHBUTTON, 'D', "Ctrl<Key>D", "Ctrl-D",
		TextEditDialog::DeleteAllCB, (XtPointer)this, 0, 0, 1); i++;
	editItems[i] = MenuItem::NUL;

	searchItems = new MenuItem[24]; i = 0;
	searchItems[i] = MenuItem(
		"Find...", MenuItem::PUSHBUTTON, 'F', "Ctrl<Key>F", "Ctrl-F",
		TextViewDialog::FindCB, (XtPointer)this, 0, 0, 1); i++;
	searchItems[i] = MenuItem(
		"Replace...", MenuItem::PUSHBUTTON, 'R', "Ctrl<Key>Z", "Ctrl-Z",
		TextEditDialog::ReplaceCB, (XtPointer)this, 0, 0, 1); i++;
	searchItems[i] = MenuItem::NUL;
}
