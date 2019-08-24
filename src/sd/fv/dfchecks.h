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
#ifndef _DFCHECKS_H
#define _DFCHECKS_H

#include "diagramchecks.h"
class DFProcess;

/// implements checks for soft constraints on DFDs.
class DFChecks: public DiagramChecks {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DFChecks(Diagram *d, Graph *g);

	/// each data process should have an input and an output flow.
	unsigned CheckDataProcessCoherence(string &chkbuf);

	/// Check if splitmerge nodes are properly connected.
	unsigned CheckSplitMergeNodeCoherence(string &chkbuf);

	/// empty names are not allowed except for identical split/merge.
	unsigned CheckNamelessSplitMergeEdges(string &chkbuf);
	
	/// Check that flows have a name.
	unsigned CheckNamelessFlows(int edgetype, int nodetype1, 
		int nodetype2, string &chkbuf);

	/// Check that each data process has a minispec.
	unsigned CheckMinispecs(string &chkbuf);

	///
	void WriteCheckProcess(DFProcess *d, string &chkbuf);
};
#endif
