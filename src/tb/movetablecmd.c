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
#include "movetablecmd.h"

#define max(a,b) ((a)>(b)?(a):(b))

const int MoveTableCmd::MOVE_DISTANCE = 10;

MoveTableCmd::MoveTableCmd(Table *t, TableViewer *v, Document::MoveType m):
			Command(t,v) {
	moveType = m;
	oldPosition = *((TableViewer *)GetViewer())->GetTopLeft();
}

void MoveTableCmd::Execute() {
	Point pt;
	if (moveType==Document::UP)
		pt = Point(0, -MOVE_DISTANCE);
	else if (moveType==Document::DOWN)
		pt = Point(0, MOVE_DISTANCE);
	else if (moveType==Document::LEFT)
		pt = Point(-MOVE_DISTANCE, 0);
	else if (moveType==Document::RIGHT)
		pt = Point(MOVE_DISTANCE, 0);
	else if (moveType==Document::CENTER) {
		Point oldCenter, newCenter;
		Point tl, br;
		double elWidth, elHeight;
		double w, h;
		GetViewer()->GetPageSize(w, h);
		// center of the table.
		GetViewer()->CalcSizeElements(tl, br);
		elWidth = Scale(br.x - tl.x);
		elHeight = Scale(br.y - tl.y);
		tl = Scale(&tl); br = Scale(&br);
		oldCenter.x = (br.x + tl.x)/2;
		oldCenter.y = (br.y + tl.y)/2;
		// fit it to the first page.
		newCenter.x = int(0.5 + max(w, elWidth) * 0.5);
		newCenter.y = int(0.5 + max(h, elHeight) * 0.5);
		// distance to move to new center point.
		pt = newCenter - oldCenter;
	}
	pt = ScaleCorrect(&pt);
	((TableViewer *)GetViewer())->Move(&pt);
	GetMainWindow()->FitDocument();
	Command::Execute();
	if (moveType==Document::UP)
		GetMainWindow()->SetStatus("commited: move table up"); 
	else if (moveType==Document::DOWN)
		GetMainWindow()->SetStatus("commited: move table down"); 
	else if (moveType==Document::LEFT)
		GetMainWindow()->SetStatus("commited: move table left"); 
	else if (moveType==Document::RIGHT)
		GetMainWindow()->SetStatus("commited: move table right"); 
	else if (moveType==Document::CENTER)
		GetMainWindow()->SetStatus("commited: move table center"); 
}

void MoveTableCmd::UnExecute() {
	Point pt = *((TableViewer *)GetViewer())->GetTopLeft();
	pt = oldPosition - pt;
	((TableViewer *)GetViewer())->Move(&pt);
	Command::UnExecute();
}
