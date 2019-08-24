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
//// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
//#include "grafport.h"
#include "nodeshape.h"
#include "shapeview.h"
#include "diagram.h"
#include "subject.h"
#include "diagramviewer.h"
//#include "drawwindow.h"
#include "pullshapecmd.h"
#include "lifeline.h"
#include "sqobjectnode.h"


// dir = handle nr + 1

PullShapeCmd::PullShapeCmd(GShape *s, int dir)
	:Command(s->GetView()->GetViewer()->GetDiagram(), 
		s->GetView()->GetViewer()),
	fixpoint(*s->GetPosition()),
	centre(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0),
	corner(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0)
{
std::cout << "<<<  PullShapeCmd::PullShapeCmd(*s, " <<  dir << ")" << std::endl << std::flush; 

	if ( ! (shape = dynamic_cast<NodeShape *>(s)) )
		error("Illegal use of size shape command");
	SetPdirection(dir);

std::cout << "-1-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
std::cout << "-2-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
	SetPdirection(5);
std::cout << "-3-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
	
	LifeLine *l = (LifeLine *) shape;
	newEndPositionY = oldEndPositionY = l->GetEndPositionY();
	std::cout << " newEndPositionY = oldEndPositionY = " << newEndPositionY  << std::endl << std::flush; 
std::cout << "-4-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
}


void PullShapeCmd::TrackMouse(TrackType aPhase, Point * /* anchorPoint */,
	Point * /* previousPoint */, Point *nextPoint)
{
std::cout << "-M-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
std::cout << "MMMMM PullShapeCmd::TrackMouse(" << aPhase << ", -, -, " << *nextPoint << ") pdirection=" 
<< pdirection << std::endl << std::flush; 
	LifeLine *l = (LifeLine *) shape;
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetSizeCursor(pdirection);
			CalcEndPoint(nextPoint);
//			Draw();
			break;
		case TRACK_DRAG:
//			l->UndrawTail(nextPoint);
//			l->Undraw();
			CalcEndPoint(nextPoint);
			DrawTail(nextPoint);
//			Draw();
			break;
		case TRACK_RELEASE:
//			Undraw();
			l->DrawOutLineTail(shape->GetPosition(), l->GetEndPositionY());	//undraw
			l->DrawOutLineTail(shape->GetPosition(), newEndPositionY);		//draw


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
//	l->Undraw();
	int yy = l->GetEndPositionY();
std::cout << " WE ARE AT CalcEndPoint[" << *p << "] @end:" << yy << " p->y=" << p->y << std::endl << std::flush; 
//	l->SetEndPositionY(p->y);
//	l->SetPositionHandles();
//	l->Draw();
}


void PullShapeCmd::Draw() {
std::cout << " *****************!!! void PullShapeCmd::Draw() " << std::endl << std::flush; 
//	shape->DrawOutLine(shape->GetPosition());
	LifeLine *l = (LifeLine *) shape;
//	l->DrawOutLine(shape->GetPosition(), np->y);
}



void PullShapeCmd::DrawTail(const Point *np) {
	LifeLine *l = (LifeLine *) shape;
std::cout << " !____set_____! void PullShapeCmd::DrawTail( [" << l->GetEndPositionY() << "-->" <<  np->y << "] ) {" << std::endl << std::flush; 
//	l->DrawOutLine(shape->GetPosition(), l->GetEndPositionY());
	l->DrawOutLineTail(shape->GetPosition(), newEndPositionY);		//prev endPosY
	newEndPositionY = np->y;
	l->DrawOutLineTail(shape->GetPosition(), np->y);
}


void PullShapeCmd::Execute() {
	LifeLine *l = (LifeLine *) shape;
	int xx = l->GetPosition()->y + l->GetHeight()/2;
	int yy = l->GetEndPositionY();
std::cout << " X: WE ARE AT LifeLine @ [" << xx << "->" << yy << "]" << std::endl << std::flush; 
std::cout << " X: MinAnchor =" << ((SQObjectNode *)l->GetSubject())->GetMinAnchor() << std::endl << std::flush; 
std::cout << " X: MaxAnchor =" << ((SQObjectNode *)l->GetSubject())->GetMaxAnchor() << std::endl << std::flush; 

//in or above starting point 
	if ( newEndPositionY <= (l->GetPosition()->y + l->GetHeight()/2) ) {
		GetMainWindow()->SetStatus("aborted: invalid lifeline");
		Abort();
		return;
	}

//above existing FOC 
	if ( newEndPositionY < ((SQObjectNode *)l->GetSubject())->GetMaxAnchor() ) {
		GetMainWindow()->SetStatus("aborted: above FOC");
		Abort();
		return;
	}

//in existing FOC 
	if ( l->PtInFOCblock(l->GetPosition()->x, newEndPositionY) ) {
		GetMainWindow()->SetStatus("aborted: in FOC");
		Abort();
		return;
	}




	l->Undraw();
std::cout << " newEndPositionY : " << newEndPositionY << " <-- " << l->GetEndPositionY() << std::endl << std::flush; 
	l->SetEndPositionY(newEndPositionY);
	l->SetPositionHandles();
	l->Draw();

//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);
//	GetMainWindow()->FitDocument();

	Command::Execute();
}


void PullShapeCmd::UnExecute() {
	Command::UnExecute();

	LifeLine *l = (LifeLine *) shape;
	int yy = l->GetEndPositionY();
std::cout << "UX: WE ARE AT LifeLine End? @end:" << yy << "<--" << oldEndPositionY << std::endl << std::flush; 
	l->Undraw();
	l->SetEndPositionY(oldEndPositionY);
	l->SetPositionHandles();
	l->Draw();


//	shape->UpdateSize(int(0.5 + oldWidth), int(0.5 + oldHeight));
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
}
