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
#include "psgraph.h"
#include "psviewer.h"
#include "pswindow.h"
#include "pschecks.h"
#include "emptyedge.h"
#include "psprocess.h"
#include "urlabeledbox.h"
#include "textbox.h"
#include "comment.h"
#include "line.h"
#include "messagedialog.h"
#include "psdiagram.h"

PSDiagram::PSDiagram(Config *c, PSWindow *d, PSViewer *v, PSGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	treeSequenceNr = 0;
	actionSequenceNr = 0;
	psChecks = new PSChecks(this,g);
}

PSDiagram::~PSDiagram() {
	delete psChecks;
}

Thing *PSDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	PSGraph *pg = (PSGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());
	// node shapes
	else if (classNr == Code::UR_LABELED_BOX)
		thing = new URLabeledBox(v, g, 0, 0);
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0);
	// lines
	else if (classNr == Code::LINE) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetFixedName(True);
		thing = line;
	}
	// nodes
	else if (classNr == Code::PS_PROCESS)
		thing = new PSProcess(pg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(pg);
	// edges
	else if (classNr == Code::EMPTY_EDGE)
		thing = new EmptyEdge(pg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d in file\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *PSDiagram::CreateNode(){
	Node *node = 0;
	PSGraph *pg = (PSGraph *)GetGraph();
	if (GetNodeType() == Code::PS_PROCESS)
		node = new PSProcess(pg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(pg);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}
 
Edge *PSDiagram::CreateEdge(Subject *n1, Subject *n2){
	if (!CheckEdgeConstraints(n1, n2))
		return 0;
	Edge *edge = 0;
	PSGraph *pg = (PSGraph *)GetGraph();
	if (GetEdgeType() == Code::EMPTY_EDGE)
		edge = new EmptyEdge(pg, n1, n2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *PSDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::UR_LABELED_BOX)
		shape = new URLabeledBox(v, g, x, y);
	else
		error("%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);

	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *PSDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Line *line = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	*((*l)[0]) = *(from->GetPosition());
	*((*l)[l->count()-1]) = *(to->GetPosition());
	if (GetLineType() == Code::LINE) {
		line = new Line(v, g, from, to, l, IsCurve());
		line->SetFixedName(True);
	}
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

void PSDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::PS_PROCESS);
		SetNodeShapeType(Code::UR_LABELED_BOX);
		break;
	case 2: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown node type selected\n", __FILE__, __LINE__);
	}
}
 
void PSDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::EMPTY_EDGE);
		SetLineType(Code::LINE);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown edge type selected\n", __FILE__, __LINE__);
	}
}

bool PSDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	if (!CheckConnection(subj1, subj2))
		return False;
	if ((subj1 == subj2) || GetGraph()->PathExists(subj1, subj2)) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"This connection violates the tree constraint");
		return False;
	}
	return True;
}

void PSDiagram::SaveEntries() {
	TraverseTree(False);
	Diagram::SaveEntries();
	((PSViewer *)GetDiagramViewer())->UpdateShowSequences();
}
 
unsigned PSDiagram::TraverseTree(bool chec) {
	unsigned errors = 0;
	List<Subject *> all_nodes;
	treeSequenceNr = 0;
	actionSequenceNr = 0;
	GetGraph()->GetNodes(&all_nodes, Code::PS_PROCESS);
	PSProcess *root;
	unsigned nrRoots = FindRoot(&all_nodes, &root);
	List<Subject *> tree_nodes;

	if (nrRoots == 1) {
		root->SetRoot(True);
		tree_nodes.add(root);
			if (chec)
				errors += psChecks->CheckRootOperator(root, chkbuf);
		errors += TraverseChildren(root, &tree_nodes, chec);
	}
	else if (nrRoots == 0 && chec) {
		chkbuf +="* Error: there is no root process\n";
		errors++;
	}
	else if (nrRoots > 1 && chec) {
		chkbuf +="* Error: there is no unique root process\n";
		errors++;
	}
	// Check if there are remaining nodes not part of the tree:
	for (all_nodes.first(); !all_nodes.done(); all_nodes.next()) {
		Subject *node = all_nodes.cur();
		if (tree_nodes.find(node) == -1) {
			// give remaining node unused sequence numbers.
			((PSProcess *)node)->SetTreeSequence(0);
			((PSProcess *)node)->SetActionSequence(0);
			// give error if required.
			if (chec && nrRoots == 1 && *node->GetName() != "") {
				// empty names are noted elsewhere.
				errors++;
				chkbuf += "* Error: Process '";
				chkbuf += *node->GetName();
				chkbuf += "' is not part of the main tree\n";
			}
		}
	}
	return errors;
}

unsigned PSDiagram::FindRoot(List<Subject *> *nodes, PSProcess **root) {
	// find the root: the subject that has the shape with
	// the smallest y-coordinate.
	Point root_pos;
	unsigned card = 0;
	if (nodes->first()) {
		PSProcess *node = (PSProcess *)nodes->cur();
		Shape *nshape = GetDiagramViewer()->GetShape(node);
		root_pos = *nshape->GetPosition();
		*root = node;
		card = 1;
		while (nodes->next()) {
			node = (PSProcess *)nodes->cur();
			nshape = GetDiagramViewer()->GetShape(node);
			const Point *pt = nshape->GetPosition();
			if (root_pos.y > pt->y) {
				root_pos = *pt;
				*root = node;
				card = 1;
			}
			else if (root_pos.y == pt->y) {
				// more than one root ?
				card++;
			}
		}
	}
	return card;
}

void PSDiagram::FindChildren(PSProcess *parent, List<Subject *> *nodes, 
			List<Subject *> *children) {
	List<Subject *> edges;
	List<Subject *> child_edges;
	// find all edges that connect the parent with its children.
	GetGraph()->CompleteSubject(&edges, parent);
	for (edges.first(); !edges.done(); edges.next()) {
		Edge *edge = (Edge *)edges.cur();
		Subject *n1 = edge->GetSubject1();
		Subject *n2 = edge->GetSubject2();
		if (n1 == parent && nodes->find(n2) == -1) {
			child_edges.add(edge);
		}
		else if (n2 == parent && nodes->find(n1) == -1) {
			child_edges.add(edge);
		}
	}
	children->empty();
	Edge *leftMost = 0;
	// look repeatedly for the 'leftMost' edge: i.e. the
	// edge whose line connects to the shape of the parent
	// with the smallest x-coordinate.
	while ((leftMost = FindLeftMostEdge(parent, &child_edges))) {
		if (leftMost->GetSubject2() == parent)
			children->add(leftMost->GetSubject1());
		else
			children->add(leftMost->GetSubject2());
		child_edges.remove(leftMost);
	}
}

Edge *PSDiagram::FindLeftMostEdge(PSProcess *parent, List<Subject *> *child_edges) {
	Edge *leftMost =0;
	int min_x;
	if (child_edges->first()) {
		Edge *edge = (Edge *)(*child_edges)[0];
		Line *line = (Line *)GetDiagramViewer()->GetShape(edge);
		Shape *nshape = GetDiagramViewer()->GetShape(parent);
		// we have to take care of the two different directions 
		// of the line.
		if (line->GetFromShape() == nshape)
			min_x = (*line->GetLine())[0]->x;
		else
			min_x = (*line->GetLine())[line->NrPoints()-1]->x;
		leftMost = edge;
		while (child_edges->next()) {
			edge = (Edge *)child_edges->cur();
			line = (Line *)GetDiagramViewer()->GetShape(edge);
			Point *pt;
			if (line->GetFromShape() == nshape)
				pt = (*line->GetLine())[0];
			else
				pt = (*line->GetLine())[line->NrPoints()-1];
			if (pt->x < min_x) {
				min_x = pt->x; 
				leftMost = edge;
			}
		}
	}
	return leftMost;
}

unsigned PSDiagram::TraverseChildren(PSProcess *parent, List<Subject *> *nodes, bool chec) {
	unsigned errors = 0;
	List<Subject *> children;
	FindChildren(parent, nodes, &children);
	// list name of parent and of their children.
	// Call this function recursively for all the children.
	for (children.first(); !children.done(); children.next()) {
		PSProcess *child = (PSProcess *)children.cur();
		child->SetRoot(False);
		nodes->add(children.cur());
	}
	if (chec) {
		errors += psChecks->CheckChildPositions(
			GetDiagramViewer(), parent, &children, chkbuf);
		errors += psChecks->CheckChildOperators(parent, &children, chkbuf);
	}
	for (children.first(); !children.done(); children.next())
		errors += TraverseChildren((PSProcess *)children.cur(), nodes, chec);
	if (children.count() == 0) {
		char op = parent->GetOperator();
		if (op != '?' && op != '!')
			parent->SetAction(True);
		else
			parent->SetAction(False);
	}
	else if (children.count() == 1) {
		// parent of a '!' process is also considered as a action.
		PSProcess *p = (PSProcess *)children[0];
		if (p->GetOperator() == '!')
			parent->SetAction(True);
		else
			parent->SetAction(False);
	}
	else
		parent->SetAction(False);
	parent->SetTreeSequence(++treeSequenceNr);
	if (parent->IsAction())
		parent->SetActionSequence(++actionSequenceNr);
	else
		parent->SetActionSequence(0);

	return errors;
}

void PSDiagram::CheckDocument() {
	chkbuf = "";
	unsigned errors = 0;
	errors += TraverseTree(True);
	((PSViewer *)GetDiagramViewer())->UpdateShowSequences();
	errors += psChecks->CheckNamelessNodes(Code::PS_PROCESS, chkbuf);
	errors += psChecks->CheckDoubleProcessNames(chkbuf);
	ReportCheck(errors, &chkbuf);
}

bool PSDiagram::SetOperator(PSProcess *proc, const string *s) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(proc, &shapes);
	// empty string means sequence (space).
	char op;
	if (s->length() == 0)
		op = ' ';
	else
		op = (*s)[0];
	if (proc->SetOperator(op)) {
		if (check(shapes.first()))
			do
				((URLabeledBox *)shapes.cur())->UpdateURLabel(s);
			while (shapes.next());
		else 
			return False;
	}
	else {
		string txt = *s + " is not a valid process operator";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	return True;
}

bool PSDiagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Process Operator" &&
		    (subj->GetClassType()==Code::PS_PROCESS))
		return SetOperator((PSProcess *)subj, s);
	else
		return Diagram::SetText(t, s);
}
