//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//         Rik Eshuis (eshuis@cs.utwente.nl)
//         Jose Canete (canete@lsi.us.es)
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
#ifndef _SCGRAPH_H
#define _SCGRAPH_H

#include "graph.h"

class Prop;

/// state transition graph class.
class SCGraph: public Graph {
/*@Doc: {\large {\bf scope:} TSTD} */
public:
	///
	SCGraph();
	///
	void InitConnections();


	///
	void ComputeExtraOrStates();
	///
	bool AddProp(Prop *p);
	///
	Prop *FindSimilarProp(Prop *p);
	///
	void GetPropList(List <Prop *> &l);
	///
	bool ParseGuardLabel(const string *str);
	///
	bool Init();
	///
	void ComputeInternalProperties();
	///
	void ComputeConflicts();
	///
	void WriteNuSMV(OutputFile *ofile, bool sf);
	///
	bool IsTrigger (string ev);
	///
	bool IsAction (string ev);
	///
	void RetypeEvents ();
	///
	void PrintPropl ();
	///
        Prop *EventInPropl (char *event);

 private:
	/// the list of properties
	List <Prop *> propl;   
};
#endif
