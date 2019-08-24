//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
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
#ifndef _FIGGRAFPORT_H 
#define _FIGGRAFPORT_H

#include "grafport.h"
#include <stdio.h>

/// Fig Grafport Class
class FigGrafport: public Grafport {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// open grafport to filename, When filename = "", stdout is used.
	FigGrafport(const char *fileName);
	///
	virtual ~FigGrafport();

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
	///
	void DrawStringLeftUnderlined(double x, double y, const char *str);
	///
	void DrawStringCenteredUnderlined(double x, double y, const char *str);
	///
	void DrawStringRightUnderlined(double x, double y, const char *str);

// Drawing Lines.
	///
//	void DrawLine(double x1, double y1, double x2, double y2);
	///
	void DrawUnzoomedLine(double x1, double y1, double x2, double y2);


// Drawing Points.
	///
	void DrawPoint(double x, double y);

// Drawing Arcs.
	///
	/* virtual */ void FillSegment(double x, double y, double wd, double ht,
		int arc1, int arc2);

// Drawing Polygons.
	/// draw n lines between the first n points in list.
	void DrawPolygon(const Point *points, int n);
	///
	void FillPolygon(const Point *points, int n);
	///
	/* virtual */ void FillPolygon(const DPoint *points, int n);

// thingies.
	/// generate Fig header.
	void Header(bool landscape=False);

	/// set grafport font.
	void SetFont(XFont *font);

	///
	void SetPageSize(double x, double y) {width = x; height = y;}
	///
	void SetFactor(double f) {factor = f;}

	///
	void SetTexFonts(bool b) {texFonts=b;}
	///
	bool IsTexFonts() {return texFonts;}

protected:
	///
	/* virtual */ void DrawSimpleArc(double x, double y,
		double wd, double ht, int arc1, int arc2);
	///
	/* virtual */ void DrawSimplePolygon(const DPoint *points,
		int n);
	///
	/* virtual */ void DrawSimpleCurve(const DPoint *p);
	///
	void FillCurve(const DPoint *p);
	///
	static void MakeFigString(string *str);
private:
	/// output file.
	FILE *fd;

	/// Factor to convert X coordinates to Fig coordinates.
	static const double F;

	/// Load built-in Fig colors.
	void InitColors();

	/// Xfig pen color number, set by SetForeground.
	int penColor;
	/// Xfig fill color number, set by FillXXXX.
	int fillColor;

	///
	double width;
	///
	double height;
	///
	double factor;
	///
	bool succes;
	///
	int psFont;
	///
	int texFont;

	///
	bool texFonts;

	///
	void DrawFigPolyLine(List<DPoint *> *points, 
			int sub_type, double radius = -1);
	///
	void DrawFigRectangle(double x, double y, double wd, double ht, 
			int sub_type, double radius = -1);
	///
	void DrawFigEllipse(double x, double y, double rd_x, double rd_y);
	///
	void FillFigEllipse(double x, double y, double rd_x, double rd_y);
	///
	void DrawFigText(double x, double y, const char *text, int sub_type); 

	///
	void SetFillColor();
	///
	void SetPSFont();
	///
	void SetTexFont();
	///
	void GetFigStringSize(const char *str, double &ht, double &wd);
};
#endif
