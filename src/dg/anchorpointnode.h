//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, University of Twente
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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
#ifndef _ANCHORPOINTNODE_H
#define _ANCHORPOINTNODE_H

#include "node.h"
#include "anchorpoint.h"

/// A node that has an extra list of anchorpoints.
class AnchorPointNode: public Node {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	AnchorPointNode(Graph *g);
	///
	AnchorPointNode(const AnchorPointNode &a);
	///
	virtual ~AnchorPointNode();
	///
	Subject *Clone() {return new AnchorPointNode(*this);}
	///
	Subject::NameErrType SetName(const string *name);
	///
	enum AnchorErrorType {
		ANCHOR_OK, ANCHOR_SYNTAX_ERROR, ANCHOR_ALREADY_EXISTS};
	///
	virtual AnchorPointNode::AnchorErrorType SetAnchor(
		const AnchorPoint *p, unsigned n, bool update); 
	///
	const AnchorPoint *GetAnchor(unsigned n) 
		{return ((n < anchors->count()) ? (*anchors)[n] : 0);}
	///
	unsigned NrAnchors() {return anchors->count();}
	///
	bool HasAnchor(const AnchorPoint *p);
	///
	void WriteMembers(OutputFile *f);
	///
	bool ReadMembers(InputFile *f, double format);
protected:
	///
	List<AnchorPoint *> *GetAnchors() {return anchors;}
private:
	///
	List<AnchorPoint *> *anchors;
};
#endif
