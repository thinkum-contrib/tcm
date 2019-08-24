//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#ifndef _T4TLISTLINE_H
#define _T4TLISTLINE_H

#include "t4line.h"

/// line having 4 text shapes at 4 positions.
class T4TListLine: public T4Line {
/*@Doc: {\large {\bf scope:} Diagram} */
public:
	///
	T4TListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	T4TListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	T4TListLine(const T4TListLine &);
	///
	virtual ~T4TListLine();
	///
	int GetClassType() const {return Code::T4_TLIST_LINE;}

	/// see T4Line. Holds all text shapes into account.
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
	void UpdateTListTextShape(const string *s, unsigned n);

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

	/// calculate position of all text shapes.
	void CalcPositionTextShapes(); 
	/// calculate position of text shapes list.
	void CalcPositionTextShapeList(); 
protected:
	///
	List<TextShape *> *GetTList() const { return tlist;}
	///
	void DrawTextShapes();
	/// draw line+ 4 other text shapes.
	void DrawShape(); 

private:
	///
	List <TextShape *> *tlist;
	///
	int MessageCount;
	///
	void InitTextShapes();
};
#endif
