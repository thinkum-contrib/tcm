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
#include "crgraph.h"
#include "code.h"
 
CRGraph::CRGraph(): ERGraph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::CLASS_NODE;
	nodeTypes[i++] = Code::TAXONOMY_JUNCTION;
	nodeTypes[i++] = Code::MODE_JUNCTION;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::BINARY_RELATIONSHIP;
	edgeTypes[j++] = Code::FUNCTION;
	edgeTypes[j++] = Code::COMPONENT_FUNCTION;
	edgeTypes[j++] = Code::EMPTY_EDGE;
	edgeTypes[j++] = Code::ISA_RELATIONSHIP;
	edgeTypes[j++] = 0;
}

void CRGraph::InitConnections() {
	int OBJ = Code::GetIndex(Code::CLASS_NODE, nodeTypes);
	int TAX = Code::GetIndex(Code::TAXONOMY_JUNCTION, nodeTypes);
	int MOD = Code::GetIndex(Code::MODE_JUNCTION, nodeTypes);

	int FUN = Code::GetIndex(Code::FUNCTION, edgeTypes);
	int MAN = Code::GetIndex(Code::BINARY_RELATIONSHIP, edgeTypes);
	int EMP = Code::GetIndex(Code::EMPTY_EDGE, edgeTypes);
	int ISA = Code::GetIndex(Code::ISA_RELATIONSHIP, edgeTypes);
	int COM = Code::GetIndex(Code::COMPONENT_FUNCTION, edgeTypes);
 
	connections[OBJ][OBJ][FUN] = True;
	connections[OBJ][OBJ][MAN] = True;
	connections[OBJ][OBJ][ISA] = True;
	connections[OBJ][OBJ][COM] = True;

	connections[MOD][OBJ][ISA] = True;
	connections[MOD][OBJ][EMP] = True;
	connections[OBJ][MOD][EMP] = True;

	connections[TAX][OBJ][ISA] = True;
	connections[TAX][OBJ][EMP] = True;
	connections[OBJ][TAX][EMP] = True;
}
