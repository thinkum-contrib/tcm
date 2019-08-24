//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _TABLE_H
#define _TABLE_H

#include "document.h"
#include "side.h"
#include "tableviewer.h"
class ToggleListDialog;
class TextAlignmentDialog;
class NToggleListDialog;
class LineWidthSideDialog;
class LineStyleSideDialog;

// A table is one of the possible kinds of documents (another is Diagram).
// A generic table is a document of type Table. Special types of tables are 
// implemented as subclasses of class Table

/// Table class.
class Table: public Document {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	Table(Config *c, TableWindow *w, TableViewer *v);
	///
	virtual ~Table();

	///
	virtual void Initialize();
	///
	void LoadEntries();
	///
	void SaveEntries();
	///
	void RemoveAll();

	// Many table edit transactions are called via a menu.
	// Some of them are directly forwarded to the table viewer.
	// or, when they are more complex, they result into the creation and 
	// probably execution of a table command object (see further below).
	// all actions up to 'SelectAll' can be undone/redone.

	// The following actions are main entry points for execution of 
	// the table edit transactions.
	///
	void AddRows();
	///
	void AddColumns();
	///
	void DeleteRows();
	///
	void DeleteColumns();
	///
	void DeleteAll();
	///
	void Purge();
	///
	void CutTexts();
	///
	void CopyTexts();
	///
	void PasteTexts();
	///
	void SortRows();
	///
	void SortColumns();
	///
	void SameWidth();
	///
	void SameHeight();
	///
	void Span();
	///
	void UnSpan();
	///
	void SelectAll();

	/// Move table on mainwindow according to move type.
	void Move(MoveType t);

	///
	void Append();

	/// set append to bottom(Trye) or to the right(False).
	void SetAppendToggle(bool set);
	///
	bool IsAppendBottom() {return appendBottom;}

	/// called via add rows dialog.
	void SetAddRowsToggle(bool set);
	///
	void SetAddColumnsToggle(bool set);
	///
	void AddRows(unsigned count);
	///
	void AddColumns(unsigned count);

	///
	void FindAll(const string *s, bool sens, bool sub, bool);
	///
	void FindNext(const string *s, bool sens, bool sub, bool);
	///
	void ReplaceNext(const string *s1, const string *s2, 
		bool sens, bool sub, bool);
	///
	void ReplaceAll(const string *s1, const string *s2, 
		bool sens, bool sub, bool);

	///
	virtual bool UpdateText(Cell *c, const string *text);

	///
	void SetDefaultNumberOfRows();
	///
	void SetDefaultNumberOfColumns();
	///
	void SetDefaultRowHeight();
	///
	void SetDefaultColumnWidth();

	///
	void SetDefaultNumberOfRows(unsigned n);
	///
	void SetDefaultNumberOfColumns(unsigned n);
	///
	void SetDefaultRowHeight(int n);
	///
	void SetDefaultColumnWidth(int n);
	///
	void SetMarginHeight(int n);
	///
	void SetMarginWidth(int n);

	///
	void DefaultRowAlignment();
	///
	void DefaultColumnAlignment();
	///
	void UpdateRowAlignment();
	///
	void UpdateColumnAlignment();
	///
	void UpdateColumnAlignment(TextAlign::Type type);
	///
	void UpdateRowAlignment(TextAlign::Type type);
	///
	void UpdateDefaultColumnAlignment(TextAlign::Type newType);
	///
	void UpdateDefaultRowAlignment(TextAlign::Type newType);
	///
	void ShowConfigRowAlignment();
	///
	void ShowDefaultRowAlignment();
	///
	void ShowConfigColumnAlignment();
	///
	void ShowDefaultColumnAlignment();

	///
	void UpdateTableLineStyle();
	/// 
	void UpdateLineStyle(Side::Type side, LineStyle::Type style);
	///
	void ShowConfigLineStyle();
	///
	void ShowDefaultLineStyle();

	///
	void UpdateTableLineWidth();
	/// 
	void UpdateLineWidth(Side::Type side, unsigned width);
	///
	void ShowConfigLineWidth();
	///
	void ShowDefaultLineWidth();

	///
	void UpdateCellTextUnderline();

	///
	void ShowRowColumnLabels(bool b);
	///
	void PrintRowColumnLabels(bool b);

	///
	void UpdateMarginWidth();
	///
	void UpdateMarginHeight();

	///
	void AnnotateCell();
	///
	void SetCellAnnotation(const string *s);

	///
	ScaleDialog *GetScaleDialog() {return scaleDialog;}
	///
	ToggleListDialog *GetPromptToggleDialog() {
		return promptToggleDialog;}
	///
	LineStyleSideDialog *GetTableLineStyleDialog() {
		return tableLineStyleDialog;}
	///
	LineWidthSideDialog *GetTableLineWidthDialog() {
		return tableLineWidthDialog;}
	///
	TextAlignmentDialog *GetRowAlignmentDialog() {
		return rowAlignmentDialog;}
	///
	NToggleListDialog *GetColumnAlignmentDialog() {
		return columnAlignmentDialog;}

	///
	static const int MIN_ROW_HEIGHT;
	///
	static const int MIN_COLUMN_WIDTH;
	///
	static const int MAX_ROW_HEIGHT;
	///
	static const int MAX_COLUMN_WIDTH;
	///
	static const int MIN_MARGIN_WIDTH;
	///
	static const int MIN_MARGIN_HEIGHT;
	///
	static const int MAX_MARGIN_WIDTH;
	///
	static const int MAX_MARGIN_HEIGHT;
	///
	static const int MIN_NUMBER_OF_COLUMNS;
	///
	static const int MIN_NUMBER_OF_ROWS;
	///
	static const int MAX_NUMBER_OF_COLUMNS;
	///
	static const int MAX_NUMBER_OF_ROWS;

protected:
	///
	TableViewer *GetTableViewer() {return tviewer;}
private:
	///
	TableViewer *tviewer;
	///
	bool topAdd;
	///
	bool leftAdd;
	///
	bool appendBottom;

	///
	ScaleDialog *scaleDialog;
	///
	ToggleListDialog *promptToggleDialog;
	///
	LineStyleSideDialog *tableLineStyleDialog;
	///
	LineWidthSideDialog *tableLineWidthDialog;
	///
	TextAlignmentDialog *rowAlignmentDialog;
	///
	NToggleListDialog *columnAlignmentDialog;

	///
	unsigned defaultNumberOfRows;
	///
	unsigned defaultNumberOfColumns;
	///
	int defaultRowHeight;
	///
	int defaultColumnWidth;
	///
	int defaultMarginWidth;
	///
	int defaultMarginHeight;
	///
	Cell *annotationCell;

	///
	static const int DEFAULT_ADD_ROWS;
	///
	static const int DEFAULT_ADD_COLUMNS;

	///
	void FitTable();
	///
	void DeleteAllCells();
	///
	void AnnotateCell(Cell *cell);

	///
	void EmptySelectionMessage();
	///
	void EmptyTableMessage();

};
#endif
