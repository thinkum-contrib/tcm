////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente, Enschede, Netherlands.
// Author: David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "scgraph.h"
//#include "node.h"
//#include "edge.h"
//#include "util.h"
#include "code.h"

SCGraph::SCGraph(): Graph() {
	int i=0;
	nodeTypes[i++] = Code::SCD_AND_STATE;
	nodeTypes[i++] = Code::SCD_DECISION_STATE;
	nodeTypes[i++] = Code::SCD_DEFAULT_STATE;
	nodeTypes[i++] = Code::SCD_FINAL_STATE;
	nodeTypes[i++] = Code::SCD_OR_STATE;
	nodeTypes[i++] = Code::SCD_SYNCHRONIZATION_STATE;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = 0;

	int j=0;
	edgeTypes[j++] = Code::SCD_TRANSITION_EDGE;
	edgeTypes[j++] = Code::SCD_AND_EDGE;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = 0;
}

void SCGraph::InitConnections () {
	int ANS = Code::GetIndex(Code::SCD_AND_STATE, nodeTypes);
	int DCS = Code::GetIndex(Code::SCD_DECISION_STATE, nodeTypes);
	int DES = Code::GetIndex(Code::SCD_DEFAULT_STATE, nodeTypes);
	int FIS = Code::GetIndex(Code::SCD_FINAL_STATE, nodeTypes);
	int STA = Code::GetIndex(Code::SCD_OR_STATE, nodeTypes);
	int SYS = Code::GetIndex(Code::SCD_SYNCHRONIZATION_STATE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);
	int TRA = Code::GetIndex(Code::SCD_TRANSITION_EDGE, edgeTypes);
	int ANL = Code::GetIndex(Code::SCD_AND_EDGE, edgeTypes);
	int NBL = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);

	connections[ANS][ANS][TRA] = True;
	connections[ANS][DCS][TRA] = True;
	connections[ANS][FIS][TRA] = True;
	connections[ANS][STA][TRA] = True;
	connections[ANS][SYS][TRA] = True;

	connections[ANS][ANS][ANL] = True;

	connections[DCS][ANS][TRA] = True;
	connections[DCS][DCS][TRA] = True;
	connections[DCS][FIS][TRA] = True;
	connections[DCS][STA][TRA] = True;
	connections[DCS][SYS][TRA] = True;

	connections[DES][ANS][TRA] = True;
	connections[DES][DCS][TRA] = True;
	connections[DES][STA][TRA] = True;
	connections[DES][SYS][TRA] = True;

	connections[STA][ANS][TRA] = True;
	connections[STA][DCS][TRA] = True;
	connections[STA][FIS][TRA] = True;
	connections[STA][STA][TRA] = True;
	connections[STA][SYS][TRA] = True;

	connections[SYS][ANS][TRA] = True;
	connections[SYS][DCS][TRA] = True;
	connections[SYS][FIS][TRA] = True;
	connections[SYS][STA][TRA] = True;
	connections[SYS][SYS][TRA] = True;

	connections[ANS][NOT][NBL]= True;
	connections[NOT][ANS][NBL]= True;
	connections[DCS][NOT][NBL]= True;
	connections[NOT][DCS][NBL]= True;
	connections[DES][NOT][NBL]= True;
	connections[NOT][DES][NBL]= True;
	connections[FIS][NOT][NBL]= True;
	connections[NOT][FIS][NBL]= True;
	connections[STA][NOT][NBL]= True;
	connections[NOT][STA][NBL]= True;
	connections[SYS][NOT][NBL]= True;
	connections[NOT][SYS][NBL]= True;
}
