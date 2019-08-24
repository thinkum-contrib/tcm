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
#ifndef _VIEWER_H
#define _VIEWER_H

#include "llist.h"
#include "linestyle.h"
#include "fillstyle.h"
#include "textalign.h"
#include "drawwindow.h"
#include "scaler.h"
class Command;
class Grafport;
class XFont;
class InlineEditor;
class NToggleListDialog;
class FontChooserDialog;
class ColorChooserDialog;
class FileSelectionDialog;
class InputFile;
class OutputFile;

/// (abstract) viewer class, responsible for the contents of the drawing area.
class Viewer {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// 
	Viewer(Config *c, DrawWindow *d); 
	///
	virtual ~Viewer();
	///
	virtual void Initialize() = 0;
	///
	Scaler *GetScaler() const {return scaler;}
	///
	Command *GetLastCmd();
	///
	DrawWindow *GetMainWindow() const {return mainwindow;}
	///
	Grafport *GetGrafport() const {return grafport;}
	///
	Printer *GetPrinter() const {return printer;}
	///
	void SetPrinter(Printer *p) {printer = p;}
	///
	virtual void SetGrafport(Grafport *g) {grafport = g;}
	///
	NToggleListDialog *GetLineWidthDialog() {return lineWidthDialog;}
	///
	NToggleListDialog *GetLineStyleDialog() {return lineStyleDialog;}
	///
	NToggleListDialog *GetTextAlignmentDialog() {
		return textAlignmentDialog;}
	///
	FontChooserDialog *GetFontChooserDialog() {return fontChooserDialog;}
	///
	FileSelectionDialog *GetPrintFileSelectionDialog();
	///
	ColorChooserDialog *GetColorChooserDialog() {return colorChooserDialog;}

	/// forwarding to scaler object.
	double Scale(double x) const {return scaler->Scale(x);}
	///
	Point Scale(const Point *p) const {return scaler->Scale(p);}
	///
	double ScaleCorrect(double x) const {return scaler->ScaleCorrect(x);}
	///
	Point ScaleCorrect(const Point *p) const {
		return scaler->ScaleCorrect(p);}
 
	/// Draw all elements of the viewer in grafport.
	virtual void Draw() = 0;
	/// Erase all elements from grafport.
	virtual void Undraw() = 0;

	/// Undo last command.
	void Undo(); 	

	/// Redo last command.
	void Redo(); 	

	/// Clear grafport contents, and redraw all viewer elements.
	void Refresh(); 

	/// redraw contents of grafport.
	virtual void Redraw(); 

	/// deselect all elements in viewer;
	virtual void DeselectAll() = 0; 

	/// Perform the function of the 1st button function of the mouse 
	virtual void Select(int x, int y) =0;

	/// Perform the function of the 2nd button function of the mouse.
	virtual void Adjust(int x, int y) =0;

	/// show that viewer is active.
	virtual void Activate() {}

	/// show that viewer is not active.
	virtual void Deactivate() {}

	/// stop being in editing mode.
	virtual void TextModeOff() = 0; 

	///
	void SetDefaultLineWidth(unsigned d); 
	///
	int GetDefaultLineWidth() {return defaultLineWidth;}
	///
	void UpdateLineWidth();
	///
	void DefaultLineWidth();
	///
	void ShowDefaultLineWidth();
	///
	void ShowConfigLineWidth();
	///
	virtual void UpdateLineWidthSelection(unsigned i) = 0;

	///
	void SetDefaultLineStyle(LineStyle::Type l) {defaultLineStyle = l;}
	///
	LineStyle::Type GetDefaultLineStyle() {return defaultLineStyle;}
	///
	void UpdateLineStyle();
	///
	void DefaultLineStyle();
	///
	void ShowDefaultLineStyle();
	///
	void ShowConfigLineStyle();
	///
	virtual void UpdateLineStyleSelection(LineStyle::Type s) = 0;

	///
	void SetDefaultLineColor(const string *s) {defaultLineColor = *s;}
	///
	const string *GetDefaultLineColor() {return &defaultLineColor;}

	///
	void SetDefaultTextColor(const string *s) {defaultTextColor = *s;}
	///
	const string *GetDefaultTextColor() {return &defaultTextColor;}

	///
	void SetDefaultFillColor(const string *s) { 
		defaultFillColor = *s; }
	///
	const string *GetDefaultFillColor() {return &defaultFillColor;}

	///
	FillStyle::Type GetDefaultFillStyle() const {
                return defaultFillStyle;}
	///
        void SetDefaultFillStyle(FillStyle::Type l) {
                defaultFillStyle=l;
        }


	///
	virtual void UpdateLineColorSelection(const string *s) = 0;
	///
	virtual void UpdateTextColorSelection(const string *s) = 0;
	///
	virtual void UpdateFillColorSelection(
		const string *s, FillStyle::Type f) = 0;

	///
	void UpdateLineColor();
	///
	void DefaultLineColor();
	///
	void ShowDefaultLineColor();
	///
	void ShowConfigLineColor();

	///
	void UpdateTextColor();
	///
	void DefaultTextColor();
	///
	void ShowDefaultTextColor();
	///
	void ShowConfigTextColor();

	///
	void UpdateFillColor();
	///
	void DefaultFillColor();
	///
	void ShowDefaultFillColor();
	///
	void ShowConfigFillColor();

	///
	XFont *GetDefaultFont() const {return defaultFont;}
	///
	void SetDefaultFontAttributes(int f, int s, int p);
	///
	virtual void SetDefaultFont(XFont *ft) {defaultFont=ft;}
	///
	void UpdateFont();
	///
	void DefaultFont();
	///
	void ShowDefaultFont();
	///
	void ShowConfigFont();
	/// 
	virtual void UpdateFontSelection(int family, int style, int size) = 0;
	///
	XFont *GetFont(int family, int style, int size);
	///
	XFont *GetFont(const char *description);

	///
	void UpdateTextAlignment();
	///
	void DefaultTextAlignment();
	///
	void ShowDefaultTextAlignment();
	///
	void ShowConfigTextAlignment();
	///
	TextAlign::Type GetDefaultTextAlignment() const {
		return defaultTextAlignment;}
	///
	void SetDefaultTextAlignment(TextAlign::Type a) {
		defaultTextAlignment = a;
	}
	///
	virtual void UpdateTextAlignmentSelection(TextAlign::Type a) = 0;

	///
	void EditText(int key);
	///
	bool IsAutoResize() const {return autoResizing;}
	///
	void SetAutoResize(bool s);
	///
	bool IsInlineEdit() const {return inlineEditor;}
	///
	void SetInlineEdit(bool s);
	///
	bool IsPasting() const {return pasting;}
	///
	void SetPasting(bool b) {pasting=b;}
	///
	bool IsZigZag() const {return zigZag;}
	///
	void SetZigZag(bool b) {zigZag=b;}
	///
	bool IsEditing() const {return editing;}

	/// change cursor to show which command can be performed.
	virtual void MovingPointer(int x, int y) = 0;

	/// not yet implemented (double clicked button).
	void DoubleClick(); 	 

	/// not yet implemented (function keys). 
	void DoFunctionKey(int); 

	/// enable execution of last command as newCmd.
	void NewCommand(Command *newCmd); 

	/// abort execution of last command.
	void AbortCommand();

	/// execute last command.
	void ExecuteCommand();

	/// undo execution of last command.
	void UndoCommand();

	/// redo execution of last command.
	void RedoCommand();

	/// delete command history, make undo impossible.
	void DeleteCommands();

	/// Perform the function of 1st button drag.
	virtual Command *Drag(int x, int y) = 0; 

	/// Perform the function of 2nd button drag.
	virtual Command *Connect(int x, int y) = 0; 

	/// Perform the function of keypress 'c'.
	virtual void KeyTyped(int x, int y, int c) = 0;

	/// calculate covered area of elements in grafport.
	virtual void CalcSizeElements(Point &topLeft, Point &bottomRight) = 0;

	/// calculate covered area of selected elements in grafport.
	virtual void CalcSizeSelection(Point &topLeft, Point &bottomRight) = 0;

	/// return page size (pixels).
	void GetPageSize(double &width, double &height);

	/// Save view attributes to file.
	void Save(OutputFile *f);

	/// Load view attributes from file.
	bool Load(InputFile *f, double format);

	/// Check but not load view attributes from file.
	bool Check(InputFile *f, double format);

	///
	static const int MIN_LINE_WIDTH;
	///
	static const int MAX_LINE_WIDTH;
protected:
	/// Clear contents of grafport.
	void ClearGrafport(); 
	///
	InlineEditor *GetInlineEditor() const {return edit;}
	///
	void SetInlineEditor(InlineEditor *i) {edit=i;}
	///
	void SetEditing(bool b) {editing=b;}
private:
	/// the main edit window.
	DrawWindow *mainwindow; 

	/// the grafport.
	Grafport *grafport; 

	/// for scaling coordinates.
	Scaler *scaler;	 

	/// the commands that were executed.
	enum {MAXHISTSIZE = 500};
	
	///
	Command *cmdHist[MAXHISTSIZE];
	///
	int cmdHistSize;

	/// the index of the last command that is executed.
	int lastCmd;
	/// when NewCommand(0) is called, execute can not take place.
	bool lastCmdIllegal;

	///
	Config *config;
	///
	XFont *defaultFont;
	///
	List<XFont *> *fontList;

	/// being in editing mode.
	bool editing;

	/// busy pasting.
	bool pasting;

	/// being zigzagging (busy drawing lines).
	bool zigZag;
	///
	InlineEditor *edit;
	///
	Printer *printer;

	/// if true, shapes automatically adapted to fit a text.
	bool autoResizing;

	/// text editing happens in drawing area (True) or in separate window.
	bool inlineEditor;

	/// newly created figures get this line width.
	unsigned defaultLineWidth;

	/// newly created figures get this line type.
	LineStyle::Type defaultLineStyle;

	/// newly created text get this text alignment.
	TextAlign::Type defaultTextAlignment;

	/// newly created lines get this color
	string defaultLineColor;

	/// newly created texts get this color
	string defaultTextColor;

	/// newly created filled items get this color
	string defaultFillColor;

	///
        FillStyle::Type defaultFillStyle;

	///
	NToggleListDialog *lineWidthDialog;
	///
	NToggleListDialog *lineStyleDialog;
	///
	NToggleListDialog *textAlignmentDialog;
	///
	FontChooserDialog *fontChooserDialog;
	///
	ColorChooserDialog *colorChooserDialog;
};
#endif
