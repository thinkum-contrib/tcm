//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _XFONT_H
#define _XFONT_H

#include "afont.h"
#include "util.h"
#include <X11/Xlib.h>

/// A class for X fonts.
class XFont: public AFont {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// Creates new X font with the specified name, style and point size.
	XFont(const string *foundry, int name, int style, int size, 
		bool scalable);
	///
	~XFont();

	/// scale the X font (if scalable) with factor.
	void Scale(double factor);

	/// Gets family name from X font description.
	static int FindFamily(const char *desc);

	/// Gets font style from X font description.
	static int FindStyle(const char *desc);

	/// Gets point size from X font description.
	static int FindSize(const char *desc);

	/// Gets the standard leading, or line spacing, for the font.
	int GetLeading() { return 0; }

	/// Gets font ascent (distance from base line to top of characters).
	int GetAscent();

	/// Gets font descent (distance from base line to bottom of characters).
	int GetDescent();

	/// Gets total height of font (= is leading + ascent + descent) 
	int GetHeight() { return GetLeading() + GetAscent() + GetDescent(); }

	/// Gets the maximum ascent of all characters in this Font.
	int GetMaxAscent() { return GetAscent(); }

	/// Gets the maximum descent of all characters.
	int GetMaxDescent() { return GetDescent(); }

	/// Gets maximum advance width of any character (-1 if unknown).
	int GetMaxAdvance() { return -1; }

	/// Returns width of specified String in Font.
	int StringWidth(const string *str);

	/// see above.
	int StringWidth(const char *str);

	/// calculates height and width of multiline string in grafport.
	void Box(const string *s, int &wd, int &ht);

	/// see above.
	void Box(const char *s, int &wd, int &ht);

	/// Return x font id of stored X font.
	long GetXFid() {return xFont->fid; }

	/// Get XLFD description.
	void GetXLFD(char *xd);

	/// Get XLFD description.
	void GetXLFD(string *xd);

	/// Get PostScript name of this Font.
	void GetPostScript(char *ps);

	///
	XFontStruct *GetXFontStruct() {return xFont;}

protected:
	/// Calculate X logical font description.
	void CalcXLFD(string *fn, bool scalable);
	///
	static bool IsScalableFont(const string *name);
	///
	static XFontStruct *LoadQueryScalableFont(Display *d, 
		const char *name, int size);
private:
	/// X font struct corresponding to this font.
	XFontStruct *xFont;

	///
	Display *display;

	/// the full XLFD fontname.
	string fontName;
};
#endif
