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
#ifndef _ATCHECKS_H
#define _ATCHECKS_H

#include "diagramchecks.h"

/// implements generic checks for soft constraints on AT diagrams.
class ATChecks: public DiagramChecks {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	ATChecks(Diagram *d, Graph *g);
	///
	unsigned CheckUnreachableStates(string &chkbuf);
	///
	unsigned CheckEmptyEvents(string &chkbuf);
	///
	unsigned CheckEmptyActions(string &chkbuf);
	///
	unsigned CheckNoActions(string &chkbuf);
	///
	unsigned CheckDoubleEvents(string &chkbuf);
};
#endif
