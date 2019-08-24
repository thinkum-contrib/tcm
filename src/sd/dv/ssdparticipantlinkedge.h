//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl)
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
#ifndef _SSD_PARTICIPANTLINKEDGE_H
#define _SSD_PARTICIPANTLINKEDGE_H

#include "c1edge.h"
class SSDGraph;

/// SSD participant edge class connecting N-ary relationship nodes.
class SSDParticipantLinkEdge: public C1Edge {
/*@Doc: {\large {\bf scope:} TSSD} */
public:
	///
	SSDParticipantLinkEdge(SSDGraph *g, Subject *n1, Subject *n2);
	///
	SSDParticipantLinkEdge(const SSDParticipantLinkEdge &bin);
	///
	int GetClassType() const {return Code::SSD_PARTICIPANT_LINK_EDGE;}
	///
	Subject *Clone() { return new SSDParticipantLinkEdge(*this);}
	///
        Subject::NameErrType SetName(const string *s) {
                return *s == "" ? Subject::OK : Subject::WRONG_NAME;}
	///
	bool SetConstraint(const string *s);
	///
	bool SetRoleName(const string *s);
	///
	const string *GetRoleName() const {return &roleName;}
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
private:
	///
	string roleName;
};
#endif
