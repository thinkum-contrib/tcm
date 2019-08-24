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
#include "ergraph.h"
#include "edge.h"
#include "util.h"

ERGraph::ERGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::ENTITY_TYPE;
	nodeTypes[i++] = Code::VALUE_TYPE;
	nodeTypes[i++] = Code::TAXONOMY_JUNCTION;
	nodeTypes[i++] = Code::RELATIONSHIP_NODE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::BINARY_RELATIONSHIP;
	edgeTypes[j++] = Code::FUNCTION;
	edgeTypes[j++] = Code::EMPTY_EDGE;
	edgeTypes[j++] = Code::ISA_RELATIONSHIP;
	edgeTypes[j++] = 0;
}

Subject *ERGraph::GetGeneralization(Subject *subj) {
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		if (edge->GetClassType()==Code::ISA_RELATIONSHIP) {
			if (edge->GetSubject1() == subj)
				return edge->GetSubject2();
		}
		else if (edge->GetClassType()==Code::EMPTY_EDGE) {
			Subject *junction = 0;
			if (edge->GetSubject1() == subj)
				junction = edge->GetSubject2();
			else if (edge->GetSubject2() == subj)
				junction = edge->GetSubject1();
			if (junction) {
				List<Edge *> edges2 = *edges;
				for (edges2.first(); !edges2.done(); edges2.next()) {
					Edge *edge2 = edges2.cur();
					if (edge2->GetClassType()==Code::ISA_RELATIONSHIP) {
						if (edge2->GetSubject1() == junction)
							return edge2->GetSubject2();
					}
				}
			}
		}
	}
	return 0;
}

bool ERGraph::IsaLeaves(Subject *subj) {
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		Subject *n1 = edge->GetSubject1();
		if (n1 == subj && edge->GetClassType()==Code::ISA_RELATIONSHIP) {
			return True;
		}
	}
	return False;
}

bool ERGraph::IsaPathExists(Subject *subj1, Subject *subj2) {
	List<Edge *> path;
	return IsaPathExists(subj1, subj2, &path);
}

bool ERGraph::IsaPathExists(Subject *subj1, Subject *subj2, List<Edge *> *path) {
	// should be made more generic !!!
	for (edges->first(); !edges->done(); edges->next()) {
		Edge *edge = edges->cur();
		Subject *n1 = edge->GetSubject1();
		Subject *n2 = edge->GetSubject2();
		bool step = False;

		// is_a: only n1 -> n2.
		int edgetype = edge->GetClassType();
		int subj1type = subj1->GetClassType();
		if (n1 == subj1 && edgetype==Code::ISA_RELATIONSHIP) {
			step = True;
		}
		else if (edgetype==Code::EMPTY_EDGE && 
			 (subj1type==Code::ENTITY_TYPE||subj1type==Code::CLASS_NODE) &&
			 (n1 == subj1 || n2 == subj1)) {

			step = True;
			if (subj1==n2) {
				Subject *tmp = n1;
				n1 = n2;
				n2 = tmp;
			}
		}
		if (step) {
			if (n2==subj2) {
				path->add(edge);
				return True;
			}
			else if (path->find(edge) == -1) {
				path->add(edge);
				if (IsaPathExists(n2, subj2, path))
					return True;
				path->remove(edge);
				if (!edges->setcur(edge))
					error("%s %d: internal graph error\n", 
						__FILE__, __LINE__);
			}
			step = False;
		}
	} 
	return False;
}

void ERGraph::InitConnections () {
	int ENT = Code::GetIndex(Code::ENTITY_TYPE, nodeTypes);
	int TAX = Code::GetIndex(Code::TAXONOMY_JUNCTION, nodeTypes);
	int VAL = Code::GetIndex(Code::VALUE_TYPE, nodeTypes);
	int REL = Code::GetIndex(Code::RELATIONSHIP_NODE, nodeTypes);
	int FUN = Code::GetIndex(Code::FUNCTION, edgeTypes);
	int MAN = Code::GetIndex(Code::BINARY_RELATIONSHIP, edgeTypes);
	int EMP = Code::GetIndex(Code::EMPTY_EDGE, edgeTypes);
	int ISA = Code::GetIndex(Code::ISA_RELATIONSHIP, edgeTypes);

	connections[ENT][ENT][FUN] = True;
	connections[ENT][ENT][MAN] = True;
	connections[ENT][ENT][ISA] = True;

	connections[ENT][VAL][FUN] = True;
	connections[ENT][TAX][EMP] = True;

	connections[TAX][ENT][EMP] = True;
	connections[TAX][ENT][ISA] = True;

	connections[REL][ENT][FUN] = True;
	connections[REL][VAL][FUN] = True;
}
