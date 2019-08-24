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
#ifndef _TABLESTUBS_H
#define _TABLESTUBS_H

#include "editstubs.h"

/// Calback stubs for table editor menu items and popup dialogs.
class TableStubs: public EditStubs {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	static void AppendCB(Widget, XtPointer, XtPointer);
	///
	static void AppendToggleCB(Widget, XtPointer, XtPointer);

	///
	static void AddRowsOKCB(Widget, XtPointer, XtPointer);
	///
	static void AddColumnsOKCB(Widget, XtPointer, XtPointer);
	///
	static void AddRowsToggleCB(Widget, XtPointer, XtPointer);
	///
	static void AddColumnsToggleCB(Widget, XtPointer, XtPointer);

	///
	static void NumberOfRowsCB(Widget, XtPointer, XtPointer);
	///
	static void NumberOfColumnsCB(Widget, XtPointer, XtPointer);

	///
	static void RowHeightCB(Widget, XtPointer, XtPointer);
	///
	static void ColumnWidthCB(Widget, XtPointer, XtPointer);

	///
	static void MarginHeightCB(Widget, XtPointer, XtPointer);
	///
	static void MarginWidthCB(Widget, XtPointer, XtPointer);

	/// Callbacks for the edit functions.
	static void AddRowsCB(Widget, XtPointer, XtPointer);
	///
	static void AddColumnsCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteRowsCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteColumnsCB(Widget, XtPointer, XtPointer);
	///
	static void PurgeCB(Widget, XtPointer, XtPointer);
	///
	static void DeleteAllCB(Widget, XtPointer, XtPointer);
	///
	static void CutTextsCB(Widget, XtPointer, XtPointer);
	///
	static void CopyTextsCB(Widget, XtPointer, XtPointer);
	///
	static void PasteTextsCB(Widget, XtPointer, XtPointer);
	///
	static void SelectAllCB(Widget, XtPointer, XtPointer);
	///
	static void SortRowsCB(Widget, XtPointer, XtPointer);
	///
	static void SortColumnsCB(Widget, XtPointer, XtPointer);

	/// Callbacks for the view functions
	static void ShowRowColumnLabelsCB(Widget, XtPointer, XtPointer);
	///
	static void PrintRowColumnLabelsCB(Widget, XtPointer, XtPointer);

	/// Callbacks for the properties functions.
	static void SetNumberOfRowsCB(Widget, XtPointer, XtPointer);
	///
	static void SetNumberOfColumnsCB(Widget, XtPointer, XtPointer);
	///
	static void SetDefaultRowHeightCB(Widget, XtPointer, XtPointer);
	///
	static void SetDefaultColumnWidthCB(Widget, XtPointer, XtPointer);
	///
	static void SetMarginWidthCB(Widget, XtPointer, XtPointer);
	///
	static void SetMarginHeightCB(Widget, XtPointer, XtPointer);
	///
	static void AnnotateCellCB(Widget, XtPointer, XtPointer);
	///
	static void AnnotateCellOKCB(Widget, XtPointer, XtPointer);

	///
	static void DefaultRowAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultColumnAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateRowAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateColumnAlignmentCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultColumnAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultColumnAlignmentDefaultCB(
		Widget, XtPointer, XtPointer);
	///
	static void UpdateColumnAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateColumnAlignmentDefaultCB(
		Widget, XtPointer, XtPointer);
	///
	static void DefaultRowAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void DefaultRowAlignmentDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateRowAlignmentOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateRowAlignmentDefaultCB(Widget, XtPointer, XtPointer);
	
	///
	static void UpdateTableLineStyleCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTableLineStyleOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTableLineStyleDefaultCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTableLineWidthCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTableLineWidthOKCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateTableLineWidthDefaultCB(Widget, XtPointer, XtPointer);

	///
	static void UpdateCellTextUnderlineCB(Widget, XtPointer, XtPointer);
};
#endif
