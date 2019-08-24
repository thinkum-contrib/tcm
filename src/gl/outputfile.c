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
#include "outputfile.h"
#include "util.h"
#include <fstream>

OutputFile::OutputFile(): File() {
	ofile = new std::ofstream();
}

OutputFile::~OutputFile() {
	if (ofile)
		delete ofile;
}

void OutputFile::Open(const string *file) {
	File::Open(file);
	ofile->clear();
	ofile->open(file->getstr());
}

bool OutputFile::Good() {return ofile->good();}

void OutputFile::Close() {
	if (IsOpened()) {
		ofile->close();
		File::Close();
	}
}

OutputFile &OutputFile::operator<<(const char *v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(unsigned char v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(char v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(short v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(unsigned short v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(int v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(unsigned int v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(long v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(unsigned long v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(float v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}

OutputFile &OutputFile::operator<<(double v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}
  
OutputFile &OutputFile::operator<<(string v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}
  
OutputFile &OutputFile::operator<<(Point v) {
	if (check(ofile))
		(*ofile) << v;
	return *this;
}
