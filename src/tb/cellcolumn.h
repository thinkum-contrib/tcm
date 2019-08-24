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
#ifndef _CELLCOLUMN_H
#define _CELLCOLUMN_H

#include "cellvector.h"
#include "tableviewer.h"

/// (table) column class.

int Compare(CellColumn *c1, CellColumn *c2);

class CellColumn: public CellVector {	
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	CellColumn(TableViewer *v, unsigned columnNumber, int width);

	///
	friend int Compare(CellColumn *c1, CellColumn *c2) {return *c1 == *c2;}

	/// make each cell width wide.
	void UpdateWidth(int width);	

	/// move each cell delta left/right.
	void UpdatePosition(int delta); 

	/// resize all cells from index rownr and lower.
	void UpdateHeight(unsigned rownr);	

	/// if (x,y) is on a linepiece, return it.
	LinePiece *HitLinePiece(int x, int y); 

	/// append cell to column.
	void AddCell(Cell *c, bool redraw=True); 		

	/// delete cell from column.
	void DeleteCell(Cell *c, bool redraw=True);	

	/// insert cell in column at position n.
	void InsertCell(Cell *c, unsigned n, bool redraw=True);
	
	///
	bool ContainsPt(int x, int y) const;

	/// write attributes (but not cell contents) to file.
	void Write(OutputFile *f);

	/// write part of column to file (only given rows).
	void WritePartial(OutputFile *f, int i, List<int> *rowNumbers);

	/// read attributes back from file starting at row n.
	bool Read(InputFile *f, unsigned fromRow, double format);

	///
	int GetMinimalWidth();

	///
	int GetWidth() const {return width;}

	///
	int GetMarginWidth() const {return GetViewer()->GetMarginWidth();}

	///
	void UpdateTextPositions();

	///
	void CalcLabelPositions();
private:
	/// width of a column = width of its cells which span 1 column.
	int width;
};
#endif
