//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente.
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#ifndef _CBINTERACTION_H
#define _CBINTERACTION_H

#include "binaryrelationship.h"
#include "textshape.h"
class CBGraph;
class CBDMessage;

/// binary object link edge class in a CBD.
class CBInteraction: public BinaryRelationship {
/*@Doc: {\large {\bf scope:} TCBD} */
public:
	///
	CBInteraction(CBGraph *g, Subject *n1, Subject *n2);
	///
	virtual ~CBInteraction();
	///
	bool HasMessage(const CBDMessage *m);
	/// the number of messages.
	unsigned NrOfMessages() const {return messages->count();}

	///
	Subject::NameErrType SetMessage( const CBDMessage *m,
									unsigned n, bool update);
	///
	Subject::NameErrType SetMessage(string *s, unsigned n, bool update);
	///
	Subject::NameErrType SetMessage(string *s, unsigned n, bool update,
									bool toggle);
	///
	const CBDMessage *GetMessage(unsigned n);

private:
	///
	List<CBDMessage *> *messages;
	///
	bool SetConstraint(string *cons, const string *name);
	///
	void WriteMembers(OutputFile *ofile);
	///
	bool ReadMembers(InputFile *ifile, double format);
};
#endif
