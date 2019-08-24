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
#ifndef _INITIALSTATEBOX_H
#define _INITIALSTATEBOX_H

#include "box.h"
#include "lineend.h"

/// box having downwards pointing arrow on top and list of action shapes (STD).
class InitialStateBox: public Box {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	InitialStateBox(ShapeView *v, Grafport *g, double x, double y);
	///
	InitialStateBox(const InitialStateBox &a);
	///
	virtual ~InitialStateBox();
	///
	Shape *Clone() {return new InitialStateBox(*this);}
	///
	int GetClassType() const {return Code::ARROW_BOX;}
	///
	void SetSize(int w, int h);
	///
	void SetPosition(const Point *p, bool b);
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;
	///
	bool ContainsPt(int x, int y);
	///
	bool HitHLine(int x, int y);
	///
	const Point *GetHLineFrom() const {return &hlineFrom;}
	///
	const Point *GetHLineTo() const {return &hlineTo;}
	///
	void UpdateAnchor(const Point *delta, const Point *position);
	/// update or insert string of n-th attribute.
	void UpdateAction(const string *s, unsigned n, bool update);
	/// take actions into account.
	int GetLeftMost() const; 
	///
	int GetTopMost() const;
	///
	int GetRightMost() const;
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	///
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasString(const string*, bool, bool, List<TextShape *> *);
private:
	///
	LineEnd end;
	///
	void DrawShape();
	///
	Point hlineFrom;
	///
	Point hlineTo;
	///
	Point anchorPoint;
	///
	int HLineLength();
	///
	bool HitVLine(int x, int y);
	///
	void CalcHLinePart();
	///
	void CalcPositionHLine();
	///
	void CalcPositionActions();
	///
	void SetAction(const string *s, unsigned n, bool update);
	///
	List<TextShape *> *actions;
	///
	static const int ARROWLEN;
	/// minimal length hline.
	static const int HLINELEN;
	///
	static const int HLINEXOFFSET;
	///
	static const int HLINEYOFFSET;
};
#endif
