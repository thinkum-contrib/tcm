//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _UPDATETEXTUNDERLINECMD_H
#define _UPDATETEXTUNDERLINECMD_H

#include "command.h"
class GShape;
class ShapeView;

/// command class for updating underlining of text shapes.
class UpdateTextUnderlineCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	UpdateTextUnderlineCmd(ShapeView *view);
	///
	virtual ~UpdateTextUnderlineCmd();
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "set/unset text underlining";}
private:
	///
	List<TextShape *> *textShapes;
};
#endif
