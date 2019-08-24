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
#include "printeroptions.h"
#include "config.h"
#include "util.h"

const int PrinterOptions::MIN_PRINT_COPIES=1;
const int PrinterOptions::MAX_PRINT_COPIES=10;

PrinterOptions::PrinterOptions() {
	printCopies = MIN_PRINT_COPIES;
	printBannerPage = Config::DEF_BANNER;
	printCommand = "lpr";
	printerName = "lp";
	tmpFile = "/tmp/";
}

void PrinterOptions::SetPrintCopies(unsigned i) {
	printCopies = max(min(i, MAX_PRINT_COPIES), MIN_PRINT_COPIES);
}

