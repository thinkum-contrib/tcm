//////////////////////////////////////////////////////////////////////////////////
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2001, Universiteit Twente.
// Author: Rik Eshuis (eshuis@cs.utwente.nl).
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
#ifndef _ADSPROP_H
#define _ADSPROP_H



#include "../../gl/bool.h"
#include "../../gl/lstring.h"
#include "adspropertytype.h"
#include "thing.h"

class OutputFile;
class ADSVar;


/// boolean property class
class Prop  {
/*@Doc: {\large {\bf scope:} } */
public:
	///
        Prop(const char *str, PropType p);
	///
      	Prop(){};
	///
	Prop(const Prop &p);
	///
	~Prop();
	///
	bool operator==(const Prop &comp) const;
	///
        string GetName(void);
	///
	PropType GetType(void) const ;
	///
	void SetType(PropType);
	///
	void SetVar(ADSVar *var);
	///
	ADSVar *GetVar(void) const;
	///
	bool isInternal(void);
	///
	void Write(OutputFile *ofile);
	///

	///
	int GetId();

	void Write();

 private:
	/// property name 
	string s;
	/// property type
	PropType stype;
	/// variable property refers to
	ADSVar *v;

};
#endif
