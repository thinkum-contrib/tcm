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
#ifndef _T4LINE_H
#define _T4LINE_H

#include "t2line.h"

/// line having 4 text shapes at 4 positions.
class T4Line: public T2Line {
/*@Doc: {\large {\bf scope:} Diagram} */
public:
	///
	T4Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	T4Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	T4Line(const T4Line &);
	///
	virtual ~T4Line();
	///
	int GetClassType() const {return Code::T4_LINE;}

	/// see T2Line. Holds all text shapes into account.
	bool InTextArea(int x, int y); 

	///
	TextShape *HitTextShape(int x, int y);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;

	///
	void SetSelect(bool s);

	///
	void UpdateTextShape3(const string *s);
	///
	void UpdateTextShape4(const string *s);

	/// as line, but all text shapes are considered
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
	void SetTextShape();
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
	///
	void SetAlignment(TextAlign::Type alignment);

	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	///
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasString(const string*, bool, bool, List<TextShape *> *);
	///
	void MoveRaw(const Point *delta);

protected:
	/// calculate position of all text shapes.
	void CalcPositionTextShapes(); 
	///
	TextShape *GetTextShape3() const {return textShape3;}
	///
	void SetTextShape3(TextShape *t) {textShape3=t;}
	///
	TextShape *GetTextShape4() const {return textShape4;}
	///
	void SetTextShape4(TextShape *t) {textShape4=t;}
	///
	PositionType GetT3Position() {return t3Position;}
	///
	void SetT3Position(PositionType t) {t3Position=t;}
	///
	PositionType GetT4Position() {return t4Position;}
	///
	void SetT4Position(PositionType t) {t4Position=t;}

	/// draw line+ 4 other text shapes.
	void DrawShape(); 
private:
	///
	TextShape *textShape3;
	///
	TextShape *textShape4;
	///
	PositionType t3Position;
	///
	PositionType t4Position;
	///
	void InitTextShapes();
};
#endif
