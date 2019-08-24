////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
////////////////////////////////////////////////////////////////////////////////
#include "nodealign.h"
#include "lstring.h"

void NodeAlign::Type2String(NodeAlign::Type l, string *s) {
	if (l == TOP)
		*s = "Top";
	else if (l == BOTTOM)
		*s = "Bottom";
	else if (l == LEFT)
		*s = "Left";
	else if (l == RIGHT)
		*s = "Right";
	else if (l == HORIZONTAL)
		*s = "Horizontal";
	else if (l == VERTICAL)
		*s = "Vertical";
	else
		*s = "Top";
}
 
NodeAlign::Type NodeAlign::String2Type(const string *s) {
	if (*s %= "Top")
		return TOP;
	else if (*s %= "Bottom")
		return BOTTOM;
	else if (*s %= "Left")
		return LEFT;
	else if (*s %= "Right")
		return RIGHT;
	else if (*s %= "Horizontal")
		return HORIZONTAL;
	else if (*s %= "Vertical")
		return VERTICAL;
	else
		return TOP;
}
