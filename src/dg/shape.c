////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "grafport.h"
#include "subject.h"
#include "shapeview.h"
#include "diagramviewer.h"
#include "assoclist.h"
#include "inputfile.h"
#include "outputfile.h"
#include "shape.h"
#include <stdlib.h>

const int Shape::MIN_HEIGHT = 20;
const int Shape::MIN_WIDTH = 20;
const int Shape::HANDLE_WIDTH = 6;
const int Shape::MIN_HANDLES = 4;

Shape::Shape(ShapeView *v, Grafport *g): Thing() {
	position = Point(0,0);
	topleft = Point(0,0);
	width = height = 0;
	selected = firstSelected = False;
	visible = True;
	nrHandles = 0;
	subject = 0;
	grafport = g;
	view = v;
	duplicate = False;
	color = "black";
	viewer = v->GetViewer();
}

void Shape::SetDrawAttributes() {
	GetGrafport()->SetForegroundColor(&color);
}

void Shape::SetOutlineAttributes() {
	GetGrafport()->SetLineWidth(1);
	GetGrafport()->SetForegroundColor("black");
	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
}

void Shape::UpdatePosition(const Point *pos, bool snap) {
	if (visible) 
		Undraw();
	SetPosition(pos, snap);
	PositiveCoord();
	if (visible) 
		Draw();
}

void Shape::UpdateSize(int w, int h) {
	if (visible) 
		Undraw();
	SetSize(w, h);
	PositiveCoord();
	if (visible) 
		Draw();
}

void Shape::UpdateColor(string *c) {
	if (visible)
		Undraw();
	SetColor(c);
	if (visible) 
		Draw();
}

void Shape::UpdateFirstSelect(bool s) {
	if (visible) 
		Undraw();
	firstSelected = s;
	selected = s;
	if (visible) 
		Draw();
}

void Shape::UpdateSelect(bool s) {
	if (selected != s) {
		if (visible) 
			Undraw();
		selected = s;
		if (visible) 
			Draw();
	}
}

void Shape::UpdateDuplicate(bool b) {
	if (visible)
		Undraw();
	duplicate = b;
	if (visible)
		Draw();
}

void Shape::UpdateMove(const Point *delta) {
	if (visible) 
		Undraw();
	Move(delta);
	PositiveCoord();
	if (visible) 
		Draw();
}

void Shape::Move(const Point *delta) {
	Point newPosition(position.x + delta->x, position.y + delta->y);
	SetPosition(&newPosition);
}


void Shape::DrawSelect() {
	if (selected) {
		GetGrafport()->SetLineWidth(1);
		GetGrafport()->SetLineStyle(LineStyle::SOLID);
		GetGrafport()->SetForegroundColor("black"); 
		grafport->FillRectangles((Rectangle *)handles, nrHandles);
	}
}

void Shape::DrawGraySelect() {
	 if (selected) {
		GetGrafport()->SetLineWidth(1);
		GetGrafport()->SetLineStyle(LineStyle::SOLID);
		GetGrafport()->SetForegroundColor("gray"); 
		grafport->FillRectangles((Rectangle *)handles, nrHandles);
	}
}

int Shape::HitHandles(int x, int y) {
	for (int i=0;i<nrHandles;i++) {
		if (handles[i].Inside(x, y))
			return i+1;
	}
	return -1;
}

bool Shape::ContainsPt(int x, int y) {
	Rectangle rect(position.x - (width + HANDLE_WIDTH)/2, position.y - (height + HANDLE_WIDTH)/2,
			width + HANDLE_WIDTH, height + HANDLE_WIDTH);
	return rect.Inside(x, y);
}

void Shape::SetPosition(const Point *pos, bool snap) {
	position = *pos;
	if (snap)
		SnapPosition();
	topleft.x = position.x - width / 2;
	topleft.y = position.y - height / 2;
	SetPositionHandles();
}

void Shape::ForcePosition(const Point *pos) {
	position = *pos;
//	PositiveCoord();
	topleft.x = position.x - width / 2;
	topleft.y = position.y - height / 2;
	SetPositionHandles();
}

void Shape::SetSize(int w, int h) {
	if (!HasMinSize()) {
		width = max(w, MIN_WIDTH);
		height = max(h, MIN_HEIGHT);
	}
	else {
		width = w;
		height = h;
	}
	topleft.x = position.x - width / 2;
	topleft.y = position.y - height / 2;
	SetPositionHandles();
}

void Shape::SnapTopleft() {
	// snap topleft
	if (check(view)) {
		topleft.x = view->Snap(topleft.x);
		topleft.y = view->Snap(topleft.y);
	}
	// calculate position
	position.x = topleft.x + width / 2;
	position.y = topleft.y + height / 2;
}

void Shape::SnapPosition() {
	// snap position
	if (check(view)) {
		position.x = view->Snap(position.x);
		position.y = view->Snap(position.y);
	}
	// calculate topLeft
	topleft.x = position.x - width / 2;
	topleft.y = position.y - height / 2;
}


void Shape::SetTopLeft(const Point *topLeft) {
	Point pt(position);
	pt.x += topLeft->x - GetLeftMost();
	pt.y += topLeft->y - GetTopMost();
	SetPosition(&pt);
}


void Shape::SetPositionHandles() {
	// 0, 4, 6 and 8 give reasonable layout.
	if (nrHandles == 0)
		return;
	int x = position.x - HANDLE_WIDTH/2;
	int y = position.y - HANDLE_WIDTH/2;
	int w = width/2;
	int h = height/2;
	handles[0].x = x - w;
	handles[0].y = y - h;
	handles[1].x = x + w;
	handles[1].y = y - h;
	handles[2].x = x + w;
	handles[2].y = y + h;
	handles[3].x = x - w;
	handles[3].y = y + h;
	handles[4].x = x;
	handles[4].y = y + h;
	handles[5].x = x;
	handles[5].y = y - h;
	handles[6].x = x - w;
	handles[6].y = y;
	handles[7].x = x + w;
	handles[7].y = y;
}

void Shape::SetHandles(int n) {
	// set number of handles
	nrHandles = n;
	// set sizes and positions of handles
	for (int i = 0; i < n; i++) {
		handles[i].width  = HANDLE_WIDTH;
		handles[i].height = HANDLE_WIDTH;
	}
}

void Shape::PositiveCoord() {
	Point pos = *GetPosition();
	int deltax = GetLeftMost(); // position.x - width / 2;
	if (deltax < 0)
		pos.x -= deltax;
	int deltay = GetTopMost(); // position.y - height / 2;
	if (deltay < 0)
		pos.y -= deltay;
	if ( deltay < 0 || deltax < 0 )
		SetPosition(&pos);
}
 
void Shape::WriteMembers(OutputFile *ofile) {
	(*ofile) << "\t{ View " << (check(view)?view->GetId():0) << " }\n";
	(*ofile) << "\t{ Subject " << 
		(check(subject)?subject->GetId():0) << " }\n";
	(*ofile) << "\t{ Position " << position << " }\n";
	(*ofile) << "\t{ Size " << width << " " << height << " }\n";
	(*ofile) << "\t{ Color " << '"' << color << '"' << " }\n";
}

bool Shape::ReadMembers(InputFile *ifile, double format) {
	// give view and subject dummy values which are later adjusted.
	string val1, val2;
	if (format >= 1.20) {
		// read view id.
		if (!ifile->ReadAttribute("View", &val1))
			return False;
		view = (ShapeView *)(val1.toulong());
	}
	if (!ifile->ReadAttribute("Subject", &val1))
		return False;
	subject = (Subject *)(val1.toulong());
	if (!ifile->ReadAttribute2("Position", &val1, &val2))
		return False;
	position.x = val1.toint();
	position.y = val2.toint();
	if (!ifile->ReadAttribute2("Size", &val1, &val2))
		return False;
	width = val1.toint();
	height = val2.toint();
	if (format >= 1.21) {
		if (!ifile->ReadStringAttribute("Color", &val1))
			return False;
		color = val1; 
	}
	topleft.x = position.x - width / 2;
	topleft.y = position.y - height / 2;
	SetPositionHandles();
	return True;
}

bool Shape::SetAssocView(AssocList *al) {
	Assoc *find = new Assoc(view);
	Assoc *assoc = al->Get(find);
	if (assoc) {
		ShapeView *view1 = (ShapeView *)assoc->copy;
		if (check(view1))
			// search the view in viewer with the same index.
			view = viewer->GetView(view1->GetIndex());
		else
			// when no view is found, 
			// make shape part of current view.
			view = viewer->GetCurView();
	}
	else 
		// when no view is found, make shape part of current view.
		view = viewer->GetCurView();
	if (view) {
		delete find;
		return True;
	}
	else {
		error("shape %ld has no existing view\n", GetId());
		delete find;
		return False;
	}
}

bool Shape::SetAssocSubject(AssocList *al) {
	Assoc *find = new Assoc(subject);
	Assoc *assoc = al->Get(find);
	if (assoc) {
		subject = (Subject *)assoc->copy;
		if (!subject->IsSubject()) {
			error("shape %ld has not a proper subject\n", GetId());
			subject = 0;
			delete find;
			return False;
		}
		delete find;
		return True;
	}
	else {
		subject = 0;
		error("shape %ld has no existing subject\n", GetId());
		delete find;
		return False;
	}
}

bool Shape::CheckReferences() {
	// the view and subject should be existing.
	return (check(view) && check(subject) &&
		check(viewer->HasView(view)) && check(subject->InGraph()));
}

void Shape::MoveRaw(const Point *delta) {
        Point pos = *GetPosition() + *delta;
        SetPosition(&pos, False);
}
