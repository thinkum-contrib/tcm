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
#ifndef _ENDC1ARROW_H
#define _ENDC1ARROW_H

#include "t1line.h"

/// arrow having card constraint at 'to' side, name is not editable (SND).
class EndC1Arrow: public T1Line {
/*@Doc: {\large {\bf scope:} TSND} */
public:
	///
	EndC1Arrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	EndC1Arrow(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	Shape *Clone() {return new EndC1Arrow(*this);}
	///
        int GetClassType() const {return Code::T1_ARROW;}
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
private:
	///
	void Initialize();
};
#endif
