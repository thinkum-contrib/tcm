//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
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

#ifndef _SHAPETYPE_H
#define _SHAPETYPE_H

class NodeShape;
#include "polygon.h"

/// shape type class, describes node shapes
class ShapeType {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ShapeType(int ct, double dw, double dh,
		double minar, double maxar, const Polygon *na,
		const Polygon *ca, const PolyPoint *ip, const PolyPoint *dp,
		const PolyPoint *mp, const Polygon *extr,
		const Polygon *intr = 0);

	///
	~ShapeType() {};

	///
	bool HasFixedName() const { return NULL == nameArea; }

	///
	bool HasFixedWidth() const { return exterior->HasFixedWidth(); }

	///
	bool HasFixedHeight() const { return exterior->HasFixedHeight(); }

	///
	void Fill(Grafport *g, double x, double y, double hs, double vs,
		const TextShape *text) const;
	///
	void Draw(Grafport *g, double x, double y, double hs, double vs,
		const TextShape *text, const string *fillcolor = NULL) const;

	void DrawOutLine(Grafport *g, double x, double y, double hs, double vs,
		double tw, double th) const
	{
		exterior->DrawOutLine(g, x, y, hs, vs, tw, th);
	}

	///
	bool IsInside(double x, double y, double hs, double vs,
		double tw, double th) const
	{
		return exterior->IsInside(x, y, hs, vs, tw, th);
	}
	/// Does the shape contain a child located in (0,0)?
	bool ContainsChild(double x, double y, double hs, double vs,
		double tw, double th,
		const ShapeType *cst, double chs, double cvs,
		double ctw, double cth) const
	{
		return cst->exterior->IsContainedIn(chs, cvs, ctw, cth,
			childArea, x, y, hs, vs, tw, th);
	}
	///
	bool IsHit(double x, double y, double hs, double vs,
		double tw, double th) const;

	///
	PolyPoint CalcTopLeft() const {
		return exterior->CalcTopLeft();
	}

	///
	PolyPoint CalcBottomRight() const {
		return exterior->CalcBottomRight();
	}

	///
	const Polygon *GetNameArea() const { return nameArea; }

	///
	const Polygon *GetChildArea() const { return childArea; }

	///
	const PolyPoint *GetIndexPoint() const { return indexPoint; }

	///
	const PolyPoint *GetDuplicatePoint() const { return duplicatePoint; }

	///
	const PolyPoint *GetMultiplicityPoint() const {
		return multiplicityPoint;
	}

	/// sets *phs and *pvs such that the exterior size becomes w x h.
	void SetSize(double *phs, double *pvs, double tw, double th,
		double w, double h) const
	{
		exterior->SetSize(phs, pvs, tw, th, w, h);
	}

	void GetSize(double *pw, double *ph, double hs, double vs,
		double tw, double th) const
	{
		exterior->GetSize(pw, ph, hs, vs, tw, th);
	}

	/// sets *phs and *pvs such that the name area becomes large enough.
	void FitText(double *phs, double *pvs, double tw, double th) const {
		nameArea->FitText(phs, pvs, tw, th);
	}

	double GetDefaultWidth() const {
		return defaultWidth;
	}

	double GetDefaultHeight() const {
		return defaultHeight;
	}

	double GetLeftMost(double x, double y, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GetLeftMost(x, y, hs, vs, tw, th);
	}

	double GetTopMost(double x, double y, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GetTopMost(x, y, hs, vs, tw, th);
	}

	double GetBottomMost(double x, double y, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GetBottomMost(x, y, hs, vs, tw, th);
	}

	double GetRightMost(double x, double y, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GetRightMost(x, y, hs, vs, tw, th);
	}

	void GetLeft(PolyPoint *p) const {
		exterior->GetLeft(p);
	}
	void GetRight(PolyPoint *p) const {
		exterior->GetRight(p);
	}
	void GetTop(PolyPoint *p) const {
		exterior->GetTop(p);
	}
	void GetBottom(PolyPoint *p) const {
		exterior->GetBottom(p);
	}

	DPoint GiveSnp(double dx, double dy, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GiveSnp(dx, dy, 0.0, 0.0, hs, vs, tw, th);
	}
	DPoint GiveSnp(int order, int count, double dx, double dy,
		double hs, double vs, double tw, double th) const
	{
		return exterior->GiveSnp(order, count, dx, dy, hs, vs, tw, th);
	}
	DPoint GiveOrthoSnp(double dx, double dy, double hs, double vs,
		double tw, double th) const
	{
		return exterior->GiveOrthoSnp(dx, dy, hs, vs, tw, th);
	}

	/// correct horizontal and vertical scale if necessary.
	void CorrectScale(double *phs, double *pvs, double tw, double th,
		bool constrainX, bool constrainY) const;

	int GetClassType() const {
		return classtype;
	}
protected:

private:
	///
	const int classtype;

	///
//	const double minHorizScale;

	///
//	const double minVertScale;

	///
//	const double maxHorizScale;

	///
//	const double maxVertScale;

	const double defaultWidth;
	const double defaultHeight;

	///
	const double minAspectRatio;

	///
	const double maxAspectRatio;

	///
	const Polygon * const nameArea;

	///
	const Polygon * const childArea;

	///
	const PolyPoint * const indexPoint;

	///
	const PolyPoint * const duplicatePoint;

	///
	const PolyPoint * const multiplicityPoint;

	///
	const Polygon * const exterior;

	const Polygon * const interior;
};
#endif
