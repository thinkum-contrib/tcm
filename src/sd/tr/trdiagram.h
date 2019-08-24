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
#ifndef _TRDIAGRAM_H
#define _TRDIAGRAM_H

#include "diagram.h"
class DiagramChecks;
class TRGraph;
class TRViewer;
class TRWindow;
class TextNode;
class TextRoot;

/// generic tree diagram class.
class TRDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TGTT} */
public:
	///
	TRDiagram(Config *, TRWindow *, TRViewer *, TRGraph *);
	///
	virtual ~TRDiagram();
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
	void DrawTreeLayout();
	///
	void UndrawTreeLayout();
	///
	void RemoveAll();
	///
	void Append();
protected:
	///
	bool FindRoot(Subject *subj);
	///
	bool CheckEdgeConstraints(Subject *n1, Subject *n2);
	///
	void RecalculateTree();
	///
	Thing *CreateThing(int classNr);
	///
	DiagramChecks *GetTreeChecks() {return trChecks;}
	///
	void CheckDocument();
	///
	void DoLoad(const string *file);

	/// force the viewer to draw in right mode.
	void PlaceShapes();
	///
	void CalcParents(TextNode *parent, TextNode *node);
	///
	void GetChildren(TextNode *node, List<Subject *> *children);
	///
	void DumpChildren(TextNode *node, unsigned level);
	///
	void DrawTreeLayout(TextNode *parent);
private:
	///
	DiagramChecks *trChecks;
};
#endif
