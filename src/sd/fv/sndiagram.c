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
#include "snviewer.h"
#include "snwindow.h"
#include "sngraph.h"
#include "snprocess.h"
#include "snchecks.h"
#include "datastream.h"
#include "controlleddatastream.h"
#include "statevector.h"
#include "connectionstart.h"
#include "connectionend.h"
#include "startc1line.h"
#include "endc1arrow.h"
#include "leftlinecircle.h"
#include "diamond.h"
#include "textbox.h"
#include "comment.h"
#include "messagedialog.h"
#include "sndiagram.h"
#include "box.h"
#include "circle.h"

const int SNDiagram::DIAMOND_WIDTH = 38;
const int SNDiagram::DIAMOND_HEIGHT = 38;
const int SNDiagram::CIRCLE_WIDTH = 38;

SNDiagram::SNDiagram(Config *c, SNWindow *d, SNViewer *v, SNGraph *g): 
		Diagram(c,d,v,g) { 
	snChecks = new SNChecks(this,g);
	UpdateNodeType(1);
	UpdateEdgeType(1);
}

SNDiagram::~SNDiagram() {
	delete snChecks;
}

Thing *SNDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	SNGraph *sg = (SNGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());
	// node shapes
	else if (classNr == Code::BOX)
		thing = new Box(v, g, 0, 0);
	else if (classNr == Code::CIRCLE)
		thing = new Circle(v, g, 0, 0);
	else if (classNr == Code::DIAMOND)
		thing = new Diamond(v, g, 0, 0);
	else if (classNr == Code::LEFT_LINE_CIRCLE)
		thing = new LeftLineCircle(v, g, 0, 0);
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0);
	// lines
	else if (classNr == Code::T1_LINE)
		thing = new StartC1Line(v, g, 0, 0, 0);
	else if (classNr == Code::T1_ARROW)
		thing = new EndC1Arrow(v, g, 0, 0, 0);
	// nodes
	else if (classNr == Code::SN_PROCESS)
		thing = new SNProcess(sg);
	else if (classNr == Code::DATA_STREAM)
		thing = new DataStream(sg);
	else if (classNr == Code::STATE_VECTOR)
		thing = new StateVector(sg);
	else if (classNr == Code::CONTROLLED_DATA_STREAM)
		thing = new ControlledDataStream(sg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(sg);
	// edges
	else if (classNr == Code::CONNECTION_START)
		thing = new ConnectionStart(sg, 0, 0);
	else if (classNr == Code::CONNECTION_END)
		thing = new ConnectionEnd(sg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d in file\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *SNDiagram::CreateNode(){
	Node *node = 0;
	SNGraph *sg = (SNGraph *)GetGraph();
	if (GetNodeType() == Code::SN_PROCESS)
		node = new SNProcess(sg);
	else if (GetNodeType() == Code::DATA_STREAM)
		node = new DataStream(sg);
	else if (GetNodeType() == Code::STATE_VECTOR)
		node = new StateVector(sg);
	else if (GetNodeType() == Code::CONTROLLED_DATA_STREAM)
		node = new ControlledDataStream(sg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(sg);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}
 
Edge *SNDiagram::CreateEdge(Subject *s1, Subject *s2){
	if (!CheckEdgeConstraints(s1, s2))
		return 0;
	Edge *edge = 0;
	SNGraph *sg = (SNGraph *)GetGraph();
	if (GetEdgeType() == Code::CONNECTION_START)
		edge = new ConnectionStart(sg, s1, s2);
	else if (GetEdgeType() == Code::CONNECTION_END)
		edge = new ConnectionEnd(sg, s1, s2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *SNDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::BOX)
		shape = new Box(v, g, x, y);
	else if (GetNodeShapeType() == Code::DIAMOND)
		shape = new Diamond(v, g, x, y);
	else if (GetNodeShapeType() == Code::CIRCLE)
		shape = new Circle(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::LEFT_LINE_CIRCLE)
		shape = new LeftLineCircle(v, g, x, y);
	else
		error("%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *SNDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	if (GetLineType() == Code::T1_LINE)
		line = new StartC1Line(v, g, from, to, l, IsCurve());
	else if (GetLineType() == Code::T1_ARROW)
		line = new EndC1Arrow(v, g, from, to, l, IsCurve());
	else
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
	}
	return line;
}

void SNDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::SN_PROCESS);
		SetNodeShapeType(Code::BOX);
		break;
	case 2: SetNodeType(Code::DATA_STREAM);
		SetNodeShapeType(Code::CIRCLE);
		break;
	case 3: SetNodeType(Code::STATE_VECTOR);
		SetNodeShapeType(Code::DIAMOND);
		break;
	case 4: SetNodeType(Code::CONTROLLED_DATA_STREAM);
		SetNodeShapeType(Code::LEFT_LINE_CIRCLE);
		break;
	case 5: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__, __LINE__);
	}
}
 
void SNDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::CONNECTION_START);
		SetLineType(Code::T1_LINE);
		break;
	case 2: SetEdgeType(Code::CONNECTION_END);
		SetLineType(Code::T1_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__, __LINE__);
	}
}

bool SNDiagram::CheckEdgeConstraints(Subject *s1, Subject *s2) {
	if (!CheckConnection(s1, s2))
		return False;
	// sufficient in SND, two nodes can never be double connected.
	string msg = "Cannot add another ";
	msg += Code::GetName(GetEdgeType());
	msg += " here.";
	if (GetGraph()->IsConnected(s1, s2)) {
		ShowDialog(MessageDialog::ERROR, "Error", &msg);
		return False;
	}
	// a node cannot have two connection start edges comming to it.
	string empty("");
	if (GetEdgeType()==Code::CONNECTION_START &&
	    GetGraph()->CountEdgesTo(s2, &empty, Code::CONNECTION_START)) {
		ShowDialog(MessageDialog::ERROR, "Error", &msg);
		return False;
	}
	return True;
}
 

bool SNDiagram::SetConstraint(Subject *subject, const string *s, unsigned) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	C1Edge *edge = (C1Edge *)subject;
	if (!edge->SetConstraint(s)) {
		string msg = "'" + *s + "' wrong syntax\n"
			     "for a cardinality constraint";
		ShowDialog(MessageDialog::ERROR, "Error", &msg);
		return False;
	}
	if (shapes.first()) {
		do {
			Shape *shape = shapes.cur();
			if (shape->GetClassType() == Code::T1_LINE) 
				((T1Line *)shape)->UpdateTextShape1(s);
			else if (shape->GetClassType() == Code::T1_ARROW) 
				((T1Line *)shape)->UpdateTextShape1(s);
		}
		while (shapes.next());
	}
	else {
		error("%s, line %d: impl error: "
				"shape does not exist!\n",
				__FILE__, __LINE__);
		return False;
	}
	return True;
}

void SNDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += snChecks->CheckNamelessNodes(Code::SN_PROCESS, chkbuf);
	total += snChecks->CheckNamelessNodes(Code::DATA_STREAM, chkbuf);
	total += snChecks->CheckNamelessNodes(Code::STATE_VECTOR, chkbuf);
	total += snChecks->CheckNamelessNodes(Code::CONTROLLED_DATA_STREAM, chkbuf);
	total += snChecks->CheckConnected(Code::SN_PROCESS, False, chkbuf);
	total += snChecks->CheckConnected(Code::DATA_STREAM, False, chkbuf);
	total += snChecks->CheckConnected(Code::STATE_VECTOR, False, chkbuf);
	total += snChecks->CheckConnected(Code::CONTROLLED_DATA_STREAM, False, chkbuf);
	total += snChecks->CheckDoubleNodes(Code::SN_PROCESS, chkbuf);
	total += snChecks->CheckDoubleNodes(Code::DATA_STREAM, chkbuf);
	total += snChecks->CheckDoubleNodes(Code::STATE_VECTOR, chkbuf);
	total += snChecks->CheckDoubleNodes(Code::CONTROLLED_DATA_STREAM, chkbuf);
	// total += snChecks->CheckConnectionCoherence(Code::DATA_STREAM, chkbuf);
	total += snChecks->CheckConnectionCoherence(Code::STATE_VECTOR, chkbuf);
	total += snChecks->CheckConnectionCoherence(Code::CONTROLLED_DATA_STREAM, chkbuf);
	ReportCheck(total, &chkbuf);
}

bool SNDiagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Cardinality Constraint")
		return SetConstraint(subj, s, t->GetSequence());
	else 
		return Diagram::SetText(t, s);
}
