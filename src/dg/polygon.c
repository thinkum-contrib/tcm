///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente, Enschede.
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

#include "fillstyle.h"
#include "polygon.h"

#include "grafport.h"
#include <math.h>
#include <string.h>
#include "application.h"
#include "config.h"

#define sgn(x) ((x)>0?1:((x)<0?-1:0))
#define square(x) ((x)*(x))

/* This code pattern is the basis for every part where the edges of the polygon
   are handled one after the other.
	if ( ! corners->first() )
		return;
	DPoint s;
	corners->cur()->CalcPoint(&s, x, y, hs, vs, tw, th);
	DPoint first(s);
	do {
		const PolyPoint *start = corners->cur();
		DPoint e;
		if ( corners->next() )
			corners->cur()->CalcPoint(&e, x, y, hs, vs, tw, th);
		else
			e = first;
		if ( start->EdgeIsArc() ) {
			DPoint centre, radii;
			int angle;
			CalcEllipse(&centre, &radii, &angle, s, e);
			... (handle arc edge)
		} else {
			... (handle straight edge)
		}
		s = e;
	} while ( ! corners->done() );
	return;
*/

/* This code pattern is the basis for a linear equation system:
	// Ax = b
	// ( a11   a12 )   ( x1 )   ( b1 )
	// (           ) * (    ) = (    )
	// ( a21   a22 )   ( x2 )   ( b2 )
	double a11 = ..., a12 = ...;
	double a21 = ..., a22 = ...;
	double det = a11 * a22 - a12 * a21;
	if ( det ) {
		double b1 = ...;
		double b2 = ...;
		double x1 = (b1 * a22 - b2 * a12) / det;
		double x2 = (b2 * a11 - b1 * a21) / det;
	} else {
		... (handle degenerate case)
	}
*/

const Polygon Polygon::BlackDot((new List<const PolyPoint *>)
	->add(&PolyPoint::LeftAbsArc)->add(&PolyPoint::BottomAbsArc)
	->add(&PolyPoint::RightAbsArc)->add(&PolyPoint::TopAbsArc), ALWAYS);

const Polygon Polygon::FolderExterior((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::FolderTR1)
	->add(&PolyPoint::FolderTR2)->add(&PolyPoint::FolderTR3),
	Polygon::ON_DEMAND);
const Polygon Polygon::FolderNameArea((new List<const PolyPoint *>)
	->add(&PolyPoint::FolderLeft)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::FolderTR1));

const Polygon Polygon::Circle((new List<const PolyPoint *>)
	->add(&PolyPoint::LeftSqArc)->add(&PolyPoint::BottomSqArc)
	->add(&PolyPoint::RightSqArc)->add(&PolyPoint::TopSqArc),
	Polygon::ON_DEMAND);

const Polygon Polygon::Box((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft)->add(&PolyPoint::BottomLeft)
	->add(&PolyPoint::BottomRight)->add(&PolyPoint::TopRight),
	Polygon::ON_DEMAND);
const Polygon Polygon::Box1((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeft1)->add(&PolyPoint::BottomLeft1)
	->add(&PolyPoint::BottomRight1)->add(&PolyPoint::TopRight1));

const Polygon Polygon::TextBox((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeftTxt)->add(&PolyPoint::BottomLeftTxt)
	->add(&PolyPoint::BottomRightTxt)->add(&PolyPoint::TopRightTxt),
	Polygon::ON_DEMAND);

const Polygon Polygon::TextBox2((new List<const PolyPoint *>)
	->add(&PolyPoint::TopLeftTxt2)->add(&PolyPoint::BottomLeftTxt2)
	->add(&PolyPoint::BottomRightTxt2)->add(&PolyPoint::TopRightTxt2),
	Polygon::ON_DEMAND);

const Polygon Polygon::RoundedBox((new List<const PolyPoint *>)
	->add(&PolyPoint::RoundedBoxTTL)->add(&PolyPoint::RoundedBoxTLL)
	->add(&PolyPoint::RoundedBoxBLL)->add(&PolyPoint::RoundedBoxBBL)
	->add(&PolyPoint::RoundedBoxBBR)->add(&PolyPoint::RoundedBoxBRR)
	->add(&PolyPoint::RoundedBoxTRR)->add(&PolyPoint::RoundedBoxTTR),
	Polygon::ON_DEMAND);
const Polygon Polygon::RoundedBox1((new List<const PolyPoint *>)
	->add(&PolyPoint::RoundedBoxTTL1)->add(&PolyPoint::RoundedBoxTLL1)
	->add(&PolyPoint::RoundedBoxBLL1)->add(&PolyPoint::RoundedBoxBBL1)
	->add(&PolyPoint::RoundedBoxBBR1)->add(&PolyPoint::RoundedBoxBRR1)
	->add(&PolyPoint::RoundedBoxTRR1)->add(&PolyPoint::RoundedBoxTTR1));

const Polygon Polygon::SubtitleSq((new List<const PolyPoint *>)
	->add(&PolyPoint::SubtitleTLSq)->add(&PolyPoint::SubtitleBLSq)
	->add(&PolyPoint::SubtitleBRSq)->add(&PolyPoint::SubtitleTRSq));

Polygon::Polygon(List<const PolyPoint *> *c, DrawFillType ft /* = NEVER */)
: corners(c),
filltype(ft)
{
	fixedCalculated = false;
	left = right = top = bottom = 0;
}


Polygon::~Polygon()
{
	corners->empty();
}


bool Polygon::HasFixedWidth() const
{
	if ( ! fixedCalculated )
		const_cast<Polygon *>(this)->CalculateFixedSize();
	return fixedWidth;
}


bool Polygon::HasFixedHeight() const
{
	if ( ! fixedCalculated )
		const_cast<Polygon *>(this)->CalculateFixedSize();
	return fixedHeight;
}


static inline void CalcEllipse(DPoint *centre, DPoint *radii, int *angle,
	const DPoint &start, const DPoint &end)
{ /* calculates the centre, start angle and both radii of the ellipse arc */
	//		|
	//  *angle = 90	| *angle = 0
	//		|
	//	--------+--------
	//		|
	// *angle = 180	| *angle = 270
	//		|
	radii->Set(end.x - start.x, end.y - start.y);
	if ( sgn(radii->x) != sgn(radii->y) ) {
		centre->Set(start.x, end.y);
		*angle = 270;
	} else {
		centre->Set(end.x, start.y);
		*angle = 180;
	}
	if ( radii->x < 0 ) {
		radii->x = -radii->x;
		*angle -= 180;
	}
	if ( radii->y < 0 )
		radii->y = -radii->y;
}


void Polygon::IntDraw(Grafport *g, DrawFillType ds, FillStyle::Type fs,
	double x, double y, double hs, double vs, double tw, double th) const
{
	/* IntDraw could fill and draw the shape in one call. However, some
	   parts of the polygon would be drawn in an incorrect order, if the
	   fill colour would be different from the draw colour.
	   The reason for this is that arc segments and straight lines
	   are drawn in the loop, while the polygonial part is filled only
	   at the end of the procedure. */
	switch ( filltype ) {
	case NEVER:
		fs = FillStyle::UNFILLED;
		break;
	case ALWAYS:
		fs = FillStyle::FILLED;
		break;
	case ON_DEMAND:
		break; // do nothing
	}
	if ( FillStyle::UNFILLED == fs
	   && (NEVER == ds || LineStyle::INVISIBLE == g->GetLineStyle()) )
		return;
	DPoint *plist = CalcPoints(x, y, hs, vs, tw, th);
	if ( ! plist )
		return;

	// draw visible parts of the polygon:
	corners->first();
	const PolyPoint *start = corners->cur();
	DPoint nextCentre, nextRadii;
	int fillAngle = -1, drawAngle = -1, nextAngle, i = 1, straight;
	if ( start->EdgeIsArc() ) {
		CalcEllipse(&nextCentre, &nextRadii,
			&nextAngle, plist[0], plist[1]);
		straight = 1;
	} else
		straight = (ON_DEMAND == ds && ! start->EdgeIsVisible()) ? 1 : 0;
	do {
		start = corners->cur();
		DPoint centre, radii;
		int angle = 0;
		if ( start->EdgeIsArc() ) {
			centre = nextCentre;
			radii = nextRadii;
			angle = nextAngle;
		}
		const PolyPoint *end = 0;
		if ( corners->next() ) {
			end = corners->cur();
			if ( end->EdgeIsArc() )
				CalcEllipse(&nextCentre, &nextRadii,
					&nextAngle, plist[i], plist[i+1]);
		}
		if ( NEVER != ds && (corners->done() || end->EdgeIsArc()
		    || (ON_DEMAND == ds && ! end->EdgeIsVisible()) ) ) {
			if ( i > straight )
				g->DrawOpenPolygon(&plist[straight],
					i - straight + 1);
			straight = i + 1;
		}
		if ( start->EdgeIsArc() ) {
			if ( fillAngle < 0 )
				fillAngle = angle;
			if ( drawAngle < 0 && (ALWAYS == ds || start->EdgeIsVisible()) )
				drawAngle = angle;
			if ( ! corners->done() && end->EdgeIsArc()
			    && centre == nextCentre && radii == nextRadii
			    && (angle + 90) % 360 == nextAngle ) {
				// the next arc is a continuation of the current one.
				plist[i] = plist[i-1];
// alternatively:
// memmove(&plist[i], &plist[i+1], ((cnt--) - i) * sizeof(plist[0])); i--;
				if ( ON_DEMAND == ds && start->EdgeIsVisible()
				    && ! end->EdgeIsVisible() ) {
					centre -= radii;
					radii += radii;
					int endAngle = (angle + 90) % 360;
					if ( drawAngle == endAngle ) {
						drawAngle = 0;
						endAngle = 360;
					} else if ( drawAngle > endAngle )
						endAngle += 360;
					g->DrawArc(centre.x, centre.y,
						radii.x, radii.y, drawAngle, endAngle);
					drawAngle = -1;
				}
			} else {
				// the next edge is not an arc that continues the current one.
				centre -= radii;
				radii += radii;
				if ( fs != FillStyle::UNFILLED ) {
					int endAngle = (angle + 90) % 360;
					if ( fillAngle == endAngle ) {
						fillAngle = 0;
						endAngle = 360;
					} else if ( fillAngle > endAngle )
						endAngle += 360;
					g->FillSegment(centre.x, centre.y,
						radii.x, radii.y, fillAngle, endAngle);
					fillAngle = -1;
				}
				if ( NEVER != ds && (ALWAYS == ds || start->EdgeIsVisible()) ) {
					int endAngle = (angle + 90) % 360;
					if ( drawAngle == endAngle ) {
						drawAngle = 0;
						endAngle = 360;
					} else if ( drawAngle > endAngle )
						endAngle += 360;
					g->DrawArc(centre.x, centre.y,
						radii.x, radii.y, drawAngle, endAngle);
					drawAngle = -1;
				}
			}
		}
		i++;
	} while ( ! corners->done() );

	// fill the polygonial part of the shape:
	if ( fs != FillStyle::UNFILLED ) {
//		int cnt = corners->count();
//		for ( i = cnt ; i > 0 ; i-- ) {
//			if ( plist[i-1] == plist[i] )
//				memmove(&plist[i], &plist[i+1], ((cnt--) - i) * sizeof(plist[0]));
//		}
		g->FillPolygon(plist, corners->count());
	}

	delete [/* corners->count() + 1 */] plist;
	return;
}


// void Polygon::DrawOutLine(Grafport *g, double x, double y,
//	double hs, double vs, double tw, double th) const
// {
//	if ( ! corners->first() )
//		return;
//	DPoint *plist = new DPoint [corners->count() + 1];
//	int i = 0, straight = 0;
//	corners->cur()->CalcPoint(&plist[0], x, y, hs, vs, tw, th);
//	do {
//		const PolyPoint *start = corners->cur(), *end;
//		if ( corners->next() ) {
//			end = corners->cur();
//			end->CalcPoint(&plist[i], x, y, hs, vs, tw, th);
//		else
//			plist[i] = plist[0];
//
//		if ( corners->done() || ! end->EdgeIsVisible()
//		     || end->EdgeIsArc() ) {
//			if ( i > straight )
//				g->DrawOpenPolygon(&plist[straight],
//					i - straight + 1);
//			straight = i + 1;
//		}
//		if ( start->EdgeIsArc() ) {
//			DPoint centre, radii;
//			int angle;
//			CalcEllipse(&centre, &radii, &angle,
//				plist[i-1], plist[i]);
//			centre -= radii;
//			radii *= 2;
//			g->DrawArc(centre.x, centre.y, radii.x, radii.y,
//				angle, angle + 90);
//		}
//		i++;
//	} while ( ! corners->done() );
//	delete [/* corners->count() */] plist;
//	return;
//}


void Polygon::CalculateExtremePoint()
{
	if ( ! corners->first() )
		return;
	const PolyPoint *l = corners->cur(), *r = l, *t = l, *b = l, *c;
	while ( corners->next() ) {
		c = corners->cur();
		if ( *c < *l )
			l = c;
		if ( *c ^ *t )
			t = c;
		if ( *r < *c )
			r = c;
		if ( *b ^ *c )
			b = c;
	}
	left = l;
	right = r;
	top = t;
	bottom = b;
}


void Polygon::CalculateFixedSize()
{
	fixedCalculated = true;
	if ( ! left ) {
		CalculateExtremePoint();
		if ( ! left ) {
			fixedWidth = fixedHeight = true;
			return;
		}
	}
	fixedWidth = right->GetXHorizScaled() == left->GetXHorizScaled() &&
		right->GetXVertScaled() == left->GetXVertScaled();
	fixedHeight = top->GetYHorizScaled() == bottom->GetYHorizScaled() &&
		top->GetYVertScaled() == bottom->GetYVertScaled();
	return;
}


PolyPoint Polygon::CalcCentre() const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left )
			return PolyPoint(0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0);
	}
	return PolyPoint(0.5 * (left->GetXUnscaled() + right->GetXUnscaled()),
		0.5 * (left->GetXHorizScaled() + right->GetXHorizScaled()),
		0.5 * (left->GetXVertScaled() + right->GetXVertScaled()),
		0.5 * (left->GetXNameScaled() + right->GetXNameScaled()),
		0.5 * (top->GetYUnscaled() + bottom->GetYUnscaled()),
		0.5 * (top->GetYHorizScaled() + bottom->GetYHorizScaled()),
		0.5 * (top->GetYVertScaled() + bottom->GetYVertScaled()),
		0.5 * (top->GetYNameScaled() + bottom->GetYNameScaled()));
}


PolyPoint Polygon::CalcTopLeft() const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left )
			return PolyPoint(0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0);
	}
	return PolyPoint(left->GetXUnscaled(), left->GetXHorizScaled(),
		left->GetXVertScaled(), left->GetXNameScaled(),
		top->GetYUnscaled(), top->GetYHorizScaled(),
		top->GetYVertScaled(), top->GetYNameScaled());
}


PolyPoint Polygon::CalcBottomRight() const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left )
			return PolyPoint(0.0, 0.0, 0.0, 0.0,
				0.0, 0.0, 0.0, 0.0);
	}
	return PolyPoint(right->GetXUnscaled(), right->GetXHorizScaled(),
		right->GetXVertScaled(), right->GetXNameScaled(),
		bottom->GetYUnscaled(), bottom->GetYHorizScaled(),
		bottom->GetYVertScaled(), bottom->GetYNameScaled());
}


double Polygon::GetLeftMost(double x, double, double hs, double vs,
	double tw, double) const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left )
			return x;
	}
	return x + left->GetXUnscaled() + left->GetXHorizScaled() * hs
		+ left->GetXVertScaled() * vs + left->GetXNameScaled() * tw;
}


double Polygon::GetTopMost(double, double y, double hs, double vs,
	double, double th) const
{
	if ( ! top ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! top )
			return y;
	}
	return y + top->GetYUnscaled() + top->GetYHorizScaled() * hs
		+ top->GetYVertScaled() * vs + top->GetYNameScaled() * th;
}


double Polygon::GetBottomMost(double, double y, double hs, double vs,
	double, double th) const
{
	if ( ! bottom ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! bottom )
			return y;
	}
	return y + bottom->GetYUnscaled() + bottom->GetYHorizScaled() * hs
		+ bottom->GetYVertScaled() * vs + bottom->GetYNameScaled() * th;
}


double Polygon::GetRightMost(double x, double, double hs, double vs,
	double tw, double) const
{
	if ( ! right ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! right )
			return x;
	}
	return x + right->GetXUnscaled() + right->GetXHorizScaled() * hs
		+ right->GetXVertScaled() * vs + right->GetXNameScaled() * tw;
}


void Polygon::GetLeft(PolyPoint *p) const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left ) {
			p->SetXUnscaled(0.0);
			p->SetXHorizScaled(0.0);
			p->SetXVertScaled(0.0);
			p->SetXNameScaled(0.0);
			return;
		}
	}
	p->SetXUnscaled(left->GetXUnscaled());
	p->SetXHorizScaled(left->GetXHorizScaled());
	p->SetXVertScaled(left->GetXVertScaled());
	p->SetXNameScaled(left->GetXNameScaled());
	return;
}


void Polygon::GetRight(PolyPoint *p) const
{
	if ( ! right ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! right ) {
			p->SetXUnscaled(0.0);
			p->SetXHorizScaled(0.0);
			p->SetXVertScaled(0.0);
			p->SetXNameScaled(0.0);
			return;
		}
	}
	p->SetXUnscaled(right->GetXUnscaled());
	p->SetXHorizScaled(right->GetXHorizScaled());
	p->SetXVertScaled(right->GetXVertScaled());
	p->SetXNameScaled(right->GetXNameScaled());
	return;
}


void Polygon::GetTop(PolyPoint *p) const
{
	if ( ! top ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! top ) {
			p->SetYUnscaled(0.0);
			p->SetYHorizScaled(0.0);
			p->SetYVertScaled(0.0);
			p->SetYNameScaled(0.0);
			return;
		}
	}
	p->SetYUnscaled(top->GetYUnscaled());
	p->SetYHorizScaled(top->GetYHorizScaled());
	p->SetYVertScaled(top->GetYVertScaled());
	p->SetYNameScaled(top->GetYNameScaled());
	return;
}


void Polygon::GetBottom(PolyPoint *p) const
{
	if ( ! bottom ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! bottom ) {
			p->SetYUnscaled(0.0);
			p->SetYHorizScaled(0.0);
			p->SetYVertScaled(0.0);
			p->SetYNameScaled(0.0);
			return;
		}
	}
	p->SetYUnscaled(bottom->GetYUnscaled());
	p->SetYHorizScaled(bottom->GetYHorizScaled());
	p->SetYVertScaled(bottom->GetYVertScaled());
	p->SetYNameScaled(bottom->GetYNameScaled());
	return;
}


void Polygon::SetSize(double *phs, double *pvs, double tw, double th,
	double w, double h) const
{
	/* The algorithm in this procedure fits the polygon to rectangle of
	   size w x h. */
	if ( HasFixedHeight() && HasFixedWidth() )
		return;
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left )
			return;
	}
	// solve the linear equation system:
	// Xright - Xleft = w
	// Ybottom - Ytop = h   where
	// Xleft = left->XAbs + left->XHorizScale * opths + left->XVertScale * optvs + left->XTextWidth * tw
	// Xright = right->XAbs + right->XHorizScale * opths + right->XVertScale * optvs + right->XTextWidth * tw
	// Ytop = top->YAbs + top->YHorizScale * opths + top->YVertScale * optvs + top->YTextHeight * th
	// Ybottom = bottom->YAbs + bottom->YHorizScale * opths + bottom->YVertScale * optvs + bottom->YTextHeight * th

	// In standard form:
	// a11 * opths + a12 * optvs = b1
	// a21 * opths + a22 * optvs = b2

	double b1 = w + (left->GetXNameScaled() - right->GetXNameScaled()) * tw + left->GetXUnscaled() - right->GetXUnscaled();
	double b2 = h + (top->GetYNameScaled() - bottom->GetYNameScaled()) * th + top->GetYUnscaled() - bottom->GetYUnscaled();
	double a11 = right->GetXHorizScaled() - left->GetXHorizScaled(), a12 = right->GetXVertScaled() - left->GetXVertScaled();
	double a21 = bottom->GetYHorizScaled() - top->GetYHorizScaled(), a22 = bottom->GetYVertScaled() - top->GetYVertScaled();
	double det = a11 * a22 - a12 * a21;
	if ( 0.0 != det ) {
		// there is a unique solution:
		*phs = (b1 * a22 - b2 * a12) / det;
		*pvs = (b2 * a11 - b1 * a21) / det;
	} else {
		// there may be a constraint, but a non-unique one.
		// Try to maintain the actual aspect ratio:
		// opths : optvs = hs : vs
		// so, opths = factor * hs and optvs = factor * vs
		double factor = 0.0;
		double temp = a11 * *phs + a12 * *pvs;
		if ( 0.0 != temp )
			factor = b1 / temp;
		temp = a21 * *phs + a22 * *pvs;
		if ( 0.0 != temp ) {
			temp = b2 / temp;
			if ( factor < temp )
				factor = temp;
		}
		*phs *= factor;
		*pvs *= factor;
	}
}


void Polygon::GetSize(double *pw, double *ph, double hs, double vs,
	double tw, double th) const
{
	if ( ! left ) {
		const_cast<Polygon *>(this)->CalculateExtremePoint();
		if ( ! left ) {
			*pw = *ph = 0.0;
			return;
		}
	}
	*pw = right->GetXUnscaled() - left->GetXUnscaled() +
		(right->GetXHorizScaled() - left->GetXHorizScaled()) * hs +
		(right->GetXVertScaled() - left->GetXVertScaled()) * vs +
		(right->GetXNameScaled() - left->GetXNameScaled()) * tw;
	*ph = bottom->GetYUnscaled() - top->GetYUnscaled() +
		(bottom->GetYHorizScaled() - top->GetYHorizScaled()) * hs +
		(bottom->GetYVertScaled() - top->GetYVertScaled()) * vs +
		(bottom->GetYNameScaled() - top->GetYNameScaled()) * th;
}


//double Polygon::GetDefaultHeight() const {
//	if ( ! left ) {
//		const_cast<Polygon *>(this)->CalculateExtremePoint();
//		if ( ! left )
//			return 0.0;
//	}
//	return bottom->GetYUnscaled() + bottom->GetYHorizScaled()
//		+ bottom->GetYVertScaled() - top->GetYUnscaled()
//		- top->GetYHorizScaled() - top->GetYVertScaled();
//}


//double Polygon::GetDefaultWidth() const {
//	if ( ! left ) {
//		const_cast<Polygon *>(this)->CalculateExtremePoint();
//		if ( ! left )
//			return 0.0;
//	}
//	return right->GetXUnscaled() + right->GetXHorizScaled()
//		+ right->GetXVertScaled() - left->GetXUnscaled()
//		- left->GetXHorizScaled() - left->GetXVertScaled();
//}


void Polygon::FitText(double *phs, double *pvs, double tw, double th) const
{
	if ( HasFixedHeight() && HasFixedWidth() || ! tw || ! th )
		return;
	double minhs = *phs, minvs = *pvs;
	SetSize(&minhs, &minvs, tw, th, tw, th);
	if ( *phs > minhs )
		minhs = *phs;
	if ( *pvs > minvs )
		minvs = *pvs;
	/* The algorithm can be refined as follows: Now, the
	   polygon edges are considered. If any of them still
	   intersects with the text, a factor can be calculated
	   to enlarge the figure. This enlargement should not
	   change the aspect ratio any more.
	   (In our setting, it is simpler to calculate the divisor = 1/factor.)
	   We simplify the problem by assuming that some of the parameters
	   are = 0.
	   To make the procedure even more efficient, it only looks for edges
	   in one quadrant (it assumes that the name area is symmetric in both
	   the X and the Y axis). */
	if ( ! corners->first() ) {
		*phs = minhs;
		*pvs = minvs;
		return;
	}
	const PolyPoint centre(CalcCentre());
	const PolyPoint *start = corners->cur();
	double sxa = start->GetXUnscaled() - centre.GetXUnscaled()
		+ (start->GetXNameScaled() - centre.GetXNameScaled()) * tw;
	double sya = start->GetYUnscaled() - centre.GetYUnscaled()
		+ (start->GetYNameScaled() - centre.GetYNameScaled()) * th;
	double sxf = (start->GetXHorizScaled() - centre.GetXHorizScaled()) * minhs
		+ (start->GetXVertScaled() - centre.GetXVertScaled()) * minvs;
	double syf = (start->GetYHorizScaled() - centre.GetYHorizScaled()) * minhs
		+ (start->GetYVertScaled() - centre.GetYVertScaled()) * minvs;
	double divisor = 1.0;
	do {
		const PolyPoint *end = corners->next() ? corners->cur()
			: (*corners)[0];
		double exa = end->GetXUnscaled() - centre.GetXUnscaled()
			+ (end->GetXNameScaled() - centre.GetXNameScaled()) * tw;
		double eya = end->GetYUnscaled() - centre.GetYUnscaled()
			+ (end->GetYNameScaled() - centre.GetYNameScaled()) * th;
		double exf = (end->GetXHorizScaled() - centre.GetXHorizScaled()) * minhs
			+ (end->GetXVertScaled() - centre.GetXVertScaled()) * minvs;
		double eyf = (end->GetYHorizScaled() - centre.GetYHorizScaled()) * minhs
			+ (end->GetYVertScaled() - centre.GetYVertScaled()) * minvs;
		double b1 = -sxf - exf;
		double b2 = -syf - eyf;
		if ( sxa == exa && sya == eya && b1 <= 0.0 && b2 <= 0.0 ) {
			double tempdivisor = 0.0;
			if ( start->EdgeIsArc() ) {
				double rxf = exf - sxf;
				double ryf = eyf - syf;
				double cxa, cxf, cya, cyf;
				if ( sgn(rxf) != sgn(ryf) ) {
					cxa = sxa; cxf = sxf;
					cya = eya; cyf = eyf;
				} else {
					cxa = exa; cxf = exf;
					cya = sya; cyf = syf;
				}
				double sq_rxf = square(rxf);
				double sq_ryf = square(ryf);
				// Quadratic equation a * t^2 + b *t + c == 0
				double a = square(cxa - 0.5 * tw) / sq_rxf
					+ square(cya - 0.5 * th) / sq_ryf;
				double b = cxf * (2.0 * cxa - tw) / sq_rxf
					+ cyf * (2.0 * cya - th) / sq_ryf;
				double c = square(cxf) / sq_rxf
					+ square(cyf) / sq_ryf - 1.0;
				if ( a ) {
					b /= a;
					c /= a;
					// t^2 + b * t + c == 0
					double D = square(b) - 4.0 * c;
					if ( D >= 0.0 ) { // must happen
						// always choose the larger
						// solution of the two:
						tempdivisor = (sqrt(D) - b) * 0.5;
						// Check whether we have found
						// the correct quadrant:
						if ( tempdivisor <= 0.0 || sgn(th - cya - cyf / tempdivisor) != sgn(rxf) || sgn(tw - cxa - cxf / tempdivisor) != sgn(-ryf) )
							// must not happen
							tempdivisor = 0.0;
					}
				} // else: in this case (a == 0), b == 0 follows
			} else {
				// solve the linear equation system:
				// A * (1/factor   t) = b
				// to find the intersection point of the text
				// box with the edge. If |t| <= 1, the point is
				// between start and end node of the edge.
				double a11 = sxa + exa - tw;
				double a21 = sya + eya - th;
				double a12 = sxf - exf;
				double a22 = syf - eyf;
				double det = a11 * a22 - a12 * a21;
				// (det == 0 if the line from s to e has slope
				// y/x [neglecting sxa, sya, exa, eya])
				if ( det &&
				  fabs((b2 * a11 - b1 * a21) / det) <= 1.0 )
					tempdivisor =
						(b1 * a22 - b2 * a12) / det;
					// (tempdivisor == 0 if the line from s
					// to e is radial)
			}
			if ( tempdivisor > 0.0 && tempdivisor < divisor )
				divisor = tempdivisor;
		}
		sxa = exa;
		sya = eya;
		sxf = exf;
		syf = eyf;
	} while ( ! corners->done() );
	*phs = minhs / divisor;
	*pvs = minvs / divisor;
	return;
}


bool Polygon::IsInside(double x, double y, double hs, double vs,
	double tw, double th) const
{ /* Is (0, 0) inside the polygon? */
	DPoint *plist = CalcPoints(x, y, hs, vs, tw, th);
	if ( ! plist )
		return False;
	bool result = IntIsInside(plist, DPoint(0.0, 0.0));
	delete [/* corners->count() + 1 */] plist;
	return result;
}


bool Polygon::IsContainedIn(double hs, double vs, double tw, double th,
	const Polygon *exterior, double ex, double ey,
	double ehs, double evs, double etw, double eth) const
{	// Is *this contained in *exterior?
	// simple version... only check the polygon _points_ of *this.
	DPoint *eplist = exterior->CalcPoints(ex, ey, ehs, evs, etw, eth);
	if ( ! eplist )
		return False;
	bool result = True;
	for ( unsigned i = 0 ; i < corners->count() ; i++ ) {
		DPoint s;
		(*corners)[i]->CalcPoint(&s, 0.0, 0.0, hs, vs, tw, th);
		if ( ! exterior->IntIsInside(eplist, s) ) {
			result = False;
			break;
		}
	}
	delete [/* exterior->corners->count() + 1 */] eplist;
	return result;
}


bool Polygon::IsHit(double x, double y, double hs, double vs,
	double tw, double th) const
{ /* Is (0, 0) near any edge of the polygon? */
	if ( ! corners->first() )
		return False;
	DPoint s;
	corners->cur()->CalcPoint(&s, x, y, hs, vs, tw, th);
	DPoint first(s);
	do {
		const PolyPoint *start = corners->cur();
		DPoint e;
		if ( corners->next() )
			corners->cur()->CalcPoint(&e, x, y, hs, vs, tw, th);
		else
			e = first;
		if ( ALWAYS == filltype || start->EdgeIsVisible() ) {
			if ( e.x * e.x + e.y * e.y < square(theApplication->GetConfig()->GetLineSelectDistance()) )
				return True;
			double dist2 = 0.0;
			if ( start->EdgeIsArc() ) {
				DPoint centre, radii;
				int angle;
				CalcEllipse(&centre, &radii, &angle, s, e);
				if ( centre.x || centre.y ) {
					if ( angle < 180 )
						radii.y = -radii.y;
					if ( 180 == angle || 90 == angle )
						radii.x = -radii.x;
					// This is a simple approximation
					// because it is difficult to find the
					// exact distance between (0,0) and the
					// elliptic arc.
					double t = square(centre.x * radii.y);
					t = t / (square(centre.y*radii.x) + t);
					dist2=square(centre.x+sqrt(t)*radii.x)+
					    square(centre.y+sqrt(1-t)*radii.y);
				}
			} else {
				double a11 = e.x - s.x; // a12 = -a21;
				double a21 = e.y - s.y; // a22 = a11;
				double det = a11 * a11 + a21 * a21;
				if ( det ) {
					double b1 = -s.x;
					double b2 = -s.y;
					double x1 = (b1 * a11 + b2 * a21) / det;
					if ( x1 >= 0.0 && x1 <= 1.0 )
						dist2 = square(b2 * a11 - b1 * a21) / det;
					else
						dist2 = HUGE_VAL;
				}
			}
			if ( dist2 < square(theApplication->GetConfig()->GetLineSelectDistance()) )
				return True;
		} else if ( (corners->done() ? (*corners)[0] : corners->cur())
							  ->EdgeIsVisible()
		     && (e.x * e.x + e.y * e.y < square(theApplication->GetConfig()->GetLineSelectDistance())) )
			return True;

		s = e;
	} while ( ! corners->done() );
	return False;
}


static inline bool IsRight(const DPoint &p, double dx, double dy) {
	// true = An observer looking towards (dx,dy) finds p on his right.
	// solve p = t(dx, dy) + u(-dy, dx) for u;
	// i.e. u = (p.x * dy - p.y * dx) / (dx * dx + dy * dy)
	// return u > 0;
	// (the denominator is always positive, so we only check the numerator)
	return p.y * dx - p.x * dy > 0;
}


DPoint Polygon::GiveSnp(double dx, double dy, double x, double y,
	double hs, double vs, double tw, double th) const
{
	// Goal of this procedure:
	// Find the intersection point between a polygon located in (x,y) and
	// a straight with slope dy/dx, passing through (0,0).
	// Algorithm used in this procedure:
	// Find out, for every point, on which side of the half-plane
	// (determined by the line (u dx, u dy), u in R) it lies.
	// When two successive points lie on different sides of the plane, the
	// edge between them is a candidate for the snap edge; calculate the
	// intersection point of the edge with the given line. The candidate
	// with maximum u is the snap point.
	if ( ! corners->first() )
		return DPoint(0.0, 0.0);
	if ( ! dx && ! dy )
		dy = -1.0;
	double u = 0.0;
	bool ufound = false;

	DPoint s;
	corners->cur()->CalcPoint(&s, x, y, hs, vs, tw, th);
	bool belows = IsRight(s, dx, dy);
	DPoint first(s);
	bool belowfirst(belows);
	do {
		const PolyPoint *start = corners->cur();
		DPoint e;
		bool belowe;
		if ( corners->next() ) {
			corners->cur()->CalcPoint(&e, x, y, hs, vs, tw, th);
			belowe = IsRight(e, dx, dy);
		} else {
			e = first;
			belowe = belowfirst;
		}
		if ( belows ^ belowe ) {
			if ( start->EdgeIsArc() ) {
				DPoint centre, radii;
				int angle;
				CalcEllipse(&centre, &radii, &angle, s, e);
				// this algorithm assumes that the whole ellipse
				// is part of the polygon.
				// solve the ellipse intersection:
				radii.x *= radii.x;
				radii.y *= radii.y;
				double a = square(dx) / radii.x
					+ square(dy) / radii.y;
				double b = -2.0 * ((dx * centre.x) / radii.x
						   + (dy * centre.y) / radii.y);
				double c = square(centre.x) / radii.x
					+ square(centre.y) / radii.y - 1;
				if ( a ) { // must happen
					b /= a;
					c /= a;
					double D = square(b) - 4.0 * c;
					if ( D >= 0.0 ) { // must happen
						double temp =
							((belows ? sqrt(D) : -sqrt(D)) - b) * 0.5;
						if ( ! ufound || temp > u ) {
							u = temp;
							ufound = true;
						}
					}
				}
			} else {
				// calculate the intersection between the two
				// lines (0,0)--(dx,dy) and s--e.
				// solve the equation system:
				// t * s + (1-t) * e = u (dx,dy)
				// Or, in standard form:
				// e = t (e - s) + u (dx,dy)
				double a11 = e.x - s.x; // a12 = dx;
				double a21 = e.y - s.y; // a22 = dy;
				double det = a11 * dy - dx * a21;
				if ( det ) {
					double temp =
						(e.y * a11 - e.x * a21) / det;
					if ( ! ufound || temp > u ) {
						u = temp;
						ufound = true;
					}
				}
			}
		}
		s = e;
		belows = belowe;
	} while ( ! corners->done() );
	return DPoint(ufound ? u * dx : 0.0,
		ufound ? u * dy : 0.0);
}


DPoint Polygon::GiveSnp(int order, int count, double dx, double dy, double hs,
		double vs, double tw, double th) const
{
	// gives snap points for count lines to the point (dx, dy).
	// returns the order'th snap point, order in (1, 2, ..., count).
	// Algorithm:
	// 1. find out the tangents in direction (dx,dy) to the polygon
	// 2. look for a snap point in the correct place between the tangents.
	// Look for the tangents:
	// maximize and minimize the value of t for the equation:
	// point = u(dx,dy) + t * (-dy,dx)
	if ( ! corners->first() )
		return DPoint(0.0, 0.0);
	if ( ! dx && ! dy )
		dy = -1.0;
	double tmax = 0.0, tmin = 0.0;
	DPoint s;
	corners->cur()->CalcPoint(&s, 0.0, 0.0, hs, vs, tw, th);
	DPoint first(s);
	do {
//		const PolyPoint *start = corners->cur();
		DPoint e;
		if ( corners->next() )
			corners->cur()->CalcPoint(&e, 0.0, 0.0, hs, vs, tw, th);
		else
			e = first;
		// look whether s is extreme.
		// solve the linear equation system:
		// s = u(dx,dy) + t(-dy,dx)
		double t = (s.y * dx - s.x * dy) / (square(dx) + square(dy));
		if ( t < tmin )
			tmin = t;
		else if ( t > tmax )
			tmax = t;
//		if ( start->EdgeIsArc() ) {
//			DPoint centre, radii;
//			int angle;
//			CalcEllipse(&centre, &radii, &angle, s, e);
//			// Look for the tangents to the ellipse...
//		}
		s = e;
	} while ( ! corners->done() );
	if ( dy > dx || (dy == dx && dy > 0) ) {
		double temp = tmin;
		tmin = tmax;
		tmax = temp;
	}
	// Now, distribute the edges in the interval [tmin, tmax]
	double t = tmin + (order - 0.5) * (tmax - tmin) / count;
	// the edge should start in point (-t dy, t dx)
	DPoint p(-(t * dy), t * dx);
	p += GiveSnp(dx, dy, -p.x, -p.y, hs, vs, tw, th);
	return p;
}


DPoint Polygon::GiveOrthoSnp(double dx, double dy, double hs, double vs,
	double tw, double th) const
{
	// Goal of this procedure:
	// Find the intersection point between a polygon located in (0,0) and
	// a straight towards (dx,dy). If possible, give an orthogonal from
	// (dx,dy) onto the polygon.

	if ( ! corners->first() )
		return DPoint(0.0, 0.0);
	if ( ! dx && ! dy )
		dy = -1.0;
	DPoint u;
	double dist2 = -1.0; // u is the intersection point (if found), dist2 is
	// distance^2 between p and u

	DPoint s;
	corners->cur()->CalcPoint(&s, 0, 0, hs, vs, tw, th);
	DPoint first(s);
	do {
		const PolyPoint *start = corners->cur();
		DPoint e;
		if ( corners->next() )
			corners->cur()->CalcPoint(&e, 0, 0, hs, vs, tw, th);
		else
			e = first;
		if ( start->EdgeIsArc() ) {
//			DPoint centre, radii;
//			int angle;
//			CalcEllipse(&centre, &radii, &angle, s, e);
			// it's not easy to find a normal on an ellipse.
		} else {
			double a11 = e.x - s.x; // a12 = -a21;
			double a21 = e.y - s.y; // a22 = a11;
			double det = a11 * a11 + a21 * a21;
			if ( det ) {
				double b1 = dx - s.x;
				double b2 = dy - s.y;
				double x1 = (b1 * a11 + b2 * a21) / det;
				if ( x1 >= 0.0 && x1 <= 1.0 ) {
					double x2 = (b2 * a11 - b1 * a21) / det;
					if ( x2 >= 0.0 ) {
						double tempdist2 = x2 * x2 * det;
						if ( dist2 < 0.0 || tempdist2 < dist2 ){
							u.Set(s.x + x1 * a11,
								s.y + x1 * a21);
							dist2 = tempdist2;
						}
					}
				}
			}
		}
		s = e;
	} while ( ! corners->done() );
	return dist2 >= 0.0 ? u : GiveSnp(dx, dy, 0, 0, hs, vs, tw, th);
}


DPoint *Polygon::CalcPoints(double x, double y,
	double hs, double vs, double tw, double th) const
{
	if ( ! corners->first() )
		return (DPoint *) NULL;
	DPoint *plist = new DPoint [corners->count() + 1];
	int i = 0;
	do {
		corners->cur()->CalcPoint(&plist[i], x, y, hs, vs, tw, th);
		++i;
	} while ( corners->next() );
	// now, i == corners->count()
	plist[i] = plist[0];
	return plist;
}


bool Polygon::IntIsInside(const DPoint *plist, DPoint p) const
{ /* Is p inside the polygon? */
	if ( ! corners->first() )
		return false;
	DPoint s = plist[0] - p;
	int i = 0, count = 0;
	do {
		DPoint e = plist[++i] - p;
		if ( sgn(s.x) != sgn(e.x) ) {
			if ( corners->cur()->EdgeIsArc()
			    && sgn(s.y) != sgn(e.y) ) {
				// this algorithm assumes that the pie slice
				// of the arc lies inside the figure.
				DPoint centre, radii;
				int angle;
				CalcEllipse(&centre, &radii, &angle, s, e);
				return square(centre.x / radii.x)
					+ square(centre.y / radii.y) <= 1.0;
			}
			double yy = s.y - (s.x) * (e.y - s.y) / (e.x - s.x);
			// (0, yy) is a point on the edge from s to e)
			if (  0.0 == yy )
				return true;
			if ( 0.0 > yy )
				count += sgn(s.x) - sgn(e.x);
		}
		s = e;
	} while ( corners->next() );
	return count != 0;
}
