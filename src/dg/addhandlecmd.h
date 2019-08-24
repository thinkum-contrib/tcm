//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#ifndef _ADDHANDLE_H 
#define _ADDHANDLE_H 

#include "draghandlecmd.h"

/// command class for adding line handles.
class AddHandleCmd: public DragHandleCmd {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	AddHandleCmd(Line *s, int x, int y, unsigned which);
	///
	void UnExecute();
	///
	void Executable();
	///
	void DrawOutLine(const Point *delta);
	///
	const char *GetName() const {return "add handle";}
private:
	///
	void CalcPoints();
	///
	Point CalcHandle();
	///
	Point newPoint;
	///
	unsigned addPosition;
};
#endif
