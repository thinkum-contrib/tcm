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
#ifndef _CELLTEXTBUFFER_H
#define _CELLTEXTBUFFER_H

#include "llist.h"
#include "point.h"
class CellText;
class TableViewer;

/// cut-paste buffer class for cell texts.
class CellTextBuffer {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	CellTextBuffer();
	///
	virtual ~CellTextBuffer();

	/// topleft row-column position.
	const Point GetRcTopLeft() const {return rcTopLeft;}

	/// topleft of the paste box.
	const Point GetTopLeft() const {return topLeft;}
	/// bottomright of the paste box.
	const Point GetBottomRight() const {return bottomRight;}

	/// put \_copy\_ of c in buffer.
	void PutTexts(List<CellText *> *c); 

	/// put row/column positions in the buffer.
	void PutPositions(List<Point *> *p); 

	/// return \_copy\_ of c.
	List<CellText *> *GetTexts();

	///
	List<Point *> *GetPositions() const {return rcPositions;}

	/// move prevCelltexts to cell-texts. 
	void UndoPut();		 

	/// is buffer empty ?
	bool IsEmpty();		 
private:
	///
	Point rcTopLeft;
	///
	Point topLeft;
	///
	Point bottomRight;
	///
	List<CellText *> *cellTexts;
	/// for undo.
	List<CellText *> *prevCellTexts; 
	///
	List<Point *> *rcPositions;
	///
	List<Point *> *prevRcPositions;
	///
	void CalcSizeBuffer();
};
#endif
