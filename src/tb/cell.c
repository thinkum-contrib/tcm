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
#include "cell.h"
#include "cellrow.h"
#include "linepiece.h"
#include "grafport.h"
#include "rectangle.h"
#include "inputfile.h"
#include "outputfile.h"

Cell::Cell(Grafport *g, XFont *ft, CellRow *r, CellColumn *c, 
	   int x, int y, int wd, int ht) {
	row = r; column = c;
	position.x = x; position.y = y;
	width = wd; height = ht;
	topLeft.x = x - wd/2;
	topLeft.y = y - ht/2;
	spanRows = 1;
	spanColumns = 1;
	selected = False;
	editable = True;
	visible = True;
	grafport = g;
	cellText = new CellText(g, ft, this);
	Point pt = position;
	annotation = "";
	cellText->SetPosition(&pt);
	cellText->SetUnderlined(False);
}

Cell::~Cell() {
	delete cellText;
}

int operator==(const Cell &c1, const Cell &c2) {
	return *(c1.cellText) == *(c2.cellText);
}

void Cell::Draw() {
	if (!visible)
		return;
	cellText->DrawAligned(column->GetAlignment());
	DrawSelect();
}

void Cell::Undraw() {
	if (!visible)
		return;
	cellText->UndrawAligned(column->GetAlignment());
	DrawSelect();
}

void Cell::DrawSelect() {
	const int SELECT_DIST = 2;
	if (selected) {
		grafport->SetLineWidth(1);
		grafport->SetLineStyle(LineStyle::SOLID);
		grafport->DrawRectangle(topLeft.x+SELECT_DIST, 
				topLeft.y+SELECT_DIST, 
				width-SELECT_DIST*2, height-SELECT_DIST*2);
	}
}

void Cell::SetGrafport(Grafport *g) {
	grafport = g;
	cellText->SetGrafport(g);
}

void Cell::UpdatePosition(const Point *pos) {
	if (visible)
		Undraw();
	SetPosition(pos);
	if (visible)
		Draw();
}

void Cell::UpdateSize(int wd, int ht) {
	if (visible)
		Undraw();
	SetSize(wd, ht);
	if (visible)
		Draw();
}

void Cell::UpdateFont(XFont *ft) {
	if (visible)
		Undraw();
	SetFont(ft);
	if (visible)
		Draw();
}

void Cell::UpdateSelect(bool s) {
	if (selected != s) {
		if (visible)
			Undraw();
		selected = s;
		if (visible)
			Draw();
	}
}

void Cell::UpdateTextPosition() {
	if (visible)
		Undraw();
	CalcCellTextPosition();
	if (visible)
		Draw();
}

void Cell::SetTextSize() {
	cellText->CalcSize();
	CalcCellTextPosition();
}

void Cell::SetPosition(const Point *pos) {
	position.x = pos->x;
	position.y = pos->y;
	PositiveCoord();
	topLeft.x = position.x - width/2;
	topLeft.y = position.y - height/2;
	CalcCellTextPosition();
}

void Cell::CalcCellTextPosition() {
	TextAlign::Type rowAlignment = row->GetAlignment();
	TextAlign::Type columnAlignment = column->GetAlignment();
	int marginWidth = column->GetMarginWidth();
	int marginHeight = row->GetMarginHeight();
	int textWidth = cellText->GetWidth();
	int textHeight = cellText->GetHeight();
	Point pt;
	if (columnAlignment == TextAlign::LEFT)
		pt.x = topLeft.x + marginWidth + textWidth/2;
	else if (columnAlignment == TextAlign::CENTER)
		pt.x = position.x;
	else if (columnAlignment == TextAlign::RIGHT)
		pt.x = topLeft.x + width - marginWidth - textWidth/2;
	if (rowAlignment == TextAlign::LEFT)
		pt.y = topLeft.y + marginHeight + textHeight/2;
	else if (rowAlignment == TextAlign::CENTER)
		pt.y = position.y;
	else if (rowAlignment == TextAlign::RIGHT)
		pt.y = topLeft.y + height - marginHeight - textHeight/2;
	cellText->SetPosition(&pt);
}

void Cell::SetSize(int w, int h) {
	if (w<1)
		w = 1;
	if (h<1)
		h = 1;
	width = w;
	height = h;
	PositiveCoord();
	topLeft.x = position.x - width/2;
	topLeft.y = position.y - height/2;
	CalcCellTextPosition();
}

void Cell::SetFont(XFont *ft) {
	cellText->SetFont(ft);
	CalcCellTextPosition();
}

void Cell::PositiveCoord() {
	int delta = position.x - width/2;
	if (delta < 0) {
		Point pt = position;
		pt.x += -delta;
		SetPosition(&pt);
	}
	delta = position.y - height/2; 
	if (delta < 0) {
		Point pt = position;
		pt.y += -delta;
		SetPosition(&pt);
	}
}

bool Cell::ContainsPt(int x, int y) const {
	Rectangle rect(topLeft.x, topLeft.y, width, height);
	return rect.Inside(x, y);
}

void Cell::UpdateText(const string *s) {
	if (editable) {
		Undraw();
		cellText->SetText(s);
		CalcCellTextPosition();
		Draw();
	}
}

void Cell::ClearText() {
	string empty("");
	UpdateText(&empty);
}

bool Cell::HasText(const string *s, bool sens, bool sub) {
	string t1 = *s;
	string t2 = *cellText->GetText();
	if (!sens) {
		// make them the same case.
		t1.downcase();
		t2.downcase();
	}
	if (sub)
		return (t2.contains(t1));
	else
		return (t1 == t2);
}

void Cell::Write(OutputFile *ofile) {
	cellText->Write(ofile);
	(*ofile) << "\t{ Annotation " << '"' << annotation << '"' << " }\n";
}
 
bool Cell::Read(InputFile *ifile, double format) {
	visible = False; // avoid multiple redraws.
	if (!cellText->Read(ifile, format))
		return False;
	CalcCellTextPosition();
	if (format >= 1.22) {
		if (!ifile->ReadStringAttribute("Annotation", &annotation))
			return False;
	}
	return True;
}

void Cell::SetXLFD(const char *descr) {
	XFont *ft = row->GetViewer()->GetFont(descr);
	cellText->UpdateFont(ft);
}
