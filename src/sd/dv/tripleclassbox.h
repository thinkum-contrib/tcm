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
#ifndef _TRIPLECLASSBOX_H
#define _TRIPLECLASSBOX_H

#include "triplebox.h"

/// A triple box used as a class box with attributes and operations.
class TripleClassBox: public TripleBox {
/*@Doc: {\large {\bf scope:} TCRD} */
public:
	///
	static const int TRIPLECLASSBOX_WIDTH;
	///
	static const int TRIPLECLASSBOX_HEIGHT;
	///
	TripleClassBox(ShapeView *v, Grafport *g, int x, int y, 
		int w = TRIPLECLASSBOX_WIDTH, int h = TRIPLECLASSBOX_HEIGHT);
	///
	TripleClassBox(const Box &s);
	///
	TripleClassBox(const TripleBox &s);
	///
	Shape *Clone() { return new TripleClassBox(*this);}
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
};
#endif
