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
#include "node.h"
#include "nodeshape.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "shapeview.h"
#include "drawwindow.h"
#include "createnodecmd.h"

CreateNodeCmd::CreateNodeCmd(ShapeView *v, int x, int y): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	diagram = v->GetViewer()->GetDiagram();
	node = diagram->CreateNode();
	shape = diagram->CreateNodeShape(node, x, y);
}

CreateNodeCmd::~CreateNodeCmd() {
	if (!CmdDone()) {
		if (node)
			delete node;
		if (shape)
			delete shape;
	}
}

void CreateNodeCmd::Execute() {
	if (check(node && shape)) {
		view->DeselectAll();
		view->AddShapeRaw(shape);
		view->SelectShape(shape);
		diagram->AddSubject(node);
		if (diagram->HasIndexNode(node->GetClassType()))
                        diagram->SetNextIndex(node);
		GetMainWindow()->FitDocument();
		Command::Execute();
	}
}

void CreateNodeCmd::UnExecute() {
	if (check(node && shape)) {
		view->RemoveShapeRaw(shape);
		diagram->RemoveSubject(node);
		Command::UnExecute();
	}
}
