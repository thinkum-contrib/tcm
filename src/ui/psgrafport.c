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
#include "psgrafport.h"
#include "application.h"
#include "system.h"
#include "color.h"
#include <ctype.h>

const char PSGrafport::BANNER[] = BANNER_FILE;

const double PSGrafport::DEFAULT_LINE_WIDTH = 0.750;

const double PSGrafport::XOFF = 12.90;
const double PSGrafport::YOFF = 9.50;

PSGrafport::PSGrafport(const char *fileName): Grafport() {
	if (equal(fileName, ""))
		fd = stdout;
	else
		fd = fopen(fileName, "w");
	succes = (fd != 0);
	isoLatin1Encoding = True;
	showColors = True;
	InitColors();
}

PSGrafport::~PSGrafport() {
	if (succes)
		fclose(fd);
}

void PSGrafport::SetBackgroundColor(const char *c) {
        string s = c;
        SetBackgroundColor(&s);
}
 
void PSGrafport::SetForegroundColor(const char *c) {
        string s = c;
        SetForegroundColor(&s);
}
 
void PSGrafport::SetBackgroundColor(const string *c) {
	if (*GetBackgroundColor() == *c)
		return;
	Grafport::SetBackgroundColor(c);
}

void PSGrafport::SetForegroundColor(const string *c) {
	if (*GetForegroundColor() == *c)
		return;
	Grafport::SetForegroundColor(c);
	if (!showColors)
		return;
	Color *color = LookupColor(c);
	if (color) {
		fprintf(fd, "%f %f %f setrgbcolor\n", 
			color->red, color->green, color->blue);
		return;
	}
	else
		error("color %s not found\n", c->getstr());
}

void PSGrafport::Header(const char *title, const char *creator) {
	// PostScript Language Ref. Man. page 621
	char login[MAXNAME];
	char date[MAXNAME];
	System::GetLoginName(login);
	System::GetTime(date);
	fprintf(fd, "%%!PS-Adobe-1.0\n");
	fprintf(fd, "%%%%Title: %s\n", title);
	fprintf(fd, "%%%%Creator: %s\n", creator);
	fprintf(fd, "%%%%CreationDate: %s\n", date);
	fprintf(fd, "%%%%For: %s\n", login);
	fprintf(fd, "%%%%DocumentFonts: (atend)\n");
	fprintf(fd, "%%%%Pages: (atend)\n");
	fprintf(fd, "%%%%BoundingBox: (atend)\n");
	fprintf(fd, "%%%%EndComments\n");
	FontProlog();
	fprintf(fd, "%%%%EndProlog\n");
}

void PSGrafport::BeginDrawProc() {
	fprintf(fd, "/drawall {\n");
}

void PSGrafport::EndDrawProc() {
	fprintf(fd, "} def \n");
}

void PSGrafport::CallDrawProc() {
	fprintf(fd, "drawall\n");
}

void PSGrafport::Banner(const char *title) {
	FILE *bn;
	char bfile[MAXNAME];
	char toolkit_conf[MAXNAME];
	System::GetToolkitConfig(toolkit_conf);
	strcpy(bfile, toolkit_conf);
	strcat(bfile, BANNER);
	// Open file banner.ps
	bn = fopen(bfile, "r");
	if (bn == 0) {
		error("Warning: could not open %s\n", bfile);
		return;
	}
	// Copy banner.ps
	int c;
	while ((c = getc(bn)) != EOF)
		putc(c, fd);
	// Close file banner.ps
	fclose(bn);
	char host[MAXNAME];
	char login[MAXNAME];
	char time[MAXNAME];
	System::GetHostName(host);
	System::GetLoginName(login);
	System::GetTime(time);
	// Write sline
	fprintf(fd, "(%s:%s Job: %s Date: %s)LS\n", host, login, title, time);
}

void PSGrafport::EPSHeader(const char *title, const char *creator, 
		double llx, double lly, double urx, double ury) {
	// PostScript Language Ref. Man. page 712
	char login[MAXNAME];
	char date[MAXNAME];
	System::GetLoginName(login);
	System::GetTime(date);
	fprintf(fd, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(fd, "%%%%Title: %s\n", title);
	fprintf(fd, "%%%%Creator: %s\n", creator);
	fprintf(fd, "%%%%CreationDate: %s\n", date);
	fprintf(fd, "%%%%For: %s\n", login);
	fprintf(fd, "%%%%DocumentFonts: (atend)\n");
	fprintf(fd, "%%%%Pages: 0\n");
	llx = llx * factor;
	lly = lly * factor;
	urx = urx * factor;
	ury = ury * factor;
	fprintf(fd, "%%%%BoundingBox: %f %f %f %f\n", llx, lly, urx, ury);
	fprintf(fd, "%%%%EndComments\n");
}

void PSGrafport::PageSetup() {
	// default transformation
	// move to imagable area
	fprintf(fd, "%f %f translate\n", XOFF, YOFF);
	// factor between pixel size and point size
	fprintf(fd, "%f %f scale\n", factor, factor);
	if (width < height)  {
		// Portrait mode: change to X coordinate system
		fprintf(fd, "0 %f translate\n", height);
		fprintf(fd, "1 -1 scale\n");
	}
	else {
		// Landscape mode: change to X coordinate system
		fprintf(fd, "90 rotate\n");
		fprintf(fd, "1 -1 scale\n");
	}
	fprintf(fd, "%f setlinewidth\n", GetLineWidth() * DEFAULT_LINE_WIDTH);
}

void PSGrafport::EPSProlog(double lly, double dy) {
	FontProlog();
	// default transformation
	// factor between pixel size and point size
	fprintf(fd, "%f %f scale\n", factor, factor);
	lly *= factor;
	dy *= factor;
	// change to X coordinate system
	// look at how EPSF files are used in Ref. Man. page 712
	fprintf(fd, "0 %f 2 mul %f add %f div translate\n", lly, dy, factor);
	fprintf(fd, "1 -1 scale\n");
	fprintf(fd, "%f %f scale\n", GetZoomValue(), GetZoomValue());
	fprintf(fd, "%f setlinewidth\n", GetLineWidth() * DEFAULT_LINE_WIDTH);
	fprintf(fd, "%%%%EndProlog\n");
}

void PSGrafport::SetLineWidth(unsigned int w) {
	if (w == GetLineWidth())
		return;
	Grafport::SetLineWidth(w);
	fprintf(fd, "%f setlinewidth\n", GetLineWidth() * DEFAULT_LINE_WIDTH);
}

void PSGrafport::SetFont(XFont *f) {
	Grafport::SetFont(f);
	char fname[MAXNAME];
	GetFont()->GetPostScript(fname);
	if (isoLatin1Encoding && !equal(fname, "/Symbol")) {
		if (!definedFonts.contains(fname)) {
			InstallIsoLatin1Font(fname);
			definedFonts.add(fname);
		}
		strcat(fname, "-ISOLatin1Encoding");
	}
	fprintf(fd, "%s findfont\n", fname);
	fprintf(fd, "%d scalefont setfont\n", (int) f->GetSize());
}

void PSGrafport::BeginPage(int i, int j, int nx, int tot) {
	fprintf(fd, "%%%%Page: %d %d\n", i+nx*(j-1), tot);
	// default transformation
	PageSetup();
	fprintf(fd, "%%%%BeginPageSetup\n");
	double dx = (i-1) * width;
	double dy = (j-1) * height;
	fprintf(fd, "gsave\n");
	fprintf(fd, "-%f -%f translate\n", dx, dy);
	fprintf(fd, "%f %f scale\n", GetZoomValue(), GetZoomValue());
	fprintf(fd, "%%%%EndPageSetup\n");
}

void PSGrafport::EndPage() {
	fprintf(fd, "grestore\n");
	fprintf(fd, "showpage\n");
	fprintf(fd, "%%%%PageTrailer\n");
}

void PSGrafport::Trailer() {
	fprintf(fd, "%%%%Trailer\n");
	fprintf(fd, "%%%%EOF\n");
}

void PSGrafport::DrawRectangle(double x, double y, double wd, double ht) {
	if (GetLineStyle()==LineStyle::INVISIBLE &&
            GetFillStyle()==FillStyle::UNFILLED)
                return;
	SetPSDashes();
	DrawPSRectangle(x, y, wd, ht);
	if (GetLineStyle()==LineStyle::DUAL) {
		int n = 2*GetLineWidth();
		if (ht > 2*n && wd > 2*n)
			DrawPSRectangle(x+n, y+n, wd-2*n, ht-2*n);
	}
	UnsetPSDashes();
}

void PSGrafport::DrawPSRectangle(double x, double y, double wd, double ht) {
	fprintf(fd, "newpath\n");
	fprintf(fd, "   %f %f moveto\n", x, y);
	fprintf(fd, "   %f 0  rlineto\n", wd);
	fprintf(fd, "   0 %f  rlineto\n", ht);
	fprintf(fd, "   -%f 0 rlineto\n", wd);
	fprintf(fd, "   closepath\n");
	if (GetFillStyle()==FillStyle::UNFILLED || 
	    (!showColors && *GetForegroundColor() != "black"))
		fprintf(fd, "   stroke\n");
	else
		fprintf(fd, "   fill\n");
}

void PSGrafport::DrawUnzoomedRectangle(double x, double y, double wd, double ht) {
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f scale\n", 1/GetZoomValue(), 1/GetZoomValue());
	DrawRectangle(x, y, wd, ht);
	fprintf(fd, "grestore\n");
}

void PSGrafport::FillRectangle(double x, double y, double wd, double ht) {
	SetFillStyle(FillStyle::FILLED);
	DrawRectangle(x, y, wd, ht);
	SetFillStyle(FillStyle::UNFILLED);
}

//void PSGrafport::DrawRoundedRectangle(double x, double y, double wd, double ht, double rd) {
//	if (GetLineStyle()==LineStyle::INVISIBLE &&
//            GetFillStyle()==FillStyle::UNFILLED)
//                return;
//	SetPSDashes();
//	DrawPSRoundedRectangle(x, y, wd, ht, rd);
//	if (GetLineStyle()==LineStyle::DUAL) {
//		int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)
//			DrawPSRoundedRectangle(x+n, y+n, wd-2*n, ht-2*n, rd);
//	}
//	UnsetPSDashes();
//}
//
//void PSGrafport::DrawPSRoundedRectangle(double x, double y, double wd, double ht, double rd) {
//	// draw four lines (without the corner parts).
//	DrawPSLine(x, y+rd, x, y+ht-rd);
//	DrawPSLine(x+rd, y+ht, x+wd-rd, y+ht);
//	DrawPSLine(x+wd, y+ht-rd, x+wd, y+rd);
//	DrawPSLine(x+wd-rd, y, x+rd, y);
//	// draw four corner arcs.
//	fprintf(fd, "newpath\n");
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+rd, rd, 180, 270); 
//	fprintf(fd, "    stroke\n");
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+ht-rd, rd, 90, 180); 
//	fprintf(fd, "    stroke\n");
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+ht-rd, rd, 0, 90); 
//	fprintf(fd, "    stroke\n");
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+rd, rd, 270, 360); 
//	fprintf(fd, "    stroke\n");
//}
//
//void PSGrafport::FillRoundedRectangle(double x, double y, double wd, double ht, double rd) {
//	if (!showColors && !(*GetForegroundColor() == "black")) {
//		DrawRoundedRectangle(x, y, wd, ht, rd);
//		return;
//	}
//	FillRectangle(x+rd, y, wd-2*rd, rd);
//	FillRectangle(x, y+rd, wd, ht-2*rd);
//	FillRectangle(x+rd, y+ht-rd, wd-2*rd, rd);
//	fprintf(fd, "newpath\n");
//	fprintf(fd, "    %f %f moveto\n", x+rd, y+rd);
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+rd, rd, 180, 270); 
//	fprintf(fd, "    %f %f moveto\n", x+rd, y+ht-rd);
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+ht-rd, rd, 90, 180); 
//	fprintf(fd, "    %f %f moveto\n", x+wd-rd, y+ht-rd);
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+ht-rd, rd, 0, 90); 
//	fprintf(fd, "    %f %f moveto\n", x+wd-rd, y+rd);
//	fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+rd, rd, 270, 360); 
//	fprintf(fd, "    fill\n");
//}
//
//void PSGrafport::DrawEllipsedRectangle(double x, double y, double wd, double ht, double rd) {
//	if (GetLineStyle()==LineStyle::INVISIBLE &&
//            GetFillStyle()==FillStyle::UNFILLED)
//                return;
//	SetPSDashes();
//        DrawPSEllipsedRectangle(x, y, wd, ht, rd);
//        if (GetLineStyle()==LineStyle::DUAL) {
//                int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)
//                	DrawPSEllipsedRectangle(x+n, y+n, wd-2*n, ht-2*n, rd-n);
//        }
//	UnsetPSDashes();
//}
// 
//void PSGrafport::DrawPSEllipsedRectangle(double x, double y, double wd, double ht, double rd) {
//        // draw two lines (without the corner parts).
//        DrawPSLine(x+rd, y, x+wd-rd, y);
//        DrawPSLine(x+rd, y+ht, x+wd-rd, y+ht);
//        // draw two half circles.
//        fprintf(fd, "newpath\n");
//        fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+rd, rd, 90, 270);
//        fprintf(fd, "    stroke\n");
//        fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+rd, rd, 270, 90);
//        fprintf(fd, "    stroke\n");
//}
// 
//void PSGrafport::FillEllipsedRectangle(double x, double y, double wd, double ht, double rd) {
//        if (!showColors && !(*GetForegroundColor() == "black")) {
//                DrawEllipsedRectangle(x, y, wd, ht, rd);
//                return;
//        }
//        FillRectangle(x+rd, y, wd-2*rd, ht);
//        fprintf(fd, "newpath\n");
//        fprintf(fd, "    %f %f moveto\n", x+rd, y+rd);
//        fprintf(fd, "    %f %f %f %d %d arc\n", x+rd, y+rd, rd, 90, 270);
//        fprintf(fd, "    %f %f moveto\n", x+wd-rd, y+rd);
//        fprintf(fd, "    %f %f %f %d %d arc\n", x+wd-rd, y+rd, rd, 270, 90);
//        fprintf(fd, "    fill\n");
//}
// 
//void PSGrafport::DrawDisk(double x, double y, double wd, double ht, double rd) {
//	if (GetLineStyle()==LineStyle::INVISIBLE &&
//            GetFillStyle()==FillStyle::UNFILLED)
//                return;
//	SetPSDashes();
//        DrawPSDisk(x, y, wd, ht, rd);
//        if (GetLineStyle()==LineStyle::DUAL) {
//                int n = 2*GetLineWidth();
//		if (ht > 2*n && wd > 2*n)
//                	DrawPSDisk(x+n, y+n, wd-2*n, ht-2*n, rd-2*n);
//        }
//	UnsetPSDashes();
//}
// 
//void PSGrafport::FillDisk(double x, double y, double wd, double ht, double el) {
//	SetFillStyle(FillStyle::FILLED);
//	DrawDisk(x, y, wd, ht, el);
//	FillRectangle(x, y+el/2, wd, ht-el);
//	SetFillStyle(FillStyle::UNFILLED);
//}
// 
//void PSGrafport::DrawPSDisk(double x, double y, double wd, double ht, double el) {
//        LineStyle::Type save = GetLineStyle();
//        if (save==LineStyle::DUAL)
//                SetLineStyle(LineStyle::SOLID);
//        // draw two lines (without the corner points).
//	double ah = el/2;
//        DrawPSLine(x, y+ah+1, x, y+ht-ah-1);
//        DrawPSLine(x+wd, y+ah+1, x+wd, y+ht-ah-1);
//        if (save==LineStyle::DUAL)
//                SetLineStyle(LineStyle::DUAL);
//        // draw 1st ellipse.
//	DrawPSArc(x, y, wd, el, 0, 360);
//	// draw half ellipse
//	DrawPSArc(x, y+ht-el, wd, el, 0, -180);
//}

void PSGrafport::DrawStringLeft(double x, double y, const char *str) {
	string copy = str;
	MakePSString(&copy);
	const char *newstr = copy.getstr();
	fprintf(fd, "%f %f moveto\n", x, y);
	fprintf(fd, "gsave\n");
	fprintf(fd, "1 -1 scale\n");
	fprintf(fd, "(%s) show\n", newstr);
	fprintf(fd, "grestore\n");
}

void PSGrafport::DrawUnzoomedStringLeft(double x, double y, const char *str) {
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f scale\n", 1/GetZoomValue(), 1/GetZoomValue());
	DrawStringLeft(x, y, str);
	fprintf(fd, "grestore\n");
}

void PSGrafport::DrawStringRight(double x, double y, const char *str){
	string copy = str;
	MakePSString(&copy);
	const char *newstr = copy.getstr();
	fprintf(fd, "(%s) stringwidth\n", newstr);
	fprintf(fd, "pop neg\n");
	fprintf(fd, "%f add %f moveto\n", x, y);
	fprintf(fd, "gsave\n");
	fprintf(fd, "1 -1 scale\n");
	fprintf(fd, "(%s) show\n", newstr);
	fprintf(fd, "grestore\n");
}

void PSGrafport::DrawStringCentered(double x, double y, const char *str) {
	string copy = str;
	MakePSString(&copy);
	const char *newstr = copy.getstr();
	double dy = GetFont()->GetHeight() / 2 - GetFont()->GetDescent();
	fprintf(fd, "(%s) stringwidth\n", newstr);
	fprintf(fd, "pop 2 div neg\n");
	fprintf(fd, "%f add %f moveto\n", x, y + dy);
	fprintf(fd, "gsave\n");
	fprintf(fd, "1 -1 scale\n");
	fprintf(fd, "(%s) show\n", newstr);
	fprintf(fd, "grestore\n");
}


//Underlined Strings
void PSGrafport::DrawStringLeftUnderlined(double x, double y, const char *str){
	DrawStringLeft(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringLeft... : Corrected Height for y ( == topLefty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	DrawPSLine(x, y + cht, x + wd, y + cht);
}

void PSGrafport::DrawStringRightUnderlined(double x, double y, const char *str){
	DrawStringRight(x, y, str);
	int wd = GetFont()->StringWidth(str);
	// DrawStringRight... : Corrected Height for y ( == topRighty + GetAscent()) 
	int cht = GetFont()->GetHeight() - GetFont()->GetAscent();
	DrawPSLine(x - wd, y + cht, x, y + cht);
}

void PSGrafport::DrawStringCenteredUnderlined(double x, double y, const char *str) {
	DrawStringCentered(x, y, str);
	int wd = GetFont()->StringWidth(str);
	int ht = GetFont()->GetHeight();
	DrawPSLine(x - wd/2, y + ht/2, x + wd/2, y + ht/2);
}

void PSGrafport::MakePSString(string *str) {
	FixEscapeChar(str, '\\');
	FixEscapeChar(str, '(');
	FixEscapeChar(str, ')');
	FixEscapeChar(str, '*');
	FixNonAscii(str);
}

void PSGrafport::DrawUnzoomedStringCentered(double x, double y, const char *str) {
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f scale\n", 1/GetZoomValue(), 1/GetZoomValue());
	DrawStringCentered(x, y, str);
	fprintf(fd, "grestore\n");
}

//void PSGrafport::DrawLine(double x1, double y1, double x2, double y2) {
//	if (x1 == x2 && y1 == y2)
//		return;
//	if (GetLineStyle()==LineStyle::INVISIBLE)
//		return;
//	else if (GetLineStyle()==LineStyle::DASHED)
//		fprintf(fd, "[4 2] 0 setdash\n");
//	else if (GetLineStyle()==LineStyle::DOTTED) 
//		fprintf(fd, "[1 1] 0 setdash\n");
//	else if (GetLineStyle()==LineStyle::WIDE_DOTTED)
//		fprintf(fd, "[2 2] 0 setdash\n");
//	if (GetLineStyle()==LineStyle::DUAL) {
//		int n = GetLineWidth();
//		if (y1 == y2) {  // horizontal
//			DrawPSLine(x1, y1+n, x2, y2+n);
//			DrawPSLine(x1, y1-n, x2, y2-n);
//		}
//		else if (x1 == x2) {  // vertical
//			DrawPSLine(x1+n, y1, x2+n, y2);
//			DrawPSLine(x1-n, y1, x2-n, y2);
//		}
//		else {
//			DrawPSLine(x1, y1, x2, y2);
//			DrawPSLine(x1, y1+2*n, x2, y2+2*n);
//		}
//	}
//	else
//		DrawPSLine(x1, y1, x2, y2);
//	UnsetPSDashes();
//}

void PSGrafport::DrawPSLine(double x1, double y1, double x2, double y2) {
	fprintf(fd, "newpath\n");
	fprintf(fd, "    %f %f moveto\n", x1, y1);
	fprintf(fd, "    %f %f lineto\n", x2, y2);
	fprintf(fd, "    stroke\n");
}

void PSGrafport::DrawUnzoomedLine(double x1, double y1, double x2, double y2) {
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f scale\n", 1/GetZoomValue(), 1/GetZoomValue());
	DrawLine(x1, y1, x2, y2);
	fprintf(fd, "grestore\n");
}


//void PSGrafport::DrawCurve(const Point *p0, const Point *p1, 
//			   const Point *p2, const Point *p3) {
//	if (GetLineStyle()==LineStyle::INVISIBLE)
//		return;
//	if (GetLineStyle()==LineStyle::DASHED)
//		fprintf(fd, "[4 2] 0 setdash\n");
//	if (GetLineStyle()==LineStyle::DOTTED)
//		fprintf(fd, "[1 1] 0 setdash\n");
//	if (GetLineStyle()==LineStyle::WIDE_DOTTED)
//		fprintf(fd, "[2 2] 0 setdash\n");
//	fprintf(fd, "newpath\n");
//	fprintf(fd, "    %d %d moveto\n", p0->x, p0->y);
//	fprintf(fd, "    %d %d %d %d %d %d curveto\n", p1->x, p1->y,
//		p2->x, p2->y, p3->x, p3->y);
//	fprintf(fd, "    stroke\n");
//	UnsetPSDashes();
//}


void PSGrafport::DrawSimpleCurve(const DPoint *p) {
	if (GetLineStyle()==LineStyle::INVISIBLE)
		return;
	if (GetLineStyle()==LineStyle::DASHED)
		fprintf(fd, "[4 2] 0 setdash\n");
	if (GetLineStyle()==LineStyle::DOTTED)
		fprintf(fd, "[1 1] 0 setdash\n");
	if (GetLineStyle()==LineStyle::WIDE_DOTTED)
		fprintf(fd, "[2 2] 0 setdash\n");
	fprintf(fd, "newpath\n");
	fprintf(fd, "    %f %f moveto\n", p[0].x, p[0].y);
	fprintf(fd, "    %f %f %f %f %f %f curveto\n", p[1].x, p[1].y,
		p[2].x, p[2].y, p[3].x, p[3].y);
	fprintf(fd, "    stroke\n");
	UnsetPSDashes();
}


void PSGrafport::DrawPoint(double x, double y) {
	DrawLine(x, y, x, y);
}


/* virtual */ void PSGrafport::DrawSimpleArc(double x, double y,
	double wd, double ht, int arc1, int arc2)
{
	if (GetLineStyle()==LineStyle::INVISIBLE &&
            GetFillStyle()==FillStyle::UNFILLED)
                return;
	SetPSDashes();
	fprintf(fd, "/savematrix matrix currentmatrix def\n");
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f translate\n", x, y);
	fprintf(fd, "%f %f scale\n", wd, ht);
	fprintf(fd, "newpath\n");
	fprintf(fd, "    0.5 0.5 0.5 %d %d arc\n", 359 - arc2, 361 - arc1);
	// draw a little bit more to avoid hiati in arcs.
	// fprintf(fd, "    closepath\n");
	fprintf(fd, "savematrix setmatrix\n");
	fprintf(fd, "    stroke\n");
	fprintf(fd, "grestore\n");
	UnsetPSDashes();
}


/* virtual */ void PSGrafport::FillSegment(double x, double y,
	double wd, double ht, int arc1, int arc2)
{
	SetPSDashes();
	fprintf(fd, "/savematrix matrix currentmatrix def\n");
	fprintf(fd, "gsave\n");
	fprintf(fd, "%f %f translate\n", x, y);
	fprintf(fd, "%f %f scale\n", wd, ht);
	fprintf(fd, "newpath\n");
	fprintf(fd, "    0.5 0.5 0.5 %d %d arc\n", 360 - arc2, 360 - arc1);
	// fprintf(fd, "    closepath\n");
	fprintf(fd, "savematrix setmatrix\n");
	if ( ! showColors && *GetForegroundColor() != "black" )
		fprintf(fd, "    stroke\n");
	else
		fprintf(fd, "    fill\n");
	fprintf(fd, "grestore\n");
	UnsetPSDashes();
}


//void PSGrafport::FillArc(double x, double y, double wd, double ht, int arc1, int arc2) {
//	SetFillStyle(FillStyle::FILLED);
//	DrawArc(x, y, wd, ht, arc1, arc2);
//	SetFillStyle(FillStyle::UNFILLED);
//}
//
//void PSGrafport::DrawPSArc(double x, double y, double wd, double ht, int ang1, int ang2) {
//	fprintf(fd, "/savematrix matrix currentmatrix def\n");
//	fprintf(fd, "gsave\n");
//	fprintf(fd, "%f %f translate\n", x, y);
//	fprintf(fd, "%f %f scale\n", wd, ht);
//	fprintf(fd, "newpath\n");
//	fprintf(fd, "    0.5 0.5 0.5 %d %d arc\n", ang1, ang2);
//	// fprintf(fd, "    closepath\n");
//	fprintf(fd, "savematrix setmatrix\n");
//	if (GetFillStyle()==FillStyle::UNFILLED ||
//            (!showColors && *GetForegroundColor()!="black"))
//		fprintf(fd, "    stroke\n");
//	else
//		fprintf(fd, "    fill\n");
//	fprintf(fd, "grestore\n");
//}


void PSGrafport::DrawPolygon(const Point *points, int n) {
	if (GetLineStyle()==LineStyle::INVISIBLE &&
            GetFillStyle()==FillStyle::UNFILLED)
                return;
        SetPSDashes();
	DrawPSPolygon(points, n);
        if (GetLineStyle()==LineStyle::DUAL) {
		int w = 2*GetLineWidth();
                Point *newPoints = new Point[n];
                RecalcPolygon(points, n, newPoints, w);
                DrawPSPolygon(newPoints, n);
                delete newPoints;
        }
        UnsetPSDashes();
}


void PSGrafport::DrawPSPolygon(const Point *points, int n) {
	if (n < 1) 
		return;
	fprintf(fd, "newpath\n");
	fprintf(fd, "    %d %d moveto\n", points[0].x, points[0].y);
	for (int i=1; i<n; i++) {
		fprintf(fd, "    %d %d lineto\n", points[i].x, points[i].y);
	}
	fprintf(fd, "    %d %d lineto\n", points[0].x, points[0].y);
	fprintf(fd, "    closepath\n");
	if (GetFillStyle()==FillStyle::UNFILLED ||
            (!showColors && *GetForegroundColor()!="black"))
		fprintf(fd, "    stroke\n");
	else
		fprintf(fd, "    fill\n");
}


/* virtual */ void PSGrafport::DrawSimplePolygon(const DPoint *points,
	int n)
{
	if (GetLineStyle()==LineStyle::INVISIBLE || n < 2)
		return;
	SetPSDashes();
	if (n < 2)
		return;
	fprintf(fd, "newpath\n");
	fprintf(fd, "    %f %f moveto\n", points[0].x, points[0].y);
	bool closed = False;
	if ( points[0] == points[n - 1] ) {
		n--;
		closed = True;
	}
	for ( int i=1 ; i<n ; i++ )
		fprintf(fd, "    %f %f lineto\n", points[i].x, points[i].y);
	if ( closed )
		fprintf(fd, "    closepath\n");
	fprintf(fd, "    stroke\n");
	UnsetPSDashes();
}


void PSGrafport::FillPolygon(const Point *points, int n) {
	SetFillStyle(FillStyle::FILLED);
	DrawPolygon(points, n);
	SetFillStyle(FillStyle::UNFILLED);
}


void PSGrafport::FillPolygon(const DPoint *points, int n) {
	if (n < 2)
		return;
	fprintf(fd, "newpath\n");
	fprintf(fd, "    %f %f moveto\n", points[0].x, points[0].y);
	for ( int i=1 ; i<n ; i++ )
		fprintf(fd, "    %f %f lineto\n", points[i].x, points[i].y);
	fprintf(fd, "    closepath\n");
	fprintf(fd, "    fill\n");
}


void PSGrafport::FixEscapeChar(string *str, char c) {
	string pat = c;
	string repl = "\\" + pat;
	str->replace(pat, repl);
}


void PSGrafport::FixNonAscii(string *str) {
	char buf[8];
	string newstr;
	for (unsigned i=0; i<str->length(); i++) {
		unsigned char c = (*str)[i];
		if (!isascii(c)) {
			sprintf(buf, "\\%o", c);
			newstr += buf;
		}
		else
			newstr.add(c);
	}
	*str = newstr;
}

void PSGrafport::FontProlog() {
	if (!isoLatin1Encoding)
		return;
	fprintf(fd, "/ISOLatin1Encoding[\n");
	fprintf(fd, "/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n");
	fprintf(fd, "/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n");
	fprintf(fd, "/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n");
	fprintf(fd, "/.notdef/.notdef/.notdef/.notdef/.notdef/space/exclam/quotedbl/numbersign\n");
	fprintf(fd, "/dollar/percent/ampersand/quoteright/parenleft/parenright/asterisk/plus/comma\n");
	fprintf(fd, "/minus/period/slash/zero/one/two/three/four/five/six/seven/eight/nine/colon\n");
	fprintf(fd, "/semicolon/less/equal/greater/question/at/A/B/C/D/E/F/G/H/I/J/K/L/M/N/O/P/Q/R/S\n");
	fprintf(fd, "/T/U/V/W/X/Y/Z/bracketleft/backslash/bracketright/asciicircum/underscore\n");
	fprintf(fd, "/quoteleft/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/p/q/r/s/t/u/v/w/x/y/z/braceleft/bar\n");
	fprintf(fd, "/braceright/asciitilde/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef\n");
	fprintf(fd, "/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/.notdef/space\n");
	fprintf(fd, "/dotlessi/grave/acute/circumflex/tilde/macron/breve/dotaccent/dieresis/.notdef\n");
	fprintf(fd, "/ring/cedilla/.notdef/hungarumlaut/ogonek/caron/.notdef/exclamdown/cent\n");
	fprintf(fd, "/sterling/currency/yen/brokenbar/section/dieresis/copyright/ordfeminine\n");
	fprintf(fd, "/guillemotleft/logicalnot/hyphen/registered/macron/degree/plusminus/twosuperior\n");
	fprintf(fd, "/threesuperior/acute/mu/paragraph/periodcentered/cedilla/onesuperior\n");
	fprintf(fd, "/ordmasculine/guillemotright/onequarter/onehalf/threequarters/questiondown\n");
	fprintf(fd, "/Agrave/Aacute/Acircumflex/Atilde/Adieresis/Aring/AE/Ccedilla/Egrave/Eacute\n");
	fprintf(fd, "/Ecircumflex/Edieresis/Igrave/Iacute/Icircumflex/Idieresis/Eth/Ntilde/Ograve\n");
	fprintf(fd, "/Oacute/Ocircumflex/Otilde/Odieresis/multiply/Oslash/Ugrave/Uacute/Ucircumflex\n");
	fprintf(fd, "/Udieresis/Yacute/Thorn/germandbls/agrave/aacute/acircumflex/atilde/adieresis\n");
	fprintf(fd, "/aring/ae/ccedilla/egrave/eacute/ecircumflex/edieresis/igrave/iacute\n");
	fprintf(fd, "/icircumflex/idieresis/eth/ntilde/ograve/oacute/ocircumflex/otilde/odieresis\n");
	fprintf(fd, "/divide/oslash/ugrave/uacute/ucircumflex/udieresis/yacute/thorn/ydieresis\n");
	fprintf(fd, "] def\n");
}

void PSGrafport::InstallIsoLatin1Font(const char *psFont) {
	fprintf(fd, "%s findfont\n", psFont);
	fprintf(fd, "dup length dict begin\n");
  	fprintf(fd, "   {1 index /FID ne {def} {pop pop} ifelse} forall\n");
  	fprintf(fd, "   /Encoding ISOLatin1Encoding def\n");
  	fprintf(fd, "   currentdict\n");
	fprintf(fd, "end\n");
	fprintf(fd, "%s-ISOLatin1Encoding exch definefont pop\n", psFont);
}

void PSGrafport::SetPSDashes() {
	if (GetLineStyle()==LineStyle::INVISIBLE &&
	    GetFillStyle()==FillStyle::UNFILLED)
		return;
	else if (GetLineStyle()==LineStyle::DASHED)
		fprintf(fd, "[4 2] 0 setdash\n");
	else if (GetLineStyle()==LineStyle::DOTTED)
		fprintf(fd, "[1 1] 0 setdash\n");
	else if (GetLineStyle()==LineStyle::WIDE_DOTTED)
		fprintf(fd, "[2 2] 0 setdash\n");
}

void PSGrafport::UnsetPSDashes() {
	if (GetLineStyle()==LineStyle::DASHED || 
	    GetLineStyle()==LineStyle::DOTTED ||
	    GetLineStyle()==LineStyle::WIDE_DOTTED)
		fprintf(fd, "[] 0 setdash\n");
}
