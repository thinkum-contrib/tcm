////////////////////////////////////////////////////////////////////////////////
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1996, Vrije Universiteit Amsterdam.
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
#include "snwindow.h"
#include "sndiagram.h"
#include "snviewer.h"
#include "sngraph.h"

// X bitmap data for the tiled buttons
#include "Box.xbm"
#include "StartC1Line.xbm"
#include "EndC1Arrow.xbm"
#include "Comment.xbm"
#include "MediumCircle.xbm"
#include "MediumLeftLineCircle.xbm"
#include "MediumDiamond.xbm"
 
const char *SNWindow::SN_NODE_NAMES[] = {"Process", "Data stream", "State vector", 
		"Controlled data stream", "Comment"};
const Bitmap SNWindow::SN_NODE_ICONS[] =
	{{Box_width, Box_height, Box_bits},
	 {MediumCircle_width, MediumCircle_height, MediumCircle_bits},
	 {MediumDiamond_width, MediumDiamond_height, MediumDiamond_bits},
	 {MediumLeftLineCircle_width, MediumLeftLineCircle_height, 
	  MediumLeftLineCircle_bits},
	 {Comment_width, Comment_height, Comment_bits}};

const char *SNWindow::SN_EDGE_NAMES[] = {"Start connection", "End connection"};
const Bitmap SNWindow::SN_EDGE_ICONS [] = 
	{{StartC1Line_width, StartC1Line_height, StartC1Line_bits},
	 {EndC1Arrow_width, EndC1Arrow_height, EndC1Arrow_bits}};


SNWindow::SNWindow(const char *n): DiagramWindow(n) {}

DiagramViewer *SNWindow::CreateViewer(Config *cfg) {
	return new SNViewer(cfg, this);
}

Graph *SNWindow::CreateGraph() {
	return new SNGraph();
}

Diagram *SNWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new SNDiagram(c, this, (SNViewer *)v, (SNGraph *)g);
}

void SNWindow::DetermineIcons() {
	 nodeNames = SN_NODE_NAMES;
	 nodeIcons = SN_NODE_ICONS;
	 edgeNames = SN_EDGE_NAMES;
	 edgeIcons = SN_EDGE_ICONS;
	 nrNodes = XtNumber(SN_NODE_NAMES);
	 nrEdges = XtNumber(SN_EDGE_NAMES);
}
