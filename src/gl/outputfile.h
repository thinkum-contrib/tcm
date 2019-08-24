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
#ifndef _OUTPUTFILE_H
#define _OUTPUTFILE_H

#include "file.h"
#include "point.h"

/// Output file class.
class OutputFile: public File {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	OutputFile();
	///
	virtual ~OutputFile();
	///
	void Open(const string* file);
	///
	void Close();
	///
	bool Good(); 
	///
	OutputFile &operator<<(const char* );
	///
	OutputFile &operator<<(char);
	///
	OutputFile &operator<<(unsigned char);
	///
	OutputFile &operator<<(short);
	///
	OutputFile &operator<<(unsigned short);
	///
	OutputFile &operator<<(int);
	///
	OutputFile &operator<<(unsigned int);
	///
	OutputFile &operator<<(long);
	///
	OutputFile &operator<<(unsigned long);
	///
	OutputFile &operator<<(float);
	///
	OutputFile &operator<<(double);
	///
	OutputFile &operator<<(string);
	///
	OutputFile &operator<<(Point);
private:
	/// The current output file.
	std::ofstream* ofile; 
};
#endif
