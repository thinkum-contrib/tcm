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
#include "cellcolumn.h"
#include "rowcolumnlabel.h"
#include "cell.h"
#include "linepiece.h"
#include "rectangle.h"
#include "inputfile.h"
#include "outputfile.h"
#include <stdlib.h>

CellColumn::CellColumn(TableViewer *v, unsigned n, int w): CellVector(v,n) {
	width = w;
	SetAlignment(v->GetDefaultColumnAlignment());
	CalcLabelPositions();
}

void CellColumn::CalcLabelPositions() {
	Point pt;
	RowColumnLabel *l1 = GetLabel1();
        RowColumnLabel *l2 = GetLabel2();
        if (l1 && l2) {
		if (cells->count() == 0)
			pt = GetViewer()->GetColumnTopLeft(GetNumber());
		else
			pt = *(*cells)[0]->GetTopLeft();
		pt.x += width/2;
		pt.y -= (l1->GetHeight()/2);
		if (GetViewer()->IsShowRowColumnLabels())
			l1->UpdatePosition(&pt);
		else
			l1->SetPosition(&pt);
		pt.y += GetViewer()->GetHeight() + l1->GetHeight();
		if (GetViewer()->IsShowRowColumnLabels())
			l2->UpdatePosition(&pt);
		else
			l2->SetPosition(&pt);
	}
}

void CellColumn::UpdateWidth(int w) {
	if (w == width)
		return;
	for (lines->first(); !lines->done(); lines->next()) {
		LinePiece *line = lines->cur();
		Point pt = *line->GetEnd();
		pt.x = pt.x - width + w;
		line->UpdateEnd(&pt);
	} 
	width = w;
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		int height = cell->GetHeight();
		Point pt = *cell->GetTopLeft();
		pt.x = pt.x + width/2;
		pt.y = pt.y + height/2;
		cell->Undraw();
		cell->SetSize(width, height);
		cell->SetPosition(&pt);
		cell->Draw();
	}
	CalcLabelPositions();
}

void CellColumn::UpdatePosition(int delta) {
	if (delta == 0)
		return;
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		Point pt = *cell->GetPosition();
		pt.x += delta;
		cell->UpdatePosition(&pt);
	} 
	for (lines->first(); !lines->done(); lines->next()) {
		LinePiece *line = lines->cur();
		Point pt1 = *line->GetBegin();
		if (pt1.x + delta >= 0) {
			pt1.x += delta;
			Point pt2 = *line->GetEnd();
			pt2.x += delta;
			line->UpdatePoints(&pt1, &pt2);
		}
	}
	CalcLabelPositions();
}

void CellColumn::UpdateHeight(unsigned rownr) {
	Point p1, p2, p3;
	Cell *cell;
	LinePiece *line;
	int height;
	if (rownr == 0 && cells->count() > 0) { // shift first line.
		cell = (*cells)[0];
		line = (*lines)[0];
		p1 = *cell->GetTopLeft();
		p2.y = p1.y;
		p2.x = p1.x + width;
		line->UpdatePoints(&p1, &p2);
		CalcLabelPositions();
	}
	for (unsigned i=rownr; i<cells->count(); i++) {
		cell = (*cells)[i];
		line = (*lines)[i+1];
		height = cell->GetHeight();
		p1 = *cell->GetTopLeft();
		if (line) {
			p2 = *line->GetBegin();
			p2.y = p1.y + height;
			p3 = *line->GetEnd();
			p3.y = p1.y + height;
			p3.x = p1.x + width;
			line->UpdatePoints(&p2, &p3);
		}
	}
}

void CellColumn::AddCell(Cell *c, bool redraw) {
	LineStyle::Type lineStyle = GetViewer()->GetDefaultLineStyle();
	unsigned lineWidth = GetViewer()->GetDefaultLineWidth();
	Point from, to;
	int w = c->GetWidth();
	int h = c->GetHeight();
	Point pos = *(c->GetTopLeft());
	if (!cells->first()) {
		// create first line.
		from.x = pos.x;
		from.y = pos.y;
		to.x = pos.x + w;
		to.y = pos.y;
		LinePiece *l = new LinePiece(GetGrafport(), &from, &to, 
			lineStyle, lineWidth);
		if (redraw)
			l->Draw();
		lines->add(l);
	}
	cells->add(c);
	from.x = pos.x;
	from.y = pos.y + h;
	to.x = pos.x + w;
	to.y = pos.y + h;
	LinePiece *l = new LinePiece(GetGrafport(), &from, &to,
			lineStyle, lineWidth);
	if (redraw)
		l->Draw();
	lines->add(l);
}

void CellColumn::DeleteCell(Cell *c, bool redraw) {
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
		if (cells->count() == 1) { // delete very last cell
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
	// move lower cells of column up.
	UpdateHeight(pos); 
}

void CellColumn::InsertCell(Cell *c, unsigned pos, bool redraw) {
	if (!check(pos <= cells->count()))
		return;
	if (pos == cells->count())
		AddCell(c);
	// insert cell.
	cells->insert(c, pos);
	// create new line piece below cell.
	LineStyle::Type lineStyle = GetViewer()->GetDefaultLineStyle();
	unsigned lineWidth = GetViewer()->GetDefaultLineWidth();
	Point pt1 = *c->GetTopLeft();
	pt1.y += c->GetHeight();
	Point pt2 = pt1;
	pt2.x += c->GetWidth();
	LinePiece *line = new LinePiece(GetGrafport(), &pt1, &pt2, 
		lineStyle, lineWidth);
	lines->insert(line, pos+1);
	if (redraw)
		line->Draw();
	// move lower line pieces of column lright.
	UpdateHeight(pos); 
}

LinePiece *CellColumn::HitLinePiece(int x, int y) {
	if (!lines->first())
		return 0;
	LinePiece *line = lines->cur();
	Point pt = *(line->GetBegin());
	// look for this column.
	if (x > pt.x && x < pt.x + width) {
		do {
			line = lines->cur();
			pt = *line->GetBegin();
			if (y > pt.y-3 && y < pt.y+3)
				return line;
		} while (lines->next());
	}
	return 0; // not in this column.
}

int CellColumn::GetMinimalWidth() {
	int vw = 0;
	for (cells->first(); !cells->done(); cells->next()) {
		int tw = cells->cur()->GetTextWidth() + 
			 2*GetViewer()->GetMarginWidth(); 
		if (vw < tw) 
			vw = tw;
	} 
	return vw;
}

void CellColumn::UpdateTextPositions() {
	List<Cell *> cells2 = *cells;
	for (cells2.first(); !cells2.done(); cells2.next()) {
		Cell *cell = cells2.cur();
		cell->UpdateTextPosition();
		if (GetViewer()->IsAutoResize())
			GetViewer()->RecomputeSizeCell(cell);
	} 
}

bool CellColumn::ContainsPt(int x, int y) const {
	if (cells->count()==0)
		return False;
	Point pt = *(*cells)[0]->GetTopLeft();
	pt.y = max(0, pt.y - SimpleLabel::MIN_TEXT_HEIGHT);
	int height = GetViewer()->GetHeight();
	Rectangle rect(pt.x, pt.y, width, height);
	return rect.Inside(x,y);
}

void CellColumn::Write(OutputFile *ofile) {
	(*ofile) << "Column " << GetNumber() << " {\n";
	(*ofile) << "\t{ Width " << width << " }\n";
	string t;
	TextAlign::Type2String(GetAlignment(), &t);
	(*ofile) << "\t{ Alignment " << t << " }\n";
	(*ofile) << "\t{ NumberOfCells " << cells->count() << " }\n";
	int i=0;
	for (lines->first(); !lines->done(); lines->next()) {
		(*ofile) << "\t# cell " << i << "," << GetNumber() << '\n';
		lines->cur()->Write(ofile);
		i++;
	}
	(*ofile) << "}\n\n";
}

void CellColumn::WritePartial(OutputFile *ofile, int n, List<int> *rowNumbers) {
	(*ofile) << "Column " << n << " {\n";
	(*ofile) << "\t{ Width " << width << " }\n";
	string t;
	TextAlign::Type2String(GetAlignment(), &t);
	(*ofile) << "\t{ Alignment " << t << " }\n";
	(*ofile) << "\t{ NumberOfCells " << rowNumbers->count() << " }\n";
	for (rowNumbers->first(); !rowNumbers->done(); rowNumbers->next())
		(*lines)[rowNumbers->cur()]->Write(ofile);
	if (rowNumbers->last())
		(*lines)[rowNumbers->cur()]->Write(ofile);
	(*ofile) << "}\n\n";
}

bool CellColumn::Read(InputFile *ifile, unsigned fromRow, double format) {
	// read Column
	if (!ifile->LookupWord("Column"))
		return False;
	// read column number.
	string val;
	if (!ifile->ReadWord(&val))
		return False;
	// read {
	if (!ifile->LookupChar('{'))
		return False;
	// read and update column width (depending on whether the whole column
	// is read in or just a part).
	if (!ifile->ReadAttribute("Width", &val))
		return False;
	if (val.toint() != width) {
		int wd = val.toint();
		if (fromRow == 0 || wd > width) 
			GetViewer()->ResizeColumn(this, wd);
	}
	// read and update column alignment, if whole column is read in.
	if (!ifile->ReadAttribute("Alignment", &val))
		return False;
	if (fromRow == 0) {
		if (format <= 1.08)
			SetAlignment((TextAlign::Type) val.toint());
		else
			SetAlignment(TextAlign::String2Type(&val));
	}
	// read number of cells.
	if (!ifile->ReadAttribute("NumberOfCells", &val))
		return False;
	// read and update line types.
	int n = val.toint();
	for (unsigned i=fromRow; i<fromRow+n; i++)
		(*lines)[i]->Read(ifile, format);
	if (n > 0)
		(*lines)[fromRow+n]->Read(ifile, format);
	// read }
	if (!ifile->LookupChar('}'))
		return False;
	return True;
}
