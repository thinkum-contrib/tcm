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
#include "helper.h"
#include "toolkit.h"
#include "system.h"
#include "mainwindow.h"
#include "textviewdialog.h"

Helper::Helper(Config *c, MainWindow *w) {
	mainwindow = w;
	config = c;
	helpDialog = new TextViewDialog(w->GetWidget());
	helpDialog->Initialize();
	helpDialog->SetTextSize(16, 72);
}

Helper::~Helper() {
	if (helpDialog)
		delete helpDialog;
}

void Helper::Help(HelpTopicType tp) {
	SetStatus("action: Help");
	int tool = mainwindow->GetTool();

	char toolkit_help[MAXNAME];
	System::GetToolkitHelp(toolkit_help);
	string helpFile = toolkit_help;

	switch(tp) {
	case WELCOME:
		helpDialog->SetTitle("Help: Welcome to TCM");
		helpFile += "Welcome";
		break;
	case STARTING_EDITORS:
		helpDialog->SetTitle("Help: Starting Editors");
		helpFile += "StartingEditors";
		break;
	case GETTING_STARTED:
		helpDialog->SetTitle("Help: Getting Started");
		helpFile += "GettingStarted";
		break;
	case TOOL_INTRO: {
		string title = "Help: ";
		title += "Introduction to ";
		title += Toolkit::TOOL_NAMES[tool];
		helpDialog->SetTitle(&title);
		helpFile += Toolkit::TOOL_NAMES[tool];
		helpFile += "Intro";
		break;
	}
	case THE_MAIN_WINDOW:
		if (Toolkit::TableEditor(tool)) {
			helpDialog->SetTitle("Help: Table Editor Main Window");
			helpFile += "TableMainWindow";
		}
		else if (Toolkit::TextEditor(tool)) {
			helpDialog->SetTitle("Help: Text Editor Main Window");
			helpFile += "TextMainWindow";
		}
		else {
			helpDialog->SetTitle(
				"Help: Diagram Editor Main Window");
			helpFile += "DiagramMainWindow";
		}
		break;
	case MOUSE_COMMANDS:
		if (Toolkit::TableEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Table Editor Mouse Commands");
			helpFile += "TableMouseCommands";
		}
		else if (Toolkit::TextEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Text Editor Mouse Commands");
			helpFile += "TextMouseCommands";
		}
		else  {
			helpDialog->SetTitle(
				"Help: Diagram Editor Mouse Commands");
			helpFile += "DiagramMouseCommands";
		}
		break;
	case EDIT_COMMANDS:
		if (Toolkit::TableEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Table Editor Edit Menu Commands");
			helpFile += "TableEditCommands";
		}
		else if (Toolkit::TextEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Text Editor Edit Menu Commands");
			helpFile += "TextEditCommands";
		}
		else {
			helpDialog->SetTitle(
				"Help: Diagram Editor Edit Menu Commands");
			helpFile += "DiagramEditCommands";
		}
		break;
	case FILE_COMMANDS:
		helpDialog->SetTitle("Help: File Menu Commands");
		helpFile += "FileMenuCommands";
		break;
	case PRINT_PAGE_COMMANDS:
		helpDialog->SetTitle("Help: Print and Page Commands");
		helpFile += "PrintPageCommands";
		break;
	case MISC_COMMANDS:
		if (Toolkit::TableEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Miscellaneous Table Editor Commands");
			helpFile += "TableMiscCommands";
		}
		else if (Toolkit::TextEditor(tool)) {
			helpDialog->SetTitle(
				"Help: Miscellaneous Text Editor Commands");
			helpFile += "TextMiscCommands";
		}
		else {
			helpDialog->SetTitle(
				"Help: Miscellaneous Diagram Editor Commands");
			helpFile += "DiagramMiscCommands";
		}
		break;
	case VERSION:
		helpDialog->SetTitle("Help: Version");
		helpFile += "Version";
		break;
	case COPYING:
		helpDialog->SetTitle("Help: Copying");
		helpFile += "COPYING";
		break;
	case CHANGELOG:
		helpDialog->SetTitle("Help: Change log");
		helpFile += "CHANGELOG";
		break;
	default:
		error("Error: this help topic is not available\n");
		return;
	}
	if (!System::FileRegular(helpFile.getstr())) {
		error("Can not find help file '%s'\n", helpFile.getstr());
		return;
	}
	if (helpDialog->LoadFile(&helpFile))
		helpDialog->Popup();
}

void Helper::SetStatus(const char *msg) {
	mainwindow->SetStatus(msg);
}

void Helper::SetStatus(const string *msg) {
	mainwindow->SetStatus(msg);
}
