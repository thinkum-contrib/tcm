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
#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "mousecursor.h"
#include "mwidget.h"
class string;
class PrinterOptions;
class Config;

/// class supporting the main (toplevel) window.
class MainWindow: public MWidget {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// Constructor requires only a name
	MainWindow(const char *name);
	///
	virtual ~MainWindow();

	///
	const char *GetClassName() { return "MainWindow";}
 
	/// create toplevel widget, and other class members. 
	virtual void Initialize(int argc, char** argv, Config *config);

	/// initialization to do when window is already managed.
	virtual void Finalize() {}

	/// popup the window
	virtual void Manage();

	/// pop down the window
	virtual void Unmanage(); 

	/// iconify the window
	virtual void Iconify();

	///
	void ManageUnmapped();

	/// close the window.
	void Close();

	/// Set window title.
	void SetTitle(const char *title);
	///
	void SetTitle(const string *title);

	/// Set name of window icon.
	void SetIconName(const char *name);

	/// Set pixmap of window icon.
	void SetIconPixmap(Pixmap px);

	///
	void SetCursor(int cursorNum) {cursor->Set(cursorNum);}
	///
	void SetSizeCursor(int cursorNum) {cursor->SetSize(cursorNum);}

	///
	virtual int GetTool() {return -1;}

	///
	virtual void SetStatus(const char *) {}
	///
	virtual void SetStatus(const string *) {}

	///
	PrinterOptions *GetPrinterOptions();
protected:
	/// Derived classes define this to create the appl-specific work area.
	virtual Widget CreateWorkArea(Widget, int argc, char** argv) = 0;

	/// Derived classes use this functions to parse argv.
	virtual void ParseUserOptions(int argc, char** argv) = 0;
 
	/// Functions to create the constituting parts of the main window.
	virtual void CreateComponents(Widget window) = 0;

	///
	MouseCursor *GetCursor() {return cursor;}
	///
	Config *GetConfig() {return config;}
private:
	/// The MainWindow widget.
	Widget main;
	/// 
	MouseCursor *cursor;
	///
	Widget workarea;
	/// the configuration object.
	Config *config;

	///
	void WidgetDestroyed();
};
#endif
