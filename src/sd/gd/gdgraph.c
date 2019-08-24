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
#include "gdgraph.h"
#include "code.h"

GDGraph::GDGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::GENERIC_NODE;
	nodeTypes[i++] = Code::EMPTY_NODE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::GENERIC_EDGE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::GENERIC_EDGE;
	edgeTypes[j++] = 0;
}

void GDGraph::InitConnections () {
	int NOD = Code::GetIndex(Code::GENERIC_NODE, nodeTypes);
	int EMP = Code::GetIndex(Code::EMPTY_NODE, nodeTypes);
	int COM = Code::GetIndex(Code::COMMENT, nodeTypes);
	int EDN = Code::GetIndex(Code::GENERIC_EDGE, nodeTypes);
	int EDE = Code::GetIndex(Code::GENERIC_EDGE, edgeTypes);

	connections[NOD][NOD][EDE] = True;
	connections[NOD][EMP][EDE] = True;
	connections[NOD][COM][EDE] = True;
	connections[COM][COM][EDE] = True;
	connections[COM][NOD][EDE] = True;
	connections[COM][EMP][EDE] = True;
	connections[EMP][EMP][EDE] = True;
	connections[EMP][NOD][EDE] = True;
	connections[EMP][COM][EDE] = True;

	connections[EDN][NOD][EDE] = True;
	connections[NOD][EDN][EDE] = True;
	connections[EDN][COM][EDE] = True;
	connections[COM][EDN][EDE] = True;
	connections[EDN][EMP][EDE] = True;
	connections[EMP][EDN][EDE] = True;
	connections[EDN][EDN][EDE] = True;
}
