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
#ifndef _DCFCHECKS_H
#define _DCFCHECKS_H

#include "dfchecks.h"

/// implements checks for soft constraints on EFDs.
class DCFChecks: public DFChecks {
/*@Doc: {\large {\bf scope:} TEFD} */
public:
	///
	DCFChecks(Diagram *d, Graph *g);

	///
	unsigned CheckControlProcessCoherence(string &chkbuf);
	///
	unsigned CheckContinuousSplitMergeEdges(string &chkbuf);

	/// Check if activation mechanisms are correctly specified.
	unsigned CheckActivationMechanisms(string &chkbuf);

	/// Check discrete processes do not output continuous flows.
	unsigned CheckPersistences(string &chkbuf);
};
#endif
