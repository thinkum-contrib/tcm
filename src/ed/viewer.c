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
#include "viewer.h"
#include "command.h"
#include "printer.h"
#include "inlineeditor.h"
#include "config.h"
#include "scaledialog.h"
#include "ntogglelistdialog.h"
#include "linestyledialog.h"
#include "linewidthdialog.h"
#include "textalignmentdialog.h"
#include "fontchooserdialog.h"
#include "colorchooserdialog.h"
#include "editstubs.h"
#include "key.h"
#include <ctype.h>

const int Viewer::MIN_LINE_WIDTH=1;
const int Viewer::MAX_LINE_WIDTH=10;

Viewer::Viewer(Config *c, DrawWindow *d) {

	mainwindow = d;
	config = c;
	grafport = 0;
	scaler = new Scaler(c, this, d);
	lastCmd = -1;
	lastCmdIllegal = True;
	cmdHistSize = 0;
	edit = 0;
	printer = 0;
	editing = False;
	pasting = False;
	zigZag = False;
	// set these defaults from config.
	autoResizing = config->GetAutoResizing();
	inlineEditor = config->GetInlineEditor();
	defaultLineWidth=max(MIN_LINE_WIDTH, 
			     min(config->GetLineWidth(), MAX_LINE_WIDTH));
	defaultLineStyle=config->GetLineStyle();
	defaultLineColor=*config->GetLineColor();
	defaultTextColor=*config->GetTextColor();
	defaultFillColor=*config->GetFillColor();
	defaultFillStyle = FillStyle::UNFILLED;
	defaultTextAlignment = config->GetTextAlignment();
	defaultFont = new XFont(config->GetFontFoundry(), 
		config->GetFontFamily(), config->GetFontStyle(), 
		config->GetPointSize(), config->GetScalableFonts());
	defaultFont->SetUnderlined(config->GetUnderlined());
	fontList = new List<XFont *>;
	fontList->add(defaultFont);
	// font chooser stuff
	fontChooserDialog = new FontChooserDialog(d->GetWidget(),
												config->GetAddPointSizes());
	fontChooserDialog->Initialize();
	// color chooser stuff
	colorChooserDialog = new ColorChooserDialog(d->GetWidget());
	colorChooserDialog->Initialize();
	// line width stuff
	lineWidthDialog = new LineWidthDialog(d->GetWidget());
	lineWidthDialog->Initialize();
	// line style stuff
	lineStyleDialog = new LineStyleDialog(d->GetWidget());
	lineStyleDialog->Initialize();
	// text align stuff
	textAlignmentDialog = new TextAlignmentDialog(d->GetWidget());
	textAlignmentDialog->Initialize();

	ShowConfigLineStyle();
	ShowConfigLineWidth();
	ShowConfigTextAlignment();
	ShowConfigFont();
	ShowConfigLineColor();
}

Viewer::~Viewer() {
	delete scaler;
	if (edit)
		delete edit;
	fontList->clear();
	delete fontList;
	for (int i=0; i<cmdHistSize; i++)
		delete cmdHist[i];
	delete lineWidthDialog;
	delete lineStyleDialog;
	delete fontChooserDialog;
	delete colorChooserDialog;
	delete textAlignmentDialog;
}

void Viewer::Undo() {
	mainwindow->SetStatus("action: undo");
	if (!(pasting || zigZag))
		UndoCommand();
}

void Viewer::Redo() {
	mainwindow->SetStatus("action: redo");
	if (!(pasting || zigZag))
		RedoCommand();
}

Command *Viewer::GetLastCmd() {
	if (lastCmdIllegal || lastCmd < 0 || lastCmd >= cmdHistSize)
		return 0;
	else
		return cmdHist[lastCmd];
	
}

void Viewer::Refresh() {
	// can take a while ...
	mainwindow->SetCursor(MouseCursor::WATCH);
	TextModeOff();
	ClearGrafport();
	// draw itself.
	Redraw();
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

void Viewer::Redraw() {
	Draw();
	if (printer)
		printer->Draw();
}

FileSelectionDialog *Viewer::GetPrintFileSelectionDialog() {
	return printer->GetFileSelectionDialog();
}

void Viewer::ClearGrafport() {
	grafport->ClearArea(0,0,grafport->GetWidth(),grafport->GetHeight());
}

XFont *Viewer::GetFont(int family, int style, int size) {
	// look for font in font list.
	for (fontList->first(); !fontList->done(); fontList->next()) {
		XFont *ft = fontList->cur();
		if (ft->GetFamily() == family && ft->GetStyle() == style &&
		    ft->GetSize() == size) {
			return ft;
		}
	}
	// if not found, load new font and add to font list.
	XFont *newFont = new XFont(config->GetFontFoundry(), 
		family, style, size, config->GetScalableFonts());
	fontList->add(newFont);
	return newFont;
}

XFont *Viewer::GetFont(const char *description) {
	int family = XFont::FindFamily(description);
	int style = XFont::FindStyle(description);
	int size = XFont::FindSize(description);
	return GetFont(family, style, size);
}

void Viewer::SetDefaultFontAttributes(int f, int s, int p) { 
	if (defaultFont->GetFamily()==f && 
	    defaultFont->GetStyle()==s &&
	    defaultFont->GetSize()==p)
		return;
	SetDefaultFont(GetFont(f, s, p));
	printer->SetDefaultFont(f, s, p);
}

void Viewer::DoubleClick() {
	error("Double click is not implemented\n");
}

void Viewer::DoFunctionKey(int i) {
	error("Function key %d, (not implemented)\n", i); 
}

void Viewer::DeleteCommands() {
	lastCmd = -1;
	lastCmdIllegal = True;
	for (int i=0; i<cmdHistSize; i++)
		delete cmdHist[i];
	cmdHistSize = 0;
	mainwindow->SetUndoName("Undo");
	mainwindow->EnableUndo(False);
	mainwindow->SetRedoName("Redo");
	mainwindow->EnableRedo(False);
	TextModeOff();
}

void Viewer::NewCommand(Command *newcmd) {
	TextModeOff();
	if (!newcmd) {
		lastCmdIllegal = True;
		return;
	}
	lastCmdIllegal = False;
	// make space.
	if (lastCmd >= cmdHistSize-1 && cmdHistSize >= MAXHISTSIZE) {
		Command *delCmd = cmdHist[0];
		delete delCmd;
		for (int i=1; i<cmdHistSize; i++)
			cmdHist[i-1] = cmdHist[i];
		cmdHistSize--;
		lastCmd = cmdHistSize-1;
	}
	for (int i=lastCmd+1; i<cmdHistSize; i++)
		delete cmdHist[i];
	lastCmd++;
	cmdHistSize = lastCmd+1;
	cmdHist[lastCmd] = newcmd;
	string s = "Undo (";
	s += newcmd->GetName();
	s += ")";
	mainwindow->SetUndoName(s.getstr());
	mainwindow->EnableUndo(True);
	mainwindow->SetRedoName("Redo");
	mainwindow->EnableRedo(False);
}

void Viewer::AbortCommand() {
	if (!lastCmdIllegal && lastCmd >= 0 && check(lastCmd==cmdHistSize-1)) {
		delete cmdHist[lastCmd];
		lastCmd--;
		cmdHistSize--;
		if (lastCmd >= 0) {
			string s = "Undo (";
			s += cmdHist[lastCmd]->GetName();
			s += ")";
			mainwindow->SetUndoName(s.getstr());
			mainwindow->EnableUndo(True);
		}
		else {
			lastCmdIllegal = True;
			mainwindow->SetUndoName("Undo");
			mainwindow->EnableUndo(False);
		}
		mainwindow->SetRedoName("Redo");
		mainwindow->EnableRedo(False);
	}
}
 
void Viewer::ExecuteCommand() {
	if (lastCmdIllegal)
		return;
	TextModeOff();
	if (lastCmd >= 0 && check(lastCmd < cmdHistSize))
		cmdHist[lastCmd]->Execute();
}

void Viewer::UndoCommand() {
	if (lastCmdIllegal)
		return;
	if (edit && editing && inlineEditor) {
		edit->Abort();
		editing = False;
	}
	TextModeOff();
	Command *cmd = cmdHist[lastCmd];
	if (cmd) {
		string s;
		if (cmd->CmdDone()) {
			cmd->UnExecute();
			s = "Redo (";
			s += cmd->GetName();
			s += ")";
			mainwindow->SetRedoName(s.getstr());
			mainwindow->EnableRedo(True);
		}
		lastCmd--;
		if (lastCmd >= 0) {
			s = "Undo (";
			s += cmdHist[lastCmd]->GetName();
			s += ")";
			mainwindow->SetUndoName(s.getstr());
			mainwindow->EnableUndo(True);
			return;
		}
	}
	else
		mainwindow->SetStatus("there's nothing to undo");
	mainwindow->SetUndoName("Undo");
	mainwindow->EnableUndo(False);
}

void Viewer::RedoCommand() {
	if (lastCmdIllegal)
		return;
	TextModeOff();
	if (edit && editing && inlineEditor) {
		edit->Abort();
		editing = False;
	}
	if (lastCmd < -1 || lastCmd > cmdHistSize-1)
		return;
	lastCmd++;
	Command *cmd = cmdHist[lastCmd];
	if (cmd) {
		string s;
		if (!cmd->CmdDone()) {
			cmd->ReExecute();
			s = "Undo (";
			s += cmd->GetName();
			s += ")";
			mainwindow->SetUndoName(s.getstr());
			mainwindow->EnableUndo(True);
		}
		if (lastCmd >= 0 && lastCmd < cmdHistSize-1) {
			s = "Redo (";
			s += cmdHist[lastCmd+1]->GetName();
			s += ")";
			mainwindow->SetRedoName(s.getstr());
			mainwindow->EnableRedo(True);
			return;
		}
	}
	else
		mainwindow->SetStatus("there's nothing to redo");
	mainwindow->SetRedoName("Redo");
	mainwindow->EnableRedo(False);
}

void Viewer::EditText(int key) {
	if (!check(edit))
		return;
	if (key == Key::BACKSPACE) {
		edit->BackSpace();
		mainwindow->SetStatus("delete previous char");
	}
	else if (key == Key::DELETE) {
		edit->Delete();
		mainwindow->SetStatus("delete next char");
	}
	else if (key == Key::VERTICAL_TAB || key == Key::ESCAPE) {
		edit->Clear();
		mainwindow->SetStatus("delete all chars");
	}
	else if (key == Key::HOME || key == Key::RS) {
		edit->Home();
		mainwindow->SetStatus("move cursor to first char");
	}
	else if (key == Key::END || key == Key::FS) {
		edit->End();
		mainwindow->SetStatus("move cursor to last char");
	}
	else if (key == Key::LEFT) {
		edit->CharLeft();
		mainwindow->SetStatus("move cursor 1 char left");
	}
	else if (key == Key::DOWN) {
		edit->CharDown();
		mainwindow->SetStatus("move cursor 1 line down");
	}
	else if (key == Key::UP) {
		edit->CharUp();
		mainwindow->SetStatus("move cursor 1 line up");
	}
	else if (key == Key::RIGHT) {
		edit->CharRight();
		mainwindow->SetStatus("move cursor 1 char right");
	}
	else {
		unsigned char c = (unsigned char)key;
		if (key == '\r')
			key = '\n';
		if (!iscntrl(c) || key == '\n')
			edit->AddChar(key);
		else
		 	mainwindow->SetStatus("ignoring char");
	}
}

void Viewer::GetPageSize(double &w, double &h) {
	if (printer)
		printer->GetPageSize(w, h);
}

void Viewer::SetAutoResize(bool s) {
	string buf = "Autoresize is ";
	if (s)
		buf += "True";
	else
		buf += "False";
	mainwindow->SetStatus(&buf);
	autoResizing = s;
}

void Viewer::SetInlineEdit(bool s) {
	string buf = "In-line edit is ";
	if (s)
		buf += "True";
	else
		buf += "False";
	mainwindow->SetStatus(&buf);
	TextModeOff();
	inlineEditor = s;
}

void Viewer::DefaultLineWidth() {
	mainwindow->SetStatus("action: default line width");
	lineWidthDialog->SetTitle("default line width");
	lineWidthDialog->SetHelpCallback(
	 	EditStubs::DefaultLineWidthDefaultCB, this);
	lineWidthDialog->SetOKCallback(
		EditStubs::DefaultLineWidthOKCB, this);
	ShowDefaultLineWidth();
	lineWidthDialog->Popup();
}

void Viewer::UpdateLineWidth() {
	mainwindow->SetStatus("action: update line width");
	lineWidthDialog->SetTitle("update line width");
	lineWidthDialog->SetHelpCallback(
	 	EditStubs::UpdateLineWidthDefaultCB, this);
	lineWidthDialog->SetOKCallback(
		EditStubs::UpdateLineWidthOKCB, this);
	lineWidthDialog->Popup();
}

void Viewer::SetDefaultLineWidth(unsigned d) {
	defaultLineWidth=max(MIN_LINE_WIDTH, min(d, MAX_LINE_WIDTH));
	// otherwise some problems with pixel droppings.
	Refresh();
}

void Viewer::DefaultLineColor() {
	mainwindow->SetStatus("action: default line color");
	colorChooserDialog->SetTitle("default line color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::DefaultLineColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::DefaultLineColorOKCB, this);
	colorChooserDialog->ManageFillToggle(False);
	ShowDefaultLineColor();
	colorChooserDialog->Popup();
}

void Viewer::UpdateLineColor() {
	mainwindow->SetStatus("action: update line color");
	colorChooserDialog->SetTitle("update line color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::UpdateLineColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::UpdateLineColorOKCB, this);
	colorChooserDialog->ManageFillToggle(False);
	colorChooserDialog->Popup();
}

void Viewer::ShowConfigLineColor() {
	colorChooserDialog->SetTextString(config->GetLineColor());
	colorChooserDialog->SelectItem(config->GetLineColor());
}

void Viewer::ShowDefaultLineColor() {
	colorChooserDialog->SetTextString(&defaultLineColor);
	colorChooserDialog->SelectItem(&defaultLineColor);
}

void Viewer::DefaultTextColor() {
	mainwindow->SetStatus("action: default text color");
	colorChooserDialog->SetTitle("default text color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::DefaultTextColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::DefaultTextColorOKCB, this);
	colorChooserDialog->ManageFillToggle(False);
	ShowDefaultTextColor();
	colorChooserDialog->Popup();
}

void Viewer::UpdateTextColor() {
	mainwindow->SetStatus("action: update text color");
	colorChooserDialog->SetTitle("update text color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::UpdateTextColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::UpdateTextColorOKCB, this);
	colorChooserDialog->ManageFillToggle(False);
	colorChooserDialog->Popup();
}

void Viewer::ShowConfigTextColor() {
	colorChooserDialog->SetTextString(config->GetTextColor());
	colorChooserDialog->SelectItem(config->GetTextColor());
}

void Viewer::ShowDefaultTextColor() {
	colorChooserDialog->SetTextString(&defaultTextColor);
	colorChooserDialog->SelectItem(&defaultTextColor);
}

void Viewer::DefaultFillColor() {
	mainwindow->SetStatus("action: default fill color");
	colorChooserDialog->SetTitle("default fill color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::DefaultFillColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::DefaultFillColorOKCB, this);
	colorChooserDialog->SetFillToggle(defaultFillStyle==FillStyle::FILLED);
	colorChooserDialog->ManageFillToggle(True);
	colorChooserDialog->SetFillToggleLabel("fill shapes by default");
	ShowDefaultFillColor();
	colorChooserDialog->Popup();
}

void Viewer::UpdateFillColor() {
	mainwindow->SetStatus("action: update fill color");
	colorChooserDialog->SetTitle("update fill color");
	colorChooserDialog->SetHelpCallback(
	 	EditStubs::UpdateFillColorDefaultCB, this);
	colorChooserDialog->SetOKCallback(
		EditStubs::UpdateFillColorOKCB, this);
	colorChooserDialog->ManageFillToggle(True);
	colorChooserDialog->SetFillToggleLabel("fill selected shapes");
	colorChooserDialog->Popup();
}

void Viewer::ShowConfigFillColor() {
	colorChooserDialog->SetTextString(config->GetFillColor());
	colorChooserDialog->SelectItem(config->GetFillColor());
}

void Viewer::ShowDefaultFillColor() {
	colorChooserDialog->SetTextString(&defaultTextColor);
	colorChooserDialog->SelectItem(&defaultTextColor);
}

void Viewer::DefaultLineStyle() {
	mainwindow->SetStatus("action: default line style");
	lineStyleDialog->SetTitle("default line style");
	lineStyleDialog->SetHelpCallback(
	 	EditStubs::DefaultLineStyleDefaultCB, this);
	lineStyleDialog->SetOKCallback(
		EditStubs::DefaultLineStyleOKCB, this);
	ShowDefaultLineStyle();
	lineStyleDialog->Popup();
}

void Viewer::UpdateLineStyle() {
	mainwindow->SetStatus("action: update line style");
	lineStyleDialog->SetTitle("update line style");
	lineStyleDialog->SetHelpCallback(
	 	EditStubs::UpdateLineStyleDefaultCB, this);
	lineStyleDialog->SetOKCallback(
		EditStubs::UpdateLineStyleOKCB, this);
	lineStyleDialog->Popup();
}

void Viewer::ShowDefaultLineWidth() {
	string text = defaultLineWidth;
	lineWidthDialog->SetValueOfText(0, &text);
}

void Viewer::ShowConfigLineWidth() {
	string text = config->GetLineWidth();
	lineWidthDialog->SetValueOfText(0, &text);
}

void Viewer::ShowDefaultLineStyle() {
	string text;
	LineStyle::Type2String(defaultLineStyle, &text);
	lineStyleDialog->SetValueOfText(0, &text);
}

void Viewer::ShowConfigLineStyle() {
	string text;
	LineStyle::Type2String(config->GetLineStyle(), &text);
	lineStyleDialog->SetValueOfText(0, &text);
}

void Viewer::DefaultFont() {
	mainwindow->SetStatus("action: default font");
	fontChooserDialog->SetTitle("default text font");
	fontChooserDialog->SetOKCallback(
	 	EditStubs::DefaultFontOKCB, this);
	fontChooserDialog->SetHelpCallback(
	 	EditStubs::DefaultFontDefaultCB, this);
	fontChooserDialog->SetOptionsVisible(False);
	ShowDefaultFont();
	fontChooserDialog->Popup();
}

void Viewer::UpdateFont() {
	mainwindow->SetStatus("action: update font");
	fontChooserDialog->SetTitle("update text font");
	fontChooserDialog->SetOKCallback(
	 	EditStubs::UpdateFontOKCB, this);
	fontChooserDialog->SetHelpCallback(
	 	EditStubs::UpdateFontDefaultCB, this);
	fontChooserDialog->SetOptionsVisible(True);
	fontChooserDialog->ShowExample();
	fontChooserDialog->Popup();
}

void Viewer::ShowDefaultFont() {
	mainwindow->SetStatus("show default font");
	fontChooserDialog->SetFamily(defaultFont->GetFamily());
	fontChooserDialog->SetStyle(defaultFont->GetStyle());
	fontChooserDialog->SetSize(defaultFont->GetSize());
	fontChooserDialog->ShowExample();
}

void Viewer::ShowConfigFont() {
	mainwindow->SetStatus("show config font");
	fontChooserDialog->SetFamily(config->GetFontFamily());
	fontChooserDialog->SetStyle(config->GetFontStyle());
	fontChooserDialog->SetSize(config->GetPointSize());
	fontChooserDialog->ShowExample();
}

void Viewer::DefaultTextAlignment() {
	mainwindow->SetStatus("action: default text alignment");
	textAlignmentDialog->SetTitle("default text alignment");
	textAlignmentDialog->SetHelpCallback(
	 	EditStubs::DefaultTextAlignmentDefaultCB, this);
	textAlignmentDialog->SetOKCallback(
		EditStubs::DefaultTextAlignmentOKCB, this);
	ShowDefaultTextAlignment();
	textAlignmentDialog->Popup();
}

void Viewer::UpdateTextAlignment() {
	mainwindow->SetStatus("action: update text alignment");
	textAlignmentDialog->SetTitle("update text alignment");
	textAlignmentDialog->SetHelpCallback(
	 	EditStubs::UpdateTextAlignmentDefaultCB, this);
	textAlignmentDialog->SetOKCallback(
		EditStubs::UpdateTextAlignmentOKCB, this);
	textAlignmentDialog->Popup();
}

void Viewer::ShowDefaultTextAlignment() {
	string text;
	TextAlign::Type2String(defaultTextAlignment, &text);
	textAlignmentDialog->SetValueOfText(0, &text);
}

void Viewer::ShowConfigTextAlignment() {
	string text;
	TextAlign::Type2String(config->GetTextAlignment(), &text);
	textAlignmentDialog->SetValueOfText(0, &text);
}

void Viewer::Save(OutputFile *f) {
	printer->Save(f);
	scaler->Save(f);
}

bool Viewer::Load(InputFile *f, double format) {
	return (printer->Load(f, format) &&
		scaler->Load(f, format));
}

bool Viewer::Check(InputFile *f, double format) {
	return (printer->Check(f, format) &&
		scaler->Check(f, format));
}
