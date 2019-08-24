////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "dataflow.h"
#include "inputfile.h"
#include "outputfile.h"
#include "dfgraph.h"
#include "error.h"

DataFlow::DataFlow(DFGraph *g, Subject *n1, Subject *n2): DFEdge(g, n1, n2) {
	SetDirected(True);
	contentType = UNSPECIFIED;
	content = "";
}

Subject::NameErrType DataFlow::SetName(const string *s) {
	if (*s != "" && s->letters() == 0)
		return Subject::IMPOSSIBLE_NAME;
	else if (TriggerLabel(s) || E_D_Label(s))
		return Subject::WRONG_NAME;
	else if (*s != *GetName() && *s != "" &&
			GetGraph()->CountEdges(
				GetSubject1(), GetSubject2(), s) > 0)
		return Subject::DOUBLE_EDGE;
	else
		return DFEdge::SetName(s);
}

void DataFlow::ContentType2String(DataFlow::ContentType tp, string *nm) {
	if (tp == UNSPECIFIED)
		*nm = "Unspecified";
	else if (tp == ATOMIC_SUBJECT)
		*nm = "AtomicSubject";
	else if (tp == ATTRIBUTE)
		*nm = "Attribute";
	else if (tp == DATA_TYPE)
		*nm = "DataType";
	else {
		error("%s, line %d: unknown content type\n",
			 __FILE__, __LINE__);
		*nm = "Unspecified";
	}
}

void DataFlow::WriteMembers(OutputFile *ofile) {
	DFEdge::WriteMembers(ofile);
	if (GetComponents()->count() == 0) {
		string nm;
		ContentType2String(contentType, &nm);
		(*ofile) << "\t{ ContentType " << nm << " }\n";
		if (contentType != UNSPECIFIED)
			(*ofile) << "\t{ " << nm << ' ' << '"' << 
					content << '"' << " }\n";
	}
}

bool DataFlow::ReadMembers(InputFile *ifile, double format) {
	if (!DFEdge::ReadMembers(ifile, format))
		return False;
	if (format >= 1.13) {
		if (GetComponents()->count() == 0) {
			string val;
			if (!ifile->ReadAttribute("ContentType", &val))
				return False;
			contentType = String2ContentType(&val);
			if (contentType != UNSPECIFIED) {
				if (!ifile->ReadStringAttribute(&val,&content))
					return False;
			}
		}
	}
	return True;
}

DataFlow::ContentType DataFlow::String2ContentType(const string *nm) {
	if (*nm == "Unspecified")
		return UNSPECIFIED;
	else if (*nm == "AtomicSubject")
		return ATOMIC_SUBJECT;
	else if (*nm == "Attribute")
		return ATTRIBUTE;
	else if (*nm == "DataType")
		return DATA_TYPE;
	else {
		error("%s, line %d: unknown content type\n",
				__FILE__, __LINE__);
		return UNSPECIFIED;
	}
}
