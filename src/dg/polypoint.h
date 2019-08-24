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
////////////////////////////////////////////////////////////////////////////////

#ifndef _POLYPOINT_H
#define _POLYPOINT_H

#include "dpoint.h"
#include "textshape.h"
class Grafport;

class PolyPoint {
public:
	static const PolyPoint TopLeft, Top, TopRight, Right,
		BottomRight, Bottom, BottomLeft, Left,
		TopLeft1, Top1, TopRight1, Right1,
		BottomRight1, Bottom1, BottomLeft1, Left1,
		FolderTR1, FolderTR2, FolderTR3, FolderLeft,
		TopLeftInv, TopRightInv, BottomLeftInv, BottomRightInv,
		TopArc, RightArc, BottomArc, LeftArc,
		TopAbsArc, RightAbsArc, BottomAbsArc, LeftAbsArc,
		TopArc1, RightArc1, BottomArc1, LeftArc1,
		TopLeftSq, TopSq, TopRightSq, RightSq,
		BottomRightSq, BottomSq, BottomLeftSq, LeftSq,
		TopSqArc, RightSqArc, BottomSqArc, LeftSqArc,
		TopLeftTxt, BottomLeftTxt, BottomRightTxt, TopRightTxt,
		TopLeftTxt2, BottomLeftTxt2, BottomRightTxt2, TopRightTxt2,
		RoundedBoxTTL, RoundedBoxTLL, RoundedBoxBLL, RoundedBoxBBL,
		RoundedBoxBBR, RoundedBoxBRR, RoundedBoxTRR, RoundedBoxTTR,
		RoundedBoxTTL1, RoundedBoxTLL1, RoundedBoxBLL1, RoundedBoxBBL1,
		RoundedBoxBBR1, RoundedBoxBRR1, RoundedBoxTRR1, RoundedBoxTTR1,
		Index, Dupli, Multi,
		IndexSq, DupliSq, MultiSq,
		SubtitleTLSq, SubtitleTRSq, SubtitleBLSq, SubtitleBRSq,
		BottomLeftSqInv, BottomSqInv, BottomRightSqInv;
	///
	PolyPoint(double xu, double xhs, double xvs, double xns, double yu,
		double yhs, double yvs, double yns, bool ev = false,
		bool ea = false);

	///
	~PolyPoint() { }

	///
	bool HasFixedWidth() const { return 0.0 == XHorizScaled && 0.0 == XVertScaled; }

	///
	bool HasFixedHeight() const { return 0.0 == YVertScaled && 0.0 == YHorizScaled; }

	///
	void Write(Grafport *g, double x, double y, double hs, double vs,
		TextShape *text) const;

	///
	void CalcPoint(DPoint *p, double x, double y, double hs, double vs,
		double tw, double th) const
	{
		p->Set(x + XUnscaled + hs * XHorizScaled + vs * XVertScaled + tw * XNameScaled,
		      y + YUnscaled + hs * YHorizScaled + vs * YVertScaled + th * YNameScaled);
	}
	/// looks for hs and vs s.t. corner comes as near to p as possible:
	void CalcScale(const DPoint *p, double x, double y,
		double *hs, double *vs,	double tw, double th,
		bool constrainX, bool constrainY);

	///
	bool operator <(const PolyPoint &p) const {
		/* returns true if this is to the left of p */
		if ( XHorizScaled != p.XHorizScaled )
			return XHorizScaled < p.XHorizScaled;
		if ( XNameScaled != p.XNameScaled )
			return XNameScaled < p.XNameScaled;
		if ( XVertScaled != p.XVertScaled )
			return XVertScaled < p.XVertScaled;
		return XUnscaled < p.XUnscaled;
	}

	///
	bool operator ^(const PolyPoint &p) const {
		/* returns true if this is to the top of p */
		if ( YVertScaled != p.YVertScaled )
			return YVertScaled < p.YVertScaled;
		if ( YNameScaled != p.YNameScaled )
			return YNameScaled < p.YNameScaled;
		if ( YHorizScaled != p.YHorizScaled )
			return YHorizScaled < p.YHorizScaled;
		return YUnscaled < p.YUnscaled;
	}

	double GetXUnscaled() const { return XUnscaled; }
	double GetXHorizScaled() const { return XHorizScaled; }
	double GetXVertScaled() const { return XVertScaled; }
	double GetXNameScaled() const { return XNameScaled; }

	double GetYUnscaled() const { return YUnscaled; }
	double GetYHorizScaled() const { return YHorizScaled; }
	double GetYVertScaled() const { return YVertScaled; }
	double GetYNameScaled() const { return YNameScaled; }

	void SetXUnscaled(double xu) { XUnscaled = xu; }
	void SetXHorizScaled(double xh) { XHorizScaled = xh; }
	void SetXVertScaled(double xv) { XVertScaled = xv; }
	void SetXNameScaled(double xn) { XNameScaled = xn; }

	void SetYUnscaled(double yu) { YUnscaled = yu; }
	void SetYHorizScaled(double yh) { YHorizScaled = yh; }
	void SetYVertScaled(double yv) { YVertScaled = yv; }
	void SetYNameScaled(double yn) { YNameScaled = yn; }

	bool EdgeIsArc() const { return edgeIsArc; }
	bool EdgeIsVisible() const { return edgeVisible; }
protected:
private:
	///
	double XUnscaled;

	///
	double XHorizScaled;

	///
	double XVertScaled;

	///
	double XNameScaled;

	///
	double YUnscaled;

	///
	double YHorizScaled;

	///
	double YVertScaled;

	///
	double YNameScaled;

	/// Is the edge to the next point in the polygon visible?
	const bool edgeVisible;

	/// Is the edge to the next point in the polygon an arc?
	const bool edgeIsArc;
};

#endif
