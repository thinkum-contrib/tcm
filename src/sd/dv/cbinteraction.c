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
#include "lstring.h"
#include "inputfile.h"
#include "outputfile.h"
#include "cbinteraction.h"
#include "cbgraph.h"
#include "cbdmessage.h"
#include "gshape.h"
#include "shapeview.h"
#include "cbviewer.h"
#include "diagramviewer.h"
#include "subject.h"


CBInteraction::CBInteraction(CBGraph *g, Subject *n1, Subject *n2): 
		BinaryRelationship(g, n1, n2) {
	messages = new List<CBDMessage *>;

	//add an initial message
	string *dummy_msg = new string("edit this >");
	SetMessage(dummy_msg, 0 , False);
}

CBInteraction::~CBInteraction() {
	messages->clear();
	delete messages;
}


bool CBInteraction::SetConstraint(string *cons, const string *nm) {
	// empty constraint is allowed
	string t = *nm;
	if (*nm == "" || True) {	//HZ_TMP 2B solved with bison...
		*cons = *nm;
		return True;
	}
	else
		return False;
}


Subject::NameErrType CBInteraction::SetMessage(const CBDMessage *m, unsigned n, bool update) {
	if (*m->GetString() != "" && m->GetString()->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double messages.
	if (HasMessage(m)) {
		if (n >= messages->count() || 
			*(*messages)[n]->GetString() != *m->GetString() || !update)
			return Subject::HAS_ACTION;
	}


	if (!update) 	// add new msg
		messages->add((CBDMessage *)m);
	else {	//update
		CBDMessage *dummy = (*messages)[n];
		dummy->SetString(m->GetString());
	} // update

	return Subject::OK;
}



Subject::NameErrType CBInteraction::SetMessage(string *s, unsigned n, bool update) {
	string txt = *s;
	CBDMessage::DirectionType msgDir = CBDMessage::TOSHAPE;	//init

	if (*s != "") {
		if (txt.endsWith(">") || txt.endsWith("v")) {
			msgDir = CBDMessage::TOSHAPE;
			txt.remove();		//last char
		}
		if (txt.endsWith("<") || txt.endsWith("^")) {
			msgDir = CBDMessage::FROMSHAPE;
			txt.remove();		//last char
		}
	}

	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double messages.

	if (!update) {		// add ??
		if (*s != "") {	// add valid new msg
			CBDMessage *msg = new CBDMessage(&txt,msgDir, CBDMessage::FLATFLOW);
			messages->add(msg);
		} 
	} else {	//update
		if (*s != "") {
			CBDMessage *dummy = (*messages)[n];

			if ((dummy->GetDirection() != msgDir) &&
				(msgDir != CBDMessage::NONE)) {
				dummy->SetDirection(msgDir);
			}
			dummy->SetString(&txt);
		} else
			messages->removei(n);
	} // update
	*s = txt;	// return stripped(?) string
	return Subject::OK;
}



Subject::NameErrType CBInteraction::SetMessage(string *s, unsigned n, bool update, bool toggle) {
	string txt = *s;
	CBDMessage::DirectionType msgDir = CBDMessage::TOSHAPE;	//init

	if (update && n>0) 	{	//existing msg : reset init
			msgDir = (*messages)[n]->GetDirection();
	}	//existing msg : reset init

	if (*s != "") {
		if (txt.endsWith(">") || txt.endsWith("v")) {
			msgDir = CBDMessage::TOSHAPE;
			txt.remove();		//last char
		}
		if (txt.endsWith("<") || txt.endsWith("^")) {
			msgDir = CBDMessage::FROMSHAPE;
			txt.remove();		//last char
		}
	}

	if (*s != "") {
		if (txt.endsWith(">") || txt.endsWith("v")) {
			msgDir = (!toggle ? CBDMessage::TOSHAPE : CBDMessage::FROMSHAPE);
			txt.remove();		//last char
		}
		if (txt.endsWith("<") || txt.endsWith("^")) {
			msgDir = (!toggle ? CBDMessage::FROMSHAPE : CBDMessage::TOSHAPE);
			txt.remove();		//last char
		}
	}

	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	// Check for double messages.

	if (!update) {		// add ??
		if (*s != "") {	// add valid new msg
			CBDMessage *msg = new CBDMessage(&txt, msgDir, CBDMessage::FLATFLOW);
			messages->add(msg);
		} 
	} else {	//update
		if (*s != "") {
			CBDMessage *dummy = (*messages)[n];
			if ((dummy->GetDirection() != msgDir) &&
				(msgDir != CBDMessage::NONE)) {
				dummy->SetDirection(msgDir);
			}
			dummy->SetString(&txt);
		} else
			messages->removei(n);
	} // update

	*s = txt;	// return stripped(?) string
	return Subject::OK;
}


const CBDMessage *CBInteraction::GetMessage(unsigned n) {
	if (n < messages->count()) {
		return (*messages)[n];
	}
	return 0;
}


bool CBInteraction::HasMessage(const CBDMessage *m) {
	for (messages->first(); !messages->done(); messages->next()) {
		CBDMessage *at = messages->cur();
		if (*at->GetString() == *m->GetString())
			return True;
	}
	return False;
}


void CBInteraction::WriteMembers(OutputFile *ofile) {
	BinaryRelationship::WriteMembers(ofile);

	unsigned num = messages->count();
	string x;
	(*ofile) << "\t{ Messages " << num << " }\n";

	for (unsigned i=0; i<num; i++) {
		(*ofile) << "\t{ Message " << '"' 
			<< *(*messages)[i]->GetString() << '"' << " }\n";
		CBDMessage::DirectionType2String((*messages)[i]->GetDirection(), &x);
		(*ofile) << "\t{ Direction " << x << " }\n";
		CBDMessage::ControlFlowType2String((*messages)[i]->GetFlow(), &x);
		(*ofile) << "\t{ Flow " << x << " }\n";
	}
}

bool CBInteraction::ReadMembers(InputFile *ifile, double format) {
	if (!BinaryRelationship::ReadMembers(ifile, format))
		return False;
	string val;
	if (!ifile->ReadAttribute("Messages", &val))
		return False;
	unsigned numItems = val.toint();

	string *a = new string;
	CBDMessage::DirectionType direction;
	CBDMessage::ControlFlowType flow;

	// Read messages data
	for (int i=0; i<(int) numItems; i++) {
		if (!ifile->ReadStringAttribute("Message", a)) {
			delete a;
			return False;
		}
		if (!ifile->ReadAttribute("Direction", &val))
			return False;
		direction = CBDMessage::String2DirectionType(&val);
		if (!ifile->ReadAttribute("Flow", &val))
			return False;
		flow = CBDMessage::String2ControlFlowType(&val);
		if (i == 0) 		//overrule dummy "edit this" message
			messages->clear();
		messages->add(new CBDMessage(a, direction, flow));
	}
	return True;
}
