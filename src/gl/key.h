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
#ifndef _KEY_H
#define _KEY_H
 
#include "bool.h"

/// definitions of various character codes.
class Key {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// definitions of character codes of non-printable ascii chars.
	static const int BACKSPACE;
	///
	static const int TAB;
	///
	static const int VERTICAL_TAB;
	///
	static const int ESCAPE; 
	///
	static const int FS;
	///
	static const int RS;
	///
	static const int DELETE;
	///
	static const int CTRL_B;
	///
	static const int CTRL_E;

	/// definitions of character codes of special keys (non-ascii).
	static const int HOME;
	///
	static const int LEFT;
	///
	static const int UP;
	///
	static const int RIGHT;
	///
	static const int DOWN;
	///
	static const int PAGE_UP;
	///
	static const int PAGE_DOWN;
	///
	static const int END;
	///
	static const int INSERT;

	///
	static bool ArrowKey(int key) {
		return (key==UP||key==RIGHT||key==LEFT||key==DOWN);
	}
	///
	static bool EditKey(int key) {
		return (ArrowKey(key)||key==INSERT||key==DELETE||
		key==HOME||key==END||key==PAGE_UP||key==PAGE_DOWN||
		key==ESCAPE);
	}
};
 
#endif
