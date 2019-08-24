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
#ifndef _CONNECTIONEND_H
#define _CONNECTIONEND_H

#include "c1edge.h"
class SNGraph;

/// connection end (system network) edge class.
class ConnectionEnd: public C1Edge {
/*@Doc: {\large {\bf scope:} TSND} */
public:
	///
	ConnectionEnd(SNGraph *g, Subject *n1, Subject *n2);
	///
	int GetClassType() const {return Code::CONNECTION_END;}
	///
	Subject *Clone() {return new ConnectionEnd(*this);}
	/// returns WRONG\_NAME.
	Subject::NameErrType SetName(const string *s) {
		return (*s == "") ? Subject::OK : Subject::WRONG_NAME;}
	///
	bool SetConstraint(const string *s);
private:
	///
	bool ParseCardConstraint(const string *s);
};
#endif
