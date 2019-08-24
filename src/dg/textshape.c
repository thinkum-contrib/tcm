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
#include "grafport.h"
#include "shapeview.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "textshape.h"
#include "nodeshape.h"
#include "subject.h"

TextShape::TextShape(ShapeView *v, Grafport *g, Shape *shape): Shape(v,g) {
	SetNrHandles(0);
	description = "Name";
	parent = shape;
	text = "";
	alignment = v->GetViewer()->GetDefaultTextAlignment();
	font = v->GetViewer()->GetDefaultFont();
	SetColor(v->GetViewer()->GetDefaultTextColor());
	stringWidth = 0;
	stringHeight = 0;
	sequence = 1;
	oneLine = False;
	wellPositioned = True;
	underlined = v->GetViewer()->GetDefaultFont()->IsUnderlined();
	directed = False;
	readDirection = ReadDirection::NONE;
}

TextShape::TextShape(const TextShape &t): Shape(t) {
	SetNrHandles(0);
	text = t.text;
	description = t.description;
	oneLine = t.oneLine;
	font = t.font;
	alignment = t.alignment;
	stringWidth = t.stringWidth;
	stringHeight = t.stringHeight;
	sequence = t.sequence;
	wellPositioned = True;
	underlined = t.underlined;
	directed = t.directed;
	readDirection = t.readDirection;
	parent = 0;
}

void TextShape::SetString(const string *s) {
	text = *s;
	if (oneLine)
		text.replace('\r', ' ');
	int w, h;
	font->Box(&text, w, h);
	stringWidth = w;
	stringHeight = h;
	SetSize(w+2, h);
}

void TextShape::SetString(const char *ch) {
	text = ch;
	if (oneLine)
		text.replace('\r', ' ');
	int w, h;
	font->Box(&text, w, h);
	stringWidth = w;
	stringHeight = h;
	SetSize(w+2, h);
}

void TextShape::TextBox(int &wd, int &ht) {
	wd = stringWidth;
	ht = stringHeight;
}

void TextShape::SetPosition(const Point *pos, bool) {
	Shape::SetPosition(pos, False);
}

void TextShape::DrawOutLine(const Point *c) {
	int x = c->x - GetWidth()  / 2;
	int y = c->y - GetHeight() / 2;
	SetOutlineAttributes();
	GetGrafport()->DrawRectangle(x, y, GetWidth(), GetHeight());
}

void TextShape::UpdateAlignment(TextAlign::Type a) {
	if (a != alignment) {
		Undraw();
		alignment = a;
		Draw();
	}
}

void TextShape::SetFont(XFont *ft) {
	font = ft;
	font->Box(&text, stringWidth, stringHeight);
	SetSize(stringWidth+2, stringHeight);
}

void TextShape::UpdateFont(XFont *ft) {
	if (ft != font) {
		Undraw();
		SetFont(ft);
		Draw();
	}
}

void TextShape::Draw() {
	bool setempty = False;
	if (underlined && text.length() == 0) {
		// show little dash with empty underlined text. 
		text = " ";
		setempty = True;
	}
	if (text.length() > 0) {
		SetDrawAttributes();
		GetGrafport()->SetFont(font);
		Point pos = *GetPosition();
		if (alignment == TextAlign::CENTER)
			GetGrafport()->DrawStringsCentered(
					pos.x, pos.y, &text, underlined);
		else if (alignment == TextAlign::LEFT) {
			double tlx = pos.x - stringWidth * 0.5;
			double tly = pos.y - stringHeight * 0.5;
			GetGrafport()->DrawStringsLeft(tlx, tly, &text, 
					underlined);
		}
		else {  // RIGHT
			double tlx = pos.x + stringWidth * 0.5;
			double tly = pos.y - stringHeight * 0.5;
			GetGrafport()->DrawStringsRight(tlx, tly, &text, 
					underlined);
		}
	}
	if (setempty) {
		text = "";
	}
}

void TextShape::DrawSelect() {
	if (text.length() > 0 && IsSelected()) {
		Point pos = *GetPosition();
		int x = pos.x - GetWidth() / 2;
		int y = pos.y - GetHeight() / 2;
		GetGrafport()->SetLineWidth(1);
		GetGrafport()->SetLineStyle(LineStyle::DOTTED);
		GetGrafport()->DrawRectangle(x, y, GetWidth(), GetHeight());
	}
}

bool TextShape::HasString(const string *s, bool sens, bool substr) const {
	string t1 = *s;
	string t2 = text;
	if (!sens) {
		// make them the same case.
		t1.downcase();
		t2.downcase();
	}
	if (substr)
		return (t2.contains(t1));
	else
		return (t1 == t2);
}

int TextShape::ReplaceString(const string *s1, const string *s2, 
		bool sens, bool substr) {
	string pat = *s1;
	string repl = *s2;
	string copy = text;
	if (!substr && pat != text)
		return 0;
	if (pat == repl)
		return 0;
	int n = copy.replace(pat, repl, sens);
	if (copy != text)
		GetViewer()->GetDiagram()->SetText(this, &copy);
	return n;
}

void TextShape::UpdateUnderlined(bool b) {
	if (underlined != b) {
		Undraw();
		underlined = b;
		Draw();
	}
}

bool TextShape::HasString(const string *s1, 
		bool sens, bool substr, List<TextShape *> *list) {
	bool b= HasString(s1, sens, substr);
	if (b) {
		TextShape *me = this;
	 	list->add(me);
	}
	return b;
}

bool TextShape::InTextArea(int x, int y) {
	return (ContainsPt(x, y));
}

bool TextShape::ContainsPt(int x, int y) {
	if (text.length() == 0)
		return False;
	Rectangle rect(GetLeftMost(), GetTopMost(), GetWidth(), GetHeight());
	bool iR1 = rect.Inside(x, y);
	bool iR2 = rect.Inside(x, y);	// also init
	
	if (directed) {		// directed textshape
		Rectangle rect2(GetLeftMost(), GetTopMost(), 
						GetWidth() + 16,  GetHeight());
		iR2 = rect2.Inside(x, y);
	}
	return (iR1 || iR2 ); 
}

void TextShape::UpdateReadDirection(ReadDirection::Type d) {
	if (readDirection != d) {
		Undraw();
		readDirection = d;
		Draw();
	}
}
