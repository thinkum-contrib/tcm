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
#ifndef _SCDORSTATE_H
#define _SCDORSTATE_H

#include "scnode.h"
class SCGraph;

/// state (SCD) node class.
class SCDOrState: public SCNode {
/*@Doc: {\large {\bf scope:} TSCD} */
public:
	///
	SCDOrState(SCGraph *g);
	///
	int GetClassType() const {return Code::SCD_OR_STATE;}
	///
	Subject *Clone() {return new SCDOrState(*this);}

	/// Code for model checking
       	bool isino() const ; 

	///
	bool isbasic() const ;

	///
	bool isina()const ;

};
#endif
