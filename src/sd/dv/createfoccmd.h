//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _CREATEFOCCMD_H
#define _CREATEFOCCMD_H

#include "command.h"
#include "polypoint.h"
#include "dpoint.h"
class NodeShape;
class GShape;

/// abstract command class for pulling a shape's tail.
class CreateFOCCmd: public Command {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	//Aleister5
 	CreateFOCCmd(GShape *s, int y, int startF, int endF, bool simetricResize);
	///
	CreateFOCCmd(GShape *s, int y, int startF, int endF);
	///
	void TrackMouse(TrackType aPhase, Point *anchorPoint,
		Point *previousPoint, Point *nextPoint);
	///
	const char *GetName() const {return "pull shape FOC";}
	///
	void Execute();
	///
	void UnExecute();
protected:
	///
	NodeShape *shape;
	/// coordinates of the fix point of the figure.
	DPoint fixpoint;
	/// coordinates of the position of the shape.
	PolyPoint centre;
	/// coordinates of the moving corner of the shape.
	PolyPoint corner;
	///
	int startFOC;
	///
	int endFOC;
	///
	int startY;
	///
	int endY;
	///
	int GetPdirection() const {return pdirection;}
	///
	void SetPdirection(int d) {pdirection=d;}
	///
	void CalcEndPoint(const Point *p);
	///
	void DrawFOC(const Point *np);
	///
	void Draw();
	///
	void Undraw() {
		Draw();
	}
private:
	///
	int pdirection;

	//Aleister5
	bool simetricResize;
	//Aleister5
	int simetricEndY;
};
#endif
