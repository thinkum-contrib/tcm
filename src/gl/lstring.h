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
#ifndef _LSTRING_H
#define _LSTRING_H

#include <iostream>

/// infinite length string class.
class string {
/*@Doc: {\large {\bf scope:} global} */
public:
	/// the empty string
        static const string EMPTY;

// constructors.
	/// create empty string.
	string(); 		

	/// copy constructor. usage: string x = string
	string(const string &s);

	/// copy constructor. usage: string x = "abc" 
	string(const char* s);

	/// copy constructor. usage: string x = 'a'
	string(char c);

	/// copy constructor (decimals). usage: string x = 12;
	string(int n);

	/// copy constructor (decimals). usage: string x = 12;
	string(unsigned n);

	/// copy constructor (doubles). usage: string x = 1.2;
	string(double d);

// destructor.
	/// delete string.
	virtual ~string();		

// assignment.
	/// copy operator a la strcpy.
	string &operator=(const string &s);

	/// copy operator a la strcpy.
	string &operator=(const char* s); 

	/// copy operator a la strcpy.
	string &operator=(char c); 

	/// copy operator a la strcpy. s = n in decimal notation.
	string &operator=(int n); 

	/// copy operator a la strcpy. s = n in decimal notation.
	string &operator=(unsigned n); 

	/// copy operator a la strcpy. s = d in floating point notation.
	string &operator=(double d); 

// concatenation.
	/// concat operator a la strcat.
	string &operator+=(const string &s);

	/// concat operator a la strcat.
	string &operator+=(const char* s);

	/// concat. n in decimal notation is added.
	string &operator+=(int n); 

	/// concat. n in decimal notation is added.
	string &operator+=(unsigned n); 

	/// concat. d in floating point notation is added.
	string &operator+=(double d); 

	/// concat operator a la strcat.
	string &operator+=(char c);

	/// constructive concat operator.
	friend string operator+(const char* s1, const string &s2);

	/// constructive concat operator.
	friend string operator+(const string &s1, const char* s2);

	/// constructive concat operator.
	string operator+(const string &s);

	/// constructive concat operator.
	string operator+(const char* s);

	/// add c at end of string.
	void add(char c);	 

	/// add n characters of s at end of string (0 = without limit).
	void add(const string &s, unsigned n = 0);

	/// add n characters of s at end of string (0 = without limit).
	void add(const char *s, unsigned n = 0);

	/// add character at n-th position of string.
	void insert(char c, int pos);

// searching and matching.
	/// return 1 if target is in string. 0 for failure.
	int contains(const string &s) const;

	/// return 1 if target is in string. 0 for failure.
	int contains(const char* s) const;

	/// return 1 if target is in string. 0 for failure.
	int contains(char c) const;

	/// return 1 if string starts with target, 0 for failure.
	int startsWith(const string &s) const;

	/// return 1 if string starts with target, 0 for failure.
	int startsWith(const char* s) const;

	/// return 1 if string ends with target, 0 for failure.
	int endsWith(const string &s) const;

	/// return 1 if string ends with target, 0 for failure.
	int endsWith(const char* s) const;

	/// adds suffix s. return 1 when suffix is changed, 0 when only added.
	int setSuffix(const string &s, char delim = '.');

	/// puts suffix in s. when there is no suffix returns 0, 1 otherwise.
	int getSuffix(string &s, char delim = '.') const;

// element extraction.
	/// selection of char by index a la array.
	char &operator[](int i);

	/// selection of char by index a la array.
	const char &operator[](int i) const;

// deletion.
	/// remove last character of string.
	void remove();		 

	/// remove pos-th character of string.
	void remove(int pos);	 

// substitution.
	/// replace each occurence of old char by nw char .
	int replace(char old, char nw); 

	/// global substitution.
	int replace(const string &pat, const string &repl, int casesens=1); 

	/// first occurrence substitution.
	int replaceFirst(const string &pat, const string &repl, 
		int casesens=1); 

	/// add to word an english plural ending, like horse->horses, sky->skies.
	void addPlural();

// transformation.
	/// move all chars to upper case
	friend string upcase(const string &s);

	/// move all chars to lower case
	friend string downcase(const string &s);

	/// strip all spurious blank chars.
	friend string stripblanks(const string &s);

	/// in-place version of the above.
	void upcase();
	///
	void downcase();
	///
	void stripblanks();
// conversion
	///
	unsigned long toulong() const;
	///
	long tolong() const;
	///
	double todouble() const;
	///
	int toint() const;
// status.
	/// number of characters in string.
	unsigned length() const {return len;} 

	/// the number of lines in string when printed: newlines+1.
	unsigned lines() const;

	/// return nr. of chars of line with most chars in string.
	unsigned width() const; 

	/// return which line has i-th char. pos becomes position in line.
	int whichline(int i, int &pos) const; 

	/// return position of n-th char in line-th line.
	int nthInline(int line, int n) const; 

	/// return number of letters (a-z,A-Z) in string.
	unsigned letters() const;

	/// set precision when string is interpreted as double.
	void setPrecision(unsigned p) {precision=p;}

// IO
	/// write string to output stream.
	friend std::ostream &operator<<(std::ostream &o, const string &s);

	/// read string from input stream.
	friend std::istream &operator>>(std::istream &i, string &s);

// comparison.
	/// comparison operator returns 1 if equal
	friend int operator==(const string &x, const char* s);

	/// comparison operator returns 1 if equal.
	friend int operator==(const string &x, const string &y);

	/// comparison operator that ignores case
	friend int operator%=(const string &x, const char* s);

	/// comparison operator that ignores case
	friend int operator%=(const string &x, const string &y);

	/// comparison operator a la !equal.
	friend int operator!=(const string &x, const char* s);

	/// comparison operator a la !equal.
	friend int operator!=(const string &x, const string &y);

	/// comparison operator a la strcmp
	friend int compare(const string &x, const char* s);

	/// comparison operator a la strcmp
	friend int compare(const string &x, const string &y);

// messy
	/// return a const pointer to the data to do dirty stuff.
	const char* getstr() const {return str;}
protected:
	///
	int doReplace(const string &pat, const string &repl, 
			int global, int casesens=1); 
private:
	/// pointer to data.
	char* str;		

	/// the length of the data.
	int len;

	/// the precision used for floats and doubles.
	int precision;

	/// length in which data is allocated.
	static const int CHUNK;
};
#endif
