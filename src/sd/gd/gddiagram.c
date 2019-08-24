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
#include "gdgraph.h"
#include "genericedge.h"
#include "genericnode.h"
#include "emptynode.h"
#include "miniellipse.h"
#include "blackdot.h"
#include "box.h"
#include "bullseye.h"
#include "circle.h"
#include "square.h"
#include "notebox.h"
#include "roundedbox.h"
#include "ellipsedbox.h"
#include "triangle.h"
#include "hexagon.h"
#include "horizontalbar.h"
#include "verticalbar.h"
#include "solidhorizontalbar.h"
#include "solidverticalbar.h"
#include "diamond.h"
#include "line.h"
#include "textbox.h"
#include "comment.h"
#include "stickman.h"
#include "folder.h"
#include "disk.h"
#include "buildingblock.h"
#include "cube.h"
#include "subfolder.h"
#include "gddiagram.h"
#include "gdviewer.h"
#include "gdwindow.h"

#include "gdboundaryshape.h"
#include "gdcontrollershape.h"
#include "gdentityshape.h"

const int GDDiagram::DOT_WIDTH = 8;
 
GDDiagram::GDDiagram(Config *c, GDWindow *d, GDViewer *v, GDGraph *g): 
		Diagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
}

Thing *GDDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Thing *thing = 0;

	switch ( classNr ) {
	case Code::BOX:
		thing = new Box(v, g, 0, 0); 
		break;
	case Code::SQUARE:
		thing = new Square(v, g, 0, 0); 
		break;
	case Code::CIRCLE:
		thing = new Circle(v, g, 0, 0); 
		break;
	case Code::ELLIPSE:
		thing = new Ellipse(v, g, 0, 0); 
		break;
	case Code::STICKMAN:
		thing = new StickMan(v, g, 0, 0); 
		break;
	case Code::TRIANGLE:
		thing = new Triangle(v, g, 0, 0); 
		break;
	case Code::HEXAGON:
		thing = new Hexagon(v, g, 0, 0); 
		break;
	case Code::HORIZONTAL_BAR:
		thing = new HorizontalBar(v, g, 0, 0); 
		break;
	case Code::VERTICAL_BAR:
		thing = new VerticalBar(v, g, 0, 0); 
		break;
	case Code::ROUNDED_BOX:
		thing = new RoundedBox(v, g, 0, 0); 
		break;
	case Code::ELLIPSED_BOX:
		thing = new EllipsedBox(v, g, 0, 0); 
		break;
	case Code::DIAMOND:
		thing = new Diamond(v, g, 0, 0); 
		break;
	case Code::TEXT_BOX:
		thing = new TextBox(v, g, 0, 0); 
		break;
	case Code::BLACK_DOT:
		thing = new BlackDot(v, g, 0, 0); 
		break;
	case Code::BULLS_EYE:
		thing = new BullsEye(v, g, 0, 0); 
		break;
	case Code::SOLID_HORIZONTAL_BAR:
                thing = new SolidHorizontalBar(v, g, 0, 0);
		break;
	case Code::SOLID_VERTICAL_BAR:
                thing = new SolidVerticalBar(v, g, 0, 0);
		break;
	case Code::NOTE_BOX:
                thing = new NoteBox(v, g, 0, 0);
		break;
	case Code::BUILDING_BLOCK:
                 thing = new BuildingBlock(v, g, 0, 0);
		break;
	case Code::CUBE:
                 thing = new Cube(v, g, 0, 0);
		break;
	case Code::FOLDER:
                 thing = new Folder(v, g, 0, 0);
		break;
	case Code::SUB_FOLDER:
                 thing = new SubFolder(v, g, 0, 0);
		break;
	case Code::DISK:
                 thing = new Disk(v, g, 0, 0);
		break;
	case Code::GD_BOUNDARY_SHAPE:
		thing = new GDBoundaryShape(v, g, 0, 0);
		break;
	case Code::GD_CONTROLLER_SHAPE:
		thing = new GDControllerShape(v, g, 0, 0);
		break;
	case Code::GD_ENTITY_SHAPE:
		thing = new GDEntityShape(v, g, 0, 0);
		break;

	case Code::VIEW:
		thing = new ShapeView(GetDiagramViewer()); 
		break;

	case Code::LINE:
		thing = new Line(v, g, 0, 0, 0);
		break;
	// old line (arrow) types...
	case Code::ARROW:
		{
			Line *line = new Line(v, g, 0, 0, 0);
			line->SetEnd2(LineEnd::FILLED_ARROW);
			thing = line;
		}
		break;
	case Code::DOUBLE_ARROW:
		{
			Line *line = new Line(v, g, 0, 0, 0);
			line->SetEnd1(LineEnd::FILLED_ARROW);
			line->SetEnd2(LineEnd::FILLED_ARROW);
			thing = line;
		}
		break;
	case Code::DOUBLE_HEADED_ARROW:
		{
			Line *line = new Line(v, g, 0, 0, 0);
			line->SetEnd2(LineEnd::DOUBLE_FILLED_ARROW);
			thing = line;
		}
		break;

	case Code::GENERIC_NODE:
		thing = new GenericNode(GetGraph());
		break;
	case Code::EMPTY_NODE:
		thing = new EmptyNode(GetGraph());
		break;
	case Code::COMMENT:
		thing = new Comment(GetGraph());
		break;

	case Code::GENERIC_EDGE:
		thing = new GenericEdge(GetGraph(), 0, 0);
		break;
	default:
		error("%s, line %d: impl error: " "wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
		return 0;
	}
	if (thing != 0 && HasIndexShape(thing->GetClassType()))
		((NodeShape *)thing)->SetFixedIndexLabel(False);

	return thing;
}

Node *GDDiagram::CreateNode(){
	Node *node = 0;
	switch ( GetNodeType() ) {
	case Code::GENERIC_NODE:
		node = new GenericNode(GetGraph());
		break;
	case Code::EMPTY_NODE:
		node = new EmptyNode(GetGraph());
		break;
	case Code::COMMENT:
		node = new Comment(GetGraph());
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type\n", __FILE__, __LINE__);
	}
	return node;
}

Edge *GDDiagram::CreateEdge(Subject *node1, Subject *node2){
	// Check possible connections (node-node-edge matrix).
	if (!CheckConnection(node1, node2))
		return 0; 
	Edge *edge = 0;
	if (GetEdgeType() == Code::GENERIC_EDGE)
		edge = new GenericEdge(GetGraph(), node1, node2);
	else 
		error( "%s, line %d: impl error: "
			" unknown edge type\n", __FILE__, __LINE__);
	return edge;
}

NodeShape *GDDiagram::CreateNodeShape(Node *node, int x, int y) {
	NodeShape *shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	int t = GetNodeShapeType();
	switch ( t ) {
	case Code::BOX:
		shape = new Box(v, g, x, y);
		break;
	case Code::SQUARE:
		shape = new Square(v, g, x, y);
		break;
	case Code::CIRCLE:
		shape = new Circle(v, g, x, y);
		break;
	case Code::ELLIPSE:
		shape = new Ellipse(v, g, x, y);
		break;
	case Code::STICKMAN:
		shape = new StickMan(v, g, x, y);
		break;
	case Code::HEXAGON:
		shape = new Hexagon(v, g, x, y);
		break;
	case Code::HORIZONTAL_BAR:
		shape = new HorizontalBar(v, g, x, y);
		break;
	case Code::VERTICAL_BAR:
		shape = new VerticalBar(v, g, x, y);
		break;
	case Code::TRIANGLE:
		shape = new Triangle(v, g, x, y);
		break;
	case Code::ROUNDED_BOX:
		shape = new RoundedBox(v, g, x, y);
		break;
	case Code::ELLIPSED_BOX:
		shape = new EllipsedBox(v, g, x, y);
		break;
	case Code::DIAMOND:
		shape = new Diamond(v, g, x, y);
		break;
	case Code::NOTE_BOX:
		shape = new NoteBox(v, g, x, y);
		break;
	case Code::BLACK_DOT:
		shape = new BlackDot(v, g, x, y);
		break;
	case Code::BULLS_EYE:
		shape = new BullsEye(v, g, x, y);
		break;
	case Code::TEXT_BOX:
		shape = new TextBox(v, g, x, y);
		break;
	case Code::SOLID_HORIZONTAL_BAR:
                shape = new SolidHorizontalBar(v, g, x, y);
		break;
	case Code::SOLID_VERTICAL_BAR:
                shape = new SolidVerticalBar(v, g, x, y);
		break;
	case Code::BUILDING_BLOCK:
	 	shape = new BuildingBlock(v, g, x, y);
		break;
	case Code::CUBE:
	 	shape = new Cube(v, g, x, y);
		break;
	case Code::FOLDER:
	 	shape = new Folder(v, g, x, y);
		break;
	case Code::SUB_FOLDER:
	 	shape = new SubFolder(v, g, x, y);
		break;
	case Code::DISK:
	 	shape = new Disk(v, g, x, y);
		break;
	case Code::GD_BOUNDARY_SHAPE:
		shape = new GDBoundaryShape(v, g, x, y);
		break;
	case Code::GD_CONTROLLER_SHAPE:
		shape = new GDControllerShape(v, g, x, y);
		break;
	case Code::GD_ENTITY_SHAPE:
		shape = new GDEntityShape(v, g, x, y);
		break;
	default:
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

Line *GDDiagram::CreateLine(
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

void GDDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::BOX);
		break;
	case 2: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::CIRCLE);
		break;
	case 3: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::ROUNDED_BOX);
		break;
	case 4: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::TRIANGLE);
		break;
	case 5: SetNodeType(Code::EMPTY_NODE);
		SetNodeShapeType(Code::BULLS_EYE);
		break;
	case 6: SetNodeType(Code::GENERIC_NODE);
	 	SetNodeShapeType(Code::STICKMAN);
	 	break;
	case 7: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::CUBE);
		break;
	case 8: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::GD_BOUNDARY_SHAPE);
		break;
	case 9: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		break;
	case 10: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::DIAMOND);
		break;
	case 11: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::SQUARE);
		break;
	case 12: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::VERTICAL_BAR);
		break;
	case 13: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::HEXAGON);
		break;
	case 14: SetNodeType(Code::EMPTY_NODE);
		SetNodeShapeType(Code::SOLID_VERTICAL_BAR);
		break;
	case 15: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::FOLDER);
		break;
	case 16: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::BUILDING_BLOCK);
		break;
	case 17: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::GD_CONTROLLER_SHAPE);
		break;
	case 18: SetNodeType(Code::GENERIC_NODE);
	 	SetNodeShapeType(Code::NOTE_BOX);
	 	break;
	case 19: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::ELLIPSE);
		break;
	case 20: SetNodeType(Code::EMPTY_NODE);
		SetNodeShapeType(Code::BLACK_DOT);
		break;
	case 21: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::HORIZONTAL_BAR);
		break;
	case 22: SetNodeType(Code::GENERIC_NODE);
	 	SetNodeShapeType(Code::ELLIPSED_BOX);
	 	break;
	case 23: SetNodeType(Code::EMPTY_NODE);
		SetNodeShapeType(Code::SOLID_HORIZONTAL_BAR);
		break;
	case 24: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::SUB_FOLDER);
		break;
	case 25: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::DISK);
		break;
	case 26: SetNodeType(Code::GENERIC_NODE);
		SetNodeShapeType(Code::GD_ENTITY_SHAPE);
		break;
	default:
		error("%s, line %d: impl error: "
		"unknown node type selected\n", __FILE__,__LINE__);
	}
}

void GDDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	SetEdgeType(Code::GENERIC_EDGE);
	SetLineType(Code::LINE);
	switch(num) {
	case 1: SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetLineEnd1(LineEnd::FILLED_ARROW);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 3: SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
		break;
	case 4: SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::WHITE_TRIANGLE);
		break;
	case 5: SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::DOUBLE_FILLED_ARROW);
		break;
	case 6: SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::OPEN_ARROW);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

bool GDDiagram::HasIndexNode(int code) {
	return (code == Code::GENERIC_NODE);
}

bool GDDiagram::HasIndexShape(int code) {
	switch ( code ) {
	case Code::BOX:
	case Code::SQUARE:
	case Code::ELLIPSE:
	case Code::CIRCLE:
	case Code::ROUNDED_BOX:
	case Code::DIAMOND:
	case Code::TRIANGLE:
	case Code::HORIZONTAL_BAR:
	case Code::VERTICAL_BAR:
	case Code::NOTE_BOX:
	case Code::HEXAGON:
	case Code::ELLIPSED_BOX:
	case Code::FOLDER:
	case Code::SUB_FOLDER:
	case Code::CUBE:
	case Code::BUILDING_BLOCK:
	case Code::STICKMAN:
	case Code::DISK:
	case Code::GD_BOUNDARY_SHAPE:
	case Code::GD_CONTROLLER_SHAPE:
	case Code::GD_ENTITY_SHAPE:
		return 1;
	default:
		return 0;
	}
}
