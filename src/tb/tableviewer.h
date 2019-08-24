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
#ifndef _TABLEVIEWER_H
#define _TABLEVIEWER_H

#include "point.h"
#include "lstring.h"
#include "llist.h"
#include "bool.h"
#include "textalign.h"
#include "side.h"
#include "linepiece.h"
#include "viewer.h"
#include "cellselection.h"
class TableWindow;
class Table;
class CellTextBuffer;
class CellTextEditor;
class CellRow;
class CellColumn;
class CellVector;
class CellText;
class Cell;
class Grafport;
class Config;
class InputFile;
class OutputFile;
class RowColumnLabel;

// the table viewer manages the configuration of the
// whole set of cells. Cells are partitioned into rows
// and partitioned into columns such that each cell is 
// part of exactly 1 row and 1 column. A subset of 
// the cells is member of the cell selection list.

/// table viewer class.
class TableViewer: public Viewer {	
/*@Doc: {\large {\bf scope:} table} */
public:
	/// creation
	TableViewer(Config *c, TableWindow *t);	

	/// deletion
	virtual ~TableViewer();		

	///
	void SetTable(Table *t) {table = t;}

	/// create table of (defaultNumberOf)Rows x (defaultNumberOf)Columns.
	virtual void Initialize();

	///
	void InitTable(unsigned rows, unsigned columns);

	/// Make all cells and lines (in)visible
	void SetVisible(bool b);

	/// draw all cells and labels
	void Draw();			

	/// erase all cells and labels
	void Undraw();			

	/// start edit object initialized with c
	bool TextMode(CellText *c);	

	/// stop edit object and update cell-text.
	void TextModeOff();		

	// These actions are called from the drawing area event handler.
	/// key is pressed at (x,y)
	void KeyTyped(int x, int y, int key);

	/// button1 is pressed at (x,y)
	void Select(int x, int y);

	/// button2 is pressed at (x,y)
	void Adjust(int x, int y);

	/// mouse pointer moved to (x,y)
	void MovingPointer(int x, int y);

	/// button1 is dragged to (x,y)
	Command *Drag(int x, int y);

	/// button2 is dragged to (x,y)
	Command *Connect(int x, int y);	

	/// return cell iff (x,y) is in cell, 
	Cell *HitCell(int x, int y);

	/// return cell-text iff (x,y) is in text, 
	CellText *HitCellText(int x, int y);

	/// return line iff (x,y) is on vertical line, 
	LinePiece *HitVLinePiece(int x, int y);

	/// return line iff (x,y) is on horizontal line, 
	LinePiece *HitHLinePiece(int x, int y);

	/// return row label iff (x,y) is in row-label,
	RowColumnLabel *HitRowLabel(int x, int y);

	/// return column label iff (x,y) is in column-label,
	RowColumnLabel *HitColumnLabel(int x, int y);

	/// return rownr if (x,y) is in row, 
	int HitRow(int x, int y);

	/// return colnr if (x,y) is in column,
	int HitColumn(int x, int y);

	///
	void ShowRowColumnLabels(bool b);
	///
	void PrintRowColumnLabels(bool b);

	///
	bool IsShowRowColumnLabels() const {return showRowColumnLabels;}
	///
	bool IsPrintRowColumnLabels() const {return printRowColumnLabels;}

	/// adapt cell size (row + column) to fit its cell text.
	void RecomputeSizeCell(Cell *c); 

	/// update the text in cell c.
	void UpdateText(Cell *c, const string *newtext);

	/// move row from oldpos to newpos.
	virtual void MoveRow(CellRow *r, unsigned newpos);	

	/// move column from oldpos to newpos.
	virtual void MoveColumn(CellColumn *c, unsigned newpos);

	/// add row to end of table.
	virtual void AddRow(CellRow *c);	

	/// add column to right of table.
	virtual void AddColumn(CellColumn *c);

	/// insert row into table (automatically shifting).
	virtual void InsertRow(CellRow *c);	 

	/// insert column into table (automatically shifting)
	virtual void InsertColumn(CellColumn *c);

	/// delete row from table.
	virtual void DeleteRow(CellRow *c);	

	/// delete column from table.
	virtual void DeleteColumn(CellColumn *c); 

	///
	void ResizeRow(CellRow *r, int newSize); 

	///
	void ResizeColumn(CellColumn *c, int newSize);

	/// move entire table.
	void Move(const Point *delta);	

	/// return r-th row.
	CellRow *GiveRow(unsigned r);	

	/// return c-th column.
	CellColumn *GiveColumn(unsigned c);

	///
	void GetSelectedRows(List<CellRow *> *r);
	///
	void GetSelectedColumns(List<CellColumn *> *c);

	///
	void GetEmptyRows(List<CellRow *> *r);
	///
	void GetEmptyColumns(List<CellColumn *> *c);

	// selection operations that are called by other classes. 
	// These actions are all forwarded to the selection object.
	///
	void DeselectAll() {selection->DeselectAll();}
	///
	void SelectAll();
	///
	void SelectCell(Cell *c) {selection->SelectCell(c);}
	///
	void DeselectCell(Cell *c) {selection->DeselectCell(c);}
	///
	void SelectVector(CellVector *v);
	///
	void DeselectVector(CellVector *v);
	///
	bool IsAllSelected(CellVector *v);
	///
	void MoveSelection(int key);
	///
	void CalcSizeElements(Point &topLeft, Point &bottomRight); 
	///
	void CalcSizeSelection(Point &topLeft, Point &bottomRight);

	///
	void UpdateMarginWidth(int newWidth);
	///
	void UpdateMarginHeight(int newHeight);
	///
	void UpdateDefaultRowHeight(int n);
	///
	void UpdateDefaultColumnWidth(int n);

	///
	int GetDefaultRowHeight() const {return defaultRowHeight;}
	///
	int GetDefaultColumnWidth() const {return defaultColumnWidth;}
	///
	unsigned GetNumberOfColumns() const {return columns->count();}
	///
	unsigned GetNumberOfRows() const {return rows->count();}
	///
	unsigned GetDefaultNumberOfColumns() const {
		return defaultNumberOfColumns;}
	///
	unsigned GetDefaultNumberOfRows() const {
		return defaultNumberOfRows;}
	///
	TextAlign::Type GetDefaultRowAlignment() const {
		return defaultRowAlignment;}
	///
	TextAlign::Type GetDefaultColumnAlignment() const {
		return defaultColumnAlignment;}
	///
	int GetRowHeight(unsigned row);
	///
	int GetColumnWidth(unsigned column);

	///
	const Point *GetTopLeft() const {return &topLeft;}
	///
	int GetWidth() const {return width;}
	///
	int GetHeight() const {return height;}
	///
	int GetMarginWidth() const {return marginWidth;}
	///
	int GetMarginHeight() const {return marginHeight;}

	///
	Point GetRowTopLeft(unsigned row);
	///
	Point GetColumnTopLeft(unsigned column);
	
	///
	void SetGrafport(Grafport *g);

	///
	CellTextBuffer *GetBuffer() const {return buffer;}

	/// return index of topmost selected row, or -1 if selection is empty.
	int GetTopSelectionRow();

	/// return index of leftmost selected column, -1 if selection is empty.
	int GetLeftSelectionColumn(); 

	///
	List<Cell *> *GetSelection() const {return selection->cells;}
	///
	unsigned NrSelected() const {return selection->cells->count();}

	///
	unsigned GetCurrentRow() const {return currentRow;}
	///
	unsigned GetCurrentColumn() const {return currentColumn;}
	///
	void SetCurrentRow(unsigned n) {currentRow=n;}
	///
	void SetCurrentColumn(unsigned n) {currentColumn=n;}

	/// get cell containing s as text (case sensitive, substring).
	void GetCells(List<Cell *> *cell, const string *s,
			bool sens, bool substring);
 
	/// return the next cell containing s as text.
	Cell *GetNextCell(const string *s, bool sens, bool substring);
 
	///
	void SetDefaultColumnAlignment(TextAlign::Type a) {
		defaultColumnAlignment = a;}
	///
	void SetDefaultRowAlignment(TextAlign::Type a) {
		defaultRowAlignment = a;}

	///
	void SetLineStyle(Side::Type side, LineStyle::Type style);

	///
	void SetDefaultNumberOfRows(unsigned);
	///
	void SetDefaultNumberOfColumns(unsigned);

	///
	void UpdateLineWidthSelection(unsigned wd);
	///
	void UpdateLineStyleSelection(LineStyle::Type l);
	///
	void UpdateTextAlignmentSelection(TextAlign::Type a);
	///
	void UpdateLineColorSelection(const string *color);
	///
	void UpdateTextColorSelection(const string *color);
	///
	void UpdateFillColorSelection(const string *color,
		FillStyle::Type f);
 
	///
	void SetDefaultFont(XFont *ft);
	/// set font family, style, size (no update when value < 0).
	void UpdateFontSelection(int f, int s, int p);

	///
	bool ReadAttributes(InputFile *f, bool appending, unsigned &rowsToAdd, 
		unsigned &columnsToAdd, double format);
	///
	bool ReadColumns(InputFile *f, unsigned nr, unsigned fromRow, 
		unsigned fromColumn, double format);
	///
	bool ReadRows(InputFile *f, unsigned nr, unsigned fromRow, 
		unsigned fromColumn, double format);

	///
	void WriteAttributes(OutputFile *f);
	///
	void WriteColumns(OutputFile *f);
	///
	void WriteRows(OutputFile *f);
	///
	void WriteSelection(OutputFile *f);
protected:
	/// 
	List<CellRow *> *GetRows() const { return rows;}
	/// 
	List<CellColumn *> *GetColumns() const { return columns;}
	///
	void SetDefaultColumnWidth(int w);
	///
	void SetDefaultRowHeight(int h);
	///
	void SetMarginWidth(int w);
	///
	void SetMarginHeight(int h);
private:
	///
	Table *table;

	/// the topleft position of the table.
	Point topLeft;			

	/// the width of all cells + row or column labels.
	int width;

	/// the height of all cells + row or column labels.
	int height;		

	/// a list of rows (List is user-defined ADT).
	List<CellRow *> *rows;

	/// a list of columns
	List<CellColumn *> *columns;	

	/// the current selection.
	CellSelection *selection;	

	/// a cut buffer for storing cell texts;
	CellTextBuffer *buffer;		

	/// minimal distance between text and column boundaries. 
	int marginWidth;	

	/// minimal distance between text and row boundaries.
	int marginHeight;	

	/// each newly created clm is aligned like this
	TextAlign::Type defaultColumnAlignment;

	/// each newly created row is aligned like this.
	TextAlign::Type defaultRowAlignment; 	

	/// each newly created row has this height.
	int defaultRowHeight;		

	/// each newly created column has this width.
	int defaultColumnWidth;		

	/// when there are no other rows/columns yet.
	unsigned defaultNumberOfRows;	

	/// each newly created row/column get this number of cells.
	unsigned defaultNumberOfColumns;

	///
	unsigned currentRow;
	///
	unsigned currentColumn;
	///
	bool showRowColumnLabels;
	///
	bool printRowColumnLabels;
	///
	Point defaultTopLeft;

	///
	void DeleteCells();
	///
	bool GoIntoTextMode(Cell *cell);
};
#endif
