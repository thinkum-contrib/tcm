////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "t2line.h"
 
T2Line::T2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
		T1Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
	CalcPositionTextShapes();
}

T2Line::T2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): T1Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

T2Line::T2Line(const T2Line &aline): T1Line(aline) {
	textShape2 = new TextShape(*aline.textShape2);
        textShape2->SetParent(this);
	t2Position = aline.t2Position;
}

T2Line::~T2Line() {
	delete textShape2;
}

void T2Line::InitTextShapes() {
	textShape2 = new TextShape(GetView(), GetGrafport(), this);
	textShape2->SetSequence(2);
	t2Position = BR;
}

void T2Line::CalcPositionTextShapes() {
	T1Line::CalcPositionTextShapes();
	T1Line::CalcPositionTextShape(textShape2, t2Position);
}

void T2Line::UpdateTextShape2(const string *s) {
	if (IsVisible())
		Undraw();
	textShape2->SetString(s);
	if (IsVisible())
		Draw();
}

void T2Line::SetSelect(bool s) {
	T1Line::SetSelect(s);
	textShape2->SetSelect(s);
}

void T2Line::SetFont(XFont *ft) {
	T1Line::SetFont(ft);
	textShape2->SetFont(ft);
}

void T2Line::SetTextColor(const string *c) {
	T1Line::SetTextColor(c);
	textShape2->SetColor(c);
}

TextShape *T2Line::HitTextShape(int x, int y) {
	TextShape *textShape = T1Line::HitTextShape(x, y);
	if (textShape)
		return textShape;
	if (check(textShape2) && textShape2->ContainsPt(x, y))
		return textShape2;
	return 0;
}

bool T2Line::InTextArea(int x, int y) {
	if (T1Line::InTextArea(x, y))
		return True;
	else
		return textShape2->InTextArea(x, y);
}

TextShape *T2Line::ChooseTextShape(int x, int y) {
	if (HitTextShapeArea(textShape2, t2Position, x, y))
		return textShape2;
	return T1Line::ChooseTextShape(x, y);
}

bool T2Line::HasTextShape(TextShape *t) const {
	if (T1Line::HasTextShape(t))
		return True;
	else
		return (t==textShape2);
}

bool T2Line::HasString(const string *s, bool sens, bool sub) const {
	if (T1Line::HasString(s, sens, sub))
		return True;
	return (*s != "" && textShape2->HasString(s, sens, sub));
}

bool T2Line::HasString(const string *s, bool sens, bool sub, 
		List<TextShape *> *list) {
	bool b = T1Line::HasString(s, sens, sub, list);
	if (*s != "")
		b += textShape2->HasString(s, sens, sub, list);
	return b;
}

void T2Line::WriteMembers(OutputFile *ofile) {
	T1Line::WriteMembers(ofile);
	(*ofile)<< "\t{ T2Position " << *(textShape2->GetPosition()) << " }\n";
}

bool T2Line::ReadMembers(InputFile *ifile, double format) {
	if (!T1Line::ReadMembers(ifile, format))
		return False;
	string val1, val2;
	if (format < 1.22) {
		if (!ifile->ReadAttribute2("C2Position", &val1, &val2))
			return False;
	}
	else {
		if (!ifile->ReadAttribute2("T2Position", &val1, &val2))
			return False;
	}
	int x = val1.toint();
	int y = val2.toint();
	if (x <= 0 || y <= 0)
		textShape2->SetWellPositioned(False);
	Point pt = Point(x, y);
	textShape2->SetPosition(&pt);
	return True;
}

void T2Line::SetGrafport(Grafport *g) {
	T1Line::SetGrafport(g);
	textShape2->SetGrafport(g);
}

void T2Line::SetView(ShapeView *v) {
	T1Line::SetView(v);
	textShape2->SetView(v);
}

int T2Line::GetLeftMost() const {
	return min(T1Line::GetLeftMost(), textShape2->GetLeftMost());
}

int T2Line::GetTopMost() const {
	return min(T1Line::GetTopMost(), textShape2->GetTopMost());
}

int T2Line::GetRightMost() const {
	return max(T1Line::GetRightMost(), textShape2->GetRightMost());
}

int T2Line::GetBottomMost() const {
	return max(T1Line::GetBottomMost(), textShape2->GetBottomMost());
}

void T2Line::SetTextShape() {
	T1Line::SetTextShape();
	string empty = "";
	textShape2->SetString(&empty);
	textShape2->SetParent(this);
	if (!textShape2->IsWellPositioned()) {
		CalcPositionTextShapes();
		textShape2->SetWellPositioned(True);
	}
}

void T2Line::DrawShape() {
	T1Line::DrawShape();
	textShape2->Draw();
}

void T2Line::MoveRaw(const Point *delta) {
	T1Line::MoveRaw(delta);
	textShape2->Move(delta);
}
