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
#include "nodeshape.h"
#include "shapeview.h"
#include "diagram.h"
#include "diagramviewer.h"
//#include "drawwindow.h"
#include "pullshapecmd.h"

// dir = handle nr + 1

PullShapeCmd::PullShapeCmd(GShape *s, int dir)
	:Command(s->GetView()->GetViewer()->GetDiagram(), 
		s->GetView()->GetViewer()),
	fixpoint(*s->GetPosition()),
	centre(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0),
	corner(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0)
{
	if ( ! (shape = dynamic_cast<NodeShape *>(s)) )
		error("Illegal use of size shape command");
	constrainX = False;
	constrainY = False;
	switch ( dir ) {
	case 5:
	case 6:
		constrainX = True; // only change height
		break;
	case 7:
	case 8:
		constrainY = True; // only change width
		break;
	}
	direction = 5;
}


void PullShapeCmd::TrackMouse(TrackType aPhase, Point * /* anchorPoint */,
	Point * /* previousPoint */, Point *nextPoint)
{
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetSizeCursor(direction);
			CalcEndPoint(nextPoint);
			Draw();
			break;
		case TRACK_DRAG:
			Undraw();
			CalcEndPoint(nextPoint);
			Draw();
			break;
		case TRACK_RELEASE:
			Undraw();
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}


void PullShapeCmd::CalcEndPoint(const Point *p) {


std::cout << " void PullShapeCmd::CalcEndPoint(" << *p << ") GCt=" <<
		shape->GetSubject()->GetClassType()  << std::endl << std::flush; 

	LifeLine *l = (LifeLine *) shape;
	int yy = l->GetEndPositionY();
std::cout << " WE ARE AT CalcEndPoint[" << *p << "] @end:" << yy << std::endl << std::flush; 
	l->SetEndPositionY(*p->y);
	l->SetPositionHandles();
}


void PullShapeCmd::Draw() {
	shape->DrawOutLine(shape->GetPosition());
}


void PullShapeCmd::Execute() {
	Command::Execute();
	Point pt(newEndPosition);
	shape->SetEndPositionY(pt.y);
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);
//	GetMainWindow()->FitDocument();
}


void PullShapeCmd::UnExecute() {
	Command::UnExecute();
	Point pt(oldEndPosition);


	LifeLine *l = (LifeLine *) shape;
	int yy = l->GetEndPositionY();
std::cout << " WE ARE AT LifeLine End? w=" << w << " @end:" << yy << std::endl << std::flush; 
	Undraw();
	l->SetEndPositionY(yy+50);
	l->SetPositionHandles();
	Draw();




	shape->SetEndPositionY(pt.y);
//	shape->UpdateSize(int(0.5 + oldWidth), int(0.5 + oldHeight));
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
}
