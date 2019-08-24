////////////////////////////////////////////////////////////////////////////////
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "cpddependencyedge.h"
#include "cpdrealizationedge.h"
#include "cpdcomponentnode.h"
#include "cpdinterfacenode.h"
#include "dpdresourcenode.h"
#include "dpdcommunicationedge.h"
#include "note.h"
#include "notebox.h"
#include "solidhorizontalbar.h"
#include "buildingblock.h"
#include "cube.h"
#include "miniellipse.h"
#include "line.h"
#include "commentlink.h"
#include "textbox.h"
#include "comment.h"
#include "cpdiagram.h"
#include "cpgraph.h"
#include "cpviewer.h"
#include "cpwindow.h"

const int CPDiagram::DOT_WIDTH = 8;
 
CPDiagram::CPDiagram(Config *c, CPWindow *d, CPViewer *v, CPGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
}

Thing *CPDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	CPGraph *cg = (CPGraph *)GetGraph();
	Thing *thing = 0;

	// node shapes
	if (classNr == Code::BUILDING_BLOCK)
		thing = new BuildingBlock(v, g, 0, 0); 
	else if (classNr == Code::MINI_ELLIPSE) {
		MiniEllipse *el = new MiniEllipse(v, g, 0, 0);  
		el->SetFixedName(False);
		el->SetNamePosition(MiniEllipse::RIGHT);
		thing = el;
	}
	else if (classNr == Code::CUBE)
                thing = new Cube(v, g, 0, 0);
	else if (classNr == Code::NOTE_BOX)
                thing = new NoteBox(v, g, 0, 0);
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 

	else if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer()); 

	// lines
	else if (classNr == Code::LINE)
		thing = new Line(v, g, 0, 0, 0);

	// nodes
	else if (classNr == Code::GENERIC_NODE || classNr == Code::CPD_COMPONENT_NODE)
		thing = new CPDComponentNode(cg);
	else if (classNr==Code::CPD_INTERFACE_NODE)
		thing = new CPDInterfaceNode(cg);
	else if (classNr==Code::DPD_RESOURCE_NODE)
		thing = new DPDResourceNode(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);
	else if (classNr==Code::NOTE)
		thing = new Note(cg);

	// edges
	else if (classNr == Code::GENERIC_EDGE || classNr == Code::CPD_DEPENDENCY_EDGE)
		thing = new CPDDependencyEdge(cg, 0, 0);
	else if (classNr==Code::CPD_REALIZATION_EDGE)
		thing = new CPDRealizationEdge(cg, 0, 0);
	else if (classNr==Code::DPD_COMMUNICATION_EDGE)
		thing = new DPDCommunicationEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);
	else {
		error("%s, line %d: impl error: " "wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
		return 0;
	}
	if (thing != 0 && HasIndexShape(thing->GetClassType()))
		((NodeShape *)thing)->SetFixedIndexLabel(False);

	return thing;
}

Node *CPDiagram::CreateNode(){
	Node *node = 0;
	CPGraph *g = (CPGraph *)GetGraph();
	if (GetNodeType() == Code::CPD_COMPONENT_NODE)
		node = new CPDComponentNode(g);
	else if (GetNodeType() == Code::CPD_INTERFACE_NODE)
		node = new CPDInterfaceNode(g);
	else if (GetNodeType() == Code::DPD_RESOURCE_NODE)
		node = new DPDResourceNode(g);
	else if (GetNodeType() == Code::NOTE)
		node = new Note(g);
	else if (GetNodeType() == Code::COMMENT)
		node = new Comment(g);
	else
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	return node;
}

Edge *CPDiagram::CreateEdge(Subject *node1, Subject *node2){
	// Check possible connections (node-node-edge matrix).
	if (GetEdgeType() == Code::CPD_REALIZATION_EDGE ||
	    GetEdgeType() == Code::DPD_COMMUNICATION_EDGE) {
		if (node1->GetClassType() == Code::DPD_RESOURCE_NODE ||
		    node2->GetClassType() == Code::DPD_RESOURCE_NODE)
			SetEdgeType(Code::DPD_COMMUNICATION_EDGE);
		else
			SetEdgeType(Code::CPD_REALIZATION_EDGE);
	}
	if (!CheckConnection(node1, node2))
		return 0; 
	Edge *edge = 0;
	CPGraph *g = (CPGraph *)GetGraph();
	if (GetEdgeType() == Code::CPD_DEPENDENCY_EDGE)
		edge = new CPDDependencyEdge(g, node1, node2);
	else if (GetEdgeType() == Code::CPD_REALIZATION_EDGE)
		edge = new CPDRealizationEdge(g, node1, node2);
	else if (GetEdgeType() == Code::DPD_COMMUNICATION_EDGE)
		edge = new DPDCommunicationEdge(g, node1, node2);
	else if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, node1, node2);
	else 
		error( "%s, line %d: impl error: "
			" unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *CPDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	int t = GetNodeShapeType();
	if (t == Code::BUILDING_BLOCK)
		shape = new BuildingBlock(v, g, x, y);
	else if (t == Code::MINI_ELLIPSE) {
		MiniEllipse *el = new MiniEllipse(v, g, x, y);
		el->SetFixedName(False);
		el->SetNamePosition(MiniEllipse::RIGHT);
		shape = el;
	}
	else if (t == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else if (t == Code::CUBE)
		shape = new Cube(v, g, x, y);
	else if (t == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else {
		error( "%s, line %d: impl error: "
			"node shape type does not exist\n", __FILE__, __LINE__);
	}
	if (check(shape)) {
		if (HasIndexShape(t))
			shape->SetFixedIndexLabel(False);
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *CPDiagram::CreateLine(
		Edge *edge, GShape *from, GShape *to, List<Point *> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line *line = 0;
	int t = GetLineType();
	if (t == Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error( "%s, line %d: impl error: "
			"line type does not exist\n", __FILE__, __LINE__);
	if (check(line)) {
		line->SetSubject(edge);
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());
	}
	return line;
}

void CPDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::CPD_COMPONENT_NODE);
		SetNodeShapeType(Code::BUILDING_BLOCK);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::CPD_INTERFACE_NODE);
		SetNodeShapeType(Code::MINI_ELLIPSE);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		SetNodeLineStyle(LineStyle::INVISIBLE);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void CPDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::CPD_REALIZATION_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::CPD_DEPENDENCY_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::DASHED);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
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

bool CPDiagram::HasIndexNode(int code) {
	return (code == Code::CPD_COMPONENT_NODE ||
		code == Code::DPD_RESOURCE_NODE);
}

bool CPDiagram::HasIndexShape(int code) {
	return (code==Code::BUILDING_BLOCK ||
		code==Code::CUBE);
}
