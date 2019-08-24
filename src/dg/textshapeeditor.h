//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _TEXTSHAPEEDITOR_H
#define _TEXTSHAPEEDITOR_H

#include "inlineeditor.h"
class TextShape;
class DiagramViewer;

/// text shape editor class.
class TextShapeEditor: public InlineEditor {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	TextShapeEditor(DiagramViewer *v);

	/// initialize and start the inline editor with textshape.
	void Start(TextShape *t); 

	/// stop the object and update textshape.
	void Stop();

	/// abort editing and restore everything
	void Abort();

	/// start editing in separate window.
	void StartWindow(TextShape *t); 
	
	///
	TextShape *GetTextShape() const {return textshape;}
private:
	/// the text shape that will be edited.
	TextShape *textshape;
	///
	void UpdateText();
	///
	void Draw();
	///
	void SetBackground();
	///
	void RestoreBackground();
	///
	string saveBackground;
};
#endif
