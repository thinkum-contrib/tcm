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
#ifndef _MENU_H
#define _MENU_H

#include "mwidget.h"
#include "menuitem.h"

/// Class for menu manipulation.
class Menu: public MWidget {
/*@Doc: {\large {\bf scope:} GUI} */
public:
	///
	enum MenuType {PULLDOWN, POPUP, OPTION};

	///
	Menu(Widget parent, MenuType menuType, const char *name,
		char mnemonic, MenuItem *items);

	///
	const char *GetClassName() { return "Menu";}
 
	/// 
	Widget GetNthMenuItem(int n);
	/// 
	Widget GetMenuItem(const char *label);

	/// 
	static Widget GetChild(Widget menu, MenuType type, const char *label);
	/// 
	static Widget GetNthChild(Widget menu, MenuType type, int n);
	///
	static void SetChildToggleState(
		Widget menu, MenuType type, const char *label, 
		bool state, bool notify=False);
	///
	static void SetNthChildToggleState(
		Widget menu, MenuType type, int n,
		bool state, bool notify=False);
	///
	static void SetChildSensitive(
		Widget menu, MenuType type, const char *label, bool state);
	///
	static void SetNthChildSensitive(
		Widget menu, MenuType type, int n, bool state);
private:
	///
	MenuType menuType;
	///
	Widget BuildMenu(Widget parent, MenuType type, const char *label, 
		char mnem, MenuItem *items);
};
#endif
