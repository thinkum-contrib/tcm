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
#include "erstubs.h"
#include "erdiagram.h"
#include "mstring.h"
#include <Xm/ToggleB.h>

void ERStubs::HideValueTypesCB(Widget w, XtPointer cd, XtPointer) {
	((ERViewer *)cd)->SetHideValueTypes(XmToggleButtonGetState(w));
}

void ERStubs::ShowISACB(Widget w, XtPointer cd, XtPointer) {
	((ERViewer *)cd)->SetShowISA(XmToggleButtonGetState(w));
}

void ERStubs::UpdateReadDirectionCB(Widget w, XtPointer cd, XtPointer) {
        // get menu item label and look to which dir it corresponds
        XmString xms;
        xms = CreateXmString("");
        XtVaGetValues(w, XmNlabelString, &xms, 0);
        char *txt;
        ReadDirection::Type dir;
        if (XmStringGetLtoR(xms, XmFONTLIST_DEFAULT_TAG, &txt)) {
                string s = txt;
                if (s.contains("From"))
                        dir = ReadDirection::FROMSHAPE;
                else if (s.contains("To"))
                        dir = ReadDirection::TOSHAPE;
                else
                        dir = ReadDirection::NONE;
                ((ERViewer *)cd)->UpdateReadDirection(dir);
                XtFree(txt);
        }
        XmStringFree(xms);
}

