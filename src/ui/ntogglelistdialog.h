//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _NTOGGLELISTDIALOG_H
#define _NTOGGLELISTDIALOG_H

#include "promptdialog.h"
#include "llist.h"
class string;
class Bitmap;

/// dialog class that shows a number of lists of radio buttons.
class NToggleListDialog: public PromptDialog {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	NToggleListDialog(Widget parent, bool prompt);
	///
	virtual ~NToggleListDialog();
	///
        const char *GetClassName() { return "NToggleListDialog";}
	///
	void SetToggleChangedCallback(
		unsigned n, XtCallbackProc fun, XtPointer cd);
	///
	void CreateToggleLists(List<string *> *labels, 
			List<List<string *> *> *items,
			List<string *> *options = 0);
	///
	void SetItem(unsigned n, unsigned i, const string *text);
	///
        void SetItemBitmap(unsigned n, unsigned i, Bitmap *bitmap);
	///
	void GetItem(unsigned n, unsigned i, string *text);
	///
	void SetValue(unsigned n, unsigned i);
	///
	void SetOptionValue(unsigned n, bool b);
	///
	void SetValueOfText(unsigned n, const string *text);
	///
	int GetValue(unsigned n);
	///
	int GetOptionValue(unsigned n);
	///
	bool IsPromptVisible() {return promptVisible;}
	///
	bool IsOptionsVisible() {return optionsVisible;}
	///
	void SetPromptVisible(bool b);
	///
	void SetOptionsVisible(bool b);
protected:
	///
	void CreateWidget();
	///
	void Configure();
	///
	List<List<Widget> *> *GetToggleList() {return &toggleList;}
private:
	///
	List<List<Widget> *> toggleList;
	///
	List<Widget> optionList;
	///
	bool promptVisible;
	///
	bool optionsVisible;
};

#ifdef __SUNPRO_CC
#if __SUNPRO_CC >= 0x500
template<> inline void List<Widget>::clear() { empty(); }
#else
inline void List<Widget>::clear() { empty(); }
#endif
#endif

#endif
 
