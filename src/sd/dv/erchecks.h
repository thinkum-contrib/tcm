//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl) 
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
#ifndef _ERCHECKS_H
#define _ERCHECKS_H

#include "diagramchecks.h"

/// implements checks for soft constraints on ER diagrams.
class ERChecks: public DiagramChecks {
/*@Doc: {\large {\bf scope:} TERD} */
public:
	///
	ERChecks(Diagram *d, Graph *g);
	/// relationship nodes are correctly connected.
	virtual unsigned CheckRelationshipCoherence(string &chkbuf);
	/// name + component types are unique for relationship nodes.
	unsigned CheckDoubleRelationships(string &chkbuf);
	/// relationship edges have an non-empty name or role name.
	unsigned CheckNamelessBinaryRelationships(string &chkbuf);
};
#endif
