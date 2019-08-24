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
//#include "grafport.h"
//#include "gshape.h"
//#include "shapeview.h"
//#include "diagram.h"
//#include "diagramviewer.h"
//#include "drawwindow.h"
#include "sizeshapecentercmd.h"
#include "nodeshape.h"

SizeShapeCenterCmd::SizeShapeCenterCmd(GShape *s, int dir)
	:SizeShapeCmd(s, dir)
{
	if ( ! constrainX ) {
		if ( 1 == dir || 4 == dir || 7 == dir )
			shape->GetShapeType()->GetLeft(&corner);
		else
			shape->GetShapeType()->GetRight(&corner);
	}
	if ( ! constrainY ) {
		if ( 3 == dir || 4 == dir || 5 == dir )
			shape->GetShapeType()->GetBottom(&corner);
		else
			shape->GetShapeType()->GetTop(&corner);
	}
}


//void SizeShapeCenterCmd::DrawOutline(const Point *pt) {
//	int dx, dy, x, y;
//	Point p = ScaleCorrect(pt);
//	if (!constrainX)
//		dx = abs(p.x - center.x);
//	else
//		dx = shape->GetWidth() / 2;
//	if (!constrainY)
//		dy = abs(p.y - center.y);
//	else
//		dy = shape->GetHeight() / 2;
//	newWidth  = max(1, 2 * dx);
//	newHeight = max(1, 2 * dy);
//	x = center.x - dx;
//	y = center.y - dy;
//	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
//	GetGrafport()->SetLineWidth(1);
//	GetGrafport()->SetForegroundColor("black");
//	GetGrafport()->DrawRectangle(x, y, newWidth, newHeight);
//}
//
//void SizeShapeCenterCmd::Execute() {
//	Command::Execute();
//	Executable(newWidth, newHeight);
//	GetMainWindow()->FitDocument();
//}
//
//void SizeShapeCenterCmd::UnExecute() {
//	Command::UnExecute();
//	Executable(oldWidth, oldHeight);	
//}
//
//void SizeShapeCenterCmd::Executable(int w, int h) {
//	shape->UpdateSize(w, h);
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
//}
