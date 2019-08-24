//------------------------------------------------------------------------------
// 
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam.
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
#ifndef _AFONT_H
#define _AFONT_H

#include "lstring.h"
#include "bool.h"

/// An abstract font class. 
class AFont {
/*@Doc: {\large {\bf scope:} global} */
public:
	// Constants to be used for font families.

	/// Helvetica font family.
	static const int HELVETICA;

	/// Times Roman font family.
	static const int TIMESROMAN;

	/// Courier (fixed width) font family.
	static const int COURIER;

	/// New century schoolbook font family.
	static const int NEWCENTURYSCHLBK;

	/// Symbol font family.
	static const int SYMBOL;

	// Constants to be used for styles. Can be combined to mix styles. 

	/// Plain style constant. Can be mixed with other style constants.
	static const int PLAIN;

	/// Bold style constant. Can be mixed with other style constants.
	static const int BOLD;

	/// Italicized style constant. Can be mixed with other style constants.
	static const int ITALIC;

	/// Creates new font with the specified name, style and point size.
	AFont(const string* foundry, int name, int style, int size, 
		bool scalable);

	/// Gets the family name of the font.
	int GetFamily() { return family; }

	/// Gets the style of the font.
	int GetStyle() { return style; }

	/// Gets the point size of the font.
	int GetSize() { return size; }

	/// Is the font scalable.
	bool IsScalable() {return scalable;}

	///
	const string* GetFoundry() {return &foundry;}

	///
	void SetScalable(bool b) {scalable = b;}

	/// Is the font underlined.
	bool IsUnderlined() {return underlined;}

	/// Set/Unset font underlined option
	void SetUnderlined(bool b) {underlined=b;}

	/// The factor with which a scalable font is scaled.
	double GetFactor() {return factor;}

	///
	void SetFactor(double d) {factor = d;}

	/// Returns true if the font is plain.
	bool IsPlain() { return style == 0; }

	/// Returns true if the font is bold.
	bool IsBold() { return (style & BOLD) != 0; }

	/// Returns true if the font is italic.
	bool IsItalic() { return (style & ITALIC) != 0; }

private:
	/// factor for scalable fonts.
	double factor;

	/// the font foundry
	string foundry;

	/// The family of this font. 
	int family;

	/// The style of the font (sum of constants PLAIN, BOLD, or ITALIC). 
	int style;

	/// The point size of this font.
	int size;

	/// The font is scalable.
	bool scalable;

	/// The font is underlined.
	bool underlined;
};
#endif
