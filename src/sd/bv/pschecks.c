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
#include "pschecks.h"
#include "graph.h"
#include "edge.h"
#include "gshape.h"
#include "psprocess.h"
#include "diagramviewer.h"
#include "diagram.h"

PSChecks::PSChecks(Diagram *d, Graph *g): DiagramChecks(d, g) { }

unsigned PSChecks::CheckRootOperator(PSProcess *p, string &chkbuf) {
	unsigned errors = 0;
	chkbuf +="* Remark: process '";
	chkbuf += *p->GetName();
	chkbuf += "' is considered as the root\n";
	char c;
	if ((c = p->GetOperator()) != ' ') {
		chkbuf +="* Error: root process '";
		chkbuf += *p->GetName();
		chkbuf += "' has the illegal operator '";
		chkbuf.add(c);
		chkbuf += "'\n";
		GetDiagram()->SelectSubject(p);
		errors++;
	}
	return errors;
}

unsigned PSChecks::CheckChildPositions(DiagramViewer *dviewer,
		PSProcess *parent, List<Subject *> *children, string &chkbuf){
	unsigned errors = 0;
	Shape *pshape = dviewer->GetShape(parent);
	Point ppos = *pshape->GetPosition();
	for (children->first(); !children->done(); children->next()) {
		Subject *child = children->cur();
		Shape *cshape = dviewer->GetShape(child);
		Point cpos = *cshape->GetPosition();
		// child is not lower than the parent.
		if (cpos.y <= ppos.y) {
			chkbuf +="* Warning: the process '";
			chkbuf += *parent->GetName();
			chkbuf += "' should better be positioned ";
			chkbuf += "above its child process '";
			chkbuf += *child->GetName();
			chkbuf += "'\n";
			GetDiagram()->SelectSubject(parent);
			GetDiagram()->SelectSubject(child);
			errors++;
			break;
		}
	}
	return errors;
}

unsigned PSChecks::CheckChildOperators(PSProcess *parent, 
		List<Subject *> *children, string &chkbuf){
	unsigned errors = 0;
	// There are no children.
	if (!children->first())
		return 0;
	else if (*parent->GetName() %= "QUIT") {
		chkbuf +="* Error: a '";
		chkbuf += *parent->GetName();
		chkbuf += "' process should not have children\n";
		GetDiagram()->SelectSubject(parent);
		errors++;
		return errors;
	}
	PSProcess *child = (PSProcess *)children->cur();
	char basis_c = child->GetOperator();
	if (basis_c == ' ') { // all remaining children should be a 'sequence'.
		while (children->next()) {
			child = (PSProcess *)children->cur();
			char c = child->GetOperator();
			if (c != basis_c) {
				if (c == '*') {
					chkbuf +="* Error: process '";
					chkbuf += *parent->GetName();
					chkbuf += "' has a non-single '*'"; 
					chkbuf += "(iteration) child\n";
				}
				else {
					chkbuf +="* Error: some children of process '";
					chkbuf += *parent->GetName();
					chkbuf +="' have different operators '";
					chkbuf.add(basis_c);
					chkbuf += "' and '";
					chkbuf.add(c);
					chkbuf += "'\n";
				}
				errors++;
				break;
			}
		}
	}
	else if (basis_c == '*') { // there should be no other children.
		if (children->next()) {
			chkbuf +="* Error: process '";
			chkbuf += *parent->GetName();
			chkbuf += "' has a non-single '*'"; 
			chkbuf += " (iteration) child\n";
			errors++;
		}
	}
	else if (basis_c == 'o') { // >= 1 remaining children. All children should be choices.
		if (!children->next()) {
			chkbuf +="* Error: process '";
			chkbuf += *parent->GetName();
			chkbuf += "' has a single 'o' (choice) child\n";
			errors++;
		}
		else {
			for (children->first(); !children->done(); children->next()) {
				child = (PSProcess *)children->cur();
				char c = child->GetOperator();
				if (c != basis_c) {
					if (c == '*') {
						chkbuf +="* Error: process '";
						chkbuf += *parent->GetName();
						chkbuf += "' has a non-single ";
						chkbuf += "'*' (iteration) child";
					}
					else {
						chkbuf +="* Error: the ";
						chkbuf += "children of process '";
						chkbuf += *parent->GetName();
						chkbuf += "' have different operators '";
						chkbuf.add(basis_c);
						chkbuf += "' and '";
						chkbuf.add(c);
						chkbuf += "'\n";
					}
					errors++;
					break;
				}
			}
		}
	}
	else if (basis_c == '?') { // the name is 'POSIT'. The other child is named 'ADMIT'.
		if (! parent->IsRoot()) {
			chkbuf +="* Error: non-root process '";
			chkbuf += *parent->GetName();
			chkbuf += "' should not have children with a '?'\n";
			errors++;
		}

		string s = *(child->GetName());
		if (! (s %= "POSIT")) {
			chkbuf +="* Error: the first child of process '";
			chkbuf += *parent->GetName();
			chkbuf +="' is expected to have as name 'POSIT'\n";
			errors++;
		}
		else if (!children->next() || 
			 !(*children->cur()->GetName() %= "ADMIT") || 
			(((PSProcess *)(children->cur()))->GetOperator() != '?')) {
			chkbuf +="* Error: process '";
			chkbuf += *parent->GetName();
			chkbuf += "' is expected to have a second "; 
			chkbuf += "child named 'ADMIT' with a '?'\n";
			errors++;
		}
		else if (children->next()) {
			chkbuf +="* Error: process '";
			chkbuf += *parent->GetName();
			chkbuf +="' is expected to have exactly two children\n"; 
			errors++;
		}
	}
	else if (basis_c == '!') { // the name is [qQ][Uu][Ii][Tt]
		string s = *(child->GetName());
		if (! (s %= "QUIT")) {
			chkbuf +="* Error: the child of process '";
			chkbuf += *parent->GetName();
			chkbuf += "' is expected to have name 'QUIT'\n";
			errors++;
		}
		else if (children->next()) {
			chkbuf +="* Error: process '";
			chkbuf += *parent->GetName();
			chkbuf += "' is expected to have a ";
			chkbuf += "single child\n"; 
			errors++;
		}
	}
	else {
		chkbuf +="* Error: process '";
		chkbuf += *parent->GetName();
		chkbuf += "' has the illegal operator '";
		chkbuf.add(basis_c);
		chkbuf += "'\n";
		errors++;
	}
	if (errors > 0) {
		GetDiagram()->SelectSubject(parent);
		GetDiagram()->SelectSubjects(children);
	}
	return errors;
}

unsigned PSChecks::CheckDoubleProcessNames(string &chkbuf) {
	unsigned total = 0;
	int nodetype = Code::PS_PROCESS;
	List<Subject *> nodes;
	List<Subject *> doublenodes;
	List<string> strings_got;
	GetGraph()->GetNodes(&nodes, nodetype);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		PSProcess *proc = (PSProcess *) nodes.cur();
		const string *s = proc->GetName();
		if (*s != "" && strings_got.find(*s) == -1) {
			doublenodes.empty();
			GetGraph()->GetNodes(&doublenodes, s, nodetype);
			if (doublenodes.count() > 1) {
				for (doublenodes.first(); !doublenodes.done(); 
				     doublenodes.next()) {
					PSProcess *p = (PSProcess *)doublenodes.cur();
					// all double names processes should 
					// be leaves (actions).
					if (!p->IsAction()) {
						chkbuf += "* Error: "; 
						chkbuf += doublenodes.count();
						chkbuf += " processes";
						chkbuf += " are named '";
						chkbuf += *s;
						chkbuf += "' but they are not all actions\n";
						GetDiagram()->SelectSubjects(&doublenodes);
						total++;
						break;
					}
				}
			}
			strings_got.add(*s);
		}
	}
	return total;
}
