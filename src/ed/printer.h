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
#ifndef _PRINTER_H
#define _PRINTER_H

#include "util.h"
#include "point.h"
#include "llist.h"
#include "pagesize.h"
class Viewer;
class EditWindow;
class Document;
class PrinterQueueDialog;
class PrinterOptions;
class FileSelectionDialog;
class PromptDialog;
class ScaleDialog;
class Config;
class XFont;
class InputFile;
class OutputFile;

/// class for printing and postscript generation.
class Printer {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// constructor.
	Printer(Config *c, Document *d); 	

	///
	virtual ~Printer();

	///
	enum OutputType {PS, EPS, FIGPS, FIGTEX, PNG};

	/// print document as postscript to current printer.
	void Print();

	/// show print preview in separate window.
	void ShowPrintPreview();

	/// show popup dialog for exporting to file.
	void ExportAs();	

	/// show dialog containing printer queue incl.'lprm' option.
	void ShowPrinterQueue(); 	

	/// popup dialog for new printer name.
	void Name(); 		

	/// popup dialog for new number of copies.
	void Copies();		

	/// popup dialog for setting printer command.
	void PrintCommand();		
	/// popup dialog for setting printer queue command.
	void PrinterQueueCommand();		
	/// popup dialog for setting printer remove command.
	void PrinterRemoveCommand();		
	/// popup dialog for setting preview command.
	void PreviewCommand();		

	///
	void SetName(const string *name);
	///
	void SetCopies(int copies);
	///
	void SetPrintCommand(const string *command);

	/// set page orientation to portrait or landscape.
	void SetPageOrientation(int num); 

	/// set page numbering on/off.
	void SetPageNumbering(bool b); 

	///
	int GetPageOrientation() { return pageOrientation;}

	/// set showing of page boundary.
	void SetShowPageBoundary(bool set); 

	///
	void ShowInfo(int type);

	/// set pagesize to num.
	void SetPageSize(PageSize::Type ps);

	/// return page-size (A4 etc).
	PageSize::Type GetPageSize() {return pageSize;} 

	/// return page size (pixels).
	void GetPageSize(double &width, double &height); 

	/// get area of used pages.
	void GetSizePages(Point &topLeft, Point &bottomRight);

	/// set bannerpage to num.
	void SetBannerPage(int num);

	/// return page-size (DEF\_BANNER etc).
	int GetBannerPage() {return bannerPage;} 

	/// actually save as postscript to the file.
	bool SavePostScript(const string *file, bool TcmBanner);

	/// actually save as encapsulated postscript to the file.
	bool SaveEPS(const string *file);

	/// actually save as Fig format to the file.
	bool SaveFig(const string *file, bool latexfonts=False);

	/// actually save as PNG format to the file.
	bool SavePNG(const string *file);

	/// 
	void DoSaveAsPS(const string *file);
	///
	void DoSaveAsEPS(const string *file);
	///
	void DoSaveAsFigTex(const string *file);
	///
	void DoSaveAsFigPS(const string *file);
	///
	void DoSaveAsPNG(const string *file);

	///
	void UpdateFSFiles();
	///
	void SetPreviewCommand(const string *newCommand);

	///
	void SetDefaultFont(int f, int s, int p);
	///
	void SetPrintColors(bool b);
	///
	void SetDuplex(bool b);
	///
	void SetTumble(bool b);

	/// draw page boundaries, page numbers, header and footer.
	void Draw();
	///
	void Undraw() {Draw();}

	///
	FileSelectionDialog *GetFileSelectionDialog() {
		return fileSelectionDialog;}
	///
	PromptDialog *GetPromptDialog() {return promptDialog;}
	///
	ScaleDialog *GetScaleDialog() {return scaleDialog;}
	///
	Config *GetConfig() {return config;}

	///
	void SetStatus(const string *msg);
	///
	void SetStatus(const char *msg);
	///
	void SetViewer(Viewer *v);

	/// Save page attributes to file.
	void Save(OutputFile *f);

	/// Load page attributes from file.
	bool Load(InputFile *f, double format);

	/// Check but not load page attributes from file.
	bool Check(InputFile *f, double format);

	/// put in tmp name of temporary file.
	void MakeTmpFile(string *tmp);
private:
	///
	EditWindow *mainwindow;
	///
	Viewer *viewer;
	///
	Document *document;
	///
	Config *config;
	///
	PrinterOptions *printerOptions;
	///
	PrinterQueueDialog *printerQueue;
	///
	FileSelectionDialog *fileSelectionDialog;
	///
	PromptDialog *promptDialog;
	///
	ScaleDialog *scaleDialog;

	/// A4, A3, Letter etc.
	PageSize::Type pageSize;

	/// Portrait, landscape etc.
	int pageOrientation;

	/// Default, None or TCM\_Banner
	int bannerPage;

	/// Unix command to preview postscript file.
	string previewCommand; 
	
	/// Unix command to generate diverse graphics files.
	string fig2devCommand;

	/// Unix command to filter postscript file.
	string psFilterCommand; 

	/// the name of the document that is going to be printed/saved.
	string docName; 

	/// page numbering on/off
	bool pageNumbering;

	/// is page boundary visible.
	bool showPageBoundary; 

	/// factor of screen pixels and postscript dots.
	static const double PS_FACTOR; 	

	/// show document header above each page.
	bool header;
	
	/// show document footer beneath each page.
	bool footer;

	/// print colors in PostScript or b/w only.
	bool printColors;

	/// print each page on a distinct sheet.
	bool duplex;

	/// print each backside page flipped relative to front side page.
	bool tumble;

	///
	void DoSaveAs(const string *file, OutputType type);

	///
	void MakePSFilter(string *psfilter);

	/// count nr of pages used in x (nX) and y (nY) direction.
	void GetPages(int &nX, int &nY);

	/// draw lines to reflect page boundaries.
	void DrawPageBoundary();

	/// draw all page numbers.
	void DrawPageNumbering();

	/// draw page nr at page (i,j) of size (w,h) (nX, nY pages total).
	void DrawPageNumber(int i, int j, int nX, int nY, int w, int h);

	/// draw document info in page headers.
	void DrawHeaders();
	/// draw document header on page (i,j) of size (w,h).
	void DrawHeader(int i, int j, int w, int h);

	/// draw document info in page footers.
	void DrawFooters();
	/// draw document info on page (i,j) of size (w,h).
	void DrawFooter(int i, int j, int w, int h);

	/// draw document info strings from position (x,y), info width is wd.
	void DrawInfo(int x, int y, int wd);

	/// change font of page numbers and headers to this font.
	XFont *GetFont(int family, int style, int size);

	/// 
	int ScaleCorrect(int x);

	/// font for page numbers and headers.
	XFont *defaultFont;
	/// save fonts for later reuse.
	List<XFont *> *fontList;

	/// nr. of lines of text in header/footer info.
	static const int INFO_LINES;
};
#endif
