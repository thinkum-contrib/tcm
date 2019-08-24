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
#ifndef _SNDIAGRAM_H
#define _SNDIAGRAM_H

#include "diagram.h"
class SNViewer;
class SNGraph;
class SNWindow;
class SNChecks;

/// system network diagram class.
class SNDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TSND} */
public:
	///
	SNDiagram(Config *, SNWindow *, SNViewer *, SNGraph *);
	///
	virtual ~SNDiagram();
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
	void CheckDocument();
	///
	bool SetConstraint(Subject *subject, const string *s, unsigned nr);
	///
	bool SetText(TextShape *t, const string *s);
protected:
	///
	Thing *CreateThing(int classNr);
	///
	bool CheckEdgeConstraints(Subject *s1, Subject *s2);
	///
	unsigned CheckConnectionCoherence(int type, string &chkbuf);
private:
	///
	SNChecks *snChecks;
	///
	static const int DIAMOND_WIDTH;
	///
	static const int DIAMOND_HEIGHT;
	///
	static const int CIRCLE_WIDTH;
};
#endif
