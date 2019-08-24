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
#ifndef _PSVIEWER_H
#define _PSVIEWER_H

#include "diagramviewer.h"
class PSWindow;

/// process structure viewer class.
class PSViewer: public DiagramViewer {
/*@Doc: {\large {\bf scope:} TPSD} */
public:
	///
	PSViewer(Config *c, PSWindow *w);
	/// shows Sequence of all processes in tree. 0=none, 1=actions, 2=tree.
	void SetShowSequences(int i); 
	///
	void UpdateShowSequences() {UpdateSequenceLabels(showSequence);}
protected:
	///
	void UpdateSequenceLabels(int set);
private:
	/// current type of show sequence.
	int showSequence; 
};
#endif
