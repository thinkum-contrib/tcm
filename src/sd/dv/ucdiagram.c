//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "ucgraph.h"
#include "ucwindow.h"
#include "ucviewer.h"
#include "ucchecks.h"
#include "messagedialog.h"
#include "ucdsingleclassbox.h"
#include "c2r2line.h"
#include "ucdactornode.h"
#include "ucdusecasenode.h"
#include "ucdbinaryassociationedge.h"
#include "ucdboundarybox.h"
#include "ucdgeneralizationedge.h"
#include "commentlink.h"
#include "ucdsystemnode.h"
#include "stickman.h"
#include "ellipse.h"
#include "notebox.h"
#include "comment.h"
#include "textbox.h"
#include "ucdiagram.h"
#include "note.h"
#include <stdio.h>
#include <limits.h>

UCDiagram::UCDiagram(Config *c, UCWindow *d, UCViewer *v, UCGraph *g): 
	   ERDiagram(c, d, v, g) {
	UpdateNodeType(1);
        UpdateEdgeType(1);
	ucChecks = new UCChecks(this, g);
}

UCDiagram::~UCDiagram() {
	delete ucChecks;
}

Thing *UCDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	UCGraph *cg = (UCGraph *)GetGraph();
	Thing *thing = 0;
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());

	// node shapes
	else if (classNr==Code::UCD_SINGLE_CLASS_BOX)
		thing = new UCDSingleClassBox(v, g, 0, 0); 
	else if (classNr == Code::STICKMAN)
                thing = new StickMan(v, g, 0, 0);
	else if (classNr == Code::ELLIPSE)
                thing = new Ellipse(v, g, 0, 0);
	else if (classNr == Code::UCD_BOUNDARY_BOX)
		thing = new UCDBoundaryBox(v, g, 0, 0);
	else if (classNr==Code::NOTE_BOX)
		thing = new NoteBox(v, g, 0, 0); 
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 

	// lines
	else if (classNr==Code::T4_LINE || classNr==Code::C2R2_LINE)
		thing = new C2R2Line(v, g, 0, 0, 0);
	else if (classNr==Code::LINE)
		thing = new Line(v, g, 0, 0, 0);

	// nodes
	else if (classNr==Code::UCD_ACTOR_NODE)
		thing = new UCDActorNode(cg);
	else if (classNr==Code::UCD_USE_CASE_NODE)
		thing = new UCDUseCaseNode(cg);
	else if (classNr==Code::UCD_SYSTEM_NODE)
		thing = new UCDSystemNode(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);
	else if (classNr==Code::NOTE)
		thing = new Note(cg);

	// edges
	else if (classNr==Code::BINARY_RELATIONSHIP || classNr==Code::UCD_BINARY_ASSOCIATION_EDGE)
		thing = new UCDBinaryAssociationEdge(cg, 0, 0);
	else if (classNr==Code::ISA_RELATIONSHIP || classNr==Code::UCD_GENERALIZATION_EDGE)
		thing = new UCDGeneralizationEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);

	else
		error("%s, line %d: impl error: wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
	return thing;
}
 
Node *UCDiagram::CreateNode(){
	Node *node = 0;
	UCGraph *g = (UCGraph *)GetGraph();

	if (GetNodeType()==Code::UCD_ACTOR_NODE)
		node = new UCDActorNode(g);
	else if (GetNodeType()==Code::UCD_USE_CASE_NODE)
		node = new UCDUseCaseNode(g);
	else if (GetNodeType()==Code::UCD_SYSTEM_NODE)
		node = new UCDSystemNode(g);
	else if (GetNodeType()==Code::COMMENT)
		node = new Comment(g);
	else if (GetNodeType()==Code::NOTE)
		node = new Note(g);
	else
		error( "%s, line %d: impl error: unknown node type\n", 
			__FILE__, __LINE__);
	return node;
}

Edge *UCDiagram::CreateEdge(Subject *subj1, Subject* subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge* edge = 0;
	UCGraph *g = (UCGraph *)GetGraph();
	if (GetEdgeType() == Code::UCD_BINARY_ASSOCIATION_EDGE)
		edge = new UCDBinaryAssociationEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::UCD_GENERALIZATION_EDGE)
		edge = new UCDGeneralizationEdge(g, subj1, subj2);
	else if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, subj1, subj2);
	else
		error( "%s, line %d: impl error: unknown edge type\n", 
			__FILE__, __LINE__);

	if (GetEdgeType() == Code::UCD_GENERALIZATION_EDGE) {
		if (!CheckIsaLoop(edge)) {
			delete edge;
			return 0;
		}
	}
	return edge;
}

NodeShape *UCDiagram::CreateNodeShape(Node* node, int x, int y) {
	NodeShape* shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::STICKMAN)
		shape = new StickMan(v, g, x, y);
	else if (GetNodeShapeType() == Code::UCD_SINGLE_CLASS_BOX)
		shape = new UCDSingleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::ELLIPSE)
		shape = new Ellipse(v, g, x, y);
	else if (GetNodeShapeType() == Code::UCD_BOUNDARY_BOX)
		shape = new UCDBoundaryBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else
		error( "%s, line %d: impl error: "
			"node shape type doesn't exist\n", __FILE__, __LINE__);
	
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *UCDiagram::CreateLine(Edge* edge, GShape *from, GShape *to, List<Point*> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line* line = 0;
	if (GetLineType()== Code::C2R2_LINE)
		line = new C2R2Line(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error( "%s, line %d: impl error: "
			"edge shape type does not exist\n", __FILE__, __LINE__);
	
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
                line->SetEnd2(GetLineEnd2());

		if (GetEdgeType()==Code::COMMENT_LINK)
                        line->SetFixedName(True);
	}
	return line;
}

void UCDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::UCD_ACTOR_NODE);
		SetNodeShapeType(Code::STICKMAN);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::UCD_ACTOR_NODE);
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::UCD_USE_CASE_NODE);
		SetNodeShapeType(Code::ELLIPSE);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::UCD_SYSTEM_NODE);
		SetNodeShapeType(Code::UCD_BOUNDARY_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 5: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 6: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		SetNodeLineStyle(LineStyle::INVISIBLE);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void UCDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::UCD_BINARY_ASSOCIATION_EDGE);
		SetLineType(Code::C2R2_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::UCD_GENERALIZATION_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::WHITE_TRIANGLE);
		break;
	case 3: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;

	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

void UCDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	// Check that actors and use cases are named.
	total += ucChecks->CheckNamelessNodes(Code::UCD_ACTOR_NODE, chkbuf);
	total += ucChecks->CheckNamelessNodes(Code::UCD_USE_CASE_NODE, chkbuf);

	// double nodes can occur after cut-copy-paste
	total += ucChecks->CheckDoubleNodes(Code::UCD_ACTOR_NODE, chkbuf);
	total += ucChecks->CheckDoubleNodes(Code::UCD_USE_CASE_NODE, chkbuf);

	ReportCheck(total, &chkbuf);
}

bool UCDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
        // Check possible connections (subj-subj-edge matrix).
        if (!CheckConnection(subj1, subj2))
                return False;
	// int subj1Type = subj1->GetClassType();
	// int subj2Type = subj2->GetClassType();
	// Check for double is_a between same nodes.
	if (GetEdgeType()==Code::UCD_GENERALIZATION_EDGE &&
	    GetGraph()->IsConnected(subj1, subj2, Code::UCD_GENERALIZATION_EDGE)) {
		string txt = "Cannot add another ";
		txt += Code::GetName(GetEdgeType());
		txt += " here";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	return True;
}


bool UCDiagram::CheckIsaLoop(Edge *edge) {
        if (GetEdgeType() == Code::UCD_GENERALIZATION_EDGE) {
                GetGraph()->AddEdge(edge);
                Subject *n1 = edge->GetSubject1();
                if (GetGraph()->PathExists(n1, n1, Code::UCD_GENERALIZATION_EDGE)) {
                        string txt = "'is_a loops' are not allowed";
                        ShowDialog(MessageDialog::ERROR, "Error", &txt);
                        GetGraph()->RemoveEdge(edge);
                        return False;
                }
                GetGraph()->RemoveEdge(edge);
        }
        return True;
}

bool UCDiagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Cardinality Constraint")
		return SetConstraint(subj, s, t->GetSequence());
	else if (*description == "Role Name")
		return SetRoleName(subj, s, t->GetSequence()%2);
	else
		return Diagram::SetText(t, s);
}

bool UCDiagram::SetConstraint(Subject *subject, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	bool wrong_syntax = False;
	Edge *e = (Edge *)subject;
	int eType = e->GetClassType();
	if (eType == Code::UCD_BINARY_ASSOCIATION_EDGE) {
		BinaryRelationship *edge = (BinaryRelationship *)subject;
		if (nr == 1) {
			if (!edge->SetConstraint1(s))
				wrong_syntax = True;
		}
		else if (nr == 2) {
			if (!edge->SetConstraint2(s))
				wrong_syntax = True;
		}
	}
	if (wrong_syntax) {
		string txt = "'" + *s + "' wrong syntax\n for a "
					"cardinality constraint";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	if (check(shapes.first())) {
		do {
			if (nr == 1)
				((C2R2Line *)shapes.cur())->UpdateTextShape1(s);
			else
				((C2R2Line *)shapes.cur())->UpdateTextShape2(s);
		}
		while (shapes.next());
	}
	else 
		return False;
	return True;
}

bool UCDiagram::SetRoleName(Subject *subject, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	BinaryRelationship *edge = (BinaryRelationship *)subject;
	bool succes = True;
	if (nr == 1) {
		if (!edge->SetRoleName1(s))
			succes = False;
	}
	else {
		if (!edge->SetRoleName2(s))
			succes = False;
	}
	if (!succes) {
		string txt = "'" + *s + "' is not a possible role name";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	if (check(shapes.first())) {
		do {
			Shape *shape = shapes.cur();
			if (nr == 1)
				((C2R2Line *)shape)->UpdateTextShape3(s);
			else 
				((C2R2Line *)shape)->UpdateTextShape4(s);
		} while (shapes.next());
	}
	else 
		return False;
	return True;
}
