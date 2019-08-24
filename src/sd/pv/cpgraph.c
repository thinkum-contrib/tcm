////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "cpgraph.h"
#include "code.h"

CPGraph::CPGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::CPD_COMPONENT_NODE;
	nodeTypes[i++] = Code::CPD_INTERFACE_NODE;
	nodeTypes[i++] = Code::DPD_RESOURCE_NODE;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::CPD_DEPENDENCY_EDGE;
	edgeTypes[j++] = Code::CPD_REALIZATION_EDGE;
	edgeTypes[j++] = Code::DPD_COMMUNICATION_EDGE;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = 0;
}

void CPGraph::InitConnections () {
	int COM = Code::GetIndex(Code::CPD_COMPONENT_NODE, nodeTypes);
	int INT = Code::GetIndex(Code::CPD_INTERFACE_NODE, nodeTypes);
	int RES = Code::GetIndex(Code::DPD_RESOURCE_NODE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);

	int DEP = Code::GetIndex(Code::CPD_DEPENDENCY_EDGE, edgeTypes);
	int REA = Code::GetIndex(Code::CPD_REALIZATION_EDGE, edgeTypes);
	int MUN = Code::GetIndex(Code::DPD_COMMUNICATION_EDGE, edgeTypes);
	int CML = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);

	connections[COM][INT][REA] = True;
	connections[INT][COM][REA] = True;

	connections[RES][RES][MUN] = True;

	connections[COM][COM][DEP] = True;
	connections[RES][RES][DEP] = True;
	connections[INT][INT][DEP] = True;
	connections[RES][COM][DEP] = True;
	connections[COM][RES][DEP] = True;
	connections[RES][INT][DEP] = True;
	connections[COM][INT][DEP] = True;
	connections[INT][RES][DEP] = True;
	connections[INT][COM][DEP] = True;

	connections[COM][NOT][CML] = True;
	connections[NOT][COM][CML] = True;
	connections[RES][NOT][CML] = True;
	connections[NOT][RES][CML] = True;
	connections[INT][NOT][CML] = True;
	connections[NOT][INT][CML] = True;
}
