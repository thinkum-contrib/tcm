///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2003, Universiteit Twente.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
///////////////////////////////////////////////////////////////////////////////
#include "gdentityshape.h"

/*    ___
    ,'   `.
   /       \
  /         \
  (         )
  \         /
   \       /
  __`.___,'__  */

/* static */ const Polygon GDEntityShape::boundary((new List<const PolyPoint *>)
	->add(&PolyPoint::BottomRightSq)->add(&PolyPoint::BottomLeftSqInv)
	->add(&PolyPoint::SubtitleTLSq)->add(&PolyPoint::SubtitleBLSq)
	->add(&PolyPoint::SubtitleBRSq)->add(&PolyPoint::SubtitleTRSq)
	->add(&PolyPoint::BottomRightSqInv)->add(&PolyPoint::BottomSqArc)
	->add(&PolyPoint::RightSqArc)->add(&PolyPoint::TopSqArc)
	->add(&PolyPoint::LeftSqArc)->add(&PolyPoint::BottomSqInv));

const ShapeType GDEntityShape::esType(Code::GD_ENTITY_SHAPE, 40.0, 40.0,
	1.0, 1.0,
	&Polygon::SubtitleSq, 0, &PolyPoint::IndexSq,
	&PolyPoint::DupliSq, &PolyPoint::MultiSq, &GDEntityShape::boundary);

GDEntityShape::GDEntityShape(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &esType)
{
}

GDEntityShape::GDEntityShape(const NodeShape &c)
	:NodeShape(c, &esType)
{
}
