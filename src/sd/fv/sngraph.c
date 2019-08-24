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
#include "sngraph.h"
#include "code.h"

SNGraph::SNGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::SN_PROCESS;
	nodeTypes[i++] = Code::DATA_STREAM;
	nodeTypes[i++] = Code::STATE_VECTOR;
	nodeTypes[i++] = Code::CONTROLLED_DATA_STREAM;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::CONNECTION_START;
	edgeTypes[j++] = Code::CONNECTION_END;
	edgeTypes[j++] = 0;
}
 
void SNGraph::InitConnections() {
	int PRO = Code::GetIndex(Code::SN_PROCESS, nodeTypes);
	int DAT = Code::GetIndex(Code::DATA_STREAM, nodeTypes);
	int VEC = Code::GetIndex(Code::STATE_VECTOR, nodeTypes);
	int CON = Code::GetIndex(Code::CONTROLLED_DATA_STREAM, nodeTypes);
	
	int STA = Code::GetIndex(Code::CONNECTION_START, edgeTypes);
	int END = Code::GetIndex(Code::CONNECTION_END, edgeTypes);

	connections[PRO][DAT][STA] = True;
	connections[PRO][VEC][STA] = True;
	connections[PRO][CON][STA] = True;

	connections[DAT][PRO][END] = True;
	connections[VEC][PRO][END] = True;
	connections[CON][PRO][END] = True;
	connections[PRO][DAT][END] = True;
}
