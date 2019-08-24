//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _DFDIAGRAM_H
#define _DFDIAGRAM_H

#include "diagram.h"
class DFProcess;
class DataProcess;
class DFViewer;
class DFGraph;
class DFWindow;
class DFChecks;
class ToggleListDialog;

/// data flow diagram class.
class DFDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DFDiagram(Config *, DFWindow *, DFViewer *, DFGraph *);
	///
	virtual ~DFDiagram();
	///
	Node *CreateNode();
	///
	Edge *CreateEdge(Subject *s1, Subject *s2);
	///
	NodeShape *CreateNodeShape(Node *node, int x, int y);
	///
	Line *CreateLine(Edge *edge, GShape *fromShape, 
		GShape *toShape, List<Point *> *line);
	///
	void UpdateNodeType(int n);
	///
	void UpdateEdgeType(int n);

	///
	void CheckDocument();

	/// Check and set DF diagram.
	void SetDiagram(const string *diagram);

	///
	void EditMinispec(Subject *s);
	///
	void SetMinispec();
protected:
	///
	void SetEditProcess(DataProcess *e) {editProcess=e;}
	///
	DataProcess *GetEditProcess() {return editProcess;}
	///
	Thing *CreateThing(int classNr);
	///
	virtual bool CheckEdgeConstraints(Subject *s1, Subject *s2);
	///
	bool HasIndexNode(int code);
	///
	bool HasIndexShape(int code);
private:
	///
	TextEditDialog *minispecDialog;
	///
	DataProcess *editProcess;
	///
	DFChecks *dfChecks;
};
#endif
