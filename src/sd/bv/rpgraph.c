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
#include "rpgraph.h"
#include "processgraphroot.h"
#include "util.h"

RPGraph::RPGraph(): Graph() {
	int i=0;	
	int j=0;
	nodeTypes[i++] = Code::PROCESS_GRAPH_ROOT;
	nodeTypes[i++] = Code::PROCESS_GRAPH_NODE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::EVENT;
	edgeTypes[j++] = 0;
}

void RPGraph::InitConnections () {
	int RPS = Code::GetIndex(Code::PROCESS_GRAPH_ROOT, nodeTypes);
	int RPR = Code::GetIndex(Code::PROCESS_GRAPH_NODE, nodeTypes);
	int EVT = Code::GetIndex(Code::EVENT, edgeTypes);

	connections[RPS][RPS][EVT] = True;
	connections[RPS][RPR][EVT] = True;
	connections[RPR][RPS][EVT] = True;
	connections[RPR][RPR][EVT] = True;
}
