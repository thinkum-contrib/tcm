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
#include "celltextbuffer.h"
#include "tableviewer.h"
#include "celltext.h"
#include "cell.h"

CellTextBuffer::CellTextBuffer() {
	cellTexts = 0;
	prevCellTexts = 0;
	rcPositions = new List<Point *>;
	prevRcPositions = new List<Point *>;
}

CellTextBuffer::~CellTextBuffer() {
	if (cellTexts) {
		cellTexts->clear();
		delete cellTexts;
	}
	if (prevCellTexts) {
		prevCellTexts->clear();
		delete prevCellTexts;
	}
	rcPositions->clear();
	prevRcPositions->clear();
	delete rcPositions;
	delete prevRcPositions;
}

void CellTextBuffer::PutTexts(List<CellText *> *c) {
	if (prevCellTexts) {
		prevCellTexts->clear();
		delete prevCellTexts;
	}
	prevCellTexts = cellTexts;
	cellTexts = new List<CellText *>;
	// make a copy.
	for (c->first(); !c->done(); c->next()) {
		CellText *t1 = c->cur();
		CellText *t2 = new CellText(*t1);
		cellTexts->add(t2);
	}
	CalcSizeBuffer();
}

void CellTextBuffer::PutPositions(List<Point *> *p) {
	prevRcPositions->clear();
	*prevRcPositions = *rcPositions;
	rcPositions->empty();
	if (p->first())
		rcTopLeft = *p->cur();
	else
		rcTopLeft = Point(0,0);
	for (p->first(); !p->done(); p->next()) {
		rcPositions->add(new Point(*p->cur()));
		rcTopLeft = Point(min(rcTopLeft.x,p->cur()->x),
				  min(rcTopLeft.y,p->cur()->y));
	}
}

List<CellText *> *CellTextBuffer::GetTexts() {
	if (cellTexts) { // make a copy.
		List<CellText *> *copy = new List<CellText *>;
		for (cellTexts->first(); !cellTexts->done(); 
		     cellTexts->next()) {
			CellText *t = new CellText(*cellTexts->cur());
			copy->add(t);
		}
		return copy;
	}
	else
		return 0;
}

void CellTextBuffer::UndoPut() {
	if (cellTexts) {
		cellTexts->clear();
		delete cellTexts;
	}
	cellTexts = prevCellTexts;
	if (cellTexts)
		CalcSizeBuffer();
	prevCellTexts = 0;
	rcPositions->clear();
	*rcPositions = *prevRcPositions;
	prevRcPositions->empty();
}

bool CellTextBuffer::IsEmpty() {
	return (cellTexts == 0 || cellTexts->count() == 0);
}

 
void CellTextBuffer::CalcSizeBuffer() {
	int x_max=-1, x_min=-1, y_max=-1, y_min=-1;
	int x, y;
	List<CellText *> *texts = cellTexts;
	if (!check(texts))
		return;
	for (texts->first(); !texts->done(); texts->next()) {
		CellText *celltext = texts->cur();
		if (!check(celltext))
			break;
		Point pt = *celltext->GetTopLeft();
		int wd = celltext->GetWidth();
		int ht = celltext->GetHeight();
		x = pt.x + wd + 3;
		if (x>x_max || x_max == -1)
			x_max = x;
		x = pt.x - 3;
		if (x<x_min || x_min == -1)
			x_min = x;
		y = pt.y + ht + 3;
		if (y>y_max || y_max == -1)
			y_max = y;
		y = pt.y - 3;
		if (y<y_min || y_min == -1)
			y_min = y;
	}
	topLeft.Set(x_min, y_min);
	bottomRight.Set(x_max, y_max);
}
