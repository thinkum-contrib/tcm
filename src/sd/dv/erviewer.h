//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#ifndef _ERVIEWER_H
#define _ERVIEWER_H

#include "diagramviewer.h"
#include "readdirection.h"
class ERWindow;

/// entity-relationship viewer class.
class ERViewer: public DiagramViewer {
/*@Doc: {\large {\bf scope:} TERD} */
public:
	///
	ERViewer(Config *c, ERWindow *w);
	///
	void Initialize();

	///
	bool IsIsaOnly() {return isaOnly;}
	///
	bool IsValueTypesHidden() {return valueTypesHidden;}

	/// set/reset hided value types.
	void SetHideValueTypes(bool set); 

	/// set/reset show only ISA.
	void SetShowISA(bool set);

	/// update read direction arrow selected object types.
        void UpdateReadDirection(ReadDirection::Type dir);
private:
	/// value types hidden.
	bool valueTypesHidden; 	
	/// isa hierarchy only is made visible.
	bool isaOnly; 		
};
#endif
