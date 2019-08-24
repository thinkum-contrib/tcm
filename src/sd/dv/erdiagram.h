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
#ifndef _ERDIAGRAM_H
#define _ERDIAGRAM_H

#include "erviewer.h"
#include "diagram.h"
class ERGraph;
class ERChecks;
class ERWindow;

/// entity-relationship diagram class
class ERDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TERD} */
public:
	///
	ERDiagram(Config *, ERWindow *, ERViewer *, ERGraph *);
	///
	virtual ~ERDiagram();
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
	///
	bool SetText(TextShape *t, const string *s);
	///
	void CheckDocument();

	// set name of nr-th constraint of subject. Check constraint syntax. 
	bool SetConstraint(Subject *subj, const string *s, unsigned nr);

	// set name of nr-th role name of subject. Check name syntax. 
	bool SetRoleName(Subject *subj, const string *s, unsigned nr);
protected:
	///
	Thing *CreateThing(int classNr);
	///
	bool CheckIsaLoop(Edge *edge);
	///
	bool CheckEdgeConstraints(Subject *n1, Subject *n2);
private:
	///
	ERChecks *erChecks;
};
#endif
