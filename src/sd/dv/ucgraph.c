//------------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "ucgraph.h"
#include "code.h"
 
UCGraph::UCGraph(): ERGraph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::UCD_ACTOR_NODE;
	nodeTypes[i++] = Code::UCD_USE_CASE_NODE;
	nodeTypes[i++] = Code::UCD_SYSTEM_NODE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::UCD_BINARY_ASSOCIATION_EDGE;
	edgeTypes[j++] = Code::UCD_GENERALIZATION_EDGE;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = 0;
}

void UCGraph::InitConnections() {
	int ACT = Code::GetIndex(Code::UCD_ACTOR_NODE, nodeTypes);
	int USE = Code::GetIndex(Code::UCD_USE_CASE_NODE, nodeTypes);
	int SYS = Code::GetIndex(Code::UCD_SYSTEM_NODE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);

	int BIN = Code::GetIndex(Code::UCD_BINARY_ASSOCIATION_EDGE, edgeTypes);
	int ISA = Code::GetIndex(Code::UCD_GENERALIZATION_EDGE, edgeTypes);
	int NBL = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);
 
	connections[ACT][USE][BIN] = True;
	connections[USE][ACT][BIN] = True;
	connections[ACT][ACT][ISA] = True;
	connections[USE][USE][ISA] = True;

	connections[ACT][NOT][NBL] = True;
	connections[NOT][ACT][NBL] = True;

	connections[USE][NOT][NBL] = True;
	connections[NOT][USE][NBL] = True;

	connections[SYS][NOT][NBL] = True;
	connections[NOT][SYS][NBL] = True;
}
