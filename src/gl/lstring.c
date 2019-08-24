////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////
#include "lstring.h"
#include "util.h"
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const int string::CHUNK = 512;

#ifndef error
#define error printf
#endif

const string string::EMPTY = string();

string::string() {
	str = new char[CHUNK];
	str[0] = '\0';
	len = 0;
	precision = 2;
}

string::string(const string &s) {
	str = new char[(1 + s.len/CHUNK) * CHUNK];
	::strcpy(str, s.str);
	len = s.len;
	precision = s.precision;
}

string::string(const char *s) {
	str = new char[(1+ ::strlen(s)/CHUNK) * CHUNK];
	::strcpy(str, s);
	len = ::strlen(s);
	precision = 2;
}

string::string(char c) {
	str = new char[CHUNK];
	str[0] = c; str[1] = '\0';
	len = 1;
	precision = 2;
}

string::string(int n) {
	char tmp[256];
	sprintf(tmp, "%d", n);
	str = new char[(1 + ::strlen(tmp)/CHUNK) * CHUNK];
	strcpy(str, tmp);
	len = ::strlen(tmp);
	precision = 2;
}

string::string(unsigned n) {
	char tmp[256];
	sprintf(tmp, "%u", n);
	str = new char[(1 + ::strlen(tmp)/CHUNK) * CHUNK];
	strcpy(str, tmp);
	len = ::strlen(tmp);
	precision = 2;
}

string::string(double d) {
	precision = 2;
	char tmp[256];
	char tmp2[256];
	sprintf(tmp, "%%.%df", precision);
	sprintf(tmp2, tmp, d);
	str = new char[(1 + ::strlen(tmp)/CHUNK) * CHUNK];
	strcpy(str, tmp2);
	len = ::strlen(str);
}

string::~string() {
	delete[] str;
}

string &string::operator=(const string &s) {
	if ((len/CHUNK)!=(s.len/CHUNK)) {
		delete[] str;
		str = new char[(1 + s.len/CHUNK) * CHUNK];
	}
	len = s.len;
	precision = s.precision;
	::strcpy(str, s.str);
	return *this;
}

string &string::operator=(const char *s) {
	int slen = ::strlen(s);
	if ((len/CHUNK)!=(slen/CHUNK)) {
		delete[] str;
		str = new char[(1 + slen/CHUNK) * CHUNK];
	}
	len = slen;
	::strcpy(str, s);
	return *this;
}

string &string::operator=(char c) {
	if (len > CHUNK) {
		delete[] str;
		str = new char[CHUNK];
	}
	len = 1;
	str[0] = c; str[1] = '\0';
	return *this;
}

string &string::operator=(int n) {
	if (len > CHUNK) {
		delete[] str;
		str = new char[CHUNK];
	}
	sprintf(str, "%d", n);
	len = ::strlen(str);
	return *this;
}

string &string::operator=(unsigned n) {
	if (len > CHUNK) {
		delete[] str;
		str = new char[CHUNK];
	}
	sprintf(str, "%u", n);
	len = ::strlen(str);
	return *this;
}

string &string::operator=(double d) {
	char tmp[256];
	if (len > CHUNK) {
		delete[] str;
		str = new char[CHUNK];
	}
	sprintf(tmp, "%%.%df", precision);
	sprintf(str, tmp, d);
	len = ::strlen(str);
	return *this;
}

string &string::operator+=(const string &s) {
	if ((len+s.len)/CHUNK != (len/CHUNK)) {
		char *temp = str;
		str = new char[(1+ (len+s.len)/CHUNK) * CHUNK];
		::strcpy(str, temp);
		delete[] temp;
	}
	len += s.len;
	::strcat(str, s.str);
	return *this;
}

string &string::operator+=(const char *s) {
	int slen = ::strlen(s);
	if ((len+slen)/CHUNK != (len/CHUNK)) {
		char *temp = str;
		str = new char[(1+ (len+slen)/CHUNK) * CHUNK];
		::strcpy(str, temp);
		delete[] temp;
	}
	len += slen;
	::strcat(str, s);
	return *this;
}

string &string::operator+=(char c) {
	add(c);
	return *this;
}

string &string::operator+=(int n) {
	char tmp[256];
	sprintf(tmp, "%d", n);
	return operator+=(tmp);
}

string &string::operator+=(unsigned n) {
	char tmp[256];
	sprintf(tmp, "%u", n);
	return operator+=(tmp);
}

string &string::operator+=(double d) {
	char tmp[256];
	char tmp2[256];
	sprintf(tmp, "%%.%df", precision);
	sprintf(tmp2, tmp, d);
	return operator+=(tmp2);
}

string string::operator+(const string &s) {
	char *buf = new char[s.length() + length() + 1];
	::strcpy(buf, str);
	::strcat(buf, s.str);
	string retval(buf);
	delete[] buf;	// get rid of temp. storage.
	return retval;
}

string string::operator+(const char *s) {
	char *buf = new char[strlen(s) + length() + 1];
	::strcpy(buf, str);
	::strcat(buf, s);
	string retval(buf);
	delete[] buf;	// get rid of temp. storage.
	return retval;
}

string operator+(const char *s1, const string &s2) {
	string retval = s1;
	retval += s2;
	return retval;
}

string operator+(const string &s1, const char *s2) {
	string retval = s1;
	retval += s2;
	return retval;
}

void string::add(char c) {
	if ((len+1) % CHUNK == 0) {
		char *tmp = new char[len + 1 + CHUNK];
		::strcpy(tmp, str);
		delete[] str;
		str = tmp;
	}
	str[len++] = c;
	str[len] = '\0';
}

void string::add(const string &s, unsigned n /* = 0 */) {
	if ( n == 0 || n > (unsigned) s.len )
		n = s.len;
	if ((len+n)/CHUNK != (unsigned) (len/CHUNK)) {
		char *temp = str;
		str = new char[(1+ (len+n)/CHUNK) * CHUNK];
		::strcpy(str, temp);
		delete[] temp;
	}
	len += n;
	::strncat(str, s.str, n);
}

void string::add(const char *s, unsigned n /* = 0 */) {
	unsigned slen = ::strlen(s);
	if ( n != 0 && n < slen )
		slen = n;
	if ((len+slen)/CHUNK != (unsigned) (len/CHUNK)) {
		char *temp = str;
		str = new char[(1+ (len+slen)/CHUNK) * CHUNK];
		::strcpy(str, temp);
		delete[] temp;
	}
	len += slen;
	::strncat(str, s, slen);
}

void string::insert(char c, int n) {
	if (n<0 || n > len)
		return;
	if ((len+1) % CHUNK == 0) {
		char *tmp = new char[len + 1 + CHUNK];
		::strcpy(tmp, str);
		delete[] str;
		str = tmp;
	}
	for (int i=len; i>n; i--)
		str[i] = str[i-1];
	str[n] = c;
	len++;
	str[len] = '\0';
}

int string::contains(const string &s) const {
	// here empty string is _not_ substring of non-empty string.
	if (s == "")
		return (len == 0);
	else
		return (::strstr(str, s.str) != 0);
}

int string::contains(const char *s) const {
	if (equal(s, ""))
		return (len == 0);
	else
		return (::strstr(str, s) != 0);
}

int string::contains(char c) const {
	return (::strchr(str, c) != 0);
}

int string::startsWith(const string &s) const {
	if (s.len > len)
		return 0;
	for (int i=0; i<s.len; i++)
		if (str[i] != s.str[i])
			return 0;
	return 1;
}

int string::startsWith(const char *s) const {
	int slen = strlen(s);
	if (slen > len)
		return 0;
	for (int i=0; i<slen; i++)
		if (str[i] != s[i])
			return 0;
	return 1;
}

int string::endsWith(const string &s) const {
	if (s.len > len)
		return 0;
	for (int i=0; i<s.len; i++) {
		if (str[len-s.len+i] != s.str[i])
			return 0;
	}
	return 1;
}

int string::endsWith(const char *s) const {
	int slen = strlen(s);
	if (slen > len)
		return 0;
	for (int i=0; i<slen; i++) {
		if (str[len-slen+i] != s[i])
			return 0;
	}
	return 1;
}

int string::setSuffix(const string &s, char delim) {
	char *c = strrchr(str, delim);
	char *c2 = strrchr(str, '/');
        if (c && (!c2 || c>c2)) {
		if (s[0] != delim)
			c++;
		int n = strlen(c);
		for (int i=0; i<n; i++)
			remove();
                operator+=(s);
		return 1;
	}
        else {
		if (s[0] != delim)
			operator+=(delim);	
                operator+=(s);
		return 0;
	}
}
 
int string::getSuffix(string &s, char delim) const {
	char *c = strrchr(str, delim);
        if (c) {
		s = c;
		return 1;
	}
	else
		return 0;
}

void string::remove() {
	if (len == 0) 
		return;
	str[--len] = '\0';
	if ((len+1) % CHUNK == 0) {
		char *tmp = new char[len+1];
		::strcpy(tmp, str);
		delete[] str;
		str = tmp;
	}
}

void string::remove(int n) {
	if (n<0 || n>=len)
		return;
	for (int i=n; i<len-1; i++)
		str[i] = str[i+1];
	str[--len] = '\0';
	if ((len+1) % CHUNK == 0) {
		char *tmp = new char[len+1];
		::strcpy(tmp, str);
		delete[] str;
		str = tmp;
	}
}

int string::replace(char ol, char nw) {
	int count = 0;
	for (int i=0; i<len; i++)
		if (str[i] == ol) {
			str[i] = nw;
			count++;
		}
	return count;
}

int string::replaceFirst(const string &pat, const string &repl, int casesens) {
	return doReplace(pat, repl, 0, casesens);
}

int string::replace(const string &pat, const string &repl, int casesens) {
	return doReplace(pat, repl, 1, casesens);
}

int string::doReplace(const string &pat, const string &repl, int global, 
		int casesens) {
	if (pat.len == 0) {
		if (len != 0)
			return 0;
		else {
			*this = repl;
			return 1;
		}
	}
	if (pat == repl)
		return 0;
	int count = 0;
	char *p = str;
	int ldiff = repl.len - pat.len;
	while (*p) {
		if ((casesens && strncmp(p, pat.str, pat.len) == 0) ||
		    (!casesens && strncasecmp(p, pat.str, pat.len) == 0)) {
			// add or remove chunks.
			if ((len+ldiff)/CHUNK != (len/CHUNK)) {
				int i = (p - &str[0]);
				char *tmp = 
					new char[(1+(len+ldiff)/CHUNK)*CHUNK];
				::strcpy(tmp, str);
				delete[] str;
				str = tmp;
				p = &str[i];
			}
			// shift part after pattern.
			char *q = p + pat.len;
			char *s;
			if (ldiff > 0) // shift left.
				for (s = &str[len-1]; s >= q; s--)
					*(s + ldiff) = *s;
			else if (ldiff < 0) // shift right.
				for (s = q; s < &str[len]; s++)
					*(s + ldiff) = *s;
			// place repl.
			::strncpy(p, repl.str, repl.len); 
			len += ldiff;
			p += repl.len;
			str[len] = '\0';
			count++;
			if (!global)
				return 1;
		}
		else
			p++;
	}
	return count;
}

char &string::operator[](int i) {
	if (i < 0 || len < i) {
		error("%s, line %d: string index out of range\n", 
			__FILE__, __LINE__);
		return str[0];
	}
	return str[i];
}

const char &string::operator[](int i) const {
	if (i < 0 || len < i) {
		error("%s, line %d: string index out of range\n", 
			__FILE__, __LINE__);
		return str[0];
	}
	return str[i];
}

string upcase(const string &s) {
	string retval(s);
	retval.upcase();
	return retval;
}

string downcase(const string &s) {
	string retval(s);
	retval.downcase();
	return retval;
}
 
void string::upcase() {
	for (int i=0; i<len; i++)
		str[i] = toupper(str[i]);
}

void string::downcase() {
	for (int i=0; i<len; i++)
		str[i] = tolower(str[i]);
}

unsigned long string::toulong() const {return (unsigned long) atol(str);}

long string::tolong() const {return atol(str);}

int string::toint() const {return atoi(str);}

double string::todouble() const {return atof(str);}

unsigned string::lines() const {
	unsigned nLines = 1;
	char *lstr = str;
	char c;
	if (len == 0)
		return 0;
	for (int i=0; i<len; i++) {
		c = *lstr;
		if (c == '\n' || c == '\r')
			nLines++;
		lstr++;
	}
	return nLines;
}

unsigned string::width() const {
	unsigned max = 0, llen = 0;
	char *lstr = str;
	for (int i=0; i<len; i++) {
		char c = *lstr++;
		if (c == '\n' || c == '\r') {
			if (llen > max)
				max = llen;
			llen = 0;
		}
		llen++;
	}
	if (llen > max)
		max = llen;
	return max;
}

int string::whichline(int n, int &pos) const {
	unsigned lineNr = 1;
	char *lstr = str;
	pos = -1;
	if (n < 0 || len < n)
		return -1;
	for (int i=0; i<=len; i++) {
		pos++;
		if (n == i)
			return lineNr;
		if (*lstr == '\n' || *lstr == '\r') {
			pos = -1;
			lineNr++;
		}
		lstr++;
	}
	return -1;
}

int string::nthInline(int line, int n) const {
	int lineNr = 1;
	char *lstr = str;
	if (n < 0)
		n = 0;
	for (int i=0; i<=len; i++) {
		if (lineNr == line) {
			for (int j=i; j<n+i; j++) {
				if (j==len || *lstr == '\n' || *lstr == '\r')
					return j;
				lstr++;
			}
			return i+n;
		}
		if (*lstr == '\n' || *lstr == '\r')
			lineNr++;
		lstr++;
	}
	return -1;
}

unsigned string::letters() const {
	unsigned count = 0;
	char *lstr = str;
	for (int i=0; i<len; i++) {
		if (isalpha(*lstr++))
			count++;
	}
	return count;
}
		
void string::addPlural() {
	char lc = str[len-1];
	if (lc == 's')
		operator+=("es");
	else if (lc == 'h' && len>=2) {
		char slc = str[len-2];
		if (slc == 's' || slc == 'c')
			operator+=("es");
		else
			operator+=("s");
	}
	else if (lc == 'y' && len>=2) {
		char slc = str[len-2];
		if (slc != 'a' && slc != 'e' && slc != 'o' && slc != 'u') {
			remove();
			operator+=("ies");
		}
		else
			operator+=("s");
	}
	else
		operator+=("s");
}

std::ostream &operator<<(std::ostream &o, const string &s) {
	for (int i=0; i<s.len; i++) {
		char c = s.str[i];
		if (c == '\n') {
			o.put('\\');
			o.put('n');
		}
		else if (c == '\r') {
			o.put('\\');
			o.put('r');
		}
		else if (c == '\t') {
			o.put('\\');
			o.put('t');
		}
		else if (c == '\\' || c == '"') {
			o.put('\\');
			o.put(c);
		}
		else
			o.put(c);
	}
	return o;
}

std::istream &operator>>(std::istream &i, string &s) {
	i >> s.str;
	s.len = ::strlen(s.str);
	return i;
}

int operator==(const string &x, const char *s) {
	return equal(x.str, s);
}

int operator==(const string &x, const string &y) {
	return equal(x.str, y.str);
}

int operator%=(const string &x, const char *s) {
	return equalcase(x.str, s);
}

int operator%=(const string &x, const string &y) {
	return equalcase(x.str, y.str);
}

int operator!=(const string &x, const char *s) {
	return !equal(x.str, s);
}

int operator!=(const string &x, const string &y) {
	return !equal(x.str, y.str);
}

int compare(const string &x, const char *s) {
	return strcmp(x.str, s);
}

int compare(const string &x, const string &y) {
	return strcmp(x.str, y.str);
}

string stripblanks(const string &s) {
	string retval(s);
	retval.stripblanks();
	return retval;
}
 
void string::stripblanks() {
	char *oldstring = new char[(1+ ::strlen(str)/CHUNK) * CHUNK];
	char *newstring = new char[(1+ ::strlen(str)/CHUNK) * CHUNK];
	char *token;
	const char delimiters[] = " \t\r\n";
	int i = 1;

	// traceline
	// printf ("- void string::stripblanks() : [%s] {%d}\n",
 	// 		str, ::strlen(str));

	::strcpy(oldstring, str);
	::strcpy(newstring, "");

	if ((token = strtok (oldstring, delimiters)) != 0) {
		::strcat (newstring, token);
//		printf ("%d : [%s] -> [%s]\n", i, token, newstring);
	}

	while ((token = strtok (0, delimiters)) != 0) {
		i++;
		::strcat (newstring, " ");
		::strcat (newstring, token);
//		printf ("%d : [%s] -> [%s]\n", i, token, newstring);
	}

	::strcpy(str, newstring);

	// traceline
	// printf ("  --) void string::stripblanks() : [%s] {%d}\n",
 	// 		str, ::strlen(str));
}
