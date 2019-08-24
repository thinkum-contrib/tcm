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
#include "dataprocess.h"
#include "inputfile.h"
#include "outputfile.h"
#include "dfgraph.h"
#include "util.h"

DataProcess::DataProcess(DFGraph *g): DFProcess(g) {
	minispec = "";
	instantaneous = True;
	activationMechanism = UNSPECIFIED;
	timeExpression = "";
	processGroup = False;
	stimulus = "";
}

bool DataProcess::SetReferences(AssocList *al) {
	return DFNode::SetReferences(al);
}

void DataProcess::SetProcessGroup(bool b) {
	processGroup = b;
	if (b) {
		instantaneous = True;
		minispec = "";
		activationMechanism = UNSPECIFIED;
		stimulus = "";
		timeExpression = "";
	}
}

void DataProcess::SetInstantaneous(bool b) {
	if (check(!processGroup))
		instantaneous = b;
	if (!instantaneous) {
		activationMechanism = UNSPECIFIED;
		stimulus = "";
		timeExpression = "";
	}
}

void DataProcess::SetMinispec(const string *s) {
	if (check(!processGroup))
		minispec = *s;
	else
		minispec = "";
}

void DataProcess::SetActivationMechanism(ActivationType a) {
	if (check(!processGroup && instantaneous))
		activationMechanism = a;
	else
		activationMechanism = UNSPECIFIED;
	if (activationMechanism != TIME)
		timeExpression = "";
	if (activationMechanism != STIMULUS)
		stimulus = "";
}

void DataProcess::SetStimulus(const string *s) {
	if (check(activationMechanism == STIMULUS))
		stimulus = *s;
	else
		stimulus = "";
}

void DataProcess::SetTimeExpression(const string *s) {
	if (check(activationMechanism == TIME))
		timeExpression = *s;
	else
		timeExpression = "";
}

void DataProcess::WriteMembers(OutputFile *ofile) {
	DFProcess::WriteMembers(ofile);
	(*ofile) << "\t{ ProcessGroup " << (processGroup?"True":"False") << " }\n";
	if (!processGroup) {
		(*ofile) << "\t{ Persistence " <<
			  (instantaneous?"Instantaneous":"Continuing") << " }\n";
		(*ofile) << "\t{ Minispec " << '"' << minispec << '"' << " }\n";
		if (instantaneous) {
			string nm;
			ActivationType2String(activationMechanism, &nm);
			(*ofile) << "\t{ ActivationMechanism " << nm << " }\n";
			if (activationMechanism == STIMULUS) {
				(*ofile) << "\t{ Stimulus " << '"' <<
					stimulus << '"' << " }\n";
			}
			else if (activationMechanism == TIME) {
				(*ofile) << "\t{ TimeExpression " << '"' << timeExpression 
					 << '"' << " }\n";
			}
		}
	}
}

bool DataProcess::ReadMembers(InputFile *ifile, double format) {
	if (!DFProcess::ReadMembers(ifile, format))
		return False;
	if (format >= 1.13) {
		string val;
		if (!ifile->ReadAttribute("ProcessGroup", &val))
			return False;
		processGroup = (val %= "True");
		if (!processGroup) {
			// it's a data process.
			if (!ifile->ReadAttribute("Persistence", &val))
				return False;
			instantaneous = (val %= "Instantaneous");
			if (!ifile->ReadStringAttribute("Minispec", &minispec))
				return False;
			if (instantaneous) {
				if (!ifile->ReadAttribute("ActivationMechanism", &val))
					return False;
				activationMechanism = String2ActivationType(&val);
				if (activationMechanism == STIMULUS) {
					if (!ifile->ReadStringAttribute("Stimulus", &stimulus))
						return False;
				}
				else if (activationMechanism == TIME) {
					if (!ifile->ReadStringAttribute("TimeExpression", 
									&timeExpression))
						return False;
				}
			}
		}
	}
	return True;
}

void DataProcess::ActivationType2String(DataProcess::ActivationType tp, string *nm) {
	if (tp == UNSPECIFIED)
		*nm = "Unspecified";
	else if (tp == TRIGGER)
		*nm = "Trigger";
	else if (tp == STIMULUS)
		*nm = "Stimulus";
	else if (tp == TIME)
		*nm = "Time";
	else {
		error("%s, line %d: unknown activation mechanism\n",
				__FILE__, __LINE__);
	 	*nm = "Unspecified";
	}
}

DataProcess::ActivationType DataProcess::String2ActivationType(const string *nm) {
	if (*nm == "Unspecified")
		return UNSPECIFIED;
	else if (*nm == "Trigger")
		return TRIGGER;
	else if (*nm == "Stimulus")
		return STIMULUS;
	else if (*nm == "Time")
		return TIME;
	else {
		error("%s, line %d: unknown activation mechanism\n", __FILE__, __LINE__);
		return UNSPECIFIED;
	}
}
