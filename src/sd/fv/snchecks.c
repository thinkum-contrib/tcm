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
#include "snchecks.h"
#include "graph.h"
#include "node.h"
#include "edge.h"
#include "diagram.h"

SNChecks::SNChecks(Diagram *d, Graph *g): DiagramChecks(d, g) { }

unsigned SNChecks::CheckConnectionCoherence(int ntype, string &chkbuf) {
	// ignore unconnected.
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> edges;
	GetGraph()->GetNodes(&nodes, ntype);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		unsigned ins = 0;
		unsigned outs = 0;
		Node *node = (Node *)(nodes.cur());
		GetGraph()->CompleteSubject(&edges, node);
		for (edges.first(); !edges.done(); edges.next()) {
			Edge *edge = (Edge *)edges.cur();
			int edgeType = edge->GetClassType();
			if (edgeType == Code::CONNECTION_START)
				ins++;
			else if (edgeType == Code::CONNECTION_END)
				outs++;
		}
		if (ins == 0 && outs == 0)
			;
		else if (ins == 0 || outs == 0) {
			chkbuf += "* Error: ";
			chkbuf += Code::GetName(ntype);
			chkbuf += " '";
			chkbuf += *node->GetName();
			chkbuf += "'";
			if (ins == 0)
				chkbuf += " misses a ConnectionStart edge";
			if (outs == 0)
				chkbuf += " misses a ConnectionEnd edge";
			chkbuf += "\n";
			GetDiagram()->SelectSubject(node);
			total += 1;
		}
		edges.empty();
		ins = outs = 0;
	}
	return total;
}
