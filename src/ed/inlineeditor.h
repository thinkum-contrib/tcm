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
#ifndef _INLINEEDITOR_H
#define _INLINEEDITOR_H

#include "point.h"
#include "lstring.h"
#include "textalign.h"
class Viewer;
class XFont;
class TextEditDialog;

/// (abstract) text editor class.
class InlineEditor {	
/*@Doc: {\large {\bf scope:} editor} */
public:
	///
	InlineEditor(Viewer *v);
	///
	virtual ~InlineEditor();
	/// top inline editing, update text.
	virtual void Stop() = 0;

	/// top inline editing, do not update text.
	virtual void Abort();

	///
	virtual void Draw();
	///
	void Undraw();

	/// simple inline text edit functions.
	void AddChar(char c);	
	///
	void BackSpace();
	///
	void Delete();
	///
	void CharLeft();
	///
	void CharRight();		 
	///
	void CharUp();
	///
	void CharDown();		 
	///
	void Home();			
	///
	void End();			
	/// empty text
	void Clear();

	/// set cursor to some position.
	void SetCursor(int x, int y);	

	/// set cursor on n-th char.
	void SetCursor(int whichChar);

	/// stop window editing, update text.
	void StopWindow(const string *);

	/// cancel window editing.
	void CancelWindow();
	///
	TextEditDialog *GetTextEditDialog() const {return textEditDialog;}
protected:
	///
	bool IsInUse() const {return inUse;}
	///
	void SetInUse(bool b) {inUse=b;}
	///
	void SetIgnoreWindow(bool b) {ignoreWindow=b;}
	///
	void SetText(const string *t) {text=*t;}
	///
	void SetOldText(const string *ot) {oldtext=*ot;}
	///
	void SetTextFont(XFont *ft) {textFont=ft;}
	///
	void SetTextColor(string *c) {textColor=*c;}
	///
	void SetAlignment(TextAlign::Type a) {alignment=a;}
	///
	void SetTextPosition(Point *p) {textPosition=*p;}
	///
	const string *GetText() const {return &text;}
	///
	const string *GetOldText() const {return &oldtext;}
	///
	Viewer *GetViewer() const {return viewer;}
	/// 
	virtual bool IsUnderlined() const {return underlined;}
	///
	void SetUnderlined(bool b) {underlined=b;}
private:
	/// the position of the text that is being edited.
	Point textPosition;	

	/// multi-line text that is being edited.
	string text;		

	/// the text before editing.
	string oldtext;		

	/// multi-line text that is being edited.
	XFont *textFont;		

	///
	string textColor;

	/// the coordinates where the cursor is drawn.
	Point cursorPosition;	

	/// cursor is at for cursor-th char.
	unsigned cursor;		

	/// editor is being used.
	bool inUse;		

	/// set when inline editing is performed. window callbacks are ignored.
	bool ignoreWindow;

	///
	TextAlign::Type alignment;

	///
	Viewer *viewer;
	///
	TextEditDialog *textEditDialog;
	///
	virtual void UpdateText() = 0;

	/// is the text underlined
	bool underlined;
};
#endif
