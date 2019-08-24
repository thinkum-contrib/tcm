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
#include "arrowtextbox.h"
#include "../sd/tr/trviewer.h"

#define SIN_225 0.38268343236508977
#define COS_225 0.92387953251128676

const int ArrowTextBox::ARROWLEN=20;

const PolyPoint ArrowTextBox::i0(0, 0, 0, 0,
	-ARROWLEN-2, 0, 0, -0.5, true);
const PolyPoint ArrowTextBox::i1(0, 0, 0, 0,
	-2 - 6 * COS_225, 0, 0, -0.5);
const PolyPoint ArrowTextBox::i2(-10 * SIN_225, 0, 0, 0,
	-2 - 10 * COS_225, 0, 0, -0.5);
const PolyPoint ArrowTextBox::i3(0, 0, 0, 0,
	-2, 0, 0, -0.5);
const PolyPoint ArrowTextBox::i4(10 * SIN_225, 0, 0, 0,
	-2 - 10 * COS_225, 0, 0, -0.5);

const Polygon ArrowTextBox::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeftTxt2)->add(&PolyPoint::BottomLeftTxt2)
	->add(&PolyPoint::BottomRightTxt2)->add(&PolyPoint::TopRightTxt2)
	->add(&i3)->add(&i4)->add(&i1)->add(&i0)->add(&i1)->add(&i2)->add(&i3),
	Polygon::ON_DEMAND);

const Polygon ArrowTextBox::interior((new List<const PolyPoint *>)
	->add(&i1)->add(&i2)->add(&i3)->add(&i4),
	Polygon::ALWAYS);

const ShapeType ArrowTextBox::atType(Code::ARROW_TEXT_BOX, 20.0, 20.0, 0.0, 0.0,
	&Polygon::TextBox, (const Polygon *) NULL, (const PolyPoint *) NULL,
	&PolyPoint::TopLeftTxt, &PolyPoint::TopRightTxt, &exterior,
	&interior);

ArrowTextBox::ArrowTextBox(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &atType)
{
}


ArrowTextBox::ArrowTextBox(const NodeShape &c)
	:NodeShape(c, &atType)
{
}


int ArrowTextBox::GetTopMost() const {
	int t = NodeShape::GetTopMost();
	TRViewer *trviewer = dynamic_cast<TRViewer *>(GetViewer());
	if ( trviewer && trviewer->IsTreeMode() )
		t += ARROWLEN;
	return t;
}
