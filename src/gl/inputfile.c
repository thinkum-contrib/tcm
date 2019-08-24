////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "inputfile.h"
#include "error.h"
#include <ctype.h>

InputFile::InputFile(): File() {
	ifile = new std::ifstream();
	lineNr = 0;
}

InputFile::~InputFile() {
	if (ifile)
		delete ifile;
}

void InputFile::Open(const string *file) {
	File::Open(file);
	ifile->clear();
	ifile->open(file->getstr());
	lineNr = 1;
}

bool InputFile::Good() {return ifile->good();}
 
bool InputFile::Eof() {return ifile->eof();}
 
void InputFile::Close() {
	if (IsOpened()) {
		ifile->close();
		File::Close();
	}
}

void InputFile::SkipLine() {
	char c;
	while (!ifile->eof()) {
		c = ifile->get();
		if (c == '\n') {
			lineNr++;
			return;
		}
	} 
}

int InputFile::ReadChar() {
	char c;
	while (!ifile->eof()) {
		c = ifile->get();
		if (c == '\n')
			lineNr++;
		else if (c == '#')
			SkipLine();
		else if (isspace(c))
			continue;
		else
			return c;
	}
	return -1;
}

bool InputFile::LookupChar(const char c) {
	char c2;
	while (!ifile->eof()) {
		c2 = ifile->get();
		if (c2 == '\n')
			lineNr++;
		if (c == c2)
			return True;
		else if (isspace(c2))
			continue;
		else if (c != '#' && c2 == '#')
			SkipLine();
		else {
			error("%s, line %d: '%c' expected\n",
				GetFileName()->getstr(), lineNr, c);
			return False;
		}
	}
	return False;
}

bool InputFile::LookupWord(const string *word) {
	string word2;
	char c;
	// skip white space and comment.
	do {
		if (ifile->eof())
			return False;
		c = ifile->get();
		if (c == '\n')
			lineNr++;
		else if (c == '#') {
			do {
				SkipLine();
				if (ifile->eof())
					break;
				c = ifile->get();
			} while(c == '#');
		}
	} while (isspace(c));
	while (!ifile->eof()) {
		if (isspace(c) || c == '{' || c == '}') {
			ifile->putback(c);
			// if (c == '\n')
			// 	lineNr++;
			if (*word != word2) {
				error("%s, line %d: '%s' expected\n",
					GetFileName()->getstr(), 
					lineNr, word->getstr());
				return False;
			}
			return True;
		}
		word2.add(c);
		c = ifile->get();
	}
	return False;
}

bool InputFile::LookupString(const string *s) {
	string string2;
	char c;
	bool escaped = False;
	if (!LookupChar('"'))
		return False;
	while(!ifile->eof()) {
		c = ifile->get();
		if (c == '\n')
			lineNr++;
		if (c == '\\' && !escaped)
			escaped = True;
		else if (escaped) {
			if (c == 'n')
				string2.add('\r'); // newlines have to become
			else if (c == 't')	   // carriage returns
				string2.add('\t');
			else if (c == 'r')	  
				string2.add('\r');
			else if (c == '"')
				string2.add('"');
			else if (c == '\\')
				string2.add('\\');
			else
				string2.add(c);
			escaped = False;
		}
		else if (c == '"' && !escaped) {
			if (*s != string2) {
				error("%s, line %d: \"%s\" expected\n",
					GetFileName()->getstr(), 
					lineNr, s->getstr());
				return False;
			}
			return True;
		}
		else
			string2.add(c);
	}
	return False;
}

bool InputFile::ReadWord(string *word) {
	char c;
	*word = "";
	// skip white space and comment.
	do {
		if (ifile->eof())
			return False;
		c = ifile->get();
		if (c == '\n')
			lineNr++;
		else if (c == '#') {
			do {
				SkipLine();
				if (ifile->eof())
					break;
				c = ifile->get();
			} while(c == '#');
		}
	} while (isspace(c));
	while(!ifile->eof()) {
		if (isspace(c) || c == '{' || c == '}') {
			ifile->putback(c);
			// if (c == '\n')
			// 	lineNr++;
			return True;
		}
		word->add(c);
		c = ifile->get();
	}
	return False;
}

bool InputFile::ReadString(string *s) {
	char c;
	*s = "";
	bool escaped = False;
	if (!LookupChar('"'))
		return False;
	// get string up to 2nd ".
	while(!ifile->eof()) {
		c = ifile->get();
		if (c == '\n')
			lineNr++;
		if (c == '\\' && !escaped)
			escaped = True;
		else if (escaped) {
			if (c == 'n')
				s->add('\r');
			else if (c == 'r')   // newlines have to
				s->add('\r'); // become carriage returns.
			else if (c == 't')   
				s->add('\t');
			else if (c == '"')
				s->add('"');
			else if (c == '\\')
				s->add('\\');
			else
				s->add(c);
			escaped = False;
		}
		else if (c == '"' && !escaped)
			return True;
		else
			s->add(c);
	}
	return False;
}
