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
#ifndef _UTIL_H
#define _UTIL_H

#include "error.h"
#ifdef __GNUC__
#include <string.h>
#else
#include <strings.h>
#endif

// util.h: some utility functions and constants (not put in some class).

// max. length of (file) names and some buffers.
const int MAXNAME = 1024; 

// Own assert (check) differs from standard assert that it continues 
// execution and that it returns a bool (true if check succeeded).
// Two versions because the SUNOS C++ compiler can't print the expression.
#ifdef SUNOS
#define check(EX) ((EX) || (error("Assertion failed: file \"%s\", line %d\n", __FILE__, __LINE__), 0))
#else
#define check(EX) ((EX) || (error("Assertion failed: %s, file \"%s\", line %d\n", #EX, __FILE__, __LINE__), 0))
#endif

inline int max(int a,int b) {return (a) >= (b) ? (a) : (b);}
inline int min(int a,int b) {return (a) <= (b) ? (a) : (b);}
inline int between(int a, int b, int c) {return (b) < (a) && (a) < (c);}

// inline long abs(long a) {return a>=0? a:-a;}

inline int equal(const char* s1, const char* s2) {return strcmp(s1, s2) == 0;}
inline int equalcase(const char* s1, const char* s2) {
	return strcasecmp(s1, s2) == 0;}

// pixel->millimeter conversion. 1 pixel is 1/83 inch.
inline double pixels2mm(int pixels) {return pixels * (25.4 / 83);}

// millimeter->pixel conversion. 1 pixel is 1/83 inch.
inline double mm2pixels(int mm) {return mm * (83 / 25.4);}

#endif
