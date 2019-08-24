////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "tablestubs.h"
#include "table.h"
#include "fileselectiondialog.h"
#include "togglelistdialog.h"
#include "textalignmentdialog.h"
#include "linewidthsidedialog.h"
#include "linestylesidedialog.h"
#include "texteditdialog.h"
#include "scaledialog.h"
#include <stdlib.h>
#include <Xm/XmAll.h>

void TableStubs::AppendCB(Widget, XtPointer clientData, XtPointer) {
	((Table *)clientData)->Append();
}

void TableStubs::AppendToggleCB(Widget, XtPointer clientData, XtPointer) {
	Table *tab = (Table *)clientData;
	FileSelectionDialog *d = tab->GetFileSelectionDialog();
	string s;
	d->GetOption(&s);
	if (s == "Bottom")
		tab->SetAppendToggle(True);
	else
		tab->SetAppendToggle(False);
}

void TableStubs::AddRowsOKCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	string txt;
	t->GetPromptToggleDialog()->GetTextString(&txt);
	t->AddRows(txt.toint());
}

void TableStubs::AddColumnsOKCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	string txt;
	t->GetPromptToggleDialog()->GetTextString(&txt);
	t->AddColumns(txt.toint());
}

void TableStubs::AddRowsToggleCB(Widget, XtPointer cd, XtPointer) {
	Table *tab = (Table *)cd;
	ToggleListDialog *d = tab->GetPromptToggleDialog();
	int which = d->GetValue();
	if (check(which >= 0))
		tab->SetAddRowsToggle(which);
}

void TableStubs::AddColumnsToggleCB(Widget, XtPointer cd, XtPointer) {
	Table *tab = (Table *)cd;
	ToggleListDialog *d = tab->GetPromptToggleDialog();
	int which = d->GetValue();
	if (check(which >= 0))
		tab->SetAddColumnsToggle(which);
}

void TableStubs::NumberOfRowsCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	t->SetDefaultNumberOfRows( t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::NumberOfColumnsCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	t->SetDefaultNumberOfColumns(t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::RowHeightCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	t->SetDefaultRowHeight(t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::ColumnWidthCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	t->SetDefaultColumnWidth(t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::MarginWidthCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	t->SetMarginWidth(t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::MarginHeightCB(Widget, XtPointer clientData, XtPointer) {
	Table *t = (Table *)clientData;
	t->SetMarginHeight(t->GetScaleDialog()->GetScaleValue());
}

void TableStubs::AnnotateCellCB(Widget, XtPointer clientData, XtPointer) {
	((Table *)clientData)->AnnotateCell();
}

void TableStubs::AnnotateCellOKCB(Widget, XtPointer clientData, XtPointer) {
	Table *tb = (Table *)clientData;
	if (!check(tb))
		return;
	string t;
	tb->GetEltAnnotationDialog()->GetTextString(&t);
	tb->SetCellAnnotation(&t);
}

void TableStubs::ShowRowColumnLabelsCB(Widget w, XtPointer cd, XtPointer) {
	((Table *)cd)->ShowRowColumnLabels(XmToggleButtonGetState(w));
}

void TableStubs::PrintRowColumnLabelsCB(Widget w, XtPointer cd, XtPointer) {
	((Table *)cd)->PrintRowColumnLabels(XmToggleButtonGetState(w));
}

void TableStubs::AddRowsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->AddRows();
}

void TableStubs::AddColumnsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->AddColumns();
}

void TableStubs::DeleteRowsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->DeleteRows();
}

void TableStubs::DeleteColumnsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->DeleteColumns();
}

void TableStubs::PurgeCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->Purge();
}

void TableStubs::DeleteAllCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->DeleteAll();
}

void TableStubs::CutTextsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->CutTexts();
}

void TableStubs::CopyTextsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->CopyTexts();
}

void TableStubs::PasteTextsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->PasteTexts();
}

void TableStubs::SelectAllCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SelectAll();
}

void TableStubs::SortRowsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SortRows();
}

void TableStubs::SortColumnsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SortColumns();
}

void TableStubs::SetNumberOfRowsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SetDefaultNumberOfRows();
}

void TableStubs::SetNumberOfColumnsCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SetDefaultNumberOfColumns();
}

void TableStubs::SetDefaultRowHeightCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SetDefaultRowHeight();
}

void TableStubs::SetDefaultColumnWidthCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->SetDefaultColumnWidth();
}

void TableStubs::SetMarginWidthCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateMarginWidth();
}

void TableStubs::SetMarginHeightCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateMarginHeight();
}
 
void TableStubs::DefaultRowAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->DefaultRowAlignment();
}

void TableStubs::DefaultColumnAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->DefaultColumnAlignment();
}

void TableStubs::UpdateRowAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateRowAlignment();
}

void TableStubs::UpdateColumnAlignmentCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateColumnAlignment();
}

void TableStubs::DefaultColumnAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	NToggleListDialog *d = t->GetColumnAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	t->UpdateDefaultColumnAlignment(TextAlign::String2Type(&text));
}

void TableStubs::DefaultColumnAlignmentDefaultCB(
		Widget, XtPointer cd, XtPointer) {
	((Table *) cd)->ShowConfigColumnAlignment();
}

void TableStubs::UpdateColumnAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	NToggleListDialog *d = t->GetColumnAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	t->UpdateColumnAlignment(TextAlign::String2Type(&text));
}

void TableStubs::UpdateColumnAlignmentDefaultCB(
		Widget, XtPointer cd, XtPointer) {
	((Table *) cd)->ShowDefaultColumnAlignment();
}

void TableStubs::DefaultRowAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	TextAlignmentDialog *d = t->GetRowAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	t->UpdateDefaultRowAlignment(TextAlign::String2Type(&text));
}

void TableStubs::DefaultRowAlignmentDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Table *) cd)->ShowConfigRowAlignment();
}

void TableStubs::UpdateRowAlignmentOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	TextAlignmentDialog *d = t->GetRowAlignmentDialog();
	int n = d->GetValue(0);
	string text;
	d->GetItem(0, n, &text);
	t->UpdateRowAlignment(TextAlign::String2Type(&text));
}

void TableStubs::UpdateRowAlignmentDefaultCB(Widget, XtPointer cd, XtPointer) {
	((Table *) cd)->ShowDefaultRowAlignment();
}

void TableStubs::UpdateTableLineStyleCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateTableLineStyle();
}

void TableStubs::UpdateTableLineStyleOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	LineStyleSideDialog *d = t->GetTableLineStyleDialog();
	int n = d->GetValue(0);
	int m = d->GetValue(1);
	string text1, text2;
	d->GetItem(0, n, &text1);
	d->GetItem(1, m, &text2);
	t->UpdateLineStyle(Side::String2Type(&text2),
			   LineStyle::String2Type(&text1));
}

void TableStubs::UpdateTableLineStyleDefaultCB(
		Widget, XtPointer cd, XtPointer) {
	((Table *) cd)->ShowDefaultLineStyle();
}

void TableStubs::UpdateTableLineWidthCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateTableLineWidth();
}

void TableStubs::UpdateTableLineWidthOKCB(Widget, XtPointer cd, XtPointer) {
	Table *t = (Table *)cd;
	LineWidthSideDialog *d = t->GetTableLineWidthDialog();
	int n = d->GetValue(0);
	int m = d->GetValue(1);
	string text1;
	d->GetItem(1, m, &text1);
	t->UpdateLineWidth(Side::String2Type(&text1), n+1);
}

void TableStubs::UpdateTableLineWidthDefaultCB(
		Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->ShowDefaultLineWidth();
}

void TableStubs::UpdateCellTextUnderlineCB(Widget, XtPointer cd, XtPointer) {
	((Table *)cd)->UpdateCellTextUnderline();
}
