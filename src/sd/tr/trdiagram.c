////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "messagedialog.h"
#include "textedge.h"
#include "textroot.h"
#include "comment.h"
#include "arrowtextbox.h"
#include "textbox.h"
#include "line.h"
#include "grafport.h"
#include "trdiagram.h"
#include "trviewer.h"
#include "trwindow.h"
#include "trgraph.h"
#include "trview.h"
#include "diagramchecks.h"
#include <limits.h>


TRDiagram::TRDiagram(Config *c, TRWindow *d, TRViewer *v, TRGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	trChecks = new DiagramChecks(this, g);
}

TRDiagram::~TRDiagram() {
	delete trChecks;
}

Thing *TRDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	TRGraph *tg = (TRGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new TRView((TRViewer *)GetDiagramViewer()); 
	// node shapes
	else if (classNr == Code::ARROW_TEXT_BOX)
		thing = new ArrowTextBox(v, g, 0, 0); 
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	// lines
	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);
	// nodes
	else if (classNr == Code::TEXT_ROOT)
		thing = new TextRoot(tg);
	else if (classNr == Code::TEXT_NODE)
		thing = new TextNode(tg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(tg);
	// edges
	else if (classNr == Code::TEXT_EDGE)
		thing = new TextEdge(tg, 0, 0);
	else 
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *TRDiagram::CreateNode(){
	Node *node = 0;
	TRGraph *tg = (TRGraph *)GetGraph();
	if (GetNodeType() == Code::TEXT_ROOT)
		node = new TextRoot(tg);
	else if (GetNodeType() == Code::TEXT_NODE)
		node = new TextNode(tg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(tg);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *TRDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0; 
	Edge *edge = 0;
	TRGraph *tg = (TRGraph *)GetGraph();
	if (GetEdgeType() == Code::TEXT_EDGE)
		edge = new TextEdge(tg, subj1, subj2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *TRDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::ARROW_TEXT_BOX)
		shape = new ArrowTextBox(v, g, x, y);
	else {
		error("%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);
	}
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *TRDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Line *line = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetLineType() == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else {
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	}
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
	}
	return line;
}

void TRDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::TEXT_ROOT);
		SetNodeShapeType(Code::ARROW_TEXT_BOX);
		break;
	case 2: SetNodeType(Code::TEXT_NODE);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	case 3: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
		" unknown node type selected\n", __FILE__,__LINE__);
	}
}

void TRDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::TEXT_EDGE);
		SetLineType(Code::LINE);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool TRDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False; 
	// Check for loops.
	if ((subj1==subj2) || GetGraph()->PathExists(subj1, subj2) || 
	    (FindRoot(subj1) && FindRoot(subj2))) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"This connection violates the tree constraint");
		return False;
	}
	return True;
}

void TRDiagram::DoLoad(const string *file) {
	if (IsAppending() && ((TRViewer *)GetDiagramViewer())->IsTreeMode())
		SetStatus("Append aborted: in view mode");
	else
		Diagram::DoLoad(file);
}

void TRDiagram::RemoveAll() {
	Diagram::RemoveAll();
}

void TRDiagram::PlaceShapes() {
	Diagram::PlaceShapes();
	if (!IsAppending())
		GetDiagramViewer()->Refresh();
}

void TRDiagram::Append() {
	if (!((TRViewer *)GetDiagramViewer())->IsTreeMode())
		Diagram::Append();
	else
		SetStatus("Append aborted: in view mode");
}

void TRDiagram::RecalculateTree() {
	// recalculate parent-child relationships.
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::TEXT_ROOT);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		TextNode *node = (TextNode *)(nodes.cur());
		CalcParents(0, node);
		// DumpChildren(node, 0);
	}
}

void TRDiagram::CheckDocument() {
	RecalculateTree();
	chkbuf = "";
	unsigned total = trChecks->CheckNodeCount(1, INT_MAX, Code::TEXT_ROOT, chkbuf);
	if (total == 0)
		total += trChecks->CheckReachability(
			Code::TEXT_ROOT, Code::TEXT_NODE, False, chkbuf);
	total += trChecks->CheckNamelessNodes(Code::TEXT_ROOT, chkbuf);
	total += trChecks->CheckNamelessNodes(Code::TEXT_NODE, chkbuf);
	ReportCheck(total, &chkbuf);
}

void TRDiagram::CalcParents(TextNode *parent, TextNode *node) {
	List<Subject *> nodes;
	GetGraph()->GetConnected(&nodes, node);
	node->SetParent(parent);
	if (parent != 0)
		nodes.remove(parent);
	for (nodes.first(); !nodes.done(); nodes.next())
		CalcParents(node, (TextNode *)(nodes.cur()));
}

void TRDiagram::DumpChildren(TextNode *node, unsigned level) {
	// dump text tree.
	List<Subject *> nodes;
	GetGraph()->GetConnected(&nodes, node);
	Node *parent = node->GetParent();
	if (parent != 0)
		nodes.remove(parent);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		for (unsigned i=0;i<level;i++)
			std::cout << '\t';
		std::cout << "- " << *nodes.cur()->GetName() << '\n';
		DumpChildren((TextNode *)nodes.cur(), level+1);
	} 
}

void TRDiagram::GetChildren(TextNode *node, List<Subject *> *children) {
	children->empty();
	GetGraph()->GetConnected(children, node);
	Node *parent = node->GetParent();
	if (parent)
		children->remove(parent);
}

void TRDiagram::DrawTreeLayout() {
	List<Subject *> roots;
	GetGraph()->GetNodes(&roots, Code::TEXT_ROOT);
	for (roots.first(); !roots.done(); roots.next()) {
		TextNode *root = (TextNode *)(roots.cur());
		CalcParents(0, root);
		DrawTreeLayout(root);
	} 
}

void TRDiagram::DrawTreeLayout(TextNode *parent) {
	List<Subject *> nodes;
	List<Shape *> shapes;
	Shape *parentShape;
	// find direct children of the parent node.
	GetChildren(parent, &nodes);
	if (nodes.count() == 0)
		return;
	// get the shape of the parent.
	parentShape = GetDiagramViewer()->GetShape(parent);
	if (!check(parent))
		return;
	for (nodes.first(); !nodes.done(); nodes.next()) {
		// do this recursively.
		DrawTreeLayout(((TextNode *)nodes.cur()));
		// collect the shapes of the children.
		Shape *s = GetDiagramViewer()->GetShape(nodes.cur());
		if (check(s))
			shapes.add(s);
	} 
	// draw it as a fork
	((TRViewer *)GetDiagramViewer())->DrawTreeFork(parentShape, &shapes);
}

void TRDiagram::UndrawTreeLayout() {
	DrawTreeLayout();
}

 
bool TRDiagram::FindRoot(Subject *subj) {
	// return if there is a path to a root.
	if (subj->GetClassType()==Code::TEXT_ROOT)
		return True;
	List<Subject *> roots;
	GetGraph()->GetNodes(&roots, Code::TEXT_ROOT);
	// find a root of the node if it exists.
	for (roots.first(); !roots.done(); roots.next()) {
		if (GetGraph()->PathExists(subj, (Subject *)(roots.cur())))
			return True;
	}
	return False;
}
