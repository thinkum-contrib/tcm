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
#include "ssdgraph.h"
#include "esdwindow.h"
#include "ssdviewer.h"
#include "ssdchecks.h"
#include "messagedialog.h"
#include "ssdtripleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdsingleclassbox.h"
#include "ssdsingleobjectbox.h"
#include "ssddoubleobjectbox.h"
#include "c2r2line.h"
#include "ssdr2line.h"
#include "ssdrcline.h"
#include "ssdbinaryassociationedge.h"
#include "ssdobjectlinkedge.h"
#include "ssdparticipantlinkedge.h"
#include "ssdgeneralizationedge.h"
#include "ssdassociationlinkedge.h"
#include "commentlink.h"
#include "ssdclassnode.h"
#include "ssdobjectnode.h"
#include "ssdgeneralizationnode.h"
#include "ssdaggregationnode.h"
#include "ssdassociationnode.h"
#include "ssdaggregationedge.h"
#include "ssdcompositionedge.h"
#include "diamond.h"
#include "emptyedge.h"
#include "blackdot.h"
#include "textbox.h"
#include "comment.h"
#include "notebox.h"
#include "hexagon.h"
#include "note.h"
#include "miniellipse.h"
#include "esddiagram.h"
#include <stdio.h>
#include <limits.h>

const int ESDDiagram::MINI_ELLIPSE_WIDTH = 8;
const int ESDDiagram::MINI_ELLIPSE_HEIGHT = 8;
 
ESDDiagram::ESDDiagram(Config *c, ESDWindow *d, SSDViewer *v, SSDGraph *g): 
	   ERDiagram(c, d, v, g) {
	UpdateNodeType(1);
        UpdateEdgeType(1);
	ssdChecks = new SSDChecks(this, g);
}

ESDDiagram::~ESDDiagram() {
	delete ssdChecks;
}

Thing *ESDDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	SSDGraph *cg = (SSDGraph *)GetGraph();
	Thing *thing = 0;
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());

	// node shapes (the simple triplebox, doublebox and box are used
	// in older file formats.
	else if (classNr==Code::SSD_TRIPLE_CLASS_BOX||classNr==Code::TRIPLE_BOX)
		thing = new SSDTripleClassBox(v, g, 0, 0); 
	else if (classNr==Code::SSD_DOUBLE_CLASS_BOX||classNr==Code::DOUBLE_BOX)
		thing = new SSDDoubleClassBox(v, g, 0, 0); 
	else if (classNr==Code::SSD_SINGLE_CLASS_BOX||classNr==Code::BOX)
		thing = new SSDSingleClassBox(v, g, 0, 0); 
	else if (classNr==Code::SSD_DOUBLE_OBJECT_BOX)
		thing = new SSDDoubleObjectBox(v, g, 0, 0); 
	else if (classNr==Code::SSD_SINGLE_OBJECT_BOX)
		thing = new SSDSingleObjectBox(v, g, 0, 0); 
	else if (classNr == Code::MINI_ELLIPSE) {
                MiniEllipse *el = new MiniEllipse(v, g, 0, 0);
                el->SetResizable(True);
                thing = el;
        }
	else if (classNr == Code::BLACK_DOT)
		thing = new BlackDot(v, g, 0, 0);
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	else if (classNr==Code::NOTE_BOX)
		thing = new NoteBox(v, g, 0, 0); 
	else if (classNr==Code::DIAMOND)
		thing = new Diamond(v, g, 0, 0); 

	// lines
	else if (classNr==Code::T4_LINE || classNr==Code::C2R2_LINE)
		thing = new C2R2Line(v, g, 0, 0, 0);
	else if (classNr==Code::LINE)
		thing = new Line(v, g, 0, 0, 0);
	else if (classNr==Code::SSD_RCLINE)
		thing = new SSDRCLine(v, g, 0, 0, 0);
	else if (classNr==Code::SSD_R2LINE || classNr==Code::T2_LINE)
		thing = new SSDR2Line(v, g, 0, 0, 0);

	// nodes
	else if (classNr==Code::CLASS_NODE || classNr==Code::SSD_CLASS_NODE)
		thing = new SSDClassNode(cg);
	else if (classNr==Code::SSD_OBJECT_NODE)
		thing = new SSDObjectNode(cg);
	else if (classNr==Code::TAXONOMY_JUNCTION || classNr==Code::SSD_GENERALIZATION_NODE)
		thing = new SSDGeneralizationNode(cg);
	else if (classNr==Code::SSD_AGGREGATION_NODE)
		thing = new SSDAggregationNode(cg);
	else if (classNr == Code::RELATIONSHIP_NODE || classNr==Code::SSD_ASSOCIATION_NODE)
		thing = new SSDAssociationNode(cg);
	else if (classNr==Code::NOTE)
		thing = new Note(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);

	// edges
	else if (classNr==Code::BINARY_RELATIONSHIP || classNr==Code::SSD_BINARY_ASSOCIATION_EDGE)
		thing = new SSDBinaryAssociationEdge(cg, 0, 0);
	else if (classNr==Code::SSD_ASSOCIATION_LINK_EDGE)
		thing = new SSDAssociationLinkEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);
	else if (classNr==Code::ISA_RELATIONSHIP || classNr==Code::SSD_GENERALIZATION_EDGE)
		thing = new SSDGeneralizationEdge(cg, 0, 0);
	else if (classNr==Code::SSD_OBJECT_LINK_EDGE)
		thing = new SSDObjectLinkEdge(cg, 0, 0);
	else if (classNr==Code::SSD_PARTICIPANT_LINK_EDGE)
		thing = new SSDParticipantLinkEdge(cg, 0, 0);
	else if (classNr==Code::EMPTY_EDGE)	//Compatibility
		thing = new EmptyEdge(cg, 0, 0);
	else if (classNr==Code::SSD_AGGREGATION_EDGE)
		thing = new SSDAggregationEdge(cg, 0, 0);
	else if (classNr==Code::SSD_COMPOSITION_EDGE)
		thing = new SSDCompositionEdge(cg, 0, 0);

	else
		error("%s, line %d: impl error: wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
	return thing;
}
 
Node *ESDDiagram::CreateNode(){
	Node *node = 0;
	SSDGraph *g = (SSDGraph *)GetGraph();

	if (GetNodeType()==Code::NOTE)
		node = new Note(g);
	else if (GetNodeType()==Code::SSD_GENERALIZATION_NODE)
		node = new SSDGeneralizationNode(g);
	else if (GetNodeType()==Code::SSD_CLASS_NODE)
		node = new SSDClassNode(g);
	else if (GetNodeType()==Code::SSD_ASSOCIATION_NODE)
		node = new SSDAssociationNode(g);
	else if (GetNodeType()==Code::COMMENT)
		node = new Comment(g);
	else
		error( "%s, line %d: impl error: unknown node type\n", 
			__FILE__, __LINE__);
	return node;
}

Edge *ESDDiagram::CreateEdge(Subject *subj1, Subject* subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge* edge = 0;
	SSDGraph *g = (SSDGraph *)GetGraph();
	if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, subj1, subj2);
	else if (GetEdgeType() == Code::SSD_ASSOCIATION_LINK_EDGE)
		edge = new SSDAssociationLinkEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::SSD_BINARY_ASSOCIATION_EDGE)
		edge = new SSDBinaryAssociationEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::SSD_GENERALIZATION_EDGE)
		edge = new SSDGeneralizationEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::SSD_PARTICIPANT_LINK_EDGE)
		edge = new SSDParticipantLinkEdge(g, subj1, subj2);
	else
		error( "%s, line %d: impl error: unknown edge type\n", 
			__FILE__, __LINE__);

	if (GetEdgeType() == Code::SSD_GENERALIZATION_EDGE) {
		if (!CheckIsaLoop(edge)) {
			delete edge;
			return 0;
		}
	}
	return edge;
}

NodeShape *ESDDiagram::CreateNodeShape(Node* node, int x, int y) {
	NodeShape* shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	if (GetNodeShapeType() == Code::SSD_SINGLE_CLASS_BOX)
		shape = new SSDSingleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::SSD_DOUBLE_CLASS_BOX)
		shape = new SSDDoubleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::MINI_ELLIPSE) {
                shape = new MiniEllipse(v, g, x, y);
                shape->SetResizable(True);
        }
	else if (GetNodeShapeType() == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::DIAMOND)
		shape = new Diamond(v, g, x, y);
	else
		error( "%s, line %d: impl error: "
			"node shape type doesn't exist\n", __FILE__, __LINE__);
	
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
		if (GetNodeShapeType() == Code::MINI_ELLIPSE)
			shape->SetFixedName(False);
	}
	return shape;
}

Line *ESDDiagram::CreateLine(Edge* edge, GShape *from, GShape *to, List<Point*> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line* line = 0;
	if (GetLineType()== Code::C2R2_LINE)
		line = new C2R2Line(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::SSD_R2LINE)
		line = new SSDR2Line(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::SSD_RCLINE)
		line = new SSDRCLine(v, g, from, to, l, IsCurve());
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

		if (GetEdgeType()==Code::SSD_GENERALIZATION_EDGE) {
			if (to->GetClassType()==Code::MINI_ELLIPSE)
				line->SetEnd2(LineEnd::EMPTY);
		}

		if (GetEdgeType()==Code::COMMENT_LINK ||
		    GetEdgeType()==Code::SSD_PARTICIPANT_LINK_EDGE)
                        line->SetFixedName(True);
	}
	return line;
}

void ESDDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::SSD_CLASS_NODE);
		SetNodeShapeType(Code::SSD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::SSD_CLASS_NODE);
		SetNodeShapeType(Code::SSD_DOUBLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::SSD_ASSOCIATION_NODE);
		SetNodeShapeType(Code::DIAMOND);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 5: SetNodeType(Code::SSD_GENERALIZATION_NODE);
		SetNodeShapeType(Code::MINI_ELLIPSE);
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

void ESDDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::SSD_BINARY_ASSOCIATION_EDGE);
		SetLineType(Code::C2R2_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::SSD_PARTICIPANT_LINK_EDGE);
		SetLineType(Code::SSD_RCLINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 3: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 4: SetEdgeType(Code::SSD_ASSOCIATION_LINK_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::DASHED);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 5: SetEdgeType(Code::SSD_GENERALIZATION_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::WHITE_TRIANGLE);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool ESDDiagram::SetText(TextShape *t, const string *s) {
	const string *d = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*d == "Attribute" && subj->GetClassType()==Code::SSD_CLASS_NODE)
		return SetAttribute((StringListNode*)subj, s, t->GetSequence());
	else if (*d == "Role Name" && subj->GetClassType()==Code::SSD_PARTICIPANT_LINK_EDGE)
		return SetRoleName(subj, s, t->GetSequence());
	else
		return ERDiagram::SetText(t, s);
}

bool ESDDiagram::SetRoleName(Subject *subject, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	bool succes = True;
	if (subject->GetClassType() == Code::SSD_PARTICIPANT_LINK_EDGE) {
		succes = ((SSDParticipantLinkEdge *)subject)->SetRoleName(s);
	}

	if (!succes) {
		string txt = "'" + *s + "' is not a possible role name";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	if (check(shapes.first())) {
		do {
			Shape *shape = shapes.cur();
			if (shape->GetClassType()==Code::SSD_R2LINE) {
				if (nr == 1)
					((SSDR2Line *)shape)->UpdateTextShape1(s);
				else 
					((SSDR2Line *)shape)->UpdateTextShape2(s);
			}
			else if (shape->GetClassType()==Code::SSD_RCLINE)
				((SSDRCLine *)shape)->UpdateTextShape2(s);
		} while (shapes.next());
	}
	else 
		return False;
	return True;
}

void ESDDiagram::MakeErrorMessage(StringListNode *,
                StringListNode::StringErrorType result, const string *s, string *txt) {
        if (result == StringListNode::STRING_SYNTAX_ERROR)
                *txt += "syntax error: '" + *s + "'";
        else if (result == StringListNode::STRING_ALREADY_EXISTS)
                *txt += "'" + *s + "' already exists";
}

bool ESDDiagram::SetAttribute(StringListNode *node, const string *s, unsigned nr) {
	List <GShape *> shapes;
	GetDiagramViewer()->GetShapes(node, &shapes);
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
		StringListNode::StringErrorType result;
		if (m == nr)
			result = node->SetString(ns, m, True);
		else { // m != r
			result = node->SetString(ns, m, False);
			update = False;
		}
		string txt;
		MakeErrorMessage(node, result, ns, &txt);
		if (result != StringListNode::STRING_OK) {
			ShowDialog(MessageDialog::ERROR, "Error", &txt);
			// delete the newly created attributes.
			*ns = "";
			for (shapes.first(); !shapes.done(); shapes.next()) {
				int type = shapes.cur()->GetClassType();
				if (type != Code::BOX && 
				    type != Code::SSD_SINGLE_CLASS_BOX) {
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
			int type = shapes.cur()->GetClassType();
			if (type != Code::BOX && 
			    type != Code::SSD_SINGLE_CLASS_BOX)
				((DoubleBox *)shapes.cur())->UpdateLabel(ns, m, update);
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


void ESDDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	total += ssdChecks->CheckDoubleNamelessEdges(
			Code::SSD_BINARY_ASSOCIATION_EDGE, Code::SSD_CLASS_NODE, 
			Code::SSD_CLASS_NODE, chkbuf);
	// Check that object classes are named.
	total += ssdChecks->CheckNamelessNodes(Code::SSD_CLASS_NODE, chkbuf);
	total += ssdChecks->CheckNamelessNodes(Code::SSD_ASSOCIATION_NODE, chkbuf);
	// double nodes can occur after cut-copy-paste
	total += ssdChecks->CheckDoubleNodes(Code::SSD_CLASS_NODE, chkbuf);
	ReportCheck(total, &chkbuf);
}
