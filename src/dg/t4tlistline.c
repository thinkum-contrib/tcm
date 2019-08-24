////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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

#include "subject.h"
#include "inputfile.h"
#include "outputfile.h"
#include "t4tlistline.h"
#include <stdlib.h>
#include <math.h>
#include "grafport.h"
#include "diagramviewer.h"
#include "shapeview.h"
#include "shape.h"
#include <limits.h>

T4TListLine::T4TListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
			T4Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
}

T4TListLine::T4TListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): T4Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

T4TListLine::T4TListLine(const T4TListLine &aline): T4Line(aline) {
}

void T4TListLine::InitTextShapes() {
	tlist = new List<TextShape *>;
}

T4TListLine::~T4TListLine() {
	delete tlist;
}

void T4TListLine::DrawTextShapes() {
	T4Line::DrawTextShapes();
}


void T4TListLine::DrawShape() {
	T4Line::DrawShape();
}

void T4TListLine::CalcPositionTextShapes() {
	T4Line::CalcPositionTextShapes();
	CalcPositionTextShapeList();
}

void T4TListLine::UpdateTListTextShape(const string *s, unsigned n) {
	if (IsVisible())
		Undraw();
	tlist->elem(n)->SetString(s);
	if (IsVisible())
		Draw();
}

void T4TListLine::SetSelect(bool s) {
	T4Line::SetSelect(s);
}

bool T4TListLine::InTextArea(int x, int y) {
	if (T4Line::InTextArea(x, y))
		return True;
	else 
		for (tlist->first(); !tlist->done(); tlist->next())
			if (tlist->cur()->InTextArea(x, y))
				return True;
	return False;
}

TextShape *T4TListLine::HitTextShape(int x, int y) {
	TextShape *textShape = T4Line::HitTextShape(x, y);
	if (textShape)
		return textShape;
	else
		for (tlist->first(); !tlist->done(); tlist->next()) {
			if (tlist->cur()->ContainsPt(x, y))
				return tlist->cur();
		}
	return 0;
}

TextShape *T4TListLine::ChooseTextShape(int x, int y) {
	return T4Line::ChooseTextShape(x, y);
}

bool T4TListLine::HasTextShape(TextShape *t) const {
	if (T4Line::HasTextShape(t))
		return True;
	for (tlist->first(); !tlist->done(); tlist->next())
		if (tlist->cur() == t)
			return True;
	return False;
}

int T4TListLine::GetLeftMost() const {
	int e = T4Line::GetLeftMost();
	for (tlist->first(); !tlist->done(); tlist->next()) {
		e = min(e, tlist->cur()->GetLeftMost());
	}
	return e;
}

int T4TListLine::GetTopMost() const {
	int e = T4Line::GetTopMost();
	for (tlist->first(); !tlist->done(); tlist->next()) {
		e = min(e, tlist->cur()->GetTopMost());
	}
	return e;
}

int T4TListLine::GetRightMost() const {
	int e = T4Line::GetRightMost();
	for (tlist->first(); !tlist->done(); tlist->next()) {
		e = max(e, tlist->cur()->GetRightMost());
	}
	return e;
}

int T4TListLine::GetBottomMost() const {
	int e = T4Line::GetBottomMost();
	for (tlist->first(); !tlist->done(); tlist->next()) {
		e = max(e, tlist->cur()->GetBottomMost());
	}
	return e;
}



void T4TListLine::WriteMembers(OutputFile *ofile) {
	T4Line::WriteMembers(ofile);

	string s;
	ReadDirection::Type2String(GetNameDirection(), &s);
	(*ofile) << "\t{ NameDirection " << s << " }\n";

	(*ofile) << "\t{ Messages " << tlist->count() <<" }\n";

	// Write message positions
	for (tlist->first(); !tlist->done(); tlist->next()) {
		(*ofile) << "\t{ TnPosition " << *(tlist->cur()->GetPosition()) << " }\n";

	}


}

bool T4TListLine::ReadMembers(InputFile *ifile, double format) {
	string val1, val2;
	if (!T4Line::ReadMembers(ifile, format))
		return False;
	return True;
}

void T4TListLine::SetTextShape() {
	T4Line::SetTextShape();
	tlist->clear();
}


void T4TListLine::SetFont(XFont *ft) {
	T4Line::SetFont(ft);
}

void T4TListLine::SetTextColor(const string *c) {
	T4Line::SetTextColor(c);
}

void T4TListLine::SetAlignment(TextAlign::Type al) {
	T4Line::SetAlignment(al);
	for (tlist->first(); !tlist->done(); tlist->next())
		tlist->cur()->SetAlignment(al);
}

void T4TListLine::SetGrafport(Grafport *g) {
	T4Line::SetGrafport(g);
	for (tlist->first(); !tlist->done(); tlist->next())
		tlist->cur()->SetGrafport(g);
}

void T4TListLine::SetView(ShapeView *v) {
	T4Line::SetView(v);
	for (tlist->first(); !tlist->done(); tlist->next())
		tlist->cur()->SetView(v);
}

bool T4TListLine::HasString(const string *s, bool sens, bool sub) const {
	if (T4Line::HasString(s, sens, sub))
		return True;
	else
		return False;
}

bool T4TListLine::HasString(const string *s, bool sens, bool sub, 
			List<TextShape *> *list) {
	bool b = T4Line::HasString(s, sens, sub, list);
	return b;
}

void T4TListLine::MoveRaw(const Point *delta) {
	T4Line::MoveRaw(delta);
}

void T4TListLine::CalcPositionTextShapeList() {
	Point *from, *to, *save;
	save = from = to = (*GetLine())[0];
	for (unsigned i = 1; i<=GetLineNumber(); i++) {
		from = save;
		to = (*GetLine())[i];
		save = to;
	}
	Point pos = *GetPosition();
	int wd = to->x - from->x;
	int ht = to->y - from->y;
	pos.x = min(from->x, to->x) + abs(wd) / 2;
	pos.y = min(from->y, to->y) + abs(ht) / 2;
	SetWidth(wd);
	SetHeight(ht);
	SetPosition(&pos, False);
	if (IsCurved()) {		
		return;
	}
	// keep the position of the name at fixed distance of the line.
	double alpha;
	if (wd != 0)
		alpha = atan((double)ht/(double)wd);
	else
		alpha = 2*atan(1);
	double extrax = (CL_DISTX * sin(alpha));
	double extray = (CL_DISTY * cos(alpha));
	if (extray <= 0.01 && extray >= -0.01)
		extrax = -fabs(extrax);
	Point pt;
	pt.x = pos.x - (int)extrax;
	pt.y = pos.y + (int)extray;
	for (tlist->first(); !tlist->done(); tlist->next()) {
		tlist->cur()->SetPosition(&pt);
		pt.y += tlist->cur()->GetFontHeight();
	}
	CalcDirection();
}
