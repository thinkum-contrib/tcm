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
#include "erviewer.h"
#include "erview.h"
#include "erwindow.h"
#include "edge.h"
#include "node.h"
#include "line.h"
#include "updatereaddirectioncmd.h"

ERViewer::ERViewer(Config *c, ERWindow *d): DiagramViewer(c, d) {
	valueTypesHidden = False;
	isaOnly = False;
}

void ERViewer::Initialize() {
	ERView *v = new ERView(this);
	GetViews()->add(v);
	SetView(v);
}

void ERViewer::SetHideValueTypes(bool set) {
	// DeleteCommand();
	string status = "value types are ";
	status += (set ? "hidden":"visible");
	GetMainWindow()->SetStatus(&status);
	if (set == valueTypesHidden)
		return;
	valueTypesHidden = set;
	List<ShapeView *> *v = GetViews();
	for (v->first(); !v->done(); v->next()) {
		if (valueTypesHidden)
			((ERView *)v->cur())->PutValueTypesTemp();
		else
			((ERView *)v->cur())->GetValueTypesTemp();
	}
}

void ERViewer::SetShowISA(bool set) {
	// DeleteCommand();
	if (set)
		GetMainWindow()->SetStatus("make only is-a hierarchy visible");
	else
		GetMainWindow()->SetStatus("make all visible");
	if (isaOnly == set)
		return;
	isaOnly = set;
	List<ShapeView *> *v = GetViews();
	for (v->first(); !v->done(); v->next()) {
		if (isaOnly)
			((ERView *)v->cur())->PutNotIsaTemp();
		else 
			((ERView *)v->cur())->GetNotIsaTemp();
	}
}

void ERViewer::UpdateReadDirection(ReadDirection::Type dir) {
        SetStatus("action: Update read direction");
        if (GetCurView()->NrSelected() > 0) {
                NewCommand(new UpdateReadDirectionCmd(GetCurView(), dir));
                ExecuteCommand();
        }
        else
                EmptySelectionMessage();
}

