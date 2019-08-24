//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
// Author: Henk van de Zandschulp (henkz@cs.utwente.nl)
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

#include "xresources.h"

// When there is no applications default file loaded, these resources are used 
// instead. See the applications default file for the meaning of all 
// these resources.

const char *XResources::classicColorResources[] = {
"*XmText.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*XmTextField.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*Foreground:black",
"*Background:light grey",
"*DrawingArea*Background:linen",
"*LiteClueShell*Background:light yellow",
"*LiteClueShell*FontSet: -*-helvetica-medium-r-*--10-*",
"*logo*Background:light steel blue",
"*MenuBar*Background:light yellow",
"*MenuBar*Foreground:navy",
"*DrawingArea*_popup*Background:light yellow",
"*DrawingArea*_popup*Foreground:navy",
"*DrawingArea*_pulldown*Background: light yellow",
"*DrawingArea*_pulldown*Foreground: navy",
"*Tiles*Nodes*XmToggleButton*Background:misty rose",
"*Tiles*Edges*XmToggleButton*Background:misty rose",
"*Tiles*Layout*XmToggleButton*Background:misty rose",
"*LineStyleDialog*XmToggleButton*Background:misty rose",
"*LineStyleDialog*LiteClueShell*Background:light yellow",
"*LineEndDialog*XmToggleButton*Background:misty rose",
"*LineEndDialog*LiteClueShell*Background:light yellow",
"*LineWidthDialog*XmToggleButton*Background:misty rose",
"*LineWidthDialog*LiteClueShell*Background:light yellow",
"*NodeAlignmentDialog*XmToggleButton*Background:misty rose",
"*NodeAlignmentDialog*LiteClueShell*Background:light yellow",
"*NodeShapeDialog*XmToggleButton*Background:misty rose",
"*NodeShapeDialog*LiteClueShell*Background:light yellow",
"*TextAlignmentDialog*XmToggleButton*Background:misty rose",
"*TextAlignmentDialog*LiteClueShell*Background:light yellow",
"*DocumentName.Background:gold",
"*DocumentType.Background:gold",
"*DocumentLevel.Background:steel blue",
"*DFDiagram.Background:salmon",
"*XmToggleButtonGadget.SelectColor:red",
"*XmToggleButton.SelectColor:red",
"*XmToggleButton.HighlightColor:red",
"*StartupWindow*Foreground:black",
"*StartupWindow*TGD.Background:aquamarine",
"*StartupWindow*TGT.Background:aquamarine",
"*StartupWindow*TGTT.Background:aquamarine",
"*StartupWindow*TESD.Background:light yellow",
"*StartupWindow*TEFD.Background:light yellow",
"*StartupWindow*TSTD.Background:light yellow",
"*StartupWindow*TTUT.Background:light yellow",
"*StartupWindow*TFET.Background:light yellow",
"*StartupWindow*TFRT.Background:light yellow",
"*StartupWindow*TUCD.Background:light blue",
"*StartupWindow*TSSD.Background:light blue",
"*StartupWindow*TATD.Background:light blue",
"*StartupWindow*TSCD.Background:light blue",
"*StartupWindow*TCBD.Background:light blue",
"*StartupWindow*TSQD.Background:light blue",
"*StartupWindow*TCPD.Background:light blue",
"*StartupWindow*TDPD.Background:light blue",
"*StartupWindow*TERD.Background:light pink",
"*StartupWindow*TCRD.Background:light pink",
"*StartupWindow*TDFD.Background:light pink",
"*StartupWindow*TPSD.Background:light pink",
"*StartupWindow*TSND.Background:light pink",
"*StartupWindow*TRPG.Background:light pink",
"*StartupWindow*TTDT.Background:light pink",
"*XmSelectionBox*Background:lavender",
"*XmFileSelectionBox*Background:lavender",
"*XmMessageBox*Background:lavender",
"*fontList:-*-courier-medium-r-*--12-*",
"*XmList.fontList: -*-courier-medium-r-*--12-*",
"*XmText.fontList: -*-courier-medium-r-*--12-*",
"*XmTextField.fontList: -*-courier-medium-r-*--12-*",
"*XmScale.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmLabel.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmLabelGadget.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmCascadeButton.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmCascadeButtonGadget.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmPushButton.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmPushButtonGadget.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmToggleButton.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*XmToggleButtonGadget.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*DocumentName.fontList: -*-courier-bold-r-*--12-*",
"*DocumentType.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*StatusText.fontList: -*-helvetica-medium-r-*--12-*",
"*StartupWindow*frameGEN.XmLabel.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*StartupWindow*frameUML.XmLabel.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*StartupWindow*frameSA.XmLabel.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*StartupWindow*frameMISC.XmLabel.fontList: -*-new century schoolbook-bold-r-*--12-*",
"*StartupWindow*fontList: -*-new century schoolbook-bold-r-*--10-*",
"*StartupWindow*statusBar.fontList: -*-helvetica-medium-r-*--10-*",
0 };

const char *XResources::modernColorResources[] = {
"*XmText.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*XmTextField.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*Foreground:black",
"*Background:light gray",
"*DrawingArea*Background:white",
"*LiteClueShell*Background:light yellow",
"*logo*Background:light steel blue",
"*MenuBar*Background:gray",
"*MenuBar*Foreground:black",
"*DrawingArea*_popup*Background:gray",
"*DrawingArea*_popup*Foreground:black",
"*DrawingArea*_pulldown*Background: gray",
"*DrawingArea*_pulldown*Foreground: black",
"*Tiles*Nodes*XmToggleButton*Background:alice blue",
"*Tiles*Edges*XmToggleButton*Background:alice blue",
"*Tiles*Layout*XmToggleButton*Background:alice blue",
"*DocumentName.Background:light steel blue",
"*DocumentType.Background:light steel blue",
"*DocumentLevel.Background:light steel blue",
"*DFDiagram.Background:light blue",
"*XmToggleButtonGadget.SelectColor:blue",
"*XmToggleButton.SelectColor:blue",
"*XmToggleButton.HighlightColor:red",
"*StartupWindow*Foreground:black",
"*StartupWindow*TGD.Background:aquamarine",
"*StartupWindow*TGT.Background:aquamarine",
"*StartupWindow*TGTT.Background:aquamarine",
"*StartupWindow*TESD.Background:light yellow",
"*StartupWindow*TEFD.Background:light yellow",
"*StartupWindow*TSTD.Background:light yellow",
"*StartupWindow*TTUT.Background:light yellow",
"*StartupWindow*TFET.Background:light yellow",
"*StartupWindow*TFRT.Background:light yellow",
"*StartupWindow*TUCD.Background:light blue",
"*StartupWindow*TSSD.Background:light blue",
"*StartupWindow*TATD.Background:light blue",
"*StartupWindow*TSCD.Background:light blue",
"*StartupWindow*TCBD.Background:light blue",
"*StartupWindow*TSQD.Background:light blue",
"*StartupWindow*TCPD.Background:light blue",
"*StartupWindow*TDPD.Background:light blue",
"*StartupWindow*TERD.Background:light pink",
"*StartupWindow*TCRD.Background:light pink",
"*StartupWindow*TDFD.Background:light pink",
"*StartupWindow*TPSD.Background:light pink",
"*StartupWindow*TSND.Background:light pink",
"*StartupWindow*TRPG.Background:light pink",
"*StartupWindow*TTDT.Background:light pink",
"*XmSelectionBox*Background:gray85",
"*XmFileSelectionBox*Background:gray85",
"*XmMessageBox*Background:gray85",
"*XmMessageBox*XmText*Background:light steel blue",
"*XmSelectionBox*XmTextField.background:white",
"*XmSelectionBox*XmText.background:white",
"*XmSelectionBox*XmList.background:white",
"*XmFileSelectionBox*XmTextField.background:white",
"*XmFileSelectionBox*XmText.background:white",
"*XmFileSelectionBox*XmList.background:white",
"*TextFieldListDialog*XmTextField.background:white",
"*LineStyleDialog*XmToggleButton*Background:alice blue",
"*LineStyleDialog*LiteClueShell*Background:light yellow",
"*LineEndDialog*XmToggleButton*Background:alice blue",
"*LineEndDialog*LiteClueShell*Background:light yellow",
"*LineWidthDialog*XmToggleButton*Background:alice blue",
"*LineWidthDialog*LiteClueShell*Background:light yellow",
"*NodeAlignmentDialog*XmToggleButton*Background:alice blue",
"*NodeAlignmentDialog*LiteClueShell*Background:light yellow",
"*NodeShapeDialog*XmToggleButton*Background:alice blue",
"*NodeShapeDialog*LiteClueShell*Background:light yellow",
"*TextAlignmentDialog*XmToggleButton*Background:alice blue",
"*TextAlignmentDialog*LiteClueShell*Background:light yellow",
"*fontList:-*-helvetica-bold-r-*--12-*",
"*LiteClueShell*FontSet: -*-helvetica-medium-r-*--10-*",
"*XmList.fontList: -*-courier-medium-r-*--12-*",
"*XmText.fontList: -*-courier-medium-r-*--12-*",
"*XmTextField.fontList: -*-courier-medium-r-*--12-*",
"*DocumentName.fontList: -*-helvetica-bold-r-*--12-*",
"*DocumentType.fontList: -*-helvetica-bold-r-*--12-*",
"*StatusText.fontList: -*-helvetica-medium-r-*--10-*",
"*StartupWindow*fontList: -*-helvetica-bold-r-*--12-*",
"*StartupWindow*statusBar.fontList: -*-helvetica-medium-r-*--10-*",
0 };

// monochrome X resources.
const char *XResources::monoResources[] = {
"*XmText.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*XmTextField.translations: #override \
	<Key>osfDelete: delete-next-character()\n\
	<Key>osfBackSpace: delete-previous-character()",
"*Background:white",
"*fontList:-*-helvetica-bold-r-*--12-*",
"*LiteClueShell*FontSet: -*-helvetica-medium-r-*--10-*",
"*XmList.fontList: -*-courier-medium-r-*--12-*",
"*XmText.fontList: -*-courier-medium-r-*--12-*",
"*XmTextField.fontList: -*-courier-medium-r-*--12-*",
"*DocumentName.fontList: -*-helvetica-bold-r-*--12-*",
"*DocumentType.fontList: -*-helvetica-bold-r-*--12-*",
"*StatusText.fontList: -*-helvetica-medium-r-*--11-*",
"*StartupWindow*fontList: -*-helvetica-bold-r-*--12-*",
0 };



