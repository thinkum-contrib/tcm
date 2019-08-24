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
#ifndef _EDITWINDOW_H
#define _EDITWINDOW_H

#include "mainwindow.h"
#include "util.h"
#include "bitmap.h"
class Printer;
class Document;
class Helper;
class Menu;
class MenuItem;

/// (abstract) main window class common to all editors.
class EditWindow: public MainWindow {
/*@Doc: {\large {\bf scope:} editor} */
public:
	///
	EditWindow(const char *name);
	///
	virtual ~EditWindow();
	///
	const char *GetClassName() { return "EditWindow";}

	///
	void Manage();

	/// most common screen sizes.
	enum ScreenType {EGA, VGA, SVGA, XVGA, NCD19B, SUN17, NCD16, HP19};

	/// set text field of status area to message
	void SetStatus(const char *message);
	///
	void SetStatus(const string *message);
 
	/// set text field of document name to s
	void SetDocumentName(const char *s);
	///
	void SetDocumentName(const string *s);
 
	/// set text field of document type to s
	void SetDocumentType(const char *s);
	///
	void SetDocumentType(const string *s);
 
	///
	void SetDocumentLevel(const char *s);
	///
	void SetDocumentLevel(const string *s);

	/// set text field of directory name to s
	void SetDirName(const char *s);
	///
	void SetDirName(const string *s);
 
	/// set/reset modified toggle
	void SetModified(bool set);
 
	/// sets name of edit undo menu item.
	virtual void SetUndoName(const char *s);

	/// sets name of edit redo menu item.
	virtual void SetRedoName(const char *s);

	/// enables edit undo menu item.
	virtual void EnableUndo(bool flag); 

	/// enables edit redo menu item.
	virtual void EnableRedo(bool flag); 

	/// enable show document source menu item.
	virtual void EnableDocumentSource(bool) {}
	///
	bool IsDoMap() {return doMap;}

	///
	Menu *GetFileMenu() {return fileMenu;}
	///
	Menu *GetEditMenu() {return editMenu;}
	///
	Menu *GetPrintMenu() {return printMenu;}
	///
	Menu *GetHelpMenu() {return helpMenu;}
	///
	Menu *GetViewMenu() {return viewMenu;}
	///
	Menu *GetSearchMenu() {return searchMenu;}
	///
	Menu *GetPropertiesMenu() {return propertiesMenu;}
	///
	Menu *GetDocumentMenu() { return documentMenu; }
	///
	MenuItem *GetPopupEditItems() {return popupEditItems;}

	/// set toggles in submenu of page menu.
	void SetPageSubMenuItem(const char *text, int n);
	/// set toggle in page menu.
	void SetPageMenuItem(const char *text, bool b);
protected:
	///
	Document *GetDocument() {return document;}
	///
	void SetDocument(Document *d) {document=d;}
	///
	Printer *GetPrinter() {return printer;}
	///
	Helper *GetHelper() {return helper;}

	///
	int GetArgsLeft() {return argsLeft;}
	///
	void SetArgsLeft(int n) {argsLeft=n;}
	///
	ScreenType GetScreenType() {return screenType;}
	///
	bool IsDoLoad() {return doLoad;}
	///
	void SetDoLoad(bool b) {doLoad=b;}
	///
	void SetLoadFile(const char *s) {loadFile = s;}

	///
	Widget GetMenuBar() {return menubar;}
	///
	void SetMenuBar(Widget w) {menubar=w;}
	///
	Widget GetDocumentArea() {return documentArea;}
	///
	void SetDocumentArea(Widget w) {documentArea=w;}
	///
	Widget GetStatusArea() {return statusArea;}
	///
	void SetStatusArea(Widget w) {statusArea=w;}
	///
	Widget GetControlArea() {return controlArea;}
	///
	void SetControlArea(Widget w) {controlArea=w;}
	///
	Widget GetLogo() {return logo;}
	///
	void SetLogo(Widget w) {logo=w;}
	///
	Widget GetDirName() {return dirName;}
	///
	void SetDirName(Widget w) {dirName=w;}

	/// parse user options.
	void ParseUserOptions(int argc, char **argv);

	/// create the work area of a document window widget (a frame).
	Widget CreateWorkArea(Widget parent, int argc, char **argv);

	///
	virtual Widget CreateMenuBar(Widget parent) = 0;
	/// 
	virtual Widget CreateLogo(Widget parent); 
	///
	virtual Widget CreateDocumentArea(Widget parent);
	///
	virtual Widget CreateStatusArea(Widget parent);
	///
	virtual Widget CreateControlArea(Widget parent);

	///
	Widget CreateToggle(Widget parent, const char *label, bool Init, 
			XtCallbackProc fun, XtPointer clientData);
	///
	void Finalize();

	///
	virtual void InitMenuItems() = 0;
	///
	Menu *fileMenu;
	///
	Menu *editMenu;
	///
	Menu *printMenu;
	///
	Menu *pageMenu;
	///
	Menu *viewMenu;
	///
	Menu *propertiesMenu;
	///
	Menu *helpMenu;
	///
	Menu *searchMenu;
	///
	Menu *documentMenu;
	///
	Menu *scaleMenu;

	///
	MenuItem *popupEditItems;
	///
	MenuItem *fileItems;
	///
	MenuItem *editItems;
	///
	MenuItem *viewItems;
	///
	MenuItem *bannerPageItems;
	///
	MenuItem *printItems;
	///
	MenuItem *searchItems;
	///
	MenuItem *propertiesItems;
	///
	MenuItem *printerOptionsItems;
	///
	MenuItem *helpItems;
	///
	MenuItem *pageOrientationItems;
	///
	MenuItem *pageSizeItems;
	///
	MenuItem *pageItems;
	///
	MenuItem *scaleItems;
	///
	MenuItem *documentItems;
	///
	MenuItem *documentInfoItems;
	///
	virtual void WriteUsage(const char *s);
private:
	/// The printing subsystem.
	Printer *printer;

	/// The document that is edited.
	Document *document;

	/// The helping subsystem.
	Helper *helper;

	/// Motif menu bar widget.
	Widget menubar;

	/// Motif Label widget containing logo pixmap.
	Widget logo;		

	/// Motif RowColumn Widget containg the following:
	Widget documentArea; 	

	/// Motif TextField for document type.
	Widget documentType;

	/// Motif TextField for document name.
	Widget documentName;

	///
	Widget documentLevel;

	/// Motif ToggleButton for modification.
	Widget modifiedToggle; 

	/// Motif RowColumn widget containing the following:
	Widget controlArea;

	/// Motif RowColumn Widget containing the following:
	Widget statusArea;

	/// Motif TextField for status.
	Widget statusText;

	/// Motif TextField for directory name.
	Widget dirName;

	/// the type of X screen.
	ScreenType screenType;

	///
	string loadFile;
	///
	string projDir;
	///
	bool doLoad;
	///
	int argsLeft;

	///
	virtual void CreateDocument() = 0;
	///
	void CreatePrinter();
	///
	void CreateHelper();

	/// Determine ScreenType from actual X screen width and height.
	void DetermineScreen(Screen *); 
	///
	static void AboutCB(Widget, XtPointer, XtPointer);

	/// for -toPS, -toEPS or -toFig options.
	bool generatePS;
	///
	bool generateEPS;
	///
	bool generatePNG;
	///
	bool generateFig;
	///
	bool generateLatexFonts;
	///
	string psFile;
	///
	string pngFile;
	///
	string epsFile;
	///
	string figFile;

	///
	Pixmap logoPixmap;
	///
	Bitmap logoBitmap;

	/// Do map (show) mainwindow when it is realized
	bool doMap;
};
#endif
