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
#ifndef _HELPER_H
#define _HELPER_H

#include "util.h"
#include "lstring.h"
class MainWindow;
class TextViewDialog;
class Config;

/// class for showing popup help windows.
class Helper {
/*@Doc: {\large {\bf scope:} editor} */
public:
	///
	Helper(Config *c, MainWindow *w);
	///
	virtual ~Helper();
	///
	enum HelpTopicType {WELCOME, STARTING_EDITORS, GETTING_STARTED, 
		TOOL_INTRO, THE_MAIN_WINDOW, MOUSE_COMMANDS, EDIT_COMMANDS,
		FILE_COMMANDS, PRINT_PAGE_COMMANDS, MISC_COMMANDS,
		VERSION, COPYING, CHANGELOG};

	/// Gives help about basic operations.
	void Help(HelpTopicType topic); 
	///
	void SetStatus(const char *msg);
	///
	void SetStatus(const string *msg);
private:
	///
	MainWindow *mainwindow;
	///
	TextViewDialog *helpDialog;
	///
	Config *config;
	///
	string text;
};
#endif
