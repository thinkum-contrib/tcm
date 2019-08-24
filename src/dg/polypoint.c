////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////

#include "polypoint.h"

#include "grafport.h"

const PolyPoint PolyPoint::TopLeft     ( 0, -0.5, 0, 0,   0, 0, -0.5, 0, true);
const PolyPoint PolyPoint::Top         ( 0,  0  , 0, 0,   0, 0, -0.5, 0, true);
const PolyPoint PolyPoint::TopRight    ( 0,  0.5, 0, 0,   0, 0, -0.5, 0, true);
const PolyPoint PolyPoint::Right       ( 0,  0.5, 0, 0,   0, 0,  0  , 0, true);
const PolyPoint PolyPoint::BottomRight ( 0,  0.5, 0, 0,   0, 0,  0.5, 0, true);
const PolyPoint PolyPoint::Bottom      ( 0,  0  , 0, 0,   0, 0,  0.5, 0, true);
const PolyPoint PolyPoint::BottomLeft  ( 0, -0.5, 0, 0,   0, 0,  0.5, 0, true);
const PolyPoint PolyPoint::Left        ( 0, -0.5, 0, 0,   0, 0,  0  , 0, true);

const PolyPoint PolyPoint::TopLeft1    ( 1, -0.5, 0, 0,   1, 0, -0.5, 0);
const PolyPoint PolyPoint::Top1        ( 0,  0  , 0, 0,   1, 0, -0.5, 0);
const PolyPoint PolyPoint::TopRight1   (-1,  0.5, 0, 0,   1, 0, -0.5, 0);
const PolyPoint PolyPoint::Right1      (-1,  0.5, 0, 0,   0, 0,  0  , 0);
const PolyPoint PolyPoint::BottomRight1(-1,  0.5, 0, 0,  -1, 0,  0.5, 0);
const PolyPoint PolyPoint::Bottom1     ( 0,  0  , 0, 0,  -1, 0,  0.5, 0);
const PolyPoint PolyPoint::BottomLeft1 ( 1, -0.5, 0, 0,  -1, 0,  0.5, 0);
const PolyPoint PolyPoint::Left1       ( 1, -0.5, 0, 0,   0, 0,  0  , 0);

#define INV6 (1.0/6.0)
const PolyPoint PolyPoint::FolderTR1   ( 0,  0.5, 0, 0,   0, 0,-INV6, 0, true);
const PolyPoint PolyPoint::FolderTR2   ( 0,-INV6, 0, 0,   0, 0,-INV6, 0, true);
const PolyPoint PolyPoint::FolderTR3   ( 0,-INV6, 0, 0,   0, 0, -0.5, 0, true);
const PolyPoint PolyPoint::FolderLeft  ( 0, -0.5, 0, 0,   0, 0,-INV6, 0);

const PolyPoint PolyPoint::TopLeftInv    ( 0, -0.5, 0, 0,   0, 0, -0.5, 0);
const PolyPoint PolyPoint::TopRightInv   ( 0,  0.5, 0, 0,   0, 0, -0.5, 0);
const PolyPoint PolyPoint::BottomRightInv( 0,  0.5, 0, 0,   0, 0,  0.5, 0);
const PolyPoint PolyPoint::BottomLeftInv ( 0, -0.5, 0, 0,   0, 0,  0.5, 0);

const PolyPoint PolyPoint::Index       (0, 0   , 0   ,0,    7, 0   ,-0.5,0);
const PolyPoint PolyPoint::Dupli       (0,-0.4 , 0   ,0,    7, 0   ,-0.5,0);
const PolyPoint PolyPoint::Multi       (0, 0.4 , 0   ,0,    7, 0   ,-0.5,0);

const PolyPoint PolyPoint::TopArc      (0, 0  ,0,0,   0,0,-0.5,0, true, true);
const PolyPoint PolyPoint::RightArc    (0, 0.5,0,0,   0,0, 0  ,0, true, true);
const PolyPoint PolyPoint::BottomArc   (0, 0  ,0,0,   0,0, 0.5,0, true, true);
const PolyPoint PolyPoint::LeftArc     (0,-0.5,0,0,   0,0, 0  ,0, true, true);

const PolyPoint PolyPoint::TopArc1     ( 0, 0  ,0,0,   1,0,-0.5,0, false, true);
const PolyPoint PolyPoint::RightArc1   (-1, 0.5,0,0,   0,0, 0  ,0, false, true);
const PolyPoint PolyPoint::BottomArc1  ( 0, 0  ,0,0,  -1,0, 0.5,0, false, true);
const PolyPoint PolyPoint::LeftArc1    ( 1,-0.5,0,0,   0,0, 0  ,0, false, true);

const PolyPoint PolyPoint::TopAbsArc   ( 0, 0, 0, 0, -4, 0, 0, 0, false, true);
const PolyPoint PolyPoint::RightAbsArc ( 4, 0, 0, 0,  0, 0, 0, 0, false, true);
const PolyPoint PolyPoint::BottomAbsArc( 0, 0, 0, 0,  4, 0, 0, 0, false, true);
const PolyPoint PolyPoint::LeftAbsArc  (-4, 0, 0, 0,  0, 0, 0, 0, false, true);

const PolyPoint PolyPoint::TopLeftSq    (0,-0.25,-0.25,0, 0,-0.25,-0.25,0,true);
const PolyPoint PolyPoint::TopSq        (0, 0   , 0   ,0, 0,-0.25,-0.25,0,true);
const PolyPoint PolyPoint::TopRightSq   (0, 0.25, 0.25,0, 0,-0.25,-0.25,0,true);
const PolyPoint PolyPoint::RightSq      (0, 0.25, 0.25,0, 0, 0   , 0   ,0,true);
const PolyPoint PolyPoint::BottomRightSq(0, 0.25, 0.25,0, 0, 0.25, 0.25,0,true);
const PolyPoint PolyPoint::BottomSq     (0, 0   , 0   ,0, 0, 0.25, 0.25,0,true);
const PolyPoint PolyPoint::BottomLeftSq (0,-0.25,-0.25,0, 0, 0.25, 0.25,0,true);
const PolyPoint PolyPoint::LeftSq       (0,-0.25,-0.25,0, 0, 0   , 0   ,0,true);

const PolyPoint PolyPoint::IndexSq      (0, 0   , 0   ,0, 0,-1.0/6,-1.0/6,0);
const PolyPoint PolyPoint::DupliSq      (0,-0.2 ,-0.2 ,0, 0,-1.0/6,-1.0/6,0);
const PolyPoint PolyPoint::MultiSq      (0, 0.2 , 0.2 ,0, 0,-1.0/6,-1.0/6,0);

const PolyPoint PolyPoint::TopSqArc   (0, 0   , 0   ,0, 0,-0.25,-0.25,0,true, true);
const PolyPoint PolyPoint::RightSqArc (0, 0.25, 0.25,0, 0, 0   , 0   ,0,true, true);
const PolyPoint PolyPoint::BottomSqArc(0, 0   , 0   ,0, 0, 0.25, 0.25,0,true, true);
const PolyPoint PolyPoint::LeftSqArc  (0,-0.25,-0.25,0, 0, 0   , 0   ,0,true, true);

const PolyPoint PolyPoint::TopLeftTxt     ( 0, 0, 0, -0.5,    0, 0, 0, -0.5);
const PolyPoint PolyPoint::BottomLeftTxt  ( 0, 0, 0, -0.5,    0, 0, 0,  0.5);
const PolyPoint PolyPoint::BottomRightTxt ( 0, 0, 0,  0.5,    0, 0, 0,  0.5);
const PolyPoint PolyPoint::TopRightTxt    ( 0, 0, 0,  0.5,    0, 0, 0, -0.5);

const PolyPoint PolyPoint::TopLeftTxt2    (-2, 0, 0, -0.5,   -2, 0, 0, -0.5);
const PolyPoint PolyPoint::BottomLeftTxt2 (-2, 0, 0, -0.5,    2, 0, 0,  0.5);
const PolyPoint PolyPoint::BottomRightTxt2( 2, 0, 0,  0.5,    2, 0, 0,  0.5);
const PolyPoint PolyPoint::TopRightTxt2   ( 2, 0, 0,  0.5,   -2, 0, 0, -0.5);

const PolyPoint PolyPoint::RoundedBoxTTL ( 5,-0.48, 0.02,0,  0, 0   ,-0.5 ,0, true, true);
const PolyPoint PolyPoint::RoundedBoxTLL ( 0,-0.5 , 0   ,0,  5, 0.02,-0.48,0, true);
const PolyPoint PolyPoint::RoundedBoxBLL ( 0,-0.5 , 0   ,0, -5,-0.02, 0.48,0, true, true);
const PolyPoint PolyPoint::RoundedBoxBBL ( 5,-0.48, 0.02,0,  0, 0   , 0.5 ,0, true);
const PolyPoint PolyPoint::RoundedBoxBBR (-5, 0.48,-0.02,0,  0, 0   , 0.5 ,0, true, true);
const PolyPoint PolyPoint::RoundedBoxBRR ( 0, 0.5 , 0   ,0, -5,-0.02, 0.48,0, true);
const PolyPoint PolyPoint::RoundedBoxTRR ( 0, 0.5 , 0   ,0,  5, 0.02,-0.48,0, true, true);
const PolyPoint PolyPoint::RoundedBoxTTR (-5, 0.48,-0.02,0,  0, 0   ,-0.5 ,0, true);

const PolyPoint PolyPoint::RoundedBoxTTL1( 5,-0.48, 0.02,0,  1, 0   ,-0.5 ,0, false, true);
const PolyPoint PolyPoint::RoundedBoxTLL1( 1,-0.5 , 0   ,0,  5, 0.02,-0.48,0);
const PolyPoint PolyPoint::RoundedBoxBLL1( 1,-0.5 , 0   ,0, -5,-0.02, 0.48,0, false, true);
const PolyPoint PolyPoint::RoundedBoxBBL1( 5,-0.48, 0.02,0, -1, 0   , 0.5 ,0);
const PolyPoint PolyPoint::RoundedBoxBBR1(-5, 0.48,-0.02,0, -1, 0   , 0.5 ,0, false, true);
const PolyPoint PolyPoint::RoundedBoxBRR1(-1, 0.5 , 0   ,0, -5,-0.02, 0.48,0);
const PolyPoint PolyPoint::RoundedBoxTRR1(-1, 0.5 , 0   ,0,  5, 0.02,-0.48,0, false, true);
const PolyPoint PolyPoint::RoundedBoxTTR1(-5, 0.48,-0.02,0,  1, 0   ,-0.5 ,0);

const PolyPoint PolyPoint::SubtitleTLSq(-3, 0, 0, -0.5,  0, 0.25, 0.25, 0  );
const PolyPoint PolyPoint::SubtitleBLSq(-3, 0, 0, -0.5,  6, 0.25, 0.25, 1.0);
const PolyPoint PolyPoint::SubtitleTRSq( 3, 0, 0,  0.5,  0, 0.25, 0.25, 0  );
const PolyPoint PolyPoint::SubtitleBRSq( 3, 0, 0,  0.5,  6, 0.25, 0.25, 1.0);

const PolyPoint PolyPoint::BottomLeftSqInv (0,-0.25,-0.25, 0,  0, 0.25, 0.25, 0);
const PolyPoint PolyPoint::BottomSqInv     (0, 0   , 0   , 0,  0, 0.25, 0.25, 0);
const PolyPoint PolyPoint::BottomRightSqInv(0, 0.25, 0.25, 0,  0, 0.25, 0.25, 0);

PolyPoint::PolyPoint(double xu, double xhs, double xvs, double xns, double yu,
	double yhs, double yvs, double yns, bool ev /* = false */,
	bool ea /* = false */):
XUnscaled(xu),
XHorizScaled(xhs),
XVertScaled(xvs),
XNameScaled(xns),
YUnscaled(yu),
YHorizScaled(yhs),
YVertScaled(yvs),
YNameScaled(yns),
edgeVisible(ev),
edgeIsArc(ea)
{
}

void PolyPoint::Write(Grafport *g, double x, double y, double hs, double vs,
	TextShape *text) const
{
	Point p(int(0.5 + x + XUnscaled +
		XHorizScaled * hs +
		XVertScaled * vs +
		XNameScaled * text->GetStringWidth()),
		int(0.5 + y + YUnscaled +
		YHorizScaled * hs +
		YVertScaled * vs +
		YNameScaled * text->GetStringHeight()));
	text->SetPosition(&p);
	text->SetGrafport(g);
	text->Draw();
}


void PolyPoint::CalcScale(const DPoint *p, double x, double y,
	double *hs, double *vs,	double tw, double th,
	bool constrainX, bool constrainY)
{
	double xx = p->x - x - XUnscaled - tw * XNameScaled;
	double yy = p->y - y - YUnscaled - th * YNameScaled;
	if ( constrainX ) {
		// ignore x coordinates. If possible, only change vs
		if ( YHorizScaled ) {
			double tempy = *hs * YHorizScaled + *vs * YVertScaled;
			if ( 0.0 == tempy )
				return;
			double factor = yy / tempy;
			*hs *= factor;
			*vs *= factor;
		} else if ( YVertScaled )
			*vs = yy / YVertScaled;
		return;
	}
	if ( constrainY ) {
		// ignore y coordinates. If possible, only change hs
		if ( XVertScaled ) {
			double tempx = *hs * XHorizScaled + *vs * XVertScaled;
			if ( 0.0 == tempx )
				return;
			double factor = xx / tempx;
			*hs *= factor;
			*vs *= factor;
		} else if ( XHorizScaled )
			*hs = xx / XHorizScaled;
		return;
	}
	// Ax = b
	// ( a11   a12 )   ( x1 )   ( b1 )
	// (           ) * (    ) = (    )
	// ( a21   a22 )   ( x2 )   ( b2 )
	// double a11 = XHorizScaled, a12 = XVertScaled;
	// double a21 = YHorizScaled, a22 = YVertScaled;
	double det = XHorizScaled * YVertScaled - XVertScaled * YHorizScaled;
	if ( det ) {
		// double b1 = xx;
		// double b2 = yy;
		*hs = (xx * YVertScaled  - yy * XVertScaled ) / det;
		*vs = (yy * XHorizScaled - xx * YHorizScaled) / det;
		return;
	}
	// handle degenerate case: there may be a constraint, but a
	// non-unique one.
	double factor;
	double tempx = *hs * XHorizScaled + *vs * XVertScaled;
	double tempy = *hs * YHorizScaled + *vs * YVertScaled;
	if ( 0.0 != tempx && 0.0 != tempy )
		factor = (xx / tempx + yy / tempy) * 0.5;
	else if ( 0.0 != tempx )
		factor = xx / tempx;
	else if ( 0.0 != tempy )
		factor = yy / tempy;
	else
		return;
	*hs *= factor;
	*vs *= factor;
	return;
}
