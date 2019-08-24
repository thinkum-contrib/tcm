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
#include "fdwindow.h"
#include "diagramchecks.h"
#include "edge.h"
#include "fdgraph.h"
#include "fdviewer.h"
#include "fddiagram.h"
#include "line.h"

FDDiagram::FDDiagram(Config *c, FDWindow *d, FDViewer *v, FDGraph *g): 
	TRDiagram(c,d,v,g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
}

Thing *FDDiagram::CreateThing(int classNr) {
	Thing *thing = TRDiagram::CreateThing(classNr);
	if (thing->GetClassType() == Code::LINE)
		((Line *)thing)->SetFixedName(True);
	return thing;
}

Node *FDDiagram::CreateNode(){
	return TRDiagram::CreateNode();
}

Edge *FDDiagram::CreateEdge(Subject *subj1, Subject *subj2){
	return TRDiagram::CreateEdge(subj1, subj2);
}

bool FDDiagram::CheckEdgeConstraints(Subject *n1, Subject *n2) {
	return TRDiagram::CheckEdgeConstraints(n1, n2);
}

NodeShape *FDDiagram::CreateNodeShape(Node *node, int x, int y) {
	return TRDiagram::CreateNodeShape(node, x, y);
}

Line *FDDiagram::CreateLine(
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
		line->SetFixedName(True);
	}
	return line;
}

void FDDiagram::UpdateNodeType(int num) {
	TRDiagram::UpdateNodeType(num);
}

void FDDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::TEXT_EDGE);
		SetLineType(Code::LINE);
		break;
	default:
		error("%s, line %d: impl error:"
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}

void FDDiagram::CheckDocument() {
	RecalculateTree();
	chkbuf = "";
	unsigned total = GetTreeChecks()->CheckNodeCount(1, Code::TEXT_ROOT, chkbuf);
	if (total == 0)
		total += GetTreeChecks()->CheckReachability(
			Code::TEXT_ROOT, Code::TEXT_NODE, False, chkbuf);
	total += GetTreeChecks()->CheckNamelessNodes(Code::TEXT_ROOT, chkbuf);
	total += GetTreeChecks()->CheckNamelessNodes(Code::TEXT_NODE, chkbuf);
	ReportCheck(total, &chkbuf);
}
