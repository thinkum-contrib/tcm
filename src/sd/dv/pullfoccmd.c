////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "pullfoccmd.h"
#include "lifeline.h"
#include "sqobjectnode.h"


// dir = handle nr + 1

PullFOCCmd::PullFOCCmd(GShape *s, int startY)
	:Command(s->GetView()->GetViewer()->GetDiagram(), 
		s->GetView()->GetViewer()),
	fixpoint(*s->GetPosition()),
	centre(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0),
	corner(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0)
{
std::cout << "<<<  PullFOCCmd::PullFOCCmd(*s, " <<  startY << ")" << std::endl << std::flush; 

	if ( ! (shape = dynamic_cast<NodeShape *>(s)) )
		error("Illegal use of size shape command");

	SetPdirection(5);
std::cout << "-3-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
	
	LifeLine *l = (LifeLine *) shape;
	startFOC = startY;
	newEndFOC = oldEndFOC = startY + 10;
	std::cout << " startFOC = " << startFOC  << std::endl << std::flush; 
	std::cout << " newEndFOC = oldEndFOC = " << newEndFOC  << std::endl << std::flush; 
std::cout << "-4-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
}


void PullFOCCmd::TrackMouse(TrackType aPhase, Point * /* anchorPoint */,
	Point * /* previousPoint */, Point *nextPoint)
{
std::cout << "-M-> pdirection = " << pdirection << " Gdir = " << GetPdirection() << std::endl << std::flush; 
std::cout << "MMMMM PullFOCCmd::TrackMouse(" << aPhase << ", -, -, " << *nextPoint << ") pdirection=" 
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
			DrawFOC(nextPoint);
//			Draw();
			break;
		case TRACK_RELEASE:
//			Undraw();
			l->DrawOutLineFOC(startFOC, oldEndFOC);		//undraw
			l->DrawOutLineFOC(startFOC, newEndFOC);		//draw

			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}


void PullFOCCmd::CalcEndPoint(const Point *p) {


std::cout << " void PullFOCCmd::CalcEndPoint(" << *p << ") GCt=" <<
		shape->GetSubject()->GetClassType()  << std::endl << std::flush; 

	LifeLine *l = (LifeLine *) shape;
//	l->Undraw();
	int yy = l->GetEndPositionY();
std::cout << " WE ARE AT CalcEndPoint[" << *p << "] @end:" << yy << " p->y=" << p->y << std::endl << std::flush; 
//	l->SetEndPositionY(p->y);
//	l->SetPositionHandles();
//	l->Draw();
}


void PullFOCCmd::Draw() {
std::cout << " *****************!!! void PullFOCCmd::Draw() " << std::endl << std::flush; 
//	shape->DrawOutLine(shape->GetPosition());
	LifeLine *l = (LifeLine *) shape;
//	l->DrawOutLine(shape->GetPosition(), np->y);
}



void PullFOCCmd::DrawFOC(const Point *np) {
	LifeLine *l = (LifeLine *) shape;
std::cout << " !____set_____! void PullFOCCmd::DrawFOC( [" << l->GetEndPositionY() << "-->" <<  np->y << "] ) {" << std::endl << std::flush; 
//	l->DrawOutLine(shape->GetPosition(), l->GetEndPositionY());
	l->DrawOutLineFOC(startFOC, newEndFOC);		//prev endPosY
	newEndFOC = np->y;
	l->DrawOutLineFOC(startFOC, np->y);
}


void PullFOCCmd::Execute() {
	Command::Execute();

	LifeLine *l = (LifeLine *) shape;
	int yy = l->GetEndPositionY();
std::cout << " X: WE ARE AT LifeLine End? @end:" << yy << std::endl << std::flush; 

	l->Undraw();
std::cout << " newEndFOC : " << newEndFOC << " <-- " << oldEndFOC << std::endl << std::flush; 
//F	l->SetEndPositionY(newEndPositionY);
//F	l->SetPositionHandles();


	if (newEndFOC != startFOC) {
		((SQObjectNode *)shape->GetSubject())->InsertAnchor(min(startFOC, newEndFOC), 2);
		((SQObjectNode *)shape->GetSubject())->InsertAnchor(max(startFOC, newEndFOC), 3);
	}

	l->Draw();

//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);
//	GetMainWindow()->FitDocument();
}


void PullFOCCmd::UnExecute() {
	Command::UnExecute();

	LifeLine *l = (LifeLine *) shape;
	int yy = l->GetEndPositionY();
std::cout << "UX: PullFOCcmd :" << newEndFOC << "<--" << oldEndFOC << std::endl << std::flush; 
	l->Undraw();
//E	l->SetEndPositionY(oldEndFOC);
//E	l->SetPositionHandles();
	l->Draw();


//	shape->UpdateSize(int(0.5 + oldWidth), int(0.5 + oldHeight));
//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	
}
