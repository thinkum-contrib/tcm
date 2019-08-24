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
#ifndef _DRAWINGAREA_H
#define _DRAWINGAREA_H

#include "point.h"
#include "drawwindow.h"
class XGrafport;
class Viewer;
class Menu;

/// wrapper class around the Motif drawing area widget.
class DrawingArea: public MWidget {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// Description determines the size, if empty the screen sz is used.
	DrawingArea(Config *config, Widget parent, const char *name, 
		DrawWindow *w);

	///
	const char *GetClassName() { return "DrawingArea";}

	///
	void SetViewer(Viewer *v);
	///
	XGrafport *GetGrafport() const {return grafport;}

	///
	int GetWidth() const {return width;}
	///
	int GetHeight() const {return height;}

	///
	void UpdateSize(int w, int h);

	/// resize drawing area to fit the viewer's contents.
	void FitDocument();
	/// resize drawing area to given size.
	void FitDocument(int wd, int ht);

	/// enable/disable edit popup menu entry.
	void EnableUndo(bool flag); 
	/// enable/disable edit popup menu entry.
	void EnableRedo(bool flag); 
	/// enable/disable popup menu entry.
	void Enable(const char *label, bool flag);

	/// change edit popup menu undo entry name.
	void SetUndoName(const char *name); 
	/// change edit popup menu redo entry name.
	void SetRedoName(const char *name); 

	///
	Pixel GetBackgroundColor();
	///
	Pixel GetForegroundColor();
private:
	///
	DrawWindow *drawwindow;
	///
	Viewer *viewer;
	///
	XGrafport *grafport;

	/// translations used for drawing area callback.
	static char drawTranslations[];

	/// create the popup edit menu as a child of the drawing area.
	void CreatePopupMenu(int tool); 

	// static member functions serve as an interface between callback and 
	// member function. It takes care that 'this' is called from a 
	// Motif widget.
	static void DrawCB(Widget, XtPointer, XtPointer);

	/// Dispatch event: ButtonPress, ButtonRelease, KeyPress, MotionNotify.
	void Dispatch(XtPointer event);

	/// Called after exposure (e.g. resulting from scrollbar movement)
	void Redraw(XEvent *event);

	/// when button-3 pressed this is called and edit menu is popup up.
	void PopupMenu(XEvent *e); 

	/// map keysym (from X KeyPress event) from non-ascii char to own code.
	int MapKeySym(KeySym keysym); 

	/// anchor points used for dragging.
	Point anchorPoint;

	/// previous point used for dragging.
	Point previousPoint;

	/// next point used for dragging.
	Point nextPoint; 

	/// busy dragging.
	bool beenDragging;	

	/// save last typed characters.
	char buf[5];		
	/// save last event x coordinate.
	int x;
	/// save last event y coordinate.
	int y;		

	/// a Motif PopupMenu widget.
	Menu *popupMenu;

	/// width of the drawing area in pixels
	int width; 		
	/// height of the drawing area in pixels
	int height;
	/// maximum width of the drawing area in pixels
	int maxWidth; 		
	/// maximum height of the drawing area in pixels
	int maxHeight;
};
#endif
