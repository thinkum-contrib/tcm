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
#ifndef _DUPLICATESHAPESCMD_H
#define _DUPLICATESHAPESCMD_H

#include "pasteshapescmd.h"

/// command class for duplicating node shapes.
class DuplicateShapesCmd: public PasteShapesCmd {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DuplicateShapesCmd(ShapeView *v);
	///
	virtual ~DuplicateShapesCmd();
	///
	void Abort();
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "duplicate";}
};
#endif
