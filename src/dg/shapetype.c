//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------

#include "fillstyle.h"
#include "shapetype.h"
#include "shape.h"
#include "grafport.h"
#include "application.h"
#include "config.h"
#include <math.h>

ShapeType::ShapeType(int ct, double dw, double dh,
	double minar, double maxar, const Polygon *na, const Polygon *ca,
	const PolyPoint *ip, const PolyPoint *dp, const PolyPoint *mp,
	const Polygon *extr, const Polygon *intr /* = 0 */):
classtype(ct),
defaultWidth(dw),
defaultHeight(dh),
minAspectRatio(minar),
maxAspectRatio(maxar),
nameArea(na),
childArea(ca),
indexPoint(ip),
duplicatePoint(dp),
multiplicityPoint(mp),
exterior(extr),
interior(intr)
{
}


void ShapeType::Fill(Grafport *g, double x, double y, double hs, double vs,
	const TextShape *text) const
{
	if ( Polygon::ALWAYS == exterior->GetFillType() )
		return;
	double tw, th;
	if ( text && nameArea ) {
		tw = text->GetStringWidth();
		th = text->GetStringHeight();
	} else
		tw = th = 0.0;
	exterior->Fill(g, x, y, hs, vs, tw, th);
}


void ShapeType::Draw(Grafport *g, double x, double y, double hs, double vs,
	const TextShape *text, const string *fillcolor /* = NULL */) const
{
	double tw, th;
	if ( text && nameArea ) {
		tw = text->GetStringWidth();
		th = text->GetStringHeight();
//		Point c;
//		nameArea->GetCenter(c, x, y, hs, vs, tw, th);
//		text->SetPosition(c);
//		text->Draw();
	} else
		tw = th = 0.0;
	exterior->Draw(g, x, y, hs, vs, tw, th);
	if ( interior ) {
		string oldBackground(*g->GetBackgroundColor());
		if ( exterior->GetFillType() == Polygon::ALWAYS ||
		    (exterior->GetFillType() == Polygon::ON_DEMAND &&
		     NULL != fillcolor) )
			g->SetBackgroundColor(fillcolor);
		interior->Draw(g, x, y, hs, vs, tw, th);
		g->SetBackgroundColor(&oldBackground);
	}
}


void ShapeType::CorrectScale(double *phs, double *pvs,
	double tw, double th, bool constrainX, bool constrainY) const
{
	double hs, vs;
	if ( HasFixedWidth() || HasFixedHeight() ) {
		exterior->GetSize(&hs, &vs, *phs, *pvs, tw, th);
		if ( HasFixedWidth() ) {
			constrainY = true;
			if ( HasFixedHeight() )
				constrainX = true;
			else
				vs = *pvs;
		} else {
			hs = *phs;
			// if ( HasFixedHeight() ) /* must be true */
			constrainX = true;
		}
	} else {
		hs = *phs;
		vs = *pvs;
	}
	if ( hs < 0.0 )
		hs = -hs;
	if ( vs < 0.0 )
		vs = -vs;
	if ( hs < Shape::MIN_WIDTH )
		hs = Shape::MIN_WIDTH;
	if ( vs < Shape::MIN_HEIGHT )
		vs = Shape::MIN_HEIGHT;
	double aspectratio = hs / vs;
	if ( aspectratio < minAspectRatio ) {
		// calculate new values for hs, vs according to:
		// hs_new + vs_new = hs + vs
		// hs_new / vs_new = minAspectRatio
		// or, solve the linear equation system:
		// hs_new + vs_new = hs + vs
		// hs_new - minAspectRatio * vs_new = 0
		if ( constrainY )
			vs = hs / minAspectRatio;
		else {
			if ( ! constrainX )
				vs = (hs + vs) / (minAspectRatio + 1.0);
			hs = vs * minAspectRatio;
		}
	} else if ( maxAspectRatio > 0.0 && aspectratio > maxAspectRatio ) {
		// do the same, but for maxAspectRatio...
		if ( constrainY )
			vs = hs / maxAspectRatio;
		else {
			if ( ! constrainX )
				vs = (hs + vs) / (maxAspectRatio + 1.0);
			hs = vs * maxAspectRatio;
		}
	}
	*phs = hs;
	*pvs = vs;
}


bool ShapeType::IsHit(double x, double y, double hs, double vs,
	double tw, double th) const
{
	if ( tw && th && nameArea ) {
		DPoint pt;
		nameArea->CalcCentre().CalcPoint(&pt, x, y, hs, vs, tw, th);
		double dist = theApplication->GetConfig()->GetTextSelectDistance();
		if ( fabs(pt.x) * 2.0 < tw + dist
		    && fabs(pt.y) * 2.0 < th + dist )
			return True;
	}
	if ( exterior->IsInside(x, y, hs, vs, tw, th) ) {
		if ( interior && interior->IsHit(x, y, hs, vs, tw, th) )
			return True;
		if ( exterior->IsHit(x, y, hs, vs, tw, th) )
			return True;
	}
	return False;
}
