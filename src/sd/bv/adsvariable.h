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
#ifndef _ADSVAR_H
#define _ADSVAR_H


#include "bool.h"
#include "lstring.h"
#include "adspropertytype.h"

class OutputFile;

/// variable class. 
class ADSVar {
/*@Doc: {\large {\bf scope:} } */
public:
        ADSVar(const char *str,PropType p);
	///
	ADSVar(){};
	ADSVar(const ADSVar &v);  
	///
	~ADSVar();
	///
	bool operator==(const ADSVar &comp) const;
	///
        string GetName(void) const ;
	///        
	PropType GetType(void);
  	///
	void Write(OutputFile *ofile);
 	///
	void WriteScreen();

 private:
	/// name of variable
	string name; 
	/// type of variable
	PropType ptype;

};
#endif
