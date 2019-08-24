//------------------------------------------------------------------------------ // 
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
#ifndef _VERSION_H
#define _VERSION_H

/// Version information of the software.
class Version {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// the current toolkit version as string.
	static const char TOOLKIT_VERSION[];
 
	/// the version of the (default) generated file format.
	static const double FILE_FORMAT;

	/// the text displayed "about" the software.
	static const char ABOUT_TEXT[];
};
#endif
