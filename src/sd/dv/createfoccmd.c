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
#include "createfoccmd.h"
#include "lifeline.h"
#include "sqobjectnode.h"


// dir = handle nr + 1
// Aleister5 mod line 36 , bool simetricResize
CreateFOCCmd::CreateFOCCmd(GShape *s, int y, int startF, int endF, bool simetricResize)				: Command(s->GetView()->GetViewer()->GetDiagram(),
			s->GetView()->GetViewer()),
			fixpoint(*s->GetPosition()),
			centre(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0),
			corner(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0)
{
	this->simetricResize = simetricResize;
	std::cout << "<<<  CreateFOCCmd::CreateFOCCmd(*s, " << y << " ["
	<<  startF << "->" << endF << "] )" << std::endl << std::flush;

	if ( ! (shape = dynamic_cast<NodeShape *>(s)) )
		error("Illegal use of size shape command");

	SetPdirection(5);
	std::cout << "-3-> pdirection = " << pdirection << " Gdir = " << GetPdirection()
	<< std::endl << std::flush;
	startFOC = startF;
	endFOC = endF;
	startY = y;
	//endY = endF;
	endY = y;

	if(simetricResize) {
		if(endY == startF) {
			simetricEndY = endF;
		} else {
			simetricEndY = startF;
		}
	}
	std::cout << " startFOC = " << startFOC  << std::endl << std::flush;
	std::cout << " endFOC = " << endFOC  << std::endl << std::flush;
	std::cout << " startY " << startY  << std::endl << std::flush;
	std::cout << " endY = " << endY  << std::endl << std::flush;
	std::cout << "-4-> pdirection = " << pdirection << " Gdir = " << GetPdirection()
	<< std::endl << std::flush;
}

//Begin Aleister5
CreateFOCCmd::CreateFOCCmd(GShape *s, int y, int startF, int endF)
			: Command(s->GetView()->GetViewer()->GetDiagram(),
			s->GetView()->GetViewer()),
			fixpoint(*s->GetPosition()),
			centre(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0),
			corner(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0)
{
	this->simetricResize = false;
	std::cout << "<<<  CreateFOCCmd::CreateFOCCmd(*s, " << y << " ["
	<<  startF << "->" << endF << "] )" << std::endl << std::flush;

	if ( ! (shape = dynamic_cast<NodeShape *>(s)) )
		error("Illegal use of size shape command");

	SetPdirection(5);
	std::cout << "-3-> pdirection = " << pdirection << " Gdir = " << GetPdirection()
	<< std::endl << std::flush;
	startFOC = startF;
	endFOC = endF;
	startY = y;
	//endY = endF;
	endY = y;
	std::cout << " startFOC = " << startFOC  << std::endl << std::flush;
	std::cout << " endFOC = " << endFOC  << std::endl << std::flush;
	std::cout << " startY " << startY  << std::endl << std::flush;
	std::cout << " endY = " << endY  << std::endl << std::flush;
	std::cout << "-4-> pdirection = " << pdirection << " Gdir = " << GetPdirection()
	<< std::endl << std::flush;
}
//End Aleistert5

void CreateFOCCmd::TrackMouse(TrackType aPhase, Point * /* anchorPoint */,
	Point * /* previousPoint */, Point *nextPoint)
{
std::cout << "-M-> pdirection = " << pdirection << " Gdir = " << GetPdirection()
<< std::endl << std::flush;std::cout << "MMMMM CreateFOCCmd::TrackMouse(" <<
aPhase << ", -, -, " << *nextPoint << ") pdirection="<< pdirection << std::endl
<< std::flush; 	LifeLine *l = (LifeLine *) shape;
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
//			Und raw();

			l->DrawOutLineFOC(min(startFOC,endFOC), max(startFOC,endFOC));	//undraw
//Begin Aleister6
			if(!simetricResize) {
				//Wilford ¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿

				//Wilford___antes:
				//l->DrawOutLineFOC(min(startFOC,endY), max(startFOC,endY));

				//Wilford___ahora:
				if(startY==startFOC)
					l->DrawOutLineFOC(min(endFOC,endY), max(endFOC,endY));		//draw
				else
		                	l->DrawOutLineFOC(min(startFOC,endY), max(startFOC,endY));		//draw
				//Wilford ??????????????????????????????????????????
			} else {
				l->DrawOutLineFOC(min(endY, simetricEndY), max(endY, simetricEndY));
			}
//End Aleister6
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
			break;
		default:
			error("unknown track type\n");
			break;
	}
}


void CreateFOCCmd::CalcEndPoint(const Point *p) {


std::cout << " void CreateFOCCmd::CalcEndPoint(" << *p << ") GCt=" <<
		shape->GetSubject()->GetClassType()  << std::endl << std::flush;

	LifeLine *l = (LifeLine *) shape;
//	l->Undraw();
	int yy = l->GetEndPositionY();
std::cout << " WE ARE AT CalcEndPoint[" << *p << "] @end:" << yy << " p->y=" <<
p->y << std::endl << std::flush;//	l->SetEndPositionY(p->y);
//	l->SetPositionHandles();
//	l->Draw();
}


void CreateFOCCmd::Draw() {
std::cout << " *****************!!! void CreateFOCCmd::Draw() " << std::endl <<
std::flush;//	shape->DrawOutLine(shape->GetPosition());
//	LifeLine *l = (LifeLine *) shape;
//	l->DrawOutLine(shape->GetPosition(), np->y);
}



void CreateFOCCmd::DrawFOC(const Point *np) {
	LifeLine *l = (LifeLine *) shape;

	int prevEndY = endY;	//prev end
	endY = np->y;

std::cout << " !____set_____! void CreateFOCCmd::DrawFOC( [" << startFOC << " :" << prevEndY << "-->" <<  endY << "] ) {" << std::endl << std::flush;

	SetPdirection( (endY >= startFOC) ? 5 : 6 );
	GetMainWindow()->SetSizeCursor(pdirection);
//Begin Aleister6
	if(!simetricResize) {
	//Wilford¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿¿
		//Wilford___antes:
		//l->DrawOutLineFOC(min(startFOC,prevEndY), max(startFOC,prevEndY));
		//l->DrawOutLineFOC(min(startFOC,endY), max(startFOC,endY));

		//Wilford___ahora:

		if(startY==startFOC) {
			l->DrawOutLineFOC(min(endFOC,prevEndY), max(endFOC,prevEndY));	//undraw prev endY
			l->DrawOutLineFOC(min(endFOC,endY), max(endFOC,endY));			//draw new endY
		}
        	else {
			l->DrawOutLineFOC(min(startFOC,prevEndY), max(startFOC,prevEndY));	//undraw prev endY
			l->DrawOutLineFOC(min(startFOC,endY), max(startFOC,endY));			//draw new endY
		}
	} else {
		int prevSimetricEndY = simetricEndY;

		if(startY == startFOC) {
			simetricEndY = endFOC - (endY - startFOC);
		} else {
			simetricEndY = startFOC + (endFOC - endY);
		}
		l->DrawOutLineFOC(min(prevEndY, prevSimetricEndY), max(prevEndY, prevSimetricEndY));	//undraw prevendY
		l->DrawOutLineFOC(min(endY, simetricEndY), max(endY, simetricEndY));
	}
	//Wilford?????????????????????????????????????????????????????
//Begin Aleister6//draw new endY
}


void CreateFOCCmd::Execute() {
	LifeLine *l = (LifeLine *) shape;

	if (startY == endY) {		//no action needed
		GetMainWindow()->SetStatus("aborted: no changes");
		Abort();
		return;
	}

//head && tail check
//Aleister mod
	if ( (endY < (l->GetPosition()->y + l->GetHeight()/2)) ||
	     (endY > l->GetEndPositionY()) ) {

		GetMainWindow()->SetStatus("aborted: invalid FOC");
		Abort();
		return;
	} /*Begin Aleister*/else {
		if(simetricResize) {
			if ( (simetricEndY < (l->GetPosition()->y + l->GetHeight()/2)) ||
			     (simetricEndY > l->GetEndPositionY()) ) {

				GetMainWindow()->SetStatus("aborted: invalid FOC");
				Abort();
				return;
			}
		}
	}
	/*End Aleister*/
	// Begin Aleister7
	if(l->IsOverlappingAnotherFOC(startFOC, endFOC, min(startFOC, endY), max(startFOC, endY))) {
		std::cout<<"kokokoko"<<std::endl<<std::flush;
		GetMainWindow()->SetStatus("aborted: overlapping FOC");
		Abort();
		return;
	}

	if(simetricResize) {
		if(l->IsOverlappingAnotherFOC(startFOC, endFOC,
					 min(startFOC, simetricEndY),
					 max(startFOC, simetricEndY))) {
			GetMainWindow()->SetStatus("aborted: overlapping FOC");
			Abort();
			return;
		}
	}
	// End Aleister7
//creating an new FOC block
	if (startFOC == endFOC) { 	//creating an new FOC block
		l->Undraw();
		((SQObjectNode *)shape->GetSubject())->InsertAnchor(min(startFOC, endY), 2);
		((SQObjectNode *)shape->GetSubject())->InsertAnchor(max(startFOC, endY), 3);
		endFOC = max(startFOC, endY);
		startFOC = min(startFOC, endY);
		l->Draw();
		shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
	}//creating an new FOC block

//in existing FOC
	else {  	//resizing an existing FOC block
		//Aleister6 mod if(simetricResize) {}else {}
		if(!simetricResize) {
			if (startY == startFOC) {	//at top of FOC
				if ( endY < startFOC ) {	//moved up
	std::cout << " valid upper move " << std::endl << std::flush;
					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 2);
					startFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//moved up

				if ( (endY > startFOC) &&
					(endY < endFOC) ) {		//moved down
	std::cout << " valid down move " << std::endl << std::flush;
					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 2);
					startFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//moved down

				if ( endY > endFOC ) {		//moved down
	std::cout << " valid down toggle " << std::endl << std::flush;

					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endFOC, 2);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 3);
					startFOC = endFOC;
					endFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//toggled down
			}	//at top of FOC


			if (startY == endFOC) {	//at bottom of FOC
				if (endY > endFOC) {		//moved down
	std::cout << " valid down move " << std::endl << std::flush;
					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 3);
					endFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//moved up

				if ((endY < endFOC) &&
					(endY > startFOC)) {		//moved up within FOC
	std::cout << " valid up move within FOC" << std::endl << std::flush;
					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 3);
					endFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//moved down

				if ( endY < startFOC ) {		//toggled up
	std::cout << " valid up toggle " << std::endl<< std::flush;

					l->Undraw();
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
					((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(endY, 2);
					((SQObjectNode *)shape->GetSubject())->InsertAnchor(startFOC, 3);
					endFOC = startFOC;
					startFOC = endY;
					l->Draw();
					shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
				}		//toggled down
			}	//at bottom of FOC
		} else {
////////////////Begin Aleister6 Begin//////////////////////////////////
			//Situaciones a validar
			int newStartFOC = min(endY, simetricEndY);
			int newEndFOC = max(endY, simetricEndY);

			l->Undraw();

			((SQObjectNode*)shape->GetSubject())->RemoveAnchor(startFOC,2);
			((SQObjectNode*)shape->GetSubject())->RemoveAnchor(endFOC, 3);

			((SQObjectNode *)shape->GetSubject())->InsertAnchor(newStartFOC, 2);
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(newEndFOC, 3);

			startFOC = newStartFOC;
			endFOC = newEndFOC;
			l->Draw();
			shape->GetView()->GetViewer()->ShapePositionUpdate((GShape *)shape);
		}
	} 	//resizing an existing FOC block


//	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);
//	GetMainWindow()->FitDocument();

	Command::Execute();
}


void CreateFOCCmd::UnExecute() {

std::cout << "UX: CreateFOCCmd: FOC=[" << startFOC << "-" << endFOC
<< " y: " << startY << "<--" << endY << std::endl << std::flush;

	LifeLine *l = (LifeLine *) shape;
	l->Undraw();


//removing a new FOC block
	if ( ((startFOC == startY) && (endFOC == endY)) ||
		 ((startFOC == endY) && (endFOC == startY)) ) {	//removing a FOC block
std::cout << "ux: removing a new FOC block" << std::endl << std::flush; 
		((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
		((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);

		if (startY < endY) {
std::cout << " ux: ### (startY < endY) : endFOC = startFOC; reset " << std::endl
<< std::flush; 			endFOC = startFOC;		//reset
		} else {
std::cout << " ux: ### (startY >= endY) : startFOC = endFOC; reset " <<
std::endl << std::flush; 			startFOC = endFOC;
		}
	}	//removing a FOC block

	else if ( endY == startFOC ) {	// resize at startFOC _or_ toggle
std::cout << "ux: (endY == startFOC) : resize at startFOC or toggle" << 
std::endl << std::flush;
		if ( startY < endFOC ) {
std::cout << "ux: 		( startY < endFOC ) : @startFOC" << std::endl << std::flush;
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(startY, 2);
			startFOC = startY;
		}
		else  {	//toggle
std::cout << "ux: else 	(startY >= endFOC) : toggle" << std::endl << std::flush;
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
		//always remaining FOC
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(endFOC, 2);
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(startY, 3);
			startFOC = endFOC;
			endFOC = startY;
		}	//toggle

	}	// resize at startFOC 

	else if ( endY == endFOC ) {	// resize at endFOC _or_ toggle
std::cout << "ux:  else if ( endY == endFOC ) : resize at endFOC or toggle" << 
std::endl << std::flush;		if ( startY > startFOC ) {
std::cout << "ux:  ( startY > startFOC ) {: @endFOC" << std::endl << std::flush;
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(startY, 3);
			endFOC = startY;
		}
		else  {	//toggle
std::cout << "ux:  else ( startY <= startFOC ) : toggle" << std::endl <<
std::flush; 			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);
		//always remaining FOC
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(startY, 2);
			((SQObjectNode *)shape->GetSubject())->InsertAnchor(startFOC, 3);
			endFOC = startFOC;	
			startFOC = startY;
		}	//toggle
	}	// resize at endFOC 

	l->Draw();

//	shape->UpdateSize(int(0.5 + oldWidth), int(0.5 + oldHeight));
	shape->GetView()->GetViewer()->ShapePositionUpdate(shape);	

std::cout << "==> UX AFTER: CreateFOCCmd: FOC=[" << startFOC << "-" << endFOC 
<< " y: " << startY << "<--" << endY << std::endl << std::flush;

	Command::UnExecute();
}
