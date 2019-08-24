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
#include "trviewer.h"
#include "trview.h"
#include "trwindow.h"
#include "shape.h"
#include "trdiagram.h"
#include "shapeview.h"
#include "grafport.h"

TRViewer::TRViewer(Config *c, TRWindow *d): DiagramViewer(c, d) { 
	treeMode = False;
}

void TRViewer::Initialize() {
	TRView *v = new TRView(this);
	GetViews()->add(v);
	SetView(v);
}

void TRViewer::UpdateTreeMode(bool newMode) {
	if (newMode)
		SetStatus("view as forked tree");
	else
		SetStatus("view as editable graph");
	if (newMode != treeMode && !IsPasting() && !IsZigZag()) {
		DeselectAll();
		treeMode = newMode;
		if (treeMode) {
			GetMainWindow()->EnableUndo(False);
			GetMainWindow()->EnableRedo(False);
		}
		else {
			GetMainWindow()->EnableUndo(True);
			GetMainWindow()->EnableRedo(True);
		}
		Refresh();
	}
}

void TRViewer::Select(int x, int y) {
	if (!treeMode)
		DiagramViewer::Select(x, y);
}

void TRViewer::Adjust(int x, int y) {
	if (!treeMode)
		DiagramViewer::Adjust(x, y);
}

void TRViewer::MovingPointer(int x, int y) {
	if (!treeMode)
		DiagramViewer::MovingPointer(x, y);
}

void TRViewer::KeyTyped(int x, int y, int c) {
	if (!treeMode)
		DiagramViewer::KeyTyped(x, y, c);
}

Command *TRViewer::Drag(int x, int y) {
	if (!treeMode)
		return DiagramViewer::Drag(x, y);
	else
		return 0;
}

Command *TRViewer::Connect(int x, int y) {
	if (!treeMode)
		return DiagramViewer::Connect(x, y);
	else
		return 0;
}

void TRViewer::SelectAll() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::SelectAll();
}

void TRViewer::Cut() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::Cut();
}

void TRViewer::Copy() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::Copy();
}

void TRViewer::UpdateCurve() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::UpdateCurve();
}

void TRViewer::Paste() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::Paste();
}

void TRViewer::DeleteAll() {
	treeMode? SetStatus("Aborted: in view mode"):
		DiagramViewer::DeleteAll();
}

void TRViewer::DeleteSubjects() {
	treeMode? SetStatus("Aborted: in view mode"):
		DiagramViewer::DeleteSubjects();
}

void TRViewer::AlignNodes(NodeAlign::Type n) {
	treeMode? SetStatus("Aborted: in view mode"):
		DiagramViewer::AlignNodes(n);
}

void TRViewer::SameSize() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::SameSize();
}

void TRViewer::MoveAllShapes(Document::MoveType t) {
	DiagramViewer::MoveAllShapes(t);
	if (treeMode) {
		GetMainWindow()->EnableUndo(False);
		GetMainWindow()->EnableRedo(False);
	}
}

void TRViewer::Annotate() {
	treeMode? SetStatus("Aborted: in view mode"):DiagramViewer::Annotate();
}

void TRViewer::FindAll(const string *s, bool b1, bool b2, bool b3) {
	// treeMode? SetStatus("Aborted: in view mode"):
	DiagramViewer::FindAll(s, b1, b2, b3);
}

void TRViewer::FindNext(const string *s, bool b1, bool b2, bool b3) {
	// treeMode? SetStatus("Aborted: in view mode"):
	DiagramViewer::FindNext(s, b1, b2, b3);
}

void TRViewer::ReplaceNext(const string *s1, const string *s2, 
			   bool b1, bool b2, bool b3) {
	treeMode? SetStatus("Aborted: in view mode"):
		  DiagramViewer::ReplaceNext(s1, s2, b1, b2, b3);
}

void TRViewer::ReplaceAll(const string *s1, const string *s2, 
			bool b1, bool b2, bool b3) {
	treeMode? SetStatus("Aborted: in view mode"):
		  DiagramViewer::ReplaceAll(s1, s2, b1, b2, b3);
}

void TRViewer::Draw() {
	treeMode? DrawTreeMode(): DrawNormalMode();
}

void TRViewer::DrawNormalMode() {
	GetCurView()->Draw();
}

void TRViewer::DrawTreeMode() {
	GetGrafport()->SetLineStyle(LineStyle::SOLID);
	((TRDiagram *)GetDiagram())->DrawTreeLayout();
	GetCurView()->DrawNames();
}

void TRViewer::Undraw() {
	Draw();
}

void TRViewer::DrawTreeFork(Shape *root, List<Shape *> *children) {
	if (children->count() == 0)
		return;
	List<Shape *> childrenTop;
	List<Shape *> childrenBottom;
	List<Shape *> childrenLeft;
	List<Shape *> childrenRight;
	// int rootLeftMost = root->GetLeftMost();
	// int rootRightMost = root->GetRightMost();
	Point rootPosition = *root->GetPosition();
	for (children->first(); !children->done(); children->next()) {
		Shape *child = children->cur();
		int leftMost = child->GetLeftMost();
		int rightMost = child->GetRightMost();
		Point position = *child->GetPosition();
		// if (rightMost < rootRightMost - 10)
		if (rightMost <= rootPosition.x)
			childrenLeft.add(child);
		// else if (leftMost > rootLeftMost)
		else if (leftMost >= rootPosition.x)
			childrenRight.add(child);
		if (position.y <= rootPosition.y)
			childrenTop.add(child);
		else 
			childrenBottom.add(child);
	}
	if (childrenLeft.count() == children->count() || 
	    childrenRight.count() == children->count()) {
		if (childrenTop.count() == children->count()) {
			DrawVerticalTreeFork(root, children, UP);
		}
		else if (childrenBottom.count() == children->count()) {
			DrawVerticalTreeFork(root, children, DOWN);
		}
		else {
			DrawVerticalTreeFork(root, &childrenTop, UP);
			DrawVerticalTreeFork(root, &childrenBottom, DOWN);
		}
	}
	else {
		DrawHorizontalTreeFork(root, &childrenTop, UP);
		DrawHorizontalTreeFork(root, &childrenBottom, DOWN);
	}
}

void TRViewer::DrawHorizontalTreeFork(Shape *root, List<Shape *> *children, 
		DirectionType d) {
	if (children->count() == 0)
		return;
	Point rp = *root->GetPosition();
	// find extreme coordinates of the children.
	int minx = 0, maxx = 0, maxy = 0, miny = 0;
	if (children->first()) {
		Shape *child = children->cur();
		Point p = *child->GetPosition();
		miny = child->GetTopMost();
		maxy = child->GetBottomMost();
		minx = p.x;
		maxx = p.x;
		do {
			child = children->cur();
			Point pt = *child->GetPosition();
			int top = child->GetTopMost();
			int bottom = child->GetBottomMost();

			if (pt.x < minx)
				minx = pt.x;
			if (pt.x > maxx)
				maxx = pt.x;
				
			if (top < miny)
				miny = top;
			else if (bottom > maxy)
				maxy = bottom;
		} while (children->next());
	}
	// find points to attach the root.
	// and find y coordinate of horizontal bar.
	Point p1; int hbar_y;
	if (d == DOWN) {
		p1 = Point(rp.x, root->GetBottomMost());
		hbar_y = max(p1.y + 5, miny - 20);
	}
	else {
		p1 = Point(rp.x, root->GetTopMost());
		hbar_y = min(p1.y - 5, maxy + 20);
	}
	// draw line from root to hbar.
	Point p2 = Point(rp.x, hbar_y);
	GetGrafport()->DrawLine(p1.x, p1.y, p2.x, p2.y);
	// draw horizontal bar.
	Point p5 = Point(min(minx, rp.x), hbar_y);
	Point p6 = Point(max(maxx, rp.x), hbar_y);
	GetGrafport()->DrawLine(p5.x, p5.y, p6.x, p6.y);
	// draw lines from children to the horizontal bar.
	for (children->first(); !children->done(); children->next()) {
		Shape *child = children->cur();
		Point pt = *child->GetPosition();
		Point p3;
		if (d == DOWN)
			p3 = Point(pt.x, child->GetTopMost());
		else 
			p3 = Point(pt.x, child->GetBottomMost());
		Point p4 = Point(p3.x, hbar_y);
		GetGrafport()->DrawLine(p3.x, p3.y, p4.x, p4.y);
	} 
}

void TRViewer::DrawVerticalTreeFork(Shape *root, List<Shape *> *children, 
		DirectionType d) {
	Point p1;
	if (d == DOWN)
		p1 = Point(root->GetPosition()->x, root->GetBottomMost());
	else
		p1 = Point(root->GetPosition()->x, root->GetTopMost());
	if (children->first()) {
		int py = children->cur()->GetPosition()->y;
		do {
			Shape *child = children->cur();
			int cury = child->GetPosition()->y;
			Point p2 = Point(p1.x, cury);
			Point p3 = p2;
			if (child->GetPosition()->x < p1.x)
				p3.x = child->GetRightMost() + 4;
			else
				p3.x = child->GetLeftMost() - 4;
			GetGrafport()->DrawLine(p2.x, p2.y, p3.x, p3.y);
			if (d == DOWN)
				py = max(cury, py);
			else
				py = min(cury, py);
		} while (children->next());
		Point p4 = Point(p1.x, py);
		GetGrafport()->DrawLine(p1.x, p1.y, p4.x, p4.y);
	}
}
