////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "linestyle.h"
#include "lstring.h"

void LineStyle::Type2String(LineStyle::Type l, string *s) {
	if (l == INVISIBLE)
		*s = "Invisible";
	else if (l == DASHED)
		*s = "Dashed";
	else if (l == DUAL)
		*s = "Dual";
	else if (l == DOTTED)
		*s = "Dotted";
	else if (l == WIDE_DOTTED)
		*s = "WideDotted";
	else
		*s = "Solid";
}
 
LineStyle::Type LineStyle::String2Type(const string *s) {
	if (*s %= "Invisible")
		return INVISIBLE;
	else if (*s %= "Dashed")
		return DASHED;
	else if (*s %= "Dotted")
		return DOTTED;
	else if (*s %= "WideDotted")
		return WIDE_DOTTED;
	else if (*s %= "Stippled")
		return DOTTED;
	else if (*s %= "Dual")
		return DUAL;
	else
		return SOLID;
}
