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
#include "trgraph.h"
#include "code.h"
#include "util.h"

TRGraph::TRGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::TEXT_ROOT;
	nodeTypes[i++] = Code::TEXT_NODE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::TEXT_EDGE;
	edgeTypes[j++] = 0;
}

void TRGraph::InitConnections () {
	int ROOT = Code::GetIndex(Code::TEXT_ROOT, nodeTypes);
	int NODE = Code::GetIndex(Code::TEXT_NODE, nodeTypes);
	int EDGE = Code::GetIndex(Code::TEXT_EDGE, edgeTypes);

	connections[ROOT][NODE][EDGE] = True;
	connections[NODE][ROOT][EDGE] = True;
	connections[NODE][NODE][EDGE] = True;
}
