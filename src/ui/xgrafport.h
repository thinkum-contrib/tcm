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
#ifndef _XGRAFPORT_H 
#define _XGRAFPORT_H

#include "grafport.h"
//#include "llist.h"
#include <X11/Xlib.h>

typedef unsigned long Pixel;

/// X11 grafport for Xlib drawing.
class XGrafport: public Grafport {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	XGrafport(Display *d, Window win, double wd, double ht);
	///
	virtual ~XGrafport();

	///
        bool DrawsXor() {return True;}

// Sizes, refreshment.
	///
	void ClearArea(double x, double y, double wd, double ht);
	///
	double GetWidth() {return width;}
	///
	double GetHeight() {return height;}

	/// redraw using rdPixmap.
	void Redraw(double fromX, double fromY,
		double wd, double ht, double toX, double toY);
	///
	void UpdateSize(double wd, double ht);

// Colors.
	///
	void SetBackgroundColor(const string *colorName);
	///
	void SetBackgroundColor(const char *colorName);
	///
	void SetForegroundColor(const string *colorName);
	///
	void SetForegroundColor(const char *colorName);
//
	/// linewidth.
	void SetLineWidth(unsigned n);
// Fonts.
	///
	void SetFont(XFont *font);

// Drawing Rectangles.
	///
	void DrawRectangle(double x, double y,
		double wd, double ht);
	///
	void FillRectangle(double x, double y,
		double wd, double ht);

	/// not zoomed, not printed.
	void DrawEditDashedRectangle(double x, double y, double wd, double ht);
	///
	void DrawUnzoomedRectangle(double x, double y, double wd, double ht);

// Drawing Strings.
	///
	void DrawStringLeft(double x, double y, const char *str);
	///
	void DrawStringRight(double x, double y, const char *str);
	///
	void DrawStringCentered(double x, double y, const char *str);
	///
	void DrawStringLeftUnderlined(double x, double y,
		const char *str);
	///
	void DrawStringRightUnderlined(double x, double y,
		const char *str);
	///
	void DrawStringCenteredUnderlined(double x, double y,
		const char *str);

	/// not zoomed
	void DrawUnzoomedStringLeft(double, double, const char *);
	///
	void DrawUnzoomedStringCentered(double, double, const char *);
 
// Drawing Lines.
	///
//	void DrawLine(double x1, double y1, double x2, double y2);

	/// not zoomed. Uses different dot pattern.
	void DrawEditDottedGridLine(double x1, double y1, double x2, double y2);
	/// 
	void DrawEditDottedLine(double x1, double y1, double x2, double y2);
 
	/// not zoomed and not printed
	void DrawEditLine(double x1, double y1, double x2, double y2);
	/// not zoomed and not printed
	void DrawEditPoint(double x1, double y2);

	///
	void DrawUnzoomedLine(double, double, double, double);
 
// Drawing Points
	///
	void DrawPoint(double x, double y);

// Drawing Ellipses
	///
	void DrawEllipse(double x, double y, double wd, double ht);
	///
	void FillEllipse(double x, double y, double wd, double ht);

// Drawing Arcs
	///
	/* virtual */ void FillSegment(double x, double y,	
		 double wd, double ht, int arc1, int arc2);	

// Drawing Polygons
	///
	void DrawPolygon(const Point *points, int n);
	///
	void FillPolygon(const Point *points, int n);
	///								
	/* virtual */ void FillPolygon(const DPoint *plist, int n);	
// Drawing Cursor signs.
	///
	void DrawActiveCaret(double x, double y);
	///
	void DrawDeactiveCaret(double x, double y);

protected:
	///								
	/* virtual */ void DrawSimpleArc(double x, double y,
		double wd, double ht, int arc1, int arc2);
 	///
	/* virtual */ void DrawSimplePolygon(const DPoint *plist,
		int n);
	///
	/* virtual */ void DrawSimpleCurve(const DPoint *p);
	///
	void DrawXRectangle(GC gc, double x, double y,
		double wd, double ht);
	///
	void FillXRectangle(GC gc, double x, double y,
		double wd, double ht);
	///
	void DrawXLine(GC gc, double x1, double y1,
		double x2, double y2);
	///
	void DrawXArc(GC gc, double x, double y,
		double wd, double ht, int arc1, int arc2);
	///
	void FillXArc(GC gc, double x, double y,
		double wd, double ht, int arc1, int arc2);
	///
	void DrawXPolygon(GC gc, const Point *points, int n);
	///								
	void DrawXOpenPolygon(GC gc, const Point *points, int n);	
	///
	void FillXPolygon(GC gc, const Point *points, int n);
	///								
	void DrawXOpenPolygon(GC gc, const DPoint *points, int n);	
	///								
	void FillXPolygon(GC gc, const DPoint *points, int n);	

	/// X graphics context for xor drawing.
	GC CreateXorGC();
	/// X graphics context for copy drawing.
	GC CreateCopyGC();
	/// X gc for drawing xor dotted patterns.
	GC CreateDotGC();
	/// X gc for drawing xor wide dotted patterns.
        GC CreateWideDotGC();
	/// X gc for drawing xor dashed patterns.
	GC CreateDashGC();

	///
	GC GetCopyGC() {return copyGC;}
	///
	GC GetXORGC() {return xorGC;}
	///
	GC GetDotGC() {return dotGC;}
	///
        GC GetWideDotGC() {return wideDotGC;}
	///
	GC GetDashGC() {return dashGC;}

	///
	void ColorInfo();
	///
	void SetDots(GC gc);
	///
	Pixel GetWhitePixel();
	///
	Pixel GetBlackPixel();
	///
	Pixel GetForegroundPixel();
	///
	double Px(double t);
	///
	double Py(double t);
private:
	/// The X window where the drawing area is.
	Window 	window;

	/// The X display.
	Display *display;

	/// The width of the drawing area.
	double width;

	/// The height of the drawing area.
	double height;

	/// pixmap for redrawing on exposure
	Pixmap rdPixmap;

	/// copy GC (Graphic Context). (see Xlib reference man.) 
	GC copyGC;
	/// solid xor GC.
	GC xorGC;
	/// dotted xor GC
	GC dotGC;
	/// wide dotted xor GC
        GC wideDotGC;
	/// dashed xor GC
	GC dashGC;

	/// number of points for approximating a curve.
	enum {CURVE_POINTS = 21};

	/// X colormap.
	Colormap colormap;

	///
	enum {PATTERNLEN = 8};

	/// dot pattern (for EditText)
	char grayPattern[PATTERNLEN];

	///
	bool whitePixelWarned;
	///
	bool blackPixelWarned;

	// Utils for drawing curves.
	///
	double px0, px1, px2, px3;
	///
	double py0, py1, py2, py3;
	///
//	double xx[CURVE_POINTS];
	///
//	double yy[CURVE_POINTS];
};
#endif
