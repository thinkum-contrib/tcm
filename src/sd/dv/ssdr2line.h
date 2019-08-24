//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SSDR2LINE_H
#define _SSDR2LINE_H

#include "t2line.h"

/// line having role names at both sides (SSD links)
class SSDR2Line: public T2Line {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDR2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	SSDR2Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
        int GetClassType() const {return Code::SSD_R2LINE;}
	///
	Shape *Clone() {return new SSDR2Line(*this);}
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	/// 
	TextShape *ChooseTextShape(int x, int y);
	///
	TextShape *HitTextShape(int x, int y);

	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);

protected:
	///
	void DrawShape();
private:
	///
	void InitTextShapes();
};
#endif
