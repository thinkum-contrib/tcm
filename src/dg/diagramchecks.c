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
#include "graph.h"
#include "diagram.h"
#include "node.h"
#include "edge.h"
#include "diagramchecks.h"

DiagramChecks::DiagramChecks(Diagram *d, Graph *g) {
	diagram = d;
	graph = g;
}

unsigned DiagramChecks::CheckCount(unsigned min, unsigned max,
		int type, string &chkbuf, bool node) {
	unsigned total;
	List<Subject *> s;
	if (node)
		total = graph->GetNodes(&s, type);
	else
		total = graph->GetEdges(&s, type);
	if (total < min || total > max) {
		chkbuf += "* Error: diagram has ";
		chkbuf += total;
		chkbuf += ' ';
		chkbuf += Code::GetName(type);
		if (total != 1)
			chkbuf.addPlural();
		chkbuf += "\n";
		diagram->SelectSubjects(&s);
		return 1;
	}
	return 0;
}

unsigned DiagramChecks::CheckNodeCount(unsigned count, int nodeType, 
			string &chkbuf) {
	return CheckNodeCount(count, count, nodeType, chkbuf);
}

unsigned DiagramChecks::CheckNodeCount(unsigned min, unsigned max, 
		int nodeType, string &chkbuf) {
	return CheckCount(min, max, nodeType, chkbuf, True);
}

unsigned DiagramChecks::CheckEdgeCount(unsigned count, int edgeType, 
			string &chkbuf) {
	return CheckEdgeCount(count, count, edgeType, chkbuf);
}

unsigned DiagramChecks::CheckEdgeCount(unsigned min, unsigned max, 
		int edgeType, string &chkbuf) {
	return CheckCount(min, max, edgeType, chkbuf, False);
}


unsigned DiagramChecks::CheckNamelessNodes(int nodeType, string &chkbuf) {
	string empty("");
	return CheckIllegalNodeNames(nodeType, &empty, chkbuf);
}

unsigned DiagramChecks::CheckNamelessEdges(int nodeType, string &chkbuf) {
	string empty("");
	return CheckIllegalEdgeNames(nodeType, &empty, chkbuf);
}

unsigned DiagramChecks::CheckIllegalNodeNames(int nodeType, 
			const string *name, string &chkbuf) {
	return CheckIllegalNames(nodeType, name, chkbuf, True);
}

unsigned DiagramChecks::CheckIllegalEdgeNames(int edgeType, 
			const string *name, string &chkbuf) {
	return CheckIllegalNames(edgeType, name, chkbuf, False);
}

unsigned DiagramChecks::CheckIllegalNames(int type, const string *name, 
		string &chkbuf, bool node) {
	unsigned total;
	List<Subject *> s;
	if (node)
		total = graph->GetNodes(&s, name, type);
	else
		total = graph->GetEdges(&s, name, type);
	if (total != 0) {
		chkbuf += "* Error: there ";
		if (total == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += total;
		chkbuf += " ";
		chkbuf += Code::GetName(type);
		if (node)
			chkbuf += " node";
		else
			chkbuf += " edge";
		if (total != 1)
			chkbuf.addPlural();
		if (*name == "")
			chkbuf += " without name";
		else {
			chkbuf += " named '";
			chkbuf += *name;
			chkbuf += "'";
		}
		chkbuf += "\n";
		diagram->SelectSubjects(&s);
	}
	return total;
}


unsigned DiagramChecks::CheckNamelessEdges(int edgeType, 
			int subjectType1, int subjectType2, string &chkbuf) {
	List<Subject *> edges;
	unsigned total=0;
	string empty("");
	graph->GetEdges(&edges, &empty, edgeType);
	for (edges.first(); !edges.done(); edges.next()){
		Edge *edge = (Edge *)edges.cur();
		Subject *subject1 = edge->GetSubject1();
		Subject *subject2 = edge->GetSubject2();
		if (subject1->GetClassType() == subjectType1 &&
		    subject2->GetClassType() == subjectType2) {
			chkbuf += "* Error: there is an unnamed ";
			chkbuf +=  Code::GetName(edgeType);
			chkbuf += " between ";
			chkbuf +=  Code::GetName(subjectType1);
			chkbuf += " '";
			chkbuf += *subject1->GetName();
			chkbuf += "'";
			chkbuf += " and ";
			chkbuf +=  Code::GetName(subjectType2);
			chkbuf += " '";
			chkbuf += *subject2->GetName();
			chkbuf += "'\n";
			total++;
			diagram->SelectSubject(edge);
		}
	}
	return total;
}

unsigned DiagramChecks::CheckDoubleNamelessEdges(
		int edgeType, int subjType1, int subjType2, string &chkbuf) {
	string s("");
	unsigned total = 0;
	List<Subject *> subjs_from;
	List<Subject *> subjs_to;
	List<Subject *> edges;
	graph->GetNodes(&subjs_from, subjType1);
	if (subjs_from.count() == 0)
		graph->GetEdges(&subjs_from, subjType1);
	graph->GetNodes(&subjs_to, subjType2);
	if (subjs_to.count() == 0)
		graph->GetEdges(&subjs_to, subjType2);
	string empty("");
	for (subjs_from.first(); !subjs_from.done(); subjs_from.next()) {
		Subject *subj1 = subjs_from.cur();
		for (subjs_to.first(); !subjs_to.done(); subjs_to.next()) {
			Subject *subj2 = subjs_to.cur();
			graph->GetEdges(&edges, subj1, subj2, &empty, 
					edgeType);
			unsigned count = edges.count();
			if (count > 1) {
				chkbuf += "* Error: there are ";
				chkbuf += count;
				chkbuf += " unnamed ";
				chkbuf += Code::GetName(edgeType);
				chkbuf.addPlural();
				chkbuf += " between ";
				chkbuf +=  Code::GetName(subjType1);
				chkbuf += " '";
				chkbuf += *subj1->GetName();
				chkbuf += "'";
				chkbuf += " and ";
				chkbuf +=  Code::GetName(subjType2);
				chkbuf += " '";
				chkbuf += *subj2->GetName();
				chkbuf += "'\n";
				total++;
				diagram->SelectSubjects(&edges);
			}
			edges.empty();
		}
	}
	return total;
}
 
unsigned DiagramChecks::CheckDoubleNodes(int nodeType, string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<string> strings_got;
	graph->GetNodes(&nodes, nodeType);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *node = nodes.cur();
		string name = *node->GetName();
		if (name != "" && strings_got.find(name) == -1) {
			List<Subject *> s;
			unsigned card = graph->GetNodes(&s, &name, nodeType);
			if (card != 1) {
				chkbuf += "* Error: there are "; 
				chkbuf += card;
				chkbuf += ' ';
				chkbuf += Code::GetName(nodeType);
				chkbuf.addPlural();
				chkbuf += " named '";
				chkbuf += name;
				chkbuf += "'\n";
				total++;
				diagram->SelectSubjects(&s);
			}
			strings_got.add(name);
		}
	}
	return total;
}

unsigned DiagramChecks::CheckConnected(int nodeType, bool index, string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> edges;
	graph->GetNodes(&nodes, nodeType);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *node = nodes.cur();
		graph->CompleteSubject(&edges, node);
		if (edges.count() < 1) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(nodeType);
			chkbuf += " ";
			if (index && !node->IsEdge())
				chkbuf += *((Node *)node)->GetIndex();
			else {
				chkbuf += "'";
				chkbuf += *node->GetName();
				chkbuf += "'";
			}
			chkbuf += " is not connected\n";
			total++;
			diagram->SelectSubject(node);
		}
		edges.empty();
	}
	return total;
}

unsigned DiagramChecks::CheckConnected(int fromType, int toType, int min, int max, 
		bool index, string &chkbuf) {
	unsigned total = 0;
        List<Subject *> subjects;
        List<Subject *> edges;
        List<Subject *> subjects2;
        graph->GetNodes(&subjects, fromType);
        for (subjects.first(); !subjects.done(); subjects.next()) {
                Subject *subject = subjects.cur();
		graph->CompleteSubject(&edges, subject);
		int n = 0;
		for (edges.first(); !edges.done(); edges.next()) {
			Edge *edge = (Edge *)edges.cur();
			Subject *s2;
			if (edge->GetSubject1()==subject)
				s2 = edge->GetSubject2();
			else
				s2 = edge->GetSubject1();
			if (s2->GetClassType()==toType)
				n++;
			subjects2.add(s2);
		}
		if (n<min || n>max) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(fromType);
			chkbuf += " ";
			if (index && !subject->IsEdge()) 
				chkbuf += *((Node *)subject)->GetIndex();
			else {
				chkbuf += "'";
				chkbuf += *subject->GetName();
				chkbuf += "'";
			}
			chkbuf += " is ";
			chkbuf += n;
			chkbuf += " times connected to some ";
			chkbuf += Code::GetName(toType);
			if (n != 1)
				chkbuf.addPlural();
			chkbuf += " (it should be ";
			if (n<min) {
				chkbuf += "at least ";
				chkbuf += min;
			}
			else {
				chkbuf += "at most ";
				chkbuf += max;
			}
			chkbuf += " times)\n";
			diagram->SelectSubject(subject);
			diagram->SelectSubjects(&subjects2);
			total++;
		}
		edges.empty();
		subjects2.empty();
	}
	return total;
}

unsigned DiagramChecks::CheckJunctionCoherence(int nodeType, int parenttype, 
			int childtype, unsigned minChildren, string &chkbuf) {
	unsigned total = 0;
	unsigned unconnected = 0;
	unsigned no_parent = 0;
	unsigned no_child = 0;
	unsigned few_child = 0;
	unsigned double_parent = 0;
	// Check for not properly connected junctions.
	List<Subject *> nodes;
	List<Subject *> edges;
	List<Subject *> errorNodes;
	graph->GetNodes(&nodes, nodeType);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *node = nodes.cur();
		graph->CompleteSubject(&edges, node);
		// count nr. of parent and child edges.
		bool error = False;
		unsigned parent = 0;
		unsigned child = 0;
		for (edges.first(); !edges.done(); edges.next()) {
			Edge *e = (Edge *)edges.cur();
			if (parenttype != childtype) {
				if (e->GetClassType() == parenttype)
					parent += 1;
				else if (e->GetClassType() == childtype)
					child += 1;
			}
			else {
				if (e->GetClassType() == parenttype) {
					if (e->GetSubject1()==node)
						parent++;
					else if (e->GetSubject2()==node)
						child++;
				}
			}
		}
		if (parent == 0 && child == 0) {
			unconnected++;
			error = True;
		}
		else if (parent == 0) {
			no_parent++;
			error = True;
		}
		else if (child == 0) {
			no_child++;
			error = True;
		}
		else if (child < minChildren) {
			few_child++;
			error = True;
		}
		else if (parent > 1) {
			double_parent++;
			error = True;
		}
		if (error) {
			total++;
			errorNodes.add(node);
		}
		edges.empty();
	}
	if (unconnected != 0) {
		chkbuf += "* Error: there ";
		if (unconnected == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += unconnected;
		chkbuf += " unconnected ";
		chkbuf += Code::GetName(nodeType);
		if (unconnected != 1)
			chkbuf.addPlural();
		chkbuf += "\n";
	}
	if (no_child != 0) {
		chkbuf += "* Error: there ";
		if (no_child == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += no_child;
		chkbuf += ' ';
		chkbuf += Code::GetName(nodeType);
		if (no_child != 1)
			chkbuf.addPlural();
		chkbuf += " not connected by some ";
		chkbuf += Code::GetName(childtype);
		chkbuf += "\n";
	}
	if (no_parent != 0) {
		chkbuf += "* Error: there ";
		if (no_parent == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += no_parent;
		chkbuf += ' ';
		chkbuf += Code::GetName(nodeType);
		if (no_parent != 1)
			chkbuf.addPlural();
		chkbuf += " not connected by a single ";
		chkbuf += Code::GetName(parenttype);
		chkbuf += "\n";
	}
	if (few_child != 0) {
		chkbuf += "* Error: there ";
		if (few_child == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += few_child;
		chkbuf += ' ';
		chkbuf += Code::GetName(nodeType);
		if (few_child != 1)
			chkbuf.addPlural();
		chkbuf += " connected by too few ";
		chkbuf += Code::GetName(childtype);
		chkbuf.addPlural();
		chkbuf += "\n";
	}
	if (double_parent != 0) {
		chkbuf += "* Error: there ";
		if (double_parent == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += double_parent;
		chkbuf += ' ';
		chkbuf += Code::GetName(nodeType);
		if (double_parent != 1)
			chkbuf.addPlural();
		chkbuf += " connected by more than one ";
		chkbuf += Code::GetName(parenttype);
		chkbuf += "\n";
	}
	diagram->SelectSubjects(&errorNodes);
	return total;
}

unsigned DiagramChecks::CheckCountEdgesFrom(int nType, int eType, unsigned min, 
		unsigned max, bool zero_allowed, bool index, string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> edges;
	graph->GetNodes(&nodes, nType);
	graph->GetEdges(&edges, eType);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		unsigned n = 0;
		Subject *subject = (Subject *)(nodes.cur());
		for (edges.first(); !edges.done(); edges.next()) {
			Edge *e = (Edge *)edges.cur();
			if (e->GetSubject1() == subject)
				n += 1;
		}
		if ((n > max || n < min) && (!zero_allowed || n > 0)) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(nType);
			chkbuf += " ";
			if (index && !subject->IsEdge()) 
				chkbuf += *((Node *)subject)->GetIndex();
			else {
				chkbuf += "'";
				chkbuf += *subject->GetName();
				chkbuf += "'";
			}
			chkbuf += " has ";
			chkbuf += n;
			chkbuf += " departing ";
			chkbuf += Code::GetName(eType);
			if (n != 1)
				chkbuf.addPlural();
			chkbuf += " (it should be ";
			if (n<min) {
				chkbuf += "at least ";
				chkbuf += min;
			}
			else {
				chkbuf += "at most ";
				chkbuf += max;
			}
			chkbuf += ")\n";
			diagram->SelectSubject(subject);
			total++;
		}
	}
	return total;
}

unsigned DiagramChecks::CheckReachability(
		int rootType, int nodeType, bool index, string &chkbuf) {
	unsigned total = 0;
	unsigned unnamed = 0;
	List<Subject *> roots, nodes;
	graph->GetNodes(&roots, rootType);
	graph->GetNodes(&nodes, nodeType);
	// look for each node if there is a path from one of the
	// roots.
	for (nodes.first(); !nodes.done(); nodes.next()) {
		bool pathFound = False;
		Node *node = (Node *)nodes.cur();
		for (roots.first(); !roots.done(); roots.next()) {
			Node *root = (Node *)roots.cur();
			if (graph->PathExists(root, node))
				pathFound = True; 
		}
		if (!pathFound) {
			// do not report unnamed nodes individually.
			diagram->SelectSubject(node);
			if (!index && *node->GetName() == "") {
				total++;
				unnamed++; 
				continue;
			}
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(nodeType);
			chkbuf += " ";
			if (index)
				chkbuf += *node->GetIndex();
			else {
				chkbuf += "'";
				chkbuf += *node->GetName();
				chkbuf += "'";
			}
			chkbuf += " is not reachable from some ";
			chkbuf += Code::GetName(rootType);
			chkbuf += "\n";
			total++;
		}
	}
	// report about the number of unnamed unreachable nodes found.
	if (unnamed != 0) {
		chkbuf += "* Error: there ";
		if (total == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += total;
		chkbuf += " unnamed ";
		chkbuf += Code::GetName(nodeType);
		if (total != 1)
			chkbuf.addPlural();
		chkbuf += " unreachable from some ";
		chkbuf += Code::GetName(rootType);
		chkbuf += "\n";
	}
	return total;
}

unsigned DiagramChecks::CheckDoubleIndexes(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> nodes2;
	List<string> strings_got;
	graph->GetNodes(&nodes);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Node *node = (Node *)nodes.cur();
		const string *s = node->GetIndex();
		if (*s != "" && strings_got.find(*s) == -1) {
			unsigned card = 0;
			graph->GetNodes(&nodes2);
			List<Subject *> errorNodes;
			for (nodes2.first(); !nodes2.done(); nodes2.next()) {
				Node *n = (Node *) nodes2.cur();
				if (*n->GetIndex() == *s) {
					errorNodes.add(n);
					card++;
				}
			}
			nodes2.empty();
			if (card != 1) {
				total++;
				chkbuf += "* Error: there are ";
				chkbuf += card;
				chkbuf += " nodes having index ";
				chkbuf += *s;
				chkbuf += "\n";
				diagram->SelectSubjects(&errorNodes);
			}
			strings_got.add(*s);
			errorNodes.empty();
		}
	}
	return total;
}
