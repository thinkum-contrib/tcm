//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _SHAPEVIEW_H
#define _SHAPEVIEW_H

#include "lstring.h"
#include "point.h"
#include "util.h"
#include "thing.h"
class Shape;
class GShape;
class NodeShape;
class Line;
class Subject;
class Node;
class TextShape;
class DiagramViewer;
class Grafport;

/// Class containing a single view (set of shapes). 
class ShapeView: public Thing {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ShapeView(DiagramViewer *v);
	///
	virtual ~ShapeView();
	///
	int GetClassType() const {return Code::VIEW;}
	///
	bool IsView() const {return True;}

	/// draw all shapes in the view.
	void Draw();

	/// erase all shapes in the view.
	void Undraw();

	/// set grafport of all shapes.
	void SetGrafport(Grafport *g);

	/// each view has a parent node.
	Node *GetParent() const {return parent;}

	///
	void SetParent(Node *n) {parent=n;}

	/// each view has a unique index.
	const string *GetIndex() const {return &index;}

	///
	void SetIndex(string *s) {index=*s;}

	/// the number of shapes.
	unsigned NrOfShapes() const {return shapes->count();}

	///
	List<GShape *> *GetShapes() const {return shapes;}
	///
	List<GShape *> *GetSelection() const {return selection;}

	///
	bool HasShape(GShape *s) {return (shapes->find(s) != -1);}

	/// Snap point to discrete point-position.
	void Snap(Point *p);

	/// Snap int to discrete point-position.
	int Snap(int i);
 
	///
	DiagramViewer *GetViewer() const {return viewer;}

	/// write all shapes to file (in separate clauses).
	void WriteShapes(OutputFile *f);

	/// read view section.
	bool ReadMembers(InputFile *f, double format);
 
	/// update references when view is read.
	bool SetReferences(AssocList *);
 
	/// Check parent node, Check that shapes have right view reference.
	bool CheckReferences();

	/// find all shapes with wrong references;
	void CheckShapes();

	/// the number of selected shapes.
	unsigned NrSelected() const {return selection->count();}

	/// return the first selected shape.
	GShape *FirstSelected() const {
		return selection->count()>0?(*selection)[0]:0;}

	/// deselect all shapes in the view.
	void DeselectAll();

	/// add shape to selection.
	virtual void SelectShape(GShape *shape);

	/// add shape to selection as primus inter pares.
	virtual void FirstSelectShape(GShape *shape);

	/// remove shape to selection.
	void DeselectShape(GShape *shape);

	/// return shape from view if (x,y) is in shape.
	GShape *HitShape(int x, int y);

	/// return node from view if (x,y) is in shape.
	NodeShape *HitNodeShape(int x, int y); 

	/// return line from view if (x,y) is in line. segment is set to which segment.
	Line *HitLine(int x, int y, int &whichsegment);
	
	/// return line from view if (x,y) hits handle.
	Line *HitLineHandle(int x, int y, int &which); 

	/// return text-shape from view if (x,y) is in shape.
	TextShape *HitTextShape(int x, int y, bool emptyallowed=True);

	///
	int GetCurrentShapeNr() const {return currentShapeNr;}
	///
	void SetCurrentShapeNr(int i) {if(check(i>=0)) currentShapeNr=i;}
	///
	void SetCurrentShapeNr(GShape *s) {
		currentShapeNr=max(0,shapes->find(s));}
	
	/// return the next shape containing s as name.
	GShape *GetNextShape(const string *s, bool sens,
		bool substring, bool nameOnly);

	/// get shapes containing s as name (case sensitive, substring).
	void GetShapes(List<GShape *> *shapes, const string *s,
			bool sens, bool substring, bool nameOnly);

	///
	void CalcSizeElements(Point &topLeft, Point &bottomRight);
	///
	void CalcSizeSelection(Point &topLeft, Point &bottomRight);
	/// calculate covered area of shapes in grafport.
	void CalcSizeShapes(List<GShape *> *shapes, Point &topLeft,
				Point &bottomRight);
	
	/// add to viewer and draw/redraw shape.
	void AddShapeRaw(GShape *shape);
	/// add to viewer and draw/redraw shape and recalc. line positions.
	virtual void AddShape(GShape *shape);
	///
	void AddShapes(List<GShape *> *shapes);

	/// remove from viewer and erase shape.
	void RemoveShapeRaw(GShape *shape);
	/// remove from viewer, and erase drawing and recalc line positions.
	virtual void RemoveShape(GShape *shape);
	///
	void RemoveShapes(List<GShape *> *shapes);

	/// return first shape from shapes having given subject.
	GShape *GetShape(Subject *subject);

	/// put in shapes all shapes from shapes having given subject.
	void GetShapes(Subject *subject, List<GShape *> *shapes);

	/// update the positions of the lines connecting same shapes as line.
	void MultipleLinesPosUpdate(Line *line);

	/// update multiple lines between two nodes (called when line added).
	void MultipleLines(Line *line);

	/// add to s all lines that connect shapes n1 and n2.
	void CompleteShapes(List<GShape *> *s, GShape *n1, GShape *n2);

	/// add shapes which are connected by the lines in shapes.
	void CompleteLines(List<GShape *> *shapes);

	/// add lines to shapes which connect the shapes in shapes.
	void CompleteShapes(List<GShape *> *shapes);

	/// draw only names in view.
	void DrawNames();

	/// make all shapes in view visible.
	void ShowAll();

	/// recalculate parent for shape.
	void RecalcParent(GShape *shape) const;

	/// recalculates all parents.
	void RecalcAllParents(bool hierarchicDocument) const;

	/// Does the view have duplicate (node) shapes?
	bool HasDuplicates() const;
private:
	/// the viewer that manages the view.
	DiagramViewer *viewer;

	/// the parent node.
	Node *parent;

	/// the view index.
	string index;

	/// current shape number.
	int currentShapeNr;

	/// the list of displayed shapes.
	List<GShape *> *shapes;
 
	/// the list of selected shapes.
	List<GShape *> *selection;

	/// write view clause to file.
	void WriteMembers(OutputFile *);

	/// recalculate parent of *shape.
	void IntRecalcAllParents(GShape *shape, const List<GShape *>
				*relevant, List<GShape *> *toBeHandled) const;
};
#endif
