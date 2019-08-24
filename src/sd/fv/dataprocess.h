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
#ifndef _DATAPROCESS_H
#define _DATAPROCESS_H

#include "dfprocess.h"

/// data process (DF) node class.
class DataProcess: public DFProcess {
/*@Doc: {\large {\bf scope:} TDFD} */
public:
	///
	DataProcess(DFGraph *g);
	///
	int GetClassType() const {return Code::DATA_PROCESS;}
	///
	Subject *Clone() {return new DataProcess(*this);}
	///
	enum ActivationType {UNSPECIFIED, STIMULUS, TRIGGER, TIME};
	/// 
	void WriteMembers(OutputFile *f); 
	/// 
	bool ReadMembers(InputFile *f, double format);
	///
	bool SetReferences(AssocList *);
	///
	bool IsProcessGroup() const {return processGroup;}
	///
	bool IsInstantaneous() const {return instantaneous;}
	///
	void SetInstantaneous(bool b); 
	///
	void SetProcessGroup(bool b); 
	///
	const string *GetMinispec() const {return &minispec;}
	///
	void SetMinispec(const string *s);
	///
	ActivationType GetActivationMechanism() const {
		return activationMechanism;}
	///
	void SetActivationMechanism(ActivationType a);
	///
	const string *GetStimulus() const {return &stimulus;}
	///
	void SetStimulus(const string *s);
	///
	const string *GetTimeExpression() const {return &timeExpression;}
	///
	void SetTimeExpression(const string *s);
	///
	static void ActivationType2String(ActivationType a, string *s);
	///
	static ActivationType String2ActivationType(const string *s);
private:
	///
	string minispec;
	///
	bool instantaneous;
	///
	ActivationType activationMechanism;
	///
	string timeExpression;
	///
	string stimulus;
	///
	bool processGroup;
};
#endif
