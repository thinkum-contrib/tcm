//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _BITMAP_H
#define _BITMAP_H

#include <X11/Intrinsic.h>

/// datatype for storing an X bitmap.
class Bitmap { 	
/*@Doc: {\large {\bf scope:} GUI} */
public:
	/// width in pixels.
	int xbm_width;

	/// height in pixels.
	int xbm_height;

	/// bit string.
	unsigned char *xbm_bits;

	/// returns a color pixmap from the bitmap.
	Pixmap CreatePixmap(Widget w, Display *display) const;

	/// returns the bitmap as pixmap.
	Pixmap GetBitmap(Widget w, Display *display) const;

	// default icon.
	static const Bitmap DEFAULT_ICON;
};
#endif
