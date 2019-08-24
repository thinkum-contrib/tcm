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
#ifndef _PSPROCESS_H
#define _PSPROCESS_H

#include "node.h"
class PSGraph;

/// Process structure diagram process node class.
class PSProcess: public Node {
/*@Doc: {\large {\bf scope:} TPSD} */
public:
	///
	PSProcess(PSGraph *);
	///
	Subject *Clone() {return new PSProcess(*this);}
	///
	int GetClassType() const {return Code::PS_PROCESS;}
	///
	char GetOperator() {return cOp;}
	///
	bool SetOperator(char x);
	///
	bool IsRoot() {return isRoot;}
	///
	void SetRoot(bool set) {isRoot = set;}
	///
	bool IsAction() {return isAction;}
	///
	void SetAction(bool set) {isAction = set;}
	///
	void SetTreeSequence(int i) {treeSequence = i;}
	///
	int GetTreeSequence() {return treeSequence;}
	///
	void SetActionSequence(int i) {actionSequence = i;}
	///
	int GetActionSequence() {return actionSequence;}
	///
	Subject::NameErrType SetName(const string *name);
	///
	void WriteMembers(OutputFile *f); 
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	char cOp;
	///
	bool isRoot;
	///
	bool isAction;
	///
	int treeSequence;
	///
	int actionSequence;
};
#endif
