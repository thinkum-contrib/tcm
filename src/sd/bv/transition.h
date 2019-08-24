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
#ifndef _TRANSITION_H
#define _TRANSITION_H

#include "edge.h"
class STGraph;

/// transition (STD) edge class.
class Transition: public Edge {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	Transition(STGraph *g, Subject *s1, Subject *s2);
	///
	Transition(const Transition &t);
	///
	virtual ~Transition();
	///
	int GetClassType() const {return Code::TRANSITION;}
	///
	Subject *Clone() {return new Transition(*this);}
	/// return WRONG\_NAME
	Subject::NameErrType SetName(const string *name); 
	///
	Subject::NameErrType SetAction(
		const string *a, unsigned n, bool update);
	///
	const string *GetAction(unsigned n);
	///
	bool HasAction(const string *s);
	///
	unsigned NrActions() const {return actions->count();}
	///
	Subject::NameErrType SetEvent(const string *c);
	///
	const string *GetEvent() const {return &event;}
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	string event;
	///
	List<string *> *actions;
};
#endif
