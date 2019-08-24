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
#include "reindexcmd.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "node.h"
#include "nodeshape.h"

ReindexCmd::ReindexCmd(ShapeView *v, List<Node *> *n): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	for (n->first(); !n->done(); n->next()) {
		Diagram *d = v->GetViewer()->GetDiagram();
		if (d->HasIndexNode(n->cur()->GetClassType()) &&
		    *n->cur()->GetIndex() != "") 
			nodes.add(n->cur());
	}
	if (nodes.first()) {
		nodes.cur()->GetParentIndex(&parent);
		do {
			Node *node = nodes.cur();
			string *s = new string(*node->GetIndex());
			oldIndexes.add(s);
		} while (nodes.next());
	}
}
 
ReindexCmd::~ReindexCmd() {
	oldIndexes.clear();
}

void ReindexCmd::Execute() {
	// avoid index clashes.
	for (nodes.first(); !nodes.done(); nodes.next()) {
		string empty("");
		nodes.cur()->SetIndex(&empty);
	} 
	int n = 1;
	for (nodes.first(); !nodes.done(); nodes.next()) {
		string s = parent;
		Node *node = nodes.cur();
		if (s != "")
			s += '.';
		s += n;
		n++;
		SetIndex(node, &s);
	} 
	GetDocument()->IncChanges();
	SetCmdDone(True);
	SayCommited();
}

void ReindexCmd::SetIndex(Node *node, const string *index) {
	List<GShape *> shapes;
	((DiagramViewer *)GetViewer())->GetShapes(node, &shapes);
	Subject::NameErrType err = node->Node::SetIndex(index);
	if (err == Subject::OK) {
		for (shapes.first(); !shapes.done(); shapes.next()) {
			NodeShape *t = (NodeShape *)shapes.cur();
			if (((DiagramViewer *)GetViewer())->IsShowIndexes())
				t->UpdateIndexLabel(index);
			else {
				string empty("");
				t->UpdateIndexLabel(&empty);
			}
		}
		if (!shapes.first()) {
			error("%s, line %d: shape does not exist\n",
				__FILE__, __LINE__);
			return;
		}
	}
}

void ReindexCmd::UnExecute() {
	// avoid index clashes.
	for (nodes.first(); !nodes.done(); nodes.next()) {
		string empty("");
		nodes.cur()->SetIndex(&empty);
	} 
	if (oldIndexes.first() && nodes.first()) {
		do {
			Node *node = nodes.cur();
			string s = *oldIndexes.cur();
			SetIndex(node, &s);
		} while (oldIndexes.next() && nodes.next());
	}
	GetDocument()->DecChanges();
	SetCmdDone(False);
	SayUndone();
}
