//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#ifndef _MINIELLIPSE_H
#define _MINIELLIPSE_H

#include "ellipse.h"

/// mini-ellipse shape class.
class MiniEllipse: public Ellipse {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	MiniEllipse(ShapeView *v, Grafport *g, double x, double y);
	///
        MiniEllipse(const MiniEllipse &c);
	///
        MiniEllipse(const NodeShape &c);
	///
	Shape *Clone() {return new MiniEllipse(*this);}
	///
	enum NamePositionType {TOP, BOTTOM, LEFT, RIGHT, CENTER};
	///
	void SetNamePosition(NamePositionType t) {namePosition=t;}
	///
	int GetClassType() const {return Code::MINI_ELLIPSE;}
	///
	void SetPosition(const Point *p, bool snap);
	///
	void SetName(const string *s);
	///
	void SetFont(XFont *f);
	///
	void SetAlignment(TextAlign::Type t);
	///
	void SetSize(int w, int h);
	///
	void SetTextShape();
private:
	///
	void Init();
	///
        bool HasMinSize() {return True;}
	///
	void CalcPositionName();
	///
	NamePositionType namePosition;
};
#endif
