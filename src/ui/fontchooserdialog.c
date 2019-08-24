////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1999, Vrije Universiteit Amsterdam and University of Twente.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl).
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
#include "fontchooserdialog.h"
#include "mstring.h"
#include "xfont.h"
#include <Xm/XmAll.h>

FontChooserDialog::FontChooserDialog(Widget w,
									List <string *> *aps): 
		NToggleListDialog(w, True) {
	SetAutoUnmanage(False);
	fontList = new List<XFont *>;
	exampleFont = 0;
	for (aps->first(); !aps->done(); aps->next())
		addPointSizes.add(aps->cur()); 
}

FontChooserDialog::~FontChooserDialog() {
	fontList->clear();
	delete fontList;
}

void FontChooserDialog::Configure() {
	NToggleListDialog::Configure();
	List<string *> labels;
	labels.add(new string("Family"));
	labels.add(new string("Style"));
	labels.add(new string("Point Size"));
	List<List<string *> *> items;
	List<string *> l1;
	List<string *> l2;
	List<string *> l3;
	List<string *> sl3;
	l1.add(new string("Helvetica"));
	l1.add(new string("Times"));
	l1.add(new string("Courier"));
	l1.add(new string("New Century Schoolbook"));
	l1.add(new string("Symbol (Greek)"));
	l2.add(new string("Roman (Plain)"));
	l2.add(new string("Bold"));
	l2.add(new string("Italic (Oblique)"));
	l2.add(new string("BoldItalic (BoldOblique)"));
	// l3.add(new string("6"));
	l3.add(new string("8"));
	l3.add(new string("10"));
	l3.add(new string("12")); 
	l3.add(new string("14"));
	l3.add(new string("18")); 
	l3.add(new string("24"));

	// add additional pointsizes 
	for (addPointSizes.first(); !addPointSizes.done(); addPointSizes.next()) {
		int i = 0;
		bool pos_found = false; 
		for (l3.first(); !l3.done(); l3.next()) {
			if (l3.cur()->toint() >= addPointSizes.cur()->toint()) {
				if (l3.cur()->toint() > addPointSizes.cur()->toint())
					l3.insert(new string(*addPointSizes.cur()), i);
				// and skip duplicate entry
				pos_found = true;
				break;
			}
			i++;
		}
		if (!pos_found)		// add@tail
			l3.add(new string(*addPointSizes.cur()));
	}

	items.add(&l1);
	items.add(&l2);
	items.add(&l3);
	List<string *> options;
	options.add(new string("update family"));
	options.add(new string("update style"));
	options.add(new string("update size"));
	CreateToggleLists(&labels, &items, &options);
	labels.clear();
	options.clear();
	l1.clear();
	l2.clear();
	l3.clear();
	SetSelectionLabel("Example: ");
	SetTextString("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	// underlinedToggle = XtVaCreateManagedWidget("underlined",
          //       xmToggleButtonWidgetClass, GetWidget(),
            //     XmNset, False, 0);
	ChooseDefault();
	SetToggleChangedCallback(0, ShowExampleCB, this);
	SetToggleChangedCallback(1, ShowExampleCB, this);
	SetToggleChangedCallback(2, ShowExampleCB, this);
}

void FontChooserDialog::ChooseDefault() {
	SetValue(0, 0);
	SetValue(1, 0);
	SetValue(2, 1);
	SetOptionValue(0, True);
	SetOptionValue(1, True);
	SetOptionValue(2, True);
	// SetUnderlined(False);
	ShowExample();
}

void FontChooserDialog::ShowExample() {
	int family = GetValue(0);
	int style = GetValue(1);
	string ps;
	GetItem(2, GetValue(2), &ps);
	int size = ps.toint();
	if (!exampleFont || (family != exampleFont->GetFamily() ||
		style != exampleFont->GetStyle() ||
		size != exampleFont->GetSize()))
		exampleFont = GetFont(family, style, size);
	if (check(exampleFont)) {
		XFontStruct *fs = exampleFont->GetXFontStruct();
		XmFontList fl = XmFontListCreate(fs, 
				XmSTRING_DEFAULT_CHARSET);
		XtVaSetValues(GetText(), XmNfontList, fl, 0);
		XmFontListFree(fl);
	}
}

 
XFont *FontChooserDialog::GetFont(int family, int style, int size) {
	for (fontList->first(); !fontList->done(); fontList->next()) {
		XFont *ft = fontList->cur();
		if (ft->GetFamily() == family && 
		    ft->GetStyle() == style &&
		    ft->GetSize() == size) {
			return ft;
		}
	}
	string foundry = "*";

	bool scalable = False;
	string fixed_sizes = ",8,10,12,14,18,24,";
	string match_size = "," + string(size) + ",";
	if (!fixed_sizes.contains(match_size))
		scalable = True;

	XFont *newFont = new XFont(&foundry, family, style, size, scalable);
	fontList->add(newFont);
	return newFont;
}

void FontChooserDialog::ShowExampleCB(Widget, XtPointer cd, XtPointer) {
	FontChooserDialog *fd = (FontChooserDialog *)cd;
	fd->ShowExample();
}

int FontChooserDialog::GetFamily() {
	return GetValue(0);
}

int FontChooserDialog::GetStyle() {
	return GetValue(1);
}

int FontChooserDialog::GetSize() {
	string ps;
	GetItem(2, GetValue(2), &ps);
	return ps.toint();
}

void FontChooserDialog::SetFamily(int f) {
	SetValue(0, f);
}

void FontChooserDialog::SetStyle(int s) {
	SetValue(1, s);
}

void FontChooserDialog::SetSize(int s) {
	string str = s;
	SetValueOfText(2, &str);
}

bool FontChooserDialog::GetUnderlined() {
        return XmToggleButtonGetState(underlinedToggle);
}

void FontChooserDialog::SetUnderlined(bool b) {
	XmToggleButtonSetState(underlinedToggle, b, True);
}
