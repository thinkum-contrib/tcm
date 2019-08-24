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
#include "table.h"
#include "cell.h"
#include "celltext.h"
#include "cellrow.h"
#include "celltextbuffer.h"
#include "grafport.h"
#include "pastecelltextscmd.h"

const int PasteCellTextsCmd::MIN_BOX_SIZE = 10;

PasteCellTextsCmd::PasteCellTextsCmd(Table *t, TableViewer *v): Command(t, v) {
	tviewer = v;
	buffer = v->GetBuffer();
	pastedCells = new List<Cell *>;
	oldStrings = new List<string *>;
	cellTexts = 0;
	if (buffer->IsEmpty()) {
		GetMainWindow()->SetStatus("aborted: empty paste buffer");
		return;
	}
	cellTexts = buffer->GetTexts();
	MakeBox();
}

PasteCellTextsCmd::~PasteCellTextsCmd() {
	if (cellTexts)
		cellTexts->clear();
	oldStrings->clear();
	delete pastedCells;
	delete cellTexts;
	delete oldStrings;
}

void PasteCellTextsCmd::MakeBox() {
	Point bottomRight;
	topLeft = buffer->GetTopLeft();
	bottomRight = buffer->GetBottomRight();
	width = bottomRight.x - topLeft.x;
	width = max(width, MIN_BOX_SIZE);
	height = bottomRight.y - topLeft.y;
	height = max(height, MIN_BOX_SIZE);
	tviewer->SetPasting(True);
	Point pt = Scale(&topLeft);
	// Start mouse operation
	TrackMouse(TRACK_PRESS, &pt, &pt, &pt);
}

void PasteCellTextsCmd::Execute() {
	Point p = topLeft + delta;
	Cell *topLeftCell = tviewer->HitCell(p.x, p.y);
	if (!topLeftCell) {
		GetMainWindow()->SetStatus(
			"aborted: topleft of the box is out of the table");
		Command::Abort();
		return;
	}
	Point tl1 = Point(topLeftCell->GetRow()->GetNumber(), 
			  topLeftCell->GetColumn()->GetNumber());
	List<Point *> *rcPositions = buffer->GetPositions();
	for (unsigned i=0; i<cellTexts->count(); i++) {
		CellRow *row;
		Cell *cell;
		CellText *t = (*cellTexts)[i];
		Point pt = *(*rcPositions)[i];
		pt = pt - buffer->GetRcTopLeft();
		pt = pt + tl1;
		if ((row = tviewer->GiveRow(pt.x))) {
			if ((cell = row->NthCell(pt.y))) {
				string oldText = *cell->GetText();
				pastedCells->add(cell);
				oldStrings->add(new string (oldText));
				// also Check texts.
				if (!((Table *)GetDocument())->UpdateText(
						cell, t->GetText())) {
					cell->UpdateText(&oldText);
					GetMainWindow()->SetStatus(
						"aborted: cannot paste text "
					    	"in this cell");
					return;
				}
				if (tviewer->IsAutoResize())
					tviewer->RecomputeSizeCell(cell);
			}
		}
	} 
	Command::Execute();
	GetMainWindow()->FitDocument();
}

void PasteCellTextsCmd::UnExecute() {
	if (pastedCells->first() && oldStrings->first()) {
		do {
			pastedCells->cur()->UpdateText(oldStrings->cur());
			if (tviewer->IsAutoResize())
				tviewer->RecomputeSizeCell(pastedCells->cur());
		} while (pastedCells->next() && oldStrings->next());
	}
	Command::UnExecute();
}

void PasteCellTextsCmd::Abort() {
	DrawOutLine(&delta);
	tviewer->SetPasting(False);
	Command::Abort();
}

void PasteCellTextsCmd::TrackMouse(TrackType aPhase, Point *anchorPoint,
	Point*, Point *nextPoint) {
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetCursor(MouseCursor::FLEUR);
			// draw
			delta = *nextPoint - *anchorPoint;
			DrawOutLine(&delta);
			// save
			anchor = *anchorPoint;
			break;
		case TRACK_DRAG:
			// erase
			DrawOutLine(&delta);
			// draw
			delta = *nextPoint - anchor;
			DrawOutLine(&delta);
			break;
		case TRACK_UP:
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			// erase
			DrawOutLine(&delta);
			delta = ScaleCorrect(&delta);
			MoveCellTexts(&delta);
			tviewer->SetPasting(False);
			tviewer->ExecuteCommand();
			break;
		default:
			error("unknown track type\n");
			break;
	}
}

void PasteCellTextsCmd::MoveCellTexts(const Point *d) {
	for (cellTexts->first(); !cellTexts->done(); cellTexts->next()) {
		CellText *t = cellTexts->cur();
		Point newPos = *t->GetPosition() + *d;
		t->SetPosition(&newPos);
	}
}
 
void PasteCellTextsCmd::DrawOutLine(const Point *d) {
	Point p1 = topLeft;
	Point p2 = ScaleCorrect(d);
	Point pt = p1 + p2;
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
	GetGrafport()->DrawRectangle(pt.x, pt.y, width, height);
}
