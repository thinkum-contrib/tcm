////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "atgraph.h"
#include "code.h"

ATGraph::ATGraph(): Graph() {
	int i=0;
	int j=0;
	nodeTypes[i++] = Code::ATD_INITIAL_STATE_NODE;
	nodeTypes[i++] = Code::ATD_ACTION_STATE_NODE;
	nodeTypes[i++] = Code::ATD_WAIT_STATE_NODE;
	nodeTypes[i++] = Code::ATD_DECISION_STATE_NODE;
	nodeTypes[i++] = Code::ATD_SYNCHRONIZATION_NODE;
	nodeTypes[i++] = Code::ATD_FINAL_STATE_NODE;
	nodeTypes[i++] = Code::NOTE;
	nodeTypes[i++] = Code::COMMENT;
	nodeTypes[i++] = 0;

	edgeTypes[j++] = Code::ATD_TRANSITION_EDGE;
	edgeTypes[j++] = Code::COMMENT_LINK;
	edgeTypes[j++] = 0;
}

void ATGraph::InitConnections () {

	int INI = Code::GetIndex(Code::ATD_INITIAL_STATE_NODE, nodeTypes);
	int ACT = Code::GetIndex(Code::ATD_ACTION_STATE_NODE, nodeTypes);
	// int INA = Code::GetIndex(Code::ATD_WAIT_STATE_NODE, nodeTypes);
	// int DEC = Code::GetIndex(Code::ATD_DECISION_STATE_NODE, nodeTypes);
	// int SYN = Code::GetIndex(Code::ATD_SYNCHRONIZATION_NODE, nodeTypes);
	int FIN = Code::GetIndex(Code::ATD_FINAL_STATE_NODE, nodeTypes);
	int NOT = Code::GetIndex(Code::NOTE, nodeTypes);
	// int COM = Code::GetIndex(Code::COMMENT, nodeTypes);

	int TRN = Code::GetIndex(Code::ATD_TRANSITION_EDGE, edgeTypes);
	int NBL = Code::GetIndex(Code::COMMENT_LINK, edgeTypes);

	// Initial : almost all transactions between states possible
        for (int i=INI;i<FIN;i++)		// excluding FIN
		for (int j=ACT;j<=FIN;j++)	// excluding INI 
			connections[i][j][TRN]= True;
				
	// Initial : all comment links possible
        for (int k=INI;k<=FIN;k++) {
		connections[k][NOT][NBL]= True;
		connections[NOT][k][NBL]= True;
	}
}
