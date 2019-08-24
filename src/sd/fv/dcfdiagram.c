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
#include "dcfwindow.h"
#include "dcfgraph.h"
#include "dcfviewer.h"
#include "dcfstubs.h"
#include "dcfchecks.h"
#include "externalentity.h"
#include "datastore.h"
#include "eventstore.h"
#include "dataprocess.h"
#include "controlprocess.h"
#include "splitmergenode.h"
#include "bidirectionaldataflow.h"
#include "continuousdataflow.h"
#include "continuouseventflow.h"
#include "square.h"
#include "circle.h"
#include "line.h"
#include "horizontalbar.h"
#include "textbox.h"
#include "blackdot.h"
#include "comment.h"
#include "dcfdiagram.h"
#include "togglelistdialog.h"
#include <ctype.h>
 
DCFDiagram::DCFDiagram(Config *c, DCFWindow *d, DCFViewer *v, DCFGraph *g): 
		DFDiagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	dcfChecks = new DCFChecks(this,g);
	List<string *> l;
	l.add(new string("Continuing			    "));
	l.add(new string("Instantaneous			 "));
	persistenceDialog = new ToggleListDialog(d->GetWidget(), False);
	persistenceDialog->Initialize();
	persistenceDialog->SetTitle("Process persistence");
	persistenceDialog->CreateToggles(&l);
	persistenceDialog->ManageCancelButton(False);
	persistenceDialog->SetToggleChangedCallback(
		DCFStubs::PersistenceOKCB, this);
	l.clear();
	l.add(new string("Stimulus			"));
	l.add(new string("Time				"));
	l.add(new string("Trigger			"));
	l.add(new string("Unspecified			"));
	activationDialog = new ToggleListDialog(d->GetWidget(), True);
	activationDialog->Initialize();
	activationDialog->SetTitle("Process activation");
	activationDialog->CreateToggles(&l);
	activationDialog->ManageCancelButton(False);
	activationDialog->SetToggleChangedCallback(
		DCFStubs::ActivationToggleCB, this);
	activationDialog->SetOKCallback(DCFStubs::ActivationOKCB, this);
	l.clear();
}

DCFDiagram::~DCFDiagram() {
	delete dcfChecks;
	delete activationDialog;
	delete persistenceDialog;
}

Thing *DCFDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	DCFGraph *dg = (DCFGraph *)GetGraph();
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
	else if (classNr == Code::DOUBLE_HEADED_ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd1(LineEnd::EMPTY);
		line->SetEnd2(LineEnd::DOUBLE_FILLED_ARROW);
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
	else if (classNr == Code::CONTROL_PROCESS)
		thing = new ControlProcess(dg);
	else if (classNr == Code::EVENT_STORE)
		thing = new EventStore(dg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(dg);
	// edges
	else if (classNr == Code::DATA_FLOW)
		thing = new DataFlow(dg, 0, 0);
	else if (classNr == Code::BIDIRECTIONAL_DATA_FLOW)
		thing = new BidirectionalDataFlow(dg, 0, 0);
	else if (classNr == Code::EVENT_FLOW)
		thing = new EventFlow(dg, 0, 0);
	else if (classNr == Code::CONTINUOUS_DATA_FLOW)
		thing = new ContinuousDataFlow(dg, 0, 0);
	else if (classNr == Code::CONTINUOUS_EVENT_FLOW)
		thing = new ContinuousEventFlow(dg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *DCFDiagram::CreateNode(){
	Node *node = 0;
	DCFGraph *g = (DCFGraph *)GetGraph();
	if (GetNodeType() == Code::EXTERNAL_ENTITY)
		node = new ExternalEntity(g);
	else if (GetNodeType() == Code::DATA_PROCESS)
		node = new DataProcess(g);
	else if (GetNodeType() == Code::CONTROL_PROCESS)
		node = new ControlProcess(g);
	else if (GetNodeType() == Code::DATA_STORE)
		node = new DataStore(g);
	else if (GetNodeType() == Code::EVENT_STORE)
		node = new EventStore(g);
	else if (GetNodeType() == Code::SPLIT_MERGE_NODE)
		node = new SplitMergeNode(g);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(g);
	else
		error("%s, line %d: unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *DCFDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge *edge = 0;
	DCFGraph *g = (DCFGraph *)GetGraph();
	if (GetEdgeType() == Code::DATA_FLOW)
		edge = new DataFlow(g, subj1, subj2);
	else if (GetEdgeType() == Code::BIDIRECTIONAL_DATA_FLOW)
		edge = new BidirectionalDataFlow(g, subj1, subj2);
	else if (GetEdgeType() == Code::EVENT_FLOW)
		edge = new EventFlow(g, subj1, subj2);
	else if (GetEdgeType() == Code::CONTINUOUS_DATA_FLOW)
		edge = new ContinuousDataFlow(g, subj1, subj2);
	else if (GetEdgeType() == Code::CONTINUOUS_EVENT_FLOW)
		edge = new ContinuousEventFlow(g, subj1, subj2);
	else
		error("%s, line %d: unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *DCFDiagram::CreateNodeShape(Node *node, int x, int y){
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::CIRCLE) {
		Circle *c = new Circle(v, g, x, y);
		c->SetFixedIndexLabel(False);
		shape = c;
	}
	else if (GetNodeShapeType() == Code::SQUARE)
		shape = new Square(v, g, x, y);
	else if (GetNodeShapeType() == Code::HORIZONTAL_BAR)
		shape = new HorizontalBar(v, g, x, y);
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

Line *DCFDiagram::CreateLine(
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

void DCFDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::DATA_PROCESS);
		SetNodeShapeType(Code::CIRCLE);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::CONTROL_PROCESS);
		SetNodeShapeType(Code::CIRCLE);
		SetNodeLineStyle(LineStyle::DASHED);
		break;
	case 3: SetNodeType(Code::EXTERNAL_ENTITY);
		SetNodeShapeType(Code::SQUARE);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::DATA_STORE);
		SetNodeShapeType(Code::HORIZONTAL_BAR);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 5: SetNodeType(Code::EVENT_STORE);
		SetNodeShapeType(Code::HORIZONTAL_BAR);
		SetNodeLineStyle(LineStyle::DASHED);
		break;
	case 6: SetNodeType(Code::SPLIT_MERGE_NODE);
		SetNodeShapeType(Code::BLACK_DOT);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 7: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		SetNodeLineStyle(LineStyle::INVISIBLE);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void DCFDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	SetLineType(Code::LINE);
	switch(num) {
	case 1: SetEdgeType(Code::DATA_FLOW);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		SetEdgeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetEdgeType(Code::EVENT_FLOW);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		SetEdgeLineStyle(LineStyle::DASHED);
		break;
	case 3: SetEdgeType(Code::BIDIRECTIONAL_DATA_FLOW);
		SetLineEnd1(LineEnd::FILLED_ARROW);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		SetEdgeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetEdgeType(Code::CONTINUOUS_DATA_FLOW);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::DOUBLE_FILLED_ARROW);
		SetEdgeLineStyle(LineStyle::SOLID);
		break;
	case 5: SetEdgeType(Code::CONTINUOUS_EVENT_FLOW);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::DOUBLE_FILLED_ARROW);
		SetEdgeLineStyle(LineStyle::DASHED);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

void DCFDiagram::AddSubject(Subject *subj) {
	DFDiagram::AddSubject(subj);
	int subjType = subj->GetClassType();
	if (subjType == Code::CONTINUOUS_DATA_FLOW || 
	    subjType == Code::CONTINUOUS_EVENT_FLOW) {
		Subject *n = ((Edge *)subj)->GetSubject1();
		if (n->GetClassType() == Code::DATA_PROCESS)
			((DataProcess *)n)->SetInstantaneous(False);
	}

}

void DCFDiagram::EditPersistence(Subject *s) {
	if (s->GetClassType() != Code::DATA_PROCESS) {
		ShowDialog(MessageDialog::ERROR, "Not a data process",
			"Only the persistence of data processes can be set.");
		return;
	}
	SetEditProcess((DataProcess *)s);
	if (GetEditProcess()->IsProcessGroup()) {
		ShowDialog(MessageDialog::ERROR, "A process group",
			"This data process is a process group,\n"
			"so you cannot set the persistence");
		SetEditProcess(0);
		return;
	}
	const string *n = GetEditProcess()->GetIndex();
	string x = "Persistence of process ";
	string title = x + *n;
	persistenceDialog->SetTitle(&title);
	bool ins = GetEditProcess()->IsInstantaneous();
	persistenceDialog->SetValue(ins);
	persistenceDialog->Popup();
}

void DCFDiagram::EditActivation(Subject *s) {
	if (s->GetClassType() != Code::DATA_PROCESS) {
		ShowDialog(MessageDialog::ERROR, "Not a data process",
		"Only activation mechanisms of data processes can be set.");
		return;
	}
	SetEditProcess((DataProcess *)s);
	if (GetEditProcess()->IsProcessGroup()) {
		ShowDialog(MessageDialog::ERROR, "A process group",
			"This data process is a process group,\n"
			"so you cannot set the activation mechanism");
		SetEditProcess(0);
		return;
	}
	else if (!GetEditProcess()->IsInstantaneous()) {
		ShowDialog(MessageDialog::ERROR, "A continuing process",
			"This data process is continuing,\n"
			"so you cannot set the activation mechanism");
		SetEditProcess(0);
		return;
	}
	const string *n = GetEditProcess()->GetIndex();
	string x = "Activation of process ";
	string title = x + *n;
	activationDialog->SetTitle(&title);
	DataProcess::ActivationType at = 
		GetEditProcess()-> GetActivationMechanism();
	if (at == DataProcess::STIMULUS)
		UpdateActivationDialog(0);
	else if (at == DataProcess::TIME)
		UpdateActivationDialog(1);
	else if (at == DataProcess::TRIGGER)
		UpdateActivationDialog(2);
	else
		UpdateActivationDialog(3);
	activationDialog->Popup();
}

void DCFDiagram::UpdateActivationDialog(int n) {
	activationDialog->SetValue(min(n, 3));
	if (n == 0) {
		activationDialog->ManageSelectionLabel(True);
		activationDialog->ManageTextString(True);
		activationDialog->SetSelectionLabel("Stimulus edge name");
		activationDialog->SetTextString(GetEditProcess()->GetStimulus());
	}
	else if (n == 1) {
		activationDialog->ManageSelectionLabel(True);
		activationDialog->ManageTextString(True);
		activationDialog->SetSelectionLabel("Time expression");
		activationDialog->SetTextString(GetEditProcess()->GetTimeExpression());
	}
	else {
		activationDialog->SetSelectionLabel("");
		activationDialog->SetTextString("");
		activationDialog->ManageSelectionLabel(False);
		activationDialog->ManageTextString(False);
	}
}
 
void DCFDiagram::SetPersistence() {
	SetStatus("action: Set persistence");
	if (!check(GetEditProcess()))
		return;
	bool b = persistenceDialog->GetValue();
	GetEditProcess()->SetInstantaneous(b);
}
 
void DCFDiagram::SetActivation() {
	SetStatus("action: Set activation");
	if (!check(GetEditProcess()))
		return;
	int n = activationDialog->GetValue();
	string s;
	if (n < 2) {
		activationDialog->GetTextString(&s);
	}
	if (n == 0) {
		GetEditProcess()->SetActivationMechanism(DataProcess::STIMULUS);
		GetEditProcess()->SetStimulus(&s);
	}
	else if (n == 1) {
		GetEditProcess()->SetActivationMechanism(DataProcess::TIME);
		GetEditProcess()->SetTimeExpression(&s);
	}
	else if (n == 2)
		GetEditProcess()->SetActivationMechanism(DataProcess::TRIGGER);
	else
		GetEditProcess()->SetActivationMechanism(DataProcess::UNSPECIFIED);
}

void DCFDiagram::UpdateActivationToggle() {
	SetStatus("action: Update activation toggle");
	if (!check(GetEditProcess()))
		return;
	int n = activationDialog->GetValue();
	UpdateActivationDialog(n);
}

bool DCFDiagram::CheckEdgeConstraints(Subject *s1, Subject *s2) {
	return DFDiagram::CheckEdgeConstraints(s1, s2);
}

void DCFDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += dcfChecks->CheckNamelessNodes(Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessNodes(Code::DATA_STORE, chkbuf);
	total += dcfChecks->CheckNamelessNodes(Code::EVENT_STORE, chkbuf);
	total += dcfChecks->CheckNamelessNodes(Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessNodes(Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
			Code::EXTERNAL_ENTITY, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::EXTERNAL_ENTITY, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_DATA_FLOW, 
			Code::EXTERNAL_ENTITY, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::EXTERNAL_ENTITY, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::EXTERNAL_ENTITY, Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::EXTERNAL_ENTITY, Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
			Code::DATA_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::DATA_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_DATA_FLOW, 
			Code::DATA_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::DATA_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::DATA_FLOW, 
			Code::DATA_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::DATA_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_DATA_FLOW, 
			Code::DATA_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::DATA_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::DATA_PROCESS, Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::DATA_PROCESS, Code::CONTROL_PROCESS, chkbuf);
	// nb. controlprocess -> data process should be a prompt.
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::CONTROL_PROCESS, Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::CONTROL_PROCESS, Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::CONTROL_PROCESS, Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::EVENT_FLOW, 
			Code::CONTROL_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckNamelessFlows(Code::CONTINUOUS_EVENT_FLOW, 
			Code::CONTROL_PROCESS, Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckDoubleNodes(Code::DATA_PROCESS, chkbuf);
	total += dcfChecks->CheckDoubleNodes(Code::DATA_STORE, chkbuf);
	total += dcfChecks->CheckDoubleNodes(Code::EVENT_STORE, chkbuf);
	total += dcfChecks->CheckDoubleNodes(Code::EXTERNAL_ENTITY, chkbuf);
	total += dcfChecks->CheckDoubleNodes(Code::CONTROL_PROCESS, chkbuf);
	total += dcfChecks->CheckDoubleIndexes(chkbuf);
	total += dcfChecks->CheckDataProcessCoherence(chkbuf);
	total += dcfChecks->CheckControlProcessCoherence(chkbuf);
	total += dcfChecks->CheckConnected(Code::DATA_STORE, False, chkbuf);
	total += dcfChecks->CheckConnected(Code::EVENT_STORE, False, chkbuf);
	total += dcfChecks->CheckConnected(
		Code::EXTERNAL_ENTITY, False, chkbuf);
	total += dcfChecks->CheckSplitMergeNodeCoherence(chkbuf);
	total += dcfChecks->CheckNamelessSplitMergeEdges(chkbuf);
	total += dcfChecks->CheckContinuousSplitMergeEdges(chkbuf);
	total += dcfChecks->CheckPersistences(chkbuf);
	total += dcfChecks->CheckActivationMechanisms(chkbuf);
	total += dcfChecks->CheckMinispecs(chkbuf);
	ReportCheck(total, &chkbuf);
}
