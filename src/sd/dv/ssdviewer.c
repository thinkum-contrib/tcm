//------------------------------------------------------------------------------
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
// along with TCM; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//-----------------------------------------------------------------------------
#include "esdwindow.h"
#include "ssdwindow.h"
#include "ssdsingleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdtripleclassbox.h"
#include "ssdupdateclassboxtypecmd.h"
#include "ssdupdateclassboxpropertycmd.h"
#include "ssdviewer.h"
 
SSDViewer::SSDViewer(Config *c, SSDWindow *d): ERViewer(c, d) { }

SSDViewer::SSDViewer(Config *c, ESDWindow *d): ERViewer(c, d) { }

void SSDViewer::UpdateNodeShapeType(int boxType) {
	SetStatus("action: Update box type");
	List<int *> t;
	switch (boxType) {
	case Code::SSD_SINGLE_CLASS_BOX:
	case Code::SSD_DOUBLE_CLASS_BOX:
	case Code::SSD_TRIPLE_CLASS_BOX:
		t.add(new int(Code::SSD_SINGLE_CLASS_BOX));
		t.add(new int(Code::SSD_DOUBLE_CLASS_BOX));
		t.add(new int(Code::SSD_TRIPLE_CLASS_BOX));
		break;
	case Code::SSD_SINGLE_OBJECT_BOX:
	case Code::SSD_DOUBLE_OBJECT_BOX:
		t.add(new int(Code::SSD_SINGLE_OBJECT_BOX));
		t.add(new int(Code::SSD_DOUBLE_OBJECT_BOX));
		break;
	};
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxTypeCmd(
				GetCurView(), &t, boxType));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
	t.clear();
}

void SSDViewer::UpdateShowStereotypes(bool b) {
	if (b)
		SetStatus("action: show stereotypes");
	else
		SetStatus("action: hide stereotypes");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(), 
				SSDUpdateClassBoxPropertyCmd::STEREOTYPE, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}


void SSDViewer::UpdateShowProperties(bool b) {
	if (b)
		SetStatus("action: show properties");
	else
		SetStatus("action: hide properties");
	if (GetCurView()->NrSelected() > 0) {
		NewCommand(new SSDUpdateClassBoxPropertyCmd(
				GetCurView(), 
				SSDUpdateClassBoxPropertyCmd::PROPERTIES, b));
		ExecuteCommand();
	}
	else
		EmptySelectionMessage();
}
