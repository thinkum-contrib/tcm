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
#ifndef _PSGRAFPORT_H 
#define _PSGRAFPORT_H

#include "grafport.h"
#include <stdio.h>

/// PostScript(tm) grafport class.
class PSGrafport: public Grafport {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// open grafport to filename, When filename = "", stdout is used.
	PSGrafport(const char *fileName);
	///
	virtual ~PSGrafport();

	///
	bool IsSucces() {return succes;}

// Sizes, refreshments etc.
	///
	void ClearArea(double, double, double, double) {}

// Line width.
	///
	void SetLineWidth(unsigned n);

// Colors.
	///
	void SetBackgroundColor(const string *);
	///
	void SetBackgroundColor(const char *);
	///
	void SetForegroundColor(const string *);
	///
	void SetForegroundColor(const char *);
 
// Drawing Rectangles.
	///
	void DrawRectangle(double x, double y, double wd, double ht);
	///
	void FillRectangle(double x, double y, double wd, double ht);

	///
	void DrawUnzoomedRectangle(double x, double y, double wd, double ht);

// Drawing Strings.
	///
	void DrawStringLeft(double x, double y, const char *str);
	///
	void DrawStringCentered(double x, double y, const char *str);
	///
	void DrawStringRight(double x, double y, const char *str);
	///
	void DrawUnzoomedStringLeft(double x, double y, const char *str);
	///
	void DrawUnzoomedStringCentered(double x, double y, const char *str);

// Drawing Underlined Strings.
	///
	void DrawStringLeftUnderlined(double x, double y, const char *str);
	///
	void DrawStringRightUnderlined(double x, double y, const char *str);
	///
	void DrawStringCenteredUnderlined(double x, double y, const char *str);

// Drawing Lines.
	///
//	void DrawLine(double x1, double y1, double x2, double y2);
	///
	void DrawUnzoomedLine(double x1, double y1, double x2, double y2);


// Drawing Points.
	///
	void DrawPoint(double x, double y);

// Drawing Ellipses.
	///
	void DrawEllipse(double x, double y, double wd, double ht);
	///
	void FillEllipse(double x, double y, double wd, double ht);

// Drawing Arcs.
	///								
	/* virtual */ void FillSegment(double x, double y,	
		double wd, double ht, int arc1, int arc2);	

// Drawing Polygons.
	///
	void DrawPolygon(const Point *points, int n);
	///
	void FillPolygon(const Point *points, int n);
	///								
	/* virtual */ void FillPolygon(const DPoint *points, int n);	

// Postscript thingies.
	/// generate postscript header.
	void Header(const char *title, const char *creator);

	///
	void BeginDrawProc();
	///
	void EndDrawProc();
	///
	void CallDrawProc();

	/// concat banner from file with name of document.
	void Banner(const char *title);

	///
	void BeginPage(int i, int j, int nx, int tot);

	///
	void EndPage();

	/// generate postscript trailer.
	void Trailer();

	/// set grafport font.
	void SetFont(XFont *font);

	/// header for encapsulated postscript + bounding box
	void EPSHeader(const char *title, const char *creator, 
		double llx, double lly, double urx, double ury);

	///
	void EPSProlog(double y, double dy);
	///
	void SetPageSize(double x, double y) {width = x; height = y;}
	///
	void SetFactor(double f) {factor = f;}
	///
	void SetISOLatin1Encoding(bool b) {isoLatin1Encoding = b;}
	///
	void SetShowColors(bool b) {showColors = b;}

	/// postscript file containing front page for printer.
	static const char BANNER[]; 

	///
	static const double XOFF;
	///
	static const double YOFF;
protected:
	///
	/* virtual */ void DrawSimpleArc(double x, double y,
		double wd, double ht, int arc1, int arc2);	
	///								
	/* virtual */ void DrawSimplePolygon(const DPoint *points,	
		int n);							
	///								
	/* virtual */ void DrawSimpleCurve(const DPoint *points);	
	///
	static void MakePSString(string *str);
	///
	static void FixEscapeChar(string *str, char c);
	///
	static void FixNonAscii(string *str);
	///
	void FontProlog();
	///
	void InstallIsoLatin1Font(const char *psFont);
	///
	void PageSetup();
	///
	void DrawPSRectangle(double x, double y, double wd, double ht);
	///
	void DrawPSLine(double x1, double y1, double x2, double y2);
	///
	void DrawPSPolygon(const Point *point, int nrPoints);
private:
	/// postscript output file.
	FILE *fd;
	///
	double width;
	///
	double height;
	///
	double factor;
	///
	bool succes;
	///
	bool isoLatin1Encoding;
	///
	bool showColors;

	/// default PostScript line width.
	static const double DEFAULT_LINE_WIDTH;

	///
	List<string> definedFonts;

	///
	void SetPSDashes();
	///
	void UnsetPSDashes();
};
#endif
