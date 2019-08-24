////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1998, Vrije Universiteit Amsterdam.
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
#include "properties.h"
#include "inputfile.h"
#include "outputfile.h"
#if defined(__SUNPRO_CC)
#if __SUNPRO_CC >= 0x500
template<> void List<Property>::clear() { empty(); }
#else
template<> void List<Property>::clear() { empty(); }
#endif
#endif

void Properties::Save(OutputFile *f) {
	string x("");
	Save(f, &x);
}

void Properties::Save(OutputFile *, const string *) {
}

void Properties::Load(InputFile *f) {
	f->Open(f->GetFileName());
	while (!f->Eof()) {
		Property *p = new Property;
		if (!f->ReadPair(&p->key, &p->value)) {
			delete p;
			break;
		}
		else
			add(*p);
	}
	f->Close();
}

const string *Properties::GetValue(const string *) {
	return 0;
}

const string *Properties::GetValue(const char *key) {
	string x = key;
	return GetValue(&x);
}
