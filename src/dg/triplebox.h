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
#ifndef _TRIPLEBOX_H
#define _TRIPLEBOX_H

#include "doublebox.h"

/// three compartment box: 1st for name, 2nd for labels, 3rd for labels2.
class TripleBox: public DoubleBox {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	TripleBox(ShapeView *v, Grafport *g, int x, int y, int w, int h);
	///
	TripleBox(const TripleBox &s);
	///
	TripleBox(const DoubleBox &s);
	///
	TripleBox(const Box &s);
	///
	TripleBox(const NodeShape &s);
	///
	virtual ~TripleBox();
	///
	int GetClassType() const {return Code::TRIPLE_BOX;}
	///
	Shape *Clone() { return new TripleBox(*this);}
	///
	TextShape *ChooseTextShape(int x, int y);
	///
	bool HasTextShape(TextShape *t) const;
	/// update or insert string of n-th label2.
	void UpdateLabel2(const string *s, unsigned n, bool update); 
	///
        TextShape *GetLabel2(unsigned n);
	///
	unsigned NrLabels2() {return labels2->count();}
	///
	void SetTextShape();
	///
	void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
	///
	void AdjustSize();
	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	/// text shape contains s as string.
	bool HasString(const string *s, bool sens, bool sub) const;
	///
	bool HasString(const string*, bool, bool, List<TextShape *> *);
	///
	LineStyle::Type GetSeparator2LineStyle() const
		{return separator2LineStyle;}
	///
	void SetSeparator2LineStyle(LineStyle::Type x)
		{separator2LineStyle=x;}
protected:
	///
	void DrawShape();
	///
	void DrawTextShapes();
	///
	int RequiredHeight();
	///
	int DoubleBoxHeight();
	///
	void CalcPositionLabels();
	///
	void CalcPositionLabels2();
	///
	void AdjustSizes(const string *s);
	///
	List<TextShape *> *GetLabels2() {return labels2;}
	///
	string label2Description;
private:
	/// the list of labels2 in the third compartment.
	List<TextShape *> *labels2; 
	///
	LineStyle::Type separator2LineStyle;
	///
	void Init();
};
#endif
