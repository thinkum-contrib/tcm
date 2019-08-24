//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _COLOR_H
#define _COLOR_H
#include "util.h"
#include "lstring.h"

/// Associates a color name with a pixel value and a RGB value.
class Color {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// 
	Color(string x, double r, double g, double b) {
		name = x; red = r; green =g; blue =b;
		allocated = False;
	}
	/// 
	Color(const char *x, double r, double g, double b) {
		name = x; red = r; green =g; blue =b;
		allocated = False;
	}
	///
	Color(string x, unsigned long p) {
		name = x; pixel = p;
		allocated = False;
	}
	///
	Color(const char *x, unsigned long p) {
		name = x; pixel = p;
		allocated = False;
	}
	///
	string name;
	///
	double red;
	///
	double green;
	///
	double blue;
	///
	unsigned long pixel;
	///
	bool allocated;
};
#endif
