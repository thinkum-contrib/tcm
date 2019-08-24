//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2002, Universiteit Twente, Enschede, Netherlands.
// Author: Frank Dehne (frank@cs.vu.nl), David N. Jansen (dnjansen@cs.utwente.nl)
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
#ifndef _STDIAGRAM_H
#define _STDIAGRAM_H

#include "diagram.h"
class STGraph;
class STViewer;
class STWindow;
class STChecks;
class Transition;
class InitialState;
#ifdef MODELCHECK
class ModelCheckDialog;
#endif

/// state transition diagram class
class STDiagram: public Diagram {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	STDiagram(Config *, STWindow *, STViewer *, STGraph *);
	///
	virtual ~STDiagram();
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
#ifdef MODELCHECK
	///
	/* virtual */ void ModelCheckProperty();
#endif

	///
	bool SetEvent(Transition *t, const string *s);
	///
	bool SetAction(Subject *t, const string *s, unsigned nr);

	///
	bool SetText(TextShape *t, const string *s);
protected:
	///
	Thing *CreateThing(int classNr);
	///
	bool CheckEdgeConstraints(Subject *s1, Subject *s2);
	///
	InitialState *FindInitialState(Subject *s);
private:
#ifdef MODELCHECK
	///
	void DoModelCheckDocument(const string *internal,
		const string *formula, const string *clock);
	/// callback for model check document dialog
	static void ModelCheckDocumentOKCB(Widget, XtPointer,
							XtPointer);
	/// saves the current diagram in the model checker formal to *path.
	void SaveForModelChecker(const string *path, const string *internal,
		const string *clock, const string *formula);
	/// calls the model checker for a diagram saved in *path.
	bool ExecuteModelChecker(const string *path, const string *formula);

	/// used for model checking
	ModelCheckDialog *promptDialog;
#endif
	///
	STChecks *stChecks;
	/// width and hight of boxes.
	static const int BOX_WIDTH;
	///
	static const int BOX_HEIGHT;
};
#endif
