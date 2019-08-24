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
#include "crchecks.h"
#include "crgraph.h"
#include "node.h"
#include "diagram.h"
 
CRChecks::CRChecks(Diagram *d, Graph *g): ERChecks(d,g) { }
 
unsigned CRChecks::CheckDoubleNamelessFunctions(
			int nodetype1, int nodetype2, string &chkbuf) {
	string s("");
	unsigned total = 0;
	List<Subject *> nodes_from;
	List<Subject *> nodes_to;
	List<Subject *> edges;
	GetGraph()->GetNodes(&nodes_from, nodetype1);
	GetGraph()->GetNodes(&nodes_to, nodetype2);
	string empty("");
	for (nodes_from.first(); !nodes_from.done(); nodes_from.next()) {
		Node *node1 = (Node *)nodes_from.cur();
		for (nodes_to.first(); !nodes_to.done(); nodes_to.next()) {
			Node *node2 = (Node *)nodes_to.cur();
			GetGraph()->GetEdges(&edges, node1, node2, 
						&empty, Code::FUNCTION);
			GetGraph()->GetEdges(&edges, node1, node2, 
						&empty,Code::COMPONENT_FUNCTION);
			unsigned count = edges.count();
			if (count > 1) {
				chkbuf += "* Error: there are ";
				chkbuf += count;
				chkbuf += " unnamed Function or "
					  "ComponentFunction edges from ";
				chkbuf += Code::GetName(nodetype1);
				chkbuf += " '";
				chkbuf += *node1->GetName();
				chkbuf += "'";
				chkbuf += " to ";
				chkbuf += Code::GetName(nodetype2);
				chkbuf += " '";
				chkbuf += *node2->GetName();
				chkbuf += "'\n";
				GetDiagram()->SelectSubjects(&edges);
				total++;
			}
			edges.empty();
		}
	}
	return total;
}

unsigned CRChecks::CheckRelationshipIsaClassNode(string &chkbuf) {
	int total = 0;
	List<Subject *> classes;
	List<Subject *> objectClasses;
	List<Subject *> relationshipClasses;
	GetGraph()->GetNodes(&classes, Code::CLASS_NODE);
	for (classes.first(); !classes.done(); classes.next()) {
		int components = GetGraph()->
				    	CountEdgesFrom((Node *)classes.cur(), 
						Code::COMPONENT_FUNCTION);
		if (components == 0)
			objectClasses.add(classes.cur());
		else if (components >= 2)
			relationshipClasses.add(classes.cur());
	}
	for (relationshipClasses.first(); !relationshipClasses.done(); 
					  relationshipClasses.next()) {
		Node *rel = (Node *)relationshipClasses.cur();
		Subject *spec = ((ERGraph *)GetGraph())->GetGeneralization(rel);
		if (spec) {
			if (objectClasses.contains(spec)) {
				chkbuf += "* Error: object class '";
				chkbuf += *spec->GetName();
				chkbuf += "' is specialized into "
					  "relationship class '";
				chkbuf += *rel->GetName();
				chkbuf += "'\n";
				GetDiagram()->SelectSubject(spec);
				GetDiagram()->SelectSubject(rel);
				total++;
			}
			else if (relationshipClasses.contains(spec)) {
				chkbuf += "* Error: relationship class '";
				chkbuf += *spec->GetName();
				chkbuf += "' is specialized into "
					  "relationship class '";
				chkbuf += *rel->GetName();
				chkbuf += "' which has additional "
					  "component functions\n";
				GetDiagram()->SelectSubject(spec);
				GetDiagram()->SelectSubject(rel);
				total++;
			}
		}
	}
	return total;
}
