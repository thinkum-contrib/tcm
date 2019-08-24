//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#ifndef _EDGE_H
#define _EDGE_H

#include "subject.h"

/// Graph edge class, base class of all edges. An edge connects two subjects.
class Edge: public Subject {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Edge(Graph *g, Subject *n1, Subject *n2);
	
	///
	virtual ~Edge();

	/// edge connects subject1 and subject2.
	Subject *GetSubject1() const {return subject1;}

	/// when edge is directed then subject1 is 'from' and subject2 'to'.
	Subject *GetSubject2() const {return subject2;}

	///
	void SetSubject1(Subject *n) {subject1 = n;}
	///
	void SetSubject2(Subject *n) {subject2 = n;}

	///
	bool IsDirected() const {return directed;}

	/// is edge part of the graph?
	bool InGraph() const;

	/// yes of course it is
	bool IsEdge() const {return True;}

	/// is subject one of the two subjects that edge connects?
	bool PartOf(Subject *subject) const {
		return (subject == subject1) || (subject == subject2);}

	/// set it all
	void SetSubjects(Subject *n1, Subject *n2, bool d = 0) 
		{subject1 = n1; subject2 = n2; directed = d;}

	/// write attributes to file.
	void WriteMembers(OutputFile *f); 

	/// read and check attributes from file.
	bool ReadMembers(InputFile *f, double format);

	/// set and check references to subjects after reading.
	bool SetReferences(AssocList *); 

	/// check whether subject references exist.
	bool CheckReferences();
protected:
	///
	void SetDirected(bool b) {directed=b;}
private:
	/// from subject.
	Subject *subject1; 

	/// to subject.
	Subject *subject2;

	/// is the edge directed?
	bool directed; 

	/// part of SetReference.
	bool SetSubjectReference(AssocList *al, Subject **subject, int which);
};
#endif
