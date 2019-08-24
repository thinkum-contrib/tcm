//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
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
#ifndef __DFINSTANCES_H
#define __DFINSTANCES_H

#ifdef __GNUC__

//GNU g++ does not implement a separate pass to instantiate template
//functions and classes at this point; for this reason, it will not work,
//for the most part, to declare your template functions in one file and
//define them in another. The compiler will need to see the entire
//definition of the function, and will generate a static copy of the
//function in each file in which it is used.
// 
//g++ does not automatically instantiate templates defined in other
//files. Because of this, code written for cfront will often produce
//undefined symbol errors when compiled with g++. You need to tell g++
//the file where they are defined.

#include "dginstances.h"

#include "../sd/fv/dfprocess.h"
#include "../sd/fv/dfedge.h"

template class List<DFProcess *>;
template class List<DFEdge *>;

#endif
#endif
