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
#include "erview.h"
#include "erviewer.h"
#include "edge.h"
#include "node.h"
#include "line.h"

ERView::ERView(ERViewer *v): ShapeView(v) { }

void ERView::PutValueTypesTemp() {
	DeselectAll();
	List<GShape *> *s = GetShapes();
	for (s->first(); !s->done(); s->next()) {
		Shape *shape = s->cur();
		if (!shape->IsVisible())
			continue;
		Subject *subject = shape->GetSubject();
		if (shape->IsLine()) {
			Subject *subj2 = ((Edge *)subject)->GetSubject2();
			if (subj2->GetClassType() == Code::VALUE_TYPE) {
				shape->Undraw();
				shape->SetVisible(False);
			}
		}
		else if (subject->GetClassType() == Code::VALUE_TYPE) {
			shape->Undraw();
			shape->SetVisible(False);
		}
	}
}

void ERView::GetValueTypesTemp() {
	ShowAll();
	if (((ERViewer *)GetViewer())->IsIsaOnly())
		PutNotIsaTemp();
}

void ERView::PutNotIsaTemp() {
	DeselectAll();
	List<GShape *> *s = GetShapes();
	// first make everything invisible
	for (s->first(); !s->done(); s->next()) {
		Shape *shape = s->cur();
		if (shape->IsVisible()) {
			shape->Undraw();
			shape->SetVisible(False);
		}
	}
	// then look what can be made visible.
	for (s->first(); !s->done(); s->next()) {
		Shape *shape = s->cur();
		if (shape->IsVisible())
			continue;
		Subject *subject = shape->GetSubject();
		int sType = subject->GetClassType();
		if (shape->IsLine()) {
			if (sType == Code::EMPTY_EDGE || 
			    sType == Code::ISA_RELATIONSHIP) {
				// make line and connected nodes visible
				DrawWholeLine(shape); 
			}
		}
		// single entity types, object classes or comments are drawn.
		else if (sType == Code::COMMENT || 
			 sType == Code::ENTITY_TYPE || 
			 sType == Code::CLASS_NODE) {
			shape->Draw();
			shape->SetVisible(True);
		}
	} 
}

void ERView::DrawWholeLine(Shape *shape) {
	shape->Draw();
	shape->SetVisible(True);
	if (shape->IsLine()) {
		Line *line = (Line *)shape;
		GShape *n1 = line->GetFromShape();
		GShape *n2 = line->GetToShape();
		if (!n1->IsVisible()) {
			n1->Draw();
			n1->SetVisible(True);
		}
		if (!n2->IsVisible()) {
			n2->Draw();
			n2->SetVisible(True);
		}
	}
}

void ERView::GetNotIsaTemp() {
	ShowAll();
	if (((ERViewer *)GetViewer())->IsValueTypesHidden())
		PutValueTypesTemp();
}
