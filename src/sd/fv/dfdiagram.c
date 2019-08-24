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
#include "dfgraph.h"
#include "dfviewer.h"
#include "dfwindow.h"
#include "dfstubs.h"
#include "dfchecks.h"
#include "line.h"
#include "messagedialog.h"
#include "replacedialog.h"
#include "texteditdialog.h"
#include "externalentity.h"
#include "dataprocess.h"
#include "datastore.h"
#include "splitmergenode.h"
#include "bidirectionaldataflow.h"
#include "dfdiagram.h"
#include "textbox.h"
#include "square.h"
#include "circle.h"
#include "horizontalbar.h"
#include "blackdot.h"
#include "comment.h"
#include <ctype.h>
#include <stdlib.h>

DFDiagram::DFDiagram(Config *c, DFWindow *d, DFViewer *v, DFGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	GetReplaceDialog()->ManageNameOnlyToggle(True);
	editProcess = 0;
	dfChecks = new DFChecks(this,g);
	minispecDialog = new TextEditDialog(GetMainWindow()->GetWidget());
	minispecDialog->Initialize();
	minispecDialog->SetTitle("Minispec Editor");
	minispecDialog->SetCancelCallback(0, 0);
	minispecDialog->SetOKCallback(DFStubs::MinispecOKCB, this);
	minispecDialog->SetTextSize(12, 60);
}

DFDiagram::~DFDiagram() {
	delete minispecDialog;
	delete dfChecks;
}

Thing *DFDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	DFGraph *dg = (DFGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());
	// node shapes
	else if (classNr == Code::SQUARE)
		thing = new Square(v, g, 0, 0);
	else if (classNr == Code::HORIZONTAL_BAR)
		thing = new HorizontalBar(v, g, 0, 0);
	else if (classNr == Code::CIRCLE) {
		Circle *c = new Circle(v, g, 0, 0);
		c->SetFixedIndexLabel(False);
		thing = c;
	}
	else if (classNr == Code::BLACK_DOT)
		thing = new BlackDot(v, g, 0, 0);
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0);
	// lines
	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);
	else if (classNr == Code::ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd1(LineEnd::EMPTY);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		thing = line;
	}
	else if (classNr == Code::DOUBLE_ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd1(LineEnd::FILLED_ARROW);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		thing = line;
	}
	// nodes
	else if (classNr == Code::EXTERNAL_ENTITY)
		thing = new ExternalEntity(dg);
	else if (classNr == Code::DATA_STORE)
		thing = new DataStore(dg);
	else if (classNr == Code::DATA_PROCESS)
		thing = new DataProcess(dg);
	else if (classNr == Code::SPLIT_MERGE_NODE)
		thing = new SplitMergeNode(dg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(dg);
	// edges
	else if (classNr == Code::DATA_FLOW)
		thing = new DataFlow(dg, 0, 0);
	else if (classNr == Code::BIDIRECTIONAL_DATA_FLOW)
		thing = new BidirectionalDataFlow(dg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *DFDiagram::CreateNode(){
	Node *node = 0;
	DFGraph *dg = (DFGraph *)GetGraph();
	if (GetNodeType() == Code::EXTERNAL_ENTITY)
		node = new ExternalEntity(dg);
	else if (GetNodeType() == Code::DATA_PROCESS)
		node = new DataProcess(dg);
	else if (GetNodeType() == Code::DATA_STORE)
		node = new DataStore(dg);
	else if (GetNodeType() == Code::SPLIT_MERGE_NODE)
		node = new SplitMergeNode(dg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(dg);
	else {
		error("%s, line %d: unknown node type\n", 
				__FILE__, __LINE__);
	}
	return node;
}

Edge *DFDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge *edge = 0;
	DFGraph *dg = (DFGraph *)GetGraph();
	if (GetEdgeType() == Code::DATA_FLOW)
		edge = new DataFlow(dg, subj1, subj2);
	else if (GetEdgeType() == Code::BIDIRECTIONAL_DATA_FLOW)
		edge = new BidirectionalDataFlow(dg, subj1, subj2);
	else
		error("%s, line %d: unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *DFDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::HORIZONTAL_BAR)
		shape = new HorizontalBar(v, g, x, y);
	else if (GetNodeShapeType() == Code::CIRCLE) {
		Circle *c = new Circle(v, g, x, y);
		c->SetFixedIndexLabel(False);
		shape = c;
	}
	else if (GetNodeShapeType() == Code::SQUARE)
		shape = new Square(v, g, x, y);
	else if (GetNodeShapeType() == Code::BLACK_DOT)
		shape = new BlackDot(v, g, x, y);
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

Line *DFDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	if (GetLineType() == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);

	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());
	}
	return line;
}

void DFDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::DATA_PROCESS);
		SetNodeShapeType(Code::CIRCLE);
		break;
	case 2: SetNodeType(Code::DATA_STORE);
		SetNodeShapeType(Code::HORIZONTAL_BAR);
		break;
	case 3: SetNodeType(Code::EXTERNAL_ENTITY);
		SetNodeShapeType(Code::SQUARE);
		break;
	case 4: SetNodeType(Code::SPLIT_MERGE_NODE);
		SetNodeShapeType(Code::BLACK_DOT);
		break;
	case 5: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void DFDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	SetLineType(Code::LINE);
	switch(num) {
	case 1: SetEdgeType(Code::DATA_FLOW);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 2: SetEdgeType(Code::BIDIRECTIONAL_DATA_FLOW);
		SetLineEnd1(LineEnd::FILLED_ARROW);
                SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool DFDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False;
	if (subj1 == subj2) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"Cannot add a flow from and to the same node.");
		return False;
	}
	int subj1Type = subj1->GetClassType();
	int subj2Type = subj2->GetClassType();
	// Cannot connect a data process with a splitmerge node
	// when they are already connected (even in the opposite direction).
	if ((GetEdgeType()==Code::DATA_FLOW||
	     GetEdgeType()==Code::CONTINUOUS_DATA_FLOW) &&
		(subj1Type==Code::DATA_PROCESS &&
		 subj2Type==Code::SPLIT_MERGE_NODE ||
		 subj1Type==Code::SPLIT_MERGE_NODE &&
		 subj2Type==Code::DATA_PROCESS) &&
		(GetGraph()->IsConnected(subj2, subj1) ||
		 GetGraph()->IsConnected(subj1, subj2))) {
		ShowDialog(MessageDialog::ERROR, "Error",
			"Cannot add another data flow here. ");
		return False;
	}
	return True;
}

bool DFDiagram::HasIndexNode(int code) {
	return (code == Code::DATA_PROCESS || code == Code::CONTROL_PROCESS);
}

bool DFDiagram::HasIndexShape(int code) {
	return (code == Code::CIRCLE);
}

void DFDiagram::EditMinispec(Subject *s) {
	if (s->GetClassType() != Code::DATA_PROCESS) {
		ShowDialog(MessageDialog::ERROR, "Not a data process",
			"Only data processes can have a minispec");
		return;
	}
	if (minispecDialog->IsManaged()) {
		ShowDialog(MessageDialog::WARNING, "Warning",
			"You can only open one minispec editor at a time.");
		return;
	}
	editProcess = (DataProcess *)s;
	if (editProcess->IsProcessGroup()) {
		ShowDialog(MessageDialog::ERROR, "A process group",
			"This data process is a process group,\n"
			"so it cannot have a minispec");
		editProcess = 0;
		return;
	}
	const string *n = editProcess->GetIndex();
	const string *spec = editProcess->GetMinispec();
	string x = "Minispec of process ";
	string title = x + *n;
	minispecDialog->SetTitle(&title);
	minispecDialog->SetTextString(spec);
	minispecDialog->Popup();
}

void DFDiagram::SetMinispec() {
	SetStatus("action: Update minispec");
	if (!check(editProcess))
		return;
	string t;
	minispecDialog->GetTextString(&t);
	editProcess->SetMinispec(&t);
}

void DFDiagram::SetDiagram(const string *dfd) {
	DFGraph *dg = (DFGraph *)GetGraph();
	string sdfd = *dfd;
	if (((*dfd == "") || DFProcess::CorrectIndex(&sdfd)) && 
	     (*dfd != "0")) {
		dg->SetIndexPrefix(&sdfd);
		((DFWindow *)GetMainWindow())->SetDiagram(dfd);
		if (sdfd == "")
			sdfd = "0";
		string txt = "diagram " + sdfd + " is the current diagram";
		SetStatus(&txt);
	}
	else {
		const string s = *dg->GetIndexPrefix();
		((DFWindow *)GetMainWindow())->SetDiagram(&s);
		string txt = "'";
		txt += *dfd;
		txt += "' wrong syntax for \na data flow diagram index";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
	}
}

void DFDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += dfChecks->CheckNamelessNodes(Code::DATA_PROCESS, chkbuf);
	total += dfChecks->CheckNamelessNodes(Code::DATA_STORE, chkbuf);
	total += dfChecks->CheckNamelessNodes(Code::EXTERNAL_ENTITY, chkbuf);
	total += dfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
		Code::EXTERNAL_ENTITY, Code::DATA_PROCESS, chkbuf);
	total += dfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
		Code::DATA_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
		Code::DATA_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dfChecks->CheckDoubleNodes(Code::DATA_PROCESS, chkbuf);
	total += dfChecks->CheckDoubleNodes(Code::DATA_STORE, chkbuf);
	total += dfChecks->CheckDoubleNodes(Code::EXTERNAL_ENTITY, chkbuf);
	total += dfChecks->CheckDoubleIndexes(chkbuf);
	total += dfChecks->CheckDataProcessCoherence(chkbuf);
	total += dfChecks->CheckConnected(Code::DATA_STORE, False, chkbuf);
	total += dfChecks->CheckConnected(Code::EXTERNAL_ENTITY, False, chkbuf);
	total += dfChecks->CheckSplitMergeNodeCoherence(chkbuf);
	total += dfChecks->CheckNamelessSplitMergeEdges(chkbuf);
	total += dfChecks->CheckMinispecs(chkbuf);
	ReportCheck(total, &chkbuf);
}
