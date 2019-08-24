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
#include "line.h"
#include "shapeview.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "updatetextcmd.h"

UpdateTextCmd::UpdateTextCmd(TextShape *s, const string *n, const string *o): 
		Command(s->GetView()->GetViewer()->GetDiagram(),
			s->GetView()->GetViewer()) {
	textShape = s;
	diagram = s->GetView()->GetViewer()->GetDiagram();
	parent = (GShape *)s->GetParent();
	newText = new string(*n);
	oldText = new string(*o);
	if (check(parent)) {
		oldWidth = parent->GetWidth();
		oldHeight = parent->GetHeight();
		if (parent->IsLine())
			oldParentPosition = *parent->GetPosition();
	}
}

UpdateTextCmd::~UpdateTextCmd() {
	delete newText;
	delete oldText;
}

void UpdateTextCmd::Execute() {
	if (parent && !parent->HasTextShape(textShape)) {
		GetMainWindow()->SetStatus("aborted: text is already deleted");
		Abort();
	}
	else
		Executable();
}

void UpdateTextCmd::Executable() {
	textShapePosition = *textShape->GetPosition();
	diagram->SetText(textShape, newText);
	parent->NotifyTextMove(textShape);
	if (parent->IsLine()) {
		((Line *)parent)->GetLine(oldParentPosition.x, 
					 oldParentPosition.y);
	}	
	Command::Execute();
}

void UpdateTextCmd::ReExecute() {
	if (parent && !parent->HasTextShape(textShape)) {
		Point pt = textShapePosition;
		TextShape *other = parent->ChooseTextShape(pt.x, pt.y);
		if (other) {
			textShape = other;
			Executable();
		}
		else {
			GetMainWindow()->SetStatus(
				"cannot redo: text shape is deleted by undo");
		}
	}
	else
		Executable();
}

void UpdateTextCmd::UnExecute() {
	if (parent && !parent->HasTextShape(textShape)) {
		GetMainWindow()->SetStatus("aborted: text is already deleted");
		return;
	}
	if (GetViewer()->IsAutoResize()) {
		if (parent) {
			if (parent->GetWidth() != oldWidth ||
		    	    parent->GetHeight() != oldHeight) {
				parent->UpdateSize(oldWidth, oldHeight);
				parent->GetView()->GetViewer()->
					ShapePositionUpdate(parent);
			}
			if (parent->IsLine())
				((Line *)parent)->GetLine(oldParentPosition.x, 
						 oldParentPosition.y);
		}
	}
	diagram->SetText(textShape, oldText);
	parent->NotifyTextMove(textShape);
	Command::UnExecute();
}
