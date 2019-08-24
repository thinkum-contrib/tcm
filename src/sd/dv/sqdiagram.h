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
#ifndef _SQDIAGRAM_H
#define _SQDIAGRAM_H

#include "erdiagram.h"
class SQViewer;
class SQWindow;
class SQGraph;
class SQChecks;
class SQClassNode;

/// UML sequence diagram class.
class SQDiagram : public ERDiagram {
/*@Doc: {\large {\bf scope:} TSQD} */
public:
	///
	SQDiagram(Config *, SQWindow *, SQViewer *, SQGraph *);
	///
	virtual ~SQDiagram();
	///
	Node *CreateNode();
	///
	Edge *CreateEdge(Subject *n1, Subject *n2);
	///
	NodeShape *CreateNodeShape(Node *node, int x, int y);
	///
	Line *CreateLine(Edge *edge, GShape *fromShape, 
		GShape *toShape, List<Point *> *line);
	///
	void UpdateNodeType(int n);
	///
	void UpdateEdgeType(int n);

	/// check the soft constraints on a SQD.
	void CheckDocument();

protected:
	///
	Thing *CreateThing(int classNr);
	///
	SQChecks *GetSQChecks() {return sqChecks;}
private:
	///
	SQChecks *sqChecks;
};
#endif
