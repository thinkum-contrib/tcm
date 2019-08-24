//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
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
//-----------------------------------------------------------------------------
#ifndef _LIFELINE_H
#define _LIFELINE_H

#include "nodeshape.h"

/// LifeLine shape class.
class LifeLine: public NodeShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	static const int LIFELINE_WIDTH;
	static const int LIFELINE_HEIGHT;
	///
	LifeLine(ShapeView *v, Grafport *g, double x, double y);
	///
	LifeLine(const NodeShape &c);
	///
	virtual Shape *Clone() {return new LifeLine(*this);}
	///
	int GetClassType() const {return Code::SSD_SINGLE_OBJECT_BOX;}
	///
	void DrawShape();
	///
	void DrawOutLine(double x, double y, double w, double h);
	///
	void DrawOutLine(const Point *center, double t);
	///
	void DrawOutLineTail(const Point *center, double t);
	///
	void DrawOutLineFOC(double startFOC, double endFOC);
	///
	void UndrawShape();
	///
	TextShape *ChooseTextShape(int x, int y);
	///
//	TextShape *HitTextShape(int x, int y);

	/// intersection of boundary and line from given point to anchorpoint
	/* virtual */ Point GiveSnp(Point to) const;

	/// intersection of boundary and line from given point to anchorpoint
	/* virtual */ Point GiveAnchorSnp(Point a, Point to) const;

	/// As GiveSnp but takes into account distribution of multiple lines.
	/* virtual */ Point GiveSnp(Point to, int order, int count, int &code);

	///
	/* virtual */ Point GiveOrthoSnp(double dx, double dy, 
			double hs, double vs, double tw, double th) const;
	///
	/* virtual */ Point GiveOrthoSnp(Point p) const;
	
	///
	bool ContainsPt(int x, int y);
	///
	bool PtInFOCblock(int x, int y) const;
	///
	bool PtInFOCblock(int x, int y, int *start, int *end) const;
	///
	bool PtInFOCarea(int x, int y) const;
	///
	bool IsOverlappingFOC(int startFOC, int endFOC) const;

	///
	int GetEndPositionY() const {return endPosition.y;}
	///
	void SetEndPositionY(int y) {std::cout << " LifeLine::SetEndPosition(" << y << ")" << std::endl << std::flush; endPosition.y = y;}

	///
	/* virtual */ void SnapPosition();
	///
	/* virtual */ void SetPosition(const Point *p, bool snap=True);
	///
	/* virtual */ void SetPositionHandles();

	//??????????????????????????????????
	void UndrawHandles();
	//??????????????????????????????????

	//Aleister7
	bool IsOverlappingAnotherFOC(int prevStartFOC, int prevEndFOC,
					int startFOC, int endFOC);

protected:
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
	///
//	** virtual ** void SetPositionHandles();
private:
	///
	static const ShapeType llType;
	///
	Point endPosition;
	///
	Point prevPosition;
	///
	bool destructive;
};
#endif
