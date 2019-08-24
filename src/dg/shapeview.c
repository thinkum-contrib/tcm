////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#include "inputfile.h"
#include "outputfile.h"
#include "shapeview.h"
#include "nodeshape.h"
#include "line.h"
#include "node.h"
#include "assoclist.h"
#include "diagramviewer.h"
#include "diagram.h"

ShapeView::ShapeView(DiagramViewer *v): Thing() {
	viewer = v;
	parent = 0;
	index = "0";
	currentShapeNr = 0;
	shapes = new List<GShape *>;
	selection = new List<GShape *>;
}

ShapeView::~ShapeView() {
	delete selection;
	shapes->clear();
	delete shapes; 
}

void ShapeView::Draw() {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsVisible())
			shape->Draw();
	}
}
 
void ShapeView::Undraw() {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsVisible())
			shape->Undraw();
	}
}

void ShapeView::DrawNames() {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsVisible())
			shape->DrawTextShapes();
	}
}

void ShapeView::Snap(Point *p) {viewer->Snap(p);}

int ShapeView::Snap(int i) {return viewer->Snap(i);}

void ShapeView::SetGrafport(Grafport *g) {
	for ( unsigned i = shapes->count(); i-- ; )
		(*shapes)[i]->SetGrafport(g);
}

void ShapeView::WriteShapes(OutputFile *ofile) {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ )
		(*shapes)[i]->Write(ofile);
}

void ShapeView::WriteMembers(OutputFile *ofile) {
	(*ofile) << "\t{ Index " << '"' << index << '"' << " }\n";
	(*ofile) << "\t{ Parent " << (parent?parent->GetId():0) << " }\n";
}

bool ShapeView::ReadMembers(InputFile *ifile, double) {
	if (!ifile->ReadStringAttribute("Index", &index))
		return False;
	string val;
	if (!ifile->ReadAttribute("Parent", &val))
		return False;
	unsigned long value = val.toulong();
	parent = (Node *)value;
	return True;
}

bool ShapeView::SetReferences(AssocList *al) {
	// set parent node reference (parent may be 0 
	// but only when index is "0").
	Assoc *find, *assoc;
	find = new Assoc(parent);
	assoc = al->Get(find);
	if (assoc)
		parent = (Node *)assoc->copy;
	else
		parent = 0;
	delete find;
	if (index == "0") {
		if (parent) {
			error("toplevel view %ld has a parent node\n", GetId());
			parent = 0;
			return False;
		}
		else
			return True;
	}
	else {
		if (!parent) {
			error("non-toplevel view %ld has no parent node\n", 
				GetId());
			return False;
		}
		else if (!parent->IsSubject() || parent->IsEdge()) {
			error("non-toplevel view %ld has parent %ld that is " 
				"not a node\n", GetId(), parent->GetId());
			return False;
		}
		else
			return True;
	}
}

bool ShapeView::CheckReferences() {
	if (parent) {
		// when parent exists, index should not be "0".
		if (!check(index != "0"))
			return False;
		// and parent should be a node in the graph.
		if (!check(parent->InGraph()))
			return False;
	}
	else {
		// when parent is 0, index should be "0".
		if (!check(index == "0"))
			return False;
	}
	// the view should be part of its viewer.
	if (!check(viewer->HasView(this)))
		return False;
	// all shapes should have the same view reference: this.
	for ( unsigned i = shapes->count() ; i-- ; ) {
		if (!check((*shapes)[i]->GetView() == this))
			return False;
	}
	// do it also for selection.
	for ( unsigned i = selection->count() ; i-- ; ) {
		if (!check((*selection)[i]->GetView() == this))
			return False;
	}
	// all selected shapes should also be in the shapes list.
	for ( unsigned i = selection->count() ; i-- ; ) {
		if (!check(shapes->contains((*selection)[i])))
			return False;
	}
	// everything is ok, we hope.
	return True;
}

void ShapeView::CheckShapes() {
	for ( unsigned i = shapes->count(); i-- ; ) {
		GShape *shape = (*shapes)[i];
		if (check(shape))
			shape->CheckReferences();
	}
}

void ShapeView::DeselectAll() {
	if (selection->first()) {
		selection->cur()->UpdateFirstSelect(False);
		while(selection->next())
			selection->cur()->UpdateSelect(False);
	}
	selection->empty();
}


void ShapeView::SelectShape(GShape *shape) {
	if (selection->find(shape) == -1)
		selection->add(shape);
	if (selection->count() == 1)
		shape->UpdateFirstSelect(True);
	else {
		shape->UpdateFirstSelect(False);
		shape->UpdateSelect(True);
	}
}

void ShapeView::FirstSelectShape(GShape *shape) {
	if (selection->count() > 0) {
		(*selection)[0]->UpdateFirstSelect(False);
		(*selection)[0]->UpdateSelect(True);
	}
	selection->remove(shape);
	selection->insert(shape, 0);
	shape->UpdateFirstSelect(True);
}

void ShapeView::DeselectShape(GShape *shape) {
	if (!shape->IsSelected()) {
		selection->remove(shape);
		return;
	}
	if (selection->count() == 0)
		return;
	if (shape == (*selection)[0]) {
		selection->remove(shape);
		shape->UpdateFirstSelect(False);
		if (selection->count() > 0)
			(*selection)[0]->UpdateFirstSelect(True);
	}
	else {
		selection->remove(shape);
		shape->UpdateSelect(False);
	}
}

GShape *ShapeView::HitShape(int x, int y) {
	// find smallest shape at position x,y.
	GShape *shape1 = 0;
	int area = 0;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->ContainsPt(x,y) && shape->IsVisible()) {
			if ( ! shape->IsNodeShape() )
				return shape;
			if (shape1 == 0 ||
			    (shape->GetWidth() * shape->GetHeight() < area)) { 
				shape1 = shape;
				area = shape->GetWidth() * shape->GetHeight();
			}
		}
		else if ( shape->IsLine() && shape->IsVisible() ) { 
			TextShape *text = 0;
			if ((text=shape->HitTextShape(x,y)))
				return shape;
			else if (((Line *)shape)->HitHandles(x,y) >= 0)
				return shape;
		}
	}
	return shape1;
}

Line *ShapeView::HitLine(int x, int y, int &which) {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsLine() && shape->IsVisible()) {
			Line *line = (Line *)shape;
			if (line->GetLine(x, y)) {
				which = line->GetLineNumber();
				return line;
			}
		}
	}
	return 0;
}

NodeShape *ShapeView::HitNodeShape(int x, int y) {
	// find smallest node at position x,y.
	GShape *shape1 = 0;
	int area = 0;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if ( shape->IsNodeShape() && shape->ContainsPt(x,y) &&
		    shape->IsVisible() )
			if (shape1 == 0 ||
			    (shape->GetWidth() * shape->GetHeight() < area)) { 
				shape1 = shape;
				area = shape->GetWidth() * shape->GetHeight();
			}
	}
	return (NodeShape *)shape1;
}

Line *ShapeView::HitLineHandle(int x, int y, int &which) {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		Shape *shape = (*shapes)[i];
		if (shape->IsLine() && shape->IsSelected() &&
		    (which = shape->HitHandles(x, y)) >=0 &&
		    shape->IsVisible()) {
			return (Line *)shape;
		}
	}
	return 0;
}

TextShape *ShapeView::HitTextShape(int x, int y, bool emptyallowed) {
	// return text shape (of a line) at position x,y.
	TextShape *text;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsVisible() && shape->IsLine()) {
			text = shape->HitTextShape(x,y);
			if (text) {
				if (!text->IsEmpty() || emptyallowed)
					return text;
			}
		}
	}
	return 0;
}

GShape *ShapeView::GetNextShape(const string *s, bool sens,
				   bool substr, bool nameOnly) {
	unsigned count = shapes->count();
	if (count > 0) {
		if (currentShapeNr >= (int) count)
			currentShapeNr=0;
		for ( unsigned i = 0 ; i < count ; i++ ) {
			GShape *shape = (*shapes)[currentShapeNr];
			currentShapeNr++;
			if ( currentShapeNr >= (int) count)
				currentShapeNr=0;
			if (!check(shape))
				return 0;
			if (!shape->IsVisible())
				continue;
			if (nameOnly) {
				if (shape->HasNameString(s, sens, substr))
					return shape;
			}
			else {
				if (shape->HasString(s, sens, substr))
					return shape;
			}
		}
	}
	else
		currentShapeNr = 0;
	return 0;
}

void ShapeView::GetShapes(List<GShape *> *getShapes, const string *s,
			  bool sens, bool sub, bool nameOnly) {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (!shape->IsVisible())
			continue;
		if (nameOnly) {
			if (shape->HasNameString(s, sens, sub))
				getShapes->add(shape);
		}
		else {
			if (shape->HasString(s, sens, sub))
				getShapes->add(shape);
		}
	}
}

void ShapeView::CalcSizeElements(Point &topLeft, Point &bottomRight) {
	CalcSizeShapes(shapes, topLeft, bottomRight);
}

void ShapeView::CalcSizeSelection(Point &topLeft, Point &bottomRight) {
	CalcSizeShapes(selection, topLeft, bottomRight);
}

void ShapeView::CalcSizeShapes(List<GShape *> *s, Point &topLeft,
				Point &bottomRight) {
	viewer->CalcSizeShapes(s, topLeft, bottomRight);
}

void ShapeView::AddShapeRaw(GShape *shape) {
	if (!check(shape))
		return;
	shape->SetView(this);
	shapes->add(shape);
	if (shape->IsVisible())
		shape->Draw();
	if (shape->IsSelected())
		SelectShape(shape);
//SQD-B4	if (shape->IsLine()) {
//SQD-0
	if (shape->IsLine() ) {
//SQD-1
		Line *line = (Line *)shape;
		MultipleLines(line);
	}
	RecalcParent(shape);
}

void ShapeView::AddShape(GShape *shape) {
	// add to shapes. and draw the shape.
	if (!check(shape))
		return;
	AddShapeRaw(shape);
//SQD-B4	if (shape->IsLine()) {
//SQD-0
	if (shape->IsLine() ) {
//SQD-1
		Line *line = (Line *)shape;
		if (line->NrPoints() == 2)
			MultipleLinesPosUpdate(line);
	}
}

void ShapeView::AddShapes(List<GShape *> *s) {
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		if (check(shape))
			AddShape(shape);
	}
}

void ShapeView::RemoveShapeRaw(GShape *shape) {
	if (!check(shape))
		return;
	if ( Toolkit::HierarchicEditor(GetViewer()->GetMainWindow()->GetTool())
	   && shape->IsNodeShape() ) {
		// update parents:
		Subject *subj = shape->GetSubject();
		for ( unsigned i = shapes->count() ; i-- ; )
			if ( (*shapes)[i]->GetSubject()->GetParent() == subj )
				(*shapes)[i]->UpdateParent(subj->GetParent());
	}
	shapes->remove(shape);
	DeselectShape(shape);
	if (shape->IsVisible())
		shape->Undraw();


//SQD-B4	if (shape->IsLine()) {
//SQD-0
	if (shape->IsLine() ) {
//SQD-1
		Line *line = (Line *)shape;
		MultipleLines(line);
	}
}

void ShapeView::RemoveShape(GShape *shape) {
	// remove from shapes. and undraw the shape.
	if (!check(shape))
		return;
	RemoveShapeRaw(shape);
//SQD-B4	if (shape->IsLine()) {
//SQD-0
	if (shape->IsLine() ) {
//SQD-1
		Line *line = (Line *)shape;
		if (line->NrPoints() == 2)
			MultipleLinesPosUpdate(line);
	}
}

void ShapeView::RemoveShapes(List<GShape *> *s) {
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		if (check(shape))
			RemoveShape(shape);
	}
}

GShape *ShapeView::GetShape(Subject *subject) {
	if (!check(subject))
		return 0;
	for ( unsigned i = shapes->count() ; i-- ; ) {
		GShape *shape = (*shapes)[i];
		Subject *s = shape->GetSubject();
		if (check(s) && s == subject)
			return shape;
	}
	return 0;
}

void ShapeView::GetShapes(Subject *subject, List<GShape *> *s) {
	if (!check(subject))
		return;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		Subject *subj = shape->GetSubject();
		if (check(subj) && subj == subject)
			s->add(shape);
	}
}

void ShapeView::MultipleLinesPosUpdate(Line *l) {
	GShape *n1 = l->GetFromShape();
	GShape *n2 = l->GetToShape();
	List<GShape *>lines;
	CompleteShapes(&lines, n1, n2);
	for (lines.first(); !lines.done(); lines.next()) {
		Line *line = (Line *)lines.cur();
		if (line->NrPoints() == 2) {
			line->UpdatePosition();
			if (Toolkit::EditorWithInterEdgeConnections(
                        		viewer->GetMainWindow()->GetTool()))
				viewer->ShapePositionUpdate(line);
		}
	}
}

void ShapeView::MultipleLines(Line *line) {
	 // give a order number
	int count = 0;
	if (!check(line))
		return;
	// leave segmented lines and curves as they are ...
	if (line->NrPoints() > 2)
		return;
	GShape *n1 = line->GetFromShape();
	GShape *n2 = line->GetToShape();
	if (!check(n1 != 0 && n2 != 0))
		return;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsLine()) {
			Line *item = (Line *)shape;
			if (item->NrPoints() == 2) {
				GShape *shape1 = item->GetFromShape();
				GShape *shape2 = item->GetToShape();
				if (((shape1 == n1)||(shape1 == n2)) &&
				    ((shape2 == n1)||(shape2 == n2))) {
					count += 1;
					item->SetOrder(count);
				}
			}
		}
	}
	// give a count number.
	for ( unsigned i = shapes->count() ; i-- ; ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsLine()) {
			Line *item = (Line *)shape;
			if (item->NrPoints() == 2) {
				GShape *shape1 = item->GetFromShape();
				GShape *shape2 = item->GetToShape();
				if (((shape1 == n1)||(shape1 == n2)) &&
				    ((shape2 == n1)||(shape2 == n2)))
					item->SetCount(count);
			}
		}
	}
}

void ShapeView::CompleteShapes(List<GShape *> *s, GShape *n1, GShape *n2) {
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (shape->IsLine()) {
			GShape *end1 = ((Line *)shape)->GetFromShape();
			GShape *end2 = ((Line *)shape)->GetToShape();
			if (n1==end1&&n2==end2) {
				if (s->find(shape) == -1)
					s->add(shape);
			}
			else if (n1==end2&&n2==end1) {
				if (s->find(shape) == -1)
					s->add(shape);
			}
		}
	}
}

void ShapeView::CompleteLines(List<GShape *> *s) {
	List<GShape *> newLines;
	for (s->last(); !s->done(); s->prev()) {
		GShape *shape = s->cur();
		if (check(shape)) {
			if (shape->IsLine()) {
				// add shapes connected by this line.
				// if they are not already in 's'
				GShape *n1 = ((Line *)shape)->GetFromShape();
				GShape *n2 = ((Line *)shape)->GetToShape();
				if (check(n1) && s->find(n1) == -1) {
					if (n1->IsLine())
						newLines.add(n1);
					else
						s->add(n1);
				}
				if (check(n2) && s->find(n2) == -1) {
					if (n2->IsLine())
						newLines.add(n2);
					else
						s->add(n2);
				}
			}
		}
	}
	// when lines are added, add also what these lines connect.
	if (newLines.count() > 0) {
		CompleteLines(&newLines);
		for (newLines.first(); !newLines.done(); newLines.next())
			if (s->find(newLines.cur()) == -1)
				s->add(newLines.cur());
	}
}

void ShapeView::CompleteShapes(List<GShape *> *s) {
	List<GShape *> newLines;
	for ( unsigned i = 0 ; i < shapes->count() ; i++ ) {
		GShape *shape = (*shapes)[i];
		if (check(shape)) {
			if (shape->IsLine()) {
				// add line if connected by one of the shapes
				// in s and if the line is not already in 's'.
				GShape *n1 = ((Line *)shape)->GetFromShape();
				GShape *n2 = ((Line *)shape)->GetToShape();
				if ((check(n1) && s->find(n1) != -1) ||
				    (check(n2) && s->find(n2) != -1)) {
					if (s->find(shape) == -1) {
						s->add(shape);
						newLines.add(shape);
					}
				}
			}
		}
	}
	// add lines connected to added lines.
	if (newLines.count() > 0) {
		CompleteShapes(&newLines);
		for (newLines.first(); !newLines.done(); newLines.next())
			if (s->find(newLines.cur()) == -1)
				s->add(newLines.cur());
	}
}

void ShapeView::ShowAll() {
	for ( unsigned i = shapes->count(); i-- ; ) {
		GShape *shape = (*shapes)[i];
		if (!shape->IsVisible()) {
			shape->Draw();
			shape->SetVisible(True);
		}
	}
}


void ShapeView::RecalcParent(GShape *shape) const {
	if ( ! Toolkit::HierarchicEditor(
				GetViewer()->GetMainWindow()->GetTool())
				|| ! shape->IsNodeShape() )
		return;
	Subject *subject = shape->GetSubject();
	if ( ! subject || subject->IsEdge() )
		return;
	Node *oldParent = subject->GetParent();
	shape->UpdateParent(parent); // == ShapeView's parent
	if ( ! GetViewer()->GetDiagram()->IsHierarchic() )
		return;

	List<Subject *> children;
	List<GShape *> childshapes;
	List<Node *> parents, allParents;

	// Look for potential parents and children.
	for ( unsigned i = shapes->count() ; i-- ; ) {
		GShape *shape1 = (*shapes)[i];
		if ( ! shape1->IsNodeShape() || shape1 == shape )
			continue;
		Subject *subject1 = shape1->GetSubject();
		if ( ! subject1 || subject1->IsEdge() || subject1 == subject )
			continue;
		if ( subject1->GetParent() == subject ) {
			shape1->UpdateParent(oldParent);
		}
		if ( shape->ContainsChild(shape1) ) {
			children.add(subject1);
			childshapes.add(shape1);
		} else if ( shape1->ContainsChild(shape) ) {
			parents.add((Node *) subject1);
			allParents.add((Node *) subject1);
		}
	}
	// remove non-minimal potential parents.
	for ( allParents.first() ; ! allParents.done() ; allParents.next() )
		parents.remove(allParents.cur()->GetParent());
	allParents.empty();

	if ( parents.count() ) {
		shape->UpdateParent(parents[0]);
		parents.empty();
	}

	// Maximal children's elements become children of *subject.
	if ( children.first() && childshapes.first() ) {
		do {
			Subject *par = children.cur()->GetParent();
			if ( children.find(par) < 0 )
				childshapes.cur()->UpdateParent(
							(Node *) subject);
		} while ( children.next() && childshapes.next() );
		children.empty();
		childshapes.empty();
	}
}


void ShapeView::IntRecalcAllParents(GShape *shape,
					const List<GShape *> *relevant,
					List<GShape *> *toBeHandled) const {
	// the procedure recalculates the parent of *shape's subject.
	// The parent is a member of *relevant. Not all members of *relevant
	// may be ancestors of shape.
	// For some members of *relevant, the procedure also recalculates the
	// parent. The procedure removes these members from *toBeHandled, so
	// that on return, *toBeHandled only contains members whose parent has
	// not yet been recalculated.
	toBeHandled->remove(shape);
	if ( ! shape->IsNodeShape() )
		return;
	Subject *subject = shape->GetSubject();
	if ( ! subject || subject->IsEdge() )
		return;
	// Look for ancestors of *shape.
	List<GShape *> ancestor;
	int area = -1;
	GShape *min = 0; // the shape with minimal area
	for ( unsigned i = relevant->count() ; i-- ;  ) {
		GShape *shape1 = (*relevant)[i];
		Subject *subject1 = shape1->GetSubject();
		if ( ! shape1->IsNodeShape() || shape1 == shape || ! subject1
						|| subject1->IsEdge()
						|| subject1 == subject ) {
//			toBeHandled->remove(shape1);
		} else if ( shape1->ContainsChild(shape) ) {
			int area1 = shape1->GetWidth() * shape1->GetHeight();
			if ( area1 < area || area < 0 ) {
				area = area1;
				min = shape1;
			}
			ancestor.add(shape1);
		}
	}

	// *min cannot contain any other potential parent. So, it must be the
	// actual parent
	shape->UpdateParent(min ? (Node *) min->GetSubject() : parent);

	if ( min && toBeHandled->find(min) >= 0 ) {
		ancestor.remove(min);
		IntRecalcAllParents(min, &ancestor, toBeHandled);
	}
	ancestor.empty();
}


void ShapeView::RecalcAllParents(bool hierarchicDocument) const {
	// recalculates all parents for this view.
	if ( hierarchicDocument ) {
		List<GShape *> sh = *shapes;
		while ( sh.count() )
			IntRecalcAllParents(sh[0], shapes, &sh);
	} else
		for ( shapes->first() ; ! shapes->done() ; shapes->next() )
			shapes->cur()->UpdateParent(parent);
	return;
}


bool ShapeView::HasDuplicates() const {
	for ( shapes->first() ; ! shapes->done() ; shapes->next() )
		if ( shapes->cur()->IsDuplicate() )
			return True;
	return False;
}
