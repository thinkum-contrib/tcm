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
#include "matrixviewer.h"
#include "linepiece.h"
#include "cellcolumn.h"
#include "cellrow.h"
#include "cell.h"

MatrixViewer::MatrixViewer(Config *c, TableWindow *t): TableViewer(c, t) { }

void MatrixViewer::Initialize() {
	TableViewer::Initialize();
	List<CellColumn *> *c = GetColumns();
	for (c->first(); !c->done(); c->next())
		SetNthLine(c->cur(), 1, LineStyle::DUAL);
	List<CellRow *> *r = GetRows();
	for (r->first(); !r->done(); r->next())
		SetNthLine(r->cur(), 1, LineStyle::DUAL);
}

void MatrixViewer::AddRow(CellRow *c) {
	TableViewer::AddRow(c);
	SetNthLine(c, 1, LineStyle::DUAL);
}   

void MatrixViewer::AddColumn(CellColumn *c) {
	TableViewer::AddColumn(c);
	SetNthLine(c, 1, LineStyle::DUAL);
}  

void MatrixViewer::InsertRow(CellRow *c) {
	TableViewer::InsertRow(c);
	SetNthLine(c, 1, LineStyle::DUAL);
}    

void MatrixViewer::InsertColumn(CellColumn *c) {
	TableViewer::InsertColumn(c);
	SetNthLine(c, 1, LineStyle::DUAL);
}

void MatrixViewer::SetNthLine(CellVector *v, int n, LineStyle::Type t) {
	LinePiece *line = v->NthLine(n);
	if (line)
		line->UpdateLineStyle(t);
}
