//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _SIMPLELABEL_H
#define _SIMPLELABEL_H

#include "point.h"
#include "lstring.h"
#include "xfont.h"
class Grafport;

/// abstract (simple) text label class.
class SimpleLabel {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	SimpleLabel(Grafport *g, XFont *font);
	///
	SimpleLabel(const SimpleLabel &text);	
	///
	virtual ~SimpleLabel();			

	///
	friend int operator==(const SimpleLabel &t1, const SimpleLabel &t2);
	///
	friend int Compare(SimpleLabel *r1, SimpleLabel *r2) {return *r1==*r2;}

	/// draw label.
	virtual void Draw() = 0;		

	/// erase label.
	virtual void Undraw();		

	/// when label is dragged only a dotted box (outline) is drawn
	void DrawOutLine(const Point *c);

	/// update position and redraw.
	virtual void UpdatePosition(const Point *);

	/// update label and redraw.
	virtual void UpdateText(const string *);	

	/// set position.
	void SetPosition(const Point *pt);	

	/// set label text
	void SetText(const string *s);	

	/// set grafport
	void SetGrafport(Grafport *g) {grafport = g;}

	/// calculate text size.
	void CalcSize();		

	/// true iff (x,y) is in text.
	bool HitText(int x, int y); 	

	/// simple 'get' actions.
	const Point *GetPosition() const {return &position;} 

	///
	const Point *GetTopLeft() const {return &topLeft;}
	///
	const string *GetText() const {return &text;}

	///
	int GetWidth() const {return width;}
	///
	int GetHeight() const {return height;}

	///
	XFont *GetFont() const {return font;}
	///
	void SetFont(XFont *f);

	///
	virtual void UpdateFont(XFont *font);

	///
	int FontHeight() const {return font->GetHeight();}

	/// minimal width of cell text outline.
	static const int MIN_TEXT_WIDTH; 

	/// minimal height of cell text outline.
	static const int MIN_TEXT_HEIGHT;
protected:
	///
	Grafport *GetGrafport() const {return grafport;}
private:
	/// center position of text.
	Point position;

	/// topleft position of text.
	Point topLeft;

	/// text width (depends on number of characters and point size + font).
	int width;

	/// text height (depends on font).
	int height;

	/// text string
	string text;

	/// 
	Grafport *grafport;
	///
	XFont *font;
	/// set size
	void SetSize(int wd, int ht);

	/// make sure text has positive coordinates.
	void PositiveCoord();	
};
#endif
