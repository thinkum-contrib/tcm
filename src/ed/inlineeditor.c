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
#include "grafport.h"
#include "inlineeditor.h"
#include "viewer.h"
#include "texteditdialog.h"
#include "editstubs.h"

InlineEditor::InlineEditor(Viewer *v) {
	viewer = v;
	text = "";
	textEditDialog = new TextEditDialog(
			viewer->GetMainWindow()->GetWidget());
	textEditDialog->Initialize();
	textEditDialog->SetTitle("Outline editor");
	textEditDialog->SetCancelCallback(EditStubs::UpdateTextCB, this);
	textEditDialog->SetOKCallback(EditStubs::UpdateTextCB, this);
	textEditDialog->SetTextSize(8, 40);
	oldtext = "";
	inUse = False;
	ignoreWindow = False;
	cursorPosition = Point(0,0);
	textPosition = Point(0,0);
	textFont = viewer->GetDefaultFont();
	alignment = TextAlign::CENTER;
	textColor = "black";
}

InlineEditor::~InlineEditor() {
	delete textEditDialog;
}

void InlineEditor::Draw() {
	Grafport *grafport = viewer->GetGrafport();
	if (!check(grafport))
		return;
	grafport->SetFont(textFont);
	grafport->SetForegroundColor(&textColor);
	if (alignment == TextAlign::LEFT) {
		cursorPosition = 
			grafport->DrawStringsLeft(
					textPosition.x, textPosition.y, 
					&text, IsUnderlined(), cursor);
	}
	else if (alignment == TextAlign::CENTER) {
		cursorPosition = 
			grafport->DrawStringsCentered(
					textPosition.x, textPosition.y, 
					&text, IsUnderlined(), cursor);
	}
	else if (alignment == TextAlign::RIGHT) {
		cursorPosition = 
			grafport->DrawStringsRight(
					textPosition.x, textPosition.y, 
					&text, IsUnderlined(), cursor);
	}
	grafport->DrawActiveCaret(cursorPosition.x, cursorPosition.y);
}

void InlineEditor::Undraw() {
	Draw();
}

void InlineEditor::AddChar(char c) {
	Undraw();
	text.insert(c, cursor++);
	Draw();
}

void InlineEditor::BackSpace() {
	if (cursor > 0 && text.length() > 0) {
		Undraw();
		text.remove(--cursor);
		Draw();
	}
}

void InlineEditor::Delete() {
	if (cursor < text.length()) {
		Undraw();
		text.remove(cursor);
		Draw();
	}
}

void InlineEditor::CharLeft() {
	if (cursor > 0) {
		Undraw();
		cursor--;
		Draw();
	}
}

void InlineEditor::CharRight() {
	if (cursor < text.length()) {
		Undraw();
		cursor++;
		Draw();
	}
}
 
void InlineEditor::CharUp() {
	int pos;
	int curLine = text.whichline(cursor, pos);
	if (pos == -1)
		pos = 0;
	if (curLine > 1) {
		Undraw();
		cursor = text.nthInline(curLine-1, pos);
		Draw();
	}
}

void InlineEditor::CharDown() {
	int pos;
	int curLine = text.whichline(cursor, pos);
	if (pos == -1)
		pos = 0;
	if (curLine != -1 && curLine < (int)text.lines()) {
		Undraw();
		cursor = text.nthInline(curLine+1, pos);
		Draw();
	}
}

void InlineEditor::Home() {
	Undraw();
	cursor = 0;
	Draw();
}
			
void InlineEditor::End() {
	Undraw();
	cursor = text.length();
	Draw();
}

void InlineEditor::Clear() {
	Undraw();
	int n = text.length();
	for (int i=0; i<n; i++)
		text.remove();
	cursor = 0;
	Draw();
}

void InlineEditor::SetCursor(int x, int y) {
	Undraw();
	Grafport *grafport = viewer->GetGrafport();
	cursor = grafport->CursorPosition(textPosition.x, 
			textPosition.y, &text, x, y);
	if (cursor > text.length())
		cursor = text.length();
	Draw();
}

void InlineEditor::SetCursor(int whichChar) {
	cursor = whichChar;
}

void InlineEditor::Abort() {
	if (!inUse)
		return;
	inUse=False;
	Undraw();
}

void InlineEditor::StopWindow(const string *t) {
	if (!inUse || ignoreWindow)
		return;
	inUse = False;
	text = *t;
	UpdateText();
	viewer->TextModeOff();
}
 
void InlineEditor::CancelWindow() {
	inUse = False;
	viewer->TextModeOff();
}
