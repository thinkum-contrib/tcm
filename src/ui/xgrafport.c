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
#include "xgrafport.h"
#if !defined(__GNUC__)
#include <sysent.h>
#endif
#include <stdio.h>

#define round(x) ((int)((x)+0.5))

XGrafport::XGrafport(Display *d, Window win, double wd, double ht)
:Grafport() {
	display = d;
	window = win;
	width = wd;
	height = ht;
	whitePixelWarned = False;
	blackPixelWarned = False;
	XWindowAttributes attr;
	(void)XGetWindowAttributes(display, window, &attr);
	colormap = attr.colormap;
	// colormap = DefaultColormap(display, DefaultScreen(display));
	for (int i=0; i<PATTERNLEN; i++)
		if (i % 2 == 0)
			grayPattern[i] = (unsigned char)0xAA;
		else
			grayPattern[i] = (unsigned char)0x55;
	rdPixmap = XCreatePixmap(display, window, round(wd), round(ht),
		 	DefaultDepth(display, DefaultScreen(display)));
	InitColors();
	copyGC = CreateCopyGC();
	xorGC = CreateXorGC();
	dotGC = CreateDotGC();
	wideDotGC = CreateWideDotGC();
	dashGC = CreateDashGC();
	ClearArea(0,0,wd,ht);
	SetFont(GetFont());
#ifdef DEBUG
	ColorInfo();
#endif
}

void XGrafport::SetDots(GC gc) {
	Pixmap pm = XCreateBitmapFromData(display, window, grayPattern, 
		PATTERNLEN, PATTERNLEN);
	if (!pm) {
		error("%s, line %d: Error creating bitmap\n", 
			__FILE__, __LINE__);
		return;
	}
	XSetStipple(display, gc, pm);
}

void XGrafport::SetBackgroundColor(const char *c) {
	string s = c;
	SetBackgroundColor(&s);
}

void XGrafport::SetForegroundColor(const char *c) {
	string s = c;
	SetForegroundColor(&s);
}

void XGrafport::SetBackgroundColor(const string *c) {
	if (*GetBackgroundColor() == *c)
		return;
	Grafport::SetBackgroundColor(c);
	XSetBackground(display, copyGC, GetWhitePixel());
	XSetBackground(display, xorGC, GetWhitePixel());
	XSetBackground(display, dotGC, GetWhitePixel());
	XSetBackground(display, wideDotGC, GetWhitePixel());
	XSetBackground(display, dashGC, GetWhitePixel());
	XSetForeground(display, xorGC, GetForegroundPixel());
	XSetForeground(display, dotGC, GetForegroundPixel());
	XSetForeground(display, wideDotGC, GetForegroundPixel());
	XSetForeground(display, dashGC, GetForegroundPixel());
}

void XGrafport::SetForegroundColor(const string *c) {
	if (*GetForegroundColor() == *c)
		return;
	Grafport::SetForegroundColor(c);
	XSetForeground(display, copyGC, GetBlackPixel());
	XSetForeground(display, xorGC, GetForegroundPixel());
	XSetForeground(display, dotGC, GetForegroundPixel());
	XSetForeground(display, wideDotGC, GetForegroundPixel());
	XSetForeground(display, dashGC, GetForegroundPixel());
}

Pixel XGrafport::GetWhitePixel() {
	// Look up background color in allocated color list.
	Color *color = LookupColor(GetBackgroundColor());
	if (color && color->allocated)
		return color->pixel;
	else if (color) {
		// try to allocate the color and save pixel for further use.
		XColor xcolor;
		char b[16];
                int red = int(255*color->red);
                int green = int(255*color->green);
                int blue = int(255*color->blue);
                sprintf(b, "%.2x%.2x%.2x", red, green, blue);
                string c = "#";
                c += b;
		if (XParseColor(display, colormap, c.getstr(), &xcolor)) {
			if (XAllocColor(display, colormap, &xcolor)) {
				color->allocated = True;
				color->pixel = xcolor.pixel;
				return xcolor.pixel;
                        }	
		}
	}
	if (!whitePixelWarned) {
		error("Warning: Cannot allocate colormap entry %s\n", 
			GetBackgroundColor()->getstr());
		whitePixelWarned = True; 
	}
	return WhitePixel(display, DefaultScreen(display));
}

Pixel XGrafport::GetBlackPixel() {
	// Look up foreground color in allocated color list.
	Color *color = LookupColor(GetForegroundColor());
	if (color && color->allocated)
		return color->pixel;
	else if (color) {
		// try to allocate the color and save pixel for further use.
		XColor xcolor;
		char b[16];
                int red = int(255*color->red);
                int green = int(255*color->green);
                int blue = int(255*color->blue);
                sprintf(b, "%.2x%.2x%.2x", red, green, blue);
                string c = "#";
                c += b;
		if (XParseColor(display, colormap, c.getstr(), &xcolor)) {
			if (XAllocColor(display, colormap, &xcolor)) {
				color->allocated = True;
				color->pixel = xcolor.pixel;
				return xcolor.pixel;
			}
		}
	}
	if (!blackPixelWarned) {
		error("Warning: Cannot allocate colormap entry %s\n", 
			GetForegroundColor()->getstr());
		blackPixelWarned = True;
	}
	return BlackPixel(display, DefaultScreen(display));
}

Pixel XGrafport::GetForegroundPixel() {
	return GetWhitePixel() ^ GetBlackPixel();
}

void XGrafport::ColorInfo() {
	Visual *visual = DefaultVisual(display, DefaultScreen(display));
	int depth = DefaultDepth(display, DefaultScreen(display));
	error("Colorinfo: depth = %d\n", depth);
	if (depth == 1)
		error("Monochrome\n");
	else {
		switch(visual->c_class) {
		case PseudoColor:
			error("PseudoColor\n");
			break;
		case StaticColor:
			error("StaticColor\n");
			break;
		case GrayScale:
			error("GrayScale\n");
			break;
		case StaticGray:
			error("StaticGray\n");
			break;
		case DirectColor:
			error("DirectColor\n");
			break;
		case TrueColor:
			error("TrueColor\n");
			break;
		default:
			error("Unknown color\n");
			break;
		}
	}
}

GC XGrafport::CreateXorGC() {
	GC gc;
	char dash_list[2];
	gc = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc, GetForegroundPixel());
	XSetBackground(display, gc, GetWhitePixel());
	XSetFunction(display, gc, GXxor);
	XSetLineAttributes(display, gc, 1, LineSolid, CapButt,
		JoinMiter);
	dash_list[0] = 1;
	dash_list[1] = 1;
	XSetDashes(display, gc, 0, dash_list, 2);
	// XSetGraphicsExposures(display, gc, 0);
	SetDots(gc);
	return gc;
}

GC XGrafport::CreateDotGC() {
	GC gc;
	char dash_list[2];
	gc = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc, GetForegroundPixel());
	XSetBackground(display, gc, GetWhitePixel());
	XSetFunction(display, gc, GXxor);
	XSetLineAttributes(display, gc, 1, LineOnOffDash, CapButt,
		JoinMiter);
	dash_list[0] = 1;
	dash_list[1] = 1;
	XSetDashes(display, gc, 0, dash_list, 2);
	return gc;
}

GC XGrafport::CreateWideDotGC() {
        GC gc;
        char dash_list[2];
        gc = XCreateGC(display, window, 0, 0);
        XSetForeground(display, gc, GetForegroundPixel());
        XSetBackground(display, gc, GetWhitePixel());
        XSetFunction(display, gc, GXxor);
        XSetLineAttributes(display, gc, 1, LineOnOffDash, CapButt,
		JoinMiter);
        dash_list[0] = 2;
        dash_list[1] = 2;
        XSetDashes(display, gc, 0, dash_list, 2);
        return gc;
}

GC XGrafport::CreateDashGC() {
	GC gc;
	char dash_list[2];
	gc = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc, GetForegroundPixel());
	XSetBackground(display, gc, GetWhitePixel());
	XSetFunction(display, gc, GXxor);
	// set line to dashes
	XSetLineAttributes(display, gc, 1, LineOnOffDash, CapButt,
		JoinMiter);
	dash_list[0] = 4;
	dash_list[1] = 2;
	XSetDashes(display, gc, 0, dash_list, 2);
	return gc;
}
	
GC XGrafport::CreateCopyGC() {
	GC gc;
	char dash_list[2];
	gc = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc, GetBlackPixel());
	XSetBackground(display, gc, GetWhitePixel());
	XSetLineAttributes(display, gc, 1, LineSolid, CapButt,
		JoinMiter);
	dash_list[0] = 1;
	dash_list[1] = 1;
	XSetDashes(display, gc, 0, dash_list, 2);
	// XSetGraphicsExposures(display, gc, 0);
	SetDots(gc);
	return gc;
}

XGrafport::~XGrafport(){
	XFreeGC(display, copyGC);
	XFreeGC(display, xorGC);
	XFreeGC(display, dotGC);
	XFreeGC(display, wideDotGC);
	XFreeGC(display, dashGC);
	XFreePixmap(display, rdPixmap);
}

void XGrafport::SetFont(XFont *f) {
	// unscaled font is already set.
	if (!f->IsScalable() && f == GetFont())
		return;
	// scaled font is already set and properly scaled.
	if (f->IsScalable() && f == GetFont() && 
			f->GetFactor() == GetZoomValue())
		return;
	Grafport::SetFont(f);
	if (GetFont()->IsScalable())
		GetFont()->Scale(GetZoomValue());
	long id = GetFont()->GetXFid();
	if (copyGC)
		XSetFont(display, copyGC, id);
	if (xorGC)
		XSetFont(display, xorGC, id);
	if (dotGC)
		XSetFont(display, dotGC, id);
	if (wideDotGC)
		XSetFont(display, wideDotGC, id);
	if (dashGC)
		XSetFont(display, dashGC, id);
}
 
void XGrafport::SetLineWidth(unsigned int w) {
	if (w == GetLineWidth())
		return;
	Grafport::SetLineWidth(w);
	XGCValues gv;
	gv.line_width = w;
	XChangeGC(display, xorGC, GCLineWidth, &gv);
	XChangeGC(display, dashGC, GCLineWidth, &gv);
	XChangeGC(display, dotGC, GCLineWidth, &gv);
	XChangeGC(display, wideDotGC, GCLineWidth, &gv);
	XChangeGC(display, copyGC, GCLineWidth, &gv);
}

void XGrafport::Redraw(double from_x, double from_y, double wd, double ht, 
		double to_x, double to_y) {
	XCopyArea(display, rdPixmap, window, copyGC,
		round(from_x), round(from_y),  round(wd), round(ht),
		round(to_x), round(to_y));
}

void XGrafport::UpdateSize(double wd, double ht) {
	// save old pixmap, create a new one.
	Pixmap oldPX = rdPixmap;
	rdPixmap = XCreatePixmap(display, window, round(wd), round(ht),
			DefaultDepth(display, DefaultScreen(display)));
	// clear new pixmap.
	ClearArea(0, 0, wd, ht);
	width = wd;
	height = ht;
	// free old pixmap.
	XFreePixmap(display, oldPX);
}

void XGrafport::ClearArea(double x, double y, double wd, double ht){
	// to clear a pixmap. reverse foreground and background
	XSetForeground(display, copyGC, GetWhitePixel());
	// and fill rectangle the size of the pixmap
	XFillRectangle(display, rdPixmap, copyGC, round(x), round(y),
		round(wd), round(ht));
	// copy pixmap to the window.
	XCopyArea(display, rdPixmap, window, copyGC, round(x), round(y),
		round(wd), round(ht), round(x), round(y));
	// reset the foreground to black
	XSetForeground(display, copyGC, GetBlackPixel());
}

void XGrafport::DrawRectangle(double x, double y, double wd, double ht) {
	if (GetLineStyle() == LineStyle::SOLID)
		DrawXRectangle(xorGC, x, y, wd, ht);
	else if (GetLineStyle() == LineStyle::DASHED)
		DrawXRectangle(dashGC, x, y, wd, ht);
	else if (GetLineStyle() == LineStyle::DOTTED)
		DrawXRectangle(dotGC, x, y, wd, ht);
	else if (GetLineStyle() == LineStyle::WIDE_DOTTED)
		DrawXRectangle(wideDotGC, x, y, wd, ht);
	else if (GetLineStyle() == LineStyle::DUAL) {
		DrawXRectangle(xorGC, x, y, wd, ht);
		int n = 2*GetLineWidth();
		if (ht > 2*n && wd > 2*n)  
			DrawXRectangle(xorGC, x+n, y+n, wd-2*n, ht-2*n);
	}
}

void XGrafport::FillRectangle(double x, double y, double wd, double ht) {
	FillXRectangle(xorGC, x, y, wd, ht);
}


void XGrafport::DrawXRectangle(GC gc, double x_, double y_, double wd_, double ht_) {
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_));
	XDrawRectangle(display, window, gc, x, y, wd, ht);
	XDrawRectangle(display, rdPixmap, gc, x, y, wd, ht);
}

void XGrafport::FillXRectangle(GC gc, double x_, double y_, double wd_, double ht_) {
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_));
	XFillRectangle(display, window, gc, x, y, wd, ht);
	XFillRectangle(display, rdPixmap, gc, x, y, wd, ht);
}


void XGrafport::DrawUnzoomedRectangle(double x_, double y_, double wd_, double ht_){
	int x = round(x_); int y = round(y_);
	int wd = round(wd_); int ht = round(ht_);
	XDrawRectangle(display, window, xorGC, x, y, wd, ht);
	XDrawRectangle(display, rdPixmap, xorGC, x, y, wd, ht);
}

void XGrafport::DrawEditDashedRectangle(double x_, double y_, double wd_, double ht_){
	int x = round(x_); int y = round(y_);
	int wd = round(wd_); int ht = round(ht_);
	SetLineWidth(1);
	char dash_list[4];
	// set dashes form
	dash_list[0] = 5;
	dash_list[1] = 2;
	dash_list[2] = 2;
	dash_list[3] = 2;
	XSetDashes(display, xorGC, 0, dash_list, 4);
	// set line to dashes
	XSetLineAttributes(display, xorGC,0, LineOnOffDash, CapButt, JoinMiter);
	// draw rectangle, not zoomed
	XDrawRectangle(display, window, xorGC, x, y, wd, ht);
	XDrawRectangle(display, rdPixmap, xorGC, x, y, wd, ht);
	// restore dashes
	dash_list[0] = 1;
	dash_list[1] = 1;
	XSetDashes(display, xorGC, 0, dash_list, 2);
	// restore line
	XSetLineAttributes(display, xorGC, 1, LineSolid, CapButt,
		JoinMiter);
}

void XGrafport::DrawStringLeft(double x_, double y_, const char *str){
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	XDrawString(display, window, xorGC, x, y, str, strlen(str));
	XDrawString(display, rdPixmap, xorGC, x, y, str, strlen(str));
	XFlush(display);
}

void XGrafport::DrawUnzoomedStringLeft(double x_, double y_, const char *str){
	int x = round(x_); int y = round(y_);
	XDrawString(display, window, xorGC, x, y, str, strlen(str));
	XDrawString(display, rdPixmap, xorGC, x, y, str, strlen(str));
	XFlush(display);
}

void XGrafport::DrawStringRight(double x, double y, const char *str){
	int wd = GetFont()->StringWidth(str);
	DrawStringLeft(x-wd, y, str);
}

void XGrafport::DrawStringCentered(double x_, double y_, const char *str){
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	int wd = GetFont()->StringWidth(str);
	if (GetFont()->IsScalable())
		wd = round(Zoom(wd));
	int ht = round(Zoom(GetFont()->GetHeight()));
	int dy = ht / 2 - round(Zoom(GetFont()->GetDescent()));
	XDrawString(display, window, xorGC, x-wd/2, y+dy, str, strlen(str));
	XDrawString(display, rdPixmap, xorGC, x-wd/2, y+dy, str, strlen(str));
	XFlush(display);
}

void XGrafport::DrawUnzoomedStringCentered(double x_, double y_, const char *str){
	int x = round(x_); int y = round(y_);
	int wd = GetFont()->StringWidth(str);
	int ht = GetFont()->GetHeight();
	int dy = ht / 2 - GetFont()->GetDescent();
	XDrawString(display, window, xorGC, x-wd/2, y+dy, str, strlen(str));
	XDrawString(display, rdPixmap, xorGC, x-wd/2, y+dy, str, strlen(str));
	XFlush(display);
}

//Underlined Strings
void XGrafport::DrawStringLeftUnderlined(double x, double y, const char *str) {
	DrawStringLeft(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringLeft... : Corrected Height for y ( == topLefty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	DrawXLine(xorGC, x, y + cht, x + wd, y + cht);
	XFlush(display);
}

void XGrafport::DrawStringRightUnderlined(double x, double y, const char *str) {
	DrawStringRight(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringRight... : Corrected Height for y ( == topRighty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	DrawXLine(xorGC, x - wd, y + cht, x, y+cht);
	XFlush(display);
}


void XGrafport::DrawStringCenteredUnderlined(double x, double y, const char *str) {
	// int hz = GetFont()->GetHeight();
	DrawStringCentered(x, y, str);	// STAY !
	int wd = GetFont()->StringWidth(str);
	int ht = GetFont()->GetHeight();
	DrawXLine(xorGC, x-wd/2, y+ht/2, (x-wd/2)+wd, y+ht/2);
	XFlush(display);
}


double XGrafport::Px(double t) {
	double t2 = (1 - t) * (1 - t);
	double x = px0 * t2 * (1 - t) + px1 * 3 * t * t2 + 
			px2 * 3 * t*t * (1 - t) + px3 * t*t*t;
	return x;
}

double XGrafport::Py(double t) {
	double t2 = (1 - t) * (1 - t);
	double y = py0 * t2 * (1 - t) + py1 * 3 * t * t2 + 
			py2 * 3 * t*t * (1 - t) + py3 * t*t*t;
	return y;
}


//void XGrafport::CalcCurvePoints(const Point *p1, const Point *p2, 
//				const Point *p3, const Point *p4) {
//	px0 = p1->x; py0 = p1->y;
//	px1 = p2->x; py1 = p2->y;
//	px2 = p3->x; py2 = p3->y;
//	px3 = p4->x; py3 = p4->y;
//	int i;
//	double t=0.0;
//	for (i=0;i<CURVE_POINTS;i++) {
//		xx[i] = Px(t);
//		yy[i] = Py(t);
//		t = t + 1/(double)(CURVE_POINTS-1);
//	}
//}
//
//
//void XGrafport::DrawCurve(const Point *p1, const Point *p2, 
//			  const Point *p3, const Point *p4){
//	CalcCurvePoints(p1,p2,p3,p4);
//	for (int i=0;i<CURVE_POINTS-1;i++) {
//		DrawLine(xx[i], yy[i], xx[i+1], yy[i+1]);
//	}
//}


void XGrafport::DrawSimpleCurve(const DPoint *p) {
	DPoint points[CURVE_POINTS];
	px0 = p[0].x; py0 = p[0].y;
	px1 = p[1].x; py1 = p[1].y;
	px2 = p[2].x; py2 = p[2].y;
	px3 = p[3].x; py3 = p[3].y;
	for ( int i = 0 ; i < CURVE_POINTS ; i++ ) {
		double t = i / (double) (CURVE_POINTS - 1);
		points[i].Set(Px(t), Py(t));
	}
	DrawSimplePolygon(points, CURVE_POINTS);
}


//void XGrafport::DrawLine(double x1, double y1, double x2, double y2){
//	if (GetLineStyle()==LineStyle::SOLID)
//		DrawXLine(xorGC, x1, y1, x2, y2);
//	else if (GetLineStyle()==LineStyle::DASHED)
//		DrawXLine(dashGC, x1, y1, x2, y2);
//	else if (GetLineStyle()==LineStyle::DOTTED)
//		DrawXLine(dotGC, x1, y1, x2, y2);
//	else if (GetLineStyle()==LineStyle::WIDE_DOTTED)
//		DrawXLine(wideDotGC, x1, y1, x2, y2);
//	else if (GetLineStyle()==LineStyle::DUAL) {
//		int n = GetLineWidth();
//		if (y1 == y2) {  // horizontal
//			DrawXLine(xorGC, x1, y1+n, x2, y2+n);
//			DrawXLine(xorGC, x1, y1-n, x2, y2-n);
//		}
//		else if (x1 == x2) {  // vertical
//			DrawXLine(xorGC, x1+n, y1, x2+n, y2);
//			DrawXLine(xorGC, x1-n, y1, x2-n, y2);
//		}
//		else { 			// diagonal
//			DrawXLine(xorGC, x1, y1, x2, y2);
//			DrawXLine(xorGC, x1, y1+2*n, x2, y2+2*n);
//		}
//	}
//}
//
void XGrafport::DrawXLine(GC gc, double x1_, double y1_, double x2_, double y2_){
	int x1 = round(Zoom(x1_)); int y1 = round(Zoom(y1_));
	int x2 = round(Zoom(x2_)); int y2 = round(Zoom(y2_));
	XDrawLine(display, window, gc, x1, y1, x2, y2);
	XDrawLine(display, rdPixmap, gc, x1, y1, x2, y2);
}

void XGrafport::DrawPoint(double x_, double y_){
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	XDrawPoint(display, window, xorGC, x, y);
	XDrawPoint(display, rdPixmap, xorGC, x, y);
}

void XGrafport::DrawEditDottedGridLine(double x1_, double y1_, double x2_, double y2_){
	int x1 = round(x1_); int y1 = round(y1_);
	int x2 = round(x2_); int y2 = round(y2_);
	SetLineWidth(1);
	// not zoomed.
	char dash_list[4];
	// set dashes form
	dash_list[0] = 1;
	dash_list[1] = 4;
	XSetDashes(display, xorGC, 0, dash_list, 2);
	// set line to dashes
	XSetLineAttributes(display, xorGC,0, LineOnOffDash, CapButt, JoinMiter);
	// draw line
	XDrawLine(display, window, xorGC, x1, y1, x2, y2);
	XDrawLine(display, rdPixmap, xorGC, x1, y1, x2, y2);
	// restore dashes
	dash_list[0] = 1;
	dash_list[1] = 1;
	XSetDashes(display, xorGC, 0, dash_list, 2);
	// restore line
	XSetLineAttributes(display, xorGC, 1, LineSolid, CapButt,
		JoinMiter);
}

void XGrafport::DrawUnzoomedLine(double x1_, double y1_, double x2_, double y2_) {
	int x1 = round(x1_); int y1 = round(y1_);
	int x2 = round(x2_); int y2 = round(y2_);
	XDrawLine(display, window, xorGC, x1, y1, x2, y2);
	XDrawLine(display, rdPixmap, xorGC, x1, y1, x2, y2);
}

void XGrafport::DrawEditLine(double x1_, double y1_, double x2_, double y2_) {
	int x1 = round(x1_); int y1 = round(y1_);
	int x2 = round(x2_); int y2 = round(y2_);
	SetLineWidth(1);
	DrawUnzoomedLine(x1, y1, x2, y2);
}

void XGrafport::DrawEditDottedLine(double x1_, double y1_, double x2_, double y2_) {
	int x1 = round(x1_); int y1 = round(y1_);
	int x2 = round(x2_); int y2 = round(y2_);
	SetLineWidth(1);
	XDrawLine(display, window, dotGC, x1, y1, x2, y2);
	XDrawLine(display, rdPixmap, dotGC, x1, y1, x2, y2);
}

void XGrafport::DrawEditPoint(double x_, double y_) {
	int x = round(x_); int y = round(y_);
	SetLineWidth(1);
	XDrawPoint(display, window, xorGC, x, y);
	XDrawPoint(display, rdPixmap, xorGC, x, y);
}


void XGrafport::DrawSimpleArc(double x, double y,
	double wd, double ht, int arc1, int arc2)
{
	switch ( GetLineStyle() ) {
	case LineStyle::SOLID:
	case LineStyle::DUAL:
		DrawXArc(xorGC, x, y, wd, ht, arc1, arc2);
		break;
	case LineStyle::DASHED:
		DrawXArc(dashGC, x, y, wd, ht, arc1, arc2);
		break;
	case LineStyle::DOTTED:
		DrawXArc(dotGC, x, y, wd, ht, arc1, arc2);
		break;
	case LineStyle::WIDE_DOTTED:
		DrawXArc(wideDotGC, x, y, wd, ht, arc1, arc2);
		break;
	case LineStyle::INVISIBLE:
		break;		//do nothing
	}
}


void XGrafport::FillSegment(double x, double y,
	double wd, double ht, int arc1, int arc2)
{
	XSetArcMode(display, xorGC, ArcChord);
	FillXArc(xorGC, x, y, wd, ht, arc1, arc2);
}


void XGrafport::DrawXArc(GC gc, double x_, double y_,
	double wd_, double ht_, int arc1, int arc2)
{
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_));
	XDrawArc(display, window, gc, x, y, wd, ht,
		arc1 * 64, (arc2 - arc1) * 64);
	XDrawArc(display, rdPixmap, gc, x, y, wd, ht,
		arc1 * 64, (arc2 - arc1) * 64);
}


void XGrafport::FillXArc(GC gc, double x_, double y_,
	double wd_, double ht_, int arc1, int arc2)
{
	int x = round(Zoom(x_)); int y = round(Zoom(y_));
	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_));
	XFillArc(display, window, gc, x, y, wd, ht,
		arc1 * 64, (arc2 - arc1) * 64);
	XFillArc(display, rdPixmap, gc, x, y, wd, ht,
		arc1 * 64, (arc2 - arc1) * 64);
}

void XGrafport::DrawPolygon(const Point *points, int n) {
	if (GetLineStyle()==LineStyle::SOLID)
		DrawXPolygon(xorGC, points, n);
	else if (GetLineStyle()==LineStyle::DASHED)
		DrawXPolygon(dashGC, points, n);
	else if (GetLineStyle()==LineStyle::DOTTED)
		DrawXPolygon(dotGC, points, n);
	else if (GetLineStyle()==LineStyle::WIDE_DOTTED)
		DrawXPolygon(wideDotGC, points, n);
	else if (GetLineStyle()==LineStyle::DUAL) {
		DrawXPolygon(xorGC, points, n);
		int w = 2*GetLineWidth();
		Point *newPoints = new Point[n]; 
		RecalcPolygon(points, n, newPoints, w);
		DrawXPolygon(xorGC, newPoints, n);
		delete newPoints;
	}
}

void XGrafport::DrawSimplePolygon(const DPoint *points, int n) {
	switch ( GetLineStyle() ) {
	case LineStyle::SOLID:
	case LineStyle::DUAL:
		DrawXOpenPolygon(xorGC, points, n);
		break;
	case LineStyle::DASHED:
		DrawXOpenPolygon(dashGC, points, n);
		break;
	case LineStyle::DOTTED:
		DrawXOpenPolygon(dotGC, points, n);
		break;
	case LineStyle::WIDE_DOTTED:
		DrawXOpenPolygon(wideDotGC, points, n);
		break;
	case LineStyle::INVISIBLE:
		break;		//do nothing
	}
}


void XGrafport::FillPolygon(const Point *points, int n) {
	FillXPolygon(xorGC, points, n);
}


void XGrafport::FillPolygon(const DPoint *points, int n) {
	FillXPolygon(xorGC, points, n);
}


void XGrafport::DrawXPolygon(GC gc, const Point *points, int n) {
	XPoint *p = new XPoint[n+1];
	for (int i=0; i<n; i++) {
		p[i].x = round(Zoom(points[i].x));
		p[i].y = round(Zoom(points[i].y));
	}
	p[n].x = round(Zoom(points[0].x));
	p[n].y = round(Zoom(points[0].y));
	XDrawLines(display, window, gc, p, n+1, CoordModeOrigin);
	XDrawLines(display, rdPixmap, gc, p, n+1, CoordModeOrigin);
	delete[] p;
}


void XGrafport::DrawXOpenPolygon(GC gc, const DPoint *points, int n) {
	XPoint *p = new XPoint[n];
	for (int i=0; i<n; i++) {
		p[i].x = round(Zoom(points[i].x));
		p[i].y = round(Zoom(points[i].y));
	}
	XDrawLines(display, window, gc, p, n, CoordModeOrigin);
	XDrawLines(display, rdPixmap, gc, p, n, CoordModeOrigin);
	delete[/* n */] p;
}

void XGrafport::FillXPolygon(GC gc, const Point *points, int n) {
	XPoint *p = new XPoint[n];
	for (int i=0; i<n; i++) {
		p[i].x = round(Zoom(points[i].x));
		p[i].y = round(Zoom(points[i].y));
	}
	XFillPolygon(display, window, gc, p, n, Complex, CoordModeOrigin);
	XFillPolygon(display, rdPixmap, gc, p, n, Complex, CoordModeOrigin);
	delete[] p;
}

void XGrafport::FillXPolygon(GC gc, const DPoint *points, int n) {
	XPoint *p = new XPoint[n];
	for (int i=0; i<n; i++) {
		p[i].x = round(Zoom(points[i].x));
		p[i].y = round(Zoom(points[i].y));
	}
	XFillPolygon(display, window, gc, p, n, Complex,
		CoordModeOrigin);
	XFillPolygon(display, rdPixmap, gc, p, n, Complex,
		CoordModeOrigin);
	delete[/* n */] p;
}

void XGrafport::DrawActiveCaret(double x_, double y_) {
	int x = round(Zoom(x_));
	int y = round(Zoom(y_));
	XPoint points[3];
	points[0].x = x + 1;
	points[0].y = y - 2;
	points[1].x = 4;
	points[1].y = 8;
	points[2].x = -8;
	points[2].y =  0;
	XFillPolygon(display, window, xorGC, points, 3, Convex, 
			CoordModePrevious);
	XFillPolygon(display, rdPixmap, xorGC, points, 3, Convex, 
			CoordModePrevious);
}

void XGrafport::DrawDeactiveCaret(double x_, double y_) {
	int x = round(Zoom(x_));
	int y = round(Zoom(y_));
	XPoint points[4];
	points[0].x = x+1;
	points[0].y = y-2;
	points[1].x = 4;
	points[1].y = 4;
	points[2].x = -4;
	points[2].y = 4;
	points[3].x = -4;
	points[3].y = -4;
	XSetFillStyle(display, xorGC, FillOpaqueStippled);
	XFillPolygon(display, window, xorGC, points, 4, Convex, 
		CoordModePrevious);
	XFillPolygon(display, rdPixmap, xorGC, points, 4, Convex, 
		CoordModePrevious);
}


//void XGrafport::DrawRoundedRectangle(double x, double y,
//	double wd, double ht, double rd)
//{
//	if (GetLineStyle() == LineStyle::SOLID)
//		DrawXRoundedRectangle(xorGC, x, y, wd, ht, rd);
//	else if (GetLineStyle() == LineStyle::DASHED)
//		DrawXRoundedRectangle(dashGC, x, y, wd, ht, rd);
//	else if (GetLineStyle() == LineStyle::DOTTED)
//		DrawXRoundedRectangle(dotGC, x, y, wd, ht, rd);
//	else if (GetLineStyle() == LineStyle::WIDE_DOTTED)
//		DrawXRoundedRectangle(wideDotGC, x, y, wd, ht, rd);
//	else if (GetLineStyle() == LineStyle::DUAL) {
//		DrawXRoundedRectangle(xorGC, x, y, wd, ht, rd);
//		int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)  
//			DrawXRoundedRectangle(xorGC, x+n, y+n, wd-2*n, ht-2*n, rd);
//	}
//}
//
//void XGrafport::FillRoundedRectangle(double x, double y,
//	double wd, double ht, double rd)
//{
//	FillXRoundedRectangle(xorGC, x, y, wd, ht, rd);
//}
//
//void XGrafport::DrawEllipsedRectangle(double x, double y,
//	double wd, double ht, double rd)
//{
//        if (GetLineStyle() == LineStyle::SOLID)
//                DrawXEllipsedRectangle(xorGC, x, y, wd, ht, rd);
//        else if (GetLineStyle() == LineStyle::DASHED)
//                DrawXEllipsedRectangle(dashGC, x, y, wd, ht, rd);
//        else if (GetLineStyle() == LineStyle::DOTTED)
//                DrawXEllipsedRectangle(dotGC, x, y, wd, ht, rd);
//        else if (GetLineStyle() == LineStyle::WIDE_DOTTED)
//                DrawXEllipsedRectangle(wideDotGC, x, y, wd, ht, rd);
//        else if (GetLineStyle() == LineStyle::DUAL) {
//                DrawXEllipsedRectangle(xorGC, x, y, wd, ht, rd);
//                int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)  
//                	DrawXEllipsedRectangle(xorGC, x+n, y+n, wd-2*n, ht-2*n, rd-n);
//        }
//}
//
//void XGrafport::DrawDisk(double x, double y,
//	double wd, double ht, double el)
//{
//        if (GetLineStyle() == LineStyle::SOLID)
//                DrawXDisk(xorGC, x, y, wd, ht, el);
//        else if (GetLineStyle() == LineStyle::DASHED)
//                DrawXDisk(dashGC, x, y, wd, ht, el);
//        else if (GetLineStyle() == LineStyle::DOTTED)
//                DrawXDisk(dotGC, x, y, wd, ht, el);
//        else if (GetLineStyle() == LineStyle::WIDE_DOTTED)
//                DrawXDisk(wideDotGC, x, y, wd, ht, el);
//        else if (GetLineStyle() == LineStyle::DUAL) {
//                DrawXDisk(xorGC, x, y, wd, ht, el);
//                int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)  
//                	DrawXDisk(xorGC, x+n, y+n, wd-2*n, ht-2*n, el-2*n);
//        }
//}
// 
//void XGrafport::FillEllipsedRectangle(double x, double y,
//	double wd, double ht, double rd)
//{
//        FillXEllipsedRectangle(xorGC, x, y, wd, ht, rd);
//}
//
//void XGrafport::FillDisk(double x, double y,
//	double wd, double ht, double el)
//{
//        FillXDisk(xorGC, x, y, wd, ht, el);
//}
//
//void XGrafport::DrawXRoundedRectangle(GC gc, double x_, double y_,
//	double wd_, double ht_, double rd_)
//{
//	int x = round(Zoom(x_)); int y = round(Zoom(y_));
//	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int rd = round(Zoom(rd_));
//	// draw four lines (widthout the corner parts).
//	XDrawLine(display, window, gc, x, y+rd+1, x, y+ht-rd-1);
//	XDrawLine(display, window, gc, x+rd+1, y+ht, x+wd-rd-1, y+ht);
//	XDrawLine(display, window, gc, x+wd, y+ht-rd-1, x+wd, y+rd+1);
//	XDrawLine(display, window, gc, x+wd-rd-1, y, x+rd+1, y);
//	XDrawLine(display, rdPixmap, gc, x, y+rd+1, x, y+ht-rd-1);
//	XDrawLine(display, rdPixmap, gc, x+rd+1, y+ht, x+wd-rd-1, y+ht);
//	XDrawLine(display, rdPixmap, gc, x+wd, y+ht-rd-1, x+wd, y+rd+1);
//	XDrawLine(display, rdPixmap, gc, x+wd-rd-1, y, x+rd+1, y);
//	// draw four corner arcs.
//	int diam = 2*rd;
//	XDrawArc(display, window, gc, x, y, diam, diam, 90*64, 90*64);
//	XDrawArc(display, window, gc, x, y+ht-diam, diam, diam, 180*64, 90*64);
//	XDrawArc(display, window, gc, x+wd-diam, y+ht-diam, diam, diam, 
//			270*64, 90*64);
//	XDrawArc(display, window, gc, x+wd-diam, y, diam, diam, 0*64, 90*64);
//	XDrawArc(display, rdPixmap, gc, x, y, diam, diam, 90*64, 90*64);
//	XDrawArc(display, rdPixmap, gc, x, y+ht-diam, diam, diam, 
//			180*64, 90*64);
//	XDrawArc(display, rdPixmap, gc, x+wd-diam, y+ht-diam, diam, diam, 
//			270*64, 90*64);
//	XDrawArc(display, rdPixmap, gc, x+wd-diam, y, diam, diam, 0*64, 90*64);
//}
//
//void XGrafport::FillXRoundedRectangle(GC gc, double x_, double y_,
//	double wd_, double ht_, double rd_)
//{
//	int x = round(Zoom(x_)); int y = round(Zoom(y_));
//	int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int rd = round(Zoom(rd_));
//	// fill rectangle parts.
//	XFillRectangle(display, window, gc, x, y+rd, wd, ht-2*rd);
//	XFillRectangle(display, window, gc, x+rd, y, wd-2*rd, rd);
//	XFillRectangle(display, window, gc, x+rd, y+ht-rd, wd-2*rd, rd);
//	XFillRectangle(display, rdPixmap, gc, x, y+rd, wd, ht-2*rd);
//	XFillRectangle(display, rdPixmap, gc, x+rd, y, wd-2*rd, rd);
//	XFillRectangle(display, rdPixmap, gc, x+rd, y+ht-rd, wd-2*rd, rd);
//	// fill four corner arcs.
//	int diam = 2*rd;
//	XFillArc(display, window, gc, x, y, diam, diam, 90*64, 90*64);
//	XFillArc(display, window, gc, x, y+ht-diam, diam, diam, 180*64, 90*64);
//	XFillArc(display, window, gc, x+wd-diam, y+ht-diam, diam, diam, 
//			270*64, 90*64);
//	XFillArc(display, window, gc, x+wd-diam, y, diam, diam, 0*64, 90*64);
//	XFillArc(display, rdPixmap, gc, x, y, diam, diam, 90*64, 90*64);
//	XFillArc(display, rdPixmap, gc, x, y+ht-diam, diam, diam, 
//			180*64, 90*64);
//	XFillArc(display, rdPixmap, gc, x+wd-diam, y+ht-diam, diam, diam, 
//			270*64, 90*64);
//	XFillArc(display, rdPixmap, gc, x+wd-diam, y, diam, diam, 
//			0*64, 90*64);
//}
//
//void XGrafport::DrawXEllipsedRectangle(GC gc, double x_, double y_,
//	double wd_, double ht_, double rd_)
//{
//        int x = round(Zoom(x_)); int y = round(Zoom(y_));
//        int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int rd = round(Zoom(rd_));
//        // draw two lines (without the corner parts).
//        XDrawLine(display, window, gc, x+rd+1, y, x+wd-rd-1, y);
//        XDrawLine(display, window, gc, x+rd+1, y+ht, x+wd-rd-1, y+ht);
//        XDrawLine(display, rdPixmap, gc, x+rd+1, y, x+wd-rd-1, y);
//        XDrawLine(display, rdPixmap, gc, x+rd+1, y+ht, x+wd-rd-1, y+ht);
//        // draw two half circle parts.
//        int diam = 2*rd;        // (== ht)
//        XDrawArc(display, window, gc, x, y, diam, ht, 
//		90*64, 180*64);
//        XDrawArc(display, window, gc, x+wd-diam, y, diam, ht, 
//		270*64, 180*64);
//        XDrawArc(display, rdPixmap, gc, x, y, diam, ht, 
//		90*64, 180*64);
//        XDrawArc(display, rdPixmap, gc, x+wd-diam, y, diam, ht, 
//		270*64, 180*64);
//}
// 
//void XGrafport::FillXEllipsedRectangle(GC gc, double x_, double y_,
//	double wd_, double ht_, double rd_)
//{
//        int x = round(Zoom(x_)); int y = round(Zoom(y_));
//        int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int rd = round(Zoom(rd_));
//        // fill rectangle part.
//        XFillRectangle(display, window, gc, x+rd, y, wd-2*rd, ht);
//        XFillRectangle(display, rdPixmap, gc, x+rd, y, wd-2*rd, ht);
//        // fill two half circle parts.
//        int diam = 2*rd;        // (== ht)
//        XFillArc(display, window, gc, x, y, diam, ht, 
//		 90*64, 180*64);
//        XFillArc(display, window, gc, x+wd-diam, y, diam, ht, 
//		 270*64, 180*64);
//        XFillArc(display, rdPixmap, gc, x, y, diam, ht, 
//		 90*64, 180*64);
//        XFillArc(display, rdPixmap, gc, x+wd-diam, y, diam, ht, 
//		270*64, 180*64);
//}
//
//void XGrafport::DrawXDisk(GC gc, double x_, double y_, 
//	double wd_, double ht_, double el_)
//{
//        int x = round(Zoom(x_)); int y = round(Zoom(y_));
//        int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int el = round(Zoom(el_));
//	int ah = el/2; // arc height
//        // draw two lines (without the corner points).
//        XDrawLine(display, window, gc, x, y+ah+1, x, y+ht-ah-1);
//        XDrawLine(display, window, gc, x+wd, y+ah+1, x+wd, y+ht-ah-1);
//        XDrawLine(display, rdPixmap, gc, x, y+ah+1, x, y+ht-ah-1);
//        XDrawLine(display, rdPixmap, gc, x+wd, y+ah+1, x+wd, y+ht-ah-1);
//        // draw whole ellipse (arc) and half ellipse
//        XDrawArc(display, window, gc, x, y, wd, el, 0*64, 360*64);
//        XDrawArc(display, window, gc, x, y+ht-el, wd, el, 0*64, -180*64);
//        XDrawArc(display, rdPixmap, gc, x, y, wd, el, 0*64, 360*64);
//        XDrawArc(display, rdPixmap, gc, x, y+ht-el, wd, el, 0*64, -180*64);
//}
// 
//void XGrafport::FillXDisk(GC gc, double x_, double y_, 
//	double wd_, double ht_, double el_)
//{
//        int x = round(Zoom(x_)); int y = round(Zoom(y_));
//        int wd = round(Zoom(wd_)); int ht = round(Zoom(ht_)); int el = round(Zoom(el_));
//	int ah = el/2; // arc height
//	XFillRectangle(display, window, gc, x, y+ah+1, wd, ht-2*ah-1); 
//	XFillRectangle(display, rdPixmap, gc, x, y+ah+1, wd, ht-2*ah-1); 
//	// fill ellipse parts
//        XFillArc(display, window, gc, x, y, wd, el, 0*64, 180*64);
//        XFillArc(display, window, gc, x, y+ht-el, wd, el, 0*64, -180*64);
//        XFillArc(display, rdPixmap, gc, x, y, wd, el, 0*64, 180*64);
//        XFillArc(display, rdPixmap, gc, x, y+ht-el, wd, el, 0*64, -180*64);
//}

void XGrafport::DrawEllipse(double x, double y,
	double wd, double ht)
{
	DrawArc(x, y, wd, ht, 0, 360);
}

void XGrafport::FillEllipse(double x, double y,
	double wd, double ht)
{
	FillSegment(x, y, wd, ht, 0, 360);
}

//void XGrafport::FillArc(double x, double y,
//	double wd, double ht, int arc1, int arc2)
//{
//	XSetArcMode(display, xorGC, ArcPieSlice);
//	FillXArc(xorGC, x, y, wd, ht, arc1, arc2);
//}
