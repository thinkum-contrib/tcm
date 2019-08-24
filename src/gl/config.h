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
#ifndef _CONFIG_H
#define _CONFIG_H

#include "llist.h"
#include "lstring.h"
#include "point.h"
#include "linestyle.h"
#include "textalign.h"
#include "pagesize.h"
class InputFile;

/// class for maintaining global tcm configuration.
class Config {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	Config(const char* fn);
	///
	~Config();

	///
	bool Load(const string* file);
	///
	bool Save();
	///
	void SetDefault();

// Print
	///
	const string* GetExportFormat() {return &exportFormat;}
	///
	const string* GetPrinterName() {return &printerName;}
	///
	const string* GetPrintCommand() {return &printCommand;}
	///
	const string* GetPreviewCommand() {return &previewCommand;}
	///
	const string* GetFig2DevCommand() {return &fig2devCommand;}
	///
	const string* GetPrinterQueueCommand() {return &printerQueueCommand;}
	///
	const string* GetPrinterRemoveCommand() {return &printerRemoveCommand;}
	///
	bool GetPrintColors() {return printColors;}
	///
	bool GetPrintDuplexPages() {return printDuplexPages;}
	///
	bool GetPrintTumbledPages() {return printTumbledPages;}
	///
	const string* GetPostScriptFilterCommand() {
		return &postScriptFilterCommand;}
	///
	const string* GetTmpFile() {return &tmpFile;}

	///
	bool GetSendEmailOnCrash() {return sendEmailOnCrash;}
	///
	bool GetSendEmailOnStartup() {return sendEmailOnStartup;}
	///
	const string* GetEmailAddress() {return &emailAddress;}

	///
	const string* GetText2PSFilterCommand() {
		return &text2PSFilterCommand;}
	///
	enum CharacterEncodingType {STANDARD, ISO_8859_1};
	///
	int GetCharacterEncoding() {return characterEncoding;}
	///
	enum BannerPageType {DEF_BANNER, NO_BANNER, TCM_BANNER};
	///
	BannerPageType GetBannerPage() {return bannerPage;}

// Page
	///
	enum PageOrientationType {PORTRAIT, LANDSCAPE};
	///
	enum ShowHeaderType {NONE, HEADER, FOOTER, BOTH};
	///
	PageOrientationType GetPageOrientation() {return pageOrientation;}
	///
	bool GetShowPageBoundary() {return showPageBoundary;}
	///
	PageSize::Type GetPageSize() {return pageSize;}
	///
	bool GetIncludePageNumbers() {return includePageNumbers;} 
	///
	bool GetShowDocumentInfoAsHeader() {return showDocumentInfoAsHeader;}
	///
	bool GetShowDocumentInfoAsFooter() {return showDocumentInfoAsFooter;}


// Scale
	///
	double GetScaleFactor() {return scaleFactor;}

// View
	///
	bool GetInlineEditor() {return inlineEditor;}
	///
	bool GetAutoResizing() {return autoResizing;}
	///
	bool GetAskBeforeQuit() {return askBeforeQuit;}

// Properties
	///
	const string* GetFontFoundry() {return &fontFoundry;}
	///
	int GetFontFamily() {return fontFamily;}
	///
	int GetFontStyle() {return fontStyle;}
	///
	int GetPointSize() {return pointSize;}
	///
	bool GetScalableFonts() {return scalableFonts;}
	///
	bool GetUnderlined() {return underlined;}
	///
	List <string *> *GetAddPointSizes() const {return addPointSizes;}

	///
	TextAlign::Type GetTextAlignment() {return textAlignment;}
	///
	int GetLineWidth() {return lineWidth;}
	///
	const string* GetLineColor() {return &lineColor;}
	///
	const string* GetTextColor() {return &textColor;}
	///
	const string* GetFillColor() {return &fillColor;}
	///
	LineStyle::Type GetLineStyle() {return lineStyle;}

// Drawing area
	///
	const string* GetDrawingBackground() {return &drawingBackground;}
	///
	const string* GetDrawingForeground() {return &drawingForeground;}
	///
	int GetDrawingScrollWidth() {return drawingScrollWidth;}
	///
	int GetDrawingScrollHeight() {return drawingScrollHeight;}
	///
	int GetDrawingWidth() {return drawingWidth;}
	///
	int GetDrawingHeight() {return drawingHeight;}
	///
	int GetDrawingMaxWidth() {return drawingMaxWidth;}
	///
	int GetDrawingMaxHeight() {return drawingMaxHeight;}

// Grid
	///
	bool GetShowGrid() {return showGrid;}
	///
	bool GetPointSnapping() {return pointSnapping;}
	///
	int GetGridSize() {return gridSize;} 
	///
	int GetPointDistance() {return pointDistance;} 
	///
	int GetTextSelectDistance() {return textSelectDistance;}
	///
	int GetLineSelectDistance() {return lineSelectDistance;}

// GUI style
	/// GUI style view mode
	int GetClassicGUIstyle() { return classicGUIstyle;}

	///
	bool GetPrivateColormap() { return privateColormap;}

// StartupWindow
	/// startup window view mode
	int GetStartupSmall() { return startupSmall;}

// Table
	/// margin width in pixels
	int GetTableMarginWidth() { return tableMarginWidth;}

	/// margin height in pixels
	int GetTableMarginHeight() { return tableMarginHeight;}

	///
	TextAlign::Type GetColumnAlignment() {return columnAlignment;}
	///
	TextAlign::Type GetRowAlignment() {return rowAlignment;}

	/// initial/default row height in pixels
	int GetDefaultRowHeight() {return defaultRowHeight;}

	/// standard/default column width in pixels
	int GetDefaultColumnWidth() {return defaultColumnWidth;}

	/// initial number of rows
	int GetNumberOfRows() {return numberOfRows;}

	/// initial number of columns
	int GetNumberOfColumns() {return numberOfColumns;}

	///
	bool GetShowRowColumnLabels() {return showRowColumnLabels;}
	///
	bool GetPrintRowColumnLabels() {return printRowColumnLabels;}

	/// default topleft position of a table.
	Point GetTableTopLeft() {return tableTopLeft;}

// specific table options
	///
	int GetFETcolumnWidth() {return fetColumnWidth;}
	///
	int GetTUTcolumnWidth() {return tutColumnWidth;}
	///
	int GetTUTnumberOfColumns() {return tutNumberOfColumns;}

private:
	///
	InputFile* ifile;

	/// system configuration file.
	static const char SYS_CONFIG[];
 
	/// default configuration file.
	static const char DEF_CONFIG[];

	/// user configuration file.
	static const char USER_CONFIG[];

	/// various configurations.
	string exportFormat;
	///
	string printerName;
	///
	string printCommand;
	///
	string previewCommand;
	///
	string fig2devCommand;
	///
	string postScriptFilterCommand;
	///
	string text2PSFilterCommand;
	///
	string printerQueueCommand;
	///
	string printerRemoveCommand;
	///
	CharacterEncodingType characterEncoding;

	///
	string tmpFile;

	///
	bool sendEmailOnCrash;
	///
	bool sendEmailOnStartup;
	///
	string emailAddress;

	///
	bool printColors;
	///
	bool printDuplexPages;
	///
	bool printTumbledPages;
	///
	BannerPageType bannerPage;

	///
	bool showPageBoundary;
	///
	PageSize::Type pageSize;
	///
	PageOrientationType pageOrientation;
	///
	bool includePageNumbers;
	///
	bool showDocumentInfoAsHeader;
	///
	bool showDocumentInfoAsFooter;

	///
	double scaleFactor;

	///
	bool inlineEditor;
	///
	bool autoResizing;
	///
	bool askBeforeQuit;

	///
	string fontFoundry;
	///
	int fontFamily;
	///
	int fontStyle;
	///
	int pointSize;
	///
	TextAlign::Type textAlignment;
	///
	bool scalableFonts;
	///
	bool underlined;

	///	additional pointsizes for fonts
	List <string *> *addPointSizes;

	///
	int lineWidth;
	///
	LineStyle::Type lineStyle;
	///
	string lineColor;
	///
	string textColor;
	///
	string fillColor;

	///
	int drawingScrollWidth;
	///
	int drawingScrollHeight;

	///
	string drawingBackground;
	///
	string drawingForeground;
	///
	int drawingWidth;
	///
	int drawingHeight;
	///
	int drawingMaxWidth;
	///
	int drawingMaxHeight;

	///
	bool showGrid;
	///
	bool pointSnapping;
	///
	int gridSize;
	///
	int pointDistance;
	///
	int textSelectDistance;
	///
	int lineSelectDistance;

	///
	bool classicGUIstyle;
	///
	bool privateColormap;

	///
	bool startupSmall;

	///
	int tableMarginWidth;
	///
	int tableMarginHeight;
	///
	TextAlign::Type columnAlignment;
	///
	TextAlign::Type rowAlignment;
	///
	int defaultRowHeight;
	///
	int defaultColumnWidth;
	///
	int numberOfRows;
	///
	int numberOfColumns;
	///
	bool showRowColumnLabels;
	///
	bool printRowColumnLabels;
	///
	Point tableTopLeft;

	///
	int fetColumnWidth;
	///
	int tutColumnWidth;
	///
	int tutNumberOfColumns;

	///
	bool LoadEntries();
	///
	void CheckPrintCommand();
	///
	void CheckPrinterQueueCommand();
	///
	void CheckPrinterRemoveCommand();
	///
	void CheckPreviewCommand();
	///
	void CheckFig2DevCommand();
	///
	void CheckPSFilterCommand();
	///
	void CheckText2PSCommand();
	///
	void DefaultPrintCommand();
	///
	void DefaultPrinterQueueCommand();
	///
	void DefaultPrinterRemoveCommand();
	///
	void DefaultPreviewCommand();
	///
	void DefaultFig2DevCommand();
	///
	void DefaultPSFilterCommand();
	///
	void DefaultText2PSCommand();
};
#endif
