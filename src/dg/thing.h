//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef _THING_H
#define _THING_H

#include "llist.h"
#include "code.h"
class InputFile;
class OutputFile;
class AssocList;

/// superclass of all identifiable things that can be written to file.
class Thing {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	/// 
	Thing(); 	
	///
	Thing(const Thing &s);
	///
	virtual ~Thing();
	///
	unsigned long GetId(); 
	///
	void SetId(unsigned long val) {id = val;}
 
	///
	virtual bool IsSubject() const {return False;}
	///
	virtual bool IsShape() const {return False;}
	///
	virtual bool IsView() const {return False;}

	/// return code of the lowest class.
	virtual int GetClassType() const {return 0;}

	/// write thing to file ofile.
	void Write(OutputFile *ofile);

	/// read from input file. The second param is the read file format. 
	virtual bool ReadMembers(InputFile *, double) {return True;}

	/// update references when thing is read.
	virtual bool SetReferences(AssocList *) {return True;}

	/// possible types in the assoclist.
	enum AssocType {SUBJECT, SHAPE, VIEW};

	/// Check member references.
	virtual bool CheckReferences() { return True; }
private:
	/// internal identifier.
	unsigned long id;

	/// write parts of thing to file.
	virtual void WriteMembers(OutputFile *) {}
};
#endif
