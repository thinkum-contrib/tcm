//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
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

#include "messagedialog.h"
#include "ssdsingleclassbox.h"
#include "cbsingleclassbox.h"
#include "ssdsingleobjectbox.h"
#include "c2r2mlistline.h"
#include "t4tlistline.h"
#include "commentlink.h"
#include "ssdclassnode.h"
#include "cbclassnode.h"
#include "cbobjectnode.h"
#include "ucdsingleclassbox.h"

#include "stickman.h"
#include "cbactor.h"
#include "cbclasslinkedge.h"
#include "cbobjectlinkedge.h"

#include "textbox.h"
#include "comment.h"
#include "notebox.h"
#include "note.h"

#include "cbgraph.h"
#include "cbwindow.h"
#include "cbviewer.h"
#include "cbchecks.h"
#include "cbdiagram.h"
#include "cbdmessage.h"
#include <stdio.h>
#include <limits.h>

CBDiagram::CBDiagram(Config *c, CBWindow *w, CBViewer *v, CBGraph *g): 
	   ERDiagram(c, w, v, g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	cbChecks = new CBChecks(this, g);
}

CBDiagram::~CBDiagram() {
	delete cbChecks;
}

Thing *CBDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	CBGraph *cg = (CBGraph *)GetGraph();
	Thing *thing = 0;
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());

	// node shapes
	else if (classNr==Code::UCD_SINGLE_CLASS_BOX)
		thing = new UCDSingleClassBox(v, g, 0, 0); 
	else if (classNr==Code::STICKMAN)
                thing = new StickMan(v, g, 0, 0);
	else if (classNr==Code::SSD_SINGLE_CLASS_BOX)
		thing = new SSDSingleClassBox(v, g, 0, 0); 
	else if (classNr==Code::CBD_SINGLE_CLASS_BOX)
		thing = new CBSingleClassBox(v, g, 0, 0); 
	else if (classNr==Code::SSD_SINGLE_OBJECT_BOX)
		thing = new SSDSingleObjectBox(v, g, 0, 0); 
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	else if (classNr==Code::NOTE_BOX)
		thing = new NoteBox(v, g, 0, 0); 

	// lines
	else if (classNr==Code::T4_TLIST_LINE)
		thing = new T4TListLine(v, g, 0, 0, 0);
	else if (classNr==Code::C2R2_MLIST_LINE)
		thing = new C2R2MListLine(v, g, 0, 0, 0);
	else if (classNr==Code::LINE)
		thing = new Line(v, g, 0, 0, 0);

	// nodes
	else if (classNr==Code::UCD_ACTOR_NODE)	//compatibility
		thing = new CBActor(cg);
	else if (classNr==Code::CBD_ACTOR_NODE)
		thing = new CBActor(cg);
	else if (classNr==Code::CBD_CLASS_NODE)
		thing = new CBClassNode(cg);
	else if (classNr==Code::CBD_OBJECT_NODE)
		thing = new CBObjectNode(cg);

	else if (classNr==Code::NOTE)
		thing = new Note(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);

	// edges
	else if (classNr==Code::CBD_CLASS_LINK_EDGE)
		thing = new CBClassLinkEdge(cg, 0, 0);
	else if (classNr==Code::CBD_OBJECT_LINK_EDGE)
		thing = new CBObjectLinkEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);

	else
		error("%s, line %d: impl error: wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
	return thing;
}
 
Node *CBDiagram::CreateNode(){
	Node *node = 0;
	CBGraph *g = (CBGraph *)GetGraph();

	if (GetNodeType()==Code::CBD_ACTOR_NODE)
		node = new CBActor(g);
	else if (GetNodeType()==Code::CBD_CLASS_NODE)
		node = new CBClassNode(g);
	else if (GetNodeType()==Code::CBD_OBJECT_NODE)
		node = new CBObjectNode(g);
	else if (GetNodeType()==Code::NOTE)
		node = new Note(g);
	else if (GetNodeType()==Code::COMMENT)
		node = new Comment(g);
	else
		error( "%s, line %d: impl error: unknown node type\n", 
			__FILE__, __LINE__);
	return node;
}

Edge *CBDiagram::CreateEdge(Subject *subj1, Subject* subj2){
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge* edge = 0;
	CBGraph *g = (CBGraph *)GetGraph();
	if (GetEdgeType() == Code::CBD_CLASS_LINK_EDGE)
		edge = new CBClassLinkEdge(g, subj1, subj2);
	else if (GetEdgeType() == Code::CBD_OBJECT_LINK_EDGE)
		edge = new CBObjectLinkEdge(g, subj1, subj2);
	else if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, subj1, subj2);
	else
		error( "%s, line %d: impl error: unknown edge type\n", 
			__FILE__, __LINE__);

	return edge;
}

NodeShape *CBDiagram::CreateNodeShape(Node* node, int x, int y) {
	NodeShape* shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();

	if (GetNodeShapeType() == Code::STICKMAN)
		shape = new StickMan(v, g, x, y);

	else if (GetNodeShapeType() == Code::OBJECT_STICKMAN) {
		SetNodeShapeType(Code::STICKMAN);	//reset
		shape = new StickMan(v, g, x, y);
		shape->GetName()->SetUnderlined(True);
	}

	else if (GetNodeShapeType() == Code::ACTOR_OBJECT_BOX) {
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);	//reset
		shape = new UCDSingleClassBox(v, g, x, y);
		shape->GetName()->SetUnderlined(True);
	}

	else if (GetNodeShapeType() == Code::SSD_SINGLE_OBJECT_BOX)
		shape = new SSDSingleObjectBox(v, g, x, y); 
	else if (GetNodeShapeType() == Code::CBD_SINGLE_CLASS_BOX)
			shape = new CBSingleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::SSD_SINGLE_CLASS_BOX)
			shape = new SSDSingleClassBox(v, g, x, y);

	else if (GetNodeShapeType() == Code::UCD_SINGLE_CLASS_BOX)
		shape = new UCDSingleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);
	else
		error( "%s, line %d: impl error: "
			"node shape type doesn't exist\n", __FILE__, __LINE__);
	
	if (check(shape)) {
		shape->SetSubject(node);
		shape->SetTextShape();
	}
	return shape;
}

Line *CBDiagram::CreateLine(Edge* edge, GShape *from, GShape *to, List<Point*> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line* line = 0;
	if (GetLineType()== Code::T4_TLIST_LINE)
		line = new C2R2MListLine(v, g, from, to, l, IsCurve());
	else if (GetLineType()==Code::C2R2_MLIST_LINE)
		line = new C2R2MListLine(v, g, from, to, l, IsCurve());
	else if (GetLineType()== Code::LINE)
		line = new Line(v, g, from, to, l, IsCurve());
	else
		error( "%s, line %d: impl error: "
			"edge shape type does not exist\n", __FILE__, __LINE__);
	if (check(line)) {
		line->SetSubject(edge);
		if (edge->GetClassType()==Code::CBD_CLASS_LINK_EDGE) {
			line->GetName()->SetUnderlined(False);
		}
		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());
	}
	return line;
}

void CBDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
	case 1: SetNodeType(Code::CBD_ACTOR_NODE);
		SetNodeShapeType(Code::STICKMAN);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::CBD_ACTOR_NODE);
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::CBD_CLASS_NODE);
		SetNodeShapeType(Code::SSD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::COMMENT);
		SetNodeShapeType(Code::TEXT_BOX);
		SetNodeLineStyle(LineStyle::INVISIBLE);
		break;
	case 5: SetNodeType(Code::CBD_ACTOR_NODE);
		SetNodeShapeType(Code::OBJECT_STICKMAN);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 6: SetNodeType(Code::CBD_ACTOR_NODE);
		SetNodeShapeType(Code::ACTOR_OBJECT_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 7: SetNodeType(Code::CBD_OBJECT_NODE);
		SetNodeShapeType(Code::SSD_SINGLE_OBJECT_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 8: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown node type selected\n", __FILE__,__LINE__);
	}
}


void CBDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::CBD_CLASS_LINK_EDGE);
		SetLineType(Code::T4_TLIST_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	case 2: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
		SetLineEnd1(LineEnd::EMPTY);
                SetLineEnd2(LineEnd::EMPTY);
		break;
	case 3: SetEdgeType(Code::CBD_OBJECT_LINK_EDGE);
		SetLineType(Code::T4_TLIST_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}


bool CBDiagram::SetText(TextShape *t, const string *s) {
	const string *d = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*d == "Stereotype" && subj->GetClassType()==Code::CBD_CLASS_NODE)
		return SetStereotype((CBClassNode*)subj, s);
	else if (*d == "Properties" && subj->GetClassType()==Code::CBD_CLASS_NODE)
		return SetProperties((CBClassNode*)subj, s);
	else if (*d == "Message")
		return SetMessage(subj, s, t->GetSequence());
	else
		return ERDiagram::SetText(t, s);
}


bool CBDiagram::SetStereotype(CBClassNode *object, const string *s) {
	(void)object->SetStereotype(s);
	// update all shapes in the viewer.
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(object, &shapes);
	for (check(shapes.first()); !shapes.done(); shapes.next()) {
		const string *str = object->GetStereotype();
		GShape *shape = shapes.cur();
		if (check(!shape->IsTextShape())) {
			if (shape->GetClassType()==Code::SSD_SINGLE_CLASS_BOX) { 
				SSDSingleClassBox *bs = (SSDSingleClassBox *)shape;
				bs->UpdateStereotypeLabelString(str); 
			}
			if (GetDiagramViewer()->IsAutoResize())
				shape->AdjustSize();
		}
	}
	IncChanges();
	return True;
}


bool CBDiagram::SetProperties(CBClassNode *object, const string *s) {
	(void) object->SetProperties(s);
	// update all shapes in the viewer.
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(object, &shapes);
	for (check(shapes.first()); !shapes.done(); shapes.next()) {
		const string *str = object->GetProperties();
		GShape *shape = shapes.cur();
		if (check(!shape->IsTextShape())) {
			if (shape->GetClassType()==Code::SSD_SINGLE_CLASS_BOX) { 
				SSDSingleClassBox *bs = (SSDSingleClassBox *)shape;
				bs->UpdatePropertiesLabelString(str); 
			}
			if (GetDiagramViewer()->IsAutoResize())
				shape->AdjustSize();
		}
	}
	IncChanges();
	return True;
}

bool CBDiagram::SetMessage(Subject *subj, const string *s, unsigned nr) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subj, &shapes);

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
		unsigned numItems = ((CBObjectLinkEdge *)subj)->NrOfMessages();
		bool toggle = False; 	//default
        for (check(shapes.first()); !shapes.done(); shapes.next()) {
			GShape *shape = shapes.cur();
			if (shape->GetClassType() == Code::C2R2_MLIST_LINE) {
				Point from = *(((Line *)shape)->GetFromShape()->GetPosition());
				Point to = *(((Line *)shape)->GetToShape()->GetPosition());
				if (from.x > to.x)
					toggle = True;
			}	
		}
		if ((m == nr) && (m < numItems)) {
			result = ((CBObjectLinkEdge *)subj)->SetMessage(ns, m, True, toggle);
		}
		else {
			result = ((CBObjectLinkEdge *)subj)->SetMessage(ns, m, False, toggle);
			update = False;
		}

		// update and redraw  the shapes.
		if (check(shapes.first())) {
			do {
				Shape *shape = shapes.cur();
				((C2R2MListLine *)shape)->UpdateTListTextShape(ns,m);
			} while (shapes.next());
		}
		else 
			return False;

		m++;
		x = strtok(0, "\r");
		delete ns;
	}
	return True;
}

bool CBDiagram::SetRoleName(Subject *subject, const string *s, unsigned ) {
	List<GShape *> shapes;
	GetDiagramViewer()->GetShapes(subject, &shapes);
	bool succes = True;
	if (!succes) {
		string txt = "'" + *s + "' is not a possible role name";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	return True;
}


void CBDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	// Check that classes are named.
	total += cbChecks->CheckNamelessNodes(Code::CBD_CLASS_NODE, chkbuf);
	// Check that object classes are named.
	total += cbChecks->CheckNamelessNodes(Code::CBD_OBJECT_NODE, chkbuf);

	ReportCheck(total, &chkbuf);
}
