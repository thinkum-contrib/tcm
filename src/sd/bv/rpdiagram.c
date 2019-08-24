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
#include "replacedialog.h"
#include "event.h"
#include "processgraphroot.h"
#include "rpgraph.h"
#include "rpviewer.h"
#include "rpwindow.h"
#include "miniarrowellipse.h"
#include "miniellipse.h"
#include "textbox.h"
#include "comment.h"
#include "roundedbox.h"
#include "line.h"
#include "rpdiagram.h"
#include "diagramchecks.h"
#include <limits.h>

const int RPDiagram::BOX_WIDTH = 58;
const int RPDiagram::BOX_HEIGHT = 38;
const int RPDiagram::CIRCLE_WIDTH = 12;
 
RPDiagram::RPDiagram(Config *c, RPWindow *d, RPViewer *v, RPGraph *g): 
		Diagram(c,d,v,g) { 
	UpdateNodeType(1);
	UpdateEdgeType(1);
	GetReplaceDialog()->ManageNameOnlyToggle(True);
	checks = new DiagramChecks(this,g);
}

RPDiagram::~RPDiagram() {
	delete checks;
}

void RPDiagram::PlaceShapes() {
        Diagram::PlaceShapes();
	((RPViewer *)GetViewer())->UnlabelNodeShapes();
}

Thing *RPDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	RPGraph *rg = (RPGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());
	// node shapes
	else if (classNr == Code::MINI_ELLIPSE)
		thing = new MiniEllipse(v, g, 0, 0); 
	else if (classNr == Code::MINI_ARROW_ELLIPSE)
		thing = new MiniArrowEllipse(v, g, 0, 0); 
	else if (classNr == Code::ROUNDED_BOX)
		thing = new RoundedBox(v, g, 0, 0); 
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	// lines
	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);
	else if (classNr == Code::ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		thing = line;
	}
	// nodes
	else if (classNr == Code::PROCESS_GRAPH_ROOT)
		thing = new ProcessGraphRoot(rg);
	else if (classNr == Code::PROCESS_GRAPH_NODE)
		thing = new ProcessGraphNode(rg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(rg);
	// edges
	else if (classNr == Code::EVENT)
		thing = new Event(rg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *RPDiagram::CreateNode(){
	Node *node =0;
	RPGraph *rg = (RPGraph *)GetGraph();
	if (GetNodeType() == Code::PROCESS_GRAPH_ROOT)
		node = new ProcessGraphRoot(rg);
	else if (GetNodeType() == Code::PROCESS_GRAPH_NODE)
		node = new ProcessGraphNode(rg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(rg);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *RPDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	RPGraph *rg = (RPGraph *)GetGraph();
	Edge *edge = 0;
	if (GetEdgeType() == Code::EVENT)
		edge = new Event(rg, subj1, subj2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *RPDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::MINI_ELLIPSE)
		shape = new MiniEllipse(v, g, x, y);
	else if (GetNodeShapeType() == Code::MINI_ARROW_ELLIPSE)
		shape = new MiniArrowEllipse(v, g, x, y);
	else if (GetNodeShapeType() == Code::ROUNDED_BOX)
		shape = new RoundedBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else
		error("%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);

	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *RPDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	*((*l)[0]) = *(from->GetPosition());
	*((*l)[l->count()-1]) = *(to->GetPosition());
	if (GetLineType() == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else {
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	}
	if (check(line)) {
		line->SetEnd2(LineEnd::FILLED_ARROW);
		line->SetSubject(edge);
		line->SetTextShape();
	}
	return line;
}

void RPDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::PROCESS_GRAPH_ROOT);
		SetNodeShapeType(Code::MINI_ARROW_ELLIPSE);
		break;
	case 2: SetNodeType(Code::PROCESS_GRAPH_NODE);
		SetNodeShapeType(Code::MINI_ELLIPSE);
		break;
	case 3: SetNodeType(Code::PROCESS_GRAPH_NODE);
		SetNodeShapeType(Code::ROUNDED_BOX);
		break;
	case 4: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void RPDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::EVENT);
		SetLineType(Code::LINE);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool RPDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False; 
	// Check that two roots are not connected.
	else if (subj1->GetClassType() == Code::PROCESS_GRAPH_ROOT &&
		 subj2->GetClassType() == Code::PROCESS_GRAPH_ROOT && 
		 subj1 != subj2) {
		 ShowDialog(MessageDialog::ERROR, "Error",
		 		"Cannot connect different roots nodes");
		 return False;
	}
	// Check that 2 nodes are not reachable from different life cycle roots.
	ProcessGraphRoot *init1, *init2;
	init1 = FindRoot(subj1); init2 = FindRoot(subj2);
	if (init1 && init2) {
		if (init1 != init2) {
			ShowDialog(MessageDialog::ERROR, "Error", 
				"Cannot connect nodes from different graphs");
			return False;
		}
	}
	return True;
}

ProcessGraphRoot *RPDiagram::FindRoot(Subject *subj) {
	if (subj->GetClassType() == Code::PROCESS_GRAPH_ROOT)
		return (ProcessGraphRoot *)subj;
	List<Subject *> roots;
	GetGraph()->GetNodes(&roots, Code::PROCESS_GRAPH_ROOT);
	for (roots.first(); !roots.done(); roots.next()) {
		ProcessGraphRoot *root = (ProcessGraphRoot *)roots.cur();
		if (GetGraph()->UndirectedPathExists(root, subj))
			return root;
	} 
	return 0;
}

void RPDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += checks->CheckNodeCount(
			1, INT_MAX, Code::PROCESS_GRAPH_ROOT, chkbuf);
	if (total == 0) {
		total += checks->CheckNamelessNodes(
				Code::PROCESS_GRAPH_ROOT, chkbuf);
		total += checks->CheckDoubleNodes(
				Code::PROCESS_GRAPH_ROOT, chkbuf);
		total += checks->CheckReachability(Code::PROCESS_GRAPH_ROOT,
			Code::PROCESS_GRAPH_NODE, False, chkbuf);
	}
	total += checks->CheckNamelessEdges(Code::EVENT, chkbuf);
	ReportCheck(total, &chkbuf);
}
