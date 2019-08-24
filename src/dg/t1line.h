//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _T1LINE_H
#define _T1LINE_H

#include "line.h"

/// line class (abstract) having an extra text shape.
class T1Line: public Line { 
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	T1Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	T1Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	T1Line(const T1Line &aline);
	///
	virtual ~T1Line();
	///
	int GetClassType() const {return Code::T1_LINE;}
	///
	void CalcPosition();
	/// calls corresponding members of textShape1.
	void UpdateTextShape1(const string *s); 
	///
	void SetSelect(bool s);
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);

	/// as line, but the extra textshape is also considered.
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
	enum PositionType {TL, TR, BL, BR};

	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);

	/// return if (x,y) in text-area of in textshape.
	bool InTextArea(int x, int y); 
	/// returns name or extra textshape if hit.
	TextShape *HitTextShape(int x, int y); 
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

	/// returns textshape if hit or if empty, otherwise return name.
	TextShape *ChooseTextShape(int x, int y);
	///
	void MoveRaw(const Point *delta);
protected:
	/// fraction of line for the extra textshapes.
	static const int CL_FRACTION;

	/// calculate position of textshape on first line segment.
	virtual void CalcPositionTextShapes(); 
	///
	void CalcPositionTextShape(TextShape *t, PositionType tpos);
	///
	bool HitTextShapeArea(TextShape *t, PositionType tpos, int x, int y);
	/// returns of (x,y) hits area for extra textshapes.
	bool HitExtraTextShapeArea(int x, int y, 
		const Point *from, const Point *to);
	///
	TextShape *GetTextShape1() const {return textShape1;}
	///
	void SetTextShape1(TextShape *t) {textShape1=t;}
	///
	PositionType GetT1Position() {return t1Position;}
	///
	void SetT1Position(PositionType t) {t1Position=t;}
private:
	///
	TextShape *textShape1;
	///
	PositionType t1Position;
	///
	virtual void InitTextShapes();
};
#endif
