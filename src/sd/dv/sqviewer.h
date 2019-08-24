
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
#ifndef _SQVIEWER_H
#define _SQVIEWER_H

#include "erviewer.h"
class SQWindow;

/// class-relationship viewer class.
class SQViewer: public ERViewer {
/*@Doc: {\large {\bf scope:} TSQD} */
public:
	///
	SQViewer(Config *c, SQWindow * w);

	/// Perform the function of the 1st button function of the mouse 
	void Select(int x, int y);		//resetting inConnectMode
	///
	Command *Drag(int x, int y);

	/// create an edge between nodes.
	Command *Connect(int x, int y); 

	/// change actor type of selected object types.
	void UpdateNodeShapeType(int);

	/// update show stereotypes type of selected object types.
	void UpdateShowStereotypes(bool);

	/// update show properties type of selected object types.
	void UpdateShowProperties(bool);


	//GGGGGGG
	void DeleteFOC();


	///
	void DeleteSubjects();

	///
	void Snap(Point *p);

	///
	bool IsInFOCmode() {return inFOCmode;}
	///
	bool IsInFOCblock() {return inFOCblock;}
	///
	bool IsInConnectMode() {return inConnectMode;}
	///
	bool IsInvalidConnect() {return invalidConnect;}

	/// set/reset in FOC mode
	void SetInFOCmode(bool set) {std::cout << "SetInFOCmode:" << inFOCmode << "->" << set << std::endl << std::flush; inFOCmode = set;}
	/// set/reset in FOC block
	void SetInFOCblock(bool set) {std::cout << "SetInFOCblock:" << inFOCblock << "->" << set << std::endl << std::flush; inFOCblock = set;}
	/// set/reset in Connect Mode
	void SetInConnectMode(bool set) {std::cout << "SetInConnectMode:" << inConnectMode << "->" << set << std::endl << std::flush; inConnectMode = set;}
	/// set/reset invalid Connect
	void SetInvalidConnect(bool set) {std::cout << "SetInvalidConnect:" << invalidConnect << "->" << set << std::endl << std::flush; invalidConnect = set;}




	void SetInConnectMessage(bool set) {std::cout << "SetInConnectMessage:" << inConnectMessage << "->" << set << std::endl << std::flush; inConnectMessage = set;}

private:
	/// in Focus Of Control mode
	bool inFOCmode;
	/// in Focus Of Control block
	bool inFOCblock;
	/// in Connecting Lifelines Mode
	bool inConnectMode;
	/// invalid Connect
	bool invalidConnect;
	//Aleister1
	Point lastPosition;
	//Aleister2
	bool selectedFOC;
	//Aleister2
	Point posSelectedFOC;

	bool inConnectMessage;
};
#endif
