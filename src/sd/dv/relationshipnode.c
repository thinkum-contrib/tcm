////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam
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
#include "relationshipnode.h"
#include "ergraph.h"
#include "lstring.h"
#include "edge.h"

RelationshipNode::RelationshipNode(ERGraph *g): Node(g) { }

Subject::NameErrType RelationshipNode::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else
		return Node::SetName(s);
}

void RelationshipNode::GetComponents(List<string *> *components) {
	List<Subject *> edgesFrom;
	components->empty();
	GetGraph()->GetEdgesFrom(&edgesFrom, this, Code::FUNCTION);
	for (edgesFrom.first(); !edgesFrom.done(); edgesFrom.next()) {
		Edge *edge = (Edge *)edgesFrom.cur();
		if (edge->GetSubject2()->GetClassType() == Code::ENTITY_TYPE) {
			string *n = new string(*edge->GetSubject2()->GetName());
			components->add(n);
		}
	}
	components->sort(CompareComponent);
}
