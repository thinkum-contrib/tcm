//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#ifndef _UPDATELINEENDCMD_H
#define _UPDATELINEENDCMD_H

#include "command.h"
#include "lineend.h"
class Line;
class ShapeView;

/// command class for updating line ends of lines.
class UpdateLineEndCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	UpdateLineEndCmd(ShapeView *view, LineEnd::Type e1, LineEnd::Type e2);
	///
	virtual ~UpdateLineEndCmd();
	///
	void Execute();
	///
	void UnExecute();
	///
	const char *GetName() const {return "update line end";}
private:
	///
	LineEnd::Type end1;
	///
	LineEnd::Type end2;
	///
	List<Line *> *lines;
	///
	List<LineEnd::Type> *oldEnds1;
	///
	List<LineEnd::Type> *oldEnds2;
	///
	ShapeView *view;
};
#endif
