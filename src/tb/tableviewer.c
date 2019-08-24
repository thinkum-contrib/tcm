////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "tableviewer.h"
#include "tablewindow.h"
#include "table.h"
#include "updatecelltextcmd.h"
#include "dragrowcmd.h"
#include "dragcolumncmd.h"
#include "dragcelltextcmd.h"
#include "dragrowlabelcmd.h"
#include "dragcolumnlabelcmd.h"
#include "selectcellareacmd.h"
#include "cell.h"
#include "rowcolumnlabel.h"
#include "celltexteditor.h"
#include "celltextbuffer.h"
#include "cellrow.h"
#include "cellcolumn.h"
#include "linepiece.h"
#include "inputfile.h"
#include "outputfile.h"
#include "updatecelltextfontcmd.h"
#include "messagedialog.h"
#include "config.h"
#include "key.h"
#include <ctype.h>

TableViewer::TableViewer(Config *c, TableWindow *t): Viewer(c, t) {
	width = 0; height = 0;
	table = 0;
	defaultTopLeft = c->GetTableTopLeft();
	topLeft = defaultTopLeft;
	rows = new List<CellRow *>;
	columns = new List<CellColumn *>;
	selection = new CellSelection;
	buffer = new CellTextBuffer();
	SetInlineEditor(new CellTextEditor(this));
	defaultColumnAlignment = c->GetColumnAlignment();
	defaultRowAlignment = c->GetRowAlignment();
	SetMarginWidth(c->GetTableMarginWidth());
	SetMarginHeight(c->GetTableMarginHeight());
	SetDefaultRowHeight(c->GetDefaultRowHeight());
	SetDefaultColumnWidth(c->GetDefaultColumnWidth());
	SetDefaultNumberOfColumns(c->GetNumberOfColumns());
	SetDefaultNumberOfRows(c->GetNumberOfRows());
	showRowColumnLabels = c->GetShowRowColumnLabels();
	printRowColumnLabels = c->GetPrintRowColumnLabels();
	currentRow = currentColumn = 0;
}

TableViewer::~TableViewer() {
	DeleteCells();
	delete selection;
	delete columns;
	delete rows;
	delete buffer;
}

void TableViewer::DeleteCells() {
	selection->DeselectAll();
	// to avoid that cells are deleted twice.
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->EmptyCells();
	rows->clear();
	columns->clear();
}

void TableViewer::Initialize() {
	topLeft = defaultTopLeft;
	InitTable(defaultNumberOfRows, defaultNumberOfColumns);
	GetMainWindow()->FitDocument(static_cast<int>(0.5 + Scale(width)+300), 
								 static_cast<int>(0.5 + Scale(height)+300));
	Refresh();
}

void TableViewer::InitTable(unsigned nrOfRows, unsigned nrOfColumns) {
	string s;
	DeleteCells();
	DeleteCommands();
	height = nrOfRows*defaultRowHeight; 
	width = nrOfColumns*defaultColumnWidth;;
	for (unsigned i=0; i<nrOfColumns; i++) {
		CellColumn *c = new CellColumn(this, i, defaultColumnWidth);
		columns->add(c);
		c->SetLabelsVisible(showRowColumnLabels);
	}
	for (unsigned j=0; j<nrOfRows; j++) {
		CellRow *row = new CellRow(this, j, defaultRowHeight);
		rows->add(row);
		row->SetLabelsVisible(showRowColumnLabels);
		for (unsigned k=0; k<nrOfColumns; k++) {
			int y = topLeft.y + j * defaultRowHeight + 
					defaultRowHeight/2;
			int x = topLeft.x + k * defaultColumnWidth + 
					defaultColumnWidth/2;
			CellColumn *column = (*columns)[k];
			Cell *c = new Cell(GetGrafport(), GetDefaultFont(), 
					row, column, 
					x, y, defaultColumnWidth, 
					defaultRowHeight);
			row->AddCell(c, False);
			(*columns)[k]->AddCell(c, False);
#ifdef DEBUG
			string buf = j;
			buf += ",";
			buf += k;
			c->GetCellText()->SetText(&buf);
#endif
		}
	}
}

void TableViewer::Draw() {
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->Draw();
	for (columns->first(); !columns->done(); columns->next()) {
		// don't draw the cells twice.
		columns->cur()->DrawLabels();
		columns->cur()->DrawLines();
	}
}

void TableViewer::Undraw() {
	Draw();
}			

void TableViewer::SetGrafport(Grafport *g) {
	Viewer::SetGrafport(g);
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->SetGrafport(g);
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->SetGrafport(g);
}

void TableViewer::ShowRowColumnLabels(bool s) {
	if (s == showRowColumnLabels)
		return;
	showRowColumnLabels = s;
	if (!s) {
		for (rows->first(); !rows->done(); rows->next())
			rows->cur()->UndrawLabels();
		for (columns->first(); !columns->done(); columns->next())
			columns->cur()->UndrawLabels();
	}
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->SetLabelsVisible(s);
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->SetLabelsVisible(s);
	if (s) {
		for (rows->first(); !rows->done(); rows->next())
			rows->cur()->DrawLabels();
		for (columns->first(); !columns->done(); columns->next())
			columns->cur()->DrawLabels();
	}
}

void TableViewer::PrintRowColumnLabels(bool b) {
	printRowColumnLabels = b;
}

bool TableViewer::TextMode(CellText *c) {
	if (IsEditing())
		return False;
	if (!IsInlineEdit()) {
		SetEditing(True);
		((CellTextEditor *)GetInlineEditor())->StartWindow(c);
		GetMainWindow()->SetStatus("start text editing");
	}
	if (!IsEditing()) {
		SetEditing(True);
		if (IsInlineEdit()) {
			GetMainWindow()->SetCursor(MouseCursor::TERM);
			((CellTextEditor *)GetInlineEditor())->Start(c);
		}
		GetMainWindow()->SetStatus("start text editing");
		return True;
	}
	return False;
}

void TableViewer::TextModeOff() {
	if (IsEditing()) {
		if (IsInlineEdit())
			GetInlineEditor()->Stop();
		GetMainWindow()->SetStatus("stop text editing");
		SetEditing(False);
	}
}

bool TableViewer::GoIntoTextMode(Cell *cell) {
	if (selection->NrSelected() == 1 && cell == selection->FirstSelected()
	    && cell->IsEditable()) {
		CellText *celltext = cell->GetCellText();
		if (!celltext)
			return False;
		
		return TextMode(celltext);
	}
	return False;
}

void TableViewer::KeyTyped(int x, int y, int key) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	unsigned char c = (unsigned char)key;
	if (!IsEditing()) {
		if (Key::ArrowKey(key) || key == Key::TAB) {
			MoveSelection(key);
			return;
		}
		else if (iscntrl(c) && Key::EditKey(key) || 
			     !GoIntoTextMode(selection->FirstSelected()))
			return;
	}
	if (IsInlineEdit())
		EditText(key);
}

void TableViewer::Select(int x, int y) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	if (IsEditing() && IsInlineEdit()) {
		CellText *t = HitCellText(x, y);
		if (t && t == ((CellTextEditor *)GetInlineEditor())->
						 GetCellText())
			GetInlineEditor()->SetCursor(x, y);
		else
			TextModeOff();
		return;
	}
	Cell *cell = HitCell(x,y);
	RowColumnLabel *rc = 0;
	if (cell) {
		if (GoIntoTextMode(cell))
			return;
		else {
			selection->DeselectAll();
			selection->SelectCell(cell);
			currentRow = cell->GetRow()->GetNumber();
			currentColumn = cell->GetColumn()->GetNumber();
			GetMainWindow()->SetCursor(MouseCursor::TERM);
			GetMainWindow()->SetStatus("select cell");
			return;
		}
	}
	else if ((rc = HitRowLabel(x,y))) {
		selection->DeselectAll();
		SelectVector(GiveRow(rc->GetVector()->GetNumber()));
	}
	else if ((rc = HitColumnLabel(x,y))) {
		selection->DeselectAll();
		SelectVector(GiveColumn(rc->GetVector()->GetNumber()));
	}
	else {
		selection->DeselectAll();
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
		GetMainWindow()->SetStatus("deselect all");
	}
}

void TableViewer::Adjust(int x, int y) {
	if (IsEditing() && IsInlineEdit()) {
		TextModeOff();
		return;
	}
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	RowColumnLabel *rc = 0;
	Cell *cell = HitCell(x,y);
	if (cell) {
		if (cell->IsSelected()) {
			selection->DeselectCell(cell);
			GetMainWindow()->SetStatus("deselect cell");
		}
		else {
			selection->SelectCell(cell);
			GetMainWindow()->SetStatus("add to selection");
		}
	}
	else if ((rc = HitRowLabel(x,y))) {
		CellRow *r = GiveRow(rc->GetVector()->GetNumber());
		if (IsAllSelected(r))
			DeselectVector(r);
		else
			SelectVector(r);
	}
	else if ((rc = HitColumnLabel(x,y))) {
		CellColumn *c = GiveColumn(rc->GetVector()->GetNumber());
		if (IsAllSelected(c))
			DeselectVector(c);
		else
			SelectVector(c);
	}
	else {
		DeselectAll();
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
		GetMainWindow()->SetStatus("deselect all");
	}
}

void TableViewer::MovingPointer(int x, int y) {
	if (x <= 3 || y <= 3) { // notify enter/leave
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	if (!IsAutoResize()) {
		if (HitVLinePiece(x,y)) {
			GetMainWindow()->SetCursor(MouseCursor::H_DOUBLE_ARROW);
			return;
		}
		else if (HitHLinePiece(x,y)) {
			GetMainWindow()->SetCursor(MouseCursor::V_DOUBLE_ARROW);
			return;
		}
	}
	if (selection->NrSelected() != 1) {
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	Cell *cell = selection->FirstSelected();
	if (cell->ContainsPt(x,y))
		GetMainWindow()->SetCursor(MouseCursor::TERM);
	else
		GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);

}	 

Command *TableViewer::Drag(int x, int y) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	LinePiece *line = 0;
	RowColumnLabel *rc = 0;
	CellText *t;
	// take care of line piece hitting first.
	if (!IsAutoResize() && (line = HitVLinePiece(x,y))) {
		return new DragColumnCmd(table, this, line);
	}
	else if (!IsAutoResize() && (line = HitHLinePiece(x,y))) {
		return new DragRowCmd(table, this, line);
	}
	// look for filled cell.
	else if ((t = HitCellText(x,y)) && t->GetParent()->IsEditable()) {
		TextModeOff();
		if (*t->GetText() != "")
			return new DragCellTextCmd(table, this, t);
	}
	else if ((rc = HitRowLabel(x,y))) {
		return new DragRowLabelCmd(table, this, rc);
	}
	else if ((rc = HitColumnLabel(x,y))) {
		return new DragColumnLabelCmd(table, this, rc);
	}
	return 0;
}	

Command *TableViewer::Connect(int x, int y) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	if (HitCell(x,y))
		return new SelectCellAreaCmd(table, this);
	else
		return 0;
}

Cell *TableViewer::HitCell(int x, int y) {
	for (rows->first(); !rows->done(); rows->next()) {
		CellRow *row = rows->cur();
		Cell *cell = row->HitCell(x,y);
		if (cell)
			return cell;
	} 
	return 0;
}

CellText *TableViewer::HitCellText(int x, int y) {
	Cell *cell = HitCell(x,y);
	if (cell) {
		CellText *celltext = cell->GetCellText();
		if (celltext)
			return celltext;
	}
	return 0;
}

LinePiece *TableViewer::HitVLinePiece(int x, int y) {
	for (rows->first(); !rows->done(); rows->next()) {
		CellRow *row = rows->cur();
		LinePiece *line = row->HitLinePiece(x,y);
		if (line)
			return line;
	}
	return 0;
}

LinePiece *TableViewer::HitHLinePiece(int x, int y) {
	for (columns->first(); !columns->done(); columns->next()) {
		CellColumn *column = columns->cur();
		LinePiece *line = column->HitLinePiece(x,y);
		if (line)
			return line;
	}
	return 0;
}

RowColumnLabel *TableViewer::HitRowLabel(int x, int y) {
	for (rows->first(); !rows->done(); rows->next()) {
		CellRow *row = rows->cur();
		RowColumnLabel *rc = row->HitLabel(x,y);
		if (rc)
			return rc;
	} 
	return 0;
}

RowColumnLabel *TableViewer::HitColumnLabel(int x, int y) {
	for (columns->first(); !columns->done(); columns->next()) {
		CellColumn *column = columns->cur();
		RowColumnLabel *rc = column->HitLabel(x,y);
		if (rc)
			return rc;
	}
	return 0;
}

int TableViewer::HitRow(int x, int y) {
	// if ((x > topLeft.x+width) || (y < topLeft.y) || (y > topLeft.y+height))
	// 	return -1;
	for (rows->first(); !rows->done(); rows->next()) {
		if (rows->cur()->ContainsPt(x,y))
			return rows->cur()->GetNumber();
	}
	return -1;
}

int TableViewer::HitColumn(int x, int y) {
	// if ((x < topLeft.x) || (x > topLeft.x+width) || (y > topLeft.y+height))
	// 	return -1;
	for (columns->first(); !columns->done(); columns->next()) {
		if (columns->cur()->ContainsPt(x,y))
			return columns->cur()->GetNumber();
	}
	return -1;
}

bool TableViewer::IsAllSelected(CellVector *v) {
	Cell *cell;
	for ((cell = v->FirstCell()); cell; (cell = v->NextCell())) {
		if (!cell->IsSelected())
			return False;
	} 
	return True;
}

void TableViewer::SelectVector(CellVector *v) {
	Cell *cell;
	for ((cell = v->FirstCell()); cell; (cell = v->NextCell()))
		selection->SelectCell(cell);
}

void TableViewer::DeselectVector(CellVector *v) {
	Cell *cell;
	for ((cell = v->FirstCell()); cell; (cell = v->NextCell()))
		selection->DeselectCell(cell);
}

void TableViewer::SelectAll() {
	for (rows->first(); !rows->done(); rows->next())
		SelectVector(rows->cur());
}

void TableViewer::MoveSelection(int key) {
	List<Cell *> newSelection;
	Cell *cell;
        unsigned rl = rows->count()-1;
        unsigned cl = columns->count()-1;
        for ((cell=selection->FirstSelected());cell;
                        (cell=selection->NextSelected())) {
                CellRow *row = cell->GetRow();
                CellColumn *col = cell->GetColumn();
                unsigned rowNr = row->GetNumber();
                unsigned colNr = col->GetNumber();
                if (key == Key::UP) {
                	if (rowNr > 0)        
				rowNr--;
			else {
				rowNr=rl;
                        	if (colNr > 0)
					colNr--;
				else
					colNr=cl;
			}
		}
                else if (key == Key::DOWN) {
                        if (rowNr < rl)
				rowNr++;
			else {
				rowNr = 0;
                        	if (colNr < cl)
					colNr++;
				else
					colNr=0;
			}
		}
                else if (key == Key::LEFT) {
                        if (colNr > 0)
				colNr--;
			else {
				colNr=cl;
                        	if (rowNr > 0)
					rowNr--;
				else
					rowNr=rl;
			}
		}
                else if (key == Key::RIGHT || key == Key::TAB) {
                        if (colNr < cl)
				colNr++;
			else {
				colNr=0;
                        	if (rowNr < rl)
					rowNr++;
				else
					rowNr=0;
			}
		}
		row = GiveRow(rowNr);
		if (check(row)) {
			Cell *cell2 = row->NthCell(colNr);
			if (check(cell2))
				newSelection.add(cell2);
		}
        }
	selection->DeselectAll();
	for (newSelection.first(); !newSelection.done(); newSelection.next())
		selection->SelectCell(newSelection.cur());
	GetMainWindow()->SetStatus("move selection");
	
}

int TableViewer::GetRowHeight(unsigned n) {
	CellRow *r;
	if ((r = GiveRow(n)))
		return r->GetHeight();
	else
		return defaultRowHeight;
}

int TableViewer::GetColumnWidth(unsigned n) {
	CellColumn *c;
	if ((c = GiveColumn(n)))
		return c->GetWidth();
	else
		return defaultColumnWidth;
}

Point TableViewer::GetRowTopLeft(unsigned n) {
	CellRow *r;
	if (((r = GiveRow(n)) && (r->NrCells()>0)))
		return *r->FirstCell()->GetTopLeft();
	else {
		Point pt = topLeft;
		pt.y += n*defaultRowHeight;
		return pt;
	}
}

Point TableViewer::GetColumnTopLeft(unsigned n) {
	CellColumn *c;
	if (((c = GiveColumn(n)) && (c->NrCells() > 0)))
		return *c->FirstCell()->GetTopLeft();
	else {
		Point pt = topLeft;
		pt.x += n*defaultColumnWidth;
		return pt;
	}
}

CellRow *TableViewer::GiveRow(unsigned r) {
	if (r < rows->count())
		return (*rows)[r];
	else
		return 0;
}

CellColumn *TableViewer::GiveColumn(unsigned c) {
	if (c < columns->count())
		return (*columns)[c];
	else
		return 0;
}

void TableViewer::RecomputeSizeCell(Cell *c) {
	if (!IsAutoResize())
		return;
	int cw = c->GetWidth();
	int ch = c->GetHeight();
	int tw = c->GetTextWidth() + 2*marginWidth;
	int th = c->GetTextHeight() + 2*marginHeight;
	CellColumn *column = c->GetColumn();
	CellRow *row = c->GetRow();
	if (!check(row && column))
		return;
	// bool resized = False;
	if (tw > cw) {	// column has to be made wider.
		ResizeColumn(column, tw);
		// resized = True;
	}
	if (th > ch) {
		ResizeRow(row, th); // row has to be made higher.
		// resized = True;
	}
	// if (resized)
	// 	return;
	if (tw < cw) {
		int minw = column->GetMinimalWidth();
		int colw = column->GetWidth();
		if (minw < colw)   // column can be made less wide.
			ResizeColumn(column, max(minw, defaultColumnWidth));
	}
	if (th < ch) {
		int minh = row->GetMinimalHeight();
		int rowh = row->GetHeight();
		if (minh < rowh)   // row can be made less high.
			ResizeRow(row, max(minh, defaultRowHeight));
	}
}
	
void TableViewer::ResizeRow(CellRow *r, int newSize) {
	newSize = max(newSize, Table::MIN_ROW_HEIGHT);
	int oldSize = r->GetHeight();
	if (oldSize == newSize)
		return;
	unsigned rownr = r->GetNumber();
	height += newSize - oldSize;
	r->UpdateHeight(newSize);
	for (unsigned i = rownr+1; i < rows->count(); i++) {
		CellRow *r2 = (*rows)[i];
		r2->UpdatePosition(newSize-oldSize);
	}
	for (unsigned j=0; j<columns->count(); j++) {
		CellColumn *c = (*columns)[j];
		c->UpdateHeight(rownr);
		c->CalcLabelPositions();
	}
} 

void TableViewer::ResizeColumn(CellColumn *c, int newSize) {
	newSize = max(newSize, Table::MIN_COLUMN_WIDTH);
	int oldSize = c->GetWidth();
	if (oldSize == newSize)
		return;
	unsigned colnr = c->GetNumber();
	width += newSize - oldSize;
	c->UpdateWidth(newSize);
	for (unsigned i = colnr+1; i < columns->count(); i++) {
		CellColumn *c2 = (*columns)[i];
		c2->UpdatePosition(newSize-oldSize);
	}
	for (unsigned j=0; j<rows->count(); j++) {
		CellRow *r = (*rows)[j];
		r->UpdateWidth(colnr);
		r->CalcLabelPositions();
	}
}

void TableViewer::AddRow(CellRow *r) {
	unsigned rowNr = r->GetNumber();
	(void)check(rowNr == rows->count());
	height += r->GetHeight();
	// empty table. Create new columns.
	if (columns->count() == 0) {
		for (unsigned i=0; i<r->NrCells(); i++) {
			Cell *cell = r->NthCell(i);
			if (!check(cell))
				return;
			CellColumn *c = new CellColumn(
						this, i, cell->GetWidth());
			c->SetLabelsVisible(showRowColumnLabels);
			columns->add(c);
			width += cell->GetWidth();
		}
	}
	else 	
		(void)check(r->NrCells() == columns->count());
	rows->add(r);
	Cell *cell;
	if ((cell = r->FirstCell()) && columns->first()) {
		do {
			columns->cur()->AddCell(cell);
			columns->cur()->CalcLabelPositions();
			cell->SetColumn(columns->cur());
		} while (columns->next() && (cell = r->NextCell()));
	}
	r->CalcLabelPositions();
}

void TableViewer::AddColumn(CellColumn *c) {
	unsigned colNr = c->GetNumber();
	(void)check(colNr == columns->count());
	width += c->GetWidth();
	// empty table. Create new rows.
	if (rows->count() == 0) {
		for (unsigned i=0; i<c->NrCells(); i++) {
			Cell *cell = c->NthCell(i);
			if (!check(cell))
				return;
			CellRow *r = new CellRow(this, i, cell->GetHeight());
			rows->add(r);
			r->SetLabelsVisible(showRowColumnLabels);
			height += cell->GetHeight();
		}
	}
	else 
		(void)check(c->NrCells() == rows->count());

	columns->add(c);
	Cell *cell;
	if ((cell = c->FirstCell()) && rows->first()) {
		do {
			rows->cur()->AddCell(cell);
			rows->cur()->CalcLabelPositions();
			cell->SetRow(rows->cur());
		} while (rows->next() && (cell = c->NextCell()));
		c->CalcLabelPositions();
	}
}

void TableViewer::InsertRow(CellRow *r) {
	unsigned rowNr = r->GetNumber();
	r->SetLabelsVisible(showRowColumnLabels);
	if (rowNr >= rows->count()) {
		AddRow(r);
		return;
	}
	height += r->GetHeight();
	unsigned rowHeight = r->GetHeight();
	(void)check(r->NrCells() == columns->count());
	// shift other rows down and renumber them.
	for (unsigned i = rowNr; i < rows->count(); i++) {
		CellRow *r2 = (*rows)[i];
		r2->UpdateNumber(i+1);
		r2->UpdatePosition(rowHeight);
	}
	rows->insert(r, rowNr);
	Cell *cell;
	// insert cells into columns
	if ((cell = r->FirstCell()) && columns->first()) {
		do {
			columns->cur()->InsertCell(cell, rowNr);
			columns->cur()->CalcLabelPositions();
			cell->SetColumn(columns->cur());
		} while (columns->next() && (cell = r->NextCell()));
	}
	r->CalcLabelPositions();
}

void TableViewer::InsertColumn(CellColumn *c) {
	unsigned colNr = c->GetNumber();
	c->SetLabelsVisible(showRowColumnLabels);
	if (colNr >= columns->count()) {
		AddColumn(c);
		return;
	}
	width += c->GetWidth();
	unsigned colWidth = c->GetWidth();
	(void)check(c->NrCells() == rows->count());
	// shift other columns left and renumber them.
	for (unsigned i = colNr; i < columns->count(); i++) {
		CellColumn *c2 = (*columns)[i];
		c2->UpdateNumber(i+1);
		c2->UpdatePosition(colWidth);
	}
	columns->insert(c, colNr);
	Cell *cell;
	// insert cells into rows.
	if ((cell = c->FirstCell()) && rows->first()) {
		do {
			rows->cur()->InsertCell(cell, colNr);
			rows->cur()->CalcLabelPositions();
			cell->SetRow(rows->cur());
		} while (rows->next() && (cell = c->NextCell()));
	}
	c->CalcLabelPositions();
}

void TableViewer::DeleteRow(CellRow *r) {
	unsigned rowNr = r->GetNumber();
	unsigned rowHeight = r->GetHeight();
	(void)check(r->NrCells() == columns->count());
	Cell *cell;	
	r->Undraw();
	height -= rowHeight;
	// shift lower rows up and renumber them.
	for (unsigned i = rowNr+1; i < rows->count(); i++) {
		CellRow *r2 = (*rows)[i];
		r2->UpdateNumber(i-1);
		r2->UpdatePosition(-rowHeight);
	}
	// remove the cells from the columns.
	if ((cell = r->FirstCell()) && columns->first()) {
		do {
			columns->cur()->DeleteCell(cell);
			columns->cur()->CalcLabelPositions();
		} while (columns->next() && (cell = r->NextCell()));
	}
	// remove the row.
	rows->remove(r);
	// if the last row is deleted remove also all columns.
	if (rows->count() == 0) {
		columns->clear();
		topLeft = defaultTopLeft;
		width = height = 0;
	}
}

void TableViewer::DeleteColumn(CellColumn *c) {
	unsigned colNr = c->GetNumber();
	unsigned colWidth = c->GetWidth();
	(void)check(c->NrCells() == rows->count());
	Cell *cell;
	c->Undraw();
	width -= colWidth;
	// shift right columns to the left and renumber them.
	for (unsigned i = colNr+1; i < columns->count(); i++) {
		CellColumn *c2 = (*columns)[i];
		c2->UpdateNumber(i-1);
		c2->UpdatePosition(-colWidth);
	}
	// remove the cells from the rows.
	if ((cell = c->FirstCell()) && rows->first()) {
		do {
			rows->cur()->DeleteCell(cell);
			rows->cur()->CalcLabelPositions();
		} while (rows->next() && (cell = c->NextCell()));
	}
	// remove the column.
	columns->remove(c);
	// if the last column is deleted remove also all rows.
	if (columns->count() == 0) {
		rows->clear();
		topLeft = defaultTopLeft;
		width = height = 0;
	}
}

void TableViewer::Move(const Point *delta) {
	Point d = *delta;
	if (topLeft.x + d.x < 0)
		d.x = -topLeft.x;
	if (topLeft.y + d.y < 0)
		d.y = -topLeft.y;
	topLeft = topLeft + d;
	if (d.y != 0) {
		for (rows->first(); !rows->done(); rows->next())
			rows->cur()->UpdatePosition(d.y);
		for (columns->first(); !columns->done(); columns->next())
			columns->cur()->UpdateHeight(0);
	}
	if (d.x != 0) {
		for (columns->first(); !columns->done(); columns->next())
			columns->cur()->UpdatePosition(d.x);
		for (rows->first(); !rows->done(); rows->next())
			rows->cur()->UpdateWidth(0);
	}
}

void TableViewer::MoveRow(CellRow *r, unsigned newpos) {
	unsigned oldpos = r->GetNumber();
	if (oldpos==newpos || newpos>=rows->count())
		return;
	CellRow *nrow = GiveRow(newpos);
	Point topleft1 = *(r->FirstCell()->GetTopLeft());
	Point topleft2 = *(nrow->FirstCell()->GetTopLeft());
	if (oldpos < newpos)
		topleft2.y -= (r->GetHeight()-nrow->GetHeight());
	r->Undraw();
	DeleteRow(r);
	// set row to destination position.
	r->UpdateNumber(newpos);
	r->UpdatePosition(topleft2.y - topleft1.y);
	InsertRow(r);
}	

void TableViewer::MoveColumn(CellColumn *c, unsigned newpos) {
	unsigned oldpos = c->GetNumber();
	if (oldpos==newpos || newpos>=columns->count())
		return;
	CellColumn *ncolumn = GiveColumn(newpos);
	Point topleft1 = *(c->FirstCell()->GetTopLeft());
	Point topleft2 = *(ncolumn->FirstCell()->GetTopLeft());
	if (oldpos < newpos)
		topleft2.x -= (c->GetWidth()-ncolumn->GetWidth());
	c->Undraw();
	DeleteColumn(c);
	// set column to destination position.
	c->UpdateNumber(newpos);
	c->UpdatePosition(topleft2.x - topleft1.x);
	InsertColumn(c);
}

void TableViewer::CalcSizeElements(Point &t, Point &b) {
	t = topLeft;
	b.x = t.x + width;
	b.y = t.y + height;
}

void TableViewer::CalcSizeSelection(Point &, Point &) { }

int TableViewer::GetTopSelectionRow() {
	unsigned row = rows->count();
	Cell *cell = selection->FirstSelected();
	if (cell) {
		do {
			unsigned n = cell->GetRow()->GetNumber();
			if (n < row)
				row = n;
		} while ((cell = selection->NextSelected()));
		return row;
	}
	else
		return -1;
}

int TableViewer::GetLeftSelectionColumn() {
	unsigned column = columns->count();
	Cell *cell = selection->FirstSelected();
	if (cell) {
		do {
			unsigned n = cell->GetColumn()->GetNumber();
			if (n < column)
				column = n;
		} while ((cell = selection->NextSelected()));
		return column;
	}
	else
		return -1;
}

void TableViewer::UpdateMarginWidth(int newWidth) {
	if (marginWidth == newWidth)
		return;
	SetMarginWidth(newWidth);
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->UpdateTextPositions();
	table->IncChanges();
}

void TableViewer::UpdateMarginHeight(int newHeight) {
	if (marginHeight == newHeight)
		return;
	SetMarginHeight(newHeight);
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->UpdateTextPositions();
	table->IncChanges();
}

void TableViewer::UpdateDefaultRowHeight(int newHeight) {
	if (defaultRowHeight == newHeight)
		return;
	SetDefaultRowHeight(newHeight); 
/*
	bool change = False;
	for (rows->first(); !rows->done(); rows->next()) {
		if (rows->cur()->GetHeight() < newHeight) {
			ResizeRow(rows->cur(), newHeight);
			change = True;
		}
		else if (IsAutoResize() && rows->cur()->GetHeight()>newHeight) {
			int rh = rows->cur()->GetMinimalHeight();
			ResizeRow(rows->cur(), rh);
			change = True;
		}
	} 
	if (change)
		table->IncChanges();
*/
}

void TableViewer::UpdateDefaultColumnWidth(int newWidth) {
	if (defaultColumnWidth == newWidth)
		return;
	SetDefaultColumnWidth(newWidth); 
/*
	bool change = False;
	for (columns->first(); !columns->done(); columns->next()) {
		if (columns->cur()->GetWidth() < newWidth) {
			ResizeColumn(columns->cur(), newWidth);
			change = True;
		}
		else if (IsAutoResize() && columns->cur()->GetWidth()>newWidth){
			int rw = columns->cur()->GetMinimalWidth();
			ResizeColumn(columns->cur(), rw);
			change = True;
		}
	}
	if (change)
		table->IncChanges();
*/
}

void TableViewer::GetSelectedRows(List<CellRow *> *r) {
	Cell *cell;
	r->empty();
	for ((cell=selection->FirstSelected());cell; 
			(cell=selection->NextSelected())) {
		CellRow *row = cell->GetRow();
		if (r->find(row) == -1)
			r->add(row);
	}
}

void TableViewer::GetSelectedColumns(List<CellColumn *> *c) {
	Cell *cell;
	c->empty();
	for ((cell=selection->FirstSelected());cell;
			(cell=selection->NextSelected())) {
		CellColumn *column = cell->GetColumn();
		if (c->find(column) == -1)
			c->add(column);
	}
}
 
void TableViewer::GetEmptyRows(List<CellRow *> *r) {
	r->empty();
	for (rows->first(); !rows->done(); rows->next()) {
		CellRow *row = rows->cur();
		if (row->IsAllEmpty())
			r->add(row);
	}
}

void TableViewer::GetEmptyColumns(List<CellColumn *> *c) {
	c->empty();
	for (columns->first(); !columns->done(); columns->next()) {
		CellColumn *column = columns->cur();
		if (column->IsAllEmpty())
			c->add(column);
	}
}

void TableViewer::GetCells(
		List<Cell *> *getCells, const string *s, bool sens, bool sub) {
	for (rows->first(); !rows->done(); rows->next()) {
		CellRow *row = rows->cur();
		Cell *cell;
		for ((cell = row->FirstCell()); cell; 
				(cell = row->NextCell())) {
			if (cell->HasText(s, sens, sub))
				getCells->add(cell);
		}
	}
}

Cell *TableViewer::GetNextCell(const string *s, bool sens, bool substr) {
	unsigned rowCount = rows->count();
	unsigned columnCount = columns->count();
	if (rowCount > 0 && columnCount > 0) {
		unsigned nrOfCells = rowCount*columnCount;
		for (unsigned i=0; i<nrOfCells; i++) {
			Cell *cell = ((*rows)[currentRow])->
				NthCell(currentColumn);
			currentColumn++;
			if (currentColumn >= columnCount) {
				currentColumn = 0;
				currentRow++;
			}
			if (currentRow >= rowCount)
				currentRow = 0;
			if (!check(cell))
				return 0;
			if (cell->HasText(s, sens, substr))
				return cell; 
		}
	}
	else {
		currentRow = 0;
		currentColumn = 0;
	}
	return 0;
}

void TableViewer::SetLineStyle(Side::Type side, LineStyle::Type ltype) {
	List<LinePiece *> lines;
	Cell *cell;
	for ((cell=selection->FirstSelected());cell;
			(cell=selection->NextSelected())) {
		LinePiece *line;
		CellRow *row = cell->GetRow();
		CellColumn *column = cell->GetColumn();
		unsigned columnNr = column->GetNumber();
		unsigned rowNr = row->GetNumber();
		switch(side) {
		case Side::TOP:
			line = column->NthLine(rowNr);
			if (line && lines.find(line) == -1)
				lines.add(line);
			break;
		case Side::BOTTOM:
			line = column->NthLine(rowNr + 1);
			if (line && lines.find(line) == -1)
				lines.add(line);
			break;
		case Side::LEFT:
			line = row->NthLine(columnNr);
			if (line && lines.find(line) == -1)
				lines.add(line);
			break;
		case Side::RIGHT:
			line = row->NthLine(columnNr + 1);
			if (line && lines.find(line) == -1)
				lines.add(line);
			break;
		case Side::SURROUNDING: {
			Cell *topCell = column->NthCell(rowNr - 1);
			Cell *bottomCell = column->NthCell(rowNr + 1);
			Cell *leftCell = row->NthCell(columnNr - 1);
			Cell *rightCell = row->NthCell(columnNr + 1);
			if (!topCell || !topCell->IsSelected()) {
				line = column->NthLine(rowNr);
				if (line && lines.find(line) == -1)
					lines.add(line);
			}
			if (!bottomCell || !bottomCell->IsSelected()) {
				line = column->NthLine(rowNr + 1);
				if (line && lines.find(line) == -1)
					lines.add(line);
			}
			if (!leftCell || !leftCell->IsSelected()) {
				line = row->NthLine(columnNr);
				if (line && lines.find(line) == -1)
					lines.add(line);
			}
			if (!rightCell || !rightCell->IsSelected()) {
				line = row->NthLine(columnNr +1);
				if (line && lines.find(line) == -1)
					lines.add(line);
			}
			break;
		}
		default:
			error("unknown side type\n");
			break;
		}
	}
	for (lines.first(); !lines.done(); lines.next())
		lines.cur()->UpdateLineStyle(ltype);
	table->IncChanges();
}

void TableViewer::WriteAttributes(OutputFile *ofile) {
	// write table info to file.
	(*ofile) << "Table {\n";
	(*ofile) << "\t{ TopLeft " << topLeft << " }\n";
	(*ofile) << "\t{ NumberOfRows " << rows->count() << " }\n";
	(*ofile) << "\t{ NumberOfColumns " << columns->count() << " }\n";
	(*ofile) << "\t{ MarginWidth " << marginWidth << " }\n";
	(*ofile) << "\t{ MarginHeight " << marginHeight << " }\n";
	(*ofile) << "}\n\n";
}

void TableViewer::WriteRows(OutputFile *ofile) {
	(*ofile) << "# TABLE ROWS\n\n";
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->Write(ofile);
}

void TableViewer::WriteColumns(OutputFile *ofile) {
	(*ofile) << "# TABLE COLUMNS\n\n";
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->Write(ofile);
}

void TableViewer::WriteSelection(OutputFile *ofile) {
	List<CellRow *> selectedRows;
	List<CellColumn *> selectedColumns;
	GetSelectedRows(&selectedRows);
	GetSelectedColumns(&selectedColumns);
	if (selectedRows.count() == 0)
		 (new MessageDialog(GetMainWindow()->GetWidget(), 
		  	MessageDialog::WARNING))-> Show("Warning", 
			"Writing empty table because the selection is empty");
	selectedRows.sort(Compare);
	selectedColumns.sort(Compare);
	List<int> rowNumbers;
	List<int> columnNumbers;
	for (selectedRows.first(); !selectedRows.done(); selectedRows.next())
		rowNumbers.add(selectedRows.cur()->GetNumber());
	for (selectedColumns.first(); !selectedColumns.done(); 
			selectedColumns.next())
		columnNumbers.add(selectedColumns.cur()->GetNumber());
	// write table info to file.
	(*ofile) << "Table {\n";
	(*ofile) << "\t{ TopLeft " << topLeft << " }\n";
	(*ofile) << "\t{ NumberOfRows " << selectedRows.count() << " }\n";
	(*ofile) << "\t{ NumberOfColumns " << selectedColumns.count() << " }\n";
	(*ofile) << "\t{ MarginWidth " << marginWidth << " }\n";
	(*ofile) << "\t{ MarginHeight " << marginHeight << " }\n";
	(*ofile) << "}\n\n";
	// write the selected rows to file.
	(*ofile) << "# TABLE ROWS (from Save Selection)\n\n";
	for (unsigned i=0; i<selectedRows.count(); i++)
		selectedRows[i]->WritePartial(ofile, i, &columnNumbers);
	// write the selected columns to file.
	(*ofile) << "# TABLE COLUMNS (from Save Selection)\n\n";
	for (unsigned j=0; j<selectedColumns.count(); j++)
		selectedColumns[j]->WritePartial(ofile, j, &rowNumbers);
}

bool TableViewer::ReadAttributes(InputFile *ifile, bool appending, 
			unsigned &nrows, unsigned &ncolumns, double format) {
	string val1, val2;
	nrows = 0;
	ncolumns = 0;
	if (!ifile->LookupWord("Table") || !ifile->LookupChar('{'))
		return False;
	if (!ifile->ReadAttribute2("TopLeft", &val1, &val2))
		return False;
	if (!appending) {
		topLeft.x = val1.toint();
		topLeft.y = val2.toint();
	}
	if (!ifile->ReadAttribute("NumberOfRows", &val1))
		return False;
	nrows = val1.toint();
	if (!ifile->ReadAttribute("NumberOfColumns", &val1))
		return False;
	ncolumns = val1.toint();
	if (!ifile->ReadAttribute("MarginWidth", &val1))
		return False;
	if (!appending)
		marginWidth = val1.toint();
	if (!ifile->ReadAttribute("MarginHeight", &val1))
		return False;
	if (!appending)
		marginHeight = val1.toint();

	// some extra stuff for older table file formats.
	if (format <= 1.09) {
		if (format <= 1.08) {
			if (!ifile->ReadAttribute("DefaultLineType", &val1))
				return False;
		}
		else {
			if (!ifile->ReadAttribute("DefaultLineStyle", &val1))
				return False;
		}
		if (!appending) {
			if (format <= 1.08)
				SetDefaultLineStyle(
					(LineStyle::Type)val1.toint());
			else
				SetDefaultLineStyle(
					LineStyle::String2Type(&val1));
		}
		if (!ifile->ReadAttribute("DefaultRowAlignment", &val1))
			return False;
		if (!appending) {
			if (format <= 1.08)
				defaultRowAlignment=
					(TextAlign::Type)val1.toint();
			else
				defaultRowAlignment = 
					TextAlign::String2Type(&val1);
		}
		if (!ifile->ReadAttribute("DefaultColumnAlignment", &val1))
			return False;
		if (!appending) {
			if (format <= 1.08)
				defaultColumnAlignment = 
					(TextAlign::Type) val1.toint();
			else
				defaultColumnAlignment = 
					TextAlign::String2Type(&val1);
		}
		// in older versions "Default.." was used instead of "Minimal.."
		string keyword;
		if (format <= 1.06)
			keyword = "DefaultRowHeight";
		else
			keyword = "MinimalRowHeight";
		if (!ifile->ReadAttribute(&keyword, &val1))
			return False;
		if (!appending)
			defaultRowHeight = val1.toint();;
		// in older versions "Default.." was used instead of "Minimal.."
		if (format <= 1.06)
			keyword = "DefaultColumnWidth";
		else
			keyword = "MinimalColumnWidth";
		if (!ifile->ReadAttribute(&keyword, &val1))
			return False;
		if (!appending)
			defaultColumnWidth = val1.toint();
		if (!ifile->ReadAttribute("DefaultNumberOfRows", &val1))
			return False;
		if (!appending)
			defaultNumberOfRows = val1.toint();
		if (!ifile->ReadAttribute("DefaultNumberOfColumns", &val1))
			return False;
		if (!appending)
			defaultNumberOfColumns = val1.toint();
	}
	if (!ifile->LookupChar('}'))
		return False;
	return True;
}

bool TableViewer::ReadColumns(InputFile *ifile, unsigned nr, 
			unsigned fromRow, unsigned fromColumn, double format) {
	for (unsigned i = fromColumn; i < fromColumn+nr; i++) { 
		if (!(*columns)[i]->Read(ifile, fromRow, format))
			return False;
	}
	return True;
}

bool TableViewer::ReadRows(InputFile *ifile, unsigned nr, unsigned fromRow, 
			unsigned fromColumn, double format) {
	for (unsigned i = fromRow; i < fromRow+nr; i++) {
		if (!(*rows)[i]->Read(ifile, fromColumn, format))
			return False;
	}
	return True;
}

void TableViewer::SetVisible(bool b) {
	for (rows->first(); !rows->done(); rows->next())
		rows->cur()->SetVisible(b);
	for (columns->first(); !columns->done(); columns->next())
		columns->cur()->SetVisible(b);
}

void TableViewer::SetDefaultFont(XFont *ft) {
	Viewer::SetDefaultFont(ft);
	List<CellRow *> er;
	GetEmptyRows(&er);
	for (er.first(); !er.done(); er.next()) {
		CellRow *r = er.cur();
		Cell *cell;
		for ((cell = r->FirstCell()); cell; (cell = r->NextCell()))
			cell->SetFont(ft);
	}
	List<CellColumn *> ec;
	GetEmptyColumns(&ec);
	for (ec.first(); !ec.done(); ec.next()) {
		CellColumn *c = ec.cur();
		Cell *cell;
		for ((cell = c->FirstCell()); cell; (cell = c->NextCell()))
			cell->SetFont(ft);
	}
	for (rows->first(); !rows->done(); rows->next()) {
		rows->cur()->GetLabel1()->UpdateFont(ft);
		rows->cur()->GetLabel2()->UpdateFont(ft);
	}
	for (columns->first(); !columns->done(); columns->next()) {
		columns->cur()->GetLabel1()->UpdateFont(ft);
		columns->cur()->GetLabel2()->UpdateFont(ft);
	}
}

void TableViewer::UpdateText(Cell *c, const string *s) {
	if (!check(table))
		return;
	if (c) {
		bool found = False;
		for (rows->first(); !rows->done(); rows->next())
			if (rows->cur()->HasCell(c))
				found = True;
		if (found) {
			NewCommand(new UpdateCellTextCmd(table, this, c, s));
			ExecuteCommand();
			return;
		}
	}
	GetMainWindow()->SetStatus("aborted: cell does not exist");
}

void TableViewer::UpdateFontSelection(int f, int s, int p) {
	if (selection->NrSelected() > 0) {
		NewCommand(new UpdateCellTextFontCmd(table, this, f, s, p));
		ExecuteCommand();
	}
	else
	 	(new MessageDialog(GetMainWindow()->GetWidget(), 
				   MessageDialog::WARNING))->
			Show("Warning", "No cells are selected");
}

void TableViewer::UpdateLineStyleSelection(LineStyle::Type) {
	error("update line style is not implemented in this manner\n");
}

void TableViewer::UpdateTextAlignmentSelection(TextAlign::Type) {
	error("update text alignment is not implemented in this manner\n");
}

void TableViewer::UpdateLineColorSelection(const string *) {
	error("update line color is not implemented \n");
}

void TableViewer::UpdateTextColorSelection(const string *) {
	error("update text color is not implemented \n");
}

void TableViewer::UpdateFillColorSelection(const string *,
		FillStyle::Type) {
	error("update fill color is not implemented \n");
}

void TableViewer::UpdateLineWidthSelection(unsigned) {
	error("update line width is not implemented yet\n");
}

void TableViewer::SetMarginWidth(int w) {
	marginWidth = min(max (w, Table::MIN_MARGIN_WIDTH),
		Table::MAX_MARGIN_WIDTH);
}

void TableViewer::SetMarginHeight(int h) {
	marginHeight = min(max (h, Table::MIN_MARGIN_HEIGHT),
		Table::MAX_MARGIN_HEIGHT);
}

void TableViewer::SetDefaultColumnWidth(int w) {
	defaultColumnWidth = min(max (w, Table::MIN_COLUMN_WIDTH), 
		Table::MAX_COLUMN_WIDTH);
}

void TableViewer::SetDefaultRowHeight(int h) {
	defaultRowHeight = min(max(h, Table::MIN_ROW_HEIGHT), 
		Table::MAX_ROW_HEIGHT);
}

void TableViewer::SetDefaultNumberOfRows(unsigned n) {
	defaultNumberOfRows = min(max(n, Table::MIN_NUMBER_OF_ROWS), 
		Table::MAX_NUMBER_OF_ROWS);
}

void TableViewer::SetDefaultNumberOfColumns(unsigned n) {
	defaultNumberOfColumns = min(max(n, Table::MIN_NUMBER_OF_COLUMNS), 
		Table::MAX_NUMBER_OF_COLUMNS);
}
