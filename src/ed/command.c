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
#include "command.h"
#include "document.h"

Command::Command(Document *d, Viewer *v) {
	cmdDone = False;
	viewer = v;
	document = d;
	mainwindow = v->GetMainWindow();
	grafport = v->GetGrafport();
	viewer->TextModeOff();
	Command *lastcmd = viewer->GetLastCmd();
	if (lastcmd && (viewer->IsZigZag() || viewer->IsPasting())) {
		lastcmd->Abort();
	}
}

Command::~Command() {}

void Command::Execute() {
	cmdDone = True;
	document->IncChanges();
	SayCommited();
}

void Command::UnExecute() {
	cmdDone = False;
	document->DecChanges();
	SayUndone();
}

void Command::Abort() {
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
	viewer->AbortCommand();
}

void Command::SayCommited() {
	string txt = "commited: ";
	txt += GetName();
	mainwindow->SetStatus(&txt);
}

void Command::SayUndone() {
	string txt = "undone: ";
	txt += GetName();
	mainwindow->SetStatus(&txt);
}

void Command::SayAborted() {
	string txt = "aborted: ";
	txt += GetName();
	mainwindow->SetStatus(&txt);
}
