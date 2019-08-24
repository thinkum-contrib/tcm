//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _LINEEND_H
#define _LINEEND_H

#include "typename.h"
#include "dpoint.h"
class string;
class Grafport;


/// different line ending of a line
class LineEnd{
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	enum Type {EMPTY=1, OPEN_ARROW, FILLED_ARROW, DOUBLE_OPEN_ARROW,
		   DOUBLE_FILLED_ARROW, WHITE_CIRCLE, BLACK_CIRCLE,
		   WHITE_DIAMOND, BLACK_DIAMOND, WHITE_TRIANGLE,
		   BLACK_TRIANGLE};
	///
	enum {NUMTYPES = 11};
	///
	LineEnd();
	///
	LineEnd(Type t);
	///
	void SetType(Type t);
	///
	LineEnd::Type GetType() {return type;}

	///
	void SetLength(int l);
	///
	int GetLength() {return length;}
	///
	void SetWidth(int w);
	///
	int GetWidth() {return width;}

	/// the default width of a circle line end.
	static const int CIRCLE_WIDTH;

	/// default length of open arrow.
        static const int OPEN_ARROW_LENGTH;

        /// default width of open arrow.
        static const int OPEN_ARROW_WIDTH;

        /// default length of the sides of the arrow head
        static const int FILLED_ARROW_LENGTH;

        /// angle between each side and the line in degrees
        static const int FILLED_ARROW_ANGLE;
 
        /// percentage inset for base of arrow [0..1] (values +- 0.60 work well).
        static const double FILLED_ARROW_INSET;

	/// default width of a triangle
	static const int TRIANGLE_WIDTH;
	/// default length of a side of a triangle.
	static const int TRIANGLE_LENGTH;
	/// default width of a diamond.
	static const int DIAMOND_WIDTH;
	/// default length of a side of a diamond.
	static const int DIAMOND_LENGTH;
 
	///
        static const TypeName typeNames[];

	/// e.g. convert "OpenArrow" to OPEN\_ARROW.
	static Type String2Type(const string *s);

	/// e.g. convert OPEN\_ARROW to "OpenArrow".
	static void Type2String(Type t, string *s);

	/// draw the given line ending in the grafport.
	void Draw(Grafport *g, const DPoint *from, 
		const DPoint *to, DPoint *newEnd);

	///
	void static CalcDiamond(const DPoint *from, const DPoint *to,
				int len, int wd, DPoint *points);
	///
	void static CalcDirectionDiamond(const DPoint *from, const DPoint *to,
			const DPoint *apos, int len, int wd, DPoint *points);
	///
	static void CalcFilledArrowHead(const DPoint *from, const DPoint *to,
				int len, DPoint *points);
private:
	///
	Type type;
	///
	int length;
	///
	int width;
	///
	void DrawArrowHead(Grafport *g, const DPoint *from, 
		const DPoint *to, bool filled, int count, DPoint *newEnd);
	///
	void DrawOpenArrowHead(Grafport *g, const DPoint *from, 
		const DPoint *to, DPoint *newEnd);
	///
	void DrawFilledArrowHead(Grafport *g, const DPoint *from, 
		const DPoint *to, DPoint *newEnd);
	///
	void DrawExtraArrowHead(Grafport *g, 
		const DPoint *from, const DPoint *to, bool filled, 
		DPoint *newEnd);
	///
	void DrawCircle(Grafport *g, 
		const DPoint *from, const DPoint *to, 
		bool filled, DPoint *newEnd);
	///
	void DrawTriangle(Grafport *g, 
		const DPoint *from, const DPoint *to, 
		bool filled, DPoint *newEnd);
	///
	void DrawDiamond(Grafport *g, 
		const DPoint *from, const DPoint *to, 
		bool filled, DPoint *newEnd);

	///
	void SetSizes();
};
#endif
