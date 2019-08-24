////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "celltexteditor.h"
#include "texteditdialog.h"
#include "celltext.h"
#include "cell.h"
#include "tableviewer.h"
#include "drawwindow.h"

CellTextEditor::CellTextEditor(TableViewer *v): InlineEditor(v) { }

void CellTextEditor::Start(CellText *t) {
	if (IsInUse())
		return;
	SetInUse(True);
	SetIgnoreWindow(True);
	cellText = t;
	SetText(t->GetText());
	SetOldText(t->GetText());
	SetTextFont(cellText->GetFont());
	// set text edit position to center of cell.
	Point pt = *t->GetParent()->GetPosition();
	SetTextPosition(&pt);
	SetAlignment(TextAlign::CENTER);
	cellText->UndrawAligned((t->GetParent())->GetColumnAlignment());
	SetCursor(GetText()->length());
	Draw();
}

void CellTextEditor::Abort() {
	InlineEditor::Abort();
	cellText->DrawAligned((cellText->GetParent())->GetColumnAlignment());
}

void CellTextEditor::Stop() {
	if (!IsInUse())
		return;
	Abort();
	UpdateText();
}

void CellTextEditor::StartWindow(CellText *t) {
	if (IsInUse())
		return;
	SetInUse(True);
	SetIgnoreWindow(False);
	cellText = t;
	SetText(t->GetText());
	const string *s = t->GetText();
	// window contains at least 25 columns and at most 80 columns.
	// int columns = min(80, max(25, s->width()));
	// window contains at least 4 lines and at most 40 lines.
	// int lines = min(40, max(4, s->lines()));
	// textEditDialog->SetTextSize(lines, columns);
	GetTextEditDialog()->SetTitle("Edit cell");
	GetTextEditDialog()->SetTextString(s);
	GetTextEditDialog()->Popup();
}

void CellTextEditor::UpdateText() {
	string t = *GetText();
	t.replace('\n', '\r');
	if (t != *cellText->GetText())
		((TableViewer *)GetViewer())->UpdateText(
			cellText->GetParent(), &t);
}
