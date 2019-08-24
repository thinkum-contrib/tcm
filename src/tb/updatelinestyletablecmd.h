//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _UPDATELINESTYLETABLECMD_H
#define _UPDATELINESTYLETABLECMD_H

#include "updatelinetablecmd.h"

/// command class for updating line style in a table
class UpdateLineStyleTableCmd: public UpdateLineTableCmd {
/*@Doc: {\large {\bf scope:} table} */
public:
	///
	UpdateLineStyleTableCmd(Table *t, TableViewer *v, 
		Side::Type side, LineStyle::Type style);
	///
	virtual ~UpdateLineStyleTableCmd();
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "update line style";}
private:
	///
	List<LineStyle::Type> *oldStyles;
	///
	LineStyle::Type style;
	///
	void AddLine(LinePiece *line);
};
#endif