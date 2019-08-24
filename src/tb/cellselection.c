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
#include "cellselection.h"
#include "cell.h"

CellSelection::CellSelection() {
	cells = new List<Cell *>;
}

CellSelection::~CellSelection() {
	delete cells;
}

void CellSelection::Draw() {
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->Draw();
}

void CellSelection::Undraw() {
	for (cells->first(); !cells->done(); cells->next())
		cells->cur()->Undraw();
}

void CellSelection::SelectCell(Cell *c) {
	if (!c->IsSelected()) {
		cells->add(c);
		c->UpdateSelect(True);
	}
}

void CellSelection::SelectCells(List<Cell *> *c) {
	for (c->first(); !c->done(); c->next()) {
		Cell *cell = c->cur();
		if (!cell->IsSelected()){
			cells->add(cell);
			cell->UpdateSelect(True);
		}
	}
}

void CellSelection::DeselectCell(Cell *c) {
	cells->remove(c);
	c->UpdateSelect(False);
}

void CellSelection::DeselectCells(List<Cell *> *c) {
	for (c->first(); !c->done(); c->next()) {
		Cell *cell = c->cur();
		cells->remove(cell);
		cell->UpdateSelect(False);
	} 
}

void CellSelection::DeselectAll() {
	for (cells->first(); !cells->done(); cells->next()) {
		Cell *cell = cells->cur();
		cell->UpdateSelect(False);
	} 
	cells->empty();
}

Cell *CellSelection::FirstSelected() {
	if (cells->first())
		return cells->cur();
	else
		return 0;
}

Cell *CellSelection::NextSelected() {
	if (cells->next())
		return cells->cur();
	else
		return 0;
}
