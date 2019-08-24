////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
// Author: Frank Dehne (frank@cs.vu.nl).

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

#include "solidverticalbar.h"

const PolyPoint SolidVerticalBar::p0(-2, 0, 0, 0,    0, 0, -0.5, 0);
const PolyPoint SolidVerticalBar::p1(-2, 0, 0, 0,    0, 0,  0.5, 0);
const PolyPoint SolidVerticalBar::p2( 2, 0, 0, 0,    0, 0,  0.5, 0);
const PolyPoint SolidVerticalBar::p3( 2, 0, 0, 0,    0, 0, -0.5, 0);

const Polygon SolidVerticalBar::exterior((new List<const PolyPoint *>)
	->add(&p0)->add(&p1)->add(&p2)->add(&p3), Polygon::ALWAYS);

const ShapeType SolidVerticalBar::svType(Code::SOLID_VERTICAL_BAR, 4.0, 40.0,
	0.0, 0.0, (const Polygon *) NULL, (const Polygon *) NULL,
	(const PolyPoint *) NULL, (const PolyPoint *) NULL,
	(const PolyPoint *) NULL, &exterior);


SolidVerticalBar::SolidVerticalBar(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &svType)
{
}


SolidVerticalBar::SolidVerticalBar(const NodeShape &c)
	:NodeShape(c, &svType)
{
}


bool SolidVerticalBar::ReadMembers(InputFile *ifile, double format) {
	if ( ! NodeShape::ReadMembers(ifile, format) )
		return False;
	if (format < 1.26) {	// setting defaults
//		SetWidth(BAR_WIDTH);
		SetHeight(max(GetHeight(), MIN_HEIGHT));
//		SetFillStyle(FillStyle::FILLED);
		string s = "black";
		SetFillColor(&s);
	}
	return True;
}
