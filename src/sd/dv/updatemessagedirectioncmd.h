//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _UPDATEMESSAGEDIRECTIONCMD_H
#define _UPDATEMESSAGEDIRECTIONCMD_H

#include "command.h"
#include "readdirection.h"
class CBDMessage;
class TextShape;
class ShapeView;

/// command class for updating direction arrows in messages.
class UpdateMessageDirectionCmd: public Command {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	UpdateMessageDirectionCmd(ShapeView *view, TextShape *message, 
							CBDMessage *mesg, int msgNr, 
								ReadDirection::Type direction);
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "update message direction";}
private:
	///
	ReadDirection::Type direction;
	///
	ReadDirection::Type oldDirection;
	///
	TextShape *tshape;
	///
	CBDMessage *message;
	///
	int msgNr;
	///
	ShapeView *view;
};
#endif
