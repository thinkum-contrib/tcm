//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _T2LINE_H
#define _T2LINE_H

#include "t1line.h"

/// line class (abstract) having two extra text shape.
class T2Line: public T1Line { 
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	T2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	T2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	T2Line(const T2Line &);
	///
	virtual ~T2Line();
	///
	int GetClassType() const {return Code::T2_LINE;}

	///
	void UpdateTextShape2(const string *s); 
	///
	void SetSelect(bool s);
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);

	/// as line, but the extra text shape is also considered.
	int GetLeftMost() const; 
	///
	int GetTopMost() const;
	///
	int GetRightMost() const;
	///
	int GetBottomMost() const;

	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);

	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);

	/// return if (x,y) in text-area or in text shapes.
	bool InTextArea(int x, int y); 
	/// returns name or extra text shape if hit.
	TextShape *HitTextShape(int x, int y); 
	/// returns text shape if hit or if empty, otherwise return name.
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;

	///
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasNameString(const string *, bool, bool) const {return False;}
	//
	bool HasString(const string *, bool, bool, List<TextShape *> *);
	///
	int ReplaceNameString(const string *, const string *, bool, bool) 
		 {return 0;}
	///
	void SetTextShape();
	/// draw line+textshapes.
	void DrawShape(); 

	///
	void MoveRaw(const Point *delta);
protected:
	/// calculate position of textshape on first line segment.
	virtual void CalcPositionTextShapes(); 
	///
	TextShape *GetTextShape2() const {return textShape2;}
	///
	void SetTextShape2(TextShape *t) {textShape2=t;}
	///
	PositionType GetT2Position() {return t2Position;}
	///
	void SetT2Position(PositionType t) {t2Position=t;}
private:
	///
	TextShape *textShape2;
	///
	PositionType t2Position;
	///
	void InitTextShapes();
};
#endif
