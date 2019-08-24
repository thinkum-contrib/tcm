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
#ifndef _PASTECELLTEXTSCMD_H
#define _PASTECELLTEXTSCMD_H

#include "point.h"
#include "command.h"
#include "lstring.h"
class string;
class TableViewer;
class Table;
class CellText;
class Cell;
class CellTextBuffer;

/// paste cell texts from cut-buffer command.
class PasteCellTextsCmd: public Command {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	PasteCellTextsCmd(Table *t, TableViewer *v);
	///
	virtual ~PasteCellTextsCmd();
	///
	void Execute();
	///
	void UnExecute();
	///
	void Abort();
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	const char *GetName() const {return "paste texts";}
private:
	///
	List<CellText *> *cellTexts;
	///
	Point delta;
	///
	Point topLeft;
	///
	Point anchor;
	///
	int width;
	///
	int height;
	///
	TableViewer *tviewer;
	///
	CellTextBuffer *buffer;
	///
	List<Cell *> *pastedCells;
	///
	List<string *> *oldStrings;
	///
	void DrawOutLine(const Point *p);
	///
	void MakeBox();
	///
	void MoveCellTexts(const Point *delta);
	///
	static const int MIN_BOX_SIZE;
};
#endif
