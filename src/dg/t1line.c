////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "inputfile.h"
#include "outputfile.h"
#include "t1line.h"
#include <math.h>
#include <stdlib.h>
 
const int T1Line::CL_FRACTION = 4;

T1Line::T1Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
		Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
	CalcPositionTextShapes();
}

T1Line::T1Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

T1Line::T1Line(const T1Line &aline): Line(aline) {
	textShape1 = new TextShape(*aline.textShape1);
	textShape1->SetParent(this);
	t1Position = aline.t1Position;
}

void T1Line::InitTextShapes() {
	textShape1 = new TextShape(GetView(), GetGrafport(), this);
	textShape1->SetSequence(1);
	t1Position = BL;
}

T1Line::~T1Line() {
	delete textShape1;
}

void T1Line::CalcPosition() {
	Line::CalcPosition();
	CalcPositionTextShapes();
}

void T1Line::CalcPositionTextShapes() {
	CalcPositionTextShape(textShape1, t1Position);
}

void T1Line::UpdateTextShape1(const string *s) {
	if (IsVisible())
		Undraw();
	textShape1->SetString(s);
	if (IsVisible())
		Draw();
}

void T1Line::SetSelect(bool s) {
	Line::SetSelect(s);
	textShape1->SetSelect(s);
}

void T1Line::SetFont(XFont *ft) {
	Line::SetFont(ft);
	textShape1->SetFont(ft);
}

void T1Line::SetTextColor(const string *c) {
	Line::SetTextColor(c);
	textShape1->SetColor(c);
}

TextShape *T1Line::HitTextShape(int x, int y) {
	TextShape *textShape = Line::HitTextShape(x, y);
	if (textShape)
		return textShape;
	if (check(textShape1) && textShape1->ContainsPt(x, y))
		return textShape1;
	return 0;
}

bool T1Line::InTextArea(int x, int y) {
	if (Line::InTextArea(x, y))
		return True;
	else
		return textShape1->InTextArea(x, y);
}

TextShape *T1Line::ChooseTextShape(int x, int y) {
	if (HitTextShapeArea(textShape1, t1Position, x, y))
		return textShape1;
	return Line::ChooseTextShape(x, y);
}

bool T1Line::HasTextShape(TextShape *t) const {
	if (Line::HasTextShape(t))
		return True;
	else
		return (t==textShape1);
}

bool T1Line::HasString(const string *s, bool sens, bool sub) const {
	if (Line::HasString(s, sens, sub))
		return True;
	return (*s != "" && textShape1->HasString(s, sens, sub));
}

bool T1Line::HasString(const string *s, bool sens, bool sub, 
		List<TextShape *> *list) {
	bool b = Line::HasString(s, sens, sub, list);
	if (*s != "")
		b += textShape1->HasString(s, sens, sub, list);
	return b;
}

void T1Line::WriteMembers(OutputFile *ofile) {
	Line::WriteMembers(ofile);
	(*ofile)<< "\t{ T1Position " << *(textShape1->GetPosition()) << " }\n";
}

bool T1Line::ReadMembers(InputFile *ifile, double format) {
	if (!Line::ReadMembers(ifile, format))
		return False;
	// read position of the textShape1 text shape.
	string val1, val2;
	if (format < 1.22) {
		if (!ifile->ReadAttribute2("C1Position", &val1, &val2))
			return False;
	}
	else {
		if (!ifile->ReadAttribute2("T1Position", &val1, &val2))
			return False;
	}
	int x = val1.toint();
	int y = val2.toint();
	if (x <= 0 || y <= 0)
		textShape1->SetWellPositioned(False);
	Point pt = Point(x, y);
	textShape1->SetPosition(&pt);
	return True;
}

void T1Line::SetGrafport(Grafport *g) {
	Line::SetGrafport(g);
	textShape1->SetGrafport(g);
}

void T1Line::SetView(ShapeView *v) {
	Line::SetView(v);
	textShape1->SetView(v);
}

int T1Line::GetLeftMost() const {
	return min(Line::GetLeftMost(), textShape1->GetLeftMost());
}

int T1Line::GetTopMost() const {
	return min(Line::GetTopMost(), textShape1->GetTopMost());
}

int T1Line::GetRightMost() const {
	return max(Line::GetRightMost(), textShape1->GetRightMost());
}

int T1Line::GetBottomMost() const {
	return max(Line::GetBottomMost(), textShape1->GetBottomMost());
}

void T1Line::SetTextShape() {
	Line::SetTextShape();
	string empty = "";
	textShape1->SetString(&empty);
	textShape1->SetParent(this);
	// calculate default position.
	if (!textShape1->IsWellPositioned()) {
		CalcPositionTextShapes();
		textShape1->SetWellPositioned(True);
	}
}

void T1Line::DrawShape() {
	Line::DrawShape();
	textShape1->Draw();
}

void T1Line::MoveRaw(const Point *delta) {
	Line::MoveRaw(delta);
	textShape1->Move(delta);
}

void T1Line::CalcPositionTextShape(TextShape *textShape, PositionType tpos) {
	double pi2 = 2*atan(1); // 90 degrees.
	List<Point *> *l = GetLine();
	Point *from, *to;
	if (tpos == BL || tpos == TL) {
		from = (*l)[0];
		to = (*l)[1];
	}
	else {
		int len = GetLine()->count();
		from = (*GetLine())[len-1];
		to = (*GetLine())[len-2];
	}
	double dy = (double)(to->y - from->y);
	double dx = (double)(to->x - from->x);
	double alpha = (dx == 0) ? pi2 : atan(dy/dx);
	double extrax = (CL_DISTX * sin(alpha));
	double extray = (CL_DISTY * cos(alpha));

	if (extray <= 0.01 && extray >= -0.01)
		extrax = -fabs(extrax);
	int w = (to->x - from->x)/(2*CL_FRACTION);
	int h = (to->y - from->y)/(2*CL_FRACTION);
	// some extra corrections.
	if (sqrt(w*w + h*h) <= 10) {
		if (w != 0 && h < 4 && abs(w) < 10)
			w = (w < 0)? -10 : 10;
		if (h != 0 && w < 4 && abs(h) < 10)
			h = (h < 0)? -10 : 10;
	}

	Point pt;
	switch (tpos) {
	case BL:
	case BR:
		pt.x = from->x + w - (int)extrax;
		pt.y = from->y + h + (int)extray;
		break;
	case TL:
	case TR:
		pt.x = from->x + w + (int)extrax;
		pt.y = from->y + h - (int)extray;
		break;
	}
	if (check(textShape))
		textShape->SetPosition(&pt);
}

bool T1Line::HitExtraTextShapeArea(int x, int y, 
			const Point *from, const Point *to) {
	int c_x, c_y;
	if (!ContainsPtLine(x, y, from, to, c_x, c_y))
		return False;
	// distance line-textshape
	int w = (to->x - from->x)/CL_FRACTION;
	int h = (to->y - from->y)/CL_FRACTION;
	int quadra = w * w + h * h;
	// compare distances
	int delta = (from->x - c_x) * (from->x - c_x) +
			(from->y - c_y) * (from->y - c_y);
	return (delta < quadra);
}

bool T1Line::HitTextShapeArea(TextShape *textShape, 
			PositionType tpos, int x, int y) {
	List<Point *> *l = GetLine();
	// for non empty textShape
	if (textShape->ContainsPt(x, y))
		return True;
	// for empty textShape
	Point *from, *to;
	if (tpos == TL || tpos == BL) {
		from = (*l)[0];
		to = (*l)[1];
		if (tpos==BL) {
			if (from->x == to->x) {
				if (x < from->x)
					return False; // vertical case
			}
			else if (AboveLine(x, y, from, to))
				return False;
		} 
		else if (tpos==TL) {
			if (from->x == to->x) {
				if (x > from->x)
					return False;
			}
			else if (!AboveLine(x, y, from, to))
				return False;
		}
	}
	else {
		int len = GetLine()->count();
		from = (*GetLine())[len-1];
		to = (*GetLine())[len-2];
		if (tpos==BR) {
			if (from->x == to->x) {
				if (x < from->x)
					return False; // vertical case
			}
			else if (AboveLine(x, y, from, to))
				return False;
		}
		else if (tpos==TR) {
			if (from->x == to->x) {
				if (x > from->x)
					return False;
			}
		 	else if (!AboveLine(x, y, from, to))
				return False;
		}
	}
	return (HitExtraTextShapeArea(x, y, from, to));
}
