//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// (c) copyright 1999, University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------

#ifndef _STARTUPWINDOW_H
#define _STARTUPWINDOW_H

#include "llist.h"
#include "util.h"
#include "mainwindow.h"
class Helper;
class Menu;
class MenuItem;
class Config;
class FileSelectionDialog;
class TextFieldListDialog;

/// Main window of the startup program.
class StartupWindow: public MainWindow {
/*@Doc: {\large {\bf scope:} general startup tool} */
public:
	///
	StartupWindow(const char *name);
	///
	virtual ~StartupWindow();
	///
	const char *GetClassName() { return "StartupWindow";}
	///
	void Quit();
	///
	void Project();
	///
	void OpenDocument();
	///
	void DrawingArea();
	///
	void StartEditor(int editor, const string *filename = 0);
	///
	void StartTableEditor(unsigned rows, unsigned columns, 
			 unsigned cellwidth, unsigned cellheight);
	///
	void SetDrawingArea(unsigned idw, unsigned idh, 
			unsigned mdw, unsigned mdh);
	///
	void SetProject(const string *s);
	///
	void OpenDocument(const string *s);
	///
	void SetStatus(const char *s);
	///
	void SetStatus(const string *s);
	///
	FileSelectionDialog *GetFileSelectionDialog() {
		return fileSelectionDialog;}
	///
	FileSelectionDialog *GetDirSelectionDialog() {
		return dirSelectionDialog;}
	///
	TextFieldListDialog *GetTableOptionsDialog() {
		return tableOptionsDialog;}
	///
	TextFieldListDialog *GetDrawingOptionsDialog() {
		return drawingOptionsDialog;}
	///
	static void QuitCB(Widget, XtPointer, XtPointer);
	///
	static void HelpCB(Widget, XtPointer, XtPointer);
	///
	static void ProjectCB(Widget, XtPointer, XtPointer);
	///
	static void DocumentCB(Widget, XtPointer, XtPointer);
	///
	static void OpenDocumentCB(Widget, XtPointer, XtPointer);
	///
	static void DrawingAreaCB(Widget, XtPointer, XtPointer);
	///
	static void StartEditorCB(Widget, XtPointer, XtPointer);
	///
	static void StartTableEditorCB(Widget, XtPointer, XtPointer);
	///
	static void SetProjectCB(Widget, XtPointer, XtPointer);
	///
	static void SetDrawingAreaCB(Widget, XtPointer, XtPointer);
private:
	///
	Config *config;
	///
	Helper *helper;
	///
	Widget statusBar;
	///
	FileSelectionDialog *fileSelectionDialog;
	///
	FileSelectionDialog *dirSelectionDialog;
	///
	TextFieldListDialog *tableOptionsDialog;
	///
	TextFieldListDialog *drawingOptionsDialog;
	///
	string projDir;
	///
	unsigned initDrawingWidth;
	///
	unsigned initDrawingHeight;
	///
	unsigned maxDrawingWidth;
	///
	unsigned maxDrawingHeight;
	/// the directory where the binaries are.
	string binDir;	

	///
	void InitMenuItems();
	///
	Widget CreateWorkArea(Widget w, int argc, char **argv);
	///
	void ParseUserOptions(int argc, char **argv);
	///
	void CreateComponents(Widget parent);
	///
	Widget CreateMenuBar(Widget parent);
	///
	Menu *fileMenu;
	///
	Menu *viewMenu;
	///
	Menu *helpMenu;
	///
	MenuItem *fileItems;
	///
	MenuItem *viewItems;
	///
	MenuItem *helpItems;
	///
	void AddToolEntry(Widget parent, int i);
	///
	void StartDocumentEditor(int editor, const string *filename = 0);
	///
	void ShowTableDialog(int editor);
	///
	void AppendExec(string *s, int editor);
	///
	void AppendProjDir(string *s);
	///
	void AppendDrawingArea(string *s);
	///
	void ExecCommand(string *s);
	///
	void InitTextFields();
	///
	void Finalize();
	///
	List<string *> tableFields;
	///
	List<string *> tableDefaults;
	///
	List<string *> fetDefaults;
	///
	List<string *> tutDefaults;
	///
	List<string *> drawingFields;
	///
	List<string *> drawingDefaults;
	///
	int tmpEditor;
	///
	static const int MIN_DRAWING_SIZE;
	///
	string welcomeLabel;
	///
	Widget mainForm;
	///
	Widget scrolledWindow;
};
#endif
