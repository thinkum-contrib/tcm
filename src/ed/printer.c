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
#include "printeroptions.h"
#include "fileutils.h"
#include "document.h"
#include "editwindow.h"
#include "printerqueuedialog.h"
#include "fileselectiondialog.h"
#include "questiondialog.h"
#include "promptdialog.h"
#include "scaledialog.h"
#include "psgrafport.h"
#include "xgrafport.h"
#include "figgrafport.h"
#include "viewer.h"
#include "printer.h"
#include "config.h"
#include "system.h"
#include "editstubs.h"
#include "inputfile.h"
#include "outputfile.h"
#if !defined( __GNUC__)
#include <sysent.h>
#endif
#include <stdlib.h>
#include <unistd.h>

// Screen/Paper factor
// PostScript: 1 point = 1/72 inch
// X display (xdpyinfo): 1 dot   = 1/83 inch
const double Printer::PS_FACTOR = 72.0/83.0;

// number of lines of text info in headers.
const int Printer::INFO_LINES = 5;

Printer::Printer(Config *c, Document *d) {
	document = d;
	config = c;
	viewer = 0; // set it later!
	mainwindow = d->GetMainWindow();
	printerOptions = mainwindow->GetPrinterOptions();
	fileSelectionDialog = new FileSelectionDialog(mainwindow->GetWidget());
	fileSelectionDialog->Initialize();
	fileSelectionDialog->SetTitle("Export File Selector");
	string l = "Format for Exported Document:";
	List<string *> s;
	s.add(new string("PostScript"));
	s.add(new string("EPS"));
	s.add(new string("Fig (PS fonts)"));
	s.add(new string("Fig (LaTeX fonts)"));
	s.add(new string("PNG"));
	fileSelectionDialog->CreateOptionMenu(&l, &s);
	string e = *config->GetExportFormat();
	fileSelectionDialog->SetOptionChangedCallback(
		EditStubs::UpdateFSFilesCB, this);
	fileSelectionDialog->SetOption(&e);
	s.clear();
	promptDialog = new PromptDialog(mainwindow->GetWidget());
	promptDialog->Initialize();
	scaleDialog = new ScaleDialog(mainwindow->GetWidget());
	scaleDialog->Initialize();
	defaultFont = new XFont(config->GetFontFoundry(), 
		config->GetFontFamily(), config->GetFontStyle(),
		config->GetPointSize(), config->GetScalableFonts());
	defaultFont->SetUnderlined(config->GetUnderlined());
	fontList = new List<XFont *>;
	fontList->add(defaultFont);
	printerQueue = new PrinterQueueDialog(mainwindow->GetWidget(), 
		mainwindow);
	printerQueue->Initialize();
	printerQueue->SetPrinterRemoveCommand(
		config->GetPrinterRemoveCommand());
	printerQueue->SetPrinterQueueCommand(config->GetPrinterQueueCommand());
	printerQueue->SetDefaultPrinterRemoveCommand(
		config->GetPrinterRemoveCommand());
	printerQueue->SetDefaultPrinterQueueCommand(
		config->GetPrinterQueueCommand());
	printerOptions->SetPrinterName(config->GetPrinterName());
	printerOptions->SetPrintCommand(config->GetPrintCommand());
	printerOptions->SetPrintBannerPage(config->GetBannerPage());
	printerOptions->SetTmpFile(config->GetTmpFile());
	printerOptions->SetTextFilterCommand(config->GetText2PSFilterCommand());
	pageSize = config->GetPageSize();
	pageOrientation = config->GetPageOrientation();
	showPageBoundary = config->GetShowPageBoundary();
	pageNumbering = config->GetIncludePageNumbers();
	header = config->GetShowDocumentInfoAsHeader();
	footer = config->GetShowDocumentInfoAsFooter();
	duplex = config->GetPrintDuplexPages();
	tumble = config->GetPrintTumbledPages();
	printColors = config->GetPrintColors();
	previewCommand = *config->GetPreviewCommand();
	fig2devCommand = *config->GetFig2DevCommand();
	psFilterCommand = *config->GetPostScriptFilterCommand();
}

Printer::~Printer() {
	delete fileSelectionDialog;
	delete printerQueue;
	delete promptDialog;
	delete scaleDialog;
	fontList->clear();
	delete fontList;
}

void Printer::SetViewer(Viewer *v) { viewer = v; }

void Printer::Print() {
	SetStatus("action: print");
	docName = *document->GetName();
	Widget w = mainwindow->GetWidget();
	if (!FileUtils::PrintingOK(w, docName.getstr()))
		return;
	mainwindow->SetCursor(MouseCursor::WATCH);
	string txt = "sending " + docName + " to printer";
	SetStatus(&txt);
	bool TcmBanner = (bannerPage == Config::TCM_BANNER);
	// create and write temporary PostScript file.
	string psName;
	MakeTmpFile(&psName);
	psName += ".ps";
	SavePostScript(&psName, TcmBanner);
	// make postscript filter (no duplex, tumble).
	string psfilter;
	MakePSFilter(&psfilter);
	// print it.
	if (FileUtils::Print(w, psName.getstr(), docName.getstr(), 
				psfilter.getstr()))
		SetStatus("print document succeeded");
	else
		SetStatus("print document failed");
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

void Printer::ShowPrintPreview() {
	SetStatus("action: show print preview");
	if (!System::FileExists(previewCommand.getstr())) {
		string txt = "Cannot find the PostScript previewer " + 
				previewCommand;
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))->
			Show("Error", &txt);
		SetStatus("preview document failed");
		return;
	}
	mainwindow->SetCursor(MouseCursor::WATCH);
	string psFileName;
	MakeTmpFile(&psFileName);
	psFileName += ".ps";
	SavePostScript(&psFileName, False);
	char tmp[MAXNAME];
	System::GiveFile(previewCommand.getstr(), tmp);
	string command = tmp;
	if (command == "ghostview") {
		string pgs = "-";
		string sz;
		PageSize::Type2String(pageSize, &sz);
		sz.downcase();
		pgs += sz;
		sprintf(tmp, "%s %s %s %s 2>&1\n", previewCommand.getstr(), 
				pgs.getstr(), pageOrientation==Config::PORTRAIT?
					"-portrait":"-landscape", 
				psFileName.getstr());
	}
	else if (command == "gv") {
		string sz;
		PageSize::Type2String(pageSize, &sz);
		sprintf(tmp, "%s --media=%s --orientation=%s %s 2>&1\n",
				previewCommand.getstr(), sz.getstr(),
				pageOrientation==Config::PORTRAIT?
					"portrait":"landscape", 
				psFileName.getstr());
	}
	else	// simplistic previewing ...
		sprintf(tmp, "%s %s 2>&1\n", previewCommand.getstr(), 
					     psFileName.getstr());

	int status = system(tmp);
	if (status) {
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::INFORMATION))->
			Show("Notice", "previewing did not succeed");
		string txt = "error, " + previewCommand;
		txt += " status = ";
		txt += status;
		txt += " \n";
		SetStatus(&txt);
	}
	else 
		SetStatus("preview document succeeded");
	unlink(psFileName.getstr());
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

void Printer::ExportAs() {
	SetStatus("action: export");
	UpdateFSFiles();
	fileSelectionDialog->Popup();
}

void Printer::UpdateFSFiles() {
	string defaultFile;
	fileSelectionDialog->GetDirectory(&defaultFile);
	defaultFile += *document->GetName();
	string suf = *document->GetSuffix();
	for (unsigned i=0; i<suf.length(); i++)
		defaultFile.remove();
	string s;
	fileSelectionDialog->GetOption(&s);
	if (s %= "EPS") {
		defaultFile += ".eps";
		fileSelectionDialog->SetExtension("*.eps");
		fileSelectionDialog->SetOKCallback(
				EditStubs::SaveAsEPSCB, this);
	}
	else if (s %= "PostScript") {
		defaultFile += ".ps";
		fileSelectionDialog->SetExtension("*.ps");
		fileSelectionDialog->SetOKCallback(
				EditStubs::SaveAsPSCB, this);
	}
	else if (s %= "PNG") {
		defaultFile += ".png";
		fileSelectionDialog->SetExtension("*.png");
		fileSelectionDialog->SetOKCallback(
				EditStubs::SaveAsPNGCB, this);
	}
	else if (s.contains("LaTeX fonts")) {
		defaultFile += ".fig";
		fileSelectionDialog->SetExtension("*.fig");
		fileSelectionDialog->SetOKCallback(
				EditStubs::SaveAsFigTexCB, this);
	}
	else if (s.contains("PS fonts")) {
		defaultFile += ".fig";
		fileSelectionDialog->SetExtension("*.fig");
		fileSelectionDialog->SetOKCallback(
				EditStubs::SaveAsFigPSCB, this);
	}
	// std::cout << "Default file " << defaultFile << std::endl;
	fileSelectionDialog->SetDefaultFile(&defaultFile);
}

void Printer::DoSaveAsPS(const string *file) {
	DoSaveAs(file, PS);
}

void Printer::DoSaveAsEPS(const string *file) {
	DoSaveAs(file, EPS);
}

void Printer::DoSaveAsPNG(const string *file) {
	DoSaveAs(file, PNG);
}

void Printer::DoSaveAsFigPS(const string *file) {
	DoSaveAs(file, FIGPS);
}

void Printer::DoSaveAsFigTex(const string *file) {
	DoSaveAs(file, FIGTEX);
}

void Printer::DoSaveAs(const string *file, OutputType type) {
	mainwindow->SetCursor(MouseCursor::WATCH);
	string format;
	string fileName;
	if (type == PS)
		format = "PostScript";
	else if (type == EPS)
		format = "EPS";
	else if (type == PNG)
		format = "PNG";
	else if (type == FIGTEX)
		format = "Fig (LaTeX fonts)";
	else if (type == FIGPS)
		format = "Fig (PS fonts)";
	fileName = *file;
	if (System::FileExists(fileName.getstr()) && 
	    !System::FileRegular(fileName.getstr())) {
		string txt = "'" + fileName + "'\n is not a regular file";
		(new MessageDialog(mainwindow->GetWidget(), 
				MessageDialog::ERROR))->
			Show("Error", &txt);
		txt = "document is not saved as " + format;
		SetStatus(&txt);
		mainwindow->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	if (!document->MayWrite(&fileName)) {
		SetStatus("not saved");
		mainwindow->SetCursor(MouseCursor::LEFT_PTR);
		return;
	}
	string txt = format + " to " + fileName;
	SetStatus(&txt);
	docName = *document->GetName();
	bool b = False;
	if (type == PS)
		b = SavePostScript(&fileName, False);
	else if (type == EPS)
		b = SaveEPS(&fileName);
	else if (type == FIGPS)
		b = SaveFig(&fileName, False);
	else if (type == FIGTEX)
		b = SaveFig(&fileName, True);
	else if (type == PNG)
		b = SavePNG(&fileName);
	if (b)
		txt = "save as " + format + " succeeded";
	else
		txt = "save as " + format + " failed";
	SetStatus(&txt);
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
}

void Printer::ShowPrinterQueue() {
	string n = *printerOptions->GetPrinterName();
	string txt = "printer queue of '" + n + "'";
	SetStatus(&txt);
	printerQueue->SetTitle(&txt);
	printerQueue->Update();
	printerQueue->Popup();
}

void Printer::Name() {
	SetStatus("action: set printer name");
	promptDialog->SetTitle("Printer name");
	promptDialog->SetSelectionLabel("Printer name: ");
	promptDialog->SetTextString(printerOptions->GetPrinterName());
	promptDialog->SetOKCallback(EditStubs::SetNameCB, this);
	promptDialog->SetDefaultValue(config->GetPrinterName());
	promptDialog->Popup();
}

void Printer::SetName(const string *newName) {
	printerOptions->SetPrinterName(newName);
	string txt = "printer name set to " + *newName;
	SetStatus(&txt);
}

void Printer::PrintCommand() {
	SetStatus("action: set print command");
	promptDialog->SetTitle("Print command");
	promptDialog->SetSelectionLabel("Print command: ");
	promptDialog->SetTextString(printerOptions->GetPrintCommand());
	promptDialog->SetOKCallback(EditStubs::SetPrintCommandCB, this);
	promptDialog->SetDefaultValue(config->GetPrintCommand());
	promptDialog->Popup();
}

void Printer::PrinterQueueCommand() {
	SetStatus("action: set printer queue command");
	printerQueue->PrinterQueueCommand();
}

void Printer::PrinterRemoveCommand() {
	SetStatus("action: set printer remove command");
	printerQueue->PrinterRemoveCommand();
}

void Printer::PreviewCommand() {
	SetStatus("action: set preview command");
	promptDialog->SetTitle("Preview command");
	promptDialog->SetSelectionLabel("Preview command: ");
	promptDialog->SetTextString(&previewCommand);
	promptDialog->SetOKCallback(EditStubs::SetPreviewCommandCB, this);
	promptDialog->SetDefaultValue(config->GetPreviewCommand());
	promptDialog->Popup();
}

void Printer::SetPrintCommand(const string *newpc) {
	printerOptions->SetPrintCommand(newpc);
	string txt = "print command set to " + *newpc;
	SetStatus(&txt);
}

void Printer::SetPreviewCommand(const string *newpc) {
	previewCommand = *newpc;
	string txt = "preview command set to " + previewCommand;
	SetStatus(&txt);
}

void Printer::Copies() {
	SetStatus("action: set number of copies");
	scaleDialog->SetTitle("Number of print copies");
	scaleDialog->SetScaleLabel("Number of copies");
	scaleDialog->SetScaleValues(PrinterOptions::MIN_PRINT_COPIES, 
		PrinterOptions::MAX_PRINT_COPIES, 
		printerOptions->GetPrintCopies(), 
		0, PrinterOptions::MIN_PRINT_COPIES);
	scaleDialog->SetValueChangedCallback(EditStubs::SetCopiesCB, this);
	scaleDialog->Popup();
}

void Printer::SetCopies(int i) {
	printerOptions->SetPrintCopies(i);
	string txt = "number of copies is ";
	txt += i;
	SetStatus(&txt);
}

void Printer::Draw() {
	if (showPageBoundary)
		DrawPageBoundary();
	if (pageNumbering)
		DrawPageNumbering();
	if (header)
		DrawHeaders();
	if (footer)
		DrawFooters();
}

void Printer::SetPageSize(PageSize::Type num) {
	SetStatus("action: set page size");
	if (pageSize != num) {
		pageSize = num;
		if (viewer)
			viewer->Refresh();
	}
	string pgs;
	PageSize::Type2String(num, &pgs);
	string txt = "page size is " + pgs;
	SetStatus(&txt);
}

void Printer::SetBannerPage(int num) {
	printerOptions->SetPrintBannerPage(num);
	SetStatus("action: set banner page");
	if (bannerPage != num) {
		bannerPage = num;
		if (viewer)
			viewer->Refresh();
	}
	string bps;
	if (bannerPage == Config::DEF_BANNER)
		bps = "default";
	else if (bannerPage == Config::NO_BANNER)
		bps = "off (no banner)";
	else if (bannerPage == Config::TCM_BANNER)
		bps = "TCM banner page";
	string txt = "banner page is " + bps;
	SetStatus(&txt);
}

void Printer::SetPageNumbering(bool b) {
	if (b)
		SetStatus("page numbering is on");
	else
		SetStatus("page numbering is off");
	if (pageNumbering == b)
		return;
	pageNumbering = b;
	if (viewer)
		viewer->Refresh();
}
 
XFont *Printer::GetFont(int family, int style, int size) {
	// look for font in font list.
	for (fontList->first(); !fontList->done(); fontList->next()) {
		XFont *ft = fontList->cur();
		if (ft->GetFamily() == family && ft->GetStyle() == style && 
				ft->GetSize() == size) {
			return ft;
		}
	}
	// else create new font.
	XFont *newFont = new XFont(config->GetFontFoundry(), family, style, size,
							   config->GetScalableFonts());
	fontList->add(newFont);
	return newFont;
}

void Printer::SetDefaultFont(int f, int s, int p) {
	if (defaultFont->GetFamily()!=f||
	    defaultFont->GetStyle()!=s ||
	    defaultFont->GetSize()!=p) {
		defaultFont = GetFont(f, s, p);
		if (pageNumbering || header || footer)
			viewer->Refresh();
	}
}

void Printer::SetPrintColors(bool b) {
	printColors = b;
	if (b)
		SetStatus("print colors");
	else
		SetStatus("print no colors");
}

void Printer::SetDuplex(bool b) {
	duplex = b;
	if (b)
		SetStatus("print duplex pages");
	else
		SetStatus("print no duplex pages");
}

void Printer::SetTumble(bool b) {
	tumble = b;
	if (b)
		SetStatus("print tumpled pages");
	else
		SetStatus("print no tumpled pages");
}

void Printer::ShowInfo(int t) {
	bool h = (t == Config::HEADER || t == Config::BOTH);
	bool f = (t == Config::FOOTER || t == Config::BOTH);
	string txt;
	if (h && f)
		txt = "show document info in header and footer";
	else if (h)
		txt = "show document info in header";
	else if (f)
		txt = "show document info in footer";
	else
		txt = "show no header nor footer";
	SetStatus(&txt);
	if (header == h && footer == f)
		return;
	header = h;
	footer = f;
	if (check(viewer))
		viewer->Refresh();
}

void Printer::DrawHeaders() {
	double w, h;
	GetPageSize(w, h);
	int n_x, n_y;
	GetPages(n_x, n_y);
	for (int j=1;j<=n_y;j++)
		for (int i=1;i<=n_x;i++)
			DrawHeader(i, j, (int)w, (int)h);
}

void Printer::DrawFooters() {
	double w, h;
	GetPageSize(w, h);
	int n_x, n_y;
	GetPages(n_x, n_y);
	for (int j=1;j<=n_y;j++)
		for (int i=1;i<=n_x;i++)
			DrawFooter(i, j, (int)w, (int)h);
}

int Printer::ScaleCorrect(int x) {
	double scaleValue = viewer->GetGrafport()->GetZoomValue();
	return (int)(x/scaleValue);
}

void Printer::DrawHeader(int i, int j, int w, int h) {
	int x = int((i-1) * w);
	int y = int((j-1) * h) + 5;
	if (!check(viewer))
		return;
	int fh = defaultFont->GetHeight();
	int wd = w;
	int ht = fh * INFO_LINES;
	Grafport *grafport = viewer->GetGrafport();
	grafport->DrawUnzoomedRectangle(x, y, wd, ht);
	grafport->DrawUnzoomedRectangle(x+2, y+2, wd-4, ht-4);
	DrawInfo(x, y, wd);
}

void Printer::DrawFooter(int i, int j, int w, int h) {
	int x = int((i-1) * w);
	int y = int((j) * h);
	if (!check(viewer))
		return;
	int wd = w;
	int ht = defaultFont->GetHeight() * INFO_LINES;
	Grafport *grafport = viewer->GetGrafport();
	grafport->DrawUnzoomedLine(x, y-ht, x+wd, y-ht);
	DrawInfo(x, y-ht, wd);
}

void Printer::DrawInfo(int x, int y, int wd) {
	int fh = defaultFont->GetHeight();
	const int HMARGIN = 10;
	const int VMARGIN = 1;
	string tmp;
	string dname = "Document name: ";
	dname += *document->GetName();
	string dtype = "Document type: ";
	dtype += *document->GetDocType();
	string dauthor = "Author: ";
	dauthor += *document->GetAuthor();
	string ddate = "Created on: ";
	ddate += *document->GetCreationTime();
	string dgenerator = "Generated from: ";
	dgenerator += *document->GetToolName();
	string plogin = "Printed by: ";
	System::GetLoginName(&tmp);
	plogin += tmp;
	string pdate = "Printed on: ";
	System::GetTime(&tmp);
	pdate += tmp;
	Grafport *grafport = viewer->GetGrafport();
	grafport->SetFont(defaultFont);
	grafport->DrawUnzoomedStringLeft(x+HMARGIN, y+fh+VMARGIN, 
		dname.getstr());
	grafport->DrawUnzoomedStringLeft(x+HMARGIN, y+2*(fh+VMARGIN), 
		dtype.getstr());
	grafport->DrawUnzoomedStringLeft(x+wd/2, y+2*(fh+VMARGIN), 
		dauthor.getstr());
	grafport->DrawUnzoomedStringLeft(x+HMARGIN, y+3*(fh+VMARGIN), 
		ddate.getstr());
	grafport->DrawUnzoomedStringLeft(x+wd/2, y+3*(fh+VMARGIN), 
		dgenerator.getstr());
	grafport->DrawUnzoomedStringLeft(x+HMARGIN, y+4*(fh+VMARGIN), 
		plogin.getstr());
	grafport->DrawUnzoomedStringLeft(x+wd/2, y+4*(fh+VMARGIN), 
		pdate.getstr());
}

void Printer::SetPageOrientation(int num) {
	SetStatus("action: set page orientation");
	if (pageOrientation != num) {
		Undraw();
		pageOrientation = num;
		Draw();
	}
	string txt = "page orientation is ";
	txt += (num==Config::PORTRAIT?"Portrait":"Landscape");
	SetStatus(&txt);
}

void Printer::GetPageSize(double &w, double &h) {
	// width and height in postscript points.
	w = PageSize::GetWidth(pageSize);
	h = PageSize::GetHeight(pageSize);
	// subtract offset and convert to pixels.
	w = (w - 2*PSGrafport::XOFF) / PS_FACTOR;
	h = (h - 2*PSGrafport::YOFF) / PS_FACTOR;

	if (pageOrientation == Config::LANDSCAPE) {
		double save = w;
		w = h;
		h = save;
	}
}

void Printer::SetShowPageBoundary(bool set) {
	string txt = "page boundary is ";
	txt += (set ? "visible":"invisible");
	SetStatus(&txt);
	if (showPageBoundary == set)
		return;
	showPageBoundary = set;
	DrawPageBoundary();
}

void Printer::DrawPageBoundary() {
	double w, h;
	GetPageSize(w, h);
	if (!check(viewer))
		return;
	Grafport *grafport = viewer->GetGrafport();
	int width = int(0.5 + grafport->GetWidth());
	int height = int(0.5 + grafport->GetHeight());
	int n_x = int(width / w) + 1;
	int n_y = int(height / h) + 1;
	int i;
	// I don't want the page boundary lines scaled
	XGrafport *gp = (XGrafport *)grafport;
	// vertical lines
	// left side
	gp->XGrafport::DrawEditDottedLine(0, 0, 0, height-1);
	for (i=1;i<=n_x;i++) {
		int x = int(i * w);
		gp->XGrafport::DrawEditDottedLine(x-1, 0, x-1, height-1);
	}
	// horizontal lines
	// top side
	gp->XGrafport::DrawEditDottedLine(0, 0, width-1, 0);
	for (i=1;i<=n_y;i++) {
		int y = int(i * h);
		gp->XGrafport::DrawEditDottedLine(0, y-1, width-1, y-1);
	}
}
 
void Printer::DrawPageNumbering() {
	double w, h;
	GetPageSize(w, h);
	int n_x, n_y;
	GetPages(n_x, n_y);
	for (int j=1;j<=n_y;j++)
		for (int i=1;i<=n_x;i++)
			DrawPageNumber(i, j, n_x, n_y, (int)w, (int)h);
}

void Printer::DrawPageNumber(int i, int j, int n_x, int n_y, int w, int h) {
	char pageStr[MAXNAME];
	int pages = n_x * n_y;
	const int factor = 30;
	int x = int(i * w - w/2);
	int y;
	if (footer && !header)
		y = int(j * h - (factor-1)*h/factor);
	else {
		y = int(j * h - h/factor);
		if (footer)
			y -= INFO_LINES*defaultFont->GetHeight();
	}
	sprintf(pageStr, "Page %d of %d", ((j-1)*n_x + i), pages);
	if (!check(viewer))
		return;
	Grafport *grafport = viewer->GetGrafport();
	grafport->SetFont(defaultFont);
	grafport->DrawUnzoomedStringCentered(x, y, pageStr);
}

void Printer::GetSizePages(Point &tl, Point &br) {
	double width, height;
	GetPageSize(width, height);
	if (!check(viewer))
		return;
	Point topLeft, bottomRight;
	viewer->CalcSizeElements(topLeft, bottomRight);
	Grafport *grafport = viewer->GetGrafport();
	double scaleValue = grafport->GetZoomValue();
	tl.x = int ((topLeft.x * scaleValue / width) * width);
	tl.y = int ((topLeft.y * scaleValue / height) * height);
	br.x = int ((1 + bottomRight.x * scaleValue / width) * width);
	br.y = int ((1 + bottomRight.y * scaleValue / height) * height);
}

void Printer::GetPages(int &n_x, int &n_y) {
	double w, h;
	GetPageSize(w, h);
	if (!check(viewer))
		return;
	Point topLeft, bottomRight;
	viewer->CalcSizeElements(topLeft, bottomRight);
	int x_size = bottomRight.x;
	int y_size = bottomRight.y;
	Grafport *grafport = viewer->GetGrafport();
	double scaleValue = grafport->GetZoomValue();
	n_x = int((x_size * scaleValue) / w) + 1;
	n_y = int((y_size * scaleValue) / h) + 1;
}

void Printer::MakePSFilter(string *psfilter) {
	if (tumble || !duplex) {
		if (psFilterCommand != "") {
			*psfilter = psFilterCommand;
			if (tumble)
				*psfilter += " -tumble ";
			if (!duplex)
				*psfilter += " -noduplex ";
			else
				*psfilter += " -duplex ";
			return;
		}
	}
	*psfilter = "";
}

bool Printer::SavePostScript(const string *file, bool fTcmBanner) {
	double w, h;
	string fileName = *file;
	if (fileName != "" && !fileName.endsWith(".ps"))
		fileName.setSuffix(".ps");
	if (!check(viewer))
		return False;
	viewer->DeselectAll();
	PSGrafport *psPort = new PSGrafport(fileName.getstr());
	psPort->SetISOLatin1Encoding(
			config->GetCharacterEncoding() == Config::ISO_8859_1);
	psPort->SetShowColors(printColors);
	// do we have a file ?
	if (!psPort->IsSucces()) {
		string txt = "'" + fileName + "'\n Cannot open";
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))-> Show("Error", &txt);
		delete psPort;
		return False;
	}
	docName = *document->GetName();
	// determine page size
	GetPageSize(w, h);
	psPort->SetPageSize(w, h);
	// determine factor
	psPort->SetFactor(PS_FACTOR);
	// save view grafport
	Grafport *grafport=viewer->GetGrafport();
	Grafport *savePort = grafport;
	// change current grafport to PostScript grafport
	grafport = psPort; 
	viewer->SetGrafport(psPort);
	// set scale value also in PostScript port
	double scaleValue = savePort->GetZoomValue();
	psPort->SetZoomValue(scaleValue);

	// start outputing all postscript stuff.
	psPort->Header(docName.getstr(), document->GetToolName()->getstr());
	// the code below is an improvement.
	// in stead of calling View->Draw each time
	// it is output only once, saving the code
	// in a PostScript proc, then call the proc each time per page.
	// psPort->BeginDrawProc();
	// viewer->Draw();
	// psPort->EndDrawProc();
	// but unfortunately many PS viewers and printers gave a stack
	// overflow when the procedure was very big. So we turned back to
	// a total Draw per page.
	if (fTcmBanner)
		psPort->Banner(docName.getstr());
	int n_x, n_y;
	GetPages(n_x, n_y);
	int pages = n_x*n_y;
	for (int j=1;j<=n_y;j++)
		for (int i=1;i<=n_x;i++) {
			psPort->BeginPage(i, j, n_x, pages);
			if (header)
				DrawHeader(i, j, (int)w, (int)h);
			// psPort->CallDrawProc();
			viewer->Draw();
			if (footer)
				DrawFooter(i, j, (int)w, (int)h);
			if (pageNumbering)
				DrawPageNumber(i, j, n_x, n_y, (int)w, (int)h);
			psPort->EndPage();
		}
	// close PostScript grafport
	psPort->Trailer();
	delete psPort;
	// restore grafport
	viewer->SetGrafport(savePort);
	grafport = savePort;
	return True;
}

bool Printer::SaveEPS(const string *file) {
	if (!check(viewer))
		return False;
	string fileName = *file;
	if (fileName != "" && !fileName.endsWith(".eps"))
		fileName.setSuffix(".eps");
	viewer->DeselectAll();
	PSGrafport *psPort = new PSGrafport(fileName.getstr());
	psPort->SetISOLatin1Encoding(
			config->GetCharacterEncoding() == Config::ISO_8859_1);
	psPort->SetShowColors(printColors);
	// do we have file ?
	if (!psPort->IsSucces()) {
		string txt = "'" + fileName + "'\n Cannot open";
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))-> Show("Error", &txt);
		delete psPort;
		return False;
	}
	// save view grafport
	Grafport *grafport=viewer->GetGrafport();
	Grafport *savePort = grafport;
	// change current grafport to PostScript grafport
	viewer->SetGrafport(psPort);
	// set ps factor
	psPort->SetFactor(PS_FACTOR);
	// change current grafport to PostScript grafport
	// set scale value also in PostScript port
	double scaleValue = savePort->GetZoomValue();
	psPort->SetZoomValue(scaleValue);
	grafport = psPort; 
	// determine bounding box
	double zValue = grafport->GetZoomValue();
	Point topLeft, bottomRight;
	viewer->CalcSizeElements(topLeft, bottomRight);
	int llx = (int)(zValue * topLeft.x);
	int lly = (int)(zValue * topLeft.y);
	int urx = (int)(zValue * bottomRight.x);
	int ury = (int)(zValue * bottomRight.y);
	docName = *document->GetName();
	psPort->EPSHeader(docName.getstr(), document->GetToolName()->getstr(), 
			  llx, lly, urx, ury);
	psPort->EPSProlog(lly, ury-lly);
	viewer->Draw();
	// close PostScript grafport
	psPort->Trailer();
	delete psPort;
	// restore grafport
	grafport = savePort;
	viewer->SetGrafport(savePort);
	return True;
}

bool Printer::SavePNG(const string *file) {
	mainwindow->SetCursor(MouseCursor::WATCH);
	// create and write temporary .fig file.
	string tmpFile;
	MakeTmpFile(&tmpFile);
	tmpFile += ".fig";
	SaveFig(&tmpFile, False);
	string command = fig2devCommand;
	command += " -Lpng " + tmpFile + " " + *file;
	int status = system(command.getstr());
	mainwindow->SetCursor(MouseCursor::LEFT_PTR);
	unlink(tmpFile.getstr());
	if (status) {
		string txt = "error, " + command;
		txt += "\ncannot be executed";
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::INFORMATION))->
			Show("Notice", &txt);
		return False;
	}
	return True;
}

bool Printer::SaveFig(const string *file, bool latexfonts) {
	if (!check(viewer))
		return False;
	string fileName = *file;
	if (fileName != "" && !fileName.endsWith(".fig"))
		fileName.setSuffix(".fig");
	viewer->DeselectAll();
	FigGrafport *figPort = new FigGrafport(fileName.getstr());
	if (!figPort->IsSucces()) {
		string txt = "'" + fileName + "'\nCannot open";
		(new MessageDialog(mainwindow->GetWidget(), 
			MessageDialog::ERROR))-> Show("Error", &txt);
		delete figPort;
		return False;
	}
	Grafport *grafport = viewer->GetGrafport();
	Grafport *savePort = grafport;
	viewer->SetGrafport(figPort);
	grafport = figPort;
	figPort->SetTexFonts(latexfonts);
	figPort->Header(pageOrientation==Config::LANDSCAPE);
	viewer->Draw();
	delete figPort;
	grafport = savePort;
	viewer->SetGrafport(savePort);
	return True;
}

void Printer::SetStatus(const string *msg) {
	mainwindow->SetStatus(msg->getstr());
}

void Printer::SetStatus(const char *msg) {
	mainwindow->SetStatus(msg);
}

void Printer::Save(OutputFile *ofile) {
	(*ofile) << "Page " << '\n';
	(*ofile) << "{\n";
	(*ofile) << "\t{ " << "PageOrientation " <<  
		((pageOrientation==Config::PORTRAIT) ? 
			"Portrait":"Landscape") << " }\n";
	string psz;
	PageSize::Type2String(pageSize, &psz);
	(*ofile) << "\t{ " << "PageSize " << psz << " }\n";
	(*ofile) << "\t{ " << "ShowHeaders " << 
		(header?"True":"False") << " }\n";
	(*ofile) << "\t{ " << "ShowFooters " << 
		(footer?"True":"False") << " }\n";
	(*ofile) << "\t{ " << "ShowNumbers " << 
		(pageNumbering?"True":"False") << " }\n";
	(*ofile) << "}\n\n";
}

bool Printer::Load(InputFile *ifile, double format) {
	if (format < 1.25)
		return True;
	string val = "Page";
	string s1, s2, s3, s4, s5;
	if (!(ifile->ReadWord(&val) &&
	     ifile->LookupChar('{') &&
	     ifile->ReadAttribute("PageOrientation", &s1)))
		return False;
	if (format >= 1.30) {
		if (!(ifile->ReadAttribute("PageSize", &s2)))
			return False;
		pageSize = PageSize::String2Type(&s2);
	}
	if (!(ifile->ReadAttribute("ShowHeaders", &s3) &&
	     ifile->ReadAttribute("ShowFooters", &s4) &&
	     ifile->ReadAttribute("ShowNumbers", &s5) &&
	     ifile->LookupChar('}')))
		return False;
	if (s1 %= "LandScape")
		pageOrientation=Config::LANDSCAPE;
	else
		pageOrientation=Config::PORTRAIT;
	header = (s3 %= "True");
	footer = (s4 %= "True");
	pageNumbering = (s5 %= "True");
	// update Page menu items
	mainwindow->SetPageSubMenuItem("Page Orientation", pageOrientation);
	mainwindow->SetPageSubMenuItem("Page Size", pageSize);
	mainwindow->SetPageMenuItem("Include Page Numbers", pageNumbering);
	mainwindow->SetPageSubMenuItem("Include Document Info", header + 2*footer);
	return True;
}

bool Printer::Check(InputFile *ifile, double format) {
	if (format < 1.25)
		return True;
	string val = "Page";
	return (ifile->ReadWord(&val) &&
		ifile->LookupChar('{') &&
		ifile->ReadAttribute("PageOrientation", &val) &&
		(format < 1.30 || ifile->ReadAttribute("PageSize", &val)) &&
		ifile->ReadAttribute("ShowHeaders", &val) &&
		ifile->ReadAttribute("ShowFooters", &val) &&
		ifile->ReadAttribute("ShowNumbers", &val) &&
		ifile->LookupChar('}'));
}

void Printer::MakeTmpFile(string *tmp) {
	// create and write temporary PostScript file.
	*tmp = *printerOptions->GetTmpFile();
	char buf[MAXNAME];
	strcpy(buf, tmp->getstr());
	(void)mkstemp(buf);
	*tmp = buf;
}
