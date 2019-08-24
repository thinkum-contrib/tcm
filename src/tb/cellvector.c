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
#include "cellvector.h"
#include "tableviewer.h"
#include "rowcolumnlabel.h"
#include "cell.h"
#include "linepiece.h"

CellVector::CellVector(TableViewer *v, unsigned n) {
	viewer = v;
	number = n;
	labelsVisible = True;
	cells = new List<Cell *>;
	lines = new List<LinePiece *>;
	grafport = viewer->GetGrafport();
	label1 = new RowColumnLabel(grafport, this);
	label2 = new RowColumnLabel(grafport, this);
	string s = n;
	label1->SetText(&s);
	label2->SetText(&s);
}

CellVector::~CellVector() {
	lines->clear();
	cells->clear();
	delete lines;
	delete cells;
	delete label1;
	delete label2;
}

int operator==(const CellVector &r1, const CellVector &r2) {
	if (r1.number == r2.number)
		return 0;
	else if (r1.number < r2.number)
		return -1;
	else
		return 1;
}

void CellVector::Draw() {
	DrawLabels();
	DrawLines();
	DrawCells();
}

void CellVector::DrawCells() {
	// draw cells (text+selection)
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->Draw();
}

void CellVector::DrawLines() {
	// draw all lines
	for (lines->first(); !lines->done(); lines->next())
		lines->cur()->Draw();
}

void CellVector::SetVisible(bool b) {
	labelsVisible = b;
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->SetVisible(b);
	for (lines->first(); !lines->done(); lines->next())
		lines->cur()->SetVisible(b);
}

void CellVector::DrawLabels() {
	if (labelsVisible) {
		label1->Draw();
		label2->Draw();
	}
}

void CellVector::Undraw() {
	UndrawLabels();
	UndrawLines();
	UndrawCells();
}

void CellVector::UndrawCells() {
	// undraw cells (text+selection)
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->Undraw();
}

void CellVector::UndrawLines() {
	// undraw all lines
	for (lines->first(); !lines->done(); lines->next())
		lines->cur()->Undraw();
}

void CellVector::UndrawLabels() {
	if (labelsVisible) {
		label1->Undraw();
		label2->Undraw();
	}
}

void CellVector::UpdateNumber(unsigned nr) {
	UndrawLabels();
	SetNumber(nr); 
	DrawLabels();
}

void CellVector::UpdateLabel1(const string *txt) {
	label1->UpdateText(txt);
}

void CellVector::UpdateLabel2(const string *txt) {
	label2->UpdateText(txt);
}

void CellVector::SetAlignment(TextAlign::Type a) {
	alignment = a;
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->CalcCellTextPosition();
}
 
void CellVector::UpdateAlignment(TextAlign::Type a) {
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		cell->Undraw();
	}
	SetAlignment(a);
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		cell->Draw();
	} 
}

void CellVector::SetNumber(unsigned nr) {
	number = nr;
	string s = nr;
	label1->SetText(&s);
	label2->SetText(&s);
}

void CellVector::SetGrafport(Grafport *g) {
	label1->SetGrafport(g);
	label2->SetGrafport(g);
	for (lines->first(); !lines->done(); lines->next())
		lines->cur()->SetGrafport(g);
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->SetGrafport(g);
}

RowColumnLabel *CellVector::HitLabel(int x, int y) const {
	if (!labelsVisible)
		return 0;
	else if (label1->HitText(x,y))
		return label1;
	else if (label2->HitText(x,y))
		return label2;
	else
		return 0;
}

Cell *CellVector::FirstCell() {
	if (cells->first())
		return cells->cur();
	else
		return 0;
}

Cell *CellVector::NextCell() {
	if (cells->next())
		return cells->cur();
	else
		return 0;
}

Cell *CellVector::NthCell(unsigned n) {
	if (n < cells->count())
		return (*cells)[n];
	else
		return 0;
}

LinePiece *CellVector::FirstLine() {
	if (lines->first())
		return lines->cur();
	else
		return 0;
}

LinePiece *CellVector::NextLine() {
	if (lines->next())
		return lines->cur();
	else
		return 0;
}

LinePiece *CellVector::NthLine(unsigned n) {
	if (n < lines->count())
		return (*lines)[n];
	else
		return 0;
}

unsigned CellVector::HasEmptyText() {
	string empty("");
	return HasText(&empty);
}

unsigned CellVector::HasText(const string *s) {
	unsigned total = 0;
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		if (cell->HasText(s))
			total++;
	}
	return total;
}

bool CellVector::HasCell(Cell *c) {
	return (cells->find(c) != -1);
}
