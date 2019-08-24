////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Rik Eshuis (eshuis@cs.utwente.nl).
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
////////////////////////////////////////////////////////////////////////////////
#ifndef _HYPEREDGE_H
#define _HYPEREDGE_H

#include "subject.h"
#include "llist.h"
#include "edge.h"

class Prop;
class ADSVar;



/// Graph hyper edge class, base class of all hyper edges. An edge connects two sets of subjects.
class HyperEdge: public Subject {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	HyperEdge(HyperGraph *g, List<Subject *> *n1, List<Subject *> *n2);
	///
        HyperEdge(HyperGraph *g, Edge *e);
	///
        HyperEdge(HyperGraph *g);
	///
	virtual ~HyperEdge();

        ///
        bool operator==(HyperEdge &he);

	/// hyperedge connects subject1 and subject2.
	List<Subject *> *GetSubject1() const {return subject1;}

	/// when hyperedge is directed then subject1 is 'from' and subject2 'to'.
	List<Subject *> *GetSubject2() const {return subject2;}

	///
	void SetSubject1(List<Subject *> *n) {subject1 = n;}
	///
	void SetSubject2(List<Subject *> *n) {subject2 = n;}

	///
	bool IsDirected() const {return directed;}

	/// is hyperedge part of the graph?
	bool InGraph() const;

	/// yes of course it is
	bool IsHyperEdge() const {return True;}

	/// no of course it is not
	bool IsEdge() const {return False;}


       	/// write attributes to file.
	void WriteMembers(OutputFile *f); 

	///
	Subject *Clone(){return new HyperEdge(*this);}

	///
	void AddSubject1(Subject *s);
	///
	void AddSubject2(Subject *s);
	///
	string GetLabel();
	/// return the event part of the label
	string GetEvent();
	/// return the guard part of the label
	string GetGuard();
	///
	void SetLabel(string);
	///
	bool HasEmptyEvent();
        ///
        bool HasEmptyGuard();

protected:
	///
	void SetDirected(bool b) {directed=b;}
private:
	/// from subject.
	List<Subject *> *subject1; 

	/// to subject.
	List<Subject *> *subject2;

	/// is the edge directed?
	bool directed;
	///
	string label;
};
#endif
