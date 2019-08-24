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
#include "crgraph.h"
#include "crwindow.h"
#include "crviewer.h"
#include "crchecks.h"
#include "messagedialog.h"
#include "grafport.h"
#include "tripleclassbox.h"
#include "doubleclassbox.h"
#include "c1arrow.h"
#include "c2r2line.h"
#include "binaryrelationship.h"
#include "componentfunction.h"
#include "isarelationship.h"
#include "modejunction.h"
#include "emptyedge.h"
#include "miniellipse.h"
#include "textbox.h"
#include "comment.h"
#include "crdiagram.h"
#include <limits.h>

CRDiagram::CRDiagram(Config *c, CRWindow *d, CRViewer *v, CRGraph *g): 
	   ERDiagram(c, d, v, g) {
	UpdateNodeType(1);
        UpdateEdgeType(1);
	crChecks = new CRChecks(this, g);
}

CRDiagram::~CRDiagram() {
	delete crChecks;
}

Thing *CRDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	CRGraph *cg = (CRGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());

	// node shapes
	else if (classNr==Code::TRIPLE_BOX)
		thing = new TripleClassBox(v, g, 0, 0); 
	else if (classNr==Code::DOUBLE_BOX)
		thing = new DoubleClassBox(v, g, 0, 0); 
	else if (classNr==Code::BOX)
		thing = new Box(v, g, 0, 0); 
	else if (classNr == Code::MINI_ELLIPSE) {
		MiniEllipse *ellipse = new MiniEllipse(v, g, 0, 0);
		// extra for older diagram versions.
		ellipse->SetFixedName(False); 
		thing = ellipse;
	}
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 

	// lines
	else if (classNr==Code::T1_LINE)
		thing = new C1Arrow(v, g, 0, 0, 0);
	else if (classNr==Code::T4_LINE || classNr==Code::C2R2_LINE)
		thing = new C2R2Line(v, g, 0, 0, 0);
	else if (classNr==Code::LINE)
		thing = new Line(v, g, 0, 0, 0);

	// (T1_)ARROW and DOUBLE_ARROW from old file formats.
	else if (classNr==Code::T1_ARROW)
		thing = new C1Arrow(v, g, 0, 0, 0);
	else if (classNr==Code::ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		line->SetFixedName(True);
		thing = line;
	}
	else if (classNr==Code::DOUBLE_ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetEnd1(LineEnd::FILLED_ARROW);
		line->SetEnd2(LineEnd::FILLED_ARROW);
		thing = line;
	}

	// nodes
	else if (classNr==Code::CLASS_NODE)
		thing = new ClassNode(cg);
	else if (classNr==Code::TAXONOMY_JUNCTION)
		thing = new TaxonomyJunction(cg);
	else if (classNr==Code::MODE_JUNCTION)
		thing = new ModeJunction(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);

	// edges
	else if (classNr==Code::BINARY_RELATIONSHIP)
		thing = new BinaryRelationship(cg, 0, 0);
	else if (classNr==Code::FUNCTION)
		thing = new Function(cg, 0, 0);
	else if (classNr==Code::COMPONENT_FUNCTION)
		thing = new ComponentFunction(cg, 0, 0);
	else if (classNr==Code::EMPTY_EDGE)
		thing = new EmptyEdge(cg, 0, 0);
	else if (classNr==Code::ISA_RELATIONSHIP)
		thing = new IsaRelationship(cg, 0, 0);
	else
		error("%s, line %d: impl error: wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
	return thing;
}
 
Node *CRDiagram::CreateNode(){
	Node *node = 0;
	CRGraph *g = (CRGraph *)GetGraph();
	if (GetNodeType()==Code::MODE_JUNCTION)
		node = new ModeJunction(g);
	else if (GetNodeType()==Code::TAXONOMY_JUNCTION)
		node = new TaxonomyJunction(g);
	else if (GetNodeType()==Code::CLASS_NODE)
		node = new ClassNode(g);
	else if (GetNodeType()==Code::COMMENT)
		node = new Comment(g);
	else
		error( "%s, line %d: impl error: unknown node type\n", 
			__FILE__, __LINE__);
	return node;
}

Edge *CRDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge *edge = 0;
	CRGraph *g = (CRGraph *)GetGraph();
	if (GetEdgeType() == Code::EMPTY_EDGE)
		edge = new EmptyEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::FUNCTION)
		edge = new Function(g, subj1, subj2);
	else if (GetEdgeType() == Code::BINARY_RELATIONSHIP)
		edge = new BinaryRelationship(g, subj1, subj2);
	else if (GetEdgeType() == Code::COMPONENT_FUNCTION)
		edge = new ComponentFunction(g, subj1, subj2);
	else if (GetEdgeType() == Code::ISA_RELATIONSHIP)
		edge = new IsaRelationship(g, subj1, subj2);
	else
		error( "%s, line %d: impl error: unknown edge type\n", 
			__FILE__, __LINE__);

	if (GetEdgeType() == Code::EMPTY_EDGE || 
		GetEdgeType() == Code::ISA_RELATIONSHIP) {
		if (!CheckIsaLoop(edge) || !CheckTaxonomyCombination(edge)) {
			delete edge;
			return 0;
		}
	}
	return edge;
}

NodeShape *CRDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::BOX)
		shape = new Box(v, g, x, y);
	else if (GetNodeShapeType() == Code::MINI_ELLIPSE) {
		shape = new MiniEllipse(v, g, x, y);
		shape->SetFixedName(False);
	}
	else if (GetNodeShapeType() == Code::DOUBLE_BOX)
		shape = new DoubleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TRIPLE_BOX)
		shape = new TripleClassBox(v, g, x, y);
	else
		error( "%s, line %d: impl error: "
			"node shape type doesn't exist\n", __FILE__, __LINE__);
	
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *CRDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	if (GetLineType()== Code::T1_LINE)
		line = new C1Arrow(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::C2R2_LINE)
		line = new C2R2Line(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error( "%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());
		if (GetEdgeType()==Code::EMPTY_EDGE ||
		    GetEdgeType()==Code::ISA_RELATIONSHIP)
			line->SetFixedName(True);
		if (GetLineEnd1()==LineEnd::FILLED_ARROW) {
			if (edge->GetClassType()==Code::FUNCTION) {
				string constr("1");
				((Function *)edge)->SetConstraint(&constr);
			}
		}
	}
	return line;
}

void CRDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::CLASS_NODE);
		SetNodeShapeType(Code::BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::CLASS_NODE);
		SetNodeShapeType(Code::DOUBLE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::CLASS_NODE);
		SetNodeShapeType(Code::TRIPLE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::TAXONOMY_JUNCTION);
		SetNodeShapeType(Code::MINI_ELLIPSE);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 5: SetNodeType(Code::MODE_JUNCTION);
		SetNodeShapeType(Code::MINI_ELLIPSE);
		SetNodeLineStyle(LineStyle::DASHED);
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

void CRDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::BINARY_RELATIONSHIP);
		SetLineType(Code::C2R2_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::FUNCTION);
		SetLineType(Code::T1_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 3: SetEdgeType(Code::COMPONENT_FUNCTION);
		SetLineType(Code::T1_LINE);
		SetEdgeLineStyle(LineStyle::DASHED);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 4: SetEdgeType(Code::ISA_RELATIONSHIP);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 5: SetEdgeType(Code::EMPTY_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 6: SetEdgeType(Code::FUNCTION);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::FILLED_ARROW);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool CRDiagram::SetText(TextShape *t, const string *s) {
	const string *d = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*d == "Attribute" && subj->GetClassType()==Code::CLASS_NODE)
		return SetAttribute((ClassNode *)subj, s, t->GetSequence());
	else if (*d == "Operation" && subj->GetClassType()==Code::CLASS_NODE)
		return SetOperation((ClassNode *)subj, s, t->GetSequence());
	else
		return ERDiagram::SetText(t, s);
}

void CRDiagram::MakeErrorMessage(ClassNode *cl, 
		ClassNode::TextErrType result, 
		const string *s, string *txt) {
	*txt = "class '" + *cl->GetName() + "' ";
	if (result == ClassNode::ATTRIBUTE_EXISTS)
		*txt += "already has an attribute '" + *s + "'"; 
	else if (result == ClassNode::OPERATION_EXISTS)
		*txt += "already has an operation '" + *s + "'"; 
	else if (result == ClassNode::FUNCTION_EXISTS)
		*txt += "already has a function '" + *s + "'"; 
	else if (result == ClassNode::COMPONENT_EXISTS)
		*txt += "already has a component function '" + *s + "'"; 
	else if (result == ClassNode::RELATION_EXISTS)
		*txt += "is already engaged in binary relationship '" + *s + "'"; 
	else if (result == ClassNode::IMPOSSIBLE_ATTRIBUTE)
		*txt = "'" + *s + "' wrong syntax\nfor an attribute declaration";
	else if (result == ClassNode::IMPOSSIBLE_OPERATION)
		*txt = "'" + *s + "' wrong syntax\nfor an operation declaration";
}

bool CRDiagram::SetAttribute(ClassNode *cl, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(cl, &shapes);
	unsigned m = nr;
	// split string in different strings (separated by newline).
	// each string becomes a new attribute.
	string ss(*s);
	char *str = (char *)ss.getstr();
	char *x = strtok(str, "\r");
	char empty[2] = "";
	if (x == 0)
		x = empty;
	while (x != 0) {
		string *ns = new string(x);
		bool update = True;
		ClassNode::TextErrType result;
		if (m == nr)
			result = cl->SetAttribute(ns, m, True);
		else { // m != r
			result = cl->SetAttribute(ns, m, False);
			update = False;
		}
		string txt;
		MakeErrorMessage(cl, result, ns, &txt);
		if (result != ClassNode::MEMBER_OK) {
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			// delete the newly created attributes.
			*ns = "";
			for (shapes.first(); !shapes.done(); shapes.next()) {
				if (shapes.cur()->GetClassType() != Code::BOX) {
					DoubleBox *db = 
						(DoubleBox *)(shapes.cur());
					if (db->NrLabels()-1 == m)
						db->UpdateLabel(ns, m, update);
				}
			}
			delete ns;
			return False;
		}
		// update the double box shapes.
		for (shapes.first(); !shapes.done(); shapes.next()) {
			if (shapes.cur()->GetClassType() != Code::BOX)
				((DoubleBox *)shapes.cur())->
					UpdateLabel(ns, m, update);
		}
		if (!shapes.first()) {
			error( "%s, line %d: impl error: "
				"shape does not exist!\n", __FILE__, __LINE__);
			return False;
		}
		m++;
		x = strtok(0, "\r");
		delete ns;
	}
	return True;
}

bool CRDiagram::SetOperation(ClassNode *cl, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(cl, &shapes);
	string ss(*s);
	char *str = (char *)ss.getstr();
	unsigned m = nr;
	char empty[2] = "";
	char *x = strtok(str, "\r");
	if (x == 0)
		x = empty;
	while (x != 0) {
		string *ns = new string(x);
		bool update = True;
		ClassNode::TextErrType result;
		if (m == nr) {
			result = cl->SetOperation(ns, m, True);
		}
		else { // m != r
			result = cl->SetOperation(ns, m, False);
			update = False;
		}
		string txt;
		MakeErrorMessage(cl, result, ns, &txt);
		if (result != ClassNode::MEMBER_OK) {
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			// delete the newly created operations.
			*ns = "";
			for (shapes.first(); !shapes.done(); shapes.next()) {
				if (shapes.cur()->GetClassType() == 
						Code::TRIPLE_BOX) {
					TripleBox *tb = 
						(TripleBox *)(shapes.cur());
					if (tb->NrLabels2()-1 == m)
						tb->UpdateLabel2(ns, m, update);
				}
			}
			delete ns;
			return False;
		}
		// update the triple box shapes.
		for (shapes.first(); !shapes.done(); shapes.next()) {
			if (shapes.cur()->GetClassType() == Code::TRIPLE_BOX) 
				((TripleBox *)shapes.cur())->
					UpdateLabel2(ns, m, update);
		} 
		if (!shapes.first()) {
			error( "%s, line %d: impl error: "
				"shape does not exist!\n", __FILE__, __LINE__);
			return False;
		}
		m++;
		x = strtok(0, "\r");
		delete ns;
	}
	return True;
}

void CRDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	// Check that binary relationships are named.
	total += crChecks->CheckNamelessBinaryRelationships(chkbuf);
	if (total == 0)
		total += crChecks->CheckDoubleNamelessEdges(
			Code::BINARY_RELATIONSHIP, Code::CLASS_NODE, 
			Code::CLASS_NODE, chkbuf);
	// Check that classes are named.
	total += crChecks->CheckNamelessNodes(Code::CLASS_NODE, chkbuf);
	// double nodes can occur after cut-copy-paste
	total += crChecks->CheckDoubleNodes(Code::CLASS_NODE, chkbuf);
	// Check that functions and component functions are identifiable.
	total += crChecks->CheckDoubleNamelessFunctions(
		Code::CLASS_NODE, Code::CLASS_NODE, chkbuf);
	// Check that tax. and mode junctions are connected correctly.
	total += crChecks->CheckJunctionCoherence(
		Code::TAXONOMY_JUNCTION, Code::ISA_RELATIONSHIP, 
		Code::EMPTY_EDGE, 2, chkbuf);
	total += crChecks->CheckJunctionCoherence(
		Code::MODE_JUNCTION, Code::ISA_RELATIONSHIP, 
		Code::EMPTY_EDGE, 2, chkbuf);
	// Check that classes have not 1 comp. function.
	total += crChecks->CheckCountEdgesFrom(
		Code::CLASS_NODE, Code::COMPONENT_FUNCTION, 2, INT_MAX, 
		True, False, chkbuf);
	// Check that rel. classes are not spec. of classes.
	total += crChecks->CheckRelationshipIsaClassNode(chkbuf);
	ReportCheck(total, &chkbuf);
}

bool CRDiagram::CheckTaxonomyCombination(Edge *edge) {
	// checks if adding the edge does not make a static partition 
	// (with tax.junction) part of a dynamic partition (with modejunction).
	int eType = edge->GetClassType();
	Subject *n1 = edge->GetSubject1();
	Subject *n2 = edge->GetSubject2();
	int n1Type = n1->GetClassType();
	int n2Type = n2->GetClassType();
	bool correct = True;
	if (eType == Code::EMPTY_EDGE) {
		Subject *nX = 0;
		if (n1Type == Code::CLASS_NODE && 
		    n2Type == Code::MODE_JUNCTION)
			nX = n1;
		else if (n1Type == Code::MODE_JUNCTION && 
			 n2Type == Code::CLASS_NODE) 
			nX = n2;
		if (nX) {
			List<Subject *> edges;
			GetGraph()->GetEdges(&edges, Code::ISA_RELATIONSHIP);
			for (edges.first(); !edges.done(); edges.next()) {
				Edge *e = (Edge *)edges.cur();
				if (nX == e->GetSubject2()) {
					int t=e->GetSubject1()->GetClassType();
					if (t == Code::CLASS_NODE || 
						t == Code::TAXONOMY_JUNCTION)
						correct = False;
				}
			}
		}
	}
	else if (eType == Code::ISA_RELATIONSHIP) {
		if (n1Type == Code::CLASS_NODE || 
		    n1Type == Code::TAXONOMY_JUNCTION) {
			List<Subject *> edges;
			GetGraph()->GetEdges(&edges, Code::EMPTY_EDGE);
			for (edges.first(); !edges.done(); edges.next()) {
				Edge *e = (Edge *)edges.cur();
				if (n2==e->GetSubject1()) {
					if (e->GetSubject2()->GetClassType() == 
					    Code::MODE_JUNCTION)
						correct = False;
				}
				else if (n2==e->GetSubject2()) {
					if (e->GetSubject1()->GetClassType() == 
					    Code::MODE_JUNCTION)
						correct = False;
				}
			} 
		}
	}
	if (!correct) {
		string txt = "Dynamic specialization (with ModeJunction) cannot "
			 "be specialized\n into a static specialization "
			 "(with TaxonomyJunction)";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
	}
	return correct;
}
