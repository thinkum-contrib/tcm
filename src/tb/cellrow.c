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
#include "cellrow.h"
#include "cell.h"
#include "rowcolumnlabel.h"
#include "linepiece.h"
#include "rectangle.h"
#include "inputfile.h"
#include "outputfile.h"
#include <stdlib.h>

CellRow::CellRow(TableViewer *v, unsigned n, int h): CellVector(v,n) {
	height = h;
	SetAlignment(v->GetDefaultRowAlignment());
	CalcLabelPositions();
}

void CellRow::CalcLabelPositions() {
	// distance between row label and the cells.
	const int LABEL_DIST = 4;
	RowColumnLabel *l1 = GetLabel1();
	RowColumnLabel *l2 = GetLabel2();
	if (l1 && l2) {
		Point pt;
		if (cells->count() == 0)
			pt = GetViewer()->GetRowTopLeft(GetNumber());
		else
			pt = *(*cells)[0]->GetTopLeft();
		pt.y += height/2;
		pt.x -= (l1->GetWidth()/2 + LABEL_DIST);
		if (GetViewer()->IsShowRowColumnLabels())
			l1->UpdatePosition(&pt);
		else
			l1->SetPosition(&pt);
		pt.x += GetViewer()->GetWidth() + 
			l1->GetWidth() + 2*LABEL_DIST;
		if (GetViewer()->IsShowRowColumnLabels())
			l2->UpdatePosition(&pt);
		else
			l2->SetPosition(&pt);
	}
}

void CellRow::UpdateWidth(unsigned colnr) {
	Point p1, p2, p3;
	Cell *cell;
	LinePiece *line;
	int width;
	if (colnr == 0 && cells->count() > 0) { // shift first line.
		cell = (*cells)[0];
		line = (*lines)[0];
		p1 = *cell->GetTopLeft();
		p2.x = p1.x;
		p2.y = p1.y + height;
		line->UpdatePoints(&p1, &p2);
		CalcLabelPositions();
	}
	for (unsigned i=colnr; i<cells->count(); i++) {
		cell = (*cells)[i];
		line = (*lines)[i+1];
		width = cell->GetWidth();
		p1 = *cell->GetTopLeft();
		if (line) {
			p2 = *line->GetBegin();
			p2.x = p1.x + width; 
			p3 = *line->GetEnd();
			p3.x = p1.x + width; 
			line->UpdatePoints(&p2, &p3);
		}
	}
}

void CellRow::UpdatePosition(int delta) {
	if (delta == 0)
		return;
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		Point pt = *cell->GetPosition();
		pt.y += delta;
		cell->UpdatePosition(&pt);
	}
	for (lines->first(); !lines->done(); lines->next()) {
		LinePiece *line = lines->cur();
		Point pt1 = *line->GetBegin();
		if (pt1.y + delta >= 0) {
			pt1.y += delta;
			Point pt2 = *line->GetEnd();
			pt2.y += delta;
			line->UpdatePoints(&pt1, &pt2);
		}
	}
	CalcLabelPositions();
}

void CellRow::UpdateHeight(int h) {
	if (h == height)
		return;
	for (lines->first(); !lines->done(); lines->next()) {
		LinePiece *line = lines->cur();
		Point pt = *line->GetEnd();
		pt.y = pt.y - height + h;
		line->UpdateEnd(&pt);
	} 
	height = h;
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		int wd = cell->GetWidth();
		Point pt = *cell->GetTopLeft();
		pt.y = pt.y + height/2;
		pt.x = pt.x + wd/2;
		cell->Undraw();
		cell->SetSize(wd, height);
		cell->SetPosition(&pt);
		cell->Draw();
	}
	CalcLabelPositions();
}

Cell *CellRow::HitCell(int x, int y) {
	if (!cells->first())
		return 0;
	Cell *cell = cells->cur();
	Point pt = *(cell->GetTopLeft());
	// look for this row.
	if (y > pt.y && y < pt.y + height) {
		// ok, look for right column.
		do {
			cell = cells->cur();
			int wd = cell->GetWidth();
			pt = *(cell->GetTopLeft());
			if (x > pt.x && x < pt.x + wd)
				return cell;
		} while (cells->next());
	}
	return 0; // not in this row.
}

LinePiece *CellRow::HitLinePiece(int x, int y) {
	if (!lines->first())
		return 0;
	LinePiece *line = lines->cur();
	Point pt = *(line->GetBegin());
	// look for this row.
	if (y > pt.y && y < pt.y + height) {
		do {
			line = lines->cur();
			pt = *line->GetBegin();
			if (x > pt.x-3 && x < pt.x+3)
				return line;
		} while (lines->next());
	}
	return 0; // not in this row.
}

void CellRow::AddCell(Cell *c, bool redraw) {
	LineStyle::Type lineStyle = GetViewer()->GetDefaultLineStyle();
	int lineWidth = GetViewer()->GetDefaultLineWidth();
	Point from, to;
	int w = c->GetWidth();
	int h = c->GetHeight();
	Point pos = *(c->GetTopLeft());
	if (!cells->first()) {
		// create first line.
		from.x = pos.x;
		from.y = pos.y;
		to.x = pos.x;
		to.y = pos.y + h;
		LinePiece *l = new LinePiece(GetGrafport(), &from, &to, 
				lineStyle, lineWidth);
		lines->add(l);
		if (redraw)
			l->Draw();
	}
	cells->add(c);
	from.x = pos.x + w;
	from.y = pos.y;
	to.x = pos.x + w;
	to.y = pos.y + h;
	LinePiece *l2 = new LinePiece(GetGrafport(), &from, &to,
				lineStyle, lineWidth);
	lines->add(l2);
	if (redraw)
		l2->Draw();
}
 
void CellRow::DeleteCell(Cell *c, bool redraw) {
	int pos = cells->find(c);
	if (!check(pos != -1))
		return;
	if (pos == 0) {
		// delete first cell.
		LinePiece *line = (*lines)[0];
		if (redraw)
			line->Undraw();
		lines->removei(0);
		delete line;
		if (cells->count() == 1) {  // delete last cell
			line = (*lines)[0];
			if (redraw)
				line->Undraw();
			lines->removei(0);
			if (redraw)
				UndrawLabels();
			delete line;
		}
	}
	else {
		LinePiece *line = (*lines)[pos+1];
		if (redraw)
			line->Undraw();
		lines->removei(pos+1);
		delete line;
	}
	cells->removei(pos);
	// move right cells of row left.
	UpdateWidth(pos);
}

void CellRow::InsertCell(Cell *c, unsigned pos, bool redraw) {
	if (!check(pos <= cells->count()))
		return;
	if (pos == cells->count())
		AddCell(c);
	// insert cell.
	cells->insert(c, pos);
	// create new line piece right to the cell.
	LineStyle::Type lineStyle = GetViewer()->GetDefaultLineStyle();
	unsigned lineWidth = GetViewer()->GetDefaultLineWidth();
	Point pt1 = *c->GetTopLeft();
	pt1.x += c->GetWidth();
	Point pt2 = pt1;
	pt2.y += c->GetHeight();
	LinePiece *line = new LinePiece(GetGrafport(), &pt1, &pt2, 
		lineStyle, lineWidth);
	lines->insert(line, pos+1);
	if (redraw)
		line->Draw();
	// move line pieces of row down.
	UpdateWidth(pos);
}

int CellRow::GetMinimalHeight() {
	int vh = 0;
	for (cells->first(); !cells->done(); cells->next()) {
		int th = cells->cur()->GetTextHeight() + 
			 2*GetViewer()->GetMarginHeight();
		if (vh < th)
			vh = th;
	} 
	return vh;
}

bool CellRow::ContainsPt(int x, int y) const {
	if (HitLabel(x, y))
		return True;
	if (cells->count() ==0)
		return False;
	Point pt = *(*cells)[0]->GetTopLeft();
	pt.x = max(0, pt.x - SimpleLabel::MIN_TEXT_WIDTH);
	int width = GetViewer()->GetWidth();
	Rectangle rect(pt.x, pt.y, width, height);
	return rect.Inside(x,y);
}

void CellRow::UpdateTextPositions() {
	List<Cell *> cells2 = *cells;
	for (cells2.first(); !cells2.done(); cells2.next()) {
		Cell *cell = cells2.cur();
		cell->UpdateTextPosition();
		if (GetViewer()->IsAutoResize())
			GetViewer()->RecomputeSizeCell(cell);
	}
}

void CellRow::SetTextSizes() {
	List<Cell *> cells2 = *cells;
	for (cells2.first(); !cells2.done(); cells2.next()) {
		Cell *cell = cells2.cur();
		cell->SetTextSize();
		if (GetViewer()->IsAutoResize())
			GetViewer()->RecomputeSizeCell(cell);
	}
}

void CellRow::Write(OutputFile *ofile) {
	(*ofile) << "Row " << GetNumber() << " {\n";
	(*ofile) << "\t{ Height " << height << " }\n";
	string t;
	TextAlign::Type2String(GetAlignment(), &t);
	(*ofile) << "\t{ Alignment " << t << " }\n";
	(*ofile) << "\t{ NumberOfCells " << cells->count() << " }\n";
	if (cells->first() && lines->first()) { 
		int i = 0;
		do {
			(*ofile) << "\t# cell " << GetNumber() << "," << i << '\n';
			lines->cur()->Write(ofile);
			cells->cur()->Write(ofile);
			i++;
		}
		while (cells->next() && lines->next());
		if (lines->last())
			lines->cur()->Write(ofile);
	}
	(*ofile) << "}\n\n";
}

void CellRow::WritePartial(OutputFile *ofile, int n, List<int> *columnNumbers) {
	(*ofile) << "Row " << n << " {\n";
	(*ofile) << "\t{ Height " << height << " }\n";
	string t;
	TextAlign::Type2String(GetAlignment(), &t);
	(*ofile) << "\t{ Alignment " << t << " }\n";
	(*ofile) << "\t{ NumberOfCells " << columnNumbers->count() << " }\n";
	for (columnNumbers->first(); !columnNumbers->done(); 
			columnNumbers->next()) {
		int i = columnNumbers->cur();
		(*lines)[i]->Write(ofile);
		(*cells)[i]->Write(ofile);
	}
	if (columnNumbers->last())
		(*lines)[columnNumbers->cur()+1]->Write(ofile);
	(*ofile) << "}\n\n";
}

bool CellRow::Read(InputFile *ifile, unsigned fromColumn, double format) {
	// read Row
	if (!ifile->LookupWord("Row"))
		return False;
	// read row number.
	string val;
	if (!ifile->ReadWord(&val))
		return False;
	// read {
	if (!ifile->LookupChar('{'))
		return False;
	// read and update row height (depending on whether the whole 
	// row is read in or just a part).
	if (!ifile->ReadAttribute("Height", &val))
		return False;
	if (val.toint() != height) {
		int ht = val.toint();
		if (fromColumn == 0 || ht > height)
			GetViewer()->ResizeRow(this, ht);
	}	
	// read and update row alignment (if the whole row is read in).
	if (!ifile->ReadAttribute("Alignment", &val))
		return False;
	if (fromColumn == 0) {
		if (format <= 1.08)
			SetAlignment((TextAlign::Type) val.toint());
		else
			SetAlignment(TextAlign::String2Type(&val));
	}
	// read number of cells.
	if (!ifile->ReadAttribute("NumberOfCells", &val))
		return False;
	// read and update cell texts and line types.
	int n = val.toint(); 
	for (unsigned i=fromColumn;i<fromColumn+n; i++) {
		(*lines)[i]->Read(ifile, format);
		(*cells)[i]->Read(ifile, format);
	}
	if (n > 0)
		(*lines)[fromColumn+n]->Read(ifile, format);
	// read }
	if (!ifile->LookupChar('}'))
		return False;
	return True;
}
