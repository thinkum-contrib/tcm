//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _UR_LABELED_BOX
#define _UR_LABELED_BOX

#include "box.h"
 
/// box with extra label in Upper Right corner (PSD).
class URLabeledBox: public Box {
/*@Doc: {\large {\bf scope:} TPSD} */
public:
	///
	URLabeledBox(ShapeView *v, Grafport *g, double x, double y);
	///
	URLabeledBox(const URLabeledBox &c);
	///
	virtual ~URLabeledBox();
	/// 
	Shape *Clone() {return new URLabeledBox(*this);}
	///
	int GetClassType() const {return Code::UR_LABELED_BOX;}

	/// adjusts the label to a new place
//	void SetPosition(const Point *p, bool b); 	
	///
//	void SetSize(int w, int h);
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
 
	/// chooses the name or the UR label.
	TextShape *ChooseTextShape(int x, int y); 
	///
	bool HasTextShape(TextShape *t) const;
 
	/// update string of UR label.
	void UpdateURLabel(const string *s); 
	///
	void SetURLabel(const string *s) {urLabel->SetString(s);}
 
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
protected:
	///
	virtual void CalcPositionLabels();
private:
	///
	void DrawShape();
	///
	TextShape *urLabel;
};
#endif
