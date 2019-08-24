////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "subfolder.h"
#include "code.h"

const PolyPoint SubFolder::i1( 0.0, -0.25,   0.0, 0.0,   2.0, 0.0,  -0.5, 0.0,
	true);
const PolyPoint SubFolder::i2( 0.0, -0.25,   0.0, 0.0,   0.0, 0.0,-1/3.0, 0.0);
const PolyPoint SubFolder::i3( 2.0, -0.25,-1/6.0, 0.0,  -2.0, 0.0,-1/6.0, 0.0,
	true);
const PolyPoint SubFolder::i4( 2.0, -0.25,-1/6.0, 0.0,   0.0, 0.0,-1/3.0, 0.0,
	true);
const PolyPoint SubFolder::i5(-2.0, -0.25, 1/6.0, 0.0,   0.0, 0.0,-1/3.0, 0.0,
	true);
const PolyPoint SubFolder::i6(-2.0, -0.25, 1/6.0, 0.0,  -2.0, 0.0,-1/6.0, 0.0);

const PolyPoint SubFolder::indexpoint(0.0, -1/3.0, 0.0, 0.0,
	0.0, 0.0, -1/3.0, 0.0);

const Polygon SubFolder::interior((new List<const PolyPoint *>)
	->add(&PolyPoint::FolderTR2)->add(&PolyPoint::FolderLeft)
	->add(&i1)->add(&i2)
	->add(&i3)->add(&i4)->add(&i5)->add(&i6));

const ShapeType SubFolder::sfType(Code::SUB_FOLDER, 80.0, 40.0, 1/3.0, 0.0,
	&Polygon::FolderNameArea, &Polygon::FolderNameArea, &indexpoint,
	&PolyPoint::Dupli, &PolyPoint::Multi, &Polygon::FolderExterior,
	&interior);


SubFolder::SubFolder(ShapeView *v, Grafport *g, double x, double y)
	:NodeShape(v, g, x, y, &sfType)
{
}

SubFolder::SubFolder(const NodeShape &s)
	:NodeShape(s, &sfType)
{
}
