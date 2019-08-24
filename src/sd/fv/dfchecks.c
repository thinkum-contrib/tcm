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
#include "dfchecks.h"
#include "graph.h"
#include "dataprocess.h"
#include "edge.h"
#include "util.h"
#include "diagram.h"

DFChecks::DFChecks(Diagram *d, Graph *g): DiagramChecks(d, g) { }

void DFChecks::WriteCheckProcess(DFProcess *d, string &chkbuf) {
	chkbuf += "* Error: ";
	chkbuf += Code::GetName(d->GetClassType());
	chkbuf += " ";
	chkbuf += *d->GetIndex();
}

unsigned DFChecks::CheckDataProcessCoherence(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::DATA_PROCESS);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *s = nodes.cur();
		unsigned ins = GetGraph()->CountEdgesTo(s);
		unsigned outs = GetGraph()->CountEdgesFrom(s);
		if (ins < 1 || outs < 1) {
			WriteCheckProcess((DFProcess *)s, chkbuf);
			if (ins < 1)
				chkbuf += " misses an input flow";
			if (outs < 1) {
				if (ins < 1)
					chkbuf += " and";
				chkbuf += " misses an output flow";
			}
			chkbuf += "\n";
			GetDiagram()->SelectSubject(s);
			total += 1;
		}
	}
	return total;
}

unsigned DFChecks::CheckSplitMergeNodeCoherence(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	unsigned unconnected = 0;
	unsigned no_input = 0;
	unsigned no_output = 0;
	unsigned no_split_or_merge = 0;
	unsigned split_and_merge = 0;
	GetGraph()->GetNodes(&nodes, Code::SPLIT_MERGE_NODE);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		bool error = False;
		Subject *s = nodes.cur();
		unsigned ins = GetGraph()->CountEdgesTo(s);
		unsigned outs = GetGraph()->CountEdgesFrom(s);
		if (ins == 0 && outs == 0) {
			error = True;
			unconnected++;
		}
		else if (ins == 0) {
			error = True;
			no_input++;
		}
		else if (outs == 0) {
			error = True;
			no_output++;
		}
		else if (ins == 1 && outs == 1) {
			error = True;
			no_split_or_merge++;
		}
		else if (ins > 1 && outs > 1) {
			error = True;
			split_and_merge++;
		}
		if (error) {
			total++;
			GetDiagram()->SelectSubject(s);
		}
	}
	if (unconnected != 0) {
		chkbuf += "* Error: there ";
		if (unconnected == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += unconnected;
		chkbuf += " unconnected ";
		chkbuf += Code::GetName(Code::SPLIT_MERGE_NODE);
		if (unconnected != 1)
			chkbuf.addPlural();
		chkbuf += "\n";
	}
	if (no_input != 0) {
		chkbuf += "* Error: there ";
		if (no_input == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += no_input;
		chkbuf += ' ';
		chkbuf += Code::GetName(Code::SPLIT_MERGE_NODE);
		if (no_input != 1)
			chkbuf.addPlural();
		chkbuf += " without an input flow\n";
	}
	if (no_output != 0) {
		chkbuf += "* Error: there ";
		if (no_output == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += no_output;
		chkbuf += ' ';
		chkbuf += Code::GetName(Code::SPLIT_MERGE_NODE);
		if (no_output != 1)
			chkbuf.addPlural();
		chkbuf += " without an output flow\n";
	}
	if (no_split_or_merge != 0) {
		chkbuf += "* Error: there ";
		if (no_split_or_merge == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += no_split_or_merge;
		chkbuf += ' ';
		chkbuf += Code::GetName(Code::SPLIT_MERGE_NODE);
		if (no_split_or_merge != 1)
			chkbuf.addPlural();
		chkbuf += " which is not splitting or merging\n";
	}
	if (split_and_merge != 0) {
		chkbuf += "* Error: there ";
		if (split_and_merge == 1) chkbuf += "is "; else chkbuf += "are ";
		chkbuf += split_and_merge;
		chkbuf += ' ';
		chkbuf += Code::GetName(Code::SPLIT_MERGE_NODE);
		if (split_and_merge != 1)
			chkbuf.addPlural();
		chkbuf += " which is both splitting and merging\n";
	}
	return total;
}

unsigned DFChecks::CheckNamelessSplitMergeEdges(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	List<Subject *> edgesIn;
	List<Subject *> edgesOut;
	GetGraph()->GetNodes(&nodes, Code::SPLIT_MERGE_NODE);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *s = nodes.cur();
		GetGraph()->GetEdgesTo(&edgesIn, s);
		GetGraph()->GetEdgesFrom(&edgesOut, s);
		unsigned ins = edgesIn.count();
		unsigned outs = edgesOut.count();
		if (ins == 1 && outs >= 2) {
			// split: input flow has to be named.
			Edge *edge = (Edge *)(edgesIn[0]);
			if (*edge->GetName() == "") {
				Subject *subj1 = edge->GetSubject1();
				chkbuf += "* Error: there is an unnamed "; 
				chkbuf += "splitting DataFlow from ";
				if (check(subj1->GetClassType() == 
					  Code::DATA_PROCESS)) {
					chkbuf += "DataProcess ";
					chkbuf += *((DFProcess *)subj1)->
							GetIndex();
				}
				chkbuf += "\n";
				GetDiagram()->SelectSubject(edge);
				total++;
			}
		}
		else if (ins >= 2 && outs == 1) {
			// merge: output flow has to be named
			Edge *edge = (Edge *)(edgesOut[0]);
			if (*edge->GetName() == "") {
				Subject *subj2 = edge->GetSubject2();
				chkbuf += "* Error: there is an unnamed ";
				chkbuf += "merging DataFlow to ";
				if (check(subj2->GetClassType() == 
						Code::DATA_PROCESS)) {
					chkbuf += "DataProcess ";
					chkbuf += *((DFProcess *)subj2)->
							GetIndex();
				}
				chkbuf += "\n";
				GetDiagram()->SelectSubject(edge);
				total++;
			}
		}
		edgesIn.empty();
		edgesOut.empty();
	} 
	return total;
}

unsigned DFChecks::CheckMinispecs(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::DATA_PROCESS);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		DataProcess *d = (DataProcess *)(nodes.cur());
		if (d->IsProcessGroup())
			continue;
		if (*d->GetMinispec() == "") {
			chkbuf += "* Warning: DataProcess ";
			chkbuf += *d->GetIndex();
			chkbuf += " has no minispec "
				  "(and is not a process group)\n";
			GetDiagram()->SelectSubject(d);
			total++;
		}
	}
	return total;
}

 
unsigned DFChecks::CheckNamelessFlows(
		int edgetype, int subjtype1, int subjtype2, string &chkbuf) {
	List<Subject *> edges;
	unsigned total=0;
	string empty("");
	GetGraph()->GetEdges(&edges, &empty, edgetype);
	for (edges.first(); !edges.done(); edges.next()){
		Edge *edge = (Edge *)edges.cur();
		Subject *subj1 = edge->GetSubject1();
		Subject *subj2 = edge->GetSubject2();
		if (subj1->GetClassType() == subjtype1 &&
		    subj2->GetClassType() == subjtype2 &&
		    *subj1->GetName() != "" &&
		    *subj2->GetName() != "") {
			chkbuf += "* Error: there is an unnamed ";
			chkbuf +=  Code::GetName(edgetype);
			chkbuf += " between ";
			chkbuf +=  Code::GetName(subjtype1);
			if (subjtype1 == Code::DATA_PROCESS ||
			    subjtype1 == Code::CONTROL_PROCESS) {
				chkbuf += " ";
				chkbuf += *((DFProcess *)subj1)->GetIndex();
			}
			else {
				chkbuf += " '";
				chkbuf += *subj1->GetName();
				chkbuf += "'";
			}
			chkbuf += " and ";
			chkbuf += Code::GetName(subjtype2);
			if (subjtype2 == Code::DATA_PROCESS ||
			    subjtype2 == Code::CONTROL_PROCESS) {
				chkbuf += " ";
				chkbuf += *((DFProcess *)subj2)->GetIndex();
			}
			else {
				chkbuf += " '";
				chkbuf += *subj2->GetName();
				chkbuf += "'";
			}
			chkbuf += "\n";
			GetDiagram()->SelectSubject(edge);
			total++;
		}
	}
	return total;
}
