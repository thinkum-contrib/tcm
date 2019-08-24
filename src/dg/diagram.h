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
#ifndef _DIAGRAM_H
#define _DIAGRAM_H

#include "document.h"
#include "diagramviewer.h"
#include "linestyle.h"
#include "lineend.h"
#include "sequence.h"
class Graph;
class Edge;

/// (abstract) diagram class.
class Diagram: public Document {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Diagram(Config *, DiagramWindow *, DiagramViewer *, Graph *);
	///
	virtual ~Diagram();
	///
	void Initialize();
	///
	Graph *GetGraph() const {return graph;}
	///
	AssocList *GetAssocList() const {return assocList;}

	/// Create a new node subject. Depends on current node type.
	virtual Node *CreateNode() = 0;

	/// Create edge, checks if connection is allowed. 
	virtual Edge *CreateEdge(Subject *n1, Subject *n2) = 0;

	/// Create a node shape at (x,y), with default size and node as subject.
	virtual NodeShape *CreateNodeShape(Node *node, int x, int y) = 0;

	/// Create a line of lineType from fromShape to toShape via points.
	virtual Line *CreateLine(Edge *edge,
		GShape *fromShape, GShape *toShape, List<Point *> *line) = 0;

	/// set/reset current node shape type to/from num.
	virtual void UpdateNodeType(int num) = 0;

	/// set/reset current edge shape type to/from num.
	virtual void UpdateEdgeType(int num) = 0;

	/// set/reset curved edge shapes.
	void SetCurve(bool set);
	///
	bool IsCurve() const {return dviewer->IsDefaultCurve();}

	/// Check if connection between those two nodes is allowed.
	bool CheckConnection(Subject *n1, Subject *n2);

	// when removing shapes from the screen we save them in a 
	// temp. buffer. With undo we add the shapes again, and get
	// them from the buffer. Therefore, adding means taking from
	// the temp. buffer. For symmetry, when we create a shape
	// we also put it first in the buffer.

	/// Add node/edge to graph data structure.
	virtual void AddSubject(Subject *s); 

	/// Add nodes and edges to graph data structure.
	void AddSubjects(List<Subject *> *s); 

	/// Remove node/edge from graph data structure.
	virtual void RemoveSubject(Subject *s); 

	/// Remove nodes and edges from graph data structure.
	void RemoveSubjects(List<Subject *> *s); 

	/// add edges to subjects which connect the subjects in subjects.
	void CompleteSubjects(List<Subject *> *subjects);

	/// add subjects to subjects which are connected by edges in subjects.
	void CompleteEdges(List<Subject *> *subjects);

	/// add to edges all edges of which subject is part.
	void CompleteSubject(List<Subject *> *edges, Subject *subject);

	/// Remove all nodes and edges.
	void RemoveAll(); 

	/// Annotate subject via pop-up dialog.
	void AnnotateSubject(Subject *s);

	/// Annotate annotationSubject
	void SetSubjectAnnotation(string *s);
	
	/// Redirect line from first or last subject that covers point pt.
	bool RedirectEdge(Line *line, bool first, const Point *pt);

	/// move diagram in main window.
	void Move(MoveType);

	/// select all shapes of subject in current view. 
	void SelectSubject(Subject *s);
	/// select all shapes of subjects in list in current view.
	void SelectSubjects(List<Subject *> *s);

	/// Update the text of text shape t and the corresponding subject.
	virtual bool SetText(TextShape *t, const string *s);

	///
	void FindAll(const string *s, bool send, bool substring, bool nameOnly); 
	///
	void FindNext(const string *s, bool send, bool substring, bool nameOnly); 
	///
	void ReplaceAll(const string *s1, const string *s2, 
			bool send, bool substring, bool nameOnly); 
	///
	void ReplaceNext(const string *s1, const string *s2, 
			bool send, bool substring, bool nameOnly); 
	///
	virtual bool HasIndexNode(int) {return False;}
	///
	virtual bool HasIndexShape(int) {return False;}
	///
	void Reindex();

	/// Give Node next index nr. and update shapes.
	void SetNextIndex(Node *n);

	///
	virtual void SetHierarchic(bool s);
	///
	virtual bool AllowHierarchic() const;

	///
	static Sequence sequence;
protected:
	///
	DiagramViewer *GetDiagramViewer() const {return dviewer;}

	///
	int GetNodeType() const {return dviewer->GetDefaultNodeType();}
	///
	void SetNodeType(int n) {dviewer->SetDefaultNodeType(n);}
	///
	int GetEdgeType() const {return dviewer->GetDefaultEdgeType();}
	///
	void SetEdgeType(int n) {dviewer->SetDefaultEdgeType(n);}
	///
	int GetNodeShapeType() const {
		return dviewer->GetDefaultNodeShapeType();}
	///
	void SetNodeShapeType(int n) {
		dviewer->SetDefaultNodeShapeType(n);}
	///
	void SetLineType(int n) {dviewer->SetDefaultLineType(n);}
	///
	int GetLineType() const {return dviewer->GetDefaultLineType();}
	/// 
	LineStyle::Type GetNodeLineStyle() {
		return dviewer->GetDefaultNodeLineStyle();}
	/// 
	LineStyle::Type GetEdgeLineStyle() {
		return dviewer->GetDefaultEdgeLineStyle();}
	/// 
	void SetNodeLineStyle(LineStyle::Type n) {
		dviewer->SetDefaultNodeLineStyle(n);}
	/// 
	void SetEdgeLineStyle(LineStyle::Type e) {
		dviewer->SetDefaultEdgeLineStyle(e);}
	///
	LineEnd::Type GetLineEnd1() {
		return dviewer->GetDefaultLineEnd1(); }
	///
	LineEnd::Type GetLineEnd2() {
		return dviewer->GetDefaultLineEnd2(); }
	///
	void SetLineEnd1(LineEnd::Type t) {
		dviewer->SetDefaultLineEnd1(t); }
	///
	void SetLineEnd2(LineEnd::Type t) {
		dviewer->SetDefaultLineEnd2(t); }
	
	/// Sets name of subject to s. Checks if name is allowed.
	bool SetSubjectName(Subject *subject, const string *s);

	/// Check and set index of a node.
	bool SetIndex(Node *n, const string *index);

	///
	virtual void PlaceShapes();
	///
	void LoadEntries();
	///
	void SaveEntries();

	/// Creates a new shape/subject depending on classNr.
	virtual Thing *CreateThing(int classNr) = 0;

	/// update all name strings of shapes representing subject.
	void UpdateNameStrings(Subject *subject);
private:
	///
	DiagramViewer *dviewer;
	///
	Graph *graph;
	///
	AssocList *assocList;

	///
	List<ShapeView *> viewsRead;

	///
	unsigned long maxid;

	///
	Subject *annotationSubject;

	/// fit shapes to drawing area + some extra edit space.
	void FitShapes(); 
	///
	void PlaceViews();
	///
	void PurgeViews();
	///
	void CheckSubjects();
	///
	void ReadThing(int classNr, unsigned long value, bool dashedShape);
	///
	void DeleteDiagram();
};
#endif
