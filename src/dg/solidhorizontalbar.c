////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam and University of Twente.
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "solidhorizontalbar.h"

const PolyPoint SolidHorizontalBar::p0(0, -0.5, 0, 0,    -2, 0, 0, 0);
const PolyPoint SolidHorizontalBar::p1(0, -0.5, 0, 0,     2, 0, 0, 0);
const PolyPoint SolidHorizontalBar::p2(0,  0.5, 0, 0,     2, 0, 0, 0);
const PolyPoint SolidHorizontalBar::p3(0,  0.5, 0, 0,    -2, 0, 0, 0);

const Polygon SolidHorizontalBar::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ALWAYS);

const ShapeType SolidHorizontalBar::shType(Code::SOLID_HORIZONTAL_BAR,
	80.0, 4.0, 0.0, 0.0, (const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, (const PolyPoint *) NULL,
	(const PolyPoint *) NULL, &exterior);

SolidHorizontalBar::SolidHorizontalBar(ShapeView *v, Grafport *g,
	double x, double y)
	:NodeShape(v, g, x, y, &shType)
{
}

SolidHorizontalBar::SolidHorizontalBar(const NodeShape &c)
	:NodeShape(c, &shType)
{
}


bool SolidHorizontalBar::ReadMembers(InputFile *ifile, double format) {
	if ( ! NodeShape::ReadMembers(ifile, format) )
		return False;
	if (format < 1.26) {	// setting defaults
		SetWidth(max(GetWidth(), MIN_WIDTH));
		SetHeight(4);
		SetFillStyle(FillStyle::FILLED);
		string s = "black";
		SetFillColor(&s);
	}
	return True;
}
