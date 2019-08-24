////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "table.h"
#include "tablewindow.h"
#include "tablestubs.h"
#include "tableviewer.h"
#include "texteditdialog.h"
#include "togglelistdialog.h"
#include "textalignmentdialog.h"
#include "linewidthsidedialog.h"
#include "linestylesidedialog.h"
#include "scaledialog.h"
#include "questiondialog.h"
#include "fileselectiondialog.h"
#include "config.h"
#include "cell.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "appendtablecmd.h"
#include "addrowscmd.h"
#include "addcolumnscmd.h"
#include "deleterowscmd.h"
#include "deletecolumnscmd.h"
#include "deleteallcellscmd.h"
#include "purgecellscmd.h"
#include "cutcelltextscmd.h"
#include "pastecelltextscmd.h"
#include "sortrowscmd.h"
#include "sortcolumnscmd.h"
#include "findnextcellcmd.h"
#include "updatecelltextcmd.h"
#include "movetablecmd.h"
#include "replaceallcelltextscmd.h"
#include "replacenextcelltextcmd.h"
#include "updaterowalignmentcmd.h"
#include "updatecolumnalignmentcmd.h"
#include "updatelinestyletablecmd.h"
#include "updatelinewidthtablecmd.h"
#include "updatecelltextunderlinecmd.h"
#include "celltextbuffer.h"

const int Table::MIN_ROW_HEIGHT = 10;
const int Table::MIN_COLUMN_WIDTH = 10;
const int Table::MAX_ROW_HEIGHT = 200;
const int Table::MAX_COLUMN_WIDTH = 200;
const int Table::MIN_MARGIN_WIDTH = 0;
const int Table::MIN_MARGIN_HEIGHT = 0;
const int Table::MAX_MARGIN_WIDTH = 30;
const int Table::MAX_MARGIN_HEIGHT = 30;
const int Table::MIN_NUMBER_OF_ROWS = 1;
const int Table::MIN_NUMBER_OF_COLUMNS = 1;
const int Table::MAX_NUMBER_OF_ROWS = 30;
const int Table::MAX_NUMBER_OF_COLUMNS = 30; 

const int Table::DEFAULT_ADD_ROWS = 1;
const int Table::DEFAULT_ADD_COLUMNS = 1;

Table::Table(Config *c, TableWindow *w, TableViewer *v): Document(c, w, v) {
	tviewer = v;
	topAdd = False;
	leftAdd = False;
	appendBottom = True;
	annotationCell = 0;
	string l = "Append table to the: ";
	List<string *> s;
	s.add(new string("Bottom"));
	s.add(new string("Right"));
	GetEltAnnotationDialog()->
		SetOKCallback(TableStubs::AnnotateCellOKCB, this);
	GetFileSelectionDialog()->CreateOptionMenu(&l, &s);
	GetFileSelectionDialog()->SetOptionChangedCallback(
		TableStubs::AppendToggleCB, this);
	s.clear();
	scaleDialog = new ScaleDialog(w->GetWidget());
	scaleDialog->Initialize();
	List<string *> labels;
	labels.add(new string("this entry sucks"));
	labels.add(new string("this entry sucks even more"));
	promptToggleDialog = new ToggleListDialog(w->GetWidget(), True);
	promptToggleDialog->Initialize();
	promptToggleDialog->CreateToggles(&labels); // labels are changed later.
	labels.clear();
	defaultNumberOfRows = tviewer->GetDefaultNumberOfRows();
	defaultNumberOfColumns = tviewer->GetDefaultNumberOfColumns();
	defaultRowHeight = tviewer->GetDefaultRowHeight();
	defaultColumnWidth = tviewer->GetDefaultColumnWidth();
	defaultMarginWidth = tviewer->GetMarginWidth();
	defaultMarginHeight = tviewer->GetMarginHeight();
	// line style stuff
	tableLineStyleDialog = new LineStyleSideDialog(w->GetWidget());
	tableLineStyleDialog->Initialize();
	tableLineStyleDialog->SetTitle("update line style");
	tableLineStyleDialog->SetHelpCallback(
		TableStubs::UpdateTableLineStyleDefaultCB, this);
	tableLineStyleDialog->SetOKCallback(
		TableStubs::UpdateTableLineStyleOKCB, this);
	// line width stuff
	tableLineWidthDialog = new LineWidthSideDialog(w->GetWidget());
	tableLineWidthDialog->Initialize();
	tableLineWidthDialog->SetTitle("update line width");
	tableLineWidthDialog->SetHelpCallback(
		TableStubs::UpdateTableLineWidthDefaultCB, this);
	tableLineWidthDialog->SetOKCallback(
		TableStubs::UpdateTableLineWidthOKCB, this);
	// alignment stuff
	columnAlignmentDialog = GetViewer()->GetTextAlignmentDialog();
	rowAlignmentDialog = new TextAlignmentDialog(w->GetWidget(), False);
	rowAlignmentDialog->Initialize();
	ShowConfigLineStyle();
	ShowConfigLineWidth();
	ShowConfigColumnAlignment();
	ShowConfigRowAlignment();
}

Table::~Table() {
	delete scaleDialog;
	delete promptToggleDialog;
	delete tableLineStyleDialog;
	delete tableLineWidthDialog;
	delete rowAlignmentDialog;
}


/* virtual */ void Table::Initialize() {
	Document::Initialize();
	tviewer->Initialize();
}


void Table::Append() {
	GetFileSelectionDialog()->ManageOptionMenu(True);
	Document::Append();
}
 
void Table::RemoveAll() {
	DeleteAllCells();
	tviewer->DeleteCommands();
}

void Table::LoadEntries() {
	if (IsAppending()) {
		tviewer->NewCommand(new AppendTableCmd(this, tviewer));
		tviewer->ExecuteCommand();
		return;
	}
	tviewer->TextModeOff();
	// delete the document contents.
	DeleteAllCells();
	unsigned rows, columns;
	InputFile *ipf = GetInputFile();
	if (tviewer->ReadAttributes(ipf, IsAppending(), rows, 
				    columns, GetLoadFormat())) {
		// load: add new rows and columns
		tviewer->InitTable(rows, columns);
		tviewer->SetVisible(False);
		if (GetLoadFormat() >= 1.09) {
			if (tviewer->ReadRows(ipf, rows, 0, 0, GetLoadFormat()))
				tviewer->ReadColumns(
					ipf, columns, 0, 0, GetLoadFormat());
		}
		else {
			if (tviewer->ReadColumns(ipf, columns, 0, 0, 
						 GetLoadFormat()))
				tviewer->ReadRows(ipf, rows, 0, 0, 
						  GetLoadFormat());
		}
		tviewer->DeleteCommands();
	}
	tviewer->SetVisible(True);
	tviewer->Refresh();
	FitTable();
}

void Table::FitTable() {
	Point p1, p2;
	tviewer->CalcSizeElements(p1, p2);
	double wd = tviewer->Scale(p2.x) + 300.0;
	double ht = tviewer->Scale(p2.y) + 300.0;
	((DrawWindow *)GetMainWindow())->FitDocument(static_cast<int>(0.5 + wd),
												 static_cast<int>(0.5 + ht));
}

void Table::SaveEntries() {
	tviewer->TextModeOff();
	OutputFile *opf = GetOutputFile();
	if (IsSaveSelection()) {
		tviewer->WriteSelection(opf);
	}
	else {
		tviewer->WriteAttributes(opf);
		tviewer->WriteRows(opf);
		tviewer->WriteColumns(opf);
	}
}

void Table::SetAppendToggle(bool set) {
	appendBottom = set;
	if (set)
		SetStatus("append to the bottom of the table");
	else
		SetStatus("append to the right of the table");
}

void Table::AddRows() {
	SetStatus("action: add rows");
	string d = DEFAULT_ADD_ROWS;
	string s0("To the bottom of the table");
	string s1("To the top of the selection");
	promptToggleDialog->SetToggleText(0, &s0);
	promptToggleDialog->SetToggleText(1, &s1);
	promptToggleDialog->SetTitle("Add rows");
	promptToggleDialog->SetSelectionLabel("Number of rows to add");
	promptToggleDialog->SetTextString(&d);
	promptToggleDialog->SetOKCallback(TableStubs::AddRowsOKCB, this);
	promptToggleDialog->SetToggleChangedCallback(
				TableStubs::AddRowsToggleCB, this);
	promptToggleDialog->SetValue(topAdd);
	promptToggleDialog->Popup();
}

void Table::AddColumns() {
	SetStatus("action: add columns");
	string d = DEFAULT_ADD_COLUMNS;
	string s0("To the right of the table");
	string s1("To the left of the selection");
	promptToggleDialog->SetToggleText(0, &s0);
	promptToggleDialog->SetToggleText(1, &s1);
	promptToggleDialog->SetTitle("Add columns");
	promptToggleDialog->SetSelectionLabel("Number of columns to add");
	promptToggleDialog->SetTextString(&d);
	promptToggleDialog->SetOKCallback(TableStubs::AddColumnsOKCB, this);
	promptToggleDialog->SetToggleChangedCallback(
				TableStubs::AddColumnsToggleCB, this);
	promptToggleDialog->SetValue(leftAdd);
	promptToggleDialog->Popup();
}

void Table::SetAddRowsToggle(bool set) {
	topAdd = set;
	if (set)
		SetStatus("add rows at the top of the selection");
	else
		SetStatus("add rows at the bottom of the table");
}

void Table::SetAddColumnsToggle(bool set) {
	leftAdd = set;
	if (set)
		SetStatus("add columns at the left of the selection");
	else
		SetStatus("add columns at the right of the table");
}

void Table::AddRows(unsigned n) {
	int m;
	if (topAdd) {
		if ((m = tviewer->GetTopSelectionRow()) == -1)
			m = tviewer->GetNumberOfRows();
	}
	else
		m = tviewer->GetNumberOfRows();
	tviewer->NewCommand(new AddRowsCmd(this, tviewer, n, m));
	tviewer->ExecuteCommand();
}

void Table::AddColumns(unsigned n) {
	int m;
	if (leftAdd) {
		if ((m = tviewer->GetLeftSelectionColumn()) == -1)
			m = tviewer->GetNumberOfColumns();
	}
	else
		m = tviewer->GetNumberOfColumns();
	tviewer->NewCommand(new AddColumnsCmd(this, tviewer, n, m));
	tviewer->ExecuteCommand();
}

void Table::DeleteRows() {
	SetStatus("action: delete rows");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new DeleteRowsCmd(this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::DeleteColumns() {
	SetStatus("action: delete columns");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new DeleteColumnsCmd(this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::DeleteAll() {
	SetStatus("action: delete all");
	if (tviewer->GetNumberOfRows() > 0) {
		QuestionDialog q(GetMainWindow()->GetWidget(), False);
		q.Initialize();
		q.SetTitle("delete all");
		q.SetMessageString(
			"Are you sure you want to delete everything?");
		int answer = q.GetAnswer();
		if (answer == QuestionDialog::YES)
			DeleteAllCells();
		else if (answer == QuestionDialog::NO)
			SetStatus("aborted: nothing is deleted");
	}
	else
		SetStatus("aborted: table is empty");
}

void Table::DeleteAllCells() {
	tviewer->NewCommand(new DeleteAllCellsCmd(this, tviewer));
	tviewer->ExecuteCommand();
}

void Table::Purge() {
	SetStatus("action: purge table");
	if (tviewer->GetNumberOfRows() > 0) {
		tviewer->NewCommand(new PurgeCellsCmd(this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		SetStatus("aborted: table is empty");
}

void Table::CutTexts() {
	SetStatus("action: cut texts");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new CutCellTextsCmd(this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::CopyTexts() {
	SetStatus("action: copy texts");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new CopyCellTextsCmd(this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::PasteTexts() {
	SetStatus("action: paste texts");
	if (!tviewer->GetBuffer()->IsEmpty())
		tviewer->NewCommand(new PasteCellTextsCmd(this, tviewer));
	else {
		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
			Show("Warning", "There is nothing in the paste buffer");
		SetStatus("aborted: paste buffer is empty");
	}
}

void Table::SortRows() {
	SetStatus("action: sort rows");
	tviewer->NewCommand(new SortRowsCmd(this, tviewer));
	tviewer->ExecuteCommand();
}

void Table::SortColumns() {
	SetStatus("action: sort columns");
	tviewer->NewCommand(new SortColumnsCmd(this, tviewer));
	tviewer->ExecuteCommand();
}

void Table::FindAll(const string *s, bool sens, bool substr, bool) {
	tviewer->NewCommand(new FindAllCellsCmd(
			this, tviewer, s, sens, substr));
	tviewer->ExecuteCommand();
}

void Table::FindNext(const string *s, bool sens, bool substr, bool) {
	tviewer->NewCommand(new FindNextCellCmd(
			this, tviewer, s, sens, substr));
	tviewer->ExecuteCommand();
}

void Table::ReplaceNext(const string *s1, const string *s2, 
		bool sens, bool substr, bool) {
	tviewer->NewCommand(new ReplaceNextCellTextCmd(
			this, tviewer, s1, s2, sens, substr));
	tviewer->ExecuteCommand();
}

void Table::ReplaceAll(const string *s1, const string *s2, 
		bool sens, bool substr, bool) {
	tviewer->NewCommand(new ReplaceAllCellTextsCmd(
			this, tviewer, s1, s2, sens, substr));
	tviewer->ExecuteCommand();
}

void Table::SameWidth() { }

void Table::SameHeight() { }

void Table::Span() { }

void Table::UnSpan() { }

void Table::SelectAll() {
	SetStatus("action: select all");
	tviewer->NewCommand(new SelectAllCellsCmd(this, tviewer));
	tviewer->ExecuteCommand();
}

void Table::Move(Document::MoveType t) {
	tviewer->NewCommand(new MoveTableCmd(this, tviewer, t));
	tviewer->ExecuteCommand();
}

void Table::SetDefaultNumberOfRows(unsigned n) {
	string txt = "def. number of rows is ";
	txt += n;
	SetStatus(&txt);
	tviewer->SetDefaultNumberOfRows(n);
}

void Table::SetDefaultNumberOfColumns(unsigned n) {
	string txt = "def. number of columns is ";
	txt += n;
	SetStatus(&txt);
	tviewer->SetDefaultNumberOfColumns(n);
}

void Table::SetDefaultRowHeight(int n) {
	string txt = "default row height is ";
	txt += n;
	SetStatus(&txt);
	tviewer->TextModeOff();
	tviewer->UpdateDefaultRowHeight(n);
}

void Table::SetDefaultColumnWidth(int n) {
	string txt = "default column width is ";
	txt += n;
	SetStatus(&txt);
	tviewer->TextModeOff();
	tviewer->UpdateDefaultColumnWidth(n);
}
 
void Table::SetMarginWidth(int n) {
	string txt = "text margin width is ";
	txt += n;
	SetStatus(&txt);
	tviewer->TextModeOff();
	tviewer->UpdateMarginWidth(n);
}
 
void Table::SetMarginHeight(int n) {
	string txt = "text margin height is ";
	txt += n;
	SetStatus(&txt);
	tviewer->TextModeOff();
	tviewer->UpdateMarginHeight(n);
}

void Table::ShowRowColumnLabels(bool b) {
	string txt = (b ? "Show":"Don't show");
	txt += " row and column labels";
	SetStatus(&txt);
	tviewer->ShowRowColumnLabels(b);
}

void Table::PrintRowColumnLabels(bool b) {
	string txt = (b ? "Print":"Don't print");
	txt += " row and column labels";
	SetStatus(&txt);
	tviewer->PrintRowColumnLabels(b);
}

void Table::SetDefaultNumberOfRows() {
	SetStatus("action: set number of rows");
	scaleDialog->SetTitle("Number of rows");
	scaleDialog->SetScaleLabel("Default number of rows:	   ");
	scaleDialog->SetScaleValues(MIN_NUMBER_OF_ROWS, MAX_NUMBER_OF_ROWS, 
		tviewer->GetDefaultNumberOfRows(), 0, defaultNumberOfRows);
	scaleDialog->SetValueChangedCallback(TableStubs::NumberOfRowsCB, this);
	scaleDialog->Popup();
}

void Table::SetDefaultNumberOfColumns() {
	SetStatus("action: set number of columns");
	scaleDialog->SetTitle("Number of columns");
	scaleDialog->SetScaleLabel("Default number of columns:	");
	scaleDialog->SetScaleValues(MIN_NUMBER_OF_COLUMNS, 
		MAX_NUMBER_OF_COLUMNS, tviewer->GetDefaultNumberOfColumns(), 
		0, defaultNumberOfColumns);
	scaleDialog->SetValueChangedCallback(
		TableStubs::NumberOfColumnsCB, this);
	scaleDialog->Popup();
}

void Table::SetDefaultRowHeight() {
	SetStatus("action: set default row height");
	scaleDialog->SetTitle("Row Height");
	scaleDialog->SetScaleLabel("Default row height (in pixels)    ");
	scaleDialog->SetScaleValues(MIN_ROW_HEIGHT, MAX_ROW_HEIGHT,
		tviewer->GetDefaultRowHeight(), 0, defaultRowHeight);
	scaleDialog->SetValueChangedCallback(TableStubs::RowHeightCB, this);
	scaleDialog->Popup();
}

void Table::SetDefaultColumnWidth() {
	SetStatus("action: set default column width");
	scaleDialog->SetTitle("Column Width");
	scaleDialog->SetScaleLabel("Default column width (in pixels)  ");
	scaleDialog->SetScaleValues(MIN_COLUMN_WIDTH,MAX_COLUMN_WIDTH,
		tviewer->GetDefaultColumnWidth(), 0, defaultColumnWidth);
	scaleDialog->SetValueChangedCallback(TableStubs::ColumnWidthCB, this);
	scaleDialog->Popup();
}

void Table::UpdateLineStyle(Side::Type side, 
			    LineStyle::Type ltype) {
	SetStatus("action: update line style");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new UpdateLineStyleTableCmd(
				this, tviewer, side, ltype));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::UpdateCellTextUnderline() {
	SetStatus("action: set/unset cell text underlinings");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new UpdateCellTextUnderlineCmd(
				this, tviewer));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::UpdateLineWidth(Side::Type side, unsigned width) {
	SetStatus("action: update line width");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new UpdateLineWidthTableCmd(
				this, tviewer, side, width));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::UpdateColumnAlignment(TextAlign::Type a) {
	SetStatus("action: update column alignment");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new 
				UpdateColumnAlignmentCmd(this, tviewer, a));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::UpdateRowAlignment(TextAlign::Type a) {
	SetStatus("action: update row alignment");
	if (tviewer->NrSelected() > 0) {
		tviewer->NewCommand(new 
				UpdateRowAlignmentCmd(this, tviewer, a));
		tviewer->ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void Table::UpdateMarginWidth() {
	SetStatus("action: set margin width");
	scaleDialog->SetTitle("Text margin width");
	scaleDialog->SetScaleLabel("New text margin width (in pixels)   ");
	scaleDialog->SetScaleValues(MIN_MARGIN_WIDTH, MAX_MARGIN_WIDTH,
		tviewer->GetMarginWidth(), 0, defaultMarginWidth);
	scaleDialog->SetValueChangedCallback(TableStubs::MarginWidthCB, this);
	scaleDialog->Popup();
}

void Table::UpdateMarginHeight() {
	SetStatus("action: set margin height");
	scaleDialog->SetTitle("Text margin height");
	scaleDialog->SetScaleLabel("New text margin height (in pixels)  ");
	scaleDialog->SetScaleValues(MIN_MARGIN_HEIGHT, MAX_MARGIN_HEIGHT,
		tviewer->GetMarginHeight(), 0, defaultMarginHeight);
	scaleDialog->SetValueChangedCallback(TableStubs::MarginHeightCB, this);
	scaleDialog->Popup();
}

void Table::UpdateDefaultColumnAlignment(TextAlign::Type newType) {
	SetStatus("action: default column alignment");
	tviewer->SetDefaultColumnAlignment(newType);
	List<CellColumn *> columns;
	tviewer->GetEmptyColumns(&columns);
	for (columns.first(); !columns.done(); columns.next())
		columns.cur()->UpdateAlignment(newType);
}

void Table::UpdateDefaultRowAlignment(TextAlign::Type newType) {
	SetStatus("action: default row alignment");
	tviewer->SetDefaultRowAlignment(newType);
	List<CellRow *> rows;
	tviewer->GetEmptyRows(&rows);
	for (rows.first(); !rows.done(); rows.next())
		rows.cur()->UpdateAlignment(newType);
}

bool Table::UpdateText(Cell *c, const string *t) {
	if (!check(c))
		return False;
	c->UpdateText(t);
	return True;
}

void Table::AnnotateCell() {
	SetStatus("action: annotate cell");
	if (tviewer->NrSelected() == 1) {
		Cell *cell = (*tviewer->GetSelection())[0];
		AnnotateCell(cell);
	}
	else if (tviewer->NrSelected() == 0)
		EmptySelectionMessage();
	else {
		(new MessageDialog(GetMainWindow()->GetWidget(), 
		MessageDialog::WARNING))->
		Show("Warning", "Select only one single cell to annotate");
		SetStatus("aborted: selection too large");
	}
}

void Table::AnnotateCell(Cell *cell) {
	if (GetEltAnnotationDialog()->IsManaged()) {
		ShowDialog(MessageDialog::WARNING, "Warning",
			"At most one cell annotation dialog "
			"can be opened at a time");
		return;
	}
	string n = cell->GetRow()->GetNumber();
	n += ",";
	n += cell->GetColumn()->GetNumber();
	const string *annot = cell->GetAnnotation();
	annotationCell = cell;
	string title = "Annotation of cell " + n;
	GetEltAnnotationDialog()->SetTitle(&title);
	GetEltAnnotationDialog()->SetTextString(annot);
	GetEltAnnotationDialog()->Popup();
	GetEltAnnotationDialog()->SetStatus(&title);
}

void Table::SetCellAnnotation(const string *s) {
	SetStatus("action: update cell annotation");
	if (!check(annotationCell))
		return;
	// make here an undoable command!
	annotationCell->SetAnnotation(s);
}

void Table::EmptySelectionMessage() {
	(new MessageDialog(GetMainWindow()->GetWidget(), 
		MessageDialog::WARNING))->
		Show("Warning", "No cells are selected");
	SetStatus("aborted: selection is empty");
}

void Table::EmptyTableMessage() {
	(new MessageDialog(GetMainWindow()->GetWidget(), 
		MessageDialog::WARNING))->Show("Warning", "Table is empty");
	SetStatus("aborted: there are no cells");
}

void Table::DefaultRowAlignment() {
	SetStatus("action: default row alignment");
	rowAlignmentDialog->SetTitle("default row alignment");
	rowAlignmentDialog->SetHelpCallback(
		TableStubs::DefaultRowAlignmentDefaultCB, this);
	rowAlignmentDialog->SetOKCallback(
		TableStubs::DefaultRowAlignmentOKCB, this);
	ShowDefaultRowAlignment();
	rowAlignmentDialog->Popup();
}

void Table::DefaultColumnAlignment() {
	SetStatus("action: default column alignment");
	columnAlignmentDialog->SetTitle("default column alignment");
	columnAlignmentDialog->SetHelpCallback(
		TableStubs::DefaultColumnAlignmentDefaultCB, this);
	columnAlignmentDialog->SetOKCallback(
		TableStubs::DefaultColumnAlignmentOKCB, this);
	ShowDefaultColumnAlignment();
	columnAlignmentDialog->Popup();
}

void Table::UpdateRowAlignment() {
	SetStatus("action: update row alignment");
	rowAlignmentDialog->SetTitle("update row alignment");
	rowAlignmentDialog->SetHelpCallback(
		TableStubs::UpdateRowAlignmentDefaultCB, this);
	rowAlignmentDialog->SetOKCallback(
		TableStubs::UpdateRowAlignmentOKCB, this);
	rowAlignmentDialog->Popup();
}

void Table::UpdateColumnAlignment() {
	SetStatus("action: update column alignment");
	columnAlignmentDialog->SetTitle("update column alignment");
	columnAlignmentDialog->SetHelpCallback(
		TableStubs::UpdateColumnAlignmentDefaultCB, this);
	columnAlignmentDialog->SetOKCallback(
		TableStubs::UpdateColumnAlignmentOKCB, this);
	columnAlignmentDialog->Popup();
}

void Table::UpdateTableLineStyle() {
	SetStatus("action: update line style");
	tableLineStyleDialog->Popup();
}

void Table::UpdateTableLineWidth() {
	SetStatus("action: update line width");
	tableLineWidthDialog->Popup();
}

void Table::ShowDefaultLineStyle() {
	SetStatus("reset to default line style");
	string text;
	LineStyle::Type2String(GetViewer()->GetDefaultLineStyle(), &text);
	tableLineStyleDialog->SetValueOfText(0, &text);
	tableLineStyleDialog->SetValue(1, 0);
}

void Table::ShowConfigLineStyle() {
	SetStatus("reset to config line style");
	string text;
	LineStyle::Type2String(GetConfig()->GetLineStyle(), &text);
	tableLineStyleDialog->SetValueOfText(0, &text);
	tableLineStyleDialog->SetValue(1, 0);
}

void Table::ShowDefaultLineWidth() {
	SetStatus("reset to default line width");
	string text = GetViewer()->GetDefaultLineWidth();
	tableLineWidthDialog->SetValueOfText(0, &text);
	tableLineWidthDialog->SetValue(1, 0);
}
 
void Table::ShowConfigLineWidth() {
	SetStatus("reset to config line width");
	int wd = max(Viewer::MIN_LINE_WIDTH, 
		 min(GetConfig()->GetLineWidth(), Viewer::MAX_LINE_WIDTH));
	string text = wd;
	tableLineWidthDialog->SetValueOfText(0, &text);
	tableLineWidthDialog->SetValue(1, 0);
}

void Table::ShowDefaultColumnAlignment() {
	SetStatus("reset to default column alignment");
	string text;
	TextAlign::Type2String(tviewer->GetDefaultColumnAlignment(), &text);
	columnAlignmentDialog->SetValueOfText(0, &text);
}
 
void Table::ShowConfigColumnAlignment() {
	SetStatus("reset to config column alignment");
	string text;
	TextAlign::Type2String(GetConfig()->GetColumnAlignment(), &text);
	columnAlignmentDialog->SetValueOfText(0, &text);
}

void Table::ShowDefaultRowAlignment() {
	SetStatus("reset to default row alignment");
	string text;
	TextAlign::Type2String(tviewer->GetDefaultRowAlignment(), &text);
	if (text %= "Left")
		rowAlignmentDialog->SetValue(0, 0);
	else if (text %= "Right")
		rowAlignmentDialog->SetValue(0, 2);
	else
		rowAlignmentDialog->SetValue(0, 1);
}
 
void Table::ShowConfigRowAlignment() {
	SetStatus("reset to config row alignment");
	string text;
	TextAlign::Type2String(GetConfig()->GetRowAlignment(), &text);
	if (text %= "Left")
		rowAlignmentDialog->SetValue(0, 0);
	else if (text %= "Right")
		rowAlignmentDialog->SetValue(0, 2);
	else
		rowAlignmentDialog->SetValue(0, 1);
}
