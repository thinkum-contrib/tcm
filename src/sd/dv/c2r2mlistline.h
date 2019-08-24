//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam and University of Twente.
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
#ifndef _C2R2MLISTLINE_H
#define _C2R2MLISTLINE_H

#include "t4tlistline.h"
#include "lineend.h"

/// line having card. constraints and role names at both sides  PLUS
///  a list of textshapes
class C2R2MListLine: public T4TListLine {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	C2R2MListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	C2R2MListLine(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	Shape *Clone() {return new C2R2MListLine(*this);}
	///
	int GetClassType() const {return Code::C2R2_MLIST_LINE;}
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	///
	bool InTextArea(int x, int y);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	TextShape *HitTextShape(int x, int y);
	///
	void UpdateTListTextShape(const string *s, unsigned n);
	///
	void UndrawTListTextShape(const string *s, unsigned n);
	///
	void ReDrawTListTextShape(const string *s, unsigned n);
	///
	void CalcMsgDirection(unsigned n);
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
protected:
	///
	void DrawShape();
private:
	///
	List <Point *> *plist;
	///
	LineEnd dummy;
	///
	void InitTextShapes();
};
#endif