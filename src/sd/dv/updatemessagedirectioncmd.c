////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "line.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "updatemessagedirectioncmd.h"
#include "cbdmessage.h"

UpdateMessageDirectionCmd::UpdateMessageDirectionCmd(ShapeView *v, 
		TextShape *t, CBDMessage *mesg, 	
		int nr, ReadDirection::Type dir): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	tshape = t;
	message = mesg;
	msgNr = nr;
	direction = dir;
	oldDirection = t->GetReadDirection();
}

void UpdateMessageDirectionCmd::Execute() {
//	CBDMessage::DirectionType MsgDirection = message->GetDirection();
	view->Undraw();
	message->SetDirection((CBDMessage::DirectionType) direction);
	Command::Execute();
	view->Draw();
}

void UpdateMessageDirectionCmd::UnExecute() {
	message->SetDirection((CBDMessage::DirectionType) oldDirection);
	tshape->UpdateReadDirection(oldDirection);
	Command::UnExecute();
}
