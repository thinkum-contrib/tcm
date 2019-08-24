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
#include "graph.h"
#include "diagramstubs.h"
#include "texteditdialog.h"
#include "questiondialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include "node.h"
#include "edge.h"
#include "line.h"
#include "nodeshape.h"
#include "assoclist.h"
#include "inputfile.h"
#include "outputfile.h"
#include <stdlib.h>
#include <stdio.h>
#include "diagram.h"
#include "buffer.h"
#include "subjects.h"
#include "shapes.h"
#include "menu.h"

Sequence Diagram::sequence;

Diagram::Diagram(Config *c, DiagramWindow *d, DiagramViewer *v, Graph *g): 
		 Document(c,d,v) {
	dviewer = v;
	graph = g;
	maxid = 0;
	assocList = new AssocList();
	annotationSubject = 0;
	GetEltAnnotationDialog()->
		SetOKCallback(DiagramStubs::SubjectAnnotationOKCB, this);
}

Diagram::~Diagram() {
	delete graph;
	assocList->clear();
	delete assocList;
}

void Diagram::Initialize() {
	Document::Initialize();
	sequence.Reset();
	dviewer->Initialize();
}

bool Diagram::CheckConnection(Subject *n1, Subject *n2) {
	if (!graph->CheckConnection(
		n1->GetClassType(), n2->GetClassType(), GetEdgeType())) {
		ShowDialog(MessageDialog::ERROR, "Error", 
			   "This is not a valid connection");
		return False;
	}
	return True;
}

void Diagram::AddSubject(Subject *s){
	if (s->IsEdge())
		graph->AddEdge((Edge *)s);
	else
		graph->AddNode((Node *)s);
}

void Diagram::RemoveSubject(Subject *s){
	if (s->IsEdge())
		graph->RemoveEdge((Edge *)s);
	else
		graph->RemoveNode((Node *)s);
}

void Diagram::AddSubjects(List<Subject *> *l) {
	for (l->first(); !l->done(); l->next()) {
		Subject *s = l->cur();
		AddSubject(s);
		if (!s->IsEdge()) {
			Node *n = (Node *)s;
			if (HasIndexNode(n->GetClassType()) &&
			    *n->GetIndex() != "")
				SetNextIndex((Node *)s);
		}
	}
}

void Diagram::RemoveSubjects(List<Subject *> *l) {
	for (l->first(); !l->done(); l->next())
		RemoveSubject(l->cur());
}

void Diagram::CompleteSubjects(List<Subject *> *l) {
	graph->CompleteSubjects(l);
}

void Diagram::CompleteEdges(List<Subject *> *l) {
	graph->CompleteEdges(l);
}

void Diagram::CompleteSubject(List<Subject *> *l, Subject *s) {
	graph->CompleteSubject(l, s);
}

void Diagram::RemoveAll() {
	assocList->clear();
	Buffer *buffer = dviewer->GetBuffer();
	Shapes *shapes = 0;
        Subjects *subjects = 0;
	// make a backup of old buffer contents.
	// this is because DeleteCommands deletes the buffer contents.
        if (buffer->GetSubjects())
               	subjects = buffer->GetSubjectsCopy();
        if (buffer->GetShapes())
               	shapes = buffer->GetShapesCopy();
	if (!subjects)
               	subjects = new Subjects(assocList);
	if (!shapes)
               	shapes = new Shapes(assocList);
	DeleteDiagram();
	// restore buffer contents.
        buffer->Put(subjects, shapes);
	buffer->SetUser(0);
	delete subjects;
	delete shapes;
}

void Diagram::DeleteDiagram() {
	// delete all commands & prevent undo.
	dviewer->DeleteCommands();
	// delete all shapes and views.
	dviewer->DeleteAllViews();
	// extra delete for graph elements without shapes.
	graph->ClearNodes();
	graph->ClearEdges();
}

bool Diagram::RedirectEdge(Line *line, bool first, const Point *pt) {
	// Does pt hit a node shape other than origShape?
	ShapeView *view = line->GetView();
	NodeShape *newShape = view->HitNodeShape(pt->x,pt->y);
	GShape *origShape;
	if (first)
		origShape = line->GetFromShape();
	else
		origShape = line->GetToShape();
	if (newShape && newShape != origShape) {
		if (newShape->IsLine() && ((Line*)newShape)->IsCurved())
			return False;
		Edge *edge = (Edge *)line->GetSubject();
		GShape *end1 = line->GetFromShape();
		GShape *end2 = line->GetToShape();
		Subject *subject = newShape->GetSubject();
		Subject *subject1 = edge->GetSubject1();
		Subject *subject2 = edge->GetSubject2();
		if (first) {
			// redirect subject1 to subject.
			if (line->NrPoints()<=3 && newShape==end2)
				return False;
			int tmpEdgeType = GetEdgeType();
			SetEdgeType(edge->GetClassType());
			Edge *tmpEdge;
			if ((tmpEdge = CreateEdge(subject, subject2))) {
				line->SetFromShape(newShape);
				edge->SetSubject1(subject);
				SetEdgeType(tmpEdgeType);
				delete tmpEdge;
			}
			else {
				SetEdgeType(tmpEdgeType);
				return False;
			}
		}
		else  {
			// redirect subject2 to subject.
			if (line->NrPoints()<=3 && newShape==end1)
				return False;
			int tmpEdgeType = GetEdgeType();
			SetEdgeType(edge->GetClassType());
			Edge *tmpEdge;
			if ((tmpEdge = CreateEdge(subject1, subject))) {
				line->SetToShape(newShape);
				edge->SetSubject2(subject);
				SetEdgeType(tmpEdgeType);
				delete tmpEdge;
			}
			else {
				SetEdgeType(tmpEdgeType);
				return False;
			}
		}
		string subjName = *edge->GetName();
		if (subjName != "") {
			// Check edge name constraint.
			string empty("");
			(void)edge->SetName(&empty);
			if (!SetSubjectName(edge, &subjName)) {
				// restore old situation.
				line->SetFromShape(end1);
				edge->SetSubject1(subject1);
				line->SetToShape(end2);
				edge->SetSubject2(subject2);
				(void)edge->SetName(&subjName);
			}
		}
		// update order-count of straight redirected line.

		return True;
	}
	return False;
}

void Diagram::SelectSubject(Subject *s) {
	List<GShape *> shapes;
	dviewer->GetShapes(s, &shapes);
	for (shapes.first(); !shapes.done(); shapes.next()) {
		GShape *shape = shapes.cur();
		shape->GetView()->SelectShape(shape);
	}
}

void Diagram::SelectSubjects(List<Subject *> *s) {
	for (s->first(); !s->done(); s->next())
        	SelectSubject(s->cur());
}

void Diagram::Move(MoveType t){ 
	dviewer->MoveAllShapes(t);
}

void Diagram::LoadEntries() {
	int classNr;
	unsigned long value;
	string wrd;
	dviewer->TextModeOff();
	maxid = 0;
	if (IsAppending()) {
		// keep all existing things (but deselected).
		dviewer->DeselectAll();
	}
	else {
		// delete the entire document contents.
		RemoveAll();
		//
		Initialize();
	}
	// delete assoc objects.
	assocList->clear();
	viewsRead.empty();
	InputFile *ipf = GetInputFile(); 
	while(!ipf->Eof()) {
		// read type of the Thing
		if (!ipf->ReadWord(&wrd))
			break;
		classNr = Code::GetCode(wrd.getstr());
		// workaround for old style Dashed shape types.
		// without explicit line style.
		bool dashedShape = False;
		if (GetLoadFormat() <= 1.20) {
			if (wrd.contains("Dashed"))
				dashedShape = True;
		}
		if (classNr == 0) {
			error("%s, line %d: unknown type name %s\n", 
				ipf->GetFileName()->getstr(), 
				ipf->LineNumber(), wrd.getstr());
			break;
		}
		// read Thing ID.
		if (!ipf->ReadWord(&wrd))
			break;
		value = wrd.toulong();
		if (!ipf->LookupChar('{'))
			break;
		if (ipf->Eof())
			break;
		// create and read rest of thing
		ReadThing(classNr, value, dashedShape);
		if (!ipf->LookupChar('}'))
			break;
	}
	// place the views that are read in diagramviewer.
	PlaceViews();
	// place shapes in view the views read
	PlaceShapes();
	if (IsAppending()) {
                // appended shapes were selected.
		// so simply do a cut+paste.
                dviewer->Cut();
                dviewer->Paste();
        }
        else
                dviewer->Refresh();
	// adjust grafport for the new shapes.
	FitShapes();
	// delete views that were not be made part of diagramviewer.
	PurgeViews();
	/// Check all shapes in all views.
	dviewer->CheckShapes();
	// Check all subjects in the graph.
	CheckSubjects();
	// Set sequence number to highest id that was read.
	if (!IsAppending())
		sequence.Set(maxid);
	// delete assoc objects.
	assocList->clear();
}

void Diagram::ReadThing(int classNr, unsigned long value, bool dashedShape) {
	Thing *thing; 
	Assoc *assoc;
	int type = 0;
	thing = CreateThing(classNr);
	if (thing) {
		if (thing->IsView()) {
			type = Thing::VIEW;
			viewsRead.add((ShapeView *)thing);
		}
		else if (thing->IsSubject())
			type = Thing::SUBJECT;
		else if (thing->IsShape())
			type = Thing::SHAPE;
		else {
			delete thing;
			thing = 0;
		}
	}
	InputFile *ipf = GetInputFile(); 
	if (thing && thing->ReadMembers(ipf, GetLoadFormat())) {
		assoc = new Assoc((void *)value);
		// Check for double ids.
		if (assocList->Get(assoc)) {
			error("%s, line %d: %ld already used as "
				"an id of a thing\n", 
				ipf->GetFileName()->getstr(), 
				ipf->LineNumber(), value);
			delete assoc;
			delete thing;
			return;
		}
		if (!IsAppending()) {
			// keep the same ids as in the file.
			thing->SetId(value);
			maxid = max(value, maxid);
		}
		if (dashedShape && (check(type = Thing::SHAPE))) {
			if (check(!((Shape *)thing)->IsTextShape()))  
				((GShape *)thing)->
					SetLineStyle(LineStyle::DASHED);
		}
	}
	else {
		error("%s, line %d: thing %ld can't be read in\n", 
			ipf->GetFileName()->getstr(), ipf->LineNumber(), value);
		delete thing;
		return;
	}
	// remember read thing.
	assoc->Add(thing, type);
	assocList->Put(assoc);
}

void Diagram::PlaceViews() {
	for (viewsRead.first(); !viewsRead.done(); viewsRead.next()) {
		ShapeView *view = viewsRead.cur();
		if (check(view) && view->SetReferences(assocList))
			dviewer->AddView(view);
		else 
			error("%s: view %ld can not be read\n", 
				GetInputFile()->GetFileName()->getstr(), 
				view->GetId());
	}
}

void Diagram::PlaceShapes() {
	List<Shape *> deleteShapes;
	InputFile *ipf = GetInputFile(); 
	for (assocList->first(); !assocList->done(); assocList->next()) {
		Assoc *assoc = assocList->cur();
		if (assoc->type == Thing::SHAPE) {
			GShape *shape = (GShape *)assoc->copy;
			// set view, subject and shape pointers.
			if (check(shape) && shape->SetAssocView(assocList) &&
			    shape->SetAssocSubject(assocList) &&
			    shape->SetReferences(assocList)) {
			    	shape->SetTextShape();
				if (IsAppending()) {
					shape->SetSelect(True);
					shape->SetVisible(False);
				}
				// add to view
				shape->GetView()->AddShapeRaw(shape);
			}
			else {
				deleteShapes.add(shape);
				error("%s: shape %ld can not be read\n", 
					ipf->GetFileName()->getstr(),
					assoc->original);
			}
		}
		else if (assoc->type == Thing::SUBJECT) {
			Subject *subject = (Subject *)assoc->copy;
			// set subject pointers in edges
			if (!check(subject)) 
				error("%s: subject %ld can not be read\n", 
					ipf->GetFileName()->getstr(), 
					assoc->original);
			// refs are checked later on.
			(void) subject->SetReferences(assocList);
			// add to graph.
			if (!IsAppending()) {
				Diagram::AddSubject(subject);
			}
		}
		else if (assoc->type == Thing::VIEW) {
			; // do nothing.
		}
		else
			error("%s: thing %ld can not be read\n", 
				ipf->GetFileName()->getstr(), assoc->original);
	}
	// update duplication marks.
	for (assocList->first(); !assocList->done(); assocList->next()) {
		Assoc *assoc = assocList->cur();
		if (assoc->type == Thing::SUBJECT) {
			Subject *subject = (Subject *)assoc->copy;
			if (check(subject))
				dviewer->UpdateDuplicationMarks(subject);
		}
	}
	deleteShapes.clear();
}

void Diagram::PurgeViews() {
	for (viewsRead.first(); !viewsRead.done(); viewsRead.next()) {
		ShapeView *view = viewsRead.cur();
		// delete views that were created during reading but
		// which are not part of diagram viewer.
		if (!dviewer->HasView(view)) {
			ShapeView *v2 = dviewer->GetView(view->GetIndex());
			v2->SetId(view->GetId());
			delete view;
		}
	}
}

void Diagram::CheckSubjects() {
	List<Subject *> deleteSubjects;
	List<Subject *> nodes;
	graph->GetNodes(&nodes);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *node = nodes.cur();
		if (!check(node))
			continue;
		if (!node->CheckReferences())
			deleteSubjects.add(node);
		else if (!dviewer->GetShape(node)) {
			error("node %ld has no shape representation\n", 
				node->GetId());
			deleteSubjects.add(node);
		}
	}
	List<Subject *> edges;
	graph->GetEdges(&edges);
	for (edges.first(); !edges.done(); edges.next()) {
		Edge *edge = (Edge *)edges.cur();
		if (!check(edge))
			continue;
		if (!edge->CheckReferences())
			deleteSubjects.add(edge);
		else if (!dviewer->GetShape(edge)) {
			error("edge %ld has no shape representation\n", 
				edge->GetId());
			deleteSubjects.add(edge);
		}
	}
	graph->CompleteSubjects(&deleteSubjects);
	RemoveSubjects(&deleteSubjects);
}

void Diagram::FitShapes() {
	Point p1, p2;
	dviewer->CalcSizeElements(p1, p2);
	double wd = dviewer->Scale(p2.x) + 300.0;
	double ht = dviewer->Scale(p2.y) + 300.0;
	((DiagramWindow *)GetMainWindow())->FitDocument(int(0.5 + wd), int(0.5 + ht));
}

void Diagram::SaveEntries() {
	// write all subjects and shapes to file.
	dviewer->TextModeOff();
	OutputFile *opf = GetOutputFile();
	if (IsSaveSelection())
		dviewer->WriteSelection(opf);
	else {
		graph->WriteSubjects(opf);
		dviewer->WriteShapes(opf);
	}
}

bool Diagram::SetText(TextShape *t, const string *s) {
	const string *description = t->GetDescription();
	Subject *subj = t->GetParent()->GetSubject();
	if (*description == "Index")
		return SetIndex((Node *)subj, s);
	else if (*description == "Name")
		return SetSubjectName(subj, s);
	else {
		error("%s, line %d: impl error: "
			"unknown text shape, %s\n", 
			__FILE__,__LINE__, s->getstr());
		return False;
	}
}

bool Diagram::SetSubjectName(Subject *subject, const string *s) {
	Subject::NameErrType reason = subject->SetName(s);
	if (reason != Subject::OK) {
		string txt = "'" + *s + "' ";
		switch (reason) {
		case Subject::DOUBLE_EDGE:
			txt += " conflicts\n with an already existing edge name";
			break;
		case Subject::DOUBLE_NODE:
			txt += " conflicts\n with an already existing node name";
			break;
		case Subject::HAS_ATTRIBUTE:
			txt += " conflicts\n with an already existing attribute name";
			break;
		case Subject::HAS_ACTION:
			txt += " conflicts\n with an already existing action name";
			break;
		case Subject::IMPOSSIBLE_NAME:
			txt += "\n is not a syntactically correct name";
			break;
		case Subject::WRONG_NAME:
			txt += "wrong name\n for ";
			txt += Code::GetName(subject->GetClassType()); 
			break;
		case Subject::WRONG_NAME_CONNECTION:
			txt += "wrong name\n for "; 
			txt += Code::GetName(subject->GetClassType());
			txt += " in this kind of connection";
			break;
		default:
			error("impl. error: unknown name error type\n");
			break;
		}
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	else {
		UpdateNameStrings(subject);
		IncChanges();
		return True;
	}
}

void Diagram::UpdateNameStrings(Subject *subject) {
	// update all name strings of shapes in the viewer.
	List<GShape *> shapes;
	dviewer->GetShapes(subject, &shapes);
	for (check(shapes.first()); !shapes.done(); shapes.next()) {
		const string *str = subject->GetName();
		GShape *shape = shapes.cur();
		if (check(!shape->IsTextShape())) {
			shape->UpdateNameString(str);
			if (dviewer->IsAutoResize())
				shape->AdjustSize();
		}
	}
}

bool Diagram::SetIndex(Node *node, const string *s) {
	List<GShape *> shapes;
	dviewer->GetShapes(node, &shapes);
	Subject::NameErrType n = node->SetIndex(s);
	if (n == Subject::OK) {
		for (shapes.first(); !shapes.done(); shapes.next()) {
			NodeShape *t = (NodeShape *)shapes.cur();
			if (dviewer->IsShowIndexes())
				t->UpdateIndexLabel(s);
			else {
				string empty("");
				t->UpdateIndexLabel(&empty);
			}
		}
		if (!shapes.first()) {
			error("%s, line %d: shape does not exist\n",
				__FILE__, __LINE__);
			return False;
		}
		IncChanges();
		return True;
	}
	else if (n == Subject::IMPOSSIBLE_NAME) {
		string txt = "'" + *s + "' wrong syntax for an index";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	else if (n == Subject::DOUBLE_NODE) {
		string txt = "'" + *s + "' already exists as an index";
		ShowDialog(MessageDialog::ERROR, "Error", &txt);
		return False;
	}
	else {
		error("%s, line %d: case not handled\n",
				__FILE__, __LINE__);
	}
	return True;
}

void Diagram::FindAll(const string *s, bool sens, bool substr, bool nameOnly) {
	dviewer->FindAll(s, sens, substr, nameOnly);
}

void Diagram::FindNext(const string *s, bool sens, bool substr, bool nameOnly) {
	dviewer->FindNext(s, sens, substr, nameOnly);
}

void Diagram::ReplaceNext(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly) {
	dviewer->ReplaceNext(s1, s2, sens, substr, nameOnly);
}

void Diagram::ReplaceAll(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly) {
	dviewer->ReplaceAll(s1, s2, sens, substr, nameOnly);
}

void Diagram::AnnotateSubject(Subject *s) {
	if (GetEltAnnotationDialog()->IsManaged()) {
		ShowDialog(MessageDialog::WARNING, "Warning", 
			"At most one subject annotation dialog "
			"can be opened at a time");
		return;
	}
	const string *n = s->GetName();
	const string *annot = s->GetAnnotation();
	annotationSubject = s;
	string title = "Annotation of subject " + *n;
	if (*n == "")
		title += "<unnamed>";
	GetEltAnnotationDialog()->SetTitle(&title);
	GetEltAnnotationDialog()->SetTextString(annot);
	GetEltAnnotationDialog()->Popup();
	GetEltAnnotationDialog()->SetStatus(&title);
}

void Diagram::SetSubjectAnnotation(string *s) {
	SetStatus("action: update subject annotation");
	if (!check(annotationSubject))
		return;
	// make here an undoable command!
	annotationSubject->SetAnnotation(s);
}

void Diagram::SetCurve(bool set) {
	string txt = "curve: ";
	if (set) {
		txt += "on";
		dviewer->SetDefaultCurve(True);
	}
	else {
		txt += "off";
		dviewer->SetDefaultCurve(False);
	}
	SetStatus(&txt);
}


void Diagram::SetNextIndex(Node *n) {
	string s("");
	n->SetIndex(&s);
	if (dviewer->IsShowIndexes()) {
		// set next free number in process index
		graph->GetNextIndex(&s);
		n->SetIndex(&s);
	}
	// update the node shapes of the node.
	List<GShape *> shapes; 
	dviewer->GetShapes(n, &shapes);
	for (shapes.first(); !shapes.done(); shapes.next()) {
		NodeShape *t = (NodeShape *)shapes.cur();
		if (dviewer->IsShowIndexes() && 
		    HasIndexShape(t->GetClassType()))
			t->UpdateIndexLabel(&s);
		else {
			string empty("");
			t->UpdateIndexLabel(&empty);
		}
	}
}

void Diagram::Reindex() {
	List<Subject *> nodes;
	List<Node *> nodes2;
	graph->GetNodes(&nodes);
	const string *pref = graph->GetIndexPrefix();
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Node *node = (Node *)nodes.cur();
		if (HasIndexNode(node->GetClassType())) {
			string pi;
			node->GetParentIndex(&pi);
			if (pi == *pref)
				nodes2.add(node);
		}
	}
	dviewer->Reindex(&nodes2);
}


/* virtual */ void Diagram::SetHierarchic(bool s) {
	if ( IsHierarchic() != s ) {
		Document::SetHierarchic(s);
		string txt = "Document hierarchy is ";
		if ( IsHierarchic() )
			txt += "on";
		else
			txt += "off";
		SetStatus(&txt);
		DiagramWindow *mw =
				dynamic_cast<DiagramWindow *>(GetMainWindow());
		if ( mw ) {
			mw->SetHierarchic(IsHierarchic());
			Menu *menu = mw->GetDocumentMenu();
			if ( menu )
				Menu::SetChildToggleState(menu->GetWidget(),
					Menu::PULLDOWN, "Hierarchic Document",
					IsHierarchic());
		}
		dviewer->RecalcAllParents(IsHierarchic());
	}
}


/* virtual */ bool Diagram::AllowHierarchic() const {
	int t = GetMainWindow()->GetTool();
	if ( ! Toolkit::HierarchicEditor(t) )
		return False;
	if ( Toolkit::EditorWithoutDuplicates(t) )
		return True;
	if ( dviewer->HasDuplicates() ) {
		ShowDialog(MessageDialog::ERROR, (const char *) "Error", 
			(const char *) "Cannot produce hierarchic documents\n"
					"while there are duplicates");
		return False;
	}
	return True;
}
