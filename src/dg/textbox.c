////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "textbox.h"

const ShapeType TextBox::tbType(Code::TEXT_BOX, 20.0, 20.0, 0.0, 0.0,
	&Polygon::TextBox, (const Polygon *) NULL,
	(const PolyPoint *) NULL, &PolyPoint::TopLeftTxt,
	&PolyPoint::TopRightTxt, &Polygon::TextBox2);

TextBox::TextBox(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &tbType)
{
}

TextBox::TextBox(const NodeShape &c)
	:NodeShape(c, &tbType)
{
}
