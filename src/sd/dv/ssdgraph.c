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
#include "ssdgraph.h"
#include "code.h"
 
SSDGraph::SSDGraph(): ERGraph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = Code::SSD_CLASS_NODE;
	nodeTypes[i++] = Code::SSD_OBJECT_NODE;
	nodeTypes[i++] = Code::SSD_GENERALIZATION_NODE;
	nodeTypes[i++] = Code::SSD_AGGREGATION_NODE;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = Code::SSD_ASSOCIATION_NODE;
	nodeTypes[i++] = Code::SSD_BINARY_ASSOCIATION_EDGE;	
	nodeTypes[i++] = Code::SSD_ASSOCIATION_LINK_EDGE;	 
	nodeTypes[i++] = Code::SSD_OBJECT_LINK_EDGE;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::SSD_BINARY_ASSOCIATION_EDGE;
	edgeTypes[j++] = Code::EMPTY_EDGE;
	edgeTypes[j++] = Code::SSD_GENERALIZATION_EDGE;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = Code::SSD_ASSOCIATION_LINK_EDGE;
	edgeTypes[j++] = Code::SSD_OBJECT_LINK_EDGE;
	edgeTypes[j++] = Code::SSD_PARTICIPANT_LINK_EDGE;
	edgeTypes[j++] = Code::SSD_AGGREGATION_EDGE;
	edgeTypes[j++] = Code::SSD_COMPOSITION_EDGE;
	edgeTypes[j++] = 0;
}

void SSDGraph::InitConnections() {
	int CLS = Code::GetIndex(Code::SSD_CLASS_NODE, nodeTypes);
	int OBJ = Code::GetIndex(Code::SSD_OBJECT_NODE, nodeTypes);
	int TAX = Code::GetIndex(Code::SSD_GENERALIZATION_NODE, nodeTypes);
	int AGJ = Code::GetIndex(Code::SSD_AGGREGATION_NODE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);
	int REL = Code::GetIndex(Code::SSD_ASSOCIATION_NODE, nodeTypes);
	int UBA = Code::GetIndex(Code::SSD_BINARY_ASSOCIATION_EDGE, nodeTypes);
	int UAL = Code::GetIndex(Code::SSD_ASSOCIATION_LINK_EDGE, nodeTypes);
	int UOL = Code::GetIndex(Code::SSD_OBJECT_LINK_EDGE, nodeTypes);

	int BIN = Code::GetIndex(Code::SSD_BINARY_ASSOCIATION_EDGE, edgeTypes);
	int ISA = Code::GetIndex(Code::SSD_GENERALIZATION_EDGE, edgeTypes);
	int EMP = Code::GetIndex(Code::EMPTY_EDGE, edgeTypes);
	int NBL = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);
	int ASL = Code::GetIndex(Code::SSD_ASSOCIATION_LINK_EDGE, edgeTypes);
	int LNK = Code::GetIndex(Code::SSD_OBJECT_LINK_EDGE, edgeTypes);
	int PAR = Code::GetIndex(Code::SSD_PARTICIPANT_LINK_EDGE, edgeTypes);
	int AGG = Code::GetIndex(Code::SSD_AGGREGATION_EDGE, edgeTypes);
	int COM = Code::GetIndex(Code::SSD_COMPOSITION_EDGE, edgeTypes);
 
	connections[CLS][CLS][BIN] = True;
	connections[CLS][CLS][ISA] = True;
	connections[CLS][CLS][AGG] = True;
	connections[CLS][CLS][COM] = True;

	connections[CLS][OBJ][BIN] = True;
	connections[OBJ][CLS][BIN] = True;

	connections[REL][CLS][PAR] = True;
	connections[REL][OBJ][PAR] = True;

	connections[OBJ][OBJ][LNK] = True;
	connections[OBJ][OBJ][AGG] = True;
	connections[OBJ][OBJ][COM] = True;

	connections[CLS][UBA][ASL] = True;	
	connections[UBA][CLS][ASL] = True;
	connections[CLS][REL][ASL] = True;
	connections[REL][CLS][ASL] = True;

	connections[OBJ][UOL][ASL] = True;	
	connections[UOL][CLS][ASL] = True;
	connections[OBJ][REL][ASL] = True;
	connections[REL][OBJ][ASL] = True;

	connections[CLS][TAX][EMP] = True;
	connections[CLS][TAX][ISA] = True;	//overruling EMP
	connections[TAX][CLS][EMP] = True;
	connections[TAX][CLS][ISA] = True;
	connections[TAX][CLS][PAR] = True;

	connections[CLS][AGJ][EMP] = True;
	connections[CLS][AGJ][AGG] = True;	//overruling EMP
	connections[CLS][AGJ][COM] = True;	//overruling EMP
	connections[AGJ][CLS][EMP] = True;
	connections[AGJ][CLS][AGG] = True;
	connections[AGJ][CLS][COM] = True;

	connections[CLS][NOT][NBL] = True;
	connections[NOT][CLS][NBL] = True;

	connections[NOT][OBJ][NBL] = True;
	connections[OBJ][NOT][NBL] = True;

	connections[TAX][NOT][NBL] = True;
	connections[NOT][TAX][NBL] = True;
	connections[UBA][NOT][NBL] = True;
	connections[NOT][UBA][NBL] = True;
	connections[UAL][NOT][NBL] = True;
	connections[NOT][UAL][NBL] = True;
	connections[UOL][NOT][NBL] = True;
	connections[NOT][UOL][NBL] = True;
	connections[AGJ][NOT][NBL] = True;
	connections[NOT][AGJ][NBL] = True;
}
