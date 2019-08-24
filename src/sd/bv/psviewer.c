////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1995, Vrije Universiteit Amsterdam.
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
#include "psviewer.h"
#include "psdiagram.h"
#include "urlabeledbox.h"
#include "psprocess.h"
#include "lstring.h"
#include "pswindow.h"

PSViewer::PSViewer(Config *c, PSWindow *d): DiagramViewer(c, d) {
	showSequence = 0;
}

void PSViewer::SetShowSequences(int set) {
	SetStatus("action: Show sequences");
	if (set == 0 && showSequence != 0) {
		UpdateSequenceLabels(set);
	}
	else if ((set == 1 || set == 2)) {
		((PSDiagram *)GetDiagram())->TraverseTree(False);
		UpdateSequenceLabels(set);
	}
	showSequence = set;
}

void PSViewer::UpdateSequenceLabels(int set) {
	List<GShape *> *shapes = GetCurView()->GetShapes();
	string s;
	if (set == 0) {
		s = "";
		for (shapes->first(); !shapes->done(); shapes->next()) {
			Shape *shape = shapes->cur();
			if (shape->GetClassType() == Code::UR_LABELED_BOX) {
				URLabeledBox *urbox = (URLabeledBox *)shape;
				urbox->UpdateIndexLabel(&s);
			}
		}
	}
	else {
		for (shapes->first(); !shapes->done(); shapes->next()) {
			Shape *shape = shapes->cur();
			if (shape->GetClassType() == Code::UR_LABELED_BOX) {
				PSProcess *process = 
					(PSProcess *)shape->GetSubject();
				int sequence = 0;
				if (set == 1)
					sequence = process->GetActionSequence();
				else if (set == 2)
					sequence = process->GetTreeSequence();

				if (sequence != 0)
					s = sequence;
				else
					s = "";
				URLabeledBox *urbox = (URLabeledBox *)shape;
				urbox->UpdateIndexLabel(&s);
			}
		}
	}
}
