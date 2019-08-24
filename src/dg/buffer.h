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
#ifndef _BUFFER_H
#define _BUFFER_H

#include "llist.h"
#include "command.h"
class Subjects;
class Shapes;

/// shape and subject cut-paste buffer class.
class Buffer {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	Buffer();
	///
	~Buffer();

	/// Copy lists of subjects and shapes and hold them in the buffer.
	void Put(Subjects *, Shapes *); 

	/// Copy subjects in the buffer and return them in a list.
	Subjects *GetSubjectsCopy(); 

	/// Copy shapes in the buffer and return them in a list.
	Shapes *GetShapesCopy();

	///
	Subjects *GetSubjects() const {return subjects;}
	///
	Shapes *GetShapes() const {return shapes;}

	/// Returns if buffer is empty.
	bool IsEmpty() const { return subjects == 0;} 

	/// Which command uses this buffer.
	void SetUser(Command *c) {user = c;}
	///
	Command *GetUser() {return user;}
private:
	///
	Subjects *subjects;
	///
	Shapes *shapes;
	///
	Command *user;
};
#endif
