////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente.
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
////////////////////////////////////////////////////////////////////////////////
#include "scdandline.h"
#include "nodeshape.h"


SCDAndLine::SCDAndLine(ShapeView *v, Grafport *g, GShape *node1,
		List<Point *> *aline, bool Curved)
:
	Line(v, g, node1, node1, aline, Curved)
{
	CalcEndPoints();
	CalcPosition();
	SetEnd2(LineEnd::FILLED_ARROW);
}


SCDAndLine::SCDAndLine(ShapeView *v, Grafport *g, GShape *node1, bool Curved)
:
	Line(v, g, node1, node1, Curved)
{
	if ( node1 )
		CalcEndPoints();
	SetEnd2(LineEnd::FILLED_ARROW);
}


SCDAndLine::~SCDAndLine() {
}



/* virtual */ void SCDAndLine::CalcEndPoints() {
	Line::CalcEndPoints();
//	// ... but end points have to be on the child area's border instead of
//	// the (outer) boundary.
//	NodeShape *shape = dynamic_cast<NodeShape *>(GetFromShape());
//	if ( ! shape )
//		return;
//	List<Point *> *lin = GetLine();
//	int len = lin->count();
//
//	// The code below is copied and adapted from NodeShape::GiveOrthoSnp()
//	// and ShapeType::GiveOrthoSnp().
//	const Point *to = (*lin)[1], *pos = shape->GetPosition();
//	DPoint p1(shape->GetShapeType()->GetChildArea()->GiveOrthoSnp(
//	//                               ^^^^^^^^^^^^^^
//		to->x - pos->x, to->y - pos->y,
//		shape->GetWidth(), shape->GetHeight(),
//		shape->GetName()->GetStringWidth(),
//		shape->GetName()->GetStringHeight()));
//	p1.x += pos->x;
//	p1.y += pos->y;
//
//	const Point *from = (*lin)[len-2];
//	DPoint p2(shape->GetShapeType()->GetChildArea()->GiveOrthoSnp(
//	//                               ^^^^^^^^^^^^^^
//		from->x - pos->x, from->y - pos->y,
//		shape->GetWidth(), shape->GetHeight(),
//		shape->GetName()->GetStringWidth(),
//		shape->GetName()->GetStringHeight()));
//	p2.x += pos->x;
//	p2.y += pos->y;
//
//	(*lin)[0]->Set(int(0.5 + p1.x), int(0.5 + p1.y));
//	(*lin)[len-1]->Set(int(0.5 + p2.x), int(0.5 + p2.y));
//
//	/// maybe one also wants to set the points (*line)[1] and (*line)[len-2]
//	/// if len > 3.
}


/* virtual */ void SCDAndLine::CalcPosition() {
	// line points have to lie in the child area of the corresponding shape.
	Line::CalcPosition();
	NodeShape *shape = dynamic_cast<NodeShape *>(GetFromShape());
	if ( ! shape )
		return;
	List <Point *> *lin = GetLine();
	const Polygon *ca = shape->GetShapeType()->GetChildArea();
	const Point *pos = shape->GetPosition();

	for ( int i = lin->count() ; --i >= 0 ; ) {
		Point to = *(*lin)[i];
		to -= *pos;
		if ( ! ca->IsInside(to.x, to.y,
				shape->GetWidth(), shape->GetHeight(),
				shape->GetName()->GetStringWidth(),
				shape->GetName()->GetStringHeight()) ) {
			DPoint p(ca->GiveOrthoSnp(to.x, to.y,
					shape->GetWidth(), shape->GetHeight(),
					shape->GetName()->GetStringWidth(),
					shape->GetName()->GetStringHeight()));
			p.x += pos->x;
			p.y += pos->y;
			(*lin)[i]->Set(int(0.5 + p.x), int(0.5 + p.y));
		}
	}
}
