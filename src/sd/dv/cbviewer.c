//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "cbviewer.h"
#include "cbwindow.h"
#include "cbupdateactortypecmd.h"
#include "subject.h"
#include "ssddoubleclassbox.h"		// compatibility
#include "ssdtripleclassbox.h"		// compatibility
#include "ssdupdateclassboxpropertycmd.h"
#include "updatemessagedirectioncmd.h"
#include "cbdmessage.h"
 
CBViewer::CBViewer(Config *c, CBWindow *w): ERViewer(c, w) { }

Command *CBViewer::Drag(int x, int y) {
	TextShape *textShape;
	double x1 = GetScaler()->ScaleCorrect(x);
	double y1 = GetScaler()->ScaleCorrect(y);
	// do note allow moving messages 
	if ((textShape = GetCurView()->HitTextShape(static_cast<int>(0.5 + x1),
										static_cast<int>(0.5 + y1), False))) {
		Subject *subj = textShape->GetParent()->GetSubject();

		if ((*textShape->GetDescription() == "Message") &&
		    ((subj->GetClassType() == Code::CBD_CLASS_LINK_EDGE) ||
			 (subj->GetClassType() == Code::CBD_OBJECT_LINK_EDGE))) {
			SetStatus("aborted: message can not be dragged");
			return 0;
		} 
	}
	return ERViewer::Drag(x,y);
}

void CBViewer::UpdateNodeShapeType(int actorType) {
	SetStatus("action: Update actor type");
	List<int *> t;
	t.add(new int(Code::UCD_SINGLE_CLASS_BOX));
	t.add(new int(Code::STICKMAN));
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new CBUpdateActorTypeCmd(
				GetCurView(), &t, actorType));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
	t.clear();
}


void CBViewer::UpdateShowStereotypes(bool b) {
	if (b)
		SetStatus("action: show stereotypes");
	else
		SetStatus("action: hide stereotypes");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(), 
				SSDUpdateClassBoxPropertyCmd::STEREOTYPE, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void CBViewer::UpdateShowProperties(bool b) {
	if (b)
		SetStatus("action: show properties");
	else
		SetStatus("action: hide properties");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(), 
				SSDUpdateClassBoxPropertyCmd::PROPERTIES, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void CBViewer::UpdateMessageDirection(TextShape *t, CBDMessage *msg, int k,
										ReadDirection::Type dir) {
	SetStatus("action: Update message direction");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new UpdateMessageDirectionCmd(GetCurView(), t, msg, k, dir));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}
