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
#ifndef _PRINTEROPTIONS_H
#define _PRINTEROPTIONS_H

#include "lstring.h"
#include "bool.h"

/// Printer options class.
class PrinterOptions {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	PrinterOptions();

	///
	void SetPrinterName(const string* newName) {
		printerName = *newName;}
	///
	const string* GetPrinterName() {return &printerName;}
	///
	void SetPrintCopies(unsigned i);
	///
	unsigned GetPrintCopies() {return printCopies;}
	///
        void SetPrintBannerPage(int i) {printBannerPage = i;}
        ///
        unsigned GetPrintBannerPage() {return printBannerPage;}
	///
	void SetPrintCommand(const string* newCommand) {
		printCommand = *newCommand;}
	///
	const string* GetPrintCommand() {return &printCommand;}

	///
	void SetTmpFile(const string* s) {
		tmpFile = *s;}
	///
	const string* GetTmpFile() {return &tmpFile;}

	///
	const string* GetTextFilterCommand() {return &textFilterCommand;}
	///
	void SetTextFilterCommand(const string* newCommand) {
		textFilterCommand = *newCommand;}
	///
	static const int MIN_PRINT_COPIES;
	///
	static const int MAX_PRINT_COPIES;
private:
	/// name of current printer.
	string printerName;
 
	/// number of copies that are made.
	unsigned printCopies;

        /// printer banner page
        int printBannerPage;

	/// Unix command to be used to print document.
	string printCommand;

	///
	string textFilterCommand;
	///
	string tmpFile;
};
#endif
