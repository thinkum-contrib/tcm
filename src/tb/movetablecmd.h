//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _MOVETABLECMD_H
#define _MOVETABLECMD_H

#include "point.h"
#include "command.h"
#include "document.h"
class TableViewer;
class Table;

/// move entire table in mainwindow.
class MoveTableCmd: public Command {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	MoveTableCmd(Table *t, TableViewer *v, Document::MoveType m);
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "move table";}
private:
	///
	Document::MoveType moveType;
	///
	Point oldPosition;
	///
	static const int MOVE_DISTANCE;
};
#endif
