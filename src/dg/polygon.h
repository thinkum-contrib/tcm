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

#ifndef _POLYGON_H
#define _POLYGON_H

#include "polypoint.h"
class NodeShape;

class Polygon {
public:
	static const Polygon BlackDot, FolderExterior, FolderNameArea,
		Circle, Box, Box1, TextBox, TextBox2, RoundedBox, RoundedBox1,
		SubtitleSq;

	// draw and fill type.
	enum DrawFillType { NEVER, ON_DEMAND, ALWAYS };

	///
	Polygon(List<const PolyPoint *> *c, DrawFillType ft = NEVER);

	///
	~Polygon();

	///
	DrawFillType GetFillType() const { return filltype; }

	///
	bool HasFixedWidth() const;

	///
	bool HasFixedHeight() const;

	///
	void Fill(Grafport *g, double x, double y, double hs, double vs,
		double tw, double th) const
	{
		IntDraw(g, NEVER, FillStyle::FILLED, x, y, hs, vs, tw, th);
	}
	///
	void Draw(Grafport *g, double x, double y, double hs, double vs,
		double tw, double th) const
	{
		IntDraw(g, ON_DEMAND, FillStyle::UNFILLED, x, y, hs, vs,
			tw, th);
	}
	///
	void DrawOutLine(Grafport *g, double x, double y, double hs, double vs,
		double tw, double th) const
	{
		IntDraw(g, ALWAYS, FillStyle::UNFILLED, x, y, hs, vs, tw, th);
	}

	///
	PolyPoint CalcCentre() const;

	///
	PolyPoint CalcTopLeft() const;

	///
	PolyPoint CalcBottomRight() const;

	/// Fit a rectangular text of size tw x th into the polygon.
	void FitText(double *phs, double *pvs, double tw, double th) const;

	/// Set the polygon exterior to size w x h.
	void SetSize(double *phs, double *pvs, double tw, double th,
		double w, double h) const;

	/// Gets the size of the polygon exterior.
	void GetSize(double *pw, double *ph, double hs, double vs,
		double tw, double th) const;

	/// Is (0,0) inside the polygon?
	bool IsInside(double x, double y, double hs, double vs,
		double tw, double th) const;
	/// Is (0,0) near to any visible polygon edge?
	bool IsHit(double x, double y, double hs, double vs, double tw,
		double th) const;
	/// Is the polygon, located in (0,0), contained in another one?
	bool IsContainedIn(double hs, double vs, double tw, double th,
		const Polygon *exterior, double ex, double ey,
		double ehs, double evs, double etw, double eth) const;

	///
	double GetLeftMost(double x, double y, double hs, double vs,
		double tw, double th) const;
	double GetTopMost(double x, double y, double hs, double vs,
		double tw, double th) const;
	double GetBottomMost(double x, double y, double hs, double vs,
		double tw, double th) const;
	double GetRightMost(double x, double y, double hs, double vs,
		double tw, double th) const;

	void GetLeft(PolyPoint *p) const;
	void GetRight(PolyPoint *p) const;
	void GetTop(PolyPoint *p) const;
	void GetBottom(PolyPoint *p) const;

	///
	DPoint GiveSnp(double dx, double dy, double x, double y,
		double hs, double vs, double tw, double th) const;
	DPoint GiveSnp(int order, int count, double dx, double dy,
		double hs, double vs, double tw, double th) const;
	DPoint GiveOrthoSnp(double dx, double dy,
		double hs, double vs, double tw, double th) const;
protected:
	/// Draws a polygon.
	void IntDraw(Grafport *g, DrawFillType ds, FillStyle::Type fs,
		double x, double y, double hs, double vs,
		double tw, double th) const;

	/// calculates coordinates of all points.
	DPoint *CalcPoints(double x, double y, double hs, double vs,
		double tw, double th) const;

	/// Is p inside the polygon?
	bool IntIsInside(const DPoint *plist, DPoint p) const;
private:
	///
	List<const PolyPoint *> *corners;

	/// pointers to the extreme points
	const PolyPoint *left, *right, *top, *bottom;

	///
	const DrawFillType filltype;

	///
	bool fixedCalculated;

	///
	bool fixedWidth;

	///
	bool fixedHeight;

	///
	void CalculateFixedSize();

	///
	void CalculateExtremePoint();
};

#endif
