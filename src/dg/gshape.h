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
#ifndef _GSHAPE_H
#define _GSHAPE_H

#include "linestyle.h"
#include "textshape.h"
#include "shape.h"
class Node;

// Each GShape has a name TextShape. Some derived classes of GShape
// can have additional TextShapes. Therefore, sometimes, in the comments
// we speak about text shapes.

/// (abstract) graphical shape class, superclass of box, ellipse, line etc.
class GShape: public Shape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// constructor, creates shape at position (x,y).
	GShape(ShapeView *v, Grafport *g, int x, int y); 
	/// 
	GShape(const GShape &);
	///
	virtual ~GShape();

	///
	void Draw();
	///
	void Undraw();

	/// draw the shape and all child shapes
	void DrawWithChildren();
	/// undraw the shape and all child shapes
	void UndrawWithChildren();

	/// draw the shape.
	virtual void DrawShape() = 0;
	///
	virtual void UndrawShape() {DrawShape();}

	/// 
	virtual void DrawTextShapes() {name->Draw();}
	///
	virtual void UndrawTextShapes() {DrawTextShapes();}

	/// update string of name text shape and redraw.
	virtual void UpdateNameString(const string *s);

	/// update subject's parent and redraw.
	virtual void UpdateParent(Node *parent);

	/// 
	virtual void SetNameString(const string *s) {name->SetString(s);}
	/// 
	const string *GetNameString() {return name->GetString();}

	///
	TextShape *GetName() const {return name;}
	/// 
	virtual void SetTextShape(); 
	/// select this shape and its text shapes are selected.
	virtual void SetSelect(bool s);

	///
	unsigned GetLineWidth() const {return lineWidth;}
	///
	void SetLineWidth(unsigned n) {lineWidth=n;}
	///	
	void UpdateLineWidth(unsigned n);

	///
	LineStyle::Type GetLineStyle() const {return lineStyle;}
	///
	void SetLineStyle(LineStyle::Type x) {lineStyle=x;}
	///
	void UpdateLineStyle(LineStyle::Type x);

	///
        const string *GetTextColor() const {return name->GetColor();}
	///
	void UpdateTextColor(const string *c);
 
	/// Returns if gs is contained in the child area of this shape.
	virtual bool ContainsChild(const GShape * /* gs */ ) const
	{
		return False;
	}

	/// Returns if (x,y) is in name, and if so returns name.
	virtual TextShape *HitTextShape(int x, int y);

	/// return if it has t as one of the text shapes.
	virtual bool HasTextShape(TextShape *t) const {return name==t;}

	/// refinements of those shape members.
	virtual int GetLeftMost() const; 
	///
	virtual int GetTopMost() const;
	///
	virtual int GetRightMost() const;
	///
	virtual int GetBottomMost() const;

	///
	bool IsFixedName() {return fixedName;}
	///
	void SetFixedName(bool b) {fixedName=b;}
	
	/// set grafport of itself and its text shapes.
	virtual void SetGrafport(Grafport *g);

	/// set view of itself and its text shapes.
	virtual void SetView(ShapeView *v);

	/// update font and redraw.
	virtual void UpdateFont(XFont *ft);

	/// update text alignments and redraw.
        virtual void UpdateAlignment(TextAlign::Type alignment);

	/// return a text shape near (x,y).
	virtual TextShape *ChooseTextShape(int, int);

	/// react on movement of some text shape.
	virtual void NotifyTextMove(TextShape *) {}

	/// return font of the textshapes (all textshapes have same font).
	XFont *GetFont() const {return name->GetFont();}

	///
	TextAlign::Type GetAlignment() const {return name->GetAlignment();}

	/// return if name text shape contains 's'.
	virtual bool HasNameString(const string *s, bool c1, bool c2) const {
		return fixedName? 0:name->HasString(s, c1, c2); }

	/// return if some text shape contains 's'.
	virtual bool HasString(const string *s, bool c1, bool c2) const {
		return fixedName?0:name->HasString(s, c1, c2); }

	/// put all textshapes containing 's' in the list l.
	virtual bool HasString(const string *s, bool cI, bool aS, 
		List<TextShape *> *l) {
			return fixedName? 0:name->HasString(s, cI, aS, l);}

	/// Check also that name reference is ok.
	bool CheckReferences();
protected:

	/// set fonts of text shapes.
	virtual void SetFont(XFont *ft) {name->SetFont(ft);}

	/// set color of text shapes.
	virtual void SetTextColor(const string *c) {name->SetColor(c);}

	/// write line width and style to file.
	void WriteGraphicsPart(OutputFile *ofile);

	/// read line width and style from file.
	bool ReadGraphicsPart(InputFile *ifile, double format);

	/// write font and alignment to file.
	void WriteTextPart(OutputFile *ofile);

	/// read and parse font and alignment from file.
	bool ReadTextPart(InputFile *ifile, double format);

	///
	virtual void SetDrawAttributes();

	/// set alignments of text shapes.
	virtual void SetAlignment(TextAlign::Type a) {
		name->SetAlignment(a);}

	/// snap at position and text shapes are moved with.
	virtual void SnapPosition(); 

	/// snap at topleft and text shapes are moved with.
	virtual void SnapTopleft(); 

private:
	/// the name text shape of the Gshape
	TextShape *name;

	/// line width.
	unsigned lineWidth;

	/// line style.
	LineStyle::Type lineStyle;

	/// is gshape filled?
//	bool filled;
	// (not used. dj)

	/// can name be edited?
	bool fixedName;
};
#endif
