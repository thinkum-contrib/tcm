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
#ifndef _REPLACETEXT_H
#define _REPLACETEXT_H

#include "command.h"
class string;
class TextShape;
class GShape;
class ShapeView;
class Diagram;

/// abstract command class for replacing text of all text shapes.
class ReplaceTextCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	ReplaceTextCmd(ShapeView *v,
		const string *s1, const string *s2,
		bool sens, bool substr, bool nameOnly);
	///
	virtual ~ReplaceTextCmd();
	///
	void UnExecute();
	///
	void ReExecute();
protected:
	///
	Diagram *GetDiagram() {return diagram;}
	///
	ShapeView *view;
	///
	Diagram *diagram;
	///
	List<GShape *> *oldSelection;
	///
	List<TextShape *> *textShapes;
	///
	List<string *> *oldStrings;
	///
	List<Point *> *oldSizes;
	///
	string *pattern;
	///
	string *replace;
	///
	bool caseSensitive;
	///
	bool substring;
	///
	bool nameOnly;
};
#endif
