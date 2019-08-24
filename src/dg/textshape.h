//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995-2001 Vrije Universiteit Amsterdam and University of Twente
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
//-----------------------------------------------------------------------------
#ifndef _TEXTSHAPE_H
#define _TEXTSHAPE_H

#include "xfont.h"
#include "textalign.h"
#include "shape.h"
#include "readdirection.h"

/// text shape class that displays a character string.
class TextShape: public Shape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	enum ControlFlowType {NONE, FLATFLOW, NESTEDFLOW, ASYNCHRONOUS};
	///
	TextShape(ShapeView *v, Grafport *g, Shape *parent);
	///
	TextShape(const TextShape &t);
	///
	Shape *Clone() {return new TextShape(*this);}

	///
	void Draw();
	///
	void Undraw() {Draw();}

	/// no duplicate asteriks are possible for text shapes.
	void DrawDuplicate() {}

	///
	void SetParent(Shape *shape) {parent = shape;}
	///
	Shape *GetParent() const {return parent;}

	///
	void SetString(const char *ch);

	/// set text and recalculate the sizes.
	void SetString(const string *s);

	///
	const string *GetString() const {return &text;}

	///
	TextShape *ChooseTextShape(int, int) {return this;}
	///
	TextShape *HitTextShape(int x, int y) {return ContainsPt(x, y)?this :0;}

	///
	bool InTextArea(int x, int y);

	///
	bool IsTextShape() const {return True;}
	///
	bool IsEmpty() const {return text.length() == 0;}
	///
	void SetEmpty() {text = "";}

	/// draws a dotted rectangle around the textshape.
	void DrawOutLine(const Point *center); 

	/// set textshape at position (not using grid !).
	void SetPosition(const Point *p, bool snap=False); 

	/// returns if (x,y) is in textshape (not empty string).
	bool ContainsPt(int x, int y);

	/// return text width and height (depends on font).
	void TextBox(int &wd, int &ht);
	///
	void UpdateAlignment(TextAlign::Type newtype);
	///
	void SetAlignment(TextAlign::Type newtype) {alignment = newtype;}
	///
	TextAlign::Type GetAlignment() const {return alignment;}
	///
	XFont *GetFont() const {return font;}
	///
	void SetFont(XFont *ft);
	///
	void UpdateFont(XFont *ft);
	///
	int GetFontHeight() const {return font->GetHeight();}
	///
	int GetStringHeight() const {return stringHeight;}
	///
	int GetStringWidth() const {return stringWidth;}

	/// if wellPositioned = false then current position isn't preferred. 
	bool IsWellPositioned() const {return wellPositioned;}

	/// !wellPositioned indicates parent should recalculate child position.
	void SetWellPositioned(bool b) {wellPositioned = b;} 

	/// returns a string which describes the kind of text shape.
	const string *GetDescription() const {return &description;} 
	///
	void SetDescription(const string *s) {description=*s;}
	///
	void SetDescription(const char *s) {description=s;}

	/// 
	bool IsOneLine() const {return oneLine;}
	///
	void SetOneLine(bool o) {oneLine=o;}

	/// 
	bool IsUnderlined() const {return underlined;}
	///
	void SetUnderlined(bool b) {underlined=b;}
	///
	void UpdateUnderlined(bool b);

	/// return if it has t as one of the text shapes.
	bool HasTextShape(TextShape *t) const {return this==t;}
 
	/// textshape contains s as string. 
	bool HasString(const string *s, bool sens, bool sub) const;

	/// replace occurrences of s1 by s2 (if allowed by Update).
	int ReplaceString(const string *s1, const string *s2, 
			bool sens, bool sub);

	/// puts itself into list when text contains s
	bool HasString(const string *s, bool caseSens, bool substring, 
			List<TextShape *> *list);
	///
	int GetSequence() const {return sequence;} 
	///
	void SetSequence(int n) {sequence=n;}

	///
	bool IsDirected() const {return directed;}
	/// 
	void SetDirected(bool b) {directed = b;} 

	///
	ReadDirection::Type GetReadDirection() const {return readDirection;}
	///
	void SetReadDirection(ReadDirection::Type rd) {readDirection=rd;}
	///
	void UpdateReadDirection(ReadDirection::Type rd);

private:
	/// the text of the textshape
	string text; 

	/// the shape the textshape belongs to.
	Shape *parent; 

	/// the X font for drawing.
	XFont *font;

	/// the text alignment of multi-line strings.
	TextAlign::Type alignment;

	/// the width of the text string (depends on font).
	int stringWidth;

	/// the height of the text string (depends on font).
	int stringHeight;

	/// a short text describing what kind of text shape this is.
	string description;

	/// indicates that parent should recalculate text shape.
	bool wellPositioned;

	/// draw dotted rect.
	void DrawSelect(); 

	/// optional sequence number when text shape is part of a row.
	int sequence;

	/// is the text shape supposed to be on a single line?
	bool oneLine;

	/// is the text shape underlined
	bool underlined;

	/// has the text shape an optional direction arrow?
	bool directed;

	/// direction type of optional arrow at textshape
	ReadDirection::Type readDirection;
};
#endif
