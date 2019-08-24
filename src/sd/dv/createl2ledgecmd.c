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
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.
////////////////////////////////////////////////////////////////////////////////
#include "drawwindow.h"
#include "messagedialog.h"
#include "shapeview.h"
#include "edge.h"
#include "line.h"
#include "diagram.h"
#include "diagramviewer.h"
#include "grafport.h"
#include "toolkit.h"
#include "nodeshape.h"
#include "createl2ledgecmd.h"
#include "sqviewer.h"

CreateL2LEdgeCmd::CreateL2LEdgeCmd(GShape *fs):
	Command(fs->GetView()->GetViewer()->GetDiagram(), 
		fs->GetView()->GetViewer()) {
std::cout << " CreateL2LEdgeCmd::CreateL2LEdgeCmd(GShape *fs):" << std::endl << std::flush; 
	view = fs->GetView();
	diagram = fs->GetView()->GetViewer()->GetDiagram();
	edge = 0;
	line = 0;
	fromShape = fs;
	toShape = 0;
	points = new List<Point *>;
	GetViewer()->SetZigZag(True);
	connectEdges = Toolkit::EditorWithInterEdgeConnections(
                        GetMainWindow()->GetTool());
}

void CreateL2LEdgeCmd::EraseLines() {
std::cout << " void CreateL2LEdgeCmd::EraseLines() {" << std::endl << std::flush; 
	Point *pt1, *pt2;
	if (!check(points->first()))
		return;
	pt1 = pt2 = points->cur();
	GetGrafport()->SetLineWidth(1);
        GetGrafport()->SetForegroundColor("black");
	while(points->next()) {
		pt2 = points->cur();
		GetGrafport()->DrawEditLine(pt1->x, pt1->y, pt2->x, pt2->y);
		GetGrafport()->DrawEditPoint(pt2->x, pt2->y);
		pt1 = pt2;
	}
	GetGrafport()->DrawEditPoint(pt2->x, pt2->y);
}


void CreateL2LEdgeCmd::TrackMouse(TrackType aPhase,
	Point *anchorPoint, Point *previousPoint, Point *nextPoint) {
std::cout << " #### CreateL2LEdgeCmd::TrackMouse(" << (int) aPhase << ", " <<
	*anchorPoint << "," <<  *previousPoint << "," <<  *nextPoint << ")" << std::endl << std::flush;
	int x,y;
	GetGrafport()->SetLineWidth(1);
        GetGrafport()->SetForegroundColor("black");
	switch(aPhase) {
		case TRACK_PRESS:
			GetMainWindow()->SetCursor(MouseCursor::PLUS);
			GetGrafport()->DrawEditLine(anchorPoint->x,
				anchorPoint->y, nextPoint->x, nextPoint->y);
			AddPoint(anchorPoint);
			break;
		case TRACK_DRAG:
			GetGrafport()->DrawEditLine(
				anchorPoint->x, anchorPoint->y,
				previousPoint->x, previousPoint->y);
			GetGrafport()->DrawEditLine(anchorPoint->x,
				anchorPoint->y, nextPoint->x, nextPoint->y);
			abortPoint = *nextPoint;
			break;
		case TRACK_UP:
			// erase old line
			GetGrafport()->DrawEditLine(
				anchorPoint->x, anchorPoint->y,
				previousPoint->x, previousPoint->y);
			// draw temporary
			GetGrafport()->DrawEditLine(anchorPoint->x,
				anchorPoint->y, nextPoint->x, nextPoint->y);
			AddPoint(nextPoint);
			// where was the mouse released
			x = int(0.5 + ScaleCorrect(nextPoint->x));
			y = int(0.5 + ScaleCorrect(nextPoint->y));
			if (connectEdges)
				toShape = view->HitShape(x, y);
			else
				toShape = view->HitNodeShape(x, y);
			if (toShape) 
				TrackMouse(TRACK_RELEASE, anchorPoint,
					previousPoint, nextPoint);
			break;
		case TRACK_RELEASE:
std::cout << " TRL 1 " << std::endl << std::flush; 
			GetMainWindow()->SetCursor(MouseCursor::LEFT_PTR);
std::cout << " TRL 2 " << std::endl << std::flush; 
			EraseLines();
std::cout << " TRL 3 " << std::endl << std::flush; 
			GetViewer()->SetZigZag(False);
std::cout << " TRL 4 " << std::endl << std::flush; 
			GetViewer()->ExecuteCommand();
std::cout << " TRL 5 " << std::endl << std::flush; 
			break;
		default:
			error("unknown track type\n");
			break;
	}
}


void CreateL2LEdgeCmd::Execute() {
std::cout << " void CreateL2LEdgeCmd::Execute() {" << std::endl << std::flush; 

	Subject *n1 = fromShape->GetSubject();
	Subject *n2 = toShape->GetSubject();

	if (!check(n1) || !check(n2))
		return;
	if (fromShape == toShape)
		if (points->count() <= 3 && !diagram->IsCurve()) {
			GetMainWindow()->SetStatus(
				"aborted: 2 intermediate points needed");
			(new MessageDialog(GetMainWindow()->GetWidget(),
			MessageDialog::ERROR))->
			  Show("Error", 
			  "An edge from and to the same shape requires\n"
			  " at least two intermediate points.");
			Command::Abort();
			return;
		}
	if (diagram->IsCurve()) {
		if (points->count() != 4) {
			GetMainWindow()->SetStatus(
				"aborted: 2 intermediate points needed");
			(new MessageDialog(GetMainWindow()->GetWidget(),
			MessageDialog::ERROR))->Show("Error", 
			  "A curve requires exactly two intermediate points.");
			Command::Abort();
			return;
		}
	}
	if ((fromShape->IsLine() && ((Line*)fromShape)->IsCurved()) ||
	    (toShape->IsLine() && ((Line*)toShape)->IsCurved())) {
			GetMainWindow()->SetStatus(
				"aborted: cannot connect to a curve");
			(new MessageDialog(GetMainWindow()->GetWidget(),
				MessageDialog::ERROR))->Show("Error", 
			  "It is not possible to connect to a curve");
			Command::Abort();
			return;
	}



std::cout << " CHECK INVALID CONNECT == " 
<< ((SQViewer *)GetViewer())->IsInvalidConnect() << std::endl << std::flush; 

	if (((SQViewer *)GetViewer())->IsInvalidConnect()) {

std::cout << " Aborting invalid connect " << std::endl << std::flush; 

			GetMainWindow()->SetStatus(
				"aborted: cannot connect to objectbox");
			(new MessageDialog(GetMainWindow()->GetWidget(),
				MessageDialog::ERROR))->Show("Error", 
			  "It is not possible to connect to an objectbox");
			Command::Abort();
			return;
	}


	// correct to internal coordinates and make them positive.
	for (points->first(); !points->done(); points->next()) {
		Point *pt = points->cur();
		view->Snap(pt);
		*pt = ScaleCorrect(pt);
		if (pt->x <= 0)
			pt->x = 1;	 
		if (pt->y <= 0)
			pt->y = 1;
	}
	edge  = diagram->CreateEdge(n1, n2);
	if (edge) {
		line = diagram->CreateLine(edge, fromShape, toShape, points);
		if (line) {
			ReExecute();
			GetMainWindow()->FitDocument();
			return;
		}
	}
	GetMainWindow()->SetStatus("aborted: edge could not be created");
	Command::Abort();
}

void CreateL2LEdgeCmd::UnExecute() {
std::cout << " void CreateL2LEdgeCmd::UnExecute() {" << std::endl << std::flush; 
	if (edge && line) {
		view->RemoveShape(line);
		diagram->RemoveSubject(edge);
		Command::UnExecute();
	}
}

void CreateL2LEdgeCmd::ReExecute() {
std::cout << " void CreateL2LEdgeCmd::ReExecute() {" << std::endl << std::flush; 
	if (edge && line) {
		view->DeselectAll();
		view->AddShape(line);
		view->SelectShape(line);
		diagram->AddSubject(edge);
		Command::Execute();
	}
}

void CreateL2LEdgeCmd::Abort() {
std::cout << " void CreateL2LEdgeCmd::Abort() {" << std::endl << std::flush; 
	AddPoint(&abortPoint);
	EraseLines();
	GetViewer()->SetZigZag(False);
	SayAborted();
	Command::Abort();
}

CreateL2LEdgeCmd::~CreateL2LEdgeCmd() {
std::cout << " CreateL2LEdgeCmd::~CreateL2LEdgeCmd() {" << std::endl << std::flush; 
	if (!CmdDone()) {
		if (edge)
			delete edge;
		if (line)
			delete line;
	}
	if (points) {
		points->clear();
		delete points;
	}
}
