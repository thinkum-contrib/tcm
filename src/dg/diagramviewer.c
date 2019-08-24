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
#include "alignnodeshapescmd.h"
#include "createnodecmd.h"
#include "createedgecmd.h"
#include "cutshapescmd.h"
#include "deleteshapescmd.h"
#include "deleteallsubjectscmd.h"
#include "deleteselectedsubjectscmd.h"
#include "duplicateshapescmd.h"
#include "addhandlecmd.h"
#include "deletehandlecmd.h"
#include "dragtextshapecmd.h"
#include "dragshapescmd.h"
#include "findnexttextcmd.h"
#include "moveallshapescmd.h"
#include "replacealltextscmd.h"
#include "replacenexttextcmd.h"
#include "samesizecmd.h"
#include "selectareacmd.h"
#include "sizeshapecentercmd.h"
#include "sizeshapebordercmd.h"
#include "updatetextcmd.h"
#include "updatefontcmd.h"
#include "updatetextalignmentcmd.h"
#include "updatelinewidthcmd.h"
#include "updatelinestylecmd.h"
#include "updatelinecolorcmd.h"
#include "updatefillcolorcmd.h"
#include "updatetextcolorcmd.h"
#include "updatelineendcmd.h"
#include "updatecurvecmd.h"
#include "updatetextunderlinecmd.h"
#include "reindexcmd.h"
#include "buffer.h"
#include "textshapeeditor.h"
#include "questiondialog.h"
#include "line.h"
#include "nodeshape.h"
#include "node.h"
#include "key.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "diagramstubs.h"
#include "lineenddialog.h"
#include "nodealignmentdialog.h"
#include "nodeshapedialog.h"
#include "outputfile.h"
#include <ctype.h>
#include <stdlib.h>

DiagramViewer::DiagramViewer(Config *c, DiagramWindow *w): Viewer(c, w) {
	diagram = 0;
	views = new List<ShapeView *>;
	buffer = new Buffer();
	SetInlineEditor(new TextShapeEditor(this));
	grid = new Grid(c, w, this);
	showIndexes = False;
	defaultCurve = False;
	defaultNodeLineStyle = LineStyle::SOLID;
	defaultEdgeLineStyle = LineStyle::SOLID;
	defaultLineEnd1 = LineEnd::EMPTY;
	defaultLineEnd2 = LineEnd::EMPTY;
        lineEndDialog = new LineEndDialog(w->GetWidget());
        lineEndDialog->Initialize();
	ShowDefaultLineEnd();
        alignDialog = new NodeAlignmentDialog(w->GetWidget());
        alignDialog->Initialize();
	ShowDefaultNodeAlignment();
        nodeShapeDialog = new NodeShapeDialog(w->GetWidget());
        nodeShapeDialog->Initialize();
	ShowDefaultNodeShape();
}

DiagramViewer::~DiagramViewer() {
	DeleteAllViews();
	delete views;
	delete buffer;
	delete grid;
	delete lineEndDialog;
	delete alignDialog;
	delete nodeShapeDialog;
}

void DiagramViewer::Initialize() {
	ShapeView *v = new ShapeView(this);
	views->add(v);
	SetView(v);
}

void DiagramViewer::Draw() {
	if (curView)
		curView->Draw();
}

void DiagramViewer::Undraw() {
	if (curView)
		curView->Undraw();
}

void DiagramViewer::DeleteAllViews() {
	Undraw();
	views->clear();
	curView = 0;
}

ShapeView *DiagramViewer::GetView(const string *index) {
	for (views->first(); !views->done(); views->next()) {
		if (*views->cur()->GetIndex() == *index)
			return views->cur();
	}
	return 0;
}

bool DiagramViewer::HasView(const string *index) {
	return (GetView(index) != 0);
}

bool DiagramViewer::HasView(ShapeView *view) {
	for (views->first(); !views->done(); views->next()) {
		if (views->cur() == view)
			return True;
	}
	return False;
}

bool DiagramViewer::AddView(ShapeView *v) {
	if (!HasView(v->GetIndex())) {
		views->add(v);
		// curView = v;
		return True;
	}
	return False;
}

void DiagramViewer::UpdateView(ShapeView *v) {
	Undraw();
	SetView(v);
	Draw();
}

void DiagramViewer::SetView(ShapeView *v) {
	if (!check(views->contains(v)))
		return;
	curView = v;
	((EditWindow *)GetMainWindow())->
		SetDocumentLevel(v->GetIndex());
}

void DiagramViewer::SetGrafport(Grafport *g) {
	Viewer::SetGrafport(g);
	for (views->first(); !views->done(); views->next())
		views->cur()->SetGrafport(g);
}

void DiagramViewer::Redraw() {
	Viewer::Redraw();
	if (grid->IsShowGrid())
		grid->DrawGrid();
} 

void DiagramViewer::CheckShapes() {
	for (views->first(); !views->done(); views->next()) {
		if (views->cur()->CheckReferences())
			views->cur()->CheckShapes();
	}
}

void DiagramViewer::DeselectAll() {
	for (views->first(); !views->done(); views->next())
		views->cur()->DeselectAll();
}

bool DiagramViewer::TextMode(TextShape *textShape) {
	if (IsEditing())
		return False;
	
	string status = "start text editing [";
	status += *textShape->GetDescription();
	status += "]";
	if (!IsInlineEdit()) {
		SetEditing(True);
		((TextShapeEditor *)GetInlineEditor())->StartWindow(textShape);
		SetStatus(&status);
		return False;
	}
	else if (!IsEditing()) {
		SetEditing(True);
		if (IsInlineEdit()) {
			SetCursor(MouseCursor::TERM);
			((TextShapeEditor *)GetInlineEditor())->
				Start(textShape);
		}
		SetStatus(&status);
		return True;
	}
	return False;
}

void DiagramViewer::TextModeOff() {
	if (IsEditing()) {
		if (IsInlineEdit())
			GetInlineEditor()->Stop();
		SetEditing(False);
	}
}

bool DiagramViewer::GoIntoTextMode(GShape *shape, int x, int y) {
	if (!shape)
		return False;
	if (curView->NrSelected() == 1 && shape == curView->FirstSelected()) {
		// find right textShape
		TextShape *textShape = shape->ChooseTextShape(x, y);
		if (!textShape)
			return False;
		// switch to text input
		return TextMode(textShape);
	}
	return False;
}

void DiagramViewer::KeyTyped(int x, int y, int key) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	if (!IsEditing()) {
		GShape *shape = curView->HitShape(x, y);
		unsigned char c = (unsigned char)key;
		if (!shape || Key::EditKey(key) || iscntrl(c) || 
		    !GoIntoTextMode(shape, x, y))
			return;
	}
	if (IsInlineEdit())
		EditText(key);
}

void DiagramViewer::SetCursor(int x, int y) {
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	if (IsInlineEdit()) {
		// set cursor when text shape is hit, otherwise stop editing.
		GShape *shape = curView->HitShape(x,y);
		if (shape) {
			TextShape *t = shape->ChooseTextShape(x, y);
			if (t && t==((TextShapeEditor *)GetInlineEditor())->
					GetTextShape()){
				GetInlineEditor()->SetCursor(x, y);
				return;
			}
		}
		TextModeOff();
	}
}

void DiagramViewer::Select(int x, int y) {
	if (IsEditing() && IsInlineEdit()) {
		SetCursor(x, y);
		return;
	}
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	GShape *shape = curView->HitShape(x,y);
	if (shape) {
		if (!shape->IsSelected()) {
			curView->DeselectAll();
			curView->SelectShape(shape);
			curView->SetCurrentShapeNr(shape);
			SetCursor(MouseCursor::TERM);
			SetStatus("select shape");
		}
		else if (curView->NrSelected() > 1) 
			// make selected shape the first of the selection.
			curView->FirstSelectShape(shape);
		else
			GoIntoTextMode(shape, x, y);
	}
	else
		CreateNode(x,y);
}

void DiagramViewer::Adjust(int x, int y) {
	if (IsEditing() && IsInlineEdit()) {
		TextModeOff();
		return;
	}
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	GShape *shape = curView->HitShape(x, y);
	if (shape) {
		if (shape->IsSelected()) {
			if (shape->IsLine() && curView->NrSelected() == 1) {
				Line *line = (Line *)shape; 
				int w = line->HitHandles(x, y);
				int np = line->NrPoints()-1;
				if (!line->IsCurved() && w > 0 && w < np
						&& (np > 3 || line->GetFromShape() != line->GetToShape()) ) {
					SetStatus("delete line handle");
					NewCommand(new DeleteHandleCmd(line, w));
					ExecuteCommand();
					return;
				}
			}
			curView->DeselectShape(shape);
			SetStatus("deselect shape");
		}
		else {
			curView->SelectShape(shape);
			SetStatus("add to selection");
		}
	}
	else {
		curView->DeselectAll();
	}
}

void DiagramViewer::MovingPointer(int x, int y) {
	if (curView->NrSelected() != 1) {
		SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	GShape *shape = curView->FirstSelected();
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	int w;
	if ((w = shape->HitHandles(x, y)) >= 0) {
		if ( ! shape->IsNodeShape() )
			SetSizeCursor(0);
		else
			SetSizeCursor(w);
	}
	else if (shape->InTextArea(x, y))
		SetCursor(MouseCursor::TERM);
	else
		SetCursor(MouseCursor::LEFT_PTR);
}

void DiagramViewer::CreateNode(int x, int y) {
	NewCommand(new CreateNodeCmd(curView, x, y));
	ExecuteCommand();
	SetCursor(MouseCursor::TERM);
}

Command *DiagramViewer::Drag(int x, int y) {
	GShape *shape;
	Line *line;
	TextShape *textShape;
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	int w;
	// look for text labels (of lines).
	if ((textShape = curView->HitTextShape(x, y, False))) {
		return new DragTextShapeCmd(textShape);
	}
	// look for line handle
	else if ((line = curView->HitLineHandle(x, y, w))) {
		return new DragHandleCmd(line, w);
	}
	// look for nodes shapes.
	else if ((shape = curView->HitNodeShape(x, y))) {
		if (shape->IsSelected() && (w = shape->HitHandles(x, y)) >= 0) {
			return new SizeShapeCenterCmd(shape, w);
		}
		else if (shape->IsSelected() && curView->NrSelected() > 1) {
			return new DragShapesCmd(curView);
		}
		else {
			return new DragShapeCmd(shape);
		}
	}
	else if ((line = curView->HitLine(x, y, w))) {
		if (!line->IsCurved()) {
			return new AddHandleCmd(line, x, y, w);
		}
	}
	// otherwise select area
	return new SelectAreaCmd(curView);
}

Command *DiagramViewer::Connect(int x, int y) {
	GShape *shape;
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	int w;
	// look for shape.
	if (Toolkit::EditorWithInterEdgeConnections(
			GetMainWindow()->GetTool())) { 
		if ((shape = curView->HitShape(x, y))) {
			if ( shape->IsNodeShape() && shape->IsSelected() && 
			    (w = shape->HitHandles(x, y)) >= 0)
				return new SizeShapeBorderCmd(shape, w);
			else if ( shape->IsNodeShape() || (shape->IsLine() &&
				 !((Line*)shape)->IsCurved()) )
				return new CreateEdgeCmd(shape);
		}
	}
	else if ((shape = curView->HitNodeShape(x, y))) {
		if (shape->IsSelected() && (w = shape->HitHandles(x, y)) >= 0)
			return new SizeShapeBorderCmd(shape, w);
		else
			return new CreateEdgeCmd(shape);
	}
	return 0;
}

void DiagramViewer::SelectAll() {
	SetStatus("action: select all");
	if (curView->NrOfShapes() > 0) {
		NewCommand(new SelectAllCmd(curView));
		ExecuteCommand();
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::AlignNodes(NodeAlign::Type alignType) {
	SetStatus("action: align node shapes");
	if (curView->NrSelected() >= 2) {
		NewCommand(new AlignNodeShapesCmd(curView, 
			curView->GetSelection(), alignType));
		ExecuteCommand();
	}
	else {
 		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
			Show("Warning", "You need to select two or more nodes");
		SetStatus("aborted: selection is empty or singleton");
	}
}

void DiagramViewer::FindAll(const string *s, bool sens, bool substr, 
		bool nameOnly) {
	if (curView->NrOfShapes() > 0) {
		NewCommand(new FindAllTextsCmd(curView, s, sens, substr, 
			nameOnly));
		ExecuteCommand();
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::FindNext(const string *s, bool sens, bool substr, 
		bool nameOnly) {
	if (curView->NrOfShapes() > 0) {
		NewCommand(new FindNextTextCmd(curView, s, sens, substr, 
			nameOnly));
		ExecuteCommand();
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::ReplaceNext(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly) {
	if (curView->NrOfShapes() > 0) {
		NewCommand(new ReplaceNextTextCmd(curView, s1, s2, sens, 
				substr, nameOnly));
		ExecuteCommand();
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::ReplaceAll(const string *s1, const string *s2, 
		bool sens, bool substr, bool nameOnly) {
	if (curView->NrOfShapes() > 0) {
		NewCommand(new ReplaceAllTextsCmd(
			curView, s1, s2, sens, substr, nameOnly));
		ExecuteCommand();
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::Cut() {
	SetStatus("action: cut");
	if (curView->NrSelected() > 0) {
		NewCommand(new CutShapesCmd(curView));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::Copy() {
	SetStatus("action: copy");
	if (curView->NrSelected() > 0) {
		NewCommand(new CopyShapesCmd(curView));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::Paste() {
	SetStatus("action: paste");
	if (!buffer->IsEmpty())
		NewCommand(new PasteShapesCmd(curView));
	else {
 		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
			Show("Warning", "There is nothing in the paste buffer");
		SetStatus("aborted: paste buffer is empty");
	}
}

void DiagramViewer::Duplicate() {
	SetStatus("action: duplicate");
	if (curView->NrSelected() > 0)
		NewCommand(new DuplicateShapesCmd(curView));
	else
		EmptySelectionMessage();
}

void DiagramViewer::DeleteSubjects() {
	SetStatus("action: delete Subjects");
	if (curView->NrSelected() > 0) {
		NewCommand(new DeleteSelectedSubjectsCmd(curView));
		ExecuteCommand();
		SetCursor(MouseCursor::LEFT_PTR);
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::DeleteShapes() {
	SetStatus("action: delete");
	List<GShape *> *sel = curView->GetSelection();
	bool duplicates=False;
	// Check if there are duplicate shapes.
	if (sel->first()) {
		for (sel->first(); !sel->done(); sel->next()) {
			if (sel->cur()->IsDuplicate())
				duplicates=True;
		}
		if (duplicates) {
			QuestionDialog q(GetMainWindow()->GetWidget(), True);
			q.Initialize();
			q.SetTitle("delete shapes");
			q.SetMessageString(
				"Delete all duplicates of selected shapes?");
			int answer = q.GetAnswer();
			if (answer == QuestionDialog::YES)
				DeleteSubjects();
			else if (answer == QuestionDialog::NO) {
				NewCommand(new DeleteShapesCmd(curView));
				ExecuteCommand();
				SetCursor(MouseCursor::LEFT_PTR);
			}
			else { // CANCEL.
				SetStatus("canceled: nothing deleted");
				return;
			}
		}
		else
			DeleteSubjects();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::DeleteAll() {
	SetStatus("action: delete all");
	if (curView->NrOfShapes() > 0) {
		QuestionDialog q(GetMainWindow()->GetWidget(), False);
		q.Initialize();
		q.SetTitle("delete all");
		q.SetMessageString("Are you sure you want to delete\n"
				   "all subjects in current view?");
		int answer = q.GetAnswer();
		if (answer == QuestionDialog::YES) {
			NewCommand(new DeleteAllSubjectsCmd(curView));
			ExecuteCommand();
			SetCursor(MouseCursor::LEFT_PTR);
		}
		else if (answer == QuestionDialog::NO)
			SetStatus("aborted: nothing is deleted");
	}
	else
		EmptyShapesMessage();
}

void DiagramViewer::SameSize() {
	SetStatus("action: same size");
	if (curView->NrSelected() >= 2) {
		NewCommand(new SameSizeCmd(curView));
		ExecuteCommand();
	}
	else {
 		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
			Show("Warning", "You need to select two or more nodes");
		SetStatus("aborted: selection is empty or singleton");
	}
}

void DiagramViewer::UpdateTextAlignmentSelection(TextAlign::Type a) {
	SetStatus("action: update text alignment");
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateTextAlignmentCmd(curView, a));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateLineWidthSelection(unsigned n) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateLineWidthCmd(curView, n));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateLineStyleSelection(LineStyle::Type s) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateLineStyleCmd(curView, s));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateLineColorSelection(const string *s) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateLineColorCmd(curView, s));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateTextColorSelection(const string *s) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateTextColorCmd(curView, s));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateFillColorSelection(const string *s,
		FillStyle::Type f) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateFillColorCmd(curView, s, f));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateFontSelection(int f, int s, int p) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateFontCmd(curView, f, s, p));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void DiagramViewer::Annotate() {
	SetStatus("action: annotate subject");
	if (curView->NrSelected() >= 1) {
		Subject *subject = curView->FirstSelected()->GetSubject();
		diagram->AnnotateSubject(subject);
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::MoveAllShapes(Diagram::MoveType t) {
	if (curView->NrOfShapes() > 0) {
		NewCommand(new MoveAllShapesCmd(curView, t));
		ExecuteCommand();
	}
	else
		SetStatus("aborted: empty view");
}

void DiagramViewer::UpdateText(TextShape *s, const string *n, const string *o) {
	if (s) {
		GShape *p = (GShape *)s->GetParent();
		if (curView->HasShape(p)) {
			NewCommand(new UpdateTextCmd(s, n, o));
			ExecuteCommand();
		}
		else {
 			(new MessageDialog(GetMainWindow()->GetWidget(), 
			  MessageDialog::WARNING))->
			Show("Warning", "The shape were this text "
					"belonged to,\nis already deleted");
			SetStatus("aborted: shape does not exist");
		}
	}
	else {
 		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
		Show("Warning", "The text shape of this text,\n"
				  "is already deleted");
		SetStatus("aborted: text shape does not exist");
	}
}

GShape *DiagramViewer::GetShape(Subject *subject) {
	if (!check(subject))
		return 0;
	for (views->first(); !views->done(); views->next()) {
		ShapeView *view = views->cur();
		GShape *shape = 0;
		if (check(view) && (shape = view->GetShape(subject)))
			return shape;
	}
	return 0;
}

void DiagramViewer::GetShapes(Subject *subject, List<GShape *> *s) {
	if (!check(subject))
		return;
	for (views->first(); !views->done(); views->next()) {
		ShapeView *view = views->cur();
		if (check(view))
			view->GetShapes(subject, s);
	}
}

void DiagramViewer::CalcSizeElements(Point &topLeft, Point &bottomRight) {
	curView->CalcSizeElements(topLeft, bottomRight); 
}

void DiagramViewer::CalcSizeSelection(Point &topLeft, Point &bottomRight) {
	curView->CalcSizeSelection(topLeft, bottomRight); 
}

void DiagramViewer::WriteShapes(OutputFile *f) {
	(*f) << "# VIEWS AND GRAPHICAL SHAPES\n\n";
	for (views->first(); !views->done(); views->next()) {
		views->cur()->Write(f);
		views->cur()->WriteShapes(f);
	}
}
 
void DiagramViewer::WriteSelection(OutputFile *f) {
	List<GShape *> selection (*curView->GetSelection());
	if (selection.count() == 0)
 		(new MessageDialog(GetMainWindow()->GetWidget(), 
			MessageDialog::WARNING))->
			Show("Warning", "Wrote an empty document\n"
					"because the selection is empty");
	List<Subject *> subjects;
	curView->CompleteLines(&selection);
	for (selection.first(); !selection.done(); selection.next()) {
		GShape *s = selection.cur();
		if (!subjects.contains(s->GetSubject()))
			subjects.add(s->GetSubject());
	}
	(*f) << "# NODES AND EDGES\n";
	(*f) << "# (PRODUCED BY SAVE SELECTION)\n\n";
	for (subjects.first(); !subjects.done(); subjects.next())
		subjects.cur()->Write(f);
	(*f) << "# VIEW AND GRAPHICAL SHAPES\n\n";
	curView->Write(f);
	for (selection.first(); !selection.done(); selection.next())
		selection.cur()->Write(f);
}

void DiagramViewer::EmptySelectionMessage() {
 	(new MessageDialog(GetMainWindow()->GetWidget(), 
		MessageDialog::WARNING))->
		Show("Warning", "Nothing is selected");
	SetStatus("aborted: selection is empty");
}

void DiagramViewer::EmptyShapesMessage() {
 	(new MessageDialog(GetMainWindow()->GetWidget(), 
		MessageDialog::WARNING))->
		Show("Warning", "View is empty");
	SetStatus("aborted: there are no shapes");
}


void DiagramViewer::CalcSizeShapes(List<GShape *> *s,
	Point &topLeft, Point &bottomRight) {
	if (!s->first()) {
		topLeft.Set(0, 0);
		bottomRight.Set(0, 0);
		return;
	}
	const int mval = -10;
	int x_max=mval, x_min=mval, y_max=mval, y_min=mval;
	int x, y;
	do {
		GShape *shape = s->cur();
		if (!check(shape))
			break;
		x = shape->GetRightMost() + 3;
		if (x>x_max || x_max == mval)
			x_max = x;
		x = shape->GetLeftMost() - 3;
		if (x<x_min || x_min == mval)
			x_min = x;
		y = shape->GetBottomMost() + 3;
		if (y>y_max || y_max == mval)
			y_max = y;
		y = shape->GetTopMost() - 3;
		if (y<y_min || y_min == mval)
			y_min = y;
	} while (s->next());
	x_min = abs(x_min);
	y_min = abs(y_min);
	topLeft.Set(x_min, y_min);
	bottomRight.Set(x_max, y_max);
}

void DiagramViewer::ShapePositionUpdate(GShape *shape) {
	if ( shape->IsNodeShape()
	   && Toolkit::HierarchicEditor(GetMainWindow()->GetTool()) )
		shape->GetView()->RecalcParent(shape);
	List<GShape *> shapes;
	shapes.add(shape);
	shape->GetView()->CompleteShapes(&shapes);
	for (shapes.first(); !shapes.done(); shapes.next()) {
		GShape *s = shapes.cur();
		if ( s->IsLine() && s != shape )
			((Line *)s)->UpdatePosition();
	}
}

void DiagramViewer::UpdateDuplicationMarks(List<Subject *> *s) {
	for (s->first(); !s->done(); s->next())
		UpdateDuplicationMarks(s->cur());
}

void DiagramViewer::UpdateDuplicationMarks(Subject *subject) {
	List<GShape *> shapes;
	GetShapes(subject, &shapes);
	bool duplicate = (shapes.count() >= 2);
	for (shapes.first(); !shapes.done(); shapes.next()) {
		GShape *shape = shapes.cur();
		shape->UpdateDuplicate(duplicate);
	}
}

void DiagramViewer::UpdateMoveShapes(List<GShape *> *s, const Point *delta){
	// move all shapes
	for (s->first(); !s->done(); s->next())
		s->cur()->UpdateMove(delta);
	// move line points.
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		if ( shape->IsNodeShape() )
			ShapePositionUpdate(shape);
	}
}

void DiagramViewer::MoveShapes(List<GShape *> *s, const Point *delta) {
	// move all shapes
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		shape->Move(delta);
	}
	// move line points.
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		if ( shape->IsLine() ) {
			((Line *)shape)->CalcEndPoints();
			((Line *)shape)->CalcPosition();
		}
	}
}

void DiagramViewer::ZoomIn() {
	SetStatus("action: zoom in");
}

void DiagramViewer::ZoomOut() {
	SetStatus("action: zoom out");
}

void DiagramViewer::TopLevel() {
	SetStatus("action: top level");
}

void DiagramViewer::SetIndexes(bool b) {
	SetStatus("action: show indexes");
	if (b == IsShowIndexes())
		return;
	SetShowIndexes(b);
	if (IsShowIndexes())
		SetStatus("indexes are shown");
	else
		SetStatus("indexes are hidden");
/*
	List<GShape *> *s = GetCurView()->GetShapes();
	for (s->first(); !s->done(); s->next()) {
		GShape *shape = s->cur();
		if ( ! shape->IsNodeShape() )
			continue;
		NodeShape *t = (NodeShape *)shape;
		if (IsShowIndexes())
			t->UpdateIndexLabel(((Node *)t->GetSubject())->
				GetIndex());
		else {
			const string empty("");
			t->UpdateIndexLabel(&empty);
		}
	}
*/
}

void DiagramViewer::Reindex(List<Node *> *nodes) {
	if (!check(GetDiagram()))
		return;
	if (nodes->count() > 0) {
		NewCommand(new ReindexCmd(GetCurView(), nodes));
		ExecuteCommand();
	}
	else {
		(new MessageDialog(GetMainWindow()->GetWidget(),
				   MessageDialog::WARNING))->
			Show("Warning", "There are no nodes to reindex"
					" in this diagram");
		SetStatus("aborted: no nodes");
	}
}

void DiagramViewer::UpdateLineEnd() {
	GetMainWindow()->SetStatus("action: update line ends");
	lineEndDialog->SetTitle("update line ends");
	lineEndDialog->SetHelpCallback(
		DiagramStubs::UpdateLineEndDefaultCB, this);
	lineEndDialog->SetOKCallback(
		DiagramStubs::UpdateLineEndOKCB, this);
	lineEndDialog->Popup();
}

void DiagramViewer::ShowDefaultLineEnd() {
	string text1, text2;   
	LineEnd::Type2String(defaultLineEnd1, &text1);
	LineEnd::Type2String(defaultLineEnd2, &text2);
	lineEndDialog->SetValueOfText(0, &text1);
	lineEndDialog->SetValueOfText(1, &text2);
}

void DiagramViewer::UpdateLineEndSelection(LineEnd::Type e1, LineEnd::Type e2) {
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateLineEndCmd(curView, e1, e2));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::AlignNodeShapes() {
	SetStatus("action: align node shapes");
        alignDialog->SetTitle("align node shapes");
        alignDialog->SetHelpCallback(
               DiagramStubs::AlignNodeShapesDefaultCB, this);
        alignDialog->SetOKCallback(
               DiagramStubs::AlignNodeShapesOKCB, this);
	alignDialog->Popup();
}

void DiagramViewer::ConvertNodeShapes() {
	SetStatus("action: convert node shapes");
	nodeShapeDialog->SetTitle("convert node shapes");
	nodeShapeDialog->SetHelpCallback(
		DiagramStubs::ConvertNodeShapesDefaultCB, this);
	nodeShapeDialog->SetOKCallback(
		DiagramStubs::ConvertNodeShapesOKCB, this);
	nodeShapeDialog->Popup();
}

void DiagramViewer::ShowDefaultNodeAlignment() {
	alignDialog->SetValue(0, 0);
}

void DiagramViewer::ShowDefaultNodeShape() {
	nodeShapeDialog->SetValue(0, 0);
}

void DiagramViewer::UpdateCurve() {
	SetStatus("action: convert from/to curve");
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateCurveCmd(curView));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}

void DiagramViewer::UpdateTextUnderline() {
	SetStatus("action: set/unset text underlining");
	if (curView->NrSelected() > 0) {
		NewCommand(new UpdateTextUnderlineCmd(curView));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


bool DiagramViewer::HasDuplicates() const {
	for ( views->first() ; ! views->done() ; views->next() )
		if ( views->cur()->HasDuplicates() )
			return True;
	return False;
}


void DiagramViewer::RecalcAllParents(bool hierarchicDocument) const {
	if ( ! Toolkit::HierarchicEditor(GetMainWindow()->GetTool()) )
		hierarchicDocument = False;
	for ( views->first() ; ! views->done() ; views->next() )
		views->cur()->RecalcAllParents(hierarchicDocument);
}
