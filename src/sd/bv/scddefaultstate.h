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
#ifndef _SCDDEFAULTSTATE_H
#define _SCDDEFAULTSTATE_H

#include "scnode.h"
class SCGraph;

/// state (SCD) node class.
class SCDDefaultState: public SCNode {
/*@Doc: {\large {\bf scope:} TSCD} */
public:
	///
	SCDDefaultState(SCGraph *g);
	///
	int GetClassType() const {return Code::SCD_DEFAULT_STATE;}
	///
	Subject *Clone() {return new SCDDefaultState(*this);}

	/// 
       	bool isino() const  {if (!GetParent()) return True; return (GetParent()->GetClassType()==Code::SCD_AND_STATE);} 
	///
	bool isina()const ;
};
#endif
