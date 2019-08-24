//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _REPLACECELLTEXTCMD_H
#define _REPLACECELLTEXTCMD_H

#include "command.h"
#include "lstring.h"
class Cell;
class Table;
class TableViewer;

/// abstract command class for replacing text of cells.
class ReplaceCellTextCmd: public Command {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	ReplaceCellTextCmd(Table *, TableViewer *v,
		const string *s1, const string *s2,
		bool sens, bool substr);
	///
	virtual ~ReplaceCellTextCmd();
	///
	void UnExecute();
	///
	void ReExecute();
protected:
	///
	TableViewer *GetTableViewer() {return tviewer;}
	///
	string *GetPattern() {return pattern;}
	///
	string *GetReplace() {return replace;}
	///
	bool IsCaseSensitive() {return caseSensitive;}
	///
	bool IsSubstring() {return substring;}
	///
	List<Cell *> *GetCells() {return cells;}
	///
	List<string *> *GetOldStrings() {return oldStrings;}
private:
	///
	TableViewer *tviewer;
	///
	List<Cell *> *oldSelection;
	///
	List<Cell *> *cells;
	///
	List<string *> *oldStrings;
	///
	string *pattern;
	///
	string *replace;
	///
	bool caseSensitive;
	///
	bool substring;
};
#endif
