//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _UCDSINGLECLASSBOX_H
#define _UCDSINGLECLASSBOX_H

#include "box.h"
#include "stickman.h"

/// Box for representing actor classes in a UCD.
class UCDSingleClassBox: public Box {
/*@Doc: {\large {\bf scope:} TUCD} */
public:
	///
	UCDSingleClassBox(ShapeView *v, Grafport *g, double x, double y);
	///
	UCDSingleClassBox(const UCDSingleClassBox &s);
	///
	UCDSingleClassBox(const StickMan &s);
	///
	~UCDSingleClassBox();
	///
	Shape *Clone() {return new UCDSingleClassBox(*this);}
	///
        int GetClassType() const {return Code::UCD_SINGLE_CLASS_BOX;}
	///
//	void SetSize(int w, int h);
        ///
//	void SetPosition(const Point *p, bool snap);
	///
        void SetFont(XFont *ft);
        ///
        void SetTextColor(const string *color);
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
        ///
        TextShape *ChooseTextShape(int x, int y);
        ///
        void AdjustSize();
	///
        bool SetAssocSubject(AssocList *);
protected:
        ///
        void CalcPositionLabels();
private:
        ///
        void DrawTextShapes();
        ///
        int RequiredHeight();
	///
	int RequiredWidth();
        ///
        void CalcPositionStereotypeLabel();

        ///
        static const int TEXTMARGIN;
        ///
        TextShape *stereotypeLabel;
};
#endif
