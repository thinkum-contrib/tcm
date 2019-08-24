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
#include "bitmap.h"
#include <Xm/XmStrDefs.h>
#include <X11/Shell.h>

// X bitmap data used for default icon.
#include "Default.xbm"
// default icon.
const Bitmap Bitmap::DEFAULT_ICON = 
	{Default_width, Default_height, Default_bits};
 
Pixmap Bitmap::GetBitmap(Widget w, Display *display) const {
	return XCreateBitmapFromData(display,
		RootWindowOfScreen(XtScreen(w)),
		(char *)xbm_bits, xbm_width, xbm_height);
}

Pixmap Bitmap::CreatePixmap(Widget w, Display *display) const {
	Pixel fg, bg;
	XtVaGetValues(w, XmNforeground, &fg, XmNbackground, &bg, 0);
	Screen *screen = XtScreen(w);
	return XCreatePixmapFromBitmapData(display,
			RootWindowOfScreen(screen),
			(char *)xbm_bits, xbm_width, xbm_height,
			fg, bg,
			DefaultDepthOfScreen(screen));
}
