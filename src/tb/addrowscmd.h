//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _ADDROWSCMD_H
#define _ADDROWSCMD_H

#include "command.h"
class TableViewer;
class Table;
class CellRow;

/// add rows to table command.
class AddRowsCmd: public Command {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	AddRowsCmd(Table *t, TableViewer *v, int numberOfRows, int rowPosition);
	///
	virtual ~AddRowsCmd();
	///
	void Execute();
	///
	void UnExecute();
	///
	void ReExecute();
	///
	const char *GetName() const {return "add rows";}
private:
	///
	int rowPosition;
	///
	int numberOfRows;
	///
	List<CellRow *> *rows;
	///
	TableViewer *tviewer;
};
#endif
