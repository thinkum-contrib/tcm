//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _SSDSINGLEOBJECTBOX_H
#define _SSDSINGLEOBJECTBOX_H

#include "box.h"
 
/// An object box used for an object
class SSDSingleObjectBox: public Box {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDSingleObjectBox(ShapeView *v, Grafport *g, double x, double y);
	///
	SSDSingleObjectBox(const NodeShape &s);
	///
	Shape *Clone() {return new SSDSingleObjectBox(*this);}
	///
	int GetClassType() const {return Code::SSD_SINGLE_OBJECT_BOX;}
};
#endif