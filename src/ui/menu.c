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
#include "menu.h"
#include "mstring.h"
#include "util.h"
#include <string.h>
#include <Xm/XmAll.h>

Menu::Menu(Widget parent, MenuType type, const char *n, char mnemonic, 
		MenuItem *items): MWidget(n) {
	menuType = type;
	// create menu widget.
	SetWidget(BuildMenu(parent, menuType, (char *)GetName()->getstr(), 
		  mnemonic, items));
	// set up destruction handler.
	InstallDestroyHandler();
}

Widget Menu::GetNthMenuItem(int n) {
	return GetNthChild(GetWidget(), menuType, n);
}

Widget Menu::GetNthChild(Widget w, MenuType type, int n) {
	Widget submenu;
	WidgetList wlist; int numc;
	if (type == PULLDOWN)
		XtVaGetValues(w, XmNsubMenuId, &submenu, NULL);
	else
		submenu = w;
	if (!check(submenu))
		return 0;
	XtVaGetValues(submenu, XmNchildren, &wlist, NULL);
	XtVaGetValues(submenu, XmNnumChildren, &numc, NULL);
	if (n <= numc)
		return wlist[n-1];
	else
		return 0;
}

void Menu::SetNthChildToggleState(Widget w, MenuType type, int n, 
		bool state, bool notify) {
	Widget child = GetNthChild(w, type, n);
	if (check(child))
		XmToggleButtonSetState(child, state, notify);
}

void Menu::SetNthChildSensitive(Widget w, MenuType type, int n, 
		bool state) {
	Widget child = GetNthChild(w, type, n);
	if (check(child))
		XtVaSetValues(child, XmNsensitive, state, NULL);
}

Widget Menu::GetMenuItem(const char *label) {
	return GetChild(GetWidget(), menuType, label);
}

Widget Menu::GetChild(Widget w, MenuType menuType, const char *label) {
	Widget submenu;
	WidgetList wlist; int numc;
	if (menuType == PULLDOWN)
		XtVaGetValues(w, XmNsubMenuId, &submenu, NULL);
	else
		submenu = w;
	if (!check(submenu))
		return 0;
	XtVaGetValues(submenu, XmNchildren, &wlist, NULL);
	XtVaGetValues(submenu, XmNnumChildren, &numc, NULL);
	XmString s2;
	for (int i=0; i < numc; i++) {
		s2 = CreateXmString("");
		XtVaGetValues(wlist[i], XmNlabelString, &s2, NULL); 
		char *str;
		if (XmStringGetLtoR(s2, XmFONTLIST_DEFAULT_TAG, &str)) {
			// std::cout << str << std::endl;
			// std::cout << label << std::endl;
                	if (strstr(str, label)) {
				XtFree(str);	
				XmStringFree(s2);
				return wlist[i];
			}
			XtFree(str);	
		}
		XmStringFree(s2);
	}
	return 0;
}

void Menu::SetChildToggleState(Widget w, MenuType type, 
		const char *label, bool state, bool notify) {
	Widget child = GetChild(w, type, label);
	if (check(child))
		XmToggleButtonSetState(child, state, notify);
}

void Menu::SetChildSensitive(Widget w, MenuType type, 
		const char *label, bool state) {
	Widget child = GetChild(w, type, label);
	if (check(child))
		XtVaSetValues(child, XmNsensitive, state, NULL);
}

// Build popup, option and pulldown menus, depending on the menu type.
// It may be Pulldown, Option or Popup.  Pulldowns
// return the CascadeButton that pops up the menu.  Popups return the menu.
// Option menus are created, but the RowColumn that acts as the option
// "area" is returned unmanaged. (The user must manage it.)
// Pulldown menus are built from cascade buttons, so this function
// also builds pullright menus.  The function also adds user data
// for PushButton or ToggleButton menu items.
Widget Menu::BuildMenu(Widget parent, MenuType type, const char *label, 
		char mnemonic, MenuItem *items) {
	Widget menu, cascade, submenu;
	XmString str;
	int i = 0;
	char wname[MAXNAME];
	if (type == PULLDOWN || type == OPTION) {
		strcpy(wname, "_pulldown");
		menu = XmCreatePulldownMenu(parent, wname, 0, 0);
	}
	else if (type == POPUP) {
		strcpy(wname, "_popup");
		menu = XmCreatePopupMenu(parent, wname, 0, 0);
	}
	else {
		XtWarning("Invalid menu type passed to BuildMenu()");
		return 0;
	}
	// Pulldown menus require a cascade button to be made
	if (type == PULLDOWN) {
		str = CreateXmString(label);
		cascade = XtVaCreateManagedWidget(label,
			xmCascadeButtonWidgetClass, parent,
			XmNsubMenuId, menu,
			XmNlabelString, str,
			XmNmnemonic, mnemonic, NULL);
		XmStringFree(str);
	} else if (type == OPTION) {
		// Option menus are a special case, but not hard to handle
		Arg args[9]; 
		str = CreateXmString(label);
		XtSetArg(args[i], XmNsubMenuId, menu); i++;
		XtSetArg(args[i], XmNlabelString, str); i++;
		// This really isn't a cascade, but this is the widget handle
		// we're going to return at the end of the function.
//HZ		cascade = XmCreateSimpleOptionMenu(parent, label, args, i);
		cascade = XmCreateOptionMenu(parent, (char *)label, args, i);
		XmStringFree(str);
	}
	else
		cascade = 0;
	// Now add the menu items
	for (i = 0; items[i].label != 0; i++) {
		// If subitems exist, create the pull-right menu by calling this
		// function recursively.  Since the function returns a cascade
		// button, the widget returned is used..
		//
		if (items[i].subitems) {
		  	if (type == OPTION) {
		   		XtWarning("You can't have submenus from "
					  "option menu items.");
		    		continue;
		  	} else
				submenu = BuildMenu(menu, PULLDOWN,
					items[i].label, items[i].mnemonic, 
					items[i].subitems);
		}
		else {
			WidgetClass *wc;
			int tp = items[i].itemType;
			if (tp == MenuItem::SUBMENU)
				wc = &xmCascadeButtonWidgetClass;
			else if (tp == MenuItem::RADIOBUTTON || 
				 tp == MenuItem::CHECKBUTTON)
				wc = &xmToggleButtonWidgetClass;
			else if (tp == MenuItem::SEPARATOR)
				wc = &xmSeparatorWidgetClass;
			else if (tp == MenuItem::LABEL)
				wc = &xmLabelWidgetClass;
			else
				wc = &xmPushButtonWidgetClass;
			submenu = XtVaCreateManagedWidget(items[i].label,
				*wc, menu, NULL);
		}
		// toggle buttons are always visible as such
		if (items[i].itemType == MenuItem::RADIOBUTTON || 
		    items[i].itemType == MenuItem::CHECKBUTTON) {

			XtVaSetValues(submenu, XmNindicatorOn, True,
				XmNvisibleWhenOff, True,
				XmNindicatorSize, 12, 
				NULL);
			// box or diamond ?
			if (items[i].itemType == MenuItem::RADIOBUTTON) {
				XtVaSetValues(menu, 
					XmNradioBehavior, True, NULL);
				XtVaSetValues(submenu, 
					XmNindicatorType, XmONE_OF_MANY, NULL);
			}
			// selected or not ?
			if ((long)items[i].userData & 0x1)
				XtVaSetValues(submenu, XmNset, True, 0);

		}
		if (items[i].userData)
			XtVaSetValues(submenu, XmNuserData, 
					items[i].userData, NULL);

		// Whether the item is a real item or a cascade button with a
		// menu, it can still have a mnemonic.
		//
		if (items[i].mnemonic)
			XtVaSetValues(submenu, XmNmnemonic, 
				items[i].mnemonic, NULL);
		// any item can have an accelerator, except cascade menus. But,
		// we don't worry about that; we know better in our 
		// declarations.
		if (items[i].accelerator) {
			str = CreateXmString(items[i].accelText);
			XtVaSetValues(submenu, XmNacceleratorText, str, NULL);
			XtVaSetValues(submenu, XmNaccelerator, 
					items[i].accelerator, NULL);
			XmStringFree(str);
		}

		if (items[i].callback)
			// ToggleButton class or PushButton class
			XtAddCallback(submenu,
				(items[i].itemType == MenuItem::CHECKBUTTON ||
				 items[i].itemType == MenuItem::RADIOBUTTON)?
				XmNvalueChangedCallback :
				XmNactivateCallback, 
				items[i].callback, items[i].callbackData);

		// set if item is selectable
		XtVaSetValues(submenu, XmNsensitive, items[i].sensitive, NULL);

		if (items[i].showBitmap) {
			Bitmap b = items[i].bitmap;
			if (check(XtDisplay(menu))) {
			 	Pixmap px = b.CreatePixmap(menu, 
					XtDisplay(menu));
			 	XtVaSetValues(submenu,
                          		XmNlabelType, XmPIXMAP,
                          		XmNlabelPixmap, px, NULL);
			}
		}
	}
	// for popup menus, just return the menu; pulldown menus, return
	// the cascade button; option menus, return the thing returned
	// from XmCreateOptionMenu().  This isn't a menu, or a cascade button!
	return type == POPUP? menu : cascade;
}
