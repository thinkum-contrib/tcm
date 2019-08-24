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
#ifndef _DRAWWINDOW_H
#define _DRAWWINDOW_H

#include "editwindow.h"
#include "toolkit.h"
class DrawingArea;

/// (abstract) main window class common to all drawing editors.
class DrawWindow: public EditWindow {
/*@Doc: {\large {\bf scope:} editor} */
public:
	friend class DrawingArea;
	///
	DrawWindow(const char *name);
	///
	virtual ~DrawWindow();

	///
	const char *GetClassName() { return "DrawWindow";}
	///
	void SetAutoResize(bool set);
	///
	void SetInlineEdit(bool set);
	///
	virtual void SetHierarchic(bool set);

	/// set scale value string.
	void SetScaleValue(const char *s); 

	///
	DrawingArea *GetDrawingArea() {return drawingArea;}
	///
	void FitDocument();
	///
	void FitDocument(int wd, int ht);
	///
	void ShowPosition(int x, int y);
 
	/// sets name of edit undo menu item.
	void SetUndoName(const char *s);
	/// sets name of edit redo menu item.
	void SetRedoName(const char *s);

	/// enables edit undo menu item.
	void EnableUndo(bool flag); 
	/// enables edit redo menu item.
	void EnableRedo(bool flag); 

	///
	void EnableDocumentSource(bool flag);
protected:
	///
	virtual void WriteUsage(const char *s);

	/// parse user options.
	void ParseUserOptions(int argc, char **argv);

	///
	Widget GetArrowButtons() {return arrowButtons;}
	///
	void SetArrowButtons(Widget w) {arrowButtons=w;}
	///
	Widget GetScrolledWindow() {return scrolledWindow;}
	///
	void SetScrolledWindow(Widget w) {scrolledWindow = w;}
	///
	Widget GetScaleValue() {return scaleValue;}
	///
	void SetScaleValue(Widget w) {scaleValue=w;}

	///
	void SetScrolledWindowWidth(int n) {scrollWidth=n;} 
	///
	int GetScrolledWindowWidth() {return scrollWidth;} 

	///
	void SetScrolledWindowHeight(int n) {scrollHeight=n;} 
	/// 
	int GetScrolledWindowHeight() {return scrollHeight;}

	///
	void CreateDrawingArea();

	///
	void Finalize();

	///
	Widget CreateControlArea(Widget parent);

	///
	Widget CreateScrolledWindow(Widget parent);

	///
	Widget CreateScaleValue(Widget parent);

	///
	Widget CreateArrowButtonSquare(Widget parent);

	///
	virtual void InitMenuItems();
private:
	/// DrawingArea part of main window.
	DrawingArea *drawingArea; 

	/// Motif ScrolledWindow widget.
	Widget scrolledWindow;

	/// Horiz. scrollbar of scrollwin.
	Widget horizontalScrollBar;

	/// Vert. scrollbar of scrollwin.
	Widget verticalScrollBar;

	/// Motif Label for scale value.
	Widget scaleValue;

	/// Motif ToggleButton for inline edit.
	Widget inlineEditToggle;

	/// Motif ToggleButton for recomputing sizes.
	Widget autoResizeToggle;

	/// Motif ToggleButton for hierarchic documents.
	Widget hierarchicToggle;

	/// Motif Frame Widget for arrow buttons. 
	Widget arrowButtons;

	///
	int initDrawingWidth;
	///
	int initDrawingHeight;
	///
	int maxDrawingWidth;
	///
	int maxDrawingHeight;
	///
	static const int MIN_DRAWING_SIZE;

	/// width of the scrolled part in pixels.
	int scrollWidth; 

	/// height of the scrolled part in pixels.
	int scrollHeight;

	/// Determine scrolled window size from X screen.
	void DetermineScrollSize(ScreenType); 

	///
	string toolIntroMenuLabel;
};
#endif
