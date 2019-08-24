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
#ifndef _UPDATEFONTCMD_H
#define _UPDATEFONTCMD_H

#include "command.h"
class GShape;
class ShapeView;
class XFont;

/// command class for updating fonts.
class UpdateFontCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	UpdateFontCmd(ShapeView *view, int family, int style, int size);
	///
	virtual ~UpdateFontCmd();
	///
	void UnExecute();
	///
	void Execute();
	///
	const char *GetName() const {return "update font";}
protected:
	/// save shape and its old font and size.
	void SaveShape(GShape *s);
	///
	XFont *GetNewFont(GShape *s);
	///
	void GetUpdateShapes();
private:
	///
	List<GShape *> *shapes;
	///
	List<Point *> *oldSizes;
	///
	List<XFont *> *oldFonts;
	///
	ShapeView *view;
	///
	int family;
	///
	int style;
	///
	int size;
};
#endif
