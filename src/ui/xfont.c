////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "xfont.h"
#include "application.h"
#include <stdlib.h>
#include <stdio.h>

XFont::XFont(const string *fy, int fam, int st, int sz, bool sc):
		AFont(fy, fam, st, sz, sc) {
	CalcXLFD(&fontName, IsScalable());
	display = theApplication->GetDisplay();
	if (IsScalable()) {
		xFont = LoadQueryScalableFont(display, 
						fontName.getstr(), sz*10);
		if (!xFont) {
			error("Warning: X server has no scalable font %s, "
				"using unscalable fonts instead\n", 
				fontName.getstr());
			SetScalable(False);
		}
		else
			return;
	}
	xFont = XLoadQueryFont(display, fontName.getstr());
	if (!xFont) {
		error("Warning: Cannot open unscalable font %s, using fixed\n",
	 		fontName.getstr());
		xFont = XLoadQueryFont(display, "fixed");
	}
}

XFont::~XFont() {
	if (xFont)
		XFreeFont(display, xFont);
}

void XFont::Scale(double f) {
	if (f == GetFactor())
		return;
	if (IsScalable() && IsScalableFont(&fontName)) {
		XFontStruct *newFont; 
		newFont = LoadQueryScalableFont(display, fontName.getstr(), 
			  (int)(f*(GetSize()*10)));
		if (!newFont){
			error("Warning: Cannot open font %s\n", 
				fontName.getstr());
			return;
		}
		else {
			if (xFont)
				XFreeFont(display, xFont);
			xFont = newFont;
		}
		SetFactor(f);
	}
}
 
int XFont::GetAscent() {
	if (xFont)
		return (int)(xFont->max_bounds.ascent/ GetFactor());
	else
		return 0;
}
 
int XFont::GetDescent() {
	if (xFont)
		return (int)(xFont->max_bounds.descent/ GetFactor());
	else
		return 0;
}

void XFont::Box(const char *text, int &wd, int &ht) {
	string s(text);
	Box(&s, wd, ht);
}

void XFont::Box(const string *text, int &wd, int &ht) {
	string buf = "";
	if (text->length() == 0){
		ht = 0;
		wd = 0;
		return;
	}
	int w;
	int lineNo = 1;
	int nLines = text->lines();
	int w_max = 0;
	const char *lstr = text->getstr();
	while (lineNo <= nLines) {
		buf.add(*lstr);
		if (*lstr == '\n' || *lstr == '\r' || *lstr == '\0') {
			w = StringWidth(&buf);
			if (w>w_max)
				w_max = w;
			lineNo++;
			buf = "";
		}
		lstr++;
	}
	ht = (int) (nLines * GetHeight());
	wd = (int) w_max;
}

int XFont::StringWidth(const string *s) {
	return StringWidth(s->getstr());
}

int XFont::StringWidth(const char *s) {
	if (xFont)
		return (int)(XTextWidth(xFont, s, strlen(s))/GetFactor());
	else
		return 0;
}

int XFont::FindFamily(const char *desc) {
	if (strstr(desc, "helvetica") != 0)
		return HELVETICA;
	else if (strstr(desc, "times") != 0)
		return TIMESROMAN;
	else if (strstr(desc, "courier") != 0)
		return COURIER;
	else if (strstr(desc, "new century schoolbook") != 0)
		return NEWCENTURYSCHLBK;
	else if (strstr(desc, "symbol") != 0)
		return SYMBOL;
	else
		return HELVETICA;
}

int XFont::FindStyle(const char *desc) {
	int res = 0;
	if (strstr(desc, "bold") != 0)
		res = 1;
	if (strstr(desc, "-i-") != 0)
		res += 2;
	if (strstr(desc, "-o-") != 0)
		res += 2;
	return res;
}

int XFont::FindSize(const char *desc) {
	const char *s = strpbrk(desc, "0123456789");
	if (!s)
		return 10;
	else
		return atoi(s);
}

void XFont::GetXLFD(string *fn) {
	CalcXLFD(fn, False);
}

void XFont::GetXLFD(char *fn) {
	string f = fn;
	CalcXLFD(&f, False);
}

void XFont::CalcXLFD(string *fn, bool scal) {
	char pt[MAXNAME];
	*fn = "-" + *GetFoundry() + "-";
	if (GetFamily() == HELVETICA) { *fn += "helvetica-"; }
	else if (GetFamily() == TIMESROMAN) { *fn += "times-"; }
	else if (GetFamily() == COURIER) { *fn += "courier-"; }
	else if (GetFamily() == NEWCENTURYSCHLBK) { 
		*fn += "new century schoolbook-"; }
	else if (GetFamily() == SYMBOL) { *fn += "symbol-"; }
	else {*fn += "*-"; }
	if (((GetStyle() & BOLD) != 0)  && (GetFamily() != SYMBOL))
		*fn += "bold-";
	else
		*fn += "medium-";
	if ((GetStyle() & ITALIC) != 0 && (GetFamily() != SYMBOL)) {
		if (GetFamily() == TIMESROMAN || 
		    GetFamily() == NEWCENTURYSCHLBK)
			*fn += "i-normal-";
		else
			*fn += "o-normal-";
	}
	else
		*fn += "r-normal-";
	// *fn += "*"; 
	if (scal) {
		*fn += "-0-0-*-*-*-0-*-*";
		check(IsScalableFont(fn));
	}
	else {
		sprintf(pt, "-%d*", GetSize());
		*fn += "-";
		*fn += GetSize();
		*fn += "*";
	}
}

void XFont::GetPostScript(char *ps) {
	if (GetFamily() == HELVETICA)
		strcpy(ps, "/Helvetica");
	else if (GetFamily() == TIMESROMAN)
		strcpy(ps, "/Times");
	else if (GetFamily() == COURIER) 
		strcpy(ps, "/Courier");
	else if (GetFamily() == NEWCENTURYSCHLBK) 
		strcpy(ps, "/NewCenturySchlbk");
	else if (GetFamily() == SYMBOL)
		strcpy(ps, "/Symbol");
	else
		strcpy(ps, "/Default");
	if (GetFamily() == HELVETICA || 
	    GetFamily()  == COURIER) {
		if (GetStyle() & BOLD) {
			if (GetStyle() & ITALIC)
				strcat(ps, "-BoldOblique");
			else
				strcat(ps, "-Bold");
		}
		else if (GetStyle() & ITALIC)
			strcat(ps, "-Oblique");
	}
	else if (GetFamily() == TIMESROMAN || 
		 GetFamily() == NEWCENTURYSCHLBK) {
		if (GetStyle() & BOLD) {
			if (GetStyle() & ITALIC)
				strcat(ps, "-BoldItalic");
			else
				strcat(ps, "-Bold");
		}
		else if (GetStyle() & ITALIC)
			strcat(ps, "-Italic");
		else 
			strcat(ps, "-Roman");
	}
}

//
// scalefonts.c
//
// Written by David Flanagan.  Copyright 1991, O'Reilly && Associates.
//
//    The X Consortium, and any party obtaining a copy of these files from
//    the X Consortium, directly or indirectly, is granted, free of charge, a
//    full and unrestricted irrevocable, world-wide, paid up, royalty-free,
//    nonexclusive right and license to deal in this software and
//    documentation files (the "Software"), including without limitation the
//    rights to use, copy, modify, merge, publish, distribute, sublicense,
//    and/or sell copies of the Software, and to permit persons who receive
//    copies from any such party to do so.  This license includes without
//    limitation a license to do the foregoing actions under any patents of
//    the party supplying this software to the X Consortium.
//
// This program demonstrates the use of scalable fonts in X11R5.
// Invoke it with a fully specified scalable font name as its
// only argument.  It will load that font scaled to 7 point,
// 11 point, 15 point, and 19 point precisely at the resolution
// of your screen.  It opens a very simple window and draws
// the font name at each of those point sizes.
//
//

//
// This routine returns True only if the passed name is a well-formed
// XLFD style font name with a pixel size, point size, and average
// width (fields 7,8, and 12) of "0".
// 
bool XFont::IsScalableFont(const string *name) {
    int i, field;
    
    if ((name == 0) || ((*name)[0] != '-')) 
	return False;
    
    for(i = field = 0; (*name)[i] != '\0' && field <= 14; i++) {
	if ((*name)[i] == '-') {
	    field++;
	    if ((field == 7) || (field == 8) || (field == 12))
		if (((*name)[i+1] != '0') || ((*name)[i+2] != '-'))
		    return False;
	}
    }
    
    if (field != 14) 
		return False;
    else 
		return True;
}


//
// This routine is passed a scalable font name and a point size.
// It returns an XFontStruct for the given font scaled to the 
// specified size and the exact resolution of the screen.
// The font name is assumed to be a well-formed XLFD name,
// and to have pixel size, point size, and average width fields
// of "0" and implementation dependent x-resolution and y- 
// resolution fields.  Size is specified in tenths of points.
// Returns 0 if the name is malformed or no such font exists.
//
XFontStruct *XFont::LoadQueryScalableFont(Display *dpy, const char *name, 
		int size) {
    int i,j, field;
    char newname[500];		// big enough for a long font name
    int res_x, res_y;		// resolution values for this screen
    
    // catch obvious errors
    if ((name == 0) || (name[0] != '-')) 
		return 0;
    
    // calculate our screen resolution in dots per inch. 25.4mm = 1 inch
    // int screen = DefaultScreen(dpy);
    // res_x = DisplayWidth(dpy, screen)/(DisplayWidthMM(dpy, screen)/25.4);
    // res_y = DisplayHeight(dpy, screen)/(DisplayHeightMM(dpy, screen)/25.4);
	res_x = 72;
	res_y = 72;
	res_x = 75;
	res_y = 75;
    
    // copy the font name, changing the scalable fields as we do so
    for(i = j = field = 0; name[i] != '\0' && field <= 14; i++) {
		newname[j++] = name[i];
		if (name[i] == '-') {
		    field++;
		    switch(field) {
			    case 7:  // pixel size 
			    case 12: // average width
					// change from "-0-" to "-*-"
					newname[j] = '*'; 
					j++;
					if (name[i+1] != '\0') i++;
					break;
			    case 8:  // point size
					// change from "-0-" to "-<size>-"
					(void)sprintf(&newname[j], "%d", size);
					while (newname[j] != '\0') j++;
					if (name[i+1] != '\0') i++;
					break;
			    case 9:  // x resolution 
			    case 10: // y resolution 
					// leave resolution unspecified
					newname[j] = '*'; 
					j++;
					while((name[i+1] != '-') && (name[i+1] != '\0')) i++;
					break;
		    }
		}
    }
    newname[j] = '\0';

    // if there aren't 14 hyphens, it isn't a well formed name
    if (field != 14) 
		return 0;
	return XLoadQueryFont(dpy, newname);
}
