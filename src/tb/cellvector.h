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
#ifndef _CELLVECTOR_H
#define _CELLVECTOR_H

#include "llist.h"
#include "lstring.h"
#include "textalign.h"
class TableViewer;
class RowColumnLabel;
class Cell;
class LinePiece;
class Grafport;
class InputFile;
class OutputFile;

/// abstract base class of table rows and columns.

class CellVector;
int Compare(CellVector *c1, CellVector *c2);

class CellVector {
/*@Doc: {\large {\bf scope:} table} */
public:
	/// creation.
	CellVector(TableViewer *v, unsigned number);

	virtual ~CellVector();			 

	/// -1,0,1 iff c1.number ==,<,> c2.number
	friend int operator==(const CellVector &c1, const CellVector &c2);

	/// -1,0,1 iff c1.number ==,<,> c2.number
	friend int Compare(CellVector *c1, CellVector *c2) {
		return operator==(*c1, *c2);}

	/// draw cell vector.
	void Draw();
	/// erase cell vector.
	void Undraw();

	///
	void DrawCells();
	///
	void UndrawCells();

	///
	void DrawLines();
	///
	void UndrawLines();

	///
	void DrawLabels();
	///
	void UndrawLabels();
	
	///
	void SetGrafport(Grafport *g);
	
	/// Make all cells and lines (in)visible.
	void SetVisible(bool b);

	///
	TableViewer *GetViewer() const {return viewer;}

	///
	virtual void UpdatePosition(int delta) =0;

	///
	virtual LinePiece *HitLinePiece(int x, int y) =0;

	///
	bool HasCell(Cell *c);

	///
	RowColumnLabel *HitLabel(int x, int y) const;

	/// append cell to column.
	virtual void AddCell(Cell *c, bool redraw=False)=0; 	

	/// delete cell from column.
	virtual void DeleteCell(Cell *c, bool redraw=False)=0;	

	/// insert cell in column.
	virtual void InsertCell(Cell *c, unsigned n, bool redraw=False)=0;

	///
	virtual bool ContainsPt(int x, int y) const =0;

	///
	virtual void Write(OutputFile *f) = 0;

	///
	virtual void WritePartial(OutputFile *f, int i, List<int> *nrs) = 0;

	///
	virtual bool Read(InputFile *f, unsigned from = 0, 
		double format = 1.0) = 0;

	///
	TextAlign::Type GetAlignment() const {return alignment;}
 
	///
	void SetAlignment(TextAlign::Type a);

	///
	void UpdateAlignment(TextAlign::Type a);

	///
	virtual void UpdateNumber(unsigned nr);

	///
	virtual void SetLabelsVisible(bool s) {labelsVisible = s;}

	///
	void SetNumber(unsigned nr);

	/// return first cell, 0 if cells is empty.
	Cell *FirstCell(); 	

	/// return next cell, 0 if cells is empty.
	Cell *NextCell();

	/// return n-th cell, 0 if n-th cell does not exist.
	Cell *NthCell(unsigned n);	

	/// return first line, 0 if lines is empty.
	LinePiece *FirstLine(); 

	/// return next line, 0 if lines is empty.
	LinePiece *NextLine();

	/// return n-th line, 0 if n-th line does not exist.
	LinePiece *NthLine(unsigned n);

	///
	unsigned GetNumber() const {return number;}

	///
	RowColumnLabel *GetLabel1() const {return label1;}
	///
	RowColumnLabel *GetLabel2() const {return label2;}
	///
	void UpdateLabel1(const string *txt);
	///
	void UpdateLabel2(const string *txt);

	///
	unsigned NrCells() const {return cells->count();}

	///
	int GetIndex(LinePiece *l) {return lines->find(l);}

	/// return nr of cells having empty texts.
	unsigned HasEmptyText();

	/// return nr of cells having this text.
	unsigned HasText(const string *s);

	///
	bool IsAllEmpty() {return HasEmptyText() == NrCells();}

	///
	void EmptyCells() {cells->empty();} // remove all from cells

	///
	virtual void CalcLabelPositions() = 0;
protected:
	/// the cells in the vector.
	List<Cell *> *cells;	

	/// cell boundaries between the cells in the vector. 
	List<LinePiece *> *lines; 

	///
	Grafport *GetGrafport() const {return grafport;}
private:
	///
	TableViewer *viewer;
	///
	Grafport *grafport;

	/// the row or column numbers.
	unsigned number;		

	/// a number label drawn near beginning of vector (like spreadsheet)
	RowColumnLabel *label1;	

	/// a number label drawn near end of vector.
	RowColumnLabel *label2;	

	/// is label number displayed ?
	bool labelsVisible;	

	/// beginning=left, end=right, center=center.
	TextAlign::Type alignment;
};
#endif
