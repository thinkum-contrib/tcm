////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "sizeshapebordercmd.h"
#include "nodeshape.h"

SizeShapeBorderCmd::SizeShapeBorderCmd(GShape *s, int dir)
	:SizeShapeCmd(s, dir)
{
	if ( ! constrainX ) {
		if ( 1 == dir || 4 == dir || 7 == dir ) {
			shape->GetShapeType()->GetRight(&centre);
			shape->GetShapeType()->GetLeft(&corner);
			fixpoint.x = shape->GetRightMost();
		} else {
			shape->GetShapeType()->GetLeft(&centre);
			shape->GetShapeType()->GetRight(&corner);
			fixpoint.x = shape->GetLeftMost();
		}
		// centre.x = -centre.x;
		centre.SetXUnscaled   (-centre.GetXUnscaled()   );
		centre.SetXHorizScaled(-centre.GetXHorizScaled());
		centre.SetXVertScaled (-centre.GetXVertScaled() );
		centre.SetXNameScaled (-centre.GetXNameScaled() );
		// corner.x += centre.x;
		corner.SetXUnscaled   (corner.GetXUnscaled()    +
			centre.GetXUnscaled()   );
		corner.SetXHorizScaled(corner.GetXHorizScaled() +
			centre.GetXHorizScaled());
		corner.SetXVertScaled (corner.GetXVertScaled()  +
			centre.GetXVertScaled() );
		corner.SetXNameScaled (corner.GetXNameScaled()  +
			centre.GetXNameScaled() );
	}
	if ( ! constrainY ) {
		if ( 3 == dir || 4 == dir || 5 == dir ) {
			shape->GetShapeType()->GetTop(&centre);
			shape->GetShapeType()->GetBottom(&corner);
			fixpoint.y = shape->GetTopMost();
		} else {
			shape->GetShapeType()->GetBottom(&centre);
			shape->GetShapeType()->GetTop(&corner);
			fixpoint.y = shape->GetBottomMost();
		}
		// centre.y = -centre.y;
		centre.SetYUnscaled   (-centre.GetYUnscaled()   );
		centre.SetYHorizScaled(-centre.GetYHorizScaled());
		centre.SetYVertScaled (-centre.GetYVertScaled() );
		centre.SetYNameScaled (-centre.GetYNameScaled() );
		// corner.y += centre.y;
		corner.SetYUnscaled   (corner.GetYUnscaled()    +
			centre.GetYUnscaled()   );
		corner.SetYHorizScaled(corner.GetYHorizScaled() +
			centre.GetYHorizScaled());
		corner.SetYVertScaled (corner.GetYVertScaled()  +
			centre.GetYVertScaled() );
		corner.SetYNameScaled (corner.GetYNameScaled()  +
			centre.GetYNameScaled() );
	}
}


//void SizeShapeBorderCmd::DrawOutline(const Point *pt) {
//	Point p = ScaleCorrect(pt);
//	if (!constrainX) {
//		if (direction==1||direction==4||direction==7) {
//		// left side moved.
//			p.x = min(p.x, newTopLeft.x+newWidth-Shape::MIN_WIDTH);
//			newWidth += newTopLeft.x-p.x;
//			newTopLeft.x = p.x;
//		}
//		else {
//		// right side moved.
//			p.x = max(p.x, newTopLeft.x+Shape::MIN_WIDTH);
//			newWidth = p.x - newTopLeft.x;
//		}
//	}
//	if (!constrainY) {
//		if (direction==1||direction==2||direction==6) {
//			// top side moved.
//			p.y = min(p.y,newTopLeft.y+newHeight-Shape::MIN_HEIGHT);
//			newHeight += newTopLeft.y-p.y;
//			newTopLeft.y = p.y;
//		}
//		else {
//			// bottom side moved.
//			p.y = max(p.y, newTopLeft.y+Shape::MIN_HEIGHT);
//			newHeight = p.y - newTopLeft.y;
//		}
//	}
//	newWidth = max(1, newWidth);
//	newHeight = max(1, newHeight);
//	GetGrafport()->SetLineStyle(LineStyle::DOTTED);
//	GetGrafport()->SetLineWidth(1);
//	GetGrafport()->SetForegroundColor("black");
//	GetGrafport()->DrawRectangle(newTopLeft.x, newTopLeft.y, 
//				     newWidth, newHeight);
//}
//
//void SizeShapeBorderCmd::Execute() {
//	Command::Execute();
//	Point pt;
//	pt.x = newTopLeft.x + newWidth/2;
//	pt.y = newTopLeft.y + newHeight/2;
//	shape->UpdatePosition(&pt);
//	shape->UpdateSize(newWidth, newHeight);
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
//	GetMainWindow()->FitDocument();
//}
//
//void SizeShapeBorderCmd::UnExecute() {
//	Command::UnExecute();
//	Point pt;
//	shape->UpdateSize(oldWidth, oldHeight);
//	pt.x = oldTopLeft.x + oldWidth/2;
//	pt.y = oldTopLeft.y + oldHeight/2;
//	shape->UpdatePosition(&pt);
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
//}
