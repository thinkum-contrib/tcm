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
#include "dcfchecks.h"
#include "graph.h"
#include "controlprocess.h"
#include "dataprocess.h"
#include "edge.h"
#include "diagram.h"
#include "util.h"

DCFChecks::DCFChecks(Diagram *d, Graph *g): DFChecks(d, g) { }

unsigned DCFChecks::CheckControlProcessCoherence(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::CONTROL_PROCESS);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		Subject *s = nodes.cur();
		unsigned outs = GetGraph()->CountEdgesFrom(s);
		if (outs < 1) {
			WriteCheckProcess((ControlProcess *)s, chkbuf);
			if (outs < 1)
				chkbuf += " misses an output EventFlow";
			chkbuf += "\n";
			GetDiagram()->SelectSubject(s);
			total += 1;
		}
	}
	return total;
}

unsigned DCFChecks::CheckContinuousSplitMergeEdges(string &chkbuf) {
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
			Edge *edgeIn = (Edge *)edgesIn[0];
			int EdgeType = edgeIn->GetClassType();
			Subject *subj1 = edgeIn->GetSubject1();
			for (edgesOut.first(); !edgesOut.done(); 
					edgesOut.next()) {
				Edge *edge = (Edge *)(edgesOut.cur());
				if (edge->GetClassType() != EdgeType) {
					chkbuf += "* Error: there is a half ";
					chkbuf += "discrete, half continuous "
						  "splitting flow from"; 
					if (check(subj1->GetClassType() == 
							Code::DATA_PROCESS)) {
						chkbuf += " DataProcess ";
						chkbuf += *((DFProcess *)
							subj1)->GetIndex();
					}
					chkbuf += "\n";
					GetDiagram()->SelectSubject(edgeIn);
					GetDiagram()->SelectSubjects(&edgesOut);
					total++;
					break;
				}
			}
		}
		else if (ins >= 2 && outs == 1) {
			Edge *edgeOut = (Edge *)edgesOut[0];
			int EdgeType = edgeOut->GetClassType();
			Subject *subj2 = edgeOut->GetSubject2();
			for (edgesIn.first(); !edgesIn.done(); edgesIn.next()) {
				Edge *edge = (Edge *)(edgesIn.cur());
				if (edge->GetClassType() != EdgeType) {
					chkbuf += "* Error: there is a half "; 
					chkbuf += "discrete, half continuous "
						  "splitting flow to"; 
					if (check(subj2->GetClassType() == 
						  Code::DATA_PROCESS)) {
						chkbuf += " DataProcess ";
						chkbuf += *((DFProcess *)
							subj2)->GetIndex();
					}
					chkbuf += "\n";
					GetDiagram()->SelectSubjects(&edgesIn);
					GetDiagram()->SelectSubject(edgeOut);
					total++;
					break;
				}
			}
		}
		edgesIn.empty();
		edgesOut.empty();
	}
	return total;
}

unsigned DCFChecks::CheckPersistences(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::DATA_PROCESS);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		DataProcess *d = (DataProcess *)(nodes.cur());
		if (d->IsProcessGroup() || !d->IsInstantaneous())
			continue;
		List<Subject *> edges;
		int c = GetGraph()->CountEdgesFrom(d,Code::CONTINUOUS_DATA_FLOW)+
			GetGraph()->CountEdgesFrom(d,Code::CONTINUOUS_EVENT_FLOW);
		if (c > 0) {
			WriteCheckProcess(d, chkbuf);
			chkbuf += " is discrete so it cannot output a "
				  "continuous flow\n";
			GetDiagram()->SelectSubject(d);
			total++;
		}
	}
	return total;
}

unsigned DCFChecks::CheckActivationMechanisms(string &chkbuf) {
	unsigned total = 0;
	List<Subject *> nodes;
	GetGraph()->GetNodes(&nodes, Code::DATA_PROCESS);
	for (nodes.first(); !nodes.done(); nodes.next()) {
		DataProcess *d = (DataProcess *)(nodes.cur());
		if (d->IsProcessGroup() || !d->IsInstantaneous())
			continue;
		DataProcess::ActivationType a = d->GetActivationMechanism();
		if (a == DataProcess::TRIGGER) {
			List<Subject *> edges;
			string s("T");
			GetGraph()->GetEdgesTo(&edges, d, &s, 
						  Code::EVENT_FLOW);
			if (edges.count() != 1) {
				WriteCheckProcess(d, chkbuf);
				chkbuf += " has as activation mechanism "
					  "'trigger' and should therefore have"
					  " exactly one incoming trigger "
					  "event flow\n";
				GetDiagram()->SelectSubject(d);
				total++;	
			}
		}
		else if (a == DataProcess::TIME) {
			if (*d->GetTimeExpression() == "") {
				WriteCheckProcess(d, chkbuf);
				chkbuf += " has as activation mechanism "
					  "'time' but no"
					  " time expression specified\n";
				GetDiagram()->SelectSubject(d);
				total++;
			}
		}
		else if (a == DataProcess::UNSPECIFIED) {
			chkbuf += "* Warning: DataProcess ";
			chkbuf += *d->GetIndex();
			chkbuf += " has no activation mechanism specified\n";
			GetDiagram()->SelectSubject(d);
			total++;
		}
		else if (a == DataProcess::STIMULUS) {
			const string *stimulus = d->GetStimulus();
			if (*stimulus == "") {
				WriteCheckProcess(d, chkbuf);
				chkbuf += " has as activation mechanism" 
					  " 'stimulus' but no"
					  " stimulus edge name specified\n";
				GetDiagram()->SelectSubject(d);
				total++;
			}
			else {
				List<Subject *> edges;
				GetGraph()->GetEdgesTo(&edges, d, stimulus, 
							  Code::EVENT_FLOW);
				GetGraph()->GetEdgesTo(&edges, d, stimulus, 
							  Code::DATA_FLOW);
				if (edges.count() != 1) {
					WriteCheckProcess(d, chkbuf);
					chkbuf += " has as activation "
						  "mechanism a stimulus named ";
					chkbuf += *stimulus;
					chkbuf += " and should therefore have "
						  "exactly one incoming "
						  "discrete flow with "
						  "that name\n";
					GetDiagram()->SelectSubject(d);
					total++;
				}
			}
		}
	}
	return total;
}
