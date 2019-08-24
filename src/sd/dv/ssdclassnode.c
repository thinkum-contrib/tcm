//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
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
#include "ssdclassnode.h"
#include "inputfile.h"
#include "outputfile.h"
#include "lstring.h"
#include "ssdgraph.h"

SSDClassNode::SSDClassNode(SSDGraph *g): StringListNode2(g) {
	SetStringLabel("Attribute");
        SetStringListLabel("Attributes");
        SetStringLabel2("Operation");
        SetStringListLabel2("Operations");
	stereotype = "<< - >>";
	properties = "{ - }";
}

SSDClassNode::SSDClassNode(const SSDClassNode &s): StringListNode2(s) {
	stereotype = s.stereotype;
	properties = s.properties;
}

StringListNode::StringErrorType SSDClassNode::SetString(
                const string *s, unsigned n, bool update) {
        if (*s != "" && s->letters()==0)
                return StringListNode::STRING_SYNTAX_ERROR;
        if (HasString(s)) {
                if (n >= NrStrings() || *GetString(n) != *s || !update)
                        return StringListNode::STRING_ALREADY_EXISTS;
        }
        return StringListNode2::SetString(s, n, update);
}

StringListNode::StringErrorType SSDClassNode::SetString2(
                const string *s, unsigned n, bool update) {
        if (*s != "" && s->letters()==0)
                return StringListNode::STRING_SYNTAX_ERROR;
        if (HasString2(s)) {
                if (n >= NrStrings2() || *GetString2(n) != *s || !update)
                        return StringListNode::STRING_ALREADY_EXISTS;
        }
        return StringListNode2::SetString2(s, n, update);
}

StringListNode::StringErrorType SSDClassNode::SetStereotype(const string *s) {
	if (*s != "" && s->letters()==0)
		return StringListNode::STRING_SYNTAX_ERROR;
	stereotype = *s;
	return StringListNode::STRING_OK;
}

StringListNode::StringErrorType SSDClassNode::SetProperties(const string *s) {
	if (*s != "" && s->letters()==0)
		return StringListNode::STRING_SYNTAX_ERROR;
	properties = *s;
	return StringListNode::STRING_OK;
}

bool SSDClassNode::ReadMembers(InputFile *ifile, double format) {
	string s1, s2;
        if (format < 1.27) {
                s1 = *GetStringListLabel2();
                s2 = *GetStringLabel2();
                SetStringListLabel2("Actions");
                SetStringLabel2("Action");
        }
	if (!StringListNode2::ReadMembers(ifile, format))
		return False;
	stereotype = "<< - >>";
        if ((format >= 1.25) && !ifile->ReadStringAttribute("Stereotype", &stereotype))
		return False;
	properties = "{ - }";
        if ((format >= 1.25) && !ifile->ReadStringAttribute("Properties", &properties))
		return False;
	if (format < 1.27) {
                SetStringListLabel2(&s1);
                SetStringLabel2(&s2);
        }
	return True;
}

void SSDClassNode::WriteMembers(OutputFile *ofile) {
	StringListNode2::WriteMembers(ofile);
	(*ofile) << "\t{ Stereotype " << '"' << stereotype << '"' << " }\n";
	(*ofile) << "\t{ Properties " << '"' << properties << '"' << " }\n";
}
