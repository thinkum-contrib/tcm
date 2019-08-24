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
#include "dcfgraph.h"
#include "code.h"

DCFGraph::DCFGraph(): DFGraph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::DATA_PROCESS;
	nodeTypes[i++] = Code::CONTROL_PROCESS;
	nodeTypes[i++] = Code::DATA_STORE;
	nodeTypes[i++] = Code::EVENT_STORE;
	nodeTypes[i++] = Code::EXTERNAL_ENTITY;
	nodeTypes[i++] = Code::SPLIT_MERGE_NODE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::DATA_FLOW;
	edgeTypes[j++] = Code::BIDIRECTIONAL_DATA_FLOW;
	edgeTypes[j++] = Code::CONTINUOUS_DATA_FLOW;
	edgeTypes[j++] = Code::EVENT_FLOW;
	edgeTypes[j++] = Code::CONTINUOUS_EVENT_FLOW;
	edgeTypes[j++] = 0;
}

void DCFGraph::InitConnections() {
	int DP=Code::GetIndex(Code::DATA_PROCESS, nodeTypes);	
	int DS=Code::GetIndex(Code::DATA_STORE, nodeTypes);
	int EE=Code::GetIndex(Code::EXTERNAL_ENTITY, nodeTypes);
	int SN=Code::GetIndex(Code::SPLIT_MERGE_NODE, nodeTypes);
	int CP=Code::GetIndex(Code::CONTROL_PROCESS, nodeTypes);
	int ES=Code::GetIndex(Code::EVENT_STORE, nodeTypes);

	int DD=Code::GetIndex(Code::DATA_FLOW, edgeTypes);
	int BD=Code::GetIndex(Code::BIDIRECTIONAL_DATA_FLOW, edgeTypes);
	int CD=Code::GetIndex(Code::CONTINUOUS_DATA_FLOW, edgeTypes);
	int DE=Code::GetIndex(Code::EVENT_FLOW, edgeTypes);
	int CE=Code::GetIndex(Code::CONTINUOUS_EVENT_FLOW, edgeTypes);

	connections[EE][EE][DD] = True;
	connections[EE][EE][BD] = True;
	connections[EE][EE][CD] = True;

	connections[EE][DP][DD] = True;
	connections[EE][DP][DE] = True;
	connections[EE][DP][CD] = True;
	connections[EE][DP][CE] = True;

	connections[EE][CP][DE] = True;
	connections[EE][CP][CE] = True;

	connections[DP][EE][DD] = True;
	connections[DP][EE][DE] = True;
	connections[DP][EE][CD] = True;
	connections[DP][EE][CE] = True;

	connections[DP][DP][DD] = True;
	connections[DP][DP][DE] = True;
	connections[DP][DP][CD] = True;
	connections[DP][DP][CE] = True;

	connections[DP][CP][DE] = True;
	connections[DP][CP][CE] = True;

	connections[DP][DS][DD] = True;
	connections[DP][DS][BD] = True;
	connections[DP][DS][CD] = True;

	connections[DP][SN][DD] = True;
	connections[DP][SN][CD] = True;

	connections[CP][EE][DE] = True;
	connections[CP][EE][CE] = True;

	connections[CP][DP][DE] = True;

	connections[CP][CP][DE] = True;
	connections[CP][CP][CE] = True;

	connections[CP][ES][DE] = True;
	connections[CP][ES][CE] = True;

	connections[DS][DP][DD] = True;
	connections[DS][DP][CD] = True;
	connections[DS][DP][BD] = True;

	connections[ES][CP][DE] = True;
	connections[ES][CP][CE] = True;

	connections[SN][DP][DD] = True;
	connections[SN][DP][CD] = True;
}
