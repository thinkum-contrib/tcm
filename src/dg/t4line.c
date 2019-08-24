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
#include "inputfile.h"
#include "outputfile.h"
#include "t4line.h"

T4Line::T4Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *aline, bool Curved): 
			T2Line(v, g, n1, n2, aline, Curved) {
	InitTextShapes();
	CalcPositionTextShapes();
}

T4Line::T4Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved): T2Line(v, g, n1, n2, Curved) {
	InitTextShapes();
}

T4Line::T4Line(const T4Line &aline): T2Line(aline) {
	textShape3 = new TextShape(*aline.textShape3);
        textShape4 = new TextShape(*aline.textShape4);
	textShape3->SetParent(this);
	textShape4->SetParent(this);
	t3Position = aline.t3Position;
	t4Position = aline.t4Position;
}

void T4Line::InitTextShapes() {
	textShape3 = new TextShape(GetView(), GetGrafport(), this);
	textShape4 = new TextShape(GetView(), GetGrafport(), this);
	textShape3->SetSequence(3);
	textShape4->SetSequence(4);
	t3Position = TL;
	t4Position = TR;
}

T4Line::~T4Line() {
	delete textShape3;
	delete textShape4;
}

void T4Line::DrawShape() {
	T2Line::DrawShape();
	textShape3->Draw();
	textShape4->Draw();
}

void T4Line::CalcPositionTextShapes() {
	T2Line::CalcPositionTextShapes();
	CalcPositionTextShape(textShape3, t3Position);
	CalcPositionTextShape(textShape4, t4Position);
}

void T4Line::UpdateTextShape3(const string *c) {
	if (IsVisible())
		Undraw();
	textShape3->SetString(c);
	if (IsVisible())
		Draw();
}

void T4Line::UpdateTextShape4(const string *c) {
	if (IsVisible())
		Undraw();
	textShape4->SetString(c);
	if (IsVisible())
		Draw();
}

void T4Line::SetSelect(bool s) {
	T2Line::SetSelect(s);
	textShape3->SetSelect(s);
	textShape4->SetSelect(s);
}

bool T4Line::InTextArea(int x, int y) {
	if (T2Line::InTextArea(x, y))
		return True;
	else
		return (textShape3->InTextArea(x, y) || 
		       textShape4->InTextArea(x, y));
}

TextShape *T4Line::HitTextShape(int x, int y) {
	TextShape *textShape = T2Line::HitTextShape(x, y);
	if (textShape)
		return textShape;
	else if (textShape3->ContainsPt(x, y))
		return textShape3;
	else if (textShape4->ContainsPt(x, y))
		return textShape4;
	return 0;
}

TextShape *T4Line::ChooseTextShape(int x, int y) {
	if (HitTextShapeArea(textShape3, t3Position, x, y))
		return textShape3;
	if (HitTextShapeArea(textShape4, t4Position, x, y))
		return textShape4;
	return T2Line::ChooseTextShape(x, y);
}

bool T4Line::HasTextShape(TextShape *t) const {
	if (T2Line::HasTextShape(t))
		return True;
	return (t == textShape3 || t == textShape4);
}

int T4Line::GetLeftMost() const {
	int c = textShape3->GetLeftMost();
	int d = textShape4->GetLeftMost();
	return min(T2Line::GetLeftMost(), min(c, d));
}

int T4Line::GetTopMost() const {
	int c = textShape3->GetTopMost();
	int d = textShape4->GetTopMost();
	return min(T2Line::GetTopMost(), min(c, d));
}

int T4Line::GetRightMost() const {
	int c = textShape3->GetRightMost();
	int d = textShape4->GetRightMost();
	return max(T2Line::GetRightMost(), max(c, d));
}

int T4Line::GetBottomMost() const {
	int c = textShape3->GetBottomMost();
	int d = textShape4->GetBottomMost();
	return max(T2Line::GetBottomMost(), max(c, d));
}

void T4Line::WriteMembers(OutputFile *ofile) {
	T2Line::WriteMembers(ofile);
	(*ofile) << "\t{ T3Position " << *(textShape3->GetPosition()) <<" }\n";
	(*ofile) << "\t{ T4Position " << *(textShape4->GetPosition()) <<" }\n";
}

bool T4Line::ReadMembers(InputFile *ifile, double format) {
	string val1, val2;
	if (!T2Line::ReadMembers(ifile, format))
		return False;
	if (format < 1.22) {
		if (!ifile->ReadAttribute2("R1Position", &val1, &val2))
			return False;
	}
	else {
		if (!ifile->ReadAttribute2("T3Position", &val1, &val2))
			return False;
	}
	int x = val1.toint(); 
	int y = val2.toint();
	if (x <= 0 || y <= 0)
		textShape3->SetWellPositioned(False);
	Point p = Point(x, y);
	textShape3->SetPosition(&p);
	
	if (format < 1.22) {
		if (!ifile->ReadAttribute2("R2Position", &val1, &val2))
			return False;
	}
	else {
		if (!ifile->ReadAttribute2("T4Position", &val1, &val2))
			return False;
	}
	x = val1.toint(); 
	y = val2.toint();
	if (x <= 0 || y <= 0)
		textShape4->SetWellPositioned(False);
	p.Set(x,y);
	textShape4->SetPosition(&p);
	return True;
}

void T4Line::SetTextShape() {
	T2Line::SetTextShape();
	string empty = "";
	textShape3->SetString(&empty);
	textShape4->SetString(&empty);
	textShape3->SetParent(this);
	textShape4->SetParent(this);
	if (!textShape3->IsWellPositioned() ||
	    !textShape4->IsWellPositioned()) {
		CalcPositionTextShapes();
		textShape3->SetWellPositioned(True);
		textShape4->SetWellPositioned(True);
	}
}

void T4Line::SetFont(XFont *ft) {
	T2Line::SetFont(ft);
	textShape3->SetFont(ft);
	textShape4->SetFont(ft);
}

void T4Line::SetTextColor(const string *c) {
	T2Line::SetTextColor(c);
	textShape3->SetColor(c);
	textShape4->SetColor(c);
}

void T4Line::SetAlignment(TextAlign::Type al) {
	T2Line::SetAlignment(al);
	textShape3->SetAlignment(al);
	textShape4->SetAlignment(al);
}

void T4Line::SetGrafport(Grafport *g) {
	T2Line::SetGrafport(g);
	textShape3->SetGrafport(g);
	textShape4->SetGrafport(g);
}

void T4Line::SetView(ShapeView *v) {
	T2Line::SetView(v);
	textShape3->SetView(v);
	textShape4->SetView(v);
}

bool T4Line::HasString(const string *s, bool sens, bool sub) const {
	if (T2Line::HasString(s, sens, sub))
		return True;
	else if (*s == "")
		return False;
	else if (textShape3->HasString(s, sens, sub) ||
		 textShape4->HasString(s, sens, sub))
		return True;
	else
		return False;
}

bool T4Line::HasString(const string *s, bool sens, bool sub, 
			List<TextShape *> *list) {
	bool b = T2Line::HasString(s, sens, sub, list);
	if (*s != "") {
		b += textShape3->HasString(s, sens, sub, list);
		b += textShape4->HasString(s, sens, sub, list);
	}
	return b;
}

void T4Line::MoveRaw(const Point *delta) {
	T2Line::MoveRaw(delta);
	Point pos = *textShape3->GetPosition()+*delta;
	textShape3->SetPosition(&pos);
	pos = *textShape4->GetPosition()+*delta;
	textShape4->SetPosition(&pos);
}
