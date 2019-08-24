////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl)
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
#include "stgraph.h"
#include "stviewer.h"
#include "stwindow.h"
#include "stchecks.h"
#include "messagedialog.h"
#include "replacedialog.h"
#include "initialstate.h"
#include "decisionpoint.h"
#include "transition.h"
#include "hexagon.h"
#include "textbox.h"
#include "comment.h"
#include "transitionarrow.h"
#include "initialstatebox.h"
#include "stdiagram.h"
#include "editstubs.h"
#include "system.h"
#include "printer.h"
#include <limits.h>

#ifdef MODELCHECK

#define MODELCHECK_SMV 1

#include "modelcheckdialog.h"

#if MODELCHECK_SMV
	#include "smv.h"
#else
	#include "kronos.h"
#endif

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#endif

const int STDiagram::BOX_WIDTH = 100;
const int STDiagram::BOX_HEIGHT = 38;
 
STDiagram::STDiagram(Config *c, STWindow *d, STViewer *v, STGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	GetReplaceDialog()->ManageNameOnlyToggle(True);
	stChecks = new STChecks(this,g);
#ifdef MODELCHECK
	promptDialog = new ModelCheckDialog(GetMainWindow()->GetWidget());
	promptDialog->Initialize();
#endif
}


STDiagram::~STDiagram() {
#ifdef MODELCHECK
	delete promptDialog;
#endif
	delete stChecks;
}


Thing *STDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	STGraph *sg = (STGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());
	// node shapes
	else if (classNr == Code::ARROW_BOX)
		thing = new InitialStateBox(v, g, 0, 0); 
	else if (classNr == Code::BOX)
		thing = new Box(v, g, 0, 0); 
	else if (classNr == Code::HEXAGON)
		thing = new Hexagon(v, g, 0, 0); 
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	// lines
	else if (classNr == Code::TRANSITION_ARROW)
		thing = new TransitionArrow(v, g, 0, 0, 0);
	// nodes
	else if (classNr == Code::INITIAL_STATE)
		thing = new InitialState(sg);
	else if (classNr == Code::STATE)
		thing = new State(sg);
	else if (classNr == Code::DECISION_POINT)
		thing = new DecisionPoint(sg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(sg);
	// edges
	else if (classNr == Code::TRANSITION)
		thing = new Transition(sg, 0, 0);
	else 
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *STDiagram::CreateNode(){
	Node *node = 0;
	STGraph *sg = (STGraph *)GetGraph();
	if (GetNodeType() == Code::INITIAL_STATE)
		node = new InitialState(sg);
	else if (GetNodeType() == Code::STATE)
		node = new State(sg);
	else if (GetNodeType() == Code::DECISION_POINT)
		node = new DecisionPoint(sg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(sg);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *STDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0; 
	Edge *edge = 0;
	STGraph *sg = (STGraph *)GetGraph();
	if (GetEdgeType() == Code::TRANSITION)
		edge = new Transition(sg, subj1, subj2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *STDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::ARROW_BOX)
		shape = new InitialStateBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::BOX)
		shape = new Box(v, g, x, y);
	else if (GetNodeShapeType() == Code::HEXAGON)
		shape = new Hexagon(v, g, x, y);
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

Line *STDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Line *line = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	*((*l)[0]) = *(from->GetPosition());
	*((*l)[l->count()-1]) = *(to->GetPosition());
	if (GetLineType() == Code::TRANSITION_ARROW)
		line = new TransitionArrow(v, g, from, to, l, IsCurve());
	else
		error("%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);

	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
	}
	return line;
}

void STDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::INITIAL_STATE);
		SetNodeShapeType(Code::ARROW_BOX);
		break;
	case 2: SetNodeType(Code::STATE);
		SetNodeShapeType(Code::BOX);
		break;
	case 3: SetNodeType(Code::DECISION_POINT);
		SetNodeShapeType(Code::HEXAGON);
		break;
	case 4: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void STDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::TRANSITION);
		SetLineType(Code::TRANSITION_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool STDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False;
	// Check that two different initial states can't be connected.
	else if (subj1->GetClassType() == Code::INITIAL_STATE &&
		 subj2->GetClassType() == Code::INITIAL_STATE && subj1 != subj2) {
		 ShowDialog(MessageDialog::ERROR, "Error", 
		 	"Cannot connect different initial states");
		 return False;
	}
	// Check that a decision point can not be connected to itself.
	else if (subj1->GetClassType() == Code::DECISION_POINT && subj1 == subj2) {
		 ShowDialog(MessageDialog::ERROR, "Error",
		 	"Cannot connect a decision point with itself");
		 return False;
	}

	// Check that two subjs are not reachable from different initial states.
	InitialState *init1, *init2;
	init1 = FindInitialState(subj1); init2 = FindInitialState(subj2);
	if (init1 && init2) {
		if (init1 != init2) {
			ShowDialog(MessageDialog::ERROR, "Error",
				"Cannot connect nodes from different STDs");
			return False;
		}
	}
	return True;
}

bool STDiagram::SetEvent(Transition *t, const string *s) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(t, &shapes);
	Subject::NameErrType n = t->SetEvent(s);
	if (n == Subject::OK) {
		if (shapes.first())
			do
				((TransitionArrow *)shapes.cur())->UpdateEvent(s);
			while (shapes.next());
		else {
			error("%s, line %d: shape does not exist\n", 
					__FILE__, __LINE__);
			return False;
		}
		return True;
	}
	else if (n == Subject::IMPOSSIBLE_NAME) {
		string msg = "'" + *s + "' wrong syntax\n for an event string";
		ShowDialog(MessageDialog::ERROR, "Error", &msg);
		return False;
	}
	else if (n == Subject::DOUBLE_EDGE) {
		string msg = "there is already a transition with\n"
			"event string '" + *s + "' between this pair of states";
		ShowDialog(MessageDialog::ERROR, "Error", &msg);
		return False;
	}
	else {
		error("%s, line %d: case not handled\n", __FILE__, __LINE__);
	}
	return True;
}

bool STDiagram::SetAction(Subject *t, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(t, &shapes);
	unsigned m = nr;
	// split string in different one line strings.
	string ss(*s);
	char *str = (char *)ss.getstr();
	char empty[2] = "";
	char *x = strtok(str, "\r");
	if (x == 0)
		x = empty;
	while (x != 0) {
		string *ns = new string(x);
		bool update = True;
		Subject::NameErrType result;
		if (m == nr) {
			if (t->IsEdge())
				result = ((Transition *)t)->SetAction(ns, m, True);
			else
				result = ((InitialState *)t)->SetAction(ns, m, True);
		}
		else {
			if (t->IsEdge())
				result = ((Transition *)t)->SetAction(ns, m, False);
			else
				result = ((InitialState *)t)->SetAction(ns, m, False);
			update = False;
		}
		if (result != Subject::OK) {
			string msg;
			if (result == Subject::HAS_ACTION)
				msg = "transition already has an action '" + *ns + "'";
			else
				msg = "'" + *ns + "' wrong syntax\n for an action string";
			ShowDialog(MessageDialog::ERROR, "Error", &msg);
			// make actions empty.
			*ns = "";
			if (!update) {
				for (shapes.first(); !shapes.done(); shapes.next()) {
					if (t->IsEdge())
						((TransitionArrow *)shapes.cur())->
							UpdateAction(ns, m, update);
					else
						((InitialStateBox *)shapes.cur())->
							UpdateAction(ns, m, update);
				}
			} 
			delete ns;
			return False;
		}
		// update the shapes.
		if (shapes.first())
			do {
				if (t->IsEdge())
					((TransitionArrow *)shapes.cur())->
						UpdateAction(ns, m, update);
				else
					((InitialStateBox *)shapes.cur())->
						UpdateAction(ns, m, update);
			} while (shapes.next());
		else {
			error("%s, line %d: shape does not exist\n", 
					__FILE__, __LINE__);
			return False;
		}
		m++;
		x = strtok(0, "\r");
		delete ns;
	}
	return True;
}

InitialState *STDiagram::FindInitialState(Subject *state) {
	if (state->GetClassType() == Code::INITIAL_STATE)
		return (InitialState *)state;
	List<Subject *> initStates;
	GetGraph()->GetNodes(&initStates, Code::INITIAL_STATE);
	for (initStates.first(); !initStates.done(); initStates.next()) {
		InitialState *init = (InitialState *)initStates.cur();
		if (GetGraph()->UndirectedPathExists(init, state))
			return init;
	} 
	return 0;
}

void STDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += stChecks->CheckNamelessNodes(Code::INITIAL_STATE, chkbuf);
	total += stChecks->CheckNamelessNodes(Code::STATE, chkbuf);
	total += stChecks->CheckNamelessNodes(Code::DECISION_POINT, chkbuf);
	total += stChecks->CheckDoubleNodes(Code::STATE, chkbuf);
	total += stChecks->CheckDoubleNodes(Code::DECISION_POINT, chkbuf);
	total += stChecks->CheckDoubleEvents(chkbuf);
	total += stChecks->CheckEmptyEvents(chkbuf);
	total += stChecks->CheckEmptyActions(chkbuf);
	total += stChecks->CheckNoActions(chkbuf);
	total += stChecks->CheckCountEdgesFrom(Code::DECISION_POINT, 
		Code::TRANSITION, 2, INT_MAX, False, False, chkbuf);
	int sub = stChecks->CheckNodeCount(1, Code::INITIAL_STATE, chkbuf);
	total += sub;
	if (sub == 0) {
		total += stChecks->CheckReachability(
			Code::INITIAL_STATE, Code::STATE, False, chkbuf);
		total += stChecks->CheckReachability(
			Code::INITIAL_STATE, Code::DECISION_POINT, False, chkbuf);
	}
	ReportCheck(total, &chkbuf);
}


#ifdef MODELCHECK
void STDiagram::ModelCheckProperty() {
	SetStatus("action: model check document semantics");
	promptDialog->SetTitle("Model check document semantics");
	promptDialog->SetOKCallback(ModelCheckDocumentOKCB, this);
	promptDialog->Popup();
}


/* static */ void STDiagram::ModelCheckDocumentOKCB(Widget,
		XtPointer clientData, XtPointer)
{
	STDiagram *std = (STDiagram *)clientData;
	string formula, internal, clock;
	std->promptDialog->GetFormulaString(&formula);
	std->promptDialog->GetInternString(&internal);
	std->promptDialog->GetClockString(&clock);
	std->DoModelCheckDocument(&internal, &formula, &clock);
}


void STDiagram::DoModelCheckDocument(const string *internal,
			const string *formula, const string *clock)
{
	SetStatus("action: model check document semantics");
	GetMainWindow()->SetCursor(MouseCursor::WATCH);
	string tmpModel;
tmpModel = "model";
//	GetViewer()->GetPrinter()->MakeTmpFile(&tmpModel);
#if MODELCHECK_SMV
	tmpModel += ".smv";
#else
	tmpModel += ".tg";
#endif
std::cerr << "Temporary model file: " << tmpModel.getstr() << '\n';

	SaveForModelChecker(&tmpModel, internal, clock, formula);
	bool ok = ExecuteModelChecker(&tmpModel, formula);
	GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
//	unlink(tmpModel.getstr());
	if ( ! ok )
		SetStatus("model checking aborted");
	else
		SetStatus("model checking completed");
	return;
}


void STDiagram::SaveForModelChecker(const string *path, const string *internal,
			const string * clock, const string *formula) {
	/* Split internal into a list of strings */
	List<string> intevent;
	if ( internal ) {
		const char *cp = internal->getstr();
		while ( *cp ) {
			while ( *cp && isspace(*cp) )
				++cp;
			if ( ! *cp )
				break;
			const char *ep = cp;
			if ( '[' == *cp ) {
				while ( *++ep )
					if ( ']' == *ep ) {
						++ep;
						break;
					}
			} else
				while ( *++ep && ! isspace(*ep) && '[' != *ep )
					;
			string event;
			event.add(cp, ep - cp);
			intevent.add(event);
			cp = ep;
		}
	}

#if MODELCHECK_SMV
	SMV s(GetGraph());
	s.WriteSMV(path->getstr(), &intevent, formula);
#else
	Kronos kr(this);
	kr.GenerateKronos(&intevent);
	kr.SaveKronos(path->getstr(), clock->getstr());
#endif
}


bool STDiagram::ExecuteModelChecker(const string *path, const string *formula) {
#if MODELCHECK_SMV
	return False;
#else
	string tmpFormula;
tmpFormula = "/home/maics/dnjansen/kronos/formula";
//	GetViewer()->GetPrinter()->MakeTmpFile(&tmpFormula);
	tmpFormula += ".tctl";
	FILE *fp;
	if ( (fp = fopen(tmpFormula.getstr(), "w")) == NULL ||
	    fputs(formula->getstr(), fp) == EOF ) {
		string txt("error, ");
		txt += tmpFormula;
		txt += "\ncannot be written";
		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::INFORMATION))->
			Show("Notice", &txt);
		return False;
	}
	fclose(fp);
	string command;
command = "/home/maics/dnjansen/kronos/bin/kronos";
//	read config...
	command += " -v -reach ";
	command += tmpFormula;
	command += ' ';
	command += *path;
	int status = system(command.getstr());
//	unlink(tmpFormula.getstr());
	if (status) {
		string txt = "error, " + command;
		txt += "\ncannot be executed";
		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::INFORMATION))->
			Show("Notice", &txt);
		return False;
	}
	return True;
#endif
}
#endif


bool STDiagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Event")
		return SetEvent((Transition *)subj, s);
	else if (*description == "Action")
		return SetAction(subj, s, t->GetSequence());
	else 
		return Diagram::SetText(t, s);
}
