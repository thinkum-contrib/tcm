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
#include "ssdsingleclassbox.h"
#include "ssddoubleclassbox.h"
#include "ssdtripleclassbox.h"
#include "diagramviewer.h"
#include "diagram.h"
#include "ssdupdateclassboxpropertycmd.h"

SSDUpdateClassBoxPropertyCmd::SSDUpdateClassBoxPropertyCmd(
		ShapeView *v, PropertyType p, bool b): 
		Command(v->GetViewer()->GetDiagram(), v->GetViewer()) {
	view = v;
	property = p;
	set = b;
	shapes = new List<GShape *>;
	List<GShape *> *selection = view->GetSelection();
	for (selection->first(); !selection->done(); selection->next()) {
		GShape *shape = selection->cur();
		if (shape->GetClassType()==Code::SSD_SINGLE_CLASS_BOX) {
			SSDSingleClassBox *sbs = (SSDSingleClassBox *)shape;
			if ((property == STEREOTYPE && 
			    sbs->IsShowStereotype() != set) ||
			    (property == PROPERTIES && 
			    sbs->IsShowProperties() != set))
				shapes->add(shape);
		}
		else if (shape->GetClassType()==Code::SSD_DOUBLE_CLASS_BOX) {
			SSDDoubleClassBox *dbs = (SSDDoubleClassBox *)shape;
			if ((property == STEREOTYPE && 
			    dbs->IsShowStereotype() != set) ||
			    (property == PROPERTIES && 
			    dbs->IsShowProperties() != set))
				shapes->add(shape);
		}
		else if (shape->GetClassType()==Code::SSD_TRIPLE_CLASS_BOX) {
			SSDTripleClassBox *tbs = (SSDTripleClassBox *)shape;
			if ((property == STEREOTYPE && 
			    tbs->IsShowStereotype() != set) ||
			    (property == PROPERTIES && 
			    tbs->IsShowProperties() != set))
				shapes->add(shape);
		}
	}
}

SSDUpdateClassBoxPropertyCmd::~SSDUpdateClassBoxPropertyCmd() {
	delete shapes;
}

void SSDUpdateClassBoxPropertyCmd::Execute() {
	if (!shapes->first()) {
		GetMainWindow()->SetStatus(
			"aborted: no shapes need to be updated");
		Abort();
		return;
	}
	ChangeProperties();
	Command::Execute();
}

void SSDUpdateClassBoxPropertyCmd::UnExecute() {
	set = !set;
	ChangeProperties();
	set = !set;
	Command::UnExecute();
}

void SSDUpdateClassBoxPropertyCmd::ChangeProperties() {
	for (shapes->first(); !shapes->done(); shapes->next()) {
		GShape *shape = shapes->cur();
		if (shape->GetClassType()==Code::SSD_SINGLE_CLASS_BOX) {
			if (property == STEREOTYPE)
				((SSDSingleClassBox *)shape)->UpdateShowStereotype(set);
			else if (property == PROPERTIES)
				((SSDSingleClassBox *)shape)->UpdateShowProperties(set);
		}
		else if (shape->GetClassType()==Code::SSD_DOUBLE_CLASS_BOX) {
			if (property == STEREOTYPE)
				((SSDDoubleClassBox *)shape)->UpdateShowStereotype(set);
			else if (property == PROPERTIES)
				((SSDDoubleClassBox *)shape)->UpdateShowProperties(set);
		}
		else if (shape->GetClassType()==Code::SSD_TRIPLE_CLASS_BOX) {
			if (property == STEREOTYPE)
				((SSDTripleClassBox *)shape)->UpdateShowStereotype(set);
			else if (property == PROPERTIES)
				((SSDTripleClassBox *)shape)->UpdateShowProperties(set);
		}
	}
}
