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
#include "grafport.h"
#include "inputfile.h"
#include "outputfile.h"
#include "linepiece.h"
#include <stdlib.h>

LinePiece::LinePiece(Grafport *g, Point *from, Point *to, 
			LineStyle::Type t, unsigned n) {
	lineStyle = t;
	lineWidth = n;
	beginP = *from;
	endP = *to;
	grafport = g;
	visible = True;
}

void LinePiece::Draw() {
	if (!visible)
		return;
	grafport->SetLineWidth(lineWidth);
	grafport->SetLineStyle(lineStyle);
	grafport->DrawLine(beginP.x, beginP.y, endP.x, endP.y);
}

void LinePiece::Undraw() {
	Draw();
}

void LinePiece::UpdateLineStyle(LineStyle::Type t) {
	if (visible)
		Undraw();
	lineStyle = t;
	if (visible)
		Draw();
}

void LinePiece::UpdateLineWidth(unsigned n) {
	if (visible)
		Undraw();
	lineWidth = n;
	if (visible)
		Draw();
}

bool LinePiece::HitLine(int x, int y) {
	// should be like containptline in Line::
	return (beginP.x <= x && x <= endP.x && beginP.y <= y && y <= endP.y);
}

void LinePiece::UpdatePoints(const Point *p1, const Point *p2) {
	if (visible)
		Undraw();
	SetPoints(p1, p2);
	if (visible)
		Draw();
}

void LinePiece::UpdateBegin(const Point *p) {
	if (visible)
		Undraw();
	SetBegin(p);
	if (visible)
		Draw();
}

void LinePiece::UpdateEnd(const Point *p) {
	if (visible)
		Undraw();
	SetEnd(p);
	if (visible)
		Draw();
}

void LinePiece::Write(OutputFile *ofile) {
	string nm;
	LineStyle::Type2String(lineStyle, &nm);
	(*ofile) << "\t{ LineStyle " << nm << " }\n";
	(*ofile) << "\t{ LineWidth " << lineWidth << " }\n";
}

bool LinePiece::Read(InputFile *ifile, double format) {
	visible = False; // avoid multiple redraws
	string val;
	if (format <= 1.08) {
		if (!ifile->ReadAttribute("LineType", &val))
			return False;
		if (val.toint() != lineStyle)
			lineStyle = (LineStyle::Type)val.toint();
	}
	else {
		if (!ifile->ReadAttribute("LineStyle", &val))
			return False;
		lineStyle = LineStyle::String2Type(&val);
		// Fat is old stuff.
		if (val %= "Fat")
			lineWidth = 3;
		if (format >= 1.22) {
			if (!ifile->ReadAttribute("LineWidth", &val))
				return False;
			lineWidth = val.toint();
		}
	}
	return True;
}
