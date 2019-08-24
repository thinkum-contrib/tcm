////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 2000, Vrije Universiteit Amsterdam.
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
#include "nodeshapedialog.h"
#include "bitmap.h"
#include <Xm/Xm.h>
#include "Box.xbm"
#include "Square.xbm"
#include "Circle.xbm"
#include "StickMan.xbm"
#include "Ellipse.xbm"
#include "Triangle.xbm"
#include "Diamond.xbm"
#include "NoteBox.xbm"
#include "Hexagon.xbm"
#include "HorizontalBar.xbm"
#include "VerticalBar.xbm"
#include "SolidHorizontalBar.xbm"
#include "SolidVerticalBar.xbm"
#include "BlackDot.xbm"
#include "BullsEye.xbm"
#include "RoundedBox.xbm"
#include "EllipsedBox.xbm"
#include "Comment.xbm"
#include "Cube.xbm"
#include "Folder.xbm"
#include "Disk.xbm"
#include "SubFolder.xbm"
#include "BuildingBlock.xbm"
#include "GDBoundaryShape.xbm"
#include "GDControllerShape.xbm"
#include "GDEntityShape.xbm"

NodeShapeDialog::NodeShapeDialog(Widget w): 
		NToggleListDialog(w, False) { 
	SetAutoUnmanage(False);
}

void NodeShapeDialog::Configure() {
	NToggleListDialog::Configure();
	List<string *> labels;
	labels.add(new string("Target Node Shape"));
	List<List<string *> *> items;
	List<string *> l;
        l.add(new string("Box"));
        l.add(new string("Circle"));
        l.add(new string("RoundedBox"));
        l.add(new string("Triangle"));
        l.add(new string("BullsEye"));
        l.add(new string("StickMan"));
        l.add(new string("Cube"));
        l.add(new string("GDBoundaryShape"));
        l.add(new string("TextBox"));
	l.add(new string("Diamond"));
        l.add(new string("Square"));
        l.add(new string("VerticalBar"));
        l.add(new string("Hexagon"));
        l.add(new string("SolidVerticalBar"));
        l.add(new string("Folder"));
        l.add(new string("BuildingBlock"));
        l.add(new string("GDControllerShape"));
        l.add(new string("NoteBox"));
	l.add(new string("Ellipse"));
        l.add(new string("BlackDot"));
        l.add(new string("HorizontalBar"));
        l.add(new string("EllipsedBox"));
        l.add(new string("SolidHorizontalBar"));
        l.add(new string("SubFolder"));
        l.add(new string("Disk"));
        l.add(new string("GDEntityShape"));
	items.add(&l);
	CreateToggleLists(&labels, &items);
	labels.clear();
	l.clear();
	ManageHelpButton(True);
	SetHelpButtonLabel("Default");
	Bitmap icon0 = {Box_width, Box_height, Box_bits};
	Bitmap icon1 = {Circle_width, Circle_height, Circle_bits};
	Bitmap icon2 = {RoundedBox_width, RoundedBox_height, RoundedBox_bits};
	Bitmap icon3 = {Triangle_width, Triangle_height, Triangle_bits};
	Bitmap icon4 = {BullsEye_width, BullsEye_height, BullsEye_bits};
	Bitmap icon5 = {StickMan_width, StickMan_height, StickMan_bits};
	Bitmap icon6 = {Cube_width, Cube_height, Cube_bits};
	Bitmap icon7 = {GDBoundaryShape_width, GDBoundaryShape_height, 
						GDBoundaryShape_bits};
	Bitmap icon8 = {Comment_width, Comment_height, Comment_bits};

	Bitmap icon9 = {Diamond_width, Diamond_height, Diamond_bits};
	Bitmap icon10 = {Square_width, Square_height, Square_bits};
	Bitmap icon11 = {VerticalBar_width, VerticalBar_height, VerticalBar_bits};
	Bitmap icon12 = {Hexagon_width, Hexagon_height, Hexagon_bits};
	Bitmap icon13 = {SolidVerticalBar_width, SolidVerticalBar_height,
          		SolidVerticalBar_bits};
	Bitmap icon14 = {Folder_width, Folder_height, Folder_bits};
	Bitmap icon15 = {BuildingBlock_width, BuildingBlock_height, BuildingBlock_bits};
	Bitmap icon16 = {GDControllerShape_width, GDControllerShape_height,
				GDControllerShape_bits};
	Bitmap icon17 = {NoteBox_width, NoteBox_height, NoteBox_bits};

	Bitmap icon18 = {Ellipse_width, Ellipse_height, Ellipse_bits};
	Bitmap icon19 = {BlackDot_width, BlackDot_height, BlackDot_bits};
	Bitmap icon20 = {HorizontalBar_width, HorizontalBar_height, 
			HorizontalBar_bits};
	Bitmap icon21 = {EllipsedBox_width, EllipsedBox_height, EllipsedBox_bits};
	Bitmap icon22 = {SolidHorizontalBar_width, SolidHorizontalBar_height,
          		SolidHorizontalBar_bits};
	Bitmap icon23 = {SubFolder_width, SubFolder_height, SubFolder_bits};
	Bitmap icon24 = {Disk_width, Disk_height, Disk_bits};
	Bitmap icon25 = {GDEntityShape_width, GDEntityShape_height,
				GDEntityShape_bits};

	SetItemBitmap(0, 0, &icon0);
	SetItemBitmap(0, 1, &icon1);
	SetItemBitmap(0, 2, &icon2);
	SetItemBitmap(0, 3, &icon3);
	SetItemBitmap(0, 4, &icon4);
	SetItemBitmap(0, 5, &icon5);
	SetItemBitmap(0, 6, &icon6);
	SetItemBitmap(0, 7, &icon7);
	SetItemBitmap(0, 8, &icon8);
	SetItemBitmap(0, 9, &icon9);
	SetItemBitmap(0, 10, &icon10);
	SetItemBitmap(0, 11, &icon11);
	SetItemBitmap(0, 12, &icon12);
	SetItemBitmap(0, 13, &icon13);
	SetItemBitmap(0, 14, &icon14);
	SetItemBitmap(0, 15, &icon15);
	SetItemBitmap(0, 16, &icon16);
	SetItemBitmap(0, 17, &icon17);
	SetItemBitmap(0, 18, &icon18);
	SetItemBitmap(0, 19, &icon19);
	SetItemBitmap(0, 20, &icon20);
	SetItemBitmap(0, 21, &icon21);
	SetItemBitmap(0, 22, &icon22);
	SetItemBitmap(0, 23, &icon23);
	SetItemBitmap(0, 24, &icon24);
	SetItemBitmap(0, 25, &icon25);

	List<Widget> *tl = (*GetToggleList())[0];
	Widget rc = XtParent((*tl)[0]);
	AddLiteClue((*tl)[0], "Box");
	AddLiteClue((*tl)[1], "Circle");
	AddLiteClue((*tl)[2], "Rounded box");
	AddLiteClue((*tl)[3], "Triangle");
	AddLiteClue((*tl)[4], "Bull's eye");
	AddLiteClue((*tl)[5], "Stick man");
	AddLiteClue((*tl)[6], "Cube");
	AddLiteClue((*tl)[7], "Boundary class");
	AddLiteClue((*tl)[8], "Text box");

	AddLiteClue((*tl)[9], "Diamond");
	AddLiteClue((*tl)[10], "Square");
	AddLiteClue((*tl)[11], "Vertical bar");
	AddLiteClue((*tl)[12], "Hexagon");
	AddLiteClue((*tl)[13], "Solid vertical bar");
	AddLiteClue((*tl)[14], "Folder");
	AddLiteClue((*tl)[15], "Building block");
	AddLiteClue((*tl)[16], "Controller class");
	AddLiteClue((*tl)[17], "Note box");

	AddLiteClue((*tl)[18], "Ellipse");
	AddLiteClue((*tl)[19], "Black dot");
	AddLiteClue((*tl)[20], "Horizontal bar");
	AddLiteClue((*tl)[21], "Ellipsed box");
	AddLiteClue((*tl)[22], "Solid horizontal bar");
	AddLiteClue((*tl)[23], "Subfolder");
	AddLiteClue((*tl)[24], "Disk");
	AddLiteClue((*tl)[25], "Entity class");
	XtVaSetValues(rc, XmNnumColumns, 3, 
			  XmNorientation, XmVERTICAL, 0);
}
