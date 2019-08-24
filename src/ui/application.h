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
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "mwidget.h"
#include "llist.h"
class MessageLogDialog;
class PrinterOptions;
class Color;
class Config;
class MainWindow;

/// generic window-based application class. See: MWidget.
class Application: public MWidget {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	// MainWindow needs to call 
	friend class MainWindow;
	///
	Application(const char *name);
	///
	virtual ~Application();

	/// manage application's top-level windows
	void Manage();

	/// unmanage application's top-level windows
	void Unmanage();

	/// iconify application's top-level windows
	void Iconify();

	/// close all top-level windows and quit application.
	void Quit();

	/// close window and quit application when it is the last.
	void CloseWindow(MainWindow *m);

	///
	Display *GetDisplay() { return display;}
	///
	XtAppContext GetAppContext() { return appContext;}
	///
	const char *GetAppClass() { return appClass;}
	///
	const char *GetClassName() { return "Application";}

	///
	bool Initialized() {return initialized;}

	///
	MessageLogDialog *GetMessageLogDialog() {return messageLogDialog;}
	///
	PrinterOptions *GetPrinterOptions() {return printerOptions;}

	/// Allow main and MainWindow to access protected member functions
	friend int main(int argc, char** argv);

	///
	void CreatePrivateColormap();

	///
	List<Color *> *GetColors() {return colors;}

	/// Show Xt and X error in error message log.
	static void XtErrorHandler(char *msg);
	//
	static int XErrorHandler(Display *dpy, XErrorEvent *event);
	///
	Config *GetConfig() {return config;}
protected:
	///
	virtual void Initialize(int argc, char** argv);
	///
	virtual void HandleEvents();

private:
	/// Support commonly needed data structures as a convenience
	Display *display;

	/// The configuration object.
	Config *config;

	/// Application context, needed by Xt.
	XtAppContext appContext;

	/// Class name of this application
	char *appClass;

	///
	MessageLogDialog *messageLogDialog;
	///
	PrinterOptions *printerOptions;

	///
	bool initialized;
	///
	bool privateCmap;

	/// Top-level windows in the program
	List<MainWindow*> windows;

	/// Registering toplevel windows
	void RegisterWindow(MainWindow *);

	/// Unregistering toplevel windows
	void UnregisterWindow(MainWindow *);

	///
	List<Color *> *colors;

	///
	void LoadColorFile();
	///
	static const char COLORFILE[];
};

// Pointer to single global instance
extern Application *theApplication; 

#endif
