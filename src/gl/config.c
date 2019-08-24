///////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "config.h"
#include "afont.h"
#include "util.h"
#include "inputfile.h"
#include "system.h"
#include <stdlib.h>
#include <string.h>

const char Config::SYS_CONFIG[] = CONFIG_FILE;
const char Config::USER_CONFIG[] = ".tcmrc";

Config::Config(const char *s) { 
	string sfile = s;
	string ufile;

	ifile = new InputFile();

	addPointSizes = new List <string *>;

	// get user configuration file.
	(void)System::GetHome(&ufile);
	ufile += USER_CONFIG;

	// get default and system configuration file.

	char toolkit_conf[MAXNAME];
	System::GetToolkitConfig(toolkit_conf);
	sfile = toolkit_conf;
	sfile += SYS_CONFIG;


	// start with setting (reasonable) built-in defaults.
	SetDefault();

	// load system config file.
	if (System::FileExists(sfile.getstr())) {
		if (!Load(&sfile)) {
	 		// error("Warning: can't load system config file %s, "
		 	// "using built-in defaults\n", SYS_CONFIG);
			SetDefault();
		}
	}

	// override with user config file (when this exists).
	if (System::FileExists(ufile.getstr())) {
		if (!Load(&ufile)) {
	 		error("Warning: can't load user config file %s, "
				"using built-in defaults\n", ufile.getstr());
			SetDefault();
		}
	}

	// PRINTER environment variable used when no printerName is set.
	string p;
	if (System::GetPrinter(&p)) {
		if (printerName == "lp")
			printerName = p;
	}

	CheckPrintCommand();
	CheckPrinterQueueCommand();
	CheckPrinterRemoveCommand();
	CheckPreviewCommand();
	CheckPSFilterCommand();
	CheckText2PSCommand();
	CheckFig2DevCommand();
}

Config::~Config() {
	if (ifile)
		delete ifile;
}

bool Config::Load(const string *file) {
	// open file for reading.
	ifile->Open(file);
	if (!ifile->Good()) {
		ifile->Close();
		return False;
	}
	// look if it is not a directory etc.
	if (!System::FileRegular(file->getstr())) {
		ifile->Close();
		return False;
	}
	// load config info.
	if (!LoadEntries())
		return False;
	ifile->Close(); 
	return True;
}

bool Config::LoadEntries() {
	string option;
	string value;
	char c;
	while ((c = ifile->ReadChar()) == '{') {
		if (ifile->ReadWord(&option)) {
			if (!ifile->ReadWord(&value)) {
			    error("%s, line %d: illegal value for option %s\n",
					ifile->GetFileName()->getstr(), 
					ifile->LineNumber(), option.getstr());
				// try to continue with other options.
				continue;
			}
			if (option %= "Version")
				; // ignore (not used anymore).
			else if (option %= "EncapsulatedPostScript")
				; // ignore (not used anymore)
			else if (option %= "NumberOfCopies")
				; // ignore not used anymore
			else if (option %= "ExportFormat")
				exportFormat = value;
			else if (option %= "PrinterName")
				printerName = value;
			else if (option %= "PrintCommand")
				printCommand = value;
			else if (option %= "PrinterRemoveCommand")
				printerRemoveCommand = value;
			else if (option %= "PrinterQueueCommand")
				printerQueueCommand = value;
			else if (option %= "PreviewCommand")
				previewCommand = value;
			else if (option %= "Fig2DevCommand")
				fig2devCommand = value;
			else if (option %= "PostScriptFilterCommand")
				postScriptFilterCommand = value;
			else if (option %= "Text2PSFilterCommand")
				text2PSFilterCommand = value;
			else if (option %= "PrintColors")
				printColors = (value %= "True");
			else if (option %= "PrintDuplexPages")
				printDuplexPages = (value %= "True");
			else if (option %= "PrintTumbledPages")
				printTumbledPages = (value %= "True");
			else if (option %= "CharacterEncoding") {
				if (value %= "Standard")
					characterEncoding = STANDARD;
				else if (value %= "ISO_8859_1")
					characterEncoding = ISO_8859_1;
			}
			else if (option %= "BannerPage") {
				if (value %= "Default")
					bannerPage = DEF_BANNER;
				else if (value %= "None")
					bannerPage = NO_BANNER;
				else if (value %= "TCM_Banner")
					bannerPage = TCM_BANNER;
			}
			else if (option %= "TmpFile")
				tmpFile = value;
			else if (option %= "SendEmailOnCrash")
				sendEmailOnCrash = (value %= "True");
			else if (option %= "SendEmailOnStartup")
				sendEmailOnStartup = (value %= "True");
			else if (option %= "EmailAddress")
				emailAddress = value;

			else if (option %= "AutoResizing")
				autoResizing = (value %= "True");
			else if (option %= "InlineEditor")
				inlineEditor = (value %= "True");
			else if (option %= "AskBeforeQuit")
				askBeforeQuit = (value %= "True");

			else if (option %= "ScaleFactor")
				scaleFactor = value.todouble();

			else if (option %= "ShowGrid")
				showGrid = (value %= "True");
			else if (option %= "GridSize")
				gridSize = value.toint();
			else if (option %= "PointSnapping")
				pointSnapping = (value %= "True");
			else if (option %= "PointDistance")
				pointDistance = value.toint();
			else if (option %= "TextSelectDistance")
				textSelectDistance = value.toint();
			else if (option %= "LineSelectDistance")
				lineSelectDistance = value.toint();

			else if (option %= "PageOrientation") {
				if (value %= "Portrait")
					pageOrientation = PORTRAIT;
				else if (value %= "Landscape")
					pageOrientation = LANDSCAPE;
			}
			else if (option %= "ShowPageBoundary")
				showPageBoundary = (value %= "True");
			else if (option %= "PageSize")
				pageSize = PageSize::String2Type(&value);
			else if (option %= "IncludePageNumbers")
				includePageNumbers = (value %= "True");
			else if (option %= "IncludeDocumentInfo") {
				showDocumentInfoAsHeader = (value %= "Header");
				showDocumentInfoAsFooter = (value %= "Footer");
			}

			else if (option %= "FontFamily") {
				if (value %= "Helvetica")
					fontFamily = AFont::HELVETICA;
				else if (value %= "Times")
					fontFamily = AFont::TIMESROMAN;
				else if (value %= "Courier")
					fontFamily = AFont::COURIER;
				else if (value %= "NewCenturySchoolbook")
					fontFamily = AFont::NEWCENTURYSCHLBK;
				else if (value %= "Symbol")
					fontFamily = AFont::SYMBOL;
			}
			else if (option %= "FontStyle") {
				if (value %= "Roman")
					fontStyle = AFont::PLAIN;
				else if (value %= "Italic")
					fontStyle = AFont::ITALIC;
				else if (value %= "Bold")
					fontStyle = AFont::BOLD;
				else if (value %= "BoldItalic")
					fontStyle = AFont::BOLD+AFont::ITALIC;
			}
			else if (option %= "PointSize")
				pointSize = value.toint();
			else if (option %= "FontFoundry")
				fontFoundry = value;
			else if (option %= "ScalableFonts")
				scalableFonts = (value %= "True");
			else if (option %= "Underlined")
				underlined = (value %= "True");

			else if (option %= "AddPointSize") {
				if (value.toint() > 0)
					addPointSizes->add(new string(value));
			}

			else if (option %= "LineWidth")
				lineWidth = value.toint();
			else if (option %= "LineStyle")
				lineStyle = LineStyle::String2Type(&value);
			else if (option %= "LineColor") {
				lineColor = value;
				// no spaces in word.
				lineColor.replace('_', ' ');
				lineColor.downcase();
			}
			else if (option %= "TextColor") {
				textColor = value;
				textColor.replace('_', ' ');
				textColor.downcase();
			}
			else if (option %= "FillColor") {
				fillColor = value;
				fillColor.replace('_', ' ');
				fillColor.downcase();
			}

			else if (option %= "Alignment")
				textAlignment = TextAlign::String2Type(&value);
			else if (option %= "TextAlignment")
				textAlignment = TextAlign::String2Type(&value);
	
			else if (option %= "DrawingScrollWidth")
				drawingScrollWidth = value.toint();
			else if (option %= "DrawingScrollHeight")
				drawingScrollHeight = value.toint();
			else if (option %= "DrawingWidth")
				drawingWidth = value.toint();
			else if (option %= "DrawingHeight")
				drawingHeight = value.toint();
			else if (option %= "DrawingMaxWidth")
				drawingMaxWidth = value.toint();
			else if (option %= "DrawingMaxHeight")
				drawingMaxHeight = value.toint();
			else if (option %= "DrawingBackground")
				drawingBackground = value;
			else if (option %= "DrawingForeground")
				drawingForeground = value;

                        // GUI style view mode option
                        else if (option %= "GUIstyle")
                                classicGUIstyle = (value %= "Classic");
                        else if (option %= "PrivateColormap")
                                privateColormap = (value %= "True");

			// startup window view mode option
			else if (option %= "StartupWindowSmall")
				startupSmall = (value %= "True");

			// table options
			else if (option %= "TableMarginWidth")
				tableMarginWidth = value.toint();
			else if (option %= "TableMarginHeight")
				tableMarginHeight = value.toint();
			else if (option %= "ColumnAlignment")
				columnAlignment = 
					TextAlign::String2Type(&value);
			else if (option %= "RowAlignment")
				rowAlignment = TextAlign::String2Type(&value);
			else if (option %= "MinimalRowHeight")
				defaultRowHeight = value.toint();
			else if (option %= "DefaultRowHeight")
				defaultRowHeight = value.toint();
			else if (option %= "MinimalColumnWidth")
				defaultColumnWidth = value.toint();
			else if (option %= "DefaultColumnWidth")
				defaultColumnWidth = value.toint();
			else if (option %= "ShowRowColumnLabels")
				showRowColumnLabels = (value %= "True");
			else if (option %= "PrintRowColumnLabels")
				printRowColumnLabels = (value %= "True");
			else if (option %= "NumberOfColumns")
				numberOfColumns = value.toint();
			else if (option %= "NumberOfRows")
				numberOfRows = value.toint();
			else if (option %= "TableTopLeft") {
				int x = value.toint();
				if (ifile->ReadWord(&value)) {
					int y = value.toint();
					tableTopLeft = Point(x, y);
				}
				else  {
			    		error("%s, line %d: missing value "
					"for %s\n", 
					ifile->GetFileName()->getstr(), 
					ifile->LineNumber(), option.getstr());
					continue;
				}
			}
			else if (option %= "FETcolumnWidth")
				fetColumnWidth = value.toint();
			else if (option %= "TUTcolumnWidth")
				tutColumnWidth = value.toint();
			else if (option %= "TUTnumberOfColumns")
				tutNumberOfColumns = value.toint();
			else {
				error("%s, line %d: warning: unknown "
					"option %s\n",
					ifile->GetFileName()->getstr(), 
					ifile->LineNumber(), option.getstr());
				// ignore this option then.
			}
		}
		else {
			error("%s, line %d: option expected\n",
				ifile->GetFileName()->getstr(), 
				ifile->LineNumber());
			return False;
		}
		if (!ifile->LookupChar('}'))
			return False;
	}
	return True;
}

bool Config::Save() {
	return True; // not implemented yet.
}

void Config::CheckPrintCommand() {
	if (!System::FileExecutable(printCommand.getstr())) {
		DefaultPrintCommand();
	}
#ifdef DEBUG
	std::cout << "printing with " << printCommand << std::endl;
#endif
}

void Config::CheckPrinterQueueCommand() {
	if (!System::FileExecutable(printerQueueCommand.getstr())) {
		DefaultPrinterQueueCommand();
	}
#ifdef DEBUG
	std::cout << "show printer queue with " << printerQueueCommand << std::endl;
#endif
}

void Config::CheckPrinterRemoveCommand() {
	if(!System::FileExecutable(printerRemoveCommand.getstr())) {
		DefaultPrinterRemoveCommand();
	}
#ifdef DEBUG
	std::cout << "remove from queue with " << printerRemoveCommand << std::endl;
#endif
}

void Config::CheckPreviewCommand() {
	if(!System::FileExecutable(previewCommand.getstr())) {
		DefaultPreviewCommand();
	}
#ifdef DEBUG
	std::cout << "preview ps with " << previewCommand << std::endl;
#endif
}

void Config::CheckFig2DevCommand() {
	if(!System::FileExecutable(fig2devCommand.getstr())) {
		DefaultFig2DevCommand();
	}
#ifdef DEBUG
	std::cout << "fig2dev with " << fig2devCommand << std::endl;
#endif
}

void Config::CheckPSFilterCommand() {
	if(!System::FileExecutable(postScriptFilterCommand.getstr())) {
		DefaultPSFilterCommand();
	}
#ifdef DEBUG
	std::cout << "PostScript filter (psf) with " << 
		postScriptFilterCommand << std::endl;
#endif
}

void Config::CheckText2PSCommand() {
	char file[MAXNAME];
	strcpy(file, text2PSFilterCommand.getstr());
	char *p = strchr(file, ' ');
	if (p)
		*p = '\0';
	if(!System::FileExecutable(file)) {
		DefaultText2PSCommand();
	}
#ifdef DEBUG
	std::cout << "Text to ps with " << text2PSFilterCommand << std::endl;
#endif
}

void Config::DefaultPrintCommand() {
	if (!(System::FindProgram(&printCommand, "lpr") ||
		System::FindProgram(&printCommand, "lp")))
		printCommand = "lpr";
}

void Config::DefaultPrinterQueueCommand() {
	if (!(System::FindProgram(&printerQueueCommand, "lpstat") ||
		System::FindProgram(&printerQueueCommand, "lpq")))
		printerQueueCommand = "lpq";
}

void Config::DefaultPrinterRemoveCommand() {
	if (!(System::FindProgram(&printerRemoveCommand, "cancel") ||
		System::FindProgram(&printerRemoveCommand, "lprm")))
		printerRemoveCommand = "lprm";
}

void Config::DefaultPreviewCommand() {
	if (!(System::FindProgram(&previewCommand, "gv") ||
		System::FindProgram(&previewCommand, "xpsview") ||
		System::FindProgram(&previewCommand, "pageview") ||
		System::FindProgram(&previewCommand, "ghostview") ||
		System::FindProgram(&previewCommand, "gs")))
		previewCommand = "ghostview";
}

void Config::DefaultFig2DevCommand() {
	if (!System::FindProgram(&fig2devCommand, "fig2dev"))
		fig2devCommand = "fig2dev";
}

void Config::DefaultPSFilterCommand() {
	if (!System::FindProgram(&postScriptFilterCommand, "psf"))
		postScriptFilterCommand = "psf";
}

void Config::DefaultText2PSCommand() {
	if (System::FindProgram(&text2PSFilterCommand, "text2ps"))
		text2PSFilterCommand += " -f Helvetica ";
	else
		text2PSFilterCommand = "a2ps";
}

void Config::SetDefault() {
	DefaultPrintCommand();
	DefaultPrinterQueueCommand();
	DefaultPrinterRemoveCommand();
	DefaultPreviewCommand();
	DefaultFig2DevCommand();
	DefaultPSFilterCommand();
	DefaultText2PSCommand();

	exportFormat = "PostScript";
	printerName = "lp";
	printColors = True;
	printDuplexPages = True;
	printTumbledPages = False;
	characterEncoding = STANDARD;
	bannerPage = DEF_BANNER;

	tmpFile = "/tmp/tcmXXXXXX";
	sendEmailOnCrash = False;
	sendEmailOnStartup = False;
	emailAddress = "tcm@cs.utwente.nl";
	inlineEditor = True;
	autoResizing = True;
	askBeforeQuit = True;

	scaleFactor = 1.2;

	showGrid = False;
	pointSnapping = True;
	gridSize = 30;
	pointDistance = 10;
	textSelectDistance = 2;
	lineSelectDistance = 12;

	pageOrientation = PORTRAIT;
	showPageBoundary = True;
	pageSize = PageSize::A4;
	includePageNumbers = False;
	showDocumentInfoAsHeader = False;
	showDocumentInfoAsFooter = False;

	fontFoundry = "Adobe";
	fontFamily = AFont::PLAIN;
	fontStyle = AFont::HELVETICA;
	pointSize = 10;
	textAlignment = TextAlign::CENTER;
	scalableFonts = True;
	underlined = False;
	lineWidth = 1;
	lineStyle = LineStyle::SOLID;
	lineColor = "black";
	textColor = "black";
	fillColor = "white";

	drawingScrollWidth = 820;
	drawingScrollHeight= 680;
	drawingWidth = 1330;
	drawingHeight = 1330;
	drawingMaxWidth = 10000;
	drawingMaxHeight = 10000;
	drawingBackground = "White";
	drawingForeground = "Black";
	classicGUIstyle = False;
	privateColormap = False;

	tableMarginWidth = 5;
	tableMarginHeight = 5;
	columnAlignment= TextAlign::LEFT;
	rowAlignment = TextAlign::CENTER;
	defaultRowHeight = 26;
	defaultColumnWidth = 65;
	numberOfColumns = 7;
	numberOfRows = 7;
	showRowColumnLabels = True;
	printRowColumnLabels = False;
	tableTopLeft = Point(20, 80);

	fetColumnWidth = 52;
	tutColumnWidth = 81;
	tutNumberOfColumns = 5;
}
