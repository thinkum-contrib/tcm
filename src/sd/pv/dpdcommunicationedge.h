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
// along with TCM; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _DPDCOMMUNICATIONEDGE_H
#define _DPDCOMMUNICATIONEDGE_H

#include "edge.h"
class CPGraph;

/// Component Dependency edge class
class DPDCommunicationEdge: public Edge {
/*@Doc: {\large {\bf scope:} TDPD} */
public:
	///
	DPDCommunicationEdge(CPGraph *g, Subject *s1, Subject *s2);
	///
	int GetClassType() const {return Code::DPD_COMMUNICATION_EDGE;}
	///
	Subject *Clone() {return new DPDCommunicationEdge(*this);}
};
#endif
