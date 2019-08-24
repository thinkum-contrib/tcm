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
#ifndef _PSCHECKS_H
#define _PSCHECKS_H

#include "diagramchecks.h"
#include "llist.h"
class PSProcess;
class DiagramViewer;
class Subject;

/// implements generic checks for soft constraints on PS diagrams.
class PSChecks: public DiagramChecks {
/*@Doc: {\large {\bf scope:} TPSD} */
public:
	///
	PSChecks(Diagram *d, Graph *g);
	///
	unsigned CheckRootOperator(PSProcess *root, string &chkbuf);
	///
	unsigned CheckChildOperators(PSProcess *parent, 
		List<Subject *> *children, string &chkbuf);
	///
	unsigned CheckChildPositions(DiagramViewer *dviewer,
		PSProcess *parent, List<Subject *> *children, string &chkbuf);
	///
	unsigned CheckDoubleProcessNames(string &chkbuf);
};
#endif
