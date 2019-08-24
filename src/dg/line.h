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
//------------------------------------------------------------------------------
#ifndef _LINE_H
#define _LINE_H

#include "llist.h"
#include "gshape.h"
#include "lineend.h"
#include "readdirection.h"
class InputFile;
class OutputFile;

// A line is a shape connecting two other shapes (not lines),
// and having two or more points (which form the segments of the
// line. The first and last point are equal to the connection points
// to the connected shapes. A line can be drawn as one or more
// straight line segments, or as a bezier curve. In the latter
// case the line should contain exactly four points.

/// line shape class.
class Line: public GShape {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		List<Point *> *line, bool Curved);
	///
	Line(ShapeView *v, Grafport *g, GShape *n1, GShape *n2, 
		bool Curved);
	///
	Line(const Line &s);
	///
	Shape *Clone() {return new Line(*this);}
	///
	virtual ~Line();

	///
	bool IsCurved() const {return curved;}
	///
	void UpdateCurve(bool b);

	/// empty (line has no independent position).
	void UpdatePosition(const Point *p, bool snap=True);

	/// empty (line has no independent position).
	void SetPosition(const Point *p, bool snap=True);

	/// empty, because line has no outline.
	void DrawOutLine(const Point *) {}

	/// returns if (x,y) is on one of the segments of line.
	bool ContainsPt(int x, int y);

	/// returns handle-nr if (x,y) hits a handle, otherwise -1.
	int HitHandles(int x, int y); 

	/// yep.
	bool IsLine() const {return True;}

	/// count and order are used to determine whether
	unsigned int GetCount() const {return count;} 

	/// more than one line connect the same pair of shapes.
	unsigned int GetOrder() const {return order;} 

	///
	void SetOrder(unsigned int i) {order = i;}
	///
	void SetCount(unsigned int i) {count = i;}

	/// fromShape and toShape are the connected shapes.
	GShape *GetFromShape() const {return fromShape;} 
	///
	GShape *GetToShape() const {return toShape;}

	///
	void SetFromShape(GShape *n) {fromShape = n;}
	///
	void SetToShape(GShape *n) {toShape = n;}

	///
	unsigned int NrPoints() const {return line->count();}

	/// 'line' is a list of points.
	List<Point *> *GetLine() const {return line;}

	/// get left and rigth line segments of point pt (if they exist).
	bool GetSegments(Point pt, Point *pt1, Point *pt2);

	/// get line segment n (if it exists).
	bool GetSegment(int n, Point *pt1, Point *pt2);

	/// get line segment n (if it exists).
	bool GetSegment(int n, DPoint *pt1, DPoint *pt2);

	/// returns if (x,y) is in text area (used for edit cursor).
	virtual bool InTextArea(int x, int y);

	///
	void SetEnd1(LineEnd::Type t) {end1.SetType(t);}
	///
	void SetEnd2(LineEnd::Type t) {end2.SetType(t);}
	///
	void UpdateEnd1(LineEnd::Type t);
	///
	void UpdateEnd2(LineEnd::Type t);
	///
	LineEnd::Type GetEnd1() {return end1.GetType();}
	///
	LineEnd::Type GetEnd2() {return end2.GetType();}

	///
	int GetLeftMost() const; 
	///
	int GetTopMost() const;
	///
	int GetRightMost() const;
	///
	int GetBottomMost() const;

	/// set last point of line to top of toShape.
	void SetToTop(); 
	/// set first point of line to top of fromShape.
	void SetFromTop();
	/// set last point of line to bottom of toShape.
	void SetToBottom();
	/// set first point of line to bottom of fromShape.
	void SetFromBottom();

	/// recalculates position and redraws the line.
	void UpdatePosition(); 

	/// Define a position for the line (the center of the name of the line).
	virtual void CalcPosition() {CalcPositionName();}

	/// Calculate begin and end-points (intersections with the shapes).
	virtual void CalcEndPoints();

	/// Calculate direction arrow
	void CalcDirection();

	/// ReCalculate when first or last point of line is moved to pt.
	bool CalcEndPoint(const Point *pt, unsigned which);

	/// Update point of given position n.
	void SetPoint(const Point *pt, unsigned int n);

	/// Add a point after given position n.
	void AddPoint(const Point *pt, unsigned int n);

	/// Remove the point at given position n.
	void RemovePoint(unsigned int n);

	///
	int GetClassType() const {return Code::LINE;}

	/// See shape. Reads/writes also the points.
	void WriteMembers(OutputFile *f); 

	/// See shape. Reads/writes also the points.
	bool ReadMembers(InputFile *f, double format);

	/// Set subject (edge) reference,
	bool SetAssocSubject(AssocList *);

	/// Set also fromShape and toShape references.
	bool SetReferences(AssocList *);

	/// Check also fromShape and toShape shape references.
	bool CheckReferences();
	///
	void SetTextShape();

	/// return if segment has (x,y). if so, lineNumber set to segment nr.
	bool GetLine(int x, int y);
	///
	unsigned int GetLineNumber() {return lineNumber;}
	///
	void SetLineNumber(unsigned int n) {lineNumber=n;}

	/// choose text shape near (x,y).
	TextShape *ChooseTextShape(int x, int y);

	/// move all points and text shapes with delta.
	virtual void MoveRaw(const Point *delta);

	///
	Point GiveOrthoSnp(Point to) const;
	///
	Point GiveSnp(Point to) const;
	///
	Point GiveSnp(Point p, int order, int count, int &code);

        ///
        void UpdateNameDirection(ReadDirection::Type nd);
	///
	ReadDirection::Type GetNameDirection() const {return nameDirection;}

	/// just recalculate the position of the name text shape.
	Point RecalcPositionName(bool useReadDirection);
//Begin SQD Integration
	virtual void SetAnchors() {;}
//End SQD Integration
protected:
	/// draws a line.
	void DrawShape();

	/// recalculate the position of the name text shape.
	void CalcPositionName();

	/// default x distance between textshapes to line.
	static const int CL_DISTX;
	/// default y distance between textshapes to line.
	static const int CL_DISTY;

	/// returns (x,y) is near line from-to, cx and cy are points on line.
	bool ContainsPtLine(int x, int y, const Point *from, const Point *to,
		int &cx, int &cy) const;

	/// return if (x,y) is down to line from->to.
	bool BelowLine(int x, int y, Point *from, Point *to);

	/// return if (x,y) is above line from->to.
	bool AboveLine(int x, int y, Point *from, Point *to);

        ///
        void SetNameDirection(ReadDirection::Type nd) {nameDirection=nd;}
	///
	void UndrawDirection();
	///
	void DrawDirection();
	///
	void NotifyTextMove(TextShape *t);
private:
	/// The first connected shape.
	GShape *fromShape;

	/// The other connected shape.
	GShape *toShape;

	/// The points of the line (aka handles).
	List<Point *> *line;

	/// Is the line curved?
	bool curved;

	///
	LineEnd end1;

	///
	LineEnd end2;

	///
	DPoint *directionPoints;

	/// possible read direction of name label.
        ReadDirection::Type nameDirection;

	/// The segment where the name text shape is located.
	unsigned int lineNumber;

	/// how many lines exist between fromShape and toShape.
	unsigned int count; 

	/// the order in the case of multiple lines.
	unsigned int order; 

	/// 0=free, 1=horizontal, 2=vertical.
	int orientation;

	///
	virtual void DrawLine(const DPoint *ep1, const DPoint *ep2, int b, int e);

	/// Draws a bezier curve through line's points.
	virtual void DrawBezier(const DPoint *ep1, const DPoint *ep2);

	/// at the moment. lines cannot be duplicated.
	void DrawDuplicate() {}

	/// draws black handles at each point of line.
	void DrawSelect();

	/// draws gray handles.
	void DrawGraySelect();

	/// not relevant for a line.
	void SetHandles(int) {} 

	/// moves all points of line.
	void Move(const Point *delta); 
};
#endif
