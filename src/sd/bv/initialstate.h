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
#ifndef _INITIALSTATE_H
#define _INITIALSTATE_H

#include "state.h"

/// initial state (STD) node class.
class InitialState: public State {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	InitialState(STGraph *g);
	///
	InitialState(const InitialState &i);
	///
	virtual ~InitialState();
	///
	int GetClassType() const {return Code::INITIAL_STATE;}
	///
	Subject *Clone() {return new InitialState(*this);}
	///
	Subject::NameErrType SetAction(const string *s, unsigned n, 
		bool update);
	///
	const string *GetAction(unsigned n);
	///
	unsigned NrActions() const {return actions->count();}
	///
	bool HasAction(const string *s);
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	List<string *> *actions;
	///
	string controlProcess;
};
#endif
