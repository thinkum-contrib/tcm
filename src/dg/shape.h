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
#ifndef _SHAPE_H
#define _SHAPE_H

#include "rectangle.h"
#include "lstring.h"
#include "thing.h"
class Subject;
class Grafport;
class ShapeView;
class TextShape;
class DiagramViewer;

/// (abstract) shape class, superclass of all possible shapes (graphics + text).
class Shape: public Thing {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// creates a shape at position (0,0) and size (0,0).
	Shape(ShapeView *s, Grafport *g); 	
	///
	bool IsShape() const {return True;}
	///
	virtual bool IsTextShape() const {return False;}
	///
	virtual Shape *Clone() = 0;

	/// Draws the shape: shape itself and its text and selection handles.
	virtual void Draw() = 0;

	/// Erases the shape: by redrawing it in XOR mode.
	virtual void Undraw() = 0;

	/// update position and redraw.
	virtual void UpdatePosition(const Point *position, bool snap=True); 

	/// update size and redraw.
	virtual void UpdateSize(int w, int h); 	

	/// update movement and redraw.
	virtual void UpdateMove(const Point *delta); 	

	/// update selection handles and redraw.
	virtual void UpdateSelect(bool s); 	

	/// update first selection handles and redraw.
	virtual void UpdateFirstSelect(bool s); 

	/// update color and redraw.
	virtual void UpdateColor(string *color); 

	///
	virtual void SetSelect(bool s) {selected = s;}
	///
	virtual void SetFirstSelect(bool s) {firstSelected = s; selected = s;}
	///
	bool IsFirstSelected() const {return firstSelected;}
	///
	void SetVisible(bool s) {visible = s;}
	///
	void SetSubject(Subject *s) {subject = s;}
	///
	virtual void SetView(ShapeView *v) {view = v;}
	///
	Subject *GetSubject() const {return subject;}
	///
	ShapeView *GetView() const {return view;}

	///
	virtual void SetGrafport(Grafport *g) {grafport = g;}
	///
	void SetColor(const string *c) {color = *c;}
	///
	const string *GetColor() const {return &color;}

	/// move position by delta.
	virtual void Move(const Point *delta); 	

	/// update size to make the shape fit the text shape strings.
	virtual void AdjustSize() {}

	/// Draw outline of the shape (when it is dragged).
	virtual void DrawOutLine(const Point *center) = 0; 

	/// intersection of boundary and line from given point to shape center.
	virtual Point GiveSnp(Point) const {return position;}

	/// As GiveSnp but takes into account distribution of multiple lines.
	virtual Point GiveSnp(Point, int, int, int &) {return position;}

	/// Calc the intersection of an orthogonal line with shape boundary. 
	virtual Point GiveOrthoSnp(Point to) const {return GiveSnp(to);}

	/// set n handle rectangles.
	void SetHandles(int n); 

	/// Return (x,y) handle hit (-1 if not, 0 when shape is line).
	virtual int HitHandles(int x, int y);

	/// returns whether (x,y) is geometrically in the shape.
	virtual bool ContainsPt(int x, int y); 

	///
	const Point *GetPosition() const {return &position;}
	///
	const Point *GetTopLeft() const {return &topleft;}
	///
	bool IsSelected() const {return selected;}
	///
	bool IsVisible() const {return visible;}
	///
	bool IsDuplicate() const {return duplicate;}
	///
	int GetWidth() const {return width;}
	///
	int GetHeight() const {return height;}

	/// minimal height of a shape.
	static const int MIN_HEIGHT;
	/// minimal width of a shape.
	static const int MIN_WIDTH;

	/// draw duplication indicator (asterisk).
	virtual void DrawDuplicate() = 0;
	///
	void UndrawDuplicate() {DrawDuplicate();}
	///
	void SetDuplicate(bool b) {duplicate=b;}
	/// set whether shape is a duplicate shape.
	void UpdateDuplicate(bool b);
 
	///
	virtual bool IsLine() const {return False;}

	///
	virtual bool IsNodeShape() const { return False; }

	/// smallest x-coordinate in shape.
	virtual int GetLeftMost() const {return position.x - width / 2;}
	/// smallest y-coordinate in shape. 
	virtual int GetTopMost() const {return position.y - height / 2;}
	/// largest x-coordinate in shape.
	virtual int GetRightMost() const {return position.x + width / 2;}
	/// largest y-coordinate in shape.
	virtual int GetBottomMost() const {return position.y + height / 2;}

	/// write members of shape to file.
	void WriteMembers(OutputFile *ofile); 

	/// read and parse shape members from file ofile.
	bool ReadMembers(InputFile *f, double format); 

	/// update subject reference from assocList.
	virtual bool SetAssocSubject(AssocList *);

	/// update view reference from assocList.
	bool SetAssocView(AssocList *);

	/// Check if subject exists as graph element and that view exists.
	bool CheckReferences();

	/// update the strings of text shapes with the subject strings.
	virtual void SetTextShape() {}

	/// return a text shape near (x,y).
	virtual TextShape *ChooseTextShape(int, int) = 0;

	/// return the text shape at (x,y).
	virtual TextShape *HitTextShape(int, int) = 0;

	/// Returns if (x,y) is in text-area.
	virtual bool InTextArea(int x, int y) = 0;
 
	/// true if shape's name text shape contains 's'.
	virtual bool HasNameString(const string *, bool, bool) 
		const {return False;}

	/// true if some of shape's text shapes contains 's'.
	virtual bool HasString(const string *, bool, bool) 
		const {return False;}

	/// put all text shapes containing 's' in the list l.
	virtual bool HasString(const string *, bool, bool,
		List<TextShape *> *) {return False;}

	/// return if it has t as one of the text shapes.
	virtual bool HasTextShape(TextShape *t) const = 0;

	/// move the shape over exact delta, without snap.
	virtual void MoveRaw(const Point *delta);

	/// size of selection handle.
	static const int HANDLE_WIDTH;

protected:
	///
	Grafport *GetGrafport() const {return grafport;}

	/// set attributes of grafport before drawing.
	virtual void SetDrawAttributes();

	/// set attributes of grafport for drawing outlines.
	void SetOutlineAttributes();

	/// set the size of the shape (with a minimum).
	virtual void SetSize(int w, int h);

	/// set the position (takes into account the grid when snap=True).
	virtual void SetPosition(const Point *position, bool snap=True);

	/// align the shape to the grid (by its topleft).
	virtual void SnapTopleft();

	/// align the shape to the grid (by its center).
	virtual void SnapPosition();

	///
	void SetWidth(int w) {width=w;}
	///
	void SetHeight(int h) {height=h;}
	///
	void SetNrHandles(int n) {nrHandles=n;}
	///
	DiagramViewer *GetViewer() const {return viewer;}

	/// change position so that shape has only positive coordinates.
	void PositiveCoord();

	/// minimal nr. of handles.
	static const int MIN_HANDLES;

	/// Draw the handles if object is (first) selected.
	virtual void DrawSelect();

	/// Draw grey handles if the object is selected.
	virtual void DrawGraySelect(); 	

	///
	virtual void UndrawSelect() {DrawSelect();}
	///
	virtual void UndrawGraySelect() {DrawGraySelect();}

	/// set the top-left and position (take into account width and height).
	void SetTopLeft(const Point *topLeft);

	/// set all handle rectangles. 
	virtual void SetPositionHandles();

	///
	void ForcePosition(const Point *position);

	/// the position and size of the selection handles.
	Rectangle handles[8];

private:
	/// the element in the graph that the shape represents.
	Subject *subject; 

	/// the diagram viewer (manages all views and shapes).
	DiagramViewer *viewer;

	/// the particular view in which shape resides.
	ShapeView *view;

	/// grafport to draw the shape.
	Grafport *grafport;

	/// the center position of the shape.
	Point position; 

	/// the top-left position of the shape.
	Point topleft;

	/// the height of the shape.
	int height; 	

	/// the width of the shape.
	int width; 	

	/// whether the shape is selected.
	bool selected; 	

	/// whether the shape is selected as first.
	bool firstSelected; 

	/// the shape is visible?
	bool visible;

	/// the color of the shape.
	string color;

	/// the number of handles (<= 8).
	int nrHandles;

	/// Subject of shape has more than one representation?
	bool duplicate;

	/// Has the shape always a minimal size?
	virtual bool HasMinSize() {return False;}
};
#endif
