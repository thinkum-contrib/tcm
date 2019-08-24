////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "afont.h"

// note: the numbers should correspond with the order in the
// font chooser dialog.
const int AFont::PLAIN = 0;
const int AFont::BOLD = 1;
const int AFont::ITALIC = 2;

const int AFont::HELVETICA = 0;
const int AFont::TIMESROMAN = 1;
const int AFont::COURIER = 2;
const int AFont::NEWCENTURYSCHLBK = 3;
const int AFont::SYMBOL = 4;

AFont::AFont(const string *fy, int fam, int st, int sz, bool sc) {
	family = fam;
	style = st;
	size = sz;
	scalable = sc;
	foundry = *fy;
	factor = 1.0;
	underlined = False;
}
