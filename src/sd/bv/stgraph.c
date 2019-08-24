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
#include "stgraph.h"
#include "node.h"
#include "edge.h"
#include "util.h"

STGraph::STGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::STATE;
	nodeTypes[i++] = Code::INITIAL_STATE;
	nodeTypes[i++] = Code::DECISION_POINT;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::TRANSITION;
	edgeTypes[j++] = 0;
}

void STGraph::InitConnections () {
	int STA = Code::GetIndex(Code::STATE, nodeTypes);
	int INI = Code::GetIndex(Code::INITIAL_STATE, nodeTypes);
	int DEC = Code::GetIndex(Code::DECISION_POINT, nodeTypes);
	int TRA = Code::GetIndex(Code::TRANSITION, edgeTypes);

	connections[STA][STA][TRA] = True;
	connections[STA][INI][TRA] = True;
	connections[STA][DEC][TRA] = True;
	connections[INI][STA][TRA] = True;
	connections[INI][INI][TRA] = True;
	connections[INI][DEC][TRA] = True;
	connections[DEC][STA][TRA] = True;
	connections[DEC][INI][TRA] = True;
	connections[DEC][DEC][TRA] = True;
}
