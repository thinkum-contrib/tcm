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
#ifndef _CELLROW_H
#define _CELLROW_H

#include "cellvector.h"
#include "tableviewer.h"

/// (table) row class.

int Compare(CellRow *r1, CellRow *r2);

class CellRow: public CellVector {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	CellRow(TableViewer *v, unsigned rowNumber, int height);

	///
	friend int Compare(CellRow *r1, CellRow *r2) {return *r1 == *r2;}

	/// each cell will be this height.
	void UpdateHeight(int height); 

	/// each cell is moved delta up/down
	void UpdatePosition(int delta);

	/// resize cells and lines from index cellnr and higher.
	void UpdateWidth(unsigned celnr);

	/// if (x,y) is in a cell, return it.
	Cell *HitCell(int x, int y);	

	/// if (x,y) is on a line piece, return it.
	LinePiece *HitLinePiece(int x, int y); 

	/// append cell to row.
	void AddCell(Cell *c, bool redraw=True); 		

	/// delete cell from row.
	void DeleteCell(Cell *c, bool redraw=True);	

	/// insert cell in row, at position p.
	void InsertCell(Cell *c, unsigned p, bool redraw=True);

	/// write attributes (including cell contents to file.
	void Write(OutputFile *f);	

	/// write part of row to file (only given columns).
	void WritePartial(OutputFile *f, int i, List<int> *columnNumbers);	

	/// read attributes back from file starting at position n.
	bool Read(InputFile *f, unsigned fromColumn, double format);

	///
	bool ContainsPt(int x, int y) const;

	///
	int GetMinimalHeight();

	///
	int GetHeight() const {return height;}

	///
	int GetMarginHeight() const {return GetViewer()->GetMarginHeight();}

	/// recalculate text positions in cells.
	void UpdateTextPositions(); 

	/// recalculate text size in cells.
	void SetTextSizes();

	///
	void CalcLabelPositions();
private:
	/// the height of a row is the height of its cells which span 1 row.
	int height;		 
};
#endif
