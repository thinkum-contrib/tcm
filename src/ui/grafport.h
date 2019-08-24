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
#ifndef _GRAFPORT_H 
#define _GRAFPORT_H

#include "rectangle.h"
#include "lstring.h"
#include "xfont.h"
#include "linestyle.h"
#include "fillstyle.h"
#include "llist.h"
#include "color.h"
#include "dpoint.h"

/// (abstract) grafport class (primitive drawing functions).
class Grafport {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	Grafport();
	///
	virtual ~Grafport();

	///
	virtual bool DrawsXor() {return False;}

// Sizes, refreshment.
	///
	virtual void ClearArea(double x, double y,
		double wd, double ht)=0;
	///
	virtual void UpdateSize(double, double) {;}
	///
	virtual double GetWidth() {return 0;}
	///
	virtual double GetHeight() {return 0;}
	///
	virtual void Redraw(double, double, double, double,
		double, double) {;}

// Fonts
	/// Make this the current font.
	virtual void SetFont(XFont *f) {font = f;}
	/// Get the current font.
	XFont *GetFont() {return font;}

// Colors
	///
	virtual void SetBackgroundColor(const char *colorName)
		{backgroundColor = colorName;}
	///
	virtual void SetBackgroundColor(const string *colorName)
		{backgroundColor = *colorName;}
	///
	virtual void SetForegroundColor(const char *colorName)
		{foregroundColor = colorName;}
	///
	virtual void SetForegroundColor(const string *colorName) 
		{foregroundColor = *colorName;}
	///
	const string *GetBackgroundColor() {return &backgroundColor;}
	///
	const string *GetForegroundColor() {return &foregroundColor;}

	///
	List<Color *> *GetColors() {return colors;}

// Line styles.
	///
	void SetLineStyle(LineStyle::Type s) {lineStyle=s;}
	///
	LineStyle::Type GetLineStyle() {return lineStyle;}

// Fill styles.
	///
	void SetFillStyle(FillStyle::Type s) {fillStyle=s;}
	///
	FillStyle::Type GetFillStyle() {return fillStyle;}

// Line width.
	///
	virtual void SetLineWidth(unsigned n) {lineWidth=n;}
	///
	unsigned GetLineWidth() {return lineWidth;}

/// Zooming in/out.
	/// set zoom value.
	void SetZoomValue(double newValue) {zoomValue = newValue;}
	///
	double GetZoomValue() {return zoomValue;}
	///
	double Zoom(double x) {return x * zoomValue;}
	///
	double ZoomCorrect(double x) {return x / zoomValue;}

	// All draw functions, except those called 'Edit', are printable
	// (are exported to Postscript etc.)
	// All draw functions, except those called 'Edit' or 'Unzoomed' are 
	// zoomed.

// Drawing Rectangles.
	///
	virtual void DrawRectangle(double x, double y,
		double wd, double ht)=0;
	///
	virtual void FillRectangle(double x, double y,
		double wd, double ht)=0;

	/// Draw list of n rectangles.
	void DrawRectangles(const Rectangle *rects, int n);
	///
	void FillRectangles(const Rectangle *rects, int n);

	/// Draw dashed rectangle (not zoomed, not printed)
	virtual void DrawEditDashedRectangle(double, double, double, double) {;}
	///
	virtual void DrawUnzoomedRectangle(double, double, double, double) = 0;

// Drawing Strings
	/// Draw string with topleft at (x,y)
	virtual void DrawStringLeft(double x, double y,
		const char *str)=0;

	/// Draw string centered at (x,y)
	virtual void DrawStringCentered(double x, double y,
		const char *str)=0;

	/// Draw string with topright at (x,y)
	virtual void DrawStringRight(double x, double y,
		const char *str)=0;

	/// Draw string with topleft underlined at (x,y)
	virtual void DrawStringLeftUnderlined(double x, double y,
		const char *str)=0;

	/// Draw string centered underlined at (x,y)
	virtual void DrawStringCenteredUnderlined(double x, double y,
		const char *str)=0;

	/// Draw string with topright underlined at (x,y)
	virtual void DrawStringRightUnderlined(double x, double y,
		const char *str)=0;

	/// Draws n-line string centered (underlined?) at (x,y),
	/// returns cursor position.
	Point DrawStringsCentered(double x, double y,
		const string *str, bool ul, int cursor=0);

	/// draw n-line string left aligned, returns cursor position.
	Point DrawStringsLeft(double topLeftx, double topLefty,
		const string *str, bool ul, int cursor=0);

	/// draw n-line string right aligned, return cursor position.
	Point DrawStringsRight(double topRightx, double topRighty,
		const string *str, bool ul, int cursor=0);

	/// return cursor place closest to hitX, hitY.
	unsigned CursorPosition(double x, double y,
		const string *str, double hitX, double hitY);

	///
	virtual void DrawUnzoomedStringLeft(double, double, const char *)=0;
	///
	virtual void DrawUnzoomedStringCentered(double, double, const char *)=0;

// Drawing Lines
	/// Draw a line from (x1,y1) to (x2,y2).
	void DrawLine(double x1, double y1,
		double x2, double y2);

	/// Draw a Bézier curve with 4 points.				
	void DrawCurve(const DPoint *p);				

	/// not zoomed not printed.
	virtual void DrawEditLine(double, double, double, double) {;}

	/// not zoomed or printed. Uses special dot pattern.
	virtual void DrawEditDottedGridLine(double, double, double, double) {;}
	///
	virtual void DrawEditDottedLine(double, double, double, double) {;}

	/// not zoomed or printed.
	virtual void DrawEditPoint(double, double) {;}

	///
	virtual void DrawUnzoomedLine(double, double, double, double) = 0;

// Drawing Points
	///
	virtual void DrawPoint(double x, double y)=0;
// Drawing Ellipses
	// used in lineend.c
	///
	void DrawEllipse(double x, double y,
		double wd, double ht) { DrawArc(x, y, wd, ht, 0, 360); }
	///
	void FillEllipse(double x, double y,
		double wd, double ht) { FillSegment(x, y, wd, ht, 0, 360); }

// Drawing Arcs
	/// Draw an arc. (x,y) = top left of the corresponding ellipse,
	/// (w,h) = size of the corresponding ellipse, arc1 = start angle,
	/// arc2 = end angle (°, 3 o'clock position = 0, counterclockwise)
	void DrawArc(double x, double y,			
		double w, double h, int arc1, int arc2);

	virtual void FillSegment(double x, double y,	
		double wd, double ht, int arc1, int arc2)=0;

// Drawing Polygons
	/// Draw a closed polygon with n edges.
	virtual void DrawPolygon(const Point *points, int n) = 0;
	/// Draw an open polygon between points[0]...points[n-1] with n-1
	/// edges.
	void DrawOpenPolygon(const DPoint *points, int n);		
	///
	virtual void FillPolygon(const Point *plist, int n)=0;
	///								
	virtual void FillPolygon(const DPoint *plist, int n)=0;	

// Drawing text edit cursors.
	/// Draw active cursor sign.
	virtual void DrawActiveCaret(double, double) {;}

	/// Draw deactive cursor sign.
	virtual void DrawDeactiveCaret(double, double) {;}

protected:
	///
	Point CursorPosition(double x, double y, const string *buf,
		int cursor);

	///
        Color *LookupColor(const string *colorName);
	///
        Color *LookupColor(const char *colorName);
	///
	void AddColor(const string *colorName, unsigned long pixel);
	///
	void AddColor(const char *colorName, unsigned long pixel);
	///
	void AddColor(Color *c);

	///
	virtual void InitColors();

	///
	void RecalcPolygon(const Point *points, int nrPoints, 
			   Point *newPoints, int d);

	/// Draw an arc (one line, neglect line style DUAL).		
	virtual void DrawSimpleArc(double x, double y,	
		double w, double h, int arc1, int arc2) = 0;
	/// Draw an open polygon (one line, neglect line style DUAL).	
	virtual void DrawSimplePolygon(const DPoint *points, int n)	
		= 0;							
	/// Draw a curve (one line, neglect line style DUAL).		
	virtual void DrawSimpleCurve(const DPoint *points) = 0;	

private:
	/// Current font.
	XFont *font;

	/// Default font.
	XFont *defaultFont;

	/// Current background color.
	string backgroundColor;

	/// Current foreground color.
	string foregroundColor;

	/// current line width.
	unsigned lineWidth;

	/// current line style.
	LineStyle::Type lineStyle;

	/// current fill style.
	FillStyle::Type fillStyle;

	/// current zoom value.
	double zoomValue;

	///
	string buf;

	/// a cache for the colors.
        List<Color *> *colors;
};
#endif
