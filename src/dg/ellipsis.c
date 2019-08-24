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
#include "grafport.h"
#include "ellipsis.h"

const int Ellipsis::ELLIPSIS_WIDTH = 40; 
const int Ellipsis::ELLIPSIS_HEIGHT = 30;
const int Ellipsis::DOT_WIDTH = 6; 
const int Ellipsis::DOT_HEIGHT = 6;

Ellipsis::Ellipsis(ShapeView *v, Grafport *g, int x, int y, int w, int h): 
		Box(v,g,x,y,w,h) {
	SetHandles(MIN_HANDLES);
	SetFixedName(True);
	SetFixedIndexLabel(True);
	SetResizable(False);
}

Ellipsis::Ellipsis(const NodeShape &c): Box(c) {
	SetHandles(MIN_HANDLES);
	SetFixedName(True);
	SetFixedIndexLabel(True);
	SetResizable(False);
}

void Ellipsis::DrawShape() {
	Point pt = *GetPosition();
	int wd = DOT_WIDTH;
	int ht = DOT_HEIGHT;
	GetGrafport()->FillEllipse(pt.x-wd/2,		   pt.y-ht/2, wd, ht);
	GetGrafport()->FillEllipse(pt.x-wd/2-GetWidth()/3, pt.y-ht/2, wd, ht);	
	GetGrafport()->FillEllipse(pt.x-wd/2+GetWidth()/3, pt.y-ht/2, wd, ht);	
	GetGrafport()->DrawEllipse(pt.x-wd/2,		   pt.y-ht/2, wd, ht);
	GetGrafport()->DrawEllipse(pt.x-wd/2-GetWidth()/3, pt.y-ht/2, wd, ht);	
	GetGrafport()->DrawEllipse(pt.x-wd/2+GetWidth()/3, pt.y-ht/2, wd, ht);	
}
