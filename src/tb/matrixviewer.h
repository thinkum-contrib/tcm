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
#ifndef _MATRIXVIEWER_H
#define _MATRIXVIEWER_H

#include "tableviewer.h"
class CellVector;

/// a table in which column and row 0 are different in layout.
class MatrixViewer: public TableViewer {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	MatrixViewer(Config *c, TableWindow *t);
	///
	void Initialize();
	///
	void AddRow(CellRow *c);
	///
	void AddColumn(CellColumn *c);
	///
	void InsertRow(CellRow *c);
	///
	void InsertColumn(CellColumn *c);
private:
	///
	void SetNthLine(CellVector *v, int n, LineStyle::Type t);
};
#endif
