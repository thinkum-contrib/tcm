////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl).
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
#include "figgrafport.h"
#include "application.h"
#include <ctype.h>
#include <math.h>

// Factor for X coordinates to Fig coordinates.
// X display : 1 dot = 1/80 inch
// X Fig     : 1 dot = 1/1200 inch
// const double FigGrafport::F = 1200/80;
// const double FigGrafport::F = 14.4578;
const double FigGrafport::F = 15;
#define deg2rad (M_PI / 180.0)

FigGrafport::FigGrafport(const char *fileName): Grafport() {
	if (equal(fileName, ""))
		fd = stdout;
	else
		fd = fopen(fileName, "w");
	succes = (fd != 0);
	penColor = -1;
	fillColor = -1;
	psFont = -1;
	texFont = 0;
	texFonts = False;
	InitColors();
}

FigGrafport::~FigGrafport() {
	if (succes)
		fclose(fd);
}

void FigGrafport::InitColors() {
	// add standard Xfig colors.
	// "pixel"-value is misused as xfig color key.
	AddColor("black", 0);
	AddColor("blue", 1);
	AddColor("green", 2);
	AddColor("cyan", 3);
	AddColor("red", 4);
	AddColor("magenta", 5);
	AddColor("yellow", 6);
	AddColor("white", 7);
	// here could come standard colors 8-30 (is not necessary).
	AddColor("gold", 31);

	int n = 32; // user defined colors are from 32 till 543.
	List<Color *> *appColors = theApplication->GetColors();
        for (appColors->first(); !appColors->done(); appColors->next()) {
		// define other colors as user defined colors.
		if (!LookupColor(&appColors->cur()->name)) {
			Color *color = new Color(*appColors->cur());
                	color->pixel = n; 
                	color->allocated = True;
                	GetColors()->add(color);
			n++;
			if (n > 543) {
				error("%s, line %d: "
				      "too many user defined colors"
					__FILE__, __LINE__);
				break;
			}
		}

	}
}

void FigGrafport::SetBackgroundColor(const char *c) {
        string s = c;
        SetBackgroundColor(&s);
}
 
void FigGrafport::SetForegroundColor(const char *c) {
        string s = c;
        SetForegroundColor(&s);
}
 
void FigGrafport::SetBackgroundColor(const string *c) {
	if (*GetBackgroundColor() == *c)
		return;
	Grafport::SetBackgroundColor(c);
}

void FigGrafport::SetForegroundColor(const string *c) {
	if (*GetForegroundColor() == *c)
		return;
	Grafport::SetForegroundColor(c);
	Color *color = LookupColor(c);
	if (color)
		penColor = (int)color->pixel;
	else
		penColor = -1; // default.
}

void FigGrafport::Header(bool landscape) {
	fprintf(fd, "#FIG 3.1\n");
	if (landscape)
		fprintf(fd, "Landscape\n");
	else
		fprintf(fd, "Portrait\n");
	fprintf(fd, "Center\n");
	fprintf(fd, "Inches\n");
	fprintf(fd, "1200 2\n");

	// write user defined colors.
	int object_code = 0; // color pseudo object code.
	List<Color *> *c = GetColors();
	for (c->first(); !c->done(); c->next()) {
		Color *color = c->cur();
		if (color->pixel >= 32) {
			int r= int(255*color->red);
			int g= int(255*color->green);
			int b= int(255*color->blue);
			fprintf(fd, "%d %d #", object_code, (int)color->pixel);
			fprintf(fd, "%.2x%.2x%.2x\n", r, g, b);
		}
	}
}

void FigGrafport::SetLineWidth(unsigned int w) {
	if (w == GetLineWidth())
		return;
	Grafport::SetLineWidth(w);
}

void FigGrafport::SetFont(XFont *f) {
	Grafport::SetFont(f);
	SetPSFont();
	SetTexFont();
}

void FigGrafport::DrawFigEllipse(double center_x, double center_y,
	double radius_x, double radius_y, int sub_type)
{
	int object_code = 1;  // Ellipse

	int line_style = 0;  // Solid
	if (GetLineStyle()==LineStyle::DASHED)
	 	line_style = 1;
	if (GetLineStyle()==LineStyle::DOTTED ||
	    GetLineStyle()==LineStyle::WIDE_DOTTED)
	 	line_style = 2;

	int thickness = GetLineWidth();  // 1/80 inch
	if (GetLineStyle()==LineStyle::INVISIBLE &&
	    GetFillStyle()==FillStyle::UNFILLED)
		return; // don't draw

	int pen_color = penColor;
	int fill_color = 7; // 7 = white
	int depth = 0;
	int pen_style = 0;  // not used.
	int area_fill = -1; // no fill.
	if (GetFillStyle()==FillStyle::FILLED) {
		fill_color = fillColor;
		area_fill = 20;// full saturation.
		if (GetLineStyle()==LineStyle::INVISIBLE)
			pen_color = fill_color;
	} 

	float style_val = 0;// 1/80 inch
	if (GetLineStyle()==LineStyle::DASHED)
	 	style_val = 4.0;
	if (GetLineStyle()==LineStyle::DOTTED)
	 	style_val = 1.0;
	if (GetLineStyle()==LineStyle::WIDE_DOTTED)
	 	style_val = 2.0;

	int direction = 1; // always 1
	float angle = 0;   // angle with x-axis.
	double start_x = center_x;
	double start_y = center_y;
	double end_x = start_x + radius_x;
	double end_y = start_y + radius_y;

	fprintf(fd, "%d %d %d %d %d %d %d %d %d ", object_code, sub_type,
		line_style, thickness, pen_color, fill_color, depth,
		pen_style, area_fill);
	fprintf(fd, "%f %d %f %.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f\n",
		style_val, direction, angle, center_x, center_y, radius_x,
		radius_y, start_x, start_y, end_x, end_y);
}


void FigGrafport::DrawFigPolyLine(List<DPoint *> *points,
				  int sub_type, double radius) {
	int object_code = 2; // Polyline

	int line_style = 0;  // Solid
	if (GetLineStyle()==LineStyle::DASHED)
	 	line_style = 1;
	if (GetLineStyle()==LineStyle::DOTTED ||
	    GetLineStyle()==LineStyle::WIDE_DOTTED)
	 	line_style = 2;

	int thickness = GetLineWidth();  // 1/80 inch
	if (GetLineStyle()==LineStyle::INVISIBLE &&
            GetFillStyle()==FillStyle::UNFILLED)
		return;
	 	// thickness = 0;

	int pen_color = penColor;
	int fill_color = 7; // 7 = white
	int depth = 0;
	int pen_style = 0;  // not used.
	int area_fill = -1; // no fill.
	if (GetFillStyle()==FillStyle::FILLED) {
		fill_color = fillColor;
		area_fill = 20;// full saturation.
		if (GetLineStyle()==LineStyle::INVISIBLE)
			pen_color = fill_color;
	}

	float style_val = 0;// 1/80 inch
	if (GetLineStyle()==LineStyle::DASHED)
	 	style_val = 4.0;
	if (GetLineStyle()==LineStyle::DOTTED)
	 	style_val = 1.0;
	if (GetLineStyle()==LineStyle::WIDE_DOTTED)
	 	style_val = 2.0;

	int join_style = 0; // Miter
	int cap_style = 0;  // Butt
	int forward_arrow = 0;
	int backward_arrow = 0;
	int npoints = points->count();

	fprintf(fd, "%d %d %d %d %d %d %d %d %d %.1f %d %d %.0f %d %d %d\n",
		object_code, sub_type, line_style, thickness, pen_color,
		fill_color, depth, pen_style, area_fill, style_val,
		join_style, cap_style, radius, forward_arrow, backward_arrow,
		npoints);
	for (points->first(); !points->done(); points->next()) {
		DPoint *pt = points->cur();
		fprintf(fd, "%.0f %.0f ", pt->x, pt->y);
	}
	fprintf(fd, "\n"); 
}

void FigGrafport::DrawFigRectangle(double _x, double _y, double _wd, double _ht,
				   int sub_type, double radius) {
	double x = Zoom(_x); 
	double y = Zoom(_y);
	double wd = Zoom(_wd);
	double ht = Zoom(_ht);

	List<DPoint *> points;

	double xl = x*F;
	double yt = y*F;
	double xr = (x+wd)*F;
	double yb = (y+ht)*F;
	DPoint p1(xl, yt);
	DPoint p2(xl, yb);
	DPoint p3(xr, yb);
	DPoint p4(xr, yt);
	points.add(&p1);
	points.add(&p2);
	points.add(&p3);
	points.add(&p4);
	points.add(&p1);

	DrawFigPolyLine(&points, sub_type, radius);

	if (GetLineStyle()==LineStyle::DUAL) {
		SetLineStyle(LineStyle::SOLID); // avoid recursion
	 	int n = 2*GetLineWidth();
		if (_ht > 2*n && _wd > 2*n)
	 		DrawFigRectangle(_x+n, _y+n, _wd-2*n, _ht-2*n, 
				sub_type, radius);
		SetLineStyle(LineStyle::DUAL);
	}
}

void FigGrafport::DrawRectangle(double x, double y, double wd, double ht) {
	DrawFigRectangle(x, y, wd, ht, 2);
	SetFillStyle(FillStyle::UNFILLED);
}

void FigGrafport::DrawUnzoomedRectangle(double x, double y, double wd, double ht) {
	DrawFigRectangle(ZoomCorrect(x), ZoomCorrect(y),
		      ZoomCorrect(wd), ZoomCorrect(ht), 2);
}

void FigGrafport::FillRectangle(double, double, double, double) {
	SetFillStyle(FillStyle::FILLED);
	SetFillColor();
}

//void FigGrafport::DrawRoundedRectangle(double x, double y, double wd, double ht, double rd) {
//	DrawFigRectangle(x, y, wd, ht, 4, rd);
//	SetFillStyle(FillStyle::UNFILLED);
//}
//
//void FigGrafport::FillRoundedRectangle(double, double, double, double, double) {
//	SetFillStyle(FillStyle::FILLED);
//	SetFillColor();
//}
//
//void FigGrafport::DrawEllipsedRectangle(double x, double y, double wd, double ht, double rd) {
//	DrawRoundedRectangle(x, y, wd, ht, rd);
//}
//
//void FigGrafport::FillEllipsedRectangle(double, double, double, double, double) {
//	SetFillStyle(FillStyle::FILLED);
//	SetFillColor();
//}
//
//void FigGrafport::DrawDisk(double x, double y, double wd, double ht, double el) {
//	// draw two lines (without the corner points).
//        double ah = el/2;
//        DrawLine(x, y+ah+1, x, y+ht-ah-1);
//        DrawLine(x+wd, y+ah+1, x+wd, y+ht-ah-1);
//        // draw 1st ellipse.
//        DrawEllipse(x, y, wd, el+1);
//        // draw bottom arc (in two parts)
//	DrawArc(x, y + ht - el - 1, wd, el + 1, 180, 270);
//	DrawArc(x, y + ht - el - 1, wd, el + 1, 270, 360);
//}
//
//void FigGrafport::FillDisk(double, double, double, double, double) {
//	SetFillStyle(FillStyle::FILLED);
//	SetFillColor();
//}

void FigGrafport::DrawFigText(double px, double py, const char *str, int sub_type) {
	px = Zoom(px);
	py = Zoom(py);
	int object_code = 4;  // Text
	int color = penColor;
	int depth = 0;
	int pen_style = 0;  // not used.
	int figfont;
	if (texFonts)
		figfont = texFont; // generate LaTeX fonts.
	else
		figfont = psFont;  // generate PostScript fonts.
	float font_size = GetFont()->GetSize() - 0.1; // possibly some 
	float angle = 0; 	    // problems with 'autoresize'.
	int font_flags;
	if (texFonts)
		font_flags = 2;
	else
		font_flags = 4;
	double theight, tlength;
	GetFigStringSize(str, theight, tlength);
	double x, y;
	if (sub_type == 0) {	  // lower left (was topleft)
		x = F*px;
		y = F*py;
	}
	else if (sub_type == 1) { // lower center (was center)
		x = F*px;
		y = F*py + theight/2;
	}
	else {   		 // lower right (was topright)
		x = F*px;
		y = F*py;
	}
	string theString = str;
	MakeFigString(&theString);
	fprintf(fd, "%d %d %d %d %d %d %f %f %d %f %f %.0f %.0f %s\n",
		object_code, sub_type, color, depth, pen_style,
		figfont, font_size, angle, font_flags, theight,
		tlength, x, y, theString.getstr());
}

void FigGrafport::DrawStringLeft(double x, double y, const char *str) {
	DrawFigText(x, y, str, 0);
}

void FigGrafport::DrawUnzoomedStringLeft(double x, double y, const char *str) {
	DrawStringLeft(ZoomCorrect(x), ZoomCorrect(y), str);
}

void FigGrafport::DrawStringRight(double x, double y, const char *str) {
	DrawFigText(x, y, str, 2);
}

void FigGrafport::DrawStringCentered(double x, double y, const char *str) {
	DrawFigText(x, y, str, 1);
}

void FigGrafport::DrawUnzoomedStringCentered(double x, double y, const char *str) {
	DrawStringCentered(ZoomCorrect(x), ZoomCorrect(y), str);
}

// Underlined Strings
void FigGrafport::DrawStringRightUnderlined(double x, double y, const char *str) {
	DrawStringRight(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringRight... : 
	// Corrected Height for y ( == topRighty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	LineStyle::Type save = GetLineStyle();	// save
	SetLineStyle(LineStyle::SOLID);		// set underline linestyle SOLID
	DrawLine(x-wd, y+cht, x, y+cht);
	SetLineStyle(save);			// and restore
}

void FigGrafport::DrawStringLeftUnderlined(double x, double y, const char *str) {
	DrawStringLeft(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringLeft... : 
	// Corrected Height for y ( == topLefty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	LineStyle::Type save = GetLineStyle();	// save
	SetLineStyle(LineStyle::SOLID);		// set underline linestyle SOLID
	DrawLine(x, y+cht, x+wd, y+cht);
	SetLineStyle(save);			// and restore
}

void FigGrafport::DrawStringCenteredUnderlined(double x, double y, const char *str) {
	DrawStringCentered(x, y, str);
	int wd = GetFont()->StringWidth(str);
	int ht = GetFont()->GetHeight();
	LineStyle::Type save = GetLineStyle();	// save
	SetLineStyle(LineStyle::SOLID);		// set underline linestyle SOLID
	DrawLine(x-wd/2, y+ht/2, x+wd/2, y+ht/2);
	SetLineStyle(save);			// and restore
}

//void FigGrafport::DrawLine(double _x1, double _y1, double _x2, double _y2) {
//	if (_x1 == _x2 && _y1 == _y2)
//		return;
//
//	double x1 = Zoom(_x1); 
//	double y1 = Zoom(_y1);
//	double x2 = Zoom(_x2);
//	double y2 = Zoom(_y2);
//
//	List<DPoint *> points;
//	int sub_type = 1;
//
//	DPoint p1(F*x1, F*y1);
//	DPoint p2(F*x2, F*y2);
//	points.add(&p1);
//	points.add(&p2);
//
//	DrawFigPolyLine(&points, sub_type);
//
//	if (GetLineStyle()==LineStyle::DUAL) {
//		SetLineStyle(LineStyle::SOLID);
//		int n = GetLineWidth();
//		if (y1 == y2) {  // horizontal
//			DrawLine(_x1, _y1+n, _x2, _y2+n);
//			DrawLine(_x1, _y1-n, _x2, _y2-n);
//		}
//		else if (x1 == x2) {  // vertical
//			DrawLine(_x1+n, _y1, _x2+n, _y2);
//			DrawLine(_x1-n, _y1, _x2-n, _y2);
//		}
//		else {
//			DrawLine(_x1, _y1, _x2, _y2);
//			DrawLine(_x1, _y1+2*n, _x2, _y2+2*n);
//		}
//		SetLineStyle(LineStyle::DUAL);
//	}
//	SetFillStyle(FillStyle::UNFILLED);
//}


void FigGrafport::DrawUnzoomedLine(double x1, double y1, double x2, double y2) {
	DrawLine(ZoomCorrect(x1), ZoomCorrect(y1), 
		 ZoomCorrect(x2), ZoomCorrect(y2));
}


//void FigGrafport::DrawCurve(const Point *p1, const Point *p2, 
//			   const Point *p3, const Point *p4) {
//	int object_code = 3;  // Spline
//	int sub_type = 0;     // Open Aproximated Spline
//
//	double x1 = Zoom(p1->x*F);
//	double y1 = Zoom(p1->y*F);
//	double x2 = Zoom(p2->x*F);
//	double y2 = Zoom(p2->y*F);
//	double x3 = Zoom(p3->x*F);
//	double y3 = Zoom(p3->y*F);
//	double x4 = Zoom(p4->x*F);
//	double y4 = Zoom(p4->y*F);
//
//	int line_style = 0;  // Solid
//	if (GetLineStyle()==LineStyle::DASHED)
//	 	line_style = 1;
//	if (GetLineStyle()==LineStyle::DOTTED ||
//	    GetLineStyle()==LineStyle::WIDE_DOTTED)
//	 	line_style = 2;
//
//	int thickness = GetLineWidth();  // 1/80 inch
//	if (GetLineStyle()==LineStyle::INVISIBLE)
//		return;
//	 	// thickness = 0;
//
//	int pen_color = penColor;
//	int fill_color = 7; // 7 = white
//	int depth = 0;
//	int pen_style = 0;  // not used.
//	int area_fill = -1; // no fill.
//	if (GetFillStyle()==FillStyle::FILLED) {
//		fill_color = fillColor;
//		area_fill = 20;// full saturation.
//	} 
//
//	float style_val = 0;// 1/80 inch
//	if (GetLineStyle()==LineStyle::DASHED)
//	 	style_val = 4.0;
//	if (GetLineStyle()==LineStyle::DOTTED)
//	 	style_val = 1.0;
//	if (GetLineStyle()==LineStyle::WIDE_DOTTED)
//	 	style_val = 2.0;
//
//	int cap_style = 0;  // Butt
//	int forward_arrow = 0;
//	int backward_arrow = 0;
//	int npoints = 4;
//
//	fprintf(fd, "%d %d %d %d %d %d %d %d %d %.1f %d %d %d %d\n",
//		object_code, sub_type, line_style, thickness, pen_color,
//		fill_color, depth, pen_style, area_fill, style_val,
//		cap_style, forward_arrow, backward_arrow,
//		npoints);
//	fprintf(fd, "%f %f %f %f %f %f %f %f\n",
//		x1, y1, x2, y2, x3, y3, x4, y4);
//	SetFillStyle(FillStyle::UNFILLED);
//}


void FigGrafport::FillCurve(const DPoint *p) {
	// 3 = object code: spline, 0 = subtype: open approximated, 0 = line
	// style: solid, 0 = thickness, 0 = pen color: default, 50 = depth, 0 =
	// pen style (not used), 20 = area fill: filled, 0.0 = style val: no
	// dots, 0 = cap style: butt, 0 = forward arrow: none, 0 = backward
	// arrow: none, 4 = # of points
	fprintf(fd, "3 0 0 0 0 %d 50 0 20 0.0 0 0 0 4\n", penColor);
	fprintf(fd, "%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f\n",
		Zoom(p[0].x * F), Zoom(p[0].y * F),
		Zoom(p[1].x * F), Zoom(p[1].y * F),
		Zoom(p[2].x * F), Zoom(p[2].y * F),
		Zoom(p[3].x * F), Zoom(p[3].y * F));
}


void FigGrafport::DrawSimpleCurve(const DPoint *p) {
	int line_style;
	double style_val;
	switch ( GetLineStyle() ) {
	case LineStyle::INVISIBLE:
		return;
	case LineStyle::DASHED:
		line_style = 1;
		style_val = 4.0;
		break;
	case LineStyle::DOTTED:
		line_style = 2;
		style_val = 1.0;
		break;
	case LineStyle::WIDE_DOTTED:
		line_style = 2;
		style_val = 2.0;
		break;
	default:
		line_style = 0;
		style_val = 0.0;
		break;
	}
	// 3 = object code: spline, 0 = subtype: open approximated, 7 = fill
	// color: white, 0 = depth, 0 = pen style (not used), -1 = area fill:
	// not filled, 0 = cap style: butt, 0 = forward arrow: none, 0 =
	// backward arrow: none, 4 = # of points.
	fprintf(fd, "3 0 %d %d %d 7 0 0 -1 %.1f 0 0 0 4\n",
		line_style, GetLineWidth(), penColor, style_val);
	fprintf(fd, "%.0f %.0f %.0f %.0f %.0f %.0f %.0f %.0f\n",
		Zoom(p[0].x * F), Zoom(p[0].y * F),
		Zoom(p[1].x * F), Zoom(p[1].y * F),
		Zoom(p[2].x * F), Zoom(p[2].y * F),
		Zoom(p[3].x * F), Zoom(p[3].y * F));
}


void FigGrafport::DrawPoint(double, double) { 
	// no single points in Xfig
}


static void CalcCurvePoints(DPoint *p, double x, double y,
	double wd, double ht, int a1)
{
	/* calculate points for a spline approximating a
	   quarter of an ellipse. */
	wd *= 0.5;
	x += wd;
	ht *= 0.5;
	y += ht;
	switch ( a1 ) {
	case 0:
		ht = -ht;
		break;
	case 90:
		ht = -ht;
	case 180:
		wd = -wd;
		break;
	}
	p[0].Set(x + wd, y);
#define Factor 1
// 1 is an estimation, not based on any algorithm...
// 4.0/3 = Bézier approximation, but this is too large for B-splines.
	p[1].Set(x + wd, y + ht * ((M_SQRT2 - 1.0) * Factor));
	p[2].Set(x + wd * ((M_SQRT2 - 1.0) * Factor), y + ht);
	p[3].Set(x, y + ht);
}


void FigGrafport::DrawSimpleArc(double x, double y,
	double wd, double ht, int a1, int a2)
{
	if ( ! (int) (F * Zoom(wd - ht) + 0.5) ) {
		/* (almost) circular arc */
		int line_style;
		double style_val;
		switch ( GetLineStyle() ) {
		case LineStyle::INVISIBLE:
			return;
		case LineStyle::DASHED:
			line_style = 1;
			style_val = 4.0;
			break;
		case LineStyle::DOTTED:
			line_style = 2;
			style_val = 1.0;
			break;
		case LineStyle::WIDE_DOTTED:
			line_style = 2;
			style_val = 2.0;
			break;
		default:
			line_style = 0;
			style_val = 0.0;
			break;
		}
		double radius = Zoom((wd + ht) * (F / 4.0));
		DPoint centre(Zoom(x + wd * 0.5) * F,
			Zoom(y + ht * 0.5) * F);
		// 5 = object code: arc, 1 = subtype: open, 7 = fill colour:
		// white, 0 = depth, 0 = pn style (not used), -1 = area fill:
		// not filled, 0 = cap style: butt, 1 = ???,
		// 0 = forward arrow: none, 0 = backward arrow: none
		fprintf(fd, "5 1 %d %d %d 7 0 0 -1 %.1f 0 1 0 0",
			line_style, GetLineWidth(), penColor,
			style_val);
		fprintf(fd, " %f %f", centre.x, centre.y);
		double arc1 = a1 * deg2rad;
		fprintf(fd, " %.0f %.0f", centre.x + radius * cos(arc1),
					 centre.y - radius * sin(arc1));
		double arc3 = (deg2rad / 2.0) * (a1 + a2);
		fprintf(fd, " %.0f %.0f", centre.x + radius * cos(arc3),
					 centre.y - radius * sin(arc3));
		double arc2 = a2 * deg2rad;
		fprintf(fd, " %.0f %.0f\n", centre.x+radius * cos(arc2),
					 centre.y - radius * sin(arc2));
	} else {
		/* elliptic arc: approximate by a curve */
		DPoint p[4];
		CalcCurvePoints(p, x, y, wd, ht, a1);
		DrawSimpleCurve(p);
	}
}


void FigGrafport::FillSegment(double x, double y, double wd, double ht,
	int a1, int a2)
{
	if ( ! (int) (F * Zoom(wd - ht) + 0.5) ) {
		/* (almost) circular arc */
		double radius = Zoom((wd + ht) * (F / 4.0));
		DPoint centre(Zoom(x + wd * 0.5) * F,
			Zoom(y + ht * 0.5) * F);
		// 5 = object code: arc, 1 = subtype: open, 0 = line style:
		// solid, 0 = line width, 0 = pen color: default, 50 = depth,
		// 0 = pen style (not used), 20 = area fill: filled, 0.0 =
		// style value: no dots, 0 = cap style: butt, 1 = ???,
		// 0 = forward arrow: none, 0 = backward arrow: none
		fprintf(fd, "5 1 0 0 0 %d 50 0 20 0.0 0 1 0 0",
			penColor);
		fprintf(fd, " %f %f", centre.x, centre.y);
		double arc1 = a1 * deg2rad;
		fprintf(fd, " %.0f %.0f", centre.x + radius * cos(arc1),
					 centre.y - radius * sin(arc1));
		double arc3 = (deg2rad / 2.0) * (a1 + a2);
		fprintf(fd, " %.0f %.0f", centre.x + radius * cos(arc3),
					 centre.y - radius * sin(arc3));
		double arc2 = a2 * deg2rad;
		fprintf(fd, " %.0f %.0f\n", centre.x+radius * cos(arc2),
					 centre.y - radius * sin(arc2));
	} else {
		/* elliptic arc: approximate by a curve */
		DPoint p[4];
		CalcCurvePoints(p, x, y, wd, ht, a1);
		FillCurve(p);
	}
}


//void FigGrafport::FillArc(double, double, double, double, int, int) {
//	/* Actually, this procedure is not implemented correctly; arcs
//	   are never filled as pie slices, but always as segments. dj */
//	SetFillStyle(FillStyle::FILLED);
//	SetFillColor();
//}

void FigGrafport::DrawEllipse(double x, double y, double wd, double ht) {
	int sub_type;
	if (wd == ht)
		sub_type = 3; // circle def. by radius.
	else
		sub_type = 1; // ellipse def. by radius.
	double radius_x = (wd*F)/2;
	double radius_y = (ht*F)/2;
	double center_x = x*F + radius_x;
	double center_y = y*F + radius_y;
	DrawFigEllipse(center_x, center_y, radius_x, radius_y, sub_type);
	if (GetLineStyle()==LineStyle::DUAL) {
		SetLineStyle(LineStyle::SOLID); // avoid recursion
	 	int n = 2*GetLineWidth();
		if (ht > 2*n && wd > 2*n)
	 		DrawEllipse(x+n, y+n, wd-2*n, ht-2*n);
		SetLineStyle(LineStyle::DUAL);
	}
	SetFillStyle(FillStyle::UNFILLED);
}

void FigGrafport::FillEllipse(double, double, double, double) {
	SetFillStyle(FillStyle::FILLED);
	SetFillColor();
}

void FigGrafport::DrawPolygon(const Point *p, int n) {
	if (n < 1)
		return;
	List<DPoint *> points;
	int sub_type = 3;

	for (int i=0; i<n; i++) {
		double x = F*Zoom(p[i].x);
		double y = F*Zoom(p[i].y);
		DPoint *pt = new DPoint(x, y);
		points.add(pt);
	}
	DPoint *pt = new DPoint(F*Zoom(p[0].x), F*Zoom(p[0].y));
	points.add(pt);

	DrawFigPolyLine(&points, sub_type);
	if (GetLineStyle()==LineStyle::DUAL) {
		int w = 2*GetLineWidth();
                Point *oldPoints = new Point[n];
                Point *newPoints = new Point[n];
		for (int j=0; j<n; j++)
			oldPoints[j] = *points[j];
                RecalcPolygon(oldPoints, n, newPoints, w);
		List<DPoint *> nPoints;
		for (int k=0; k<n; k++)
			nPoints.add(new DPoint(newPoints[k]));
                DrawFigPolyLine(&nPoints, sub_type);
                delete [/* n */] newPoints;
                delete [/* n */] oldPoints;
		nPoints.clear();
	}
	points.clear();
	SetFillStyle(FillStyle::UNFILLED);
}

void FigGrafport::FillPolygon(const Point *p, int n) {
	if ( n < 2 )
		return;
	DPoint *plist = new DPoint [n];
	for ( int i = n ; i-- ; )
		plist[i] = p[i];
	FillPolygon(plist, n);
}


void FigGrafport::FillPolygon(const DPoint *p, int n) {
	if (n < 2)
		return;
	if ( p[0] == p[n - 1] )
		n--;
	// 2 = type: polyline, 1 = subtype: open, 0 = line style: solid, 0 =
	// line width, -1 = pen colour: default, 50 = depth, 0 = pen style
	// (not used), 20 = area fill: filled, 0.0 = style val: no dots, 0 =
	// join style: miter, 0 = cap style: butt, -1 = radius: no round
	// corners, 0 = forward arrow: none, 0 = backward arrow: none
	fprintf(fd, "2 1 0 0 -1 %d 50 0 20 0.0 0 0 -1 0 0 %d\n",
		penColor, n);
	for (int i = 0 ; i < n ; i++ ) {
		fprintf(fd, "%.0f %.0f ",
			Zoom(p[i].x * F), Zoom(p[i].y * F));
	}
	fprintf(fd, "\n");
}


/* virtual */ void FigGrafport::DrawSimplePolygon(const DPoint *p,
	int n)
{
	if (n < 2)
		return;
	int line_style;
	double style_val;
	switch ( GetLineStyle() ) {
	case LineStyle::INVISIBLE:
		return;
	case LineStyle::DASHED:
		line_style = 1;
		style_val = 4.0;
		break;
	case LineStyle::DOTTED:
		line_style = 2;
		style_val = 1.0;
		break;
	case LineStyle::WIDE_DOTTED:
		line_style = 2;
		style_val = 2.0;
		break;
	default:
		line_style = 0;
		style_val = 0.0;
		break;
	}
	int sub_type = 1; // open polyline
	if ( p[0] == p[n - 1] )
		sub_type = 3; // closed polyline
	// 2 = type: polyline, 7 = fill colour: white, 0 = depth, 0 = pen style
	// (not used), -1 = area fill: none, 0 = join style: miter, 0 = cap
	// style: butt, -1 = radius: no round corners, 0 = forward arrow: none,
	// 0 = backward arrow: none
	fprintf(fd, "2 %d %d %d %d 7 0 0 -1 %.1f 0 0 -1 0 0 %d\n",
		sub_type, line_style, GetLineWidth(), penColor,
		style_val, n);
	for (int i = 0 ; i < n ; i++ ) {
		fprintf(fd, "%.0f %.0f ",
			Zoom(p[i].x * F), Zoom(p[i].y * F));
	}
	fprintf(fd, "\n");
}


void FigGrafport::MakeFigString(string *str) {
	char buf[8];
	string newstr;
	for (unsigned i=0; i<str->length(); i++) {
		unsigned char c = (*str)[i];
		if (!isascii(c)) {
			sprintf(buf, "\\%o", c);
			newstr += buf;
		}
		else if (c == '\\') {
			newstr.add(c);
			newstr.add(c);
		}
		else
			newstr.add(c);
	}
	newstr += "\\001";
	*str = newstr;
}

void FigGrafport::SetFillColor() {
	Color *color = LookupColor(GetForegroundColor());
        if (color)
                fillColor = (int)color->pixel;
        else
                fillColor = -1; // default.
}

void FigGrafport::GetFigStringSize(const char *str, double &ht, double &wd) {
	XCharStruct overall;
	int dir, asc, desc;
	int nchars = strlen(str);
	XTextExtents(GetFont()->GetXFontStruct(),
		(char *)str, nchars, &dir, &asc, &desc, &overall);
	ht = F * (overall.ascent + overall.descent);
	wd = F * overall.width;
}

void FigGrafport::SetPSFont() {
	XFont *f = GetFont();
	int fam = f->GetFamily();
	if (fam == XFont::HELVETICA)
		psFont = 16;
	else if (fam == XFont::TIMESROMAN)
		psFont = 0;
	else if (fam == XFont::COURIER)
		psFont = 12;
	else if (fam == XFont::NEWCENTURYSCHLBK)
		psFont = 24;
	else if (fam == XFont::SYMBOL) {
		psFont = 32;
		return;
	}
	if (f->IsItalic())
		psFont += 1;
	if (f->IsBold())
		psFont += 2;
}

void FigGrafport::SetTexFont() {
	XFont *f = GetFont();
	texFont = 1;
	if (f->IsBold())
		texFont += 1;
	if (f->IsItalic())
		texFont += 2;
	int fam = f->GetFamily();
	if (fam == XFont::COURIER)
		texFont = 5;
}
