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
#include "side.h"
#include "lstring.h"

void Side::Type2String(Side::Type l, string *s) {
        if (l == TOP)
                *s = "Top";
        else if (l == BOTTOM)
                *s = "Bottom";
        else if (l == LEFT)
                *s = "Left";
        else if (l == RIGHT)
                *s = "Right";
        else if (l == ALL)
                *s = "All Four";
        else if (l == SURROUNDING)
                *s = "Surrounding";
        else
                *s = "All Four";
}

Side::Type Side::String2Type(const string *s) {
        if (*s %= "Top")
                return TOP;
        else if (*s %= "Bottom")
                return BOTTOM;
        else if (*s %= "Left")
                return LEFT;
        else if (*s %= "Right")
                return RIGHT;
        else if (*s %= "All Four")
                return ALL;
        else if (*s %= "Surrounding")
                return SURROUNDING;
        else
                return ALL;
}
