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
#ifndef _PRINTERQUEUEDIALOG_H
#define _PRINTERQUEUEDIALOG_H
 
#include "util.h"
#include "lstring.h"
#include "selectiondialog.h"
class MainWindow;
class PrinterOptions;
class SelectionDialog;
class PromptDialog;

/// class for showing printer queue.
class PrinterQueueDialog: public SelectionDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	PrinterQueueDialog(Widget parent, MainWindow *);
	///
        const char *GetClassName() { return "PrinterQueueDialog";}

	///
	void Update();
	///
	void Remove(const char *str);

	///
	void SetPrinterName(const string *s);

	/// show popup dialog to set Unix printer queue command.
	void PrinterQueueCommand();
	/// ... printer remove command.
	void PrinterRemoveCommand();

	///
	void SetPrinterQueueCommand(const string *c);
	///
	void SetPrinterRemoveCommand(const string *c);
	///
	void SetDefaultPrinterQueueCommand(const string *c) {
		defaultQueueCommand = *c;
	}
	///
	void SetDefaultPrinterRemoveCommand(const string *c) {
		defaultRemoveCommand = *c;
	}
	///
	PromptDialog *GetPromptDialog() {return promptDialog;}
protected:
	///
	void CreateWidget();
	///
	void Configure();
	///
	static void RemoveCB(Widget, XtPointer, XtPointer);
	///
	static void UpdateCB(Widget, XtPointer, XtPointer);
	///
	static void SetPrinterQueueCommandCB(Widget, XtPointer, XtPointer);
	///
	static void SetPrinterRemoveCommandCB(Widget, XtPointer, XtPointer);
private:
	///
	string queueCommand;
	///
	string removeCommand;
	///
	string defaultQueueCommand;
	///
	string defaultRemoveCommand;

	///
	MainWindow *mainwindow;
	///
	PrinterOptions *printerOptions;
	///
	PromptDialog *promptDialog;
};
#endif
