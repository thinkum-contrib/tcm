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
#include "ergraph.h"
#include "erviewer.h"
#include "erview.h"
#include "erwindow.h"
#include "erchecks.h"
#include "c2r2line.h"
#include "c1arrow.h"
#include "textbox.h"
#include "miniellipse.h"
#include "box.h"
#include "diamond.h"
#include "comment.h"
#include "entitytype.h"
#include "relationshipnode.h"
#include "valuetype.h"
#include "taxonomyjunction.h"
#include "emptyedge.h"
#include "function.h"
#include "binaryrelationship.h"
#include "isarelationship.h"
#include "messagedialog.h"
#include "replacedialog.h"
#include "erdiagram.h"
#include "menu.h"

class Edge;
class C1Edge;
 
ERDiagram::ERDiagram(Config *c, ERWindow *d, ERViewer *v, ERGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	GetReplaceDialog()->ManageNameOnlyToggle(True);
	GetFindDialog()->ManageNameOnlyToggle(True);
	erChecks = new ERChecks(this, g);
}

ERDiagram::~ERDiagram() {
	delete erChecks;
}

Thing *ERDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	ERGraph *eg = (ERGraph *)GetGraph();
	Thing *thing = 0;
	// view
	if (classNr == Code::VIEW)
		thing = new ERView((ERViewer *)GetDiagramViewer());
	// node shapes
	else if (classNr == Code::BOX)
		thing = new Box(v, g, 0, 0); 
	else if (classNr == Code::ELLIPSE)
		thing = new Ellipse(v, g, 0, 0); 
	else if (classNr == Code::MINI_ELLIPSE) { 
		MiniEllipse *ellipse = new MiniEllipse(v, g, 0, 0);
		// extra for older diagram versions.
		ellipse->SetFixedName(False); 
		thing = ellipse;
	}
	else if (classNr == Code::DIAMOND)
		thing = new Diamond(v, g, 0, 0); 
	else if (classNr == Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	// lines
	else if (classNr == Code::T1_LINE)
		thing = new C1Arrow(v, g, 0, 0, 0);
	else if (classNr == Code::T4_LINE || classNr == Code::C2R2_LINE)
		thing = new C2R2Line(v, g, 0, 0, 0);
	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);

	// old line types
	else if (classNr == Code::T1_ARROW)
		thing = new C1Arrow(v, g, 0, 0, 0);
	else if (classNr == Code::ARROW) {
		Line *line = new Line(v, g, 0, 0, 0);
		line->SetFixedName(True);
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
	else if (classNr == Code::ENTITY_TYPE)
		thing = new EntityType(eg);
	else if (classNr == Code::VALUE_TYPE)
		thing = new ValueType(eg);
	else if (classNr == Code::TAXONOMY_JUNCTION)
		thing = new TaxonomyJunction(eg);
	else if (classNr == Code::RELATIONSHIP_NODE)
		thing = new RelationshipNode(eg);
	else if (classNr == Code::COMMENT)
		thing = new Comment(eg);
	// edges
	else if (classNr == Code::BINARY_RELATIONSHIP)
		thing = new BinaryRelationship(eg, 0, 0);
	else if (classNr == Code::FUNCTION)
		thing = new Function(eg, 0, 0);
	else if (classNr == Code::EMPTY_EDGE)
		thing = new EmptyEdge(eg, 0, 0);
	else if (classNr == Code::ISA_RELATIONSHIP)
		thing = new IsaRelationship(eg, 0, 0);
	else
		error("%s, line %d: impl error: "
			"wrong class number %d\n", __FILE__, __LINE__, classNr);
	return thing;
}

Node *ERDiagram::CreateNode(){
	Node *node;
	ERGraph *eg = (ERGraph *)GetGraph();
	if (GetNodeType() == Code::TAXONOMY_JUNCTION)
		node = new TaxonomyJunction(eg);
	else if (GetNodeType() == Code::VALUE_TYPE)
		node = new ValueType(eg);
	else if (GetNodeType() == Code::ENTITY_TYPE)
		node = new EntityType(eg);
	else if (GetNodeType() == Code::RELATIONSHIP_NODE)
		node = new RelationshipNode(eg);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(eg);
	else {
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
		node = 0;
	}
	return node;
}

bool ERDiagram::CheckEdgeConstraints(Subject *subj1, Subject *subj2) {
	// Check possible connections (subj-subj-edge matrix).
	if (!CheckConnection(subj1, subj2))
		return False;
	int subj1Type = subj1->GetClassType();
	int subj2Type = subj2->GetClassType();
	bool isError = False;
	// Check for double is_a from tax.junction (or modejunction).
	// Draw a picture for seeing these different cases.
	if (GetEdgeType()==Code::ISA_RELATIONSHIP &&
		(subj1Type==Code::TAXONOMY_JUNCTION || 
			subj1Type==Code::MODE_JUNCTION) &&
			((ERGraph *)GetGraph())->IsaLeaves(subj1)) {
		isError = True;
	}
	// Check for double is_a between same ent.types (or object classes).
	else if (GetEdgeType()==Code::ISA_RELATIONSHIP &&
		(subj1Type==Code::ENTITY_TYPE||subj1Type==Code::CLASS_NODE) &&
		(subj2Type==Code::ENTITY_TYPE||subj2Type==Code::CLASS_NODE) &&
		GetGraph()->IsConnected(subj1, subj2, Code::ISA_RELATIONSHIP)) {
		isError = True;
	}
	// Check for double empty_edge from ent. type (or object class) to a
	// taxonomyjunction (or modejunction).
	else if ((GetEdgeType()==Code::EMPTY_EDGE &&
		(subj1Type==Code::ENTITY_TYPE ||
		 subj1Type==Code::CLASS_NODE) &&
		(subj2Type==Code::TAXONOMY_JUNCTION ||
		 subj2Type==Code::MODE_JUNCTION) &&
		 GetGraph()->IsConnected(subj1, subj2)) ||
	   (GetEdgeType()==Code::EMPTY_EDGE &&
		(subj2Type==Code::ENTITY_TYPE ||
		 subj2Type==Code::CLASS_NODE) &&
		(subj1Type==Code::TAXONOMY_JUNCTION||
		 subj1Type==Code::MODE_JUNCTION) &&
		 GetGraph()->IsConnected(subj2, subj1))) {
		isError = True;
	}
	if (isError) {
		string txt = "Cannot add another ";
		txt += Code::GetName(GetEdgeType());
		txt += " here";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	return True;
}

bool ERDiagram::CheckIsaLoop(Edge *edge) {
	if (GetEdgeType() == Code::EMPTY_EDGE || 
	    GetEdgeType() == Code::ISA_RELATIONSHIP) {
		GetGraph()->AddEdge(edge);
		Subject *n1 = edge->GetSubject1();
		if (((ERGraph *)GetGraph())->IsaPathExists(n1, n1)) {
			string txt = "'is_a loops' are not allowed";
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			GetGraph()->RemoveEdge(edge);
			return False;
		}
		GetGraph()->RemoveEdge(edge);
	}
	return True;
}

Edge *ERDiagram::CreateEdge(Subject *n1, Subject *n2){
	if (!CheckEdgeConstraints(n1, n2))
		return 0; 
	Edge *edge = 0;
	ERGraph *eg = (ERGraph *)GetGraph();
	if (GetEdgeType() == Code::EMPTY_EDGE)
		edge = new EmptyEdge(eg, n1, n2);
	else if (GetEdgeType() == Code::FUNCTION)
		edge = new Function(eg, n1, n2);
	else if (GetEdgeType() == Code::BINARY_RELATIONSHIP)
		edge = new BinaryRelationship(eg, n1, n2);
	else if (GetEdgeType() == Code::ISA_RELATIONSHIP)
		edge = new IsaRelationship(eg, n1, n2);
	else
		error("%s, line %d: impl error: "
			"unknown edge type\n", __FILE__, __LINE__);

	if (!CheckIsaLoop(edge)) {
		delete edge;
		return 0;
	}
	return edge;
}
 
NodeShape *ERDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::BOX)
		shape = new Box(v, g, x, y);
	else if (GetNodeShapeType() == Code::ELLIPSE)
		shape = new Ellipse(v, g, x, y);
	else if (GetNodeShapeType() == Code::MINI_ELLIPSE) {
		shape = new MiniEllipse(v, g, x, y);
		shape->SetFixedName(False); // tax.junct. is editable
	}
	else if (GetNodeShapeType() == Code::DIAMOND)
		shape = new Diamond(v, g, x, y);
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

Line *ERDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	if (GetLineType() == Code::T1_LINE)
		line = new C1Arrow(v, g, from, to, l, IsCurve());
	else if (GetLineType() == Code::C2R2_LINE)
		line = new C2R2Line(v, g, from, to, l, IsCurve());
	else if (GetLineType() == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error("%s, line %d: impl error: "
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

void ERDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::ENTITY_TYPE);
		SetNodeShapeType(Code::BOX);
		break;
	case 2: SetNodeType(Code::VALUE_TYPE);
		SetNodeShapeType(Code::ELLIPSE);
		break;
	case 3: SetNodeType(Code::TAXONOMY_JUNCTION);
		SetNodeShapeType(Code::MINI_ELLIPSE);
		break;
	case 4: SetNodeType(Code::RELATIONSHIP_NODE);
		SetNodeShapeType(Code::DIAMOND);
		break;
	case 5: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void ERDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::BINARY_RELATIONSHIP);
		SetLineType(Code::C2R2_LINE);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::FUNCTION);
		SetLineType(Code::T1_LINE);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 3: SetEdgeType(Code::ISA_RELATIONSHIP);
		SetLineType(Code::LINE);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 4: SetEdgeType(Code::EMPTY_EDGE);
		SetLineType(Code::LINE);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 5: SetEdgeType(Code::FUNCTION);
		SetLineType(Code::LINE);
		SetLineEnd1(LineEnd::FILLED_ARROW);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool ERDiagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Cardinality Constraint")
		return SetConstraint(subj, s, t->GetSequence());
	else if (*description == "Role Name")
		return SetRoleName(subj, s, t->GetSequence()%2);
	else
		return Diagram::SetText(t, s);
}

bool ERDiagram::SetConstraint(Subject *subject, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	bool wrong_syntax = False;
	Edge *e = (Edge *)subject;
	int eType = e->GetClassType();
	if (eType == Code::FUNCTION || eType == Code::COMPONENT_FUNCTION) {
		Function *edge = (Function *)subject;
		if (!edge->SetConstraint(s))
			wrong_syntax = True;
	}
	else if (eType == Code::SSD_PARTICIPANT_LINK_EDGE) {
		wrong_syntax = !((C1Edge *)subject)->SetConstraint(s);
	}
	else if (eType == Code::BINARY_RELATIONSHIP ||
		 eType == Code::SSD_BINARY_ASSOCIATION_EDGE ||
		 eType == Code::UCD_BINARY_ASSOCIATION_EDGE ||
		 eType == Code::SSD_AGGREGATION_EDGE ||
		 eType == Code::SSD_COMPOSITION_EDGE ||
		 eType == Code::CBD_CLASS_LINK_EDGE ||
		 eType == Code::CBD_OBJECT_LINK_EDGE) {
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
				((T1Line *)shapes.cur())->UpdateTextShape1(s);
			else
				((C2R2Line *)shapes.cur())->UpdateTextShape2(s);
		}
		while (shapes.next());
	}
	else 
		return False;
	return True;
}

bool ERDiagram::SetRoleName(Subject *subject, const string *s, unsigned nr) {
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

void ERDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += erChecks->CheckNamelessBinaryRelationships(chkbuf);
	if (total == 0)
		total += erChecks->CheckDoubleNamelessEdges(
			Code::BINARY_RELATIONSHIP, Code::ENTITY_TYPE, 
			Code::ENTITY_TYPE, chkbuf);
	// all nodes have a name.
	total += erChecks->CheckNamelessNodes(Code::ENTITY_TYPE, chkbuf);
	total += erChecks->CheckNamelessNodes(Code::VALUE_TYPE, chkbuf);
	total += erChecks->CheckNamelessNodes(Code::RELATIONSHIP_NODE, chkbuf);
	// all functions and relationships are identifiable.
	total += erChecks->CheckNamelessEdges(
		Code::FUNCTION, Code::ENTITY_TYPE, Code::VALUE_TYPE, chkbuf);
	total += erChecks->CheckNamelessEdges(
		Code::FUNCTION, Code::RELATIONSHIP_NODE, Code::VALUE_TYPE, chkbuf);
	total += erChecks->CheckDoubleNamelessEdges(
		Code::FUNCTION, Code::RELATIONSHIP_NODE, Code::ENTITY_TYPE, chkbuf);
	total += erChecks->CheckDoubleNamelessEdges(
		Code::FUNCTION, Code::ENTITY_TYPE, Code::ENTITY_TYPE, chkbuf);
	// double nodes can still occur after cut-copy-paste
	total += erChecks->CheckDoubleNodes(Code::ENTITY_TYPE, chkbuf);
	total += erChecks->CheckConnected(Code::VALUE_TYPE, False, chkbuf);
	total += erChecks->CheckJunctionCoherence(
		Code::TAXONOMY_JUNCTION, Code::ISA_RELATIONSHIP, 
		Code::EMPTY_EDGE, 2, chkbuf);
	total += erChecks->CheckRelationshipCoherence(chkbuf);
	total += erChecks->CheckDoubleRelationships(chkbuf);
	ReportCheck(total, &chkbuf);
}
