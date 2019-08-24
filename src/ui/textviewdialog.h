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
#ifndef _TEXTVIEWDIALOG_H
#define _TEXTVIEWDIALOG_H

#include "dialog.h"
#include "util.h"
class Menu;
class MenuItem;
class FileSelectionDialog;
class FindDialog;
class ReplaceDialog;
class PrinterOptions;

/// manages text editor dialogs.
class TextViewDialog: public Dialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	TextViewDialog(Widget parent);
	///
	virtual ~TextViewDialog();
	///
        const char *GetClassName() { return "TextViewDialog";}
	///
	void Popup();

	///
	void SetTextSize(int nrOfRows, int nrOfColumns);
	///
	void SetTextRows(int nrOfRows);
	///
	void SetTextColumns(int nrOfColumns);
	///
	void SetTextMaxSize(int nrOfRows, int nrOfColumns);
	///
	void SetTextString(const string *text);
	///
	void GetTextString(string *t);

	///
	void SetStatus(const char *s);
	///
	void SetStatus(const string *s);

	///
	void SetDirectory(const char *d);
	///
	void SetDirectory(const string *d);
	///
	void Save();
	///
	void Print();
	///
	bool SaveFile(const char *file);
	///
	bool SaveFile(const string *file);
	///
	bool LoadFile(const char *file);
	///
	bool LoadFile(const string *file);
	
	///
	void DeleteAll();
	///
	void Cut();
	///
	void Copy();
	///
	void Paste();
	///
	void ClearSelection();
	///
	void Find();
	///
	void ClearFind();
	///
	void DoFind(int n);

	///
	FileSelectionDialog *GetFileSelectionDialog() {return fileSelector;}
protected:
	///
	void Configure();
	///
	void CreateWidget();
	///
	Widget GetTextWidget() {return textWidget;}
	///
	ReplaceDialog *GetReplaceDialog() {return replaceDialog;}
	///
	void SetReplaceDialog(ReplaceDialog *r) {replaceDialog=r;}
	///
	virtual void InitMenuItems();
	///
	static void PrintCB(Widget, XtPointer, XtPointer);
	///
	static void SaveAsCB(Widget, XtPointer, XtPointer);
	///
	static void SaveOKCB(Widget, XtPointer, XtPointer);
	///
	static void CopyCB(Widget, XtPointer, XtPointer);
	///
	static void FindCB(Widget, XtPointer, XtPointer);
	///
	static void FindNextCB(Widget, XtPointer, XtPointer);
	///
	static void FindAllCB(Widget, XtPointer, XtPointer);
	///
	static void ClearSelectionCB(Widget, XtPointer, XtPointer);
	///
	static void ClearFindCB(Widget, XtPointer, XtPointer);
	///
	MenuItem *fileItems;
	///
	MenuItem *editItems;
	///
	MenuItem *searchItems;
private:
	///
	Widget textWidget;
	///
	Widget menuBar;
	///
	Widget textStatus;
	///
	FileSelectionDialog *fileSelector;
	///
	PrinterOptions *printerOptions;
	///
	FindDialog *findDialog;
	///
	ReplaceDialog *replaceDialog;
	
	///
	Menu *fileMenu;
	///
	Menu *editMenu;
	///
	Menu *searchMenu;
	///
	string directory;
	///
	string saveFile;
	///
	string loadFile;

	///
	int maxRows;
	///
	int maxColumns;
};
#endif
