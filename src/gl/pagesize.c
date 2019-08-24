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
#include "pagesize.h"
#include "lstring.h"

void PageSize::Type2String(PageSize::Type l, string *s) {
	if (l == A3)
		*s = "A3";
	else if (l == A4)
		*s = "A4";
	else if (l == LEGAL)
		*s = "Legal";
	else if (l == LETTER)
		*s = "Letter";
	else if (l == EXECUTIVE)
		*s = "Executive";
	else
		*s = "A4";
}
 
PageSize::Type PageSize::Substring2Type(const string *s) {
	if (s->contains("A3"))
		return A3;
	else if (s->contains("A4"))
		return A4;
	else if (s->contains("Legal"))
		return LEGAL;
	else if (s->contains("Letter"))
		return LETTER;
	else if (s->contains("Executive"))
		return EXECUTIVE;
	else
		return A4;
}

PageSize::Type PageSize::String2Type(const string *s) {
	if (*s %= "A3")
		return A3;
	else if (*s %= "A4")
		return A4;
	else if (*s %= "Legal")
		return LEGAL;
	else if (*s %= "Letter")
		return LETTER;
	else if (*s %= "Executive")
		return EXECUTIVE;
	else
		return A4;
}

int PageSize::GetWidth(Type t) {
	if (t == A4)
                // w = 564.24 / PS_FACTOR;
                return 595;
        else if (t == A3)
                return 842;
        else if (t == LETTER)
                // w = 500 / PS_FACTOR;
                return 612;
        else if (t == LEGAL)
                return 612;
        else if (t == EXECUTIVE)
                return 540;
	else
		return 0;
}

int PageSize::GetHeight(Type t) {
	if (t == A4)
                // h = 823.32 / PS_FACTOR;
                return 842;
        else if (t == A3)
                return 1190;
        else if (t == LETTER)
                // h = 700 / PS_FACTOR;
                return 792;
        else if (t == LEGAL)
                return 1008;
        else if (t == EXECUTIVE)
                return 720;
	else
		return 0;
}
