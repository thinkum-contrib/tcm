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
#ifndef _CELLTEXT_H
#define _CELLTEXT_H

#include "simplelabel.h"
#include "textalign.h"
class Cell;
class TextFont;
class XFont;
class InputFile;
class OutputFile;

/// cell text class.
class CellText: public SimpleLabel {
/*@Doc: {\large {\bf scope:} table} */
public:
	/// creation.
	CellText(Grafport *g, XFont *ft, Cell *parent); 	

	/// creation + initialization.
	CellText(const CellText &text);	

	friend int Compare(CellText *r1, CellText *r2) {return *r1 == *r2;}

	///
        void Draw();

	/// draw cell text. 
	void DrawAligned(TextAlign::Type a);

	/// erase cell cell.
	void UndrawAligned(TextAlign::Type a); 

	/// update position and redraw.
	void UpdatePosition(const Point *);

	/// update text and redraw.
	void UpdateText(const string *);	

	/// update font and redraw.
	void UpdateFont(XFont *);	

	/// 
	virtual bool IsUnderlined() const {return underlined;}
	///
	void SetUnderlined(bool b) {underlined=b;}
	///
	void UpdateUnderlined(bool b);

	///
	Cell *GetParent() const {return parent;}

	///
	void Write(OutputFile *f);

	///
	bool Read(InputFile *f, double format);
private:
	/// cell that contains this text (can be 0) = inverse of cell.celltext.
	Cell *parent;		

	/// is the cell text underlined
	bool underlined;
};
#endif
