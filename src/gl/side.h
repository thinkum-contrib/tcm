//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#ifndef _SIDE_H
#define _SIDE_H

class string;

/// different sides of an item 
class Side {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// the 4 boundaries of a cell + all boundaries.
        enum Type {ALL, TOP, BOTTOM, LEFT, RIGHT, SURROUNDING};

	/// e.g. convert "Top" to TOP.
	static Type String2Type(const string* s);

	/// e.g. convert TOP to "Toop".
	static void Type2String(Type t, string* s);
};
#endif
