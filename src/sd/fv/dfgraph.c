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
#include "dfgraph.h"
#include "dataprocess.h"
#include "util.h"
#include <stdlib.h>

DFGraph::DFGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::DATA_PROCESS;
	nodeTypes[i++] = Code::DATA_STORE;
	nodeTypes[i++] = Code::EXTERNAL_ENTITY;
	nodeTypes[i++] = Code::SPLIT_MERGE_NODE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::DATA_FLOW;
	edgeTypes[j++] = Code::BIDIRECTIONAL_DATA_FLOW;
	edgeTypes[j++] = 0;
}

void DFGraph::InitConnections() {
	int DTF=Code::GetIndex(Code::DATA_PROCESS, nodeTypes);	
	int STO=Code::GetIndex(Code::DATA_STORE, nodeTypes);
	int EXT=Code::GetIndex(Code::EXTERNAL_ENTITY, nodeTypes);
	int SMN=Code::GetIndex(Code::SPLIT_MERGE_NODE, nodeTypes);

	int DFL=Code::GetIndex(Code::DATA_FLOW, edgeTypes);
	int BDF=Code::GetIndex(Code::BIDIRECTIONAL_DATA_FLOW, edgeTypes);

	connections[EXT][EXT][DFL] = True;
	connections[EXT][EXT][BDF] = True;

	connections[DTF][DTF][DFL] = True;
	connections[DTF][STO][DFL] = True;
	connections[STO][DTF][DFL] = True;
	connections[DTF][EXT][DFL] = True;
	connections[EXT][DTF][DFL] = True;
	connections[STO][DTF][BDF] = True;
	connections[DTF][STO][BDF] = True;
	connections[DTF][SMN][DFL] = True;
	connections[SMN][DTF][DFL] = True;
	// connections[SMN][SMN][DFL] = True;
}
