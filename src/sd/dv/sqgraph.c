//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
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
#include "sqgraph.h"
#include "code.h"
 
SQGraph::SQGraph(): ERGraph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::UCD_ACTOR_NODE;
	nodeTypes[i++] = Code::SSD_CLASS_NODE;
	nodeTypes[i++] = Code::SSD_OBJECT_NODE;
	nodeTypes[i++] = Code::CBD_OBJECT_NODE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::CBD_OBJECT_LINK_EDGE;
	edgeTypes[j++] = Code::BINARY_RELATIONSHIP;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = 0;
}

void SQGraph::InitConnections() {
	int ACT = Code::GetIndex(Code::UCD_ACTOR_NODE, nodeTypes);
	int _CLS = Code::GetIndex(Code::SSD_CLASS_NODE, nodeTypes);
	int _OBJ = Code::GetIndex(Code::SSD_OBJECT_NODE, nodeTypes);
	int CLS = Code::GetIndex(Code::CBD_CLASS_NODE, nodeTypes);
	int OBJ = Code::GetIndex(Code::CBD_OBJECT_NODE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);

	int CLN = Code::GetIndex(Code::CBD_CLASS_LINK_EDGE, edgeTypes);
	int OLN = Code::GetIndex(Code::CBD_OBJECT_LINK_EDGE, edgeTypes);
	int NBL = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);
 
	connections[ACT][CLS][CLN] = True;
	connections[CLS][ACT][CLN] = True;
	connections[ACT][OBJ][CLN] = True;
	connections[OBJ][ACT][CLN] = True;
	connections[CLS][OBJ][CLN] = True;
	connections[OBJ][CLS][CLN] = True;

	connections[CLS][CLS][CLN] = True;

	connections[ACT][CLS][OLN] = True;
	connections[CLS][ACT][OLN] = True;
	connections[ACT][OBJ][OLN] = True;
	connections[OBJ][ACT][OLN] = True;

	connections[OBJ][OBJ][OLN] = True;

			connections[OBJ][OBJ][CLN] = True;


	connections[ACT][NOT][NBL] = True;
	connections[NOT][ACT][NBL] = True;
	connections[OBJ][NOT][NBL] = True;
	connections[NOT][CLS][NBL] = True;
	connections[CLS][NOT][NBL] = True;
	connections[NOT][OBJ][NBL] = True;
}
