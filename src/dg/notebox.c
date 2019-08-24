///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "notebox.h"
#include "code.h"

/*  p0_____t7__________________p4
    |				\
    |				| \
    |				|   \
    |				|     \
    t0	   t8			i0______p3 = i1
    |					|
    |					|
    |					|
    |					|
    |					|
    t1	   t2			t5	t6
    |					|
    |					|
    |					|
    p1_____t3___________________t4______p2 */

const PolyPoint NoteBox::p3(  0, 0.5, 0.0, 0.0,   10, 0.0, -0.5, 0.0, true);
const PolyPoint NoteBox::p4(-10, 0.5, 0.0, 0.0,    0, 0.0, -0.5, 0.0, true);
const PolyPoint NoteBox::i0(-10, 0.5, 0.0, 0.0,   10, 0.0, -0.5, 0.0, true);
const PolyPoint NoteBox::i1(  0, 0.5, 0.0, 0.0,   10, 0.0, -0.5, 0.0);
const PolyPoint NoteBox::t4(-10, 0.5, 0.0, 0.0,    0, 0.0,  0.5, 0.0);

const PolyPoint NoteBox::multipoint(-10, 0.4, 0.0, 0.0,   7, 0.0, -0.5, 0.0);

const Polygon NoteBox::exterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&p3)->add(&p4), Polygon::ON_DEMAND);
const Polygon NoteBox::interior((new List<const PolyPoint *>)
	->add(&p4)->add(&i0)->add(&i1));
const Polygon NoteBox::namearea((new List<const PolyPoint *>)
//	->add(&t0)->add(&t1)->add(&t2)->add(&t3)->add(&t4)->add(&t5)
//	->add(&t6)->add(&i1)->add(&i0)->add(&p4)->add(&t7)->add(&t8));
	->add(&PolyPoint::TopLeft)->add(&PolyPoint::BottomLeft)
	->add(&t4)->add(&p4));
const Polygon NoteBox::childarea((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft1)->add(&PolyPoint::BottomLeft1)
	->add(&PolyPoint::BottomRight1)->add(&p3)->add(&i0)->add(&p4));

const ShapeType NoteBox::nbType(Code::NOTE_BOX, 80.0, 40.0, 0.0, 0.0,
	&namearea, &childarea, &PolyPoint::Index, &PolyPoint::Dupli,
	&multipoint, &exterior, &interior);

NoteBox::NoteBox(ShapeView *v, Grafport *g, double x, double y)
:NodeShape(v, g, x, y, &nbType)
{
}


NoteBox::NoteBox(const NodeShape &n)
	:NodeShape(n, &nbType)
{
}
