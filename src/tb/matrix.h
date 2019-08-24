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
#ifndef _MATRIX_H
#define _MATRIX_H

#include "table.h"

/// a table with some constraints on row and column zero.
class Matrix: public Table {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	Matrix(Config *c, TableWindow *t, TableViewer *v);
	///
	void CheckDocument();
	///
	bool UpdateText(Cell *c, const string *text);
protected:
	///
	virtual bool CheckTextString(Cell *c, const string *text);
	///
	unsigned CheckEmptyColumnEntries(unsigned row);
	///
	unsigned CheckEmptyRowEntries(unsigned column);
};
#endif
