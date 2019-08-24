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
#ifndef _CELL_H
#define _CELL_H

#include "point.h"
#include "celltext.h"
#include "cellcolumn.h"
class CellRow;
class Grafport;
class XFont;
class InputFile;
class OutputFile;

/// (table) cell class.
class Cell {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	Cell(Grafport *g, XFont *ft, CellRow *row, CellColumn *column, 
		int x, int y, int wd, int ht);
	///
	virtual ~Cell();

	/// alphabetical text comparison.
	friend int operator==(const Cell &c1, const Cell &c2); 

	/// draw the cell.
	void Draw();

	/// erase the cell.
	void Undraw();			 

	/// reposition and redraw 
	void UpdatePosition(const Point *pt);

	/// resize and redraw.
	void UpdateSize(int wd, int ht); 

	/// (de)select and redraw.
	void UpdateSelect(bool);	 

	/// update text font and redraw.
	void UpdateFont(XFont *ft);	 

	/// recalculate text position and redraw.
	void UpdateTextPosition();	 

	/// recalculate text size.
	void SetTextSize();

	/// reposition cell + text
	void SetPosition(const Point *pt);	 

	/// resize cell.
	void SetSize(int wd, int ht);	 

	/// change grafport
	void SetGrafport(Grafport *g);

	/// true iff (x,y) is inside cell.
	bool ContainsPt(int x, int y) const;

	/// write cell attributes to output stream (file).
	void Write(OutputFile *f);

	/// read cell attributes from input stream (file).
	bool Read(InputFile *f, double format);

	/// update cell text and redraw.
	void UpdateText(const string *);	 

	/// make cell text empty.
	void ClearText();		 

	/// true iff celltext is 's'.
	bool HasText(const string *s) const {return *s == *cellText->GetText();}

	/// true iff celltext contains 's' (c1: case sensitive).
	bool HasText(const string *s, bool c1, bool c2);

	///
	void SetRow(CellRow *r) { row = r;}

	///
	void SetColumn(CellColumn *c) { column = c;}

	///
	CellRow *GetRow() const {return row;}	 

	///
	CellColumn *GetColumn() const {return column;}

	///
	const Point *GetPosition() const {return &position;}

	///
	const Point *GetTopLeft() const {return &topLeft;}

	///
	int GetWidth() const {return width;}

	///
	int GetHeight() const {return height;}

	///
	bool IsSelected() const {return selected;}

	///
	bool IsEditable() const {return editable;}
	///
	void SetEditable(bool b) {editable = b;}

	///
	bool IsVisible() const {return visible;}
	///
	void SetVisible(bool b) {visible = b;}

	///
	CellText *GetCellText() const {return cellText;}

	///
	const string *GetText() const {return cellText->GetText();}

	///
	void SetFont(XFont *ft);

	///
	XFont *GetFont() const {return cellText->GetFont();}

	///
	void SetXLFD(const char *descr);

	///
	int GetTextWidth() const {return cellText->GetWidth();}

	///
	int GetTextHeight() const {return cellText->GetHeight();}

	///
	TextAlign::Type GetColumnAlignment() const {
		return column->GetAlignment();}

	/// set cell text pos. given row/column alignment + margin width/height.
	void CalcCellTextPosition();

	///
	void SetAnnotation(const string *s) {annotation = *s;}
	///
	const string *GetAnnotation() const {return &annotation;}
 
private:
	/// row of cell
	CellRow *row; 		

	/// column of cell.
	CellColumn *column;	

	/// the center position of the cell on the drawing area.
	Point position;

	/// the top-left position of the cell on the drawing area.
	Point topLeft;

	/// the width of the cell
	int width;

	/// the height of the cell
	int height;

	/// how many rows are spanned by the cell.
	int spanRows;

	/// how many columns are spanned by the cell.
	int spanColumns;

	/// is cell selected? (represented by highlighting the cell).
	bool selected;

	/// is cell currently visible?
	bool visible;		

	/// can the cell text be edited?
	bool editable;		

	/// cell annotation.
	string annotation;

	/// the text label inside the cell.
	CellText *cellText;	

	///
	Grafport *grafport;

	/// change position so that shape has only positive coordinates.
	void PositiveCoord(); 	

	/// draw selection rectangle into cell.
	void DrawSelect(); 	
};
#endif
