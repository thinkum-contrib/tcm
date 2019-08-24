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
#include "gdboundaryshape.h"

/*          ___
bs2       ,'   `.
 |       /       \
 |      /         \
bs1-----(         )
 |      \         /
 |       \       /
bs3       `.___,'    */

/* static */ const PolyPoint GDBoundaryShape::bs1(0, -0.4, -0.4, 0,  0,  0   ,  0   , 0);
/* static */ const PolyPoint GDBoundaryShape::bs2(0, -0.4, -0.4, 0,  0, -0.15, -0.15, 0, true);
/* static */ const PolyPoint GDBoundaryShape::bs3(0, -0.4, -0.4, 0,  0,  0.15,  0.15, 0);

/* static */ const Polygon GDBoundaryShape::boundary((new List<const PolyPoint *>)
	->add(&PolyPoint::LeftSqArc)->add(&PolyPoint::BottomSqInv)
	->add(&PolyPoint::SubtitleTLSq)->add(&PolyPoint::SubtitleBLSq)
	->add(&PolyPoint::SubtitleBRSq)->add(&PolyPoint::SubtitleTRSq)
	->add(&PolyPoint::BottomSqArc)->add(&PolyPoint::RightSqArc)
	->add(&PolyPoint::TopSqArc)->add(&PolyPoint::LeftSq)
	->add(&bs1)->add(&bs2)->add(&bs3)->add(&bs1));


const ShapeType GDBoundaryShape::bsType(Code::GD_BOUNDARY_SHAPE, 40.0, 40.0,
	1.0, 1.0,
	&Polygon::SubtitleSq, 0, &PolyPoint::IndexSq,
	&PolyPoint::DupliSq, &PolyPoint::MultiSq, &GDBoundaryShape::boundary);

GDBoundaryShape::GDBoundaryShape(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &bsType)
{
}

GDBoundaryShape::GDBoundaryShape(const NodeShape &c)
	:NodeShape(c, &bsType)
{
}
