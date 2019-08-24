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
#include "erchecks.h"
#include "graph.h"
#include "relationshipnode.h"
#include "binaryrelationship.h"
#include "util.h"
#include "diagram.h"

ERChecks::ERChecks(Diagram *d, Graph *g): DiagramChecks(d,g) { }

unsigned ERChecks::CheckNamelessBinaryRelationships(string &chkbuf) {
	List<Subject *> edges;
	unsigned total=0;
	GetGraph()->GetEdges(&edges, Code::BINARY_RELATIONSHIP);
	for (edges.first(); !edges.done(); edges.next()) {
		BinaryRelationship *edge = (BinaryRelationship *)edges.cur();
		if (*edge->GetName() == "" && 
		    *edge->GetRoleName1() == "" &&
		    *edge->GetRoleName2() == "") {
			Subject *subj1 = edge->GetSubject1();
			Subject *subj2 = edge->GetSubject2();
			chkbuf += "* Error: there is an unnamed "
				  "BinaryRelationship edge between ";
			chkbuf += Code::GetName(subj1->GetClassType());
			chkbuf += " '";
			chkbuf += *subj1->GetName();
			chkbuf += "' and ";
			chkbuf += Code::GetName(subj2->GetClassType());
			chkbuf += " '";
			chkbuf += *subj2->GetName();
			chkbuf += "'\n";
			GetDiagram()->SelectSubject(edge);
			total++;
		}
	}
	return total;
}

unsigned ERChecks::CheckDoubleRelationships(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> relationships;
	List<List<string *> *> table;
	GetGraph()->GetNodes(&nodes, Code::RELATIONSHIP_NODE);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		// get all relationship nodes having two or more components.
		RelationshipNode *rel = (RelationshipNode *)nodes.cur();
		string s = *rel->GetName();
		if (s != "") {
			List<string *> *components = new List<string *>;
			rel->GetComponents(components);
			if (components->count() < 2) {
				components->clear();
				continue;
			}
			components->insert(new string(*rel->GetName()), 0);
			relationships.add(rel);
			table.add(components);
		}
	}
	List<int> processed;
	for (unsigned i=0; i<table.count(); i++) {
		List<string *> *components1 = table[i];
		if (processed.contains(i))
			continue;
		int errs = 0;
		for (unsigned j=0; j<table.count(); j++) {
			List<string *> *components2 = table[j];
			if (!check(components1->count()+
				   components2->count() >= 6))
				return total;
			if (i==j || components1->count()!=
				    components2->count() ||
			   *(*components1)[0]!=*(*components2)[0])
				continue;
			bool error = True;
			for (unsigned k=1; k<components1->count(); k++) {
			   	if (*(*components1)[k]!=*(*components2)[k]) {
					error = False;
					break;
				}
			}
			if (error) {
				errs += 1;
				GetDiagram()->SelectSubject(relationships[i]);
				GetDiagram()->SelectSubject(relationships[j]);
				processed.add(j);
			}
		}
		if (errs != 0) {
			total += 1;
			chkbuf += "* Error: There are ";
			chkbuf += errs+1;
			chkbuf += " Relationship nodes named '";
			chkbuf += *(*components1)[0];
			chkbuf += "' having the same components '";
			chkbuf += *(*components1)[1];
			for (unsigned k=2; k<components1->count(); k++) {
				chkbuf += "', '";
				chkbuf += *(*components1)[k];
			}
			chkbuf += "'\n";
		}
		processed.add(i);
	}
	for (unsigned j=0; j<table.count(); j++)
		table[j]->clear();
	table.clear();
	return total;
}

unsigned ERChecks::CheckRelationshipCoherence(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<string *> components;
	GetGraph()->GetNodes(&nodes, Code::RELATIONSHIP_NODE);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		RelationshipNode *rel = (RelationshipNode *)(nodes.cur());
		rel->GetComponents(&components);
		unsigned ent = components.count();
		if (ent < 2) {
			chkbuf += "* Error: Relationship node '";
			chkbuf += *rel->GetName();
			chkbuf += "' misses ";
			unsigned count = 2 - ent;
			chkbuf += count;
			chkbuf += " function";
			if (count != 1)
				chkbuf.addPlural();
			chkbuf += " to an EntityType node";
			chkbuf += "\n";
			GetDiagram()->SelectSubject(rel);
			total += 1;
		}
		components.clear();
	}
	return total;
}
