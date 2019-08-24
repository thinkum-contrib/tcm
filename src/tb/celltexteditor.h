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
#ifndef _CELLTEXTEDITOR_H
#define _CELLTEXTEDITOR_H

#include "celltext.h"
#include "inlineeditor.h"
class CellText;
class TableViewer;

/// cell text editor class.
class CellTextEditor: public InlineEditor {	
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	CellTextEditor(TableViewer *v);

	/// start inline editing, initialized by cell text.
	void Start(CellText *);	

	///
	void Stop();
	///
	void Abort();

	/// start window editing, initialized by cell text.
	void StartWindow(CellText *);	

	///
	CellText *GetCellText() const {return cellText;}

	///
	bool IsUnderlined() const {return cellText->IsUnderlined();}
private:
	/// the cell-text that will be updated when editing is finished.
	CellText *cellText;
	///
	void UpdateText();
};
#endif
