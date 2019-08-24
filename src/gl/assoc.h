//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _ASSOC_H
#define _ASSOC_H
// Assocs are tuples of the form <orig, copy, type>.
// Needed for instance for associating original with copied shapes
// and subjects when they are read or cut/copied.
// Types is used to make distinction between different kinds
// of assocs.

/// binary association struct.
class Assoc {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	Assoc(void* o, void* c, int t) 
		{original = o; copy = c; type = t;}
	///
	Assoc(void* o) {original = o; copy = 0;}
	///
	void Add(void* c, int t) {copy = c; type = t;}
	///
	void* original;
	///
	void* copy;
	///
	int type;
};
#endif
