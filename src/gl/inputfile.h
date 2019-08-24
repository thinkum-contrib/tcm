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
#ifndef _INPUTFILE_H
#define _INPUTFILE_H

#include "file.h"
#include <fstream>

/// Input file class.
class InputFile: public File {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	InputFile();
	///
	virtual ~InputFile();

	/// open a file for reading.
	void Open(const string* file);

	/// close current the file.
	void Close();

	/// is it a correct file.
	bool Good(); 

	/// is end of file reached?
	bool Eof(); 

	/// return line number.
	int LineNumber() {return lineNr;}

	// all read functions skip white space and when a # is read (comment)
	// the rest of the line is skipped.

	// Functions for reading and parsing input stream (file format).
	/// return next non-white-space char from input. Return -1 on eof.
	int ReadChar();

	// reads next sequence of non-white-space-characters from input stream 
	// into s. Returns if such a sequence exists. s can be delimited by 
	// white-space a '{' or a '}'.
	bool ReadWord(string* s);

	// reads next sequence of characters from input stream that starts with 
	// a '"' end ends with a '"' into s. Returns if such a sequence exists. 
	bool ReadString(string* s);

	// reads next non-white-space-character from input stream. returns 
	// if such a character exists and if that character is equal to c
	bool LookupChar(const char c);

	// reads next sequence of non-white-space-characters from input stream. 
	// returns if such a sequence exists and if sequence is equal to s. 
	// s can be delimited by white-space a '{' or a '}'.
	bool LookupWord(const string* s);
	/// 
	bool LookupWord(const char* s) {
		string t = s;
		return LookupWord(&t);
	}

	// reads next sequence of characters from input that starts with a '"' 
	// and ends with a '"'. returns if such a sequence exists and if that 
	// sequence is equal to s.
	bool LookupString(const string* s);
	///
	bool LookupString(const char* s) {
		string t = s;
		return LookupString(&t);
	}

	/// a shorthand to lookup a name and read a value from the input file.
	bool ReadAttribute(const string* name, string* value) {
		return LookupChar('{') && LookupWord(name) && 
			ReadWord(value) && LookupChar('}');
	}
	///
	bool ReadAttribute(const char* name, string* value) {
		string s = name;
		return ReadAttribute(&s, value);
	}
	/// another shorthand to look up a word and read two word values.
	bool ReadAttribute2(
			const string* name, string* value1, string* value2) {
		return LookupChar('{') && LookupWord(name) && 
			ReadWord(value1) && ReadWord(value2) && LookupChar('}');
	}
	///
	bool ReadAttribute2(const char* name, string* value1, string* value2) {
		string s = name;
		return ReadAttribute2(&s, value1, value2);
	}
	/// another shorthand to look up a word and read three word values.
	bool ReadAttribute3(const string* name, string* v1, 
			   string* v2, string* v3) {
		return LookupChar('{') && LookupWord(name) && 
			ReadWord(v1) && ReadWord(v2) && 
			ReadWord(v3) && LookupChar('}');
	}
	///
	bool ReadAttribute3(const char* name, string* v1, 
				string* v2, string* v3) {
		string s = name;
		return ReadAttribute3(&s, v1, v2, v3);
	}

	/// another shorthand to look up a word and read a string value.
	bool ReadStringAttribute(const string* name, string* value) {
		return LookupChar('{') && LookupWord(name) && 
			ReadString(value) && LookupChar('}');
	}
	///
	bool ReadStringAttribute(const char* name, string* value) {
		string s = name;
		return ReadStringAttribute(&s, value);
	}
	///
	bool ReadPair(string* value1, string* value2) {
		return LookupChar('{') && ReadWord(value1) && 
			ReadString(value2) && LookupChar('}');
	}
protected:
	/// skip rest of line.
	void SkipLine();
private:
	/// The current input file.
	std::ifstream* ifile; 

	/// the current ifile line count. Updated by the read functions.
	int lineNr; 	
};
#endif
