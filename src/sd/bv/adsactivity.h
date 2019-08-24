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
#ifndef _ADSACT_H
#define _ADSACT_H

#include "llist.h"
#include "lstring.h"
;
class ADSVar;
class OutputFile;

/// activity class.
class ADSActivity  {
/*@Doc: {\large {\bf scope:} } */
public:
	///
        ADSActivity(string str);
	///
	ADSActivity(const ADSActivity &p);
	///
	~ADSActivity();
	///
      	bool operator==(const ADSActivity &comp) const;
	//		bool operator< (const ADSActivity &comp) const;
	//		bool operator> (const ADSActivity &comp) const {
	//			return comp < *this;
	//		};
	//		bool operator<=(const ADSActivity &comp) const {
	//			return ! (comp < *this);
	//		};
	//		bool operator>=(const ADSActivity &comp) const {
	//			return ! operator<(comp);
	//		};
	//		bool operator!=(const ADSActivity &comp) const {
	//			return ! operator==(comp);
	//		};
	///
        string GetName(void);
	///
	void AddUpdate(ADSVar *v);
	///
	void RemoveUpdate(ADSVar *v);
	/// 
	void GetUpdateList(List <ADSVar *> &l){l=ul;};
	/// true iff activity updates variable v
	bool isUpdated(ADSVar *v){ return (ul.find(v)>-1);}
	///
	void Write(OutputFile *ofile);   
 	void Write();   
   
 private:
	/// activity name
	string s;
	/// list of variables that the activity updates
	List <ADSVar *> ul; 

};
#endif
