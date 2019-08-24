//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _DECISIONPOINT_H
#define _DECISIONPOINT_H

#include "stnode.h"

/// decision point (STD) node class.
class DecisionPoint: public STNode {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	DecisionPoint(STGraph *g);
	///
	Subject *Clone() {return new DecisionPoint(*this);}
	///
	int GetClassType() const {return Code::DECISION_POINT;}
};
#endif
