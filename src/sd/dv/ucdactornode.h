//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#ifndef _UCDACTORNODE_H
#define _UCDACTORNODE_H

#include "node.h"
class UCGraph;

/// UCD actor node class.
class UCDActorNode: public Node {
/*@Doc: {\large {\bf scope:} TUCD} */
public:
	///
	UCDActorNode(UCGraph *);
	///
	Subject *Clone() {return new UCDActorNode(*this);}
	///
	Subject::NameErrType SetName(const string *name);
	///
	int GetClassType() const {return Code::UCD_ACTOR_NODE;}
};
#endif
