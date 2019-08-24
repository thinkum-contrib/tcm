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

#include "ssdupdateclassboxtypecmd.h"
#include "ssdsingleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdtripleclassbox.h"
#include "ssdsingleobjectbox.h"
#include "ssddoubleobjectbox.h"

SSDUpdateClassBoxTypeCmd::SSDUpdateClassBoxTypeCmd(
	ShapeView *v, List<int *> *l, int n): UpdateNodeShapeTypeCmd(v, l, n) {
	TransformAll();
}

Thing *SSDUpdateClassBoxTypeCmd::Transform(Thing *thing) {
        Box *oldShape = (Box *)thing;
	int fromType = oldShape->GetClassType();
	if (toType == Code::SSD_SINGLE_CLASS_BOX) {
		int twidth, theight;
		oldShape->GetName()->TextBox(twidth, theight);
		oldShape->UpdateSize(max(SSDSingleClassBox::BOX_WIDTH, twidth), 
				  max(SSDSingleClassBox::BOX_HEIGHT, theight));
		if (fromType == Code::SSD_DOUBLE_CLASS_BOX)
                	return new SSDSingleClassBox(*(SSDDoubleClassBox *)oldShape);
		else if (fromType == Code::SSD_TRIPLE_CLASS_BOX)
                	return new SSDSingleClassBox(*(SSDTripleClassBox *)oldShape);
		else
                	return new SSDSingleClassBox(*(SSDSingleClassBox *)oldShape);
	}
        else if (toType == Code::SSD_DOUBLE_CLASS_BOX) {
		if (fromType == Code::SSD_SINGLE_CLASS_BOX)
                	return new SSDDoubleClassBox(*(SSDSingleClassBox *)oldShape);
		else if (fromType == Code::SSD_TRIPLE_CLASS_BOX)
                	return new SSDDoubleClassBox(*(SSDTripleClassBox *)oldShape);
		else 
                	return new SSDDoubleClassBox(*(SSDDoubleClassBox *)oldShape);
	}
        else if (toType == Code::SSD_TRIPLE_CLASS_BOX) {
		if (fromType == Code::SSD_SINGLE_CLASS_BOX)
                	return new SSDTripleClassBox(*(SSDSingleClassBox *)oldShape);
		else if (fromType == Code::SSD_DOUBLE_CLASS_BOX)
                	return new SSDTripleClassBox(*(SSDDoubleClassBox *)oldShape);
		else 
                	return new SSDTripleClassBox(*(SSDTripleClassBox *)oldShape);
	}
        else if (toType == Code::SSD_SINGLE_OBJECT_BOX) {
		int twidth, theight;
                oldShape->GetName()->TextBox(twidth, theight);
                oldShape->UpdateSize(max(Box::BOX_WIDTH, twidth),
                                  max(Box::BOX_HEIGHT, theight));
                return new SSDSingleObjectBox(*oldShape);
	}
        else if (toType == Code::SSD_DOUBLE_OBJECT_BOX) {
                return new SSDDoubleObjectBox(*oldShape);
	}
        else {
                error("%s, %d: cannot convert class box type %d\n",
                	__FILE__, __LINE__, oldShape->GetClassType());
                return 0;
        }
}
