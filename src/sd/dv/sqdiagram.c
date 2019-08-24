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
#include "apline.h"
#include "sqobjectnode.h"
#include "ucdsingleclassbox.h"

#include "lifeline.h"
#include "stickman.h"
#include "cbactor.h"
#include "cbclasslinkedge.h"
#include "cbobjectlinkedge.h"
#include "sqanchorlinkedge.h"

#include "textbox.h"
#include "comment.h"
#include "notebox.h"
#include "note.h"

#include "sqgraph.h"
#include "sqwindow.h"
#include "sqviewer.h"
#include "sqchecks.h"
#include "sqdiagram.h"
#include "cbdmessage.h"
#include <stdio.h>
#include <values.h>

SQDiagram::SQDiagram(Config *c, SQWindow *w, SQViewer *v, SQGraph *g): 
	   ERDiagram(c, w, v, g) {
	UpdateNodeType(1);
	UpdateEdgeType(1);
	((SQViewer *)GetDiagramViewer())->SetInFOCmode(False);
	sqChecks = new SQChecks(this, g);
}

SQDiagram::~SQDiagram() {
	delete sqChecks;
}

Thing *SQDiagram::CreateThing(int classNr) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	SQGraph *cg = (SQGraph *)GetGraph();
	Thing *thing = 0;
	if (classNr == Code::VIEW)
		thing = new ShapeView(GetDiagramViewer());

	// node shapes
	else if (classNr==Code::SSD_SINGLE_OBJECT_BOX)
//		thing = new SQObjectBoxLifeLine(v, g, 0, 0);
		thing = new LifeLine(v, g, 0, 0); 
	else if (classNr==Code::BOX)
//		thing = new SQObjectBoxLifeLine(v, g, 0, 0); 
		thing = new LifeLine(v, g, 0, 0); 
/* HZ *
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
* HZ */
	else if (classNr==Code::TEXT_BOX)
		thing = new TextBox(v, g, 0, 0); 
	else if (classNr==Code::NOTE_BOX)
		thing = new NoteBox(v, g, 0, 0); 

	// lines
/* HZ *
	else if (classNr==Code::T4_TLIST_LINE)
		thing = new T4TListLine(v, g, 0, 0, 0);
	else if (classNr==Code::C2R2_MLIST_LINE)
		thing = new C2R2MListLine(v, g, 0, 0, 0);
* HZ */
	else if (classNr==Code::LINE)	{
std::cout << " got a LINE " << std::endl << std::flush; 
		thing = new Line(v, g, 0, 0, 0);
}
	else if (classNr==Code::T4_LINE) {
std::cout << " got a T4_LINE " << std::endl << std::flush; 
		thing = new APLine(v, g, 0, 0, 0);
}

	// nodes
	else if (classNr==Code::CBD_OBJECT_NODE)	//HZ
		thing = new SQObjectNode(cg);
/* HZ *
	else if (classNr==Code::UCD_ACTOR_NODE)
		thing = new CBActor(cg);
	else if (classNr==Code::CBD_CLASS_NODE)
		thing = new CBClassNode(cg);
* HZ */




	else if (classNr==Code::NOTE)
		thing = new Note(cg);
	else if (classNr==Code::COMMENT)
		thing = new Comment(cg);

	// edges
/* HZ *
//	else if (classNr==Code::CBD_CLASS_LINK_EDGE)
//		thing = new CBClassLinkEdge(cg, 0, 0);
//	else if (classNr==Code::CBD_OBJECT_LINK_EDGE)
//		thing = new CBObjectLinkEdge(cg, 0, 0);
* HZ */
	else if (classNr==Code::CBD_OBJECT_LINK_EDGE)
		thing = new SQAnchorLinkEdge(cg, 0, 0);
	else if (classNr==Code::COMMENT_LINK)
		thing = new CommentLink(cg, 0, 0);

	else
		error("%s, line %d: impl error: wrong class number %d\n", 
			__FILE__, __LINE__, classNr);
	return thing;
}
 
Node *SQDiagram::CreateNode(){
std::cout << " Node *SQDiagram::CreateNode(" << GetNodeType() << ")" << std::endl << std::flush;
	Node *node = 0;
	SQGraph *g = (SQGraph *)GetGraph();
/* HZ *
	if (GetNodeType()==Code::UCD_ACTOR_NODE)
		node = new CBActor(g);
	else if (GetNodeType()==Code::CBD_CLASS_NODE)
		node = new CBClassNode(g);
* HZ */
	if (GetNodeType()==Code::CBD_OBJECT_NODE)	//HZ
		node = new SQObjectNode(g);
	else if (GetNodeType()==Code::NOTE)
		node = new Note(g);
	else if (GetNodeType()==Code::COMMENT)
		node = new Comment(g);
	else
		error( "%s, line %d: impl error: unknown node type\n",
			__FILE__, __LINE__);
	return node;
}

Edge *SQDiagram::CreateEdge(Subject *subj1, Subject* subj2){
std::cout << " Edge *SQDiagram::CreateEdge(" << subj1->GetId()
	<< " --> " << subj2->GetId() << ")" << std::endl << std::flush;
	if (!CheckEdgeConstraints(subj1, subj2))
		return 0;
	Edge* edge = 0;
	SQGraph *g = (SQGraph *)GetGraph();

/* HZ *
//	if (GetEdgeType() == Code::CBD_CLASS_LINK_EDGE)
//		edge = new CBClassLinkEdge(g, subj1, subj2);
//	else if (GetEdgeType() == Code::CBD_OBJECT_LINK_EDGE)
//		edge = new CBObjectLinkEdge(g, subj1, subj2);
//	else if (GetEdgeType()==Code::COMMENT_LINK)
* HZ */
	if (GetEdgeType() == Code::CBD_OBJECT_LINK_EDGE)
		edge = new SQAnchorLinkEdge(g, subj1, subj2);
	else if (GetEdgeType()==Code::COMMENT_LINK)
		edge = new CommentLink(g, subj1, subj2);
	else {
		GetMainWindow()->SetStatus(
			"aborted: Anchor point link must be selected");
			(new MessageDialog(GetMainWindow()->GetWidget(),
			MessageDialog::ERROR))->
			  Show("Error",
			  "It is not possible to create an anchor point link\n"
			  "using a Focus of Control Box");
		return 0;
	}

	return edge;
}

NodeShape *SQDiagram::CreateNodeShape(Node* node, int x, int y) {
std::cout << " NodeShape *SQDiagram::CreateNodeShape(" <<  GetNodeShapeType()
<< " @[" << x << " ," << y << "] )" << std::endl << std::flush; 
	NodeShape* shape = 0;
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();



/* HZ *
	if (GetNodeShapeType() == Code::STICKMAN)
		shape = new StickMan(v, g, x, y);

//HZ TMP
	else if (GetNodeShapeType() == Code::CE_START_NODE) {
		SetNodeShapeType(Code::STICKMAN);	//reset
		shape = new StickMan(v, g, x, y);
		shape->GetName()->SetUnderlined(True);
	}

	else if (GetNodeShapeType() == Code::CE_FINAL_NODE) {
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);	//reset
		shape = new UCDSingleClassBox(v, g, x, y);
		shape->GetName()->SetUnderlined(True);
	}



//HZ TMP



	else if (GetNodeShapeType() == Code::SSD_SINGLE_OBJECT_BOX)
		shape = new SSDSingleObjectBox(v, g, x, y); 
	else if (GetNodeShapeType() == Code::CBD_SINGLE_CLASS_BOX)
			shape = new CBSingleClassBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::SSD_SINGLE_CLASS_BOX)
//HZ		shape = new CBSingleClassBox(v, g, x, y);
			shape = new SSDSingleClassBox(v, g, x, y);

	else if (GetNodeShapeType() == Code::UCD_SINGLE_CLASS_BOX)
		shape = new UCDSingleClassBox(v, g, x, y);
	else 
* HZ */	
	
	if (GetNodeShapeType() == Code::SSD_SINGLE_OBJECT_BOX)
//		shape = new SQObjectBoxLifeLine(v, g, x, y); 
		shape = new LifeLine(v, g, x, y); 

	else if (GetNodeShapeType() == Code::NOTE_BOX)
		shape = new NoteBox(v, g, x, y);
	else if (GetNodeShapeType() == Code::TEXT_BOX)
		shape = new TextBox(v, g, x, y);

	else
		error( "%s, line %d: impl error: "
			"node shape type doesn't exist\n", __FILE__, __LINE__);

//std::cout << "A" << std::endl << std::flush; 
	if (check(shape)) {
//std::cout << "B" << std::endl << std::flush; 
		shape->SetSubject(node);
//std::cout << "C" << std::endl << std::flush; 
		shape->SetTextShape();
//std::cout << "D" << std::endl << std::flush; 
	}
//std::cout << "E" << std::endl << std::flush; 
	return shape;
}

Line *SQDiagram::CreateLine(Edge* edge, GShape *from, GShape *to, List<Point*> *l) {
	Grafport *g = GetDiagramViewer()->GetGrafport();
	ShapeView *v = GetDiagramViewer()->GetCurView();
	Line* line = 0;


/* HZ *
	if (GetLineType()== Code::T4_TLIST_LINE)
		line = new C2R2MListLine(v, g, from, to, l, IsCurve());
//HZ		line = new T4TListLine(v, g, from, to, l, IsCurve());
//HZ		line = new Line(v, g, from, to, l, IsCurve());
	else if (GetLineType()==Code::C2R2_MLIST_LINE)
		line = new C2R2MListLine(v, g, from, to, l, IsCurve());

	else 
	
* HZ */	
	if (GetLineType()== Code::LINE)
{
std::cout << " create a LINE " << std::endl << std::flush; 
		line = new Line(v, g, from, to, l, IsCurve());
}
	else if (GetLineType()== Code::T4_LINE)
{
std::cout << " create a T4_LINE " << std::endl << std::flush; 
		line = new APLine(v, g, from, to, l, IsCurve());
}
	else
		error( "%s, line %d: impl error: "
			"edge shape type does not exist\n", __FILE__, __LINE__);
	
	if (check(line)) {
std::cout << " GOING 2 SET	line->SetSubject(edge);" << std::endl << std::flush; 
		line->SetSubject(edge);

		line->SetTextShape();
		line->SetEnd1(GetLineEnd1());
		line->SetEnd2(GetLineEnd2());

//std::cout << "setting underline here : " << edge->GetClassType() << std::endl << std::flush; 

		if (edge->GetClassType()==Code::CBD_CLASS_LINK_EDGE) {
std::cout << " unsetting name underlining... " << std::endl << std::flush; 
			line->GetName()->SetUnderlined(False);
		}

		if (edge->GetClassType()==Code::CBD_OBJECT_LINK_EDGE) {
std::cout << " Setting Anchors... " << std::endl << std::flush; 
			line->SetAnchors();
		}
	}
	return line;
}

void SQDiagram::UpdateNodeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetNodeName(num);
	switch (num) {
//	case 1: SetNodeType(Code::UCD_ACTOR_NODE);
//		SetNodeShapeType(Code::STICKMAN);
	case 1: SetNodeType(Code::CBD_OBJECT_NODE);			//HZ
		SetNodeShapeType(Code::SSD_SINGLE_OBJECT_BOX);	//HZ
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 2: SetNodeType(Code::NOTE);
		SetNodeShapeType(Code::NOTE_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;

/*
	case 2: SetNodeType(Code::UCD_ACTOR_NODE);
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 3: SetNodeType(Code::CBD_CLASS_NODE);
		SetNodeShapeType(Code::SSD_SINGLE_CLASS_BOX);
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 4: SetNodeType(Code::UCD_ACTOR_NODE);
		SetNodeShapeType(Code::STICKMAN);
		SetNodeShapeType(Code::CE_START_NODE);		//HZ TMP
		SetNodeLineStyle(LineStyle::SOLID);
		break;
	case 6: SetNodeType(Code::UCD_ACTOR_NODE);
		SetNodeShapeType(Code::UCD_SINGLE_CLASS_BOX);
		SetNodeShapeType(Code::CE_FINAL_NODE);		//HZ TMP
		SetNodeLineStyle(LineStyle::SOLID);
		break;
*/

	case 3: SetNodeType(Code::CBD_OBJECT_NODE);			//HZ
		SetNodeShapeType(Code::SSD_SINGLE_OBJECT_BOX);	//HZ
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


void SQDiagram::UpdateEdgeType(int num) {
	((DiagramWindow *)GetMainWindow())->SetEdgeName(num);
	switch(num) {
	case 1: SetEdgeType(Code::CBD_OBJECT_LINK_EDGE);
		SetLineType(Code::T4_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::FILLED_ARROW);
std::cout << " VB DEselected " << std::endl << std::flush; 
		((SQViewer *)GetDiagramViewer())->SetInFOCmode(False);
		break;
	case 2: SetEdgeType(Code::COMMENT_LINK);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::WIDE_DOTTED);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);

std::cout << " VB DEselected " << std::endl << std::flush; 
		((SQViewer *)GetDiagramViewer())->SetInFOCmode(False);
		break;

	case 3: SetEdgeType(Code::EMPTY_EDGE);
		SetLineType(Code::LINE);
		SetEdgeLineStyle(LineStyle::INVISIBLE);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);

std::cout << " VB selected " << std::endl << std::flush; 
		((SQViewer *)GetDiagramViewer())->SetInFOCmode(True);
		break;


/*	
	case 3: SetEdgeType(Code::CBD_OBJECT_LINK_EDGE);
		SetLineType(Code::T4_TLIST_LINE);
		SetEdgeLineStyle(LineStyle::SOLID);
		SetLineEnd1(LineEnd::EMPTY);
		SetLineEnd2(LineEnd::EMPTY);
		break;
*/	default:
		error("%s, line %d: impl error: "
			"unknown edge type selected\n", __FILE__,__LINE__);
	}
}


/* HZ *
bool SQDiagram::SetText(TextShape *t, const string *s) {

//std::cout << "void SQDiagram::SetText() {" << std::endl << std::flush;


	const string *d = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();

//std::cout << "desc=[" << d->getstr() << "] str=[" << s->getstr() << "] subj=" 
//	<< subj->GetClassType() 
//	<< std::endl << std::flush;

	if (*d == "Stereotype" && subj->GetClassType()==Code::CBD_CLASS_NODE)
		return SetStereotype((CBClassNode*)subj, s);
	else if (*d == "Properties" && subj->GetClassType()==Code::CBD_CLASS_NODE)
		return SetProperties((CBClassNode*)subj, s);
	else if (*d == "Message")
		return SetMessage(subj, s, t->GetSequence());
	else
		return ERDiagram::SetText(t, s);
}
* HZ */



void SQDiagram::CheckDocument() {
	chkbuf = "";
	unsigned total = 0;
	// Check that object classes are named.
	total += sqChecks->CheckNamelessNodes(Code::CBD_OBJECT_NODE, chkbuf);

	ReportCheck(total, &chkbuf);
}
