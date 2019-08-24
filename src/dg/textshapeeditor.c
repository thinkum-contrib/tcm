////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "grafport.h"
#include "textshapeeditor.h"
#include "nodeshape.h"
#include "texteditdialog.h"
#include "diagramviewer.h"
#include "drawwindow.h"
#include "updatetextcmd.h"

TextShapeEditor::TextShapeEditor(DiagramViewer *v): InlineEditor(v) {
	 GetTextEditDialog()->SetTextSize(4, 20);
}

void TextShapeEditor::Start(TextShape *textShape) {
	if (IsInUse())
		return;
	saveBackground = "";
	SetInUse(True);
	SetIgnoreWindow(True);
	textshape = textShape;
	SetText(textshape->GetString());
	SetOldText(textshape->GetString());
	SetTextFont(textShape->GetFont());
	SetAlignment(TextAlign::CENTER);
	SetUnderlined(textShape->IsUnderlined());
	Point pt = *textshape->GetPosition();
	SetTextPosition(&pt);
	SetCursor(GetText()->length());
	string oldBackground;
	SetBackground();
	textShape->Undraw();
	RestoreBackground();
	Draw();
}

void TextShapeEditor::Abort() {
	InlineEditor::Abort();
	SetBackground();
	textshape->Undraw();
	RestoreBackground();
}

void TextShapeEditor::Stop() {
	if (!IsInUse())
	 	return;
	Abort();
	UpdateText();
}

void TextShapeEditor::StartWindow(TextShape *textShape) {
	if (GetTextEditDialog()->IsManaged())
		return;
	SetInUse(True);
	SetIgnoreWindow(False);
	textshape = textShape;
	SetText(textshape->GetString());
	SetOldText(textshape->GetString());
	const string *s = textshape->GetString();
	string title = "";
	title += *textshape->GetDescription();
	GetTextEditDialog()->SetTitle(&title);
	GetTextEditDialog()->SetTextString(s);
	GetTextEditDialog()->Popup();
} 

void TextShapeEditor::UpdateText() {
	string t = *GetText();
	t.replace('\n', '\r');
	((DiagramViewer *)GetViewer())->UpdateText(textshape, &t, GetOldText());
}

void TextShapeEditor::Draw() {
	SetBackground();
	InlineEditor::Draw();
	RestoreBackground();
}

void TextShapeEditor::SetBackground() {
	Shape *parent = textshape->GetParent();
	Grafport *g = GetViewer()->GetGrafport();
	if (parent && parent->IsNodeShape() &&
		 ((NodeShape *)parent)->GetFillStyle() != FillStyle::UNFILLED) {
		 saveBackground = *g->GetBackgroundColor();
		 g->SetBackgroundColor(((NodeShape *)parent)->GetFillColor());
	}
}

void TextShapeEditor::RestoreBackground() {
	if (saveBackground != "") {
		Grafport *g = GetViewer()->GetGrafport();
		g->SetBackgroundColor(&saveBackground);
	}
}
