//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#ifndef _ERGRAPH_H
#define _ERGRAPH_H

#include "graph.h"

/// entity-relationship graph class
class ERGraph: public Graph {
/*@Doc: {\large {\bf scope:} TERD} */
public:
	///
	ERGraph();
	/// returns if an is\_a edge leaves this subject.
	bool IsaLeaves(Subject *s); 
	/// returns if there is an is\_a path from n1 to n2.
	bool IsaPathExists(Subject *n1, Subject *n2);
	///
	bool IsaPathExists(Subject *n1, Subject *n2, List<Edge *> *path);
	/// return the subject that is a generalization of this subject
	Subject *GetGeneralization(Subject *s);
	///
	void InitConnections();
};
#endif
