////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "application.h"
#include "config.h"
#include "mainwindow.h"
#include "messagelogdialog.h"
#include "printeroptions.h"
#include "xresources.h"
#include "inputfile.h"
#include "system.h"
#include "color.h"
#if defined(LINUX) || defined(__CYGWIN__)
#include <stdio.h>
#endif
#include <stdlib.h>
#include <string.h>
#include <Xm/XmStrDefs.h>
#ifdef USE_XMIM
#include <X11/Xlocale.h>
#else
#include <locale.h>
#endif

extern "C" int XErrorWrapper(Display *dpy, XErrorEvent *err_event) {
	return Application::XErrorHandler(dpy, err_event);
}

const char Application::COLORFILE[] = COLOR_FILE;

Application *theApplication = 0;

Application::Application(const char *appClassName): MWidget(appClassName) {
	initialized = False;
	privateCmap = False;
 
	// Set locale for C library and X, and Motif input functions.
    	if (setlocale(LC_CTYPE, "") == 0) {
		std::cerr << "Locale not supported by C library." << std::endl;
		if (setlocale(LC_CTYPE, 0)==0) {
			std::cerr << "Cannot continue" << std::endl;
	    		exit(0);
		} else
			std::cerr << "Using " << setlocale(LC_CTYPE, 0) <<
			        " locale instead." << std::endl;
    	}
    	if (!XSupportsLocale()) {
		std::cerr << "Xlib: locale " << setlocale(LC_CTYPE, 0)
			<< " not supported." << std::endl;
		exit(0);
    	}
    	if (XSetLocaleModifiers("") == 0)
		std::cerr << "Cannot set locale modifiers." << std::endl;
	display = XOpenDisplay(0); // Try to open the display.
	if (!display) {
		std::cerr << "Error: can't open display: " << std::endl;
		exit(1);
	}
	theApplication = this;  // Set the global Application pointer
	appContext = 0; 	// Initialize data members
	messageLogDialog = 0;
	config = 0;
	appClass = new char[strlen(appClassName)+1];
	strcpy(appClass, appClassName);
	colors = new List<Color *>;

	// catch Xt errors.
	XtAppSetErrorHandler(appContext, XtErrorHandler);
	XtAppSetWarningHandler(appContext, XtErrorHandler);
	// catch X errors.
	XSetErrorHandler(XErrorWrapper);
}

void Application::Initialize (int argc, char **argv) {
	// create configuration object.
	config = new Config("");

	// Do we have color or monochrome display ?
	bool color = (DefaultDepth(display, 
		DefaultScreen(display)) > 1) ? True : False;
	// if color : Do we have the classic or modern GUI style ?
	bool classicGUI = config->GetClassicGUIstyle();

	// do we send an email back when we crash?
	System::sendBugEmail = config->GetSendEmailOnCrash();
	strcpy(System::emailAddress, config->GetEmailAddress()->getstr());

	SetWidget(XtVaAppInitialize(&appContext, appClass,
		    0, 0, &argc, argv,
		    color ? (classicGUI ? 
				(char **)XResources::classicColorResources :
		 		(char **)XResources::modernColorResources) :
		 		(char **)XResources::monoResources,
		    XmNmappedWhenManaged, False, NULL));
	// The Application class is less likely to need to handle
	// "surprise" widget destruction than other classes, but
	// we might as well install a callback to be safe and consistent
	InstallDestroyHandler();

	// The instance name of this object was set in the Component 
	// constructor, before the name of the program was available
	// Free the old name and reset it to argv[0]
	SetName(argv[0]);

	// do we need a private color map?
	int n;
	if (color) {
		if (System::FindArg(argv, argc, "-priv_cmap", n) ||
		    System::FindArg(argv, argc, "-install", n) ||
		    config->GetPrivateColormap())
			CreatePrivateColormap();
	}
	// Load color rgb file.
	LoadColorFile();

	// lesstif cannot accept a window of 0 width and height.
	XtVaSetValues(GetWidget(), XmNwidth, 10, XmNheight, 10, NULL);

	// Force the shell window to exist so dialogs popped up from
	// this shell behave correctly
	XtRealizeWidget(GetWidget());

	// printer options are global.
	printerOptions = new PrinterOptions();
	// Create dialog for showing X and other info and error messages.
	// Messages are not written to stdout or stderr anymore.
	messageLogDialog = new MessageLogDialog(GetWidget());
	messageLogDialog->Initialize();
	char title[MAXNAME];
	strcpy(title, argv[0]);
	System::GiveFile(title, title);
	strcat(title, " message log");
	messageLogDialog->SetTitle(title);
	initialized = True;

	// Initialize and manage any windows registered
	// with this application.
	for (unsigned j = 0; j < windows.count(); j++) {
		windows[j]->Initialize(argc, argv, config);
		windows[j]->Manage();
		windows[j]->Finalize();
	}
}

Application::~Application() {
	delete appClass;
	windows.clear();
	if (messageLogDialog)
		delete messageLogDialog;
	delete printerOptions;
	colors->clear();
	delete colors;
	if (config)
		delete config;
}

void Application::CreatePrivateColormap() {
	// create and fill private colormap (do it only once).
	if (!GetWidget())
		return;
	if (!privateCmap) {
		Colormap cmap = DefaultColormapOfScreen(XtScreen(GetWidget()));
		cmap = XCopyColormapAndFree(display, cmap);
		XtVaSetValues(GetWidget(), XmNcolormap, cmap, NULL);
	}
	privateCmap = True;
}

void Application::HandleEvents() {
	// Just loop forever
	XtAppMainLoop (appContext);
}

void Application::RegisterWindow(MainWindow *window) {
	windows.add(window);
}

void Application::UnregisterWindow(MainWindow *window) {
	windows.remove(window);	
}

void Application::Manage() {
	// Manage all application windows. This will pop up
	// iconified windows as well.
	for (unsigned i = 0; i < windows.count(); i++)
		windows[i]->Manage();
}

void Application::Unmanage() {
	// Unmanage all application windows
	for (unsigned i = 0; i < windows.count(); i++)
		windows[i]->Unmanage();
}

void Application::Iconify() {
	// Iconify all top-level windows.
	for (unsigned i = 0; i < windows.count(); i++)
		windows[i]->Iconify();
}

void Application::Quit() {
	windows.clear();
	exit(0);
}

void Application::CloseWindow(MainWindow *m) {
	if (windows.find(m) >= 0) {
		windows.remove(m);
		delete m;
		if (windows.count() == 0)
			exit(0);
	}
}

int Application::XErrorHandler(Display *dpy, XErrorEvent *err_event) {
	char buf[BUFSIZ];
	XGetErrorText(dpy, err_event->error_code, buf, sizeof buf);
	error("X Error: <%s>\n", buf);
	return 1;
}
 
void Application::XtErrorHandler(char *msg) {
// #ifdef HPUX
// hack to prevend strange error message on tool startup.
//        if (equal(msg, "Missing charsets in String to FontSet conversion"))
//		return;
//  #endif
	error("Xt Error: %s\n", msg);
}

 
void Application::LoadColorFile() {
	char toolkit_conf[MAXNAME];
	System::GetToolkitConfig(toolkit_conf);
	string colorFile = toolkit_conf;
	colorFile += COLORFILE;

	InputFile f;
	f.Open(&colorFile);
	if (!f.Good()) {
		error("could not open color info file '%s'\n", 
			colorFile.getstr());
		return;
	}
	double red = 0, green = 0, blue = 0;
	string colorName;
	while (!f.Eof()) {
		string tmp;
		if (f.ReadWord(&tmp))
			red = tmp.todouble()/255;
		if (f.ReadWord(&tmp))
			green = tmp.todouble()/255;
		if (f.ReadWord(&tmp))
			blue = tmp.todouble()/255;
		if (f.ReadString(&colorName)) {
			Color *c = new Color(colorName, red, green, blue);
			colors->add(c);
		}
	}
	f.Close();
}
