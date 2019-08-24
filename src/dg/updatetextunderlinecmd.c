////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "textshape.h"
#include "gshape.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "updatetextunderlinecmd.h"

UpdateTextUnderlineCmd::UpdateTextUnderlineCmd(ShapeView *v): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	textShapes = new List<TextShape *>;
	List<GShape *> *selection = v->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		textShapes->add(shape->GetName());
	}
}

UpdateTextUnderlineCmd::~UpdateTextUnderlineCmd() {
	delete textShapes;
}

void UpdateTextUnderlineCmd::Execute() {
	if (!textShapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no texts need to be underlined");
		Abort();
		return;
	}
	for (textShapes->first(); !textShapes->done(); textShapes->next()) 
		textShapes->cur()->UpdateUnderlined(
			!textShapes->cur()->IsUnderlined());
	Command::Execute();
}

void UpdateTextUnderlineCmd::UnExecute() {
	for (textShapes->first(); !textShapes->done(); textShapes->next()) 
		textShapes->cur()->UpdateUnderlined(
			!textShapes->cur()->IsUnderlined());
	Command::UnExecute();
}
