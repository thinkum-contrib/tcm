//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "sqviewer.h"
#include "sqwindow.h"
#include "cbupdateactortypecmd.h"
#include "subject.h"
//X #include "ssdsingleclassbox.h"
//X #include "ucdsingleclassbox.h"
#include "ssddoubleclassbox.h"		// compatibility
#include "ssdtripleclassbox.h"		// compatibility
#include "ssdupdateclassboxpropertycmd.h"

#include "diagram.h"
#include "diagramviewer.h"
#include "apline.h"
#include "lifeline.h"
#include "createfoccmd.h"
#include "pullfoccmd.h"
#include "pullshapecmd.h"
#include "sqobjectnode.h"
#include "shapeview.h"
#include "createedgecmd.h"
#include "createl2ledgecmd.h"
#include "sqanchorlinkedge.h"


SQViewer::SQViewer(Config *c, SQWindow *w): ERViewer(c, w) { }

void SQViewer::Select(int x, int y) {
std::cout << " void SQViewer::Select(" <<  x << ", " <<  y << ") {" << std::endl << std::flush;
	SetInConnectMessage(False);		//init

	SetInvalidConnect(False);		//init
	// Begin Aleister2 Begin

	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));

	GShape *shape;
	// look for nodes shapes.
	if ((shape = GetCurView()->HitNodeShape(x, y))) {
	//xtra check here
		LifeLine *l = (LifeLine *) shape;
		int lStart = 0;
		int lEnd = 0;
//		if ( (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd))
		bool b = (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd));

		if (b) {

			selectedFOC = true;
			posSelectedFOC = Point(x, y);
			inFOCmode = true;
			return;
		} else {
			selectedFOC = false;
			inFOCmode = false;
		}
	}

	// End Aleister2 End
	ERViewer::Select(x, y);
}


Command *SQViewer::Drag(int x, int y) {
std::cout << " Command *SQViewer::Drag(" << x << "," << y << ") {" << std::endl << std::flush;
	SetInConnectMode(False);		//init
	SetInConnectMessage(False);		//init

	SetInvalidConnect(False);		//init
	TextShape *textShape;
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	// do note allow moving messages
std::cout << " A-1 " << std::endl << std::flush;
std::cout << " GNT=" << GetDefaultNodeType() << std::endl << std::flush;
std::cout << " GNsT=" << GetDefaultNodeShapeType() << std::endl << std::flush;

std::cout << " inFOCmode=" << inFOCmode << std::endl << std::flush;
std::cout << " inFOCblock=" << inFOCblock << std::endl << std::flush;
std::cout << " inConnectMode=" << inConnectMode << std::endl << std::flush;
std::cout << " invalidConnect=" << invalidConnect << std::endl << std::flush;


	if ((textShape = GetCurView()->HitTextShape(x, y, False))) {
std::cout << " B-2 " << std::endl << std::flush;
		Subject *subj = textShape->GetParent()->GetSubject();

		if ((*textShape->GetDescription() == "Message") &&
		    ((subj->GetClassType() == Code::CBD_CLASS_LINK_EDGE) ||
			 (subj->GetClassType() == Code::CBD_OBJECT_LINK_EDGE))) {
			SetStatus("aborted: message can not be dragged");
			return 0;
		}
	}


/* dragging @ LifeLine End? */

	GShape *shape;
	int w;
	// look for nodes shapes.
	if ((shape = GetCurView()->HitNodeShape(x, y))) {
lastPosition = *shape->GetPosition();//Aleister
std::cout << "shape->Sj()= " << shape->GetSubject() << std::endl << std::flush;
std::cout << "shape->Sj()->GetId()= " << shape->GetSubject()->GetId() << std::endl << std::flush;
std::cout << "shape->Sj()->GetCt()= " << shape->GetSubject()->GetClassType() << std::endl << std::flush;

		if (shape->IsSelected() &&
			(shape->GetSubject()->GetClassType()  == Code::CBD_OBJECT_NODE) &&
		    (w = shape->HitHandles(x, y)) == 5) {



			LifeLine *l = (LifeLine *) shape;
			int yy = l->GetEndPositionY();
std::cout << " WE ARE AT LifeLine End? w=" << w << " @end:" << yy << std::endl << std::flush;

			return new PullShapeCmd(shape, w);
		}

//xtra check here

		LifeLine *l = (LifeLine *) shape;
		int lStart = 0;
		int lEnd = 0;
//		if ( (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd))
		bool b = (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd));
std::cout << "=Drag=>  l->PtInFOCblock(" << l->GetPosition()->x << ", " << y << ", "
<< lStart << "," << lEnd << ")); --> " << b << std::endl << std::flush;


		if (b) {
std::cout << "*** Drag FOC End (" << b << ") x, y: " << x << ", " << y << std::endl << std::flush;
			//Begin Aleister3
			if(y - lStart <= 7) {
				y = lStart;
				return new CreateFOCCmd(shape, y, lStart, lEnd, true);
			} else {
				if(lEnd - y <= 7) {
					y = lEnd;
					return new CreateFOCCmd(shape, y, lStart, lEnd, true);
				}
			}
			//End Aleister3

		}


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

//???????????????????????????????????????????????????????????????????????????????????????????
std::cout<<"CCCCCCCCCCC"<<std::endl<<std::flush;
int w;
		if(GetCurView()->HitLineHandle(x, y, w))	{

			SetInConnectMessage(True);
			//SetInConnectMode(True);
			lastPosition.Set((l-> GetPosition()->x), y);
					std::cout<<"DDDDDDDDDD"<<std::endl<<std::flush;
			/*List<Point *> *appoints;
			appoints = ((SQObjectNode *)(l->GetSubject()))->GetAnchors();

			for(appoints->first(); !appoints->done(); appoints->next()) {

				Point p = *appoints->cur();
				if(p.y == 4 || p.y == 5) {
					//if(abs(p.x-y)< 5) {
					if(p.x-y< 5 || y-p.x < 5) {
						lastPosition = Point(x, p.x);
						spotLine=p.y;
					}
				}

			}*/



		}


//???????????????????????????????????????????????????????????????????????????????????????????



//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&



	}
	lastPosition.Set(x, y);

std::cout << " GOING 2 	return ERViewer::Drag(" << x << ", " << y << ");" << std::endl << std::flush;
//	SetInConnectMode(True);
	return ERViewer::Drag(x,y);

/* ************ *
	if (!inFOCblock) {
std::cout << " GOING 2 	return ERViewer::Drag(" << x << ", " << y << ");" << std::endl << std::flush;
		return ERViewer::Drag(x,y);
	}
	else {
std::cout << " GOING 2 	Drag FOC (" << x << ", " << y << ");" << std::endl << std::flush;

		LifeLine *l = (LifeLine *) shape;
		int lStart = 0;
		int lEnd = 0;
//		if ( (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd))
		bool b = (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd));
std::cout << "=====>  l->PtInFOCblock(" << l->GetPosition()->x << ", " << y << ", "
<< lStart << "," << lEnd << ")); --> " << b << std::endl << std::flush;
		return new CreateFOCCmd(shape, y, lStart, lEnd);
	}
* ************ */
}




void SQViewer::UpdateNodeShapeType(int actorType) {
	SetStatus("action: Update actor type");
	List<int *> t;
	t.add(new int(Code::UCD_SINGLE_CLASS_BOX));
	t.add(new int(Code::STICKMAN));
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new CBUpdateActorTypeCmd(
				GetCurView(), &t, actorType));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
	t.clear();
}


void SQViewer::UpdateShowStereotypes(bool b) {
	if (b)
		SetStatus("action: show stereotypes");
	else
		SetStatus("action: hide stereotypes");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(),
				SSDUpdateClassBoxPropertyCmd::STEREOTYPE, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void SQViewer::UpdateShowProperties(bool b) {
	if (b)
		SetStatus("action: show properties");
	else
		SetStatus("action: hide properties");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(),
				SSDUpdateClassBoxPropertyCmd::PROPERTIES, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void SQViewer::Snap(Point *p) {
std::cout << " +++++++++++++++  void SQViewer::Snap(" << *p << ") {" << std::endl << std::flush;
	GetGrid()->Snap(p);

std::cout << " ++after Snap+++  --> Snap(" << *p << ") {" << std::endl << std::flush;
std::cout << " ++after Snap+++  --> p->x,y =" << p->x << ", " << p->y  << std::endl << std::flush;

std::cout << " GetCurView()->NrOfShapes() == " << GetCurView()->NrOfShapes() << std::endl << std::flush;
std::cout << " GetCurView()->NrSelected() == " << GetCurView()->NrSelected() << std::endl << std::flush;

	GShape *shape;

	if ((shape = GetCurView()->HitNodeShape(lastPosition.x, lastPosition.y))) {//Aleister

std::cout << "t_Shape->=Sel " << shape->IsSelected() << std::endl << std::flush;
std::cout << "t_Shape->Sj()->GetId()= " << shape->GetSubject()->GetId() << std::endl << std::flush;
std::cout << "t_Shape->Sj()->GetCt()= " << shape->GetSubject()->GetClassType() << std::endl << std::flush;

std::cout << "t_Shape->GetPos()->x = " << shape->GetPosition()->x << std::endl << std::flush;
std::cout << "t_Shape->GetPos()->y = " << shape->GetPosition()->y << std::endl << std::flush;
std::cout << "t_Shape->GetHeight() = " << shape->GetHeight() << std::endl << std::flush;


		if (shape->GetSubject()->GetClassType()  == Code::CBD_OBJECT_NODE) {

			LifeLine *l = (LifeLine *) shape;
			int minPos = l->GetEndPositionY();	//init: at EOL

			if ( ((SQObjectNode *)shape->GetSubject())->NrAnchors() ) {
				minPos = min(minPos, ((SQObjectNode *)shape->GetSubject())->GetMinAnchor());
			}

//????????????????????????????????????????????????????????????????????????????????????????????





			if(inConnectMessage){
//std::cout <<"&&&&&&&&&&&&&&&&&&&&&&&&"<<"t_Shape->GetPos()->x = " <<std::endl << std::flush;
//std::cout<<(char)7<<std::endl<<std::flush;
//std::cout<<(char)7<<std::endl<<std::flush;
//std::cout<<(char)7<<std::endl<<std::flush;
				if( ! (p->y> ( (l-> GetPosition()->y) + shape->GetHeight()/2 )  && p->y <  ( l->GetEndPositionY() )) ) {

					*p=lastPosition;
					return;

				}
				else {



					lastPosition.Set((l-> GetPosition()->x), p->y);
					return;


				}
			}
/*
			} else {*/
				if(!inConnectMode) {
				if ((((GetCurView()->Snap(p->y) + shape->GetHeight()/2) > minPos) ) || (((GetCurView()->Snap(p->y) + shape->GetHeight()/2) > ( l->GetEndPositionY() )-7) )) {


					*p = *shape->GetPosition();
					return;
				} else {
					std::cout << "t_Shape valid pos: SQViewer::Snap Returning: " << *p << std::endl << std::flush;
				}
				}






		}//if (shape->GetSubject()->GetClassType()  == Code::CBD_OBJECT_NODE) {

	}

}
//????????????????????????????????????????????????????????????????????????????????????????????
/*  REEMPLAZADO
std::cout << "t_Shape GetCurView()->Snap(p->y) = " << GetCurView()->Snap(p->y) << std::endl << std::flush;
std::cout << "t_Shape: minPos = " << minPos << std::endl << std::flush;
std::cout << "t_Shape: INVALID_CONNECT = " << invalidConnect << std::endl << std::flush;


			if ( ((GetCurView()->Snap(p->y) + shape->GetHeight()/2) > minPos) &&
				 !inConnectMode ) {
std::cout << "t_Shape INVALID position!!! (!inConnectMode)"
<< (GetCurView()->Snap(p->y) + shape->GetHeight()/2) << " >>> "
<< minPos << std::endl << std::flush;
std::cout << "t_Shape->GetPosition() = " << shape->GetPosition() << std::endl << std::flush;

				//restore oldPosition; thus aborting the drag operation
				*p = *shape->GetPosition();
std::cout << "t_Shape INVALID pos: SQViewer::Snap Returning: " << *p << std::endl << std::flush;
				return;
			} else
std::cout << "t_Shape valid pos: SQViewer::Snap Returning: " << *p << std::endl << std::flush;

		}

	}

} REEMPLAZADO */


Command *SQViewer::Connect(int x, int y) {
	GShape *shape;
	SetInConnectMode(False);		//init
	SetInConnectMessage(False);		//init

	SetInvalidConnect(False);		//init
	x = int(0.5 + ScaleCorrect(x));
	y = int(0.5 + ScaleCorrect(y));
	int w = 0;

std::cout << "C: inFOCmode=" << inFOCmode << std::endl << std::flush;
std::cout << "C: inFOCblock=" << inFOCblock << std::endl << std::flush;
std::cout << "C: inConnectMode=" << inConnectMode << std::endl << std::flush;
std::cout << "C: invalidConnect=" << invalidConnect << std::endl << std::flush;


bool tHitted = False;
bool tSelected = False;
if ((shape = GetCurView()->HitNodeShape(x, y))) {
		tHitted = True;
		tSelected = shape->IsSelected();
		w = shape->HitHandles(x, y);
}


std::cout << " Command *SQViewer::Connect(" <<  x << "," <<  y << ") : HNs="
	<< tHitted  << " isSel=" << tSelected << "  HitH=" << w
	<<  " isSel&&HHs=" << (tSelected && (w >= 0))
	<< "} " << std::endl << std::flush;


	if (tHitted) {
		//Mod Aleister if (inFOCmode) {
			//Begin Aleister6
			LifeLine *l = (LifeLine *) shape;
			int lStart = 0;
			int lEnd = 0;
	//		if ( (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd))
			bool b = (l->PtInFOCblock(l->GetPosition()->x, y, &lStart, &lEnd));

			if (b) {
				if(y - lStart <= 7) {
					y = lStart;
					return new CreateFOCCmd(shape, y, lStart, lEnd);
				} else {
					if(lEnd - y <= 7) {
						y = lEnd;
						return new CreateFOCCmd(shape, y, lStart, lEnd);
					}
				}
			} else {
				if(inFOCmode) {
					std::cout << "SQViewer::Connect(): inFOCmode: CREATE FOC here @ " << y << std::endl << std::flush;
		//JZ		shape->UndrawShape();
		//JZ		shape->DrawShape();

					return new CreateFOCCmd(shape, y, y, y);
				}
			}
			//End Aleister6
		//Mod Aleister} else {	//starting in FOC area?
			//LifeLine *l = (LifeLine *) shape;
			if (l->PtInFOCarea(x, y)) {
std::cout << " Pt In FOC AREA OK " << std::endl << std::flush;
				SetInConnectMode(True);

				return ERViewer::Connect(x, y);
/* *** BYE *
				if (shape->IsSelected() && (w = shape->HitHandles(x, y)) >= 0) {
std::cout << "======= GOING 3:  return new SizeShapeBorderCmd(shape, w);" << std::endl << std::flush;
					return new SizeShapeBorderCmd(shape, w);
				} else {
//std::cout << "======= GOING 3:  return new CreateL2LEdgeCmd(shape);" << std::endl << std::flush;
//HZ					return new CreateL2LEdgeCmd(shape);
std::cout << "======= GOING 3:  return new CreateEdgeCmd(shape);" << std::endl << std::flush;
					return new CreateEdgeCmd(shape);
				}
* *** BYE */

			} else {
std::cout << " Pt In FOC AREA FALSE " << std::endl << std::flush;
				return 0;
			}
		//Mod Aleister]
	}
	else {
std::cout << " Not in NodeShape: IGNORED " << std::endl << std::flush;
	return 0;
	}
}



void SQViewer::DeleteFOC() {
//Begin Aleister2 Begin
	if(selectedFOC) {
		GShape *shape;

		if ((shape = GetCurView()->HitNodeShape(posSelectedFOC.x, posSelectedFOC.y))) {
			LifeLine *l = (LifeLine*)shape;

			int startFOC;
			int endFOC;

			l->PtInFOCblock(posSelectedFOC.x, posSelectedFOC.y,
			       &startFOC, &endFOC);
			l->Undraw();

			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(startFOC, 2);
			((SQObjectNode *)shape->GetSubject())->RemoveAnchor(endFOC, 3);

			l->Draw();

	//	shape->UpdateSize(int(0.5 + oldWidth), int(0.5 + oldHeight));
		shape->GetView()->GetViewer()->ShapePositionUpdate(shape);
		}
		return;
	}
//End Aleister2 End


}
/*

void SQViewer::DeleteSubjects() {
std::cout << " void SQViewer::DeleteSubjects() {" << std::endl << std::flush;

	if (GetCurView()->NrSelected() > 0) {
		int i = 0;

		List<GShape *> *selection = GetCurView()->GetSelection();
		for (selection->first(); !selection->done(); selection->next()) {
		std::cout<<"=========(((((((("<<i++<<")))))========="<<std::flush<<std::endl;
			GShape *shape = selection->cur();

			if (shape->GetClassType()==Code::T4_LINE) {
std::cout << "!!! GOT a T4_LINE: " << shape->GetClassType() << std::endl << std::flush;*/
//				Point from = *(((APLine *)shape)->GetFromShape()->GetPosition());
/*

std::cout << "shape->Sj()->GetId()= " << shape->GetSubject()->GetId() << std::endl << std::flush;
				Subject *subj = shape->GetSubject();
std::cout << "subj->GetId()= " << subj->GetId() << std::endl << std::flush;


				GShape *from = ((APLine *)shape)->GetFromShape();
				GShape *to = ((APLine *)shape)->GetToShape();

std::cout << " Leading from " << from->GetId() << " --> " << to->GetId() << std::endl << std::flush;


				SQAnchorLinkEdge *obj = (SQAnchorLinkEdge *)shape->GetSubject();
*/


				/*SQObjectNode *fromON = (SQObjectNode *) obj->GetSubject1();
				SQObjectNode *toON = (SQObjectNode *) obj->GetSubject2();*/

//				Point ap1 = *obj->GetAnchor1();
//				Point ap2 = *obj->GetAnchor2();

//std::cout << " #ap=" << ((SQObjectNode *)shape->GetSubject())->NrAnchors() << std::endl << std::flush;
//std::cout << " ap1=" << ap1 << "  ap1.x=" << ap1.x << std::endl << std::flush;
//std::cout << " ap2=" << ap2 << "  ap2.x=" << ap2.x << std::endl << std::flush;

				//if ( ((SQObjectNode *)shape->GetSubject())->NrAnchors() ) {



 //((SQObjectNode *)from->GetSubject())->RemoveAnchor(ap1.x, 2);
 //((SQObjectNode *)to->GetSubject())->RemoveAnchor(ap2.x, 3);
/*
 DiagramViewer::DeleteSubjects();
 std::cout<<ap1<<std::endl<<std::flush;
 std::cout<<ap2<<std::endl<<std::flush;
((SQObjectNode *)from->GetSubject())->RemoveAnchor(ap1.x, ap1.y);
 ((SQObjectNode *)to->GetSubject())->RemoveAnchor(ap2.x, ap2.y);
return;

				//}
			}

		}


		DiagramViewer::DeleteSubjects();
		SetStatus("SQVIEWR action: delete Subjects");

	}
	else
		EmptySelectionMessage();

}*/



void SQViewer::DeleteSubjects() {
std::cout << " void SQViewer::DeleteSubjects() {" << std::endl <<
std::flush;

	List<Subject *> *edges;
	edges = new List<Subject *>;

	if (GetCurView()->NrSelected() > 0) {

		List<GShape *> *selection = GetCurView()->GetSelection();

		for (selection->first(); !selection->done(); selection->next()) {

			GShape *shape = selection->cur();

			if
((shape->GetSubject())->GetClassType()==Code::CBD_OBJECT_LINK_EDGE) {
				if (edges->find(shape->GetSubject()) == -1)
					edges->add(shape->GetSubject());
			} else {
				if((shape->GetSubject())->GetClassType() == Code::CBD_OBJECT_NODE)
					GetDiagram()->CompleteSubject(edges, shape->GetSubject());
				
			}

		}

		DiagramViewer::DeleteSubjects();

		for(edges->first(); !edges->done(); edges->next()) {

			Subject *edge = edges->cur();
	
			if (edge->GetClassType()==Code::CBD_OBJECT_LINK_EDGE) {

				SQAnchorLinkEdge *obj = (SQAnchorLinkEdge *)edge;
				SQObjectNode *from = (SQObjectNode *) obj->GetSubject1();
				SQObjectNode *to = (SQObjectNode *) obj->GetSubject2();
				Point ap1 = *obj->GetAnchor1();
				Point ap2 = *obj->GetAnchor2();
				from->RemoveAnchor(ap1.x, ap1.y);
 				to->RemoveAnchor(ap2.x, ap2.y);

			}
		}
	}
	else
		EmptySelectionMessage();
}




