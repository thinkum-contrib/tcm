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
#include "fdwindow.h"
#include "fddiagram.h"
#include "fdviewer.h"
#include "fdgraph.h"

#include "TextNode.xbm"
#include "TextRoot.xbm"
#include "Comment.xbm"
#include "EmptyLine.xbm"
 
const char *FDWindow::FD_NODE_NAMES[] = {"Text root", "Text node", "Comment" };

const Bitmap FDWindow::FD_NODE_ICONS [] =
 { {TextRoot_width, TextRoot_height, TextRoot_bits},
   {TextNode_width, TextNode_height, TextNode_bits},
   {Comment_width, Comment_height, Comment_bits}};

const char *FDWindow::FD_EDGE_NAMES[] = {"Line"};
const Bitmap FDWindow::FD_EDGE_ICONS [] =
	{{EmptyLine_width, EmptyLine_height, EmptyLine_bits}};

FDWindow::FDWindow(const char *n): TRWindow(n) {}

DiagramViewer *FDWindow::CreateViewer(Config *cfg) {
	return new FDViewer(cfg, this);
}

Graph *FDWindow::CreateGraph() {
	return new FDGraph();
}

Diagram *FDWindow::CreateDiagram(Config *c, DiagramViewer *v, Graph *g) {
	 return new FDDiagram(c, this, (FDViewer *)v, (FDGraph *)g);
}

void FDWindow::DetermineIcons() {
	 nodeNames = FD_NODE_NAMES;
	 nodeIcons = FD_NODE_ICONS;
	 edgeNames = FD_EDGE_NAMES;
	 edgeIcons = FD_EDGE_ICONS;
	 nrNodes = XtNumber(FD_NODE_NAMES);
	 nrEdges = XtNumber(FD_EDGE_NAMES);
}
