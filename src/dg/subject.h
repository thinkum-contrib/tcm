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
#ifndef _SUBJECT_H
#define _SUBJECT_H

#include "thing.h"
#include "lstring.h"
class Graph;
class Node;
class HyperGraph;

/// (abstract) graph element class (is either a node or an edge).
class Subject: public Thing {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Subject(Graph *g);
        ///
        Subject(HyperGraph *g);
	///
	virtual Subject *Clone() = 0;
	/// it is a subject
	bool IsSubject() const {return True;}

	/// is it a node or an edge?
	virtual bool IsEdge() const = 0;

	/// return if subject is part of the graph.
	virtual bool InGraph() const = 0;

	/// The reasons why setting the subject name might fail (error codes)
	enum NameErrType {
		OK, IMPOSSIBLE_NAME, WRONG_NAME, 
		DOUBLE_EDGE, DOUBLE_NODE, HAS_ATTRIBUTE, HAS_ACTION,
		WRONG_NAME_CONNECTION};

	///
	const string *GetName() const {return &name;}

	/// set and check the name
	virtual NameErrType SetName(const string *s) { 
		name = *s; return OK; 
	}

	/// write members of subject to file.
	void WriteMembers(OutputFile *f);

	/// read and parse members of subject from file.
	bool ReadMembers(InputFile *f, double format);

	/// set subject references using the assoclist.
	bool SetReferences(AssocList *);

	/// Check if parent reference exists as graph node element.
	bool CheckReferences();

	/// Set the parent node (parent may be 0).
	void SetParent(Node *p) {parent = p;}
	///
	Node *GetParent() const {return parent;}

	///
	void SetAnnotation(string *s) {annotation = *s;}
	///
	const string *GetAnnotation() const {return &annotation;} 

	///
	Graph *GetGraph() const {return graph;}

        ///
        HyperGraph *GetHyperGraph() const {return hgraph;}

private:
	/// The name of the subject.
	string name;

	/// free text as annotation.
	string annotation;

	/// The graph in which the subject is a node or edge.
	Graph *graph;

        /// The hypergraph in which the subject is a node or edge.
        HyperGraph *hgraph;

	/// Parent node (parent = 0 when subject has no parent).
	Node *parent;
};
#endif
