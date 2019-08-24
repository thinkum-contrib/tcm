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
#ifndef _DOUBLEBOX_H
#define _DOUBLEBOX_H

#include "box.h"
 
/// (abstract) box with two compartments: 1st for name, 2nd for a label list.
class DoubleBox: public Box {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DoubleBox(ShapeView *v, Grafport *g, double x, double y,
		double w, double h);
	///
	DoubleBox(const DoubleBox &s);
	///
	DoubleBox(const NodeShape &s);
	///
	virtual ~DoubleBox();
	///
	Shape *Clone() {return new DoubleBox(*this);}
	///
	/* virtual */ int GetClassType() const { return Code::DOUBLE_BOX; }
	///
//	void SetSize(int w, int h);
	///
//	void SetPosition(const Point *p, bool snap=True);
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;
	///
	void AdjustSize();
	/// update or insert string of n-th label.
	void UpdateLabel(const string *s, unsigned n, bool update);
	///
	TextShape *GetLabel(unsigned n);
	///
	unsigned NrLabels() {return labels->count();}
	///
	bool SetAssocSubject(AssocList *);
	///
	void SetTextShape();
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	/// contains s as string (case sensitive, substring).
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasString(const string*, bool, bool, List<TextShape *> *list);
	///
	LineStyle::Type GetSeparatorLineStyle() const 
		{return separatorLineStyle;}
	///
	void SetSeparatorLineStyle(LineStyle::Type x) 
		{separatorLineStyle=x;}
	///
	int GetInitialHeight() const {return initialHeight;}
protected:
	///
//	void DrawShape();
	///
	void DrawTextShapes();
	///
	virtual int RequiredHeight();
	/// calculates name position in 1st compartiment, labels in 2nd.
	virtual void CalcPositionLabels(); 
	///
	virtual void AdjustSizes(const string *s);
	/// 
	List<TextShape *> *GetLabels() {return labels;} 
	///
	static const int TEXTMARGIN;
	///
	string labelDescription;
	///
	int initialHeight;
private:
	/// the list of labels in the second compartiment.
	List<TextShape *> *labels; 
	/// line style of separator line (between name and labels).
	LineStyle::Type separatorLineStyle;
	///
	void Init();
};
#endif
