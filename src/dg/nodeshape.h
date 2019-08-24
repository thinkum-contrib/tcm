//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#ifndef _NODESHAPE_H
#define _NODESHAPE_H

#include "gshape.h"
#include "fillstyle.h"
#include "shapetype.h"

/// (abstract) graphical node shape class, suited for the generic shape facility
class NodeShape: public GShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// 
	NodeShape(ShapeView *v, Grafport *g, double x, double y,
		const ShapeType *st);
	///
	NodeShape(const NodeShape &c, const ShapeType *st = NULL);

	///
	virtual ~NodeShape();

	///
	virtual bool IsNodeShape() const { return True; }

	///
	TextShape *GetIndexLabel() const {return indexLabel;}
	/// update string of label.
	virtual void SetIndexLabel(const string *s);
	/// update string of label and redraw.
	void UpdateIndexLabel(const string *s);
	///
	bool IsFixedIndexLabel() const { return fixedIndexLabel; }
	///
	void SetFixedIndexLabel(bool b) { fixedIndexLabel = b; }
	/// calculate index label with parent indication.
	void CalcCompleteIndex(string *s) const;

	///
	FillStyle::Type GetFillStyle() const { return fillStyle; }
	///
	void SetFillStyle(FillStyle::Type f) { fillStyle = f; }
	///
	void UpdateFillStyle(FillStyle::Type f);
	///
	const string *GetFillColor() const { return &fillColor; }
	///
	void SetFillColor(const string *c) {fillColor=*c;}
	///
	void UpdateFillColor(const string *c);


	/// adjusts also the handles (and new size)
	/* virtual */ void SetNameString(const string *s);

	/// adjusts also the label to a new place
	/* virtual */ void SetPosition(const Point *p, bool snap=True);

	/// adjusts also the label to a new place
	/* virtual */ void SetSize(int w, int h);

	///
	void SetGrafport(Grafport *g);
	///
	void SetView(ShapeView *v);
	///
	/* virtual */ void SetFont(XFont *ft);
	///
	void SetTextColor(const string *color);
	///
	/* virtual */ void SetTextShape();


	/// draws the graphic part of the shape.
	/* virtual */ void DrawShape();

	/// draws the outline with a specific size.
	virtual void DrawOutLine(double x, double y, double w, double h);
	///
	/* virtual */ void DrawOutLine(const Point *centre);
	///
	void CorrectScale(double *pwidth, double *pheight,
		bool constrainX, bool constrainY) const
	{
		GetShapeType()->CorrectScale(pwidth, pheight,
			GetName()->GetStringWidth(),
			GetName()->GetStringHeight(),
			constrainX, constrainY);
	}

	/// intersection of boundary and line from given point to shape center.
	/* virtual */ Point GiveSnp(Point to) const;

	/// As GiveSnp but takes into account distribution of multiple lines.
	/* virtual */ Point GiveSnp(Point to, int order, int count, int &code);

	/// Calc the intersection of an orthogonal line with shape boundary. 
	/* virtual */ Point GiveOrthoSnp(Point to) const;

	/// draw duplicate asterisk.
	/* virtual */ void DrawDuplicate();

	/// draw multiplicity number.
	void DrawMultiplicity();

	/// Returns true if (x,y) is in the shape.
	/* virtual */ bool ContainsPt(int x, int y);

	/// Returns true is ns is in the child area.
	/* virtual */ bool ContainsChild(const GShape *gs) const;

	/// Returns true if (x,y) is in text-area.
	bool InTextArea(int x, int y);

	///
	/* virtual */ int HitHandles(int x, int y);

	///
	/* virtual */ TextShape *ChooseTextShape(int x, int y);

	/// update size to make it fit the text shapes.
	/* virtual */ void AdjustSize();

	///
	void SetResizable(bool b) { resizable = b; }
	///
	bool IsResizable() const {
		return ! (shapetype->HasFixedWidth()
			  && shapetype->HasFixedHeight());
	}

	///
	const ShapeType *GetShapeType() const { return shapetype; }
	///
	void SetShapeType (const ShapeType *st) { shapetype = st; }

	///
	/* virtual */ int GetLeftMost() const;
	/* virtual */ int GetTopMost() const;
	/* virtual */ int GetBottomMost() const;
	/* virtual */ int GetRightMost() const;

	///
	/* virtual */ int GetClassType() const {
		return shapetype->GetClassType();
	}

	///
	/* virtual */ bool SetAssocSubject(AssocList *al);

	/// write it to file.
	void WriteMembers(OutputFile *ofile);

	/// read and parse it from file.
	bool ReadMembers(InputFile *ifile, double format);

//	///
//	void ForceSize(int w, int ht) {GShape::SetSize(w, ht);}

	///
	bool HasTextShape(TextShape *t) const;
	///
	/* virtual */ bool HasString(const string *s, bool sens, bool sub) const;
	///
	/* virtual */ bool HasString(const string*, bool, bool, List<TextShape *> *);
protected:
	/// draw name + index text shape.
	/* virtual */ void DrawTextShapes();

	/// calculate position of index label and text label
	virtual void CalcPositionLabels();
 
	///
	/* virtual */ void SetPositionHandles();
private:
	///
	const ShapeType *shapetype;
	///
	FillStyle::Type fillStyle;
	///
	string fillColor;
	///
	TextShape *indexLabel;
	///
	bool fixedIndexLabel;
	///
	bool resizable;
};
#endif
