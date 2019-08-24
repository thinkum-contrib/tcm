//------------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
#ifndef _DIAGRAMWINDOW_H
#define _DIAGRAMWINDOW_H

#include "bitmap.h"
#include "drawwindow.h"
#include "drawingarea.h"
class DiagramViewer;
class Diagram;
class Graph;

/// edit window class that is common to all diagram editors.
class DiagramWindow: public DrawWindow {
/*@Doc: {\large {\bf scope:} diagram} */
public:
	///
	DiagramWindow(const char *name);
	///
	virtual ~DiagramWindow();

	/// Show in status that node type n is selected.
	void SetNodeName(int n);

	/// Show in status that edge type n is selected.
	void SetEdgeName(int n);

	/// set hierarchic document toggle.
	virtual void SetHierarchic(bool s);
protected:
	/// points to the names of the node shapes. 
	const char** nodeNames; 
	/// points to the names of the edge shapes. 
	const char** edgeNames; 
	///
	int nrNodes;
	///
	int nrEdges;
 
	/// List of Icons for the "Nodes" tiled buttons.
	const Bitmap *nodeIcons; 
	/// List of Icons for the "Edges" tiled buttons.
	const Bitmap *edgeIcons; 

	/// create menu bar
	Widget CreateMenuBar(Widget parent);

	/// created tiled buttons.
	virtual Widget CreateTiles(Widget parent);

	///
	void CreateNodeIcons(Widget parent);
	///
	void CreateEdgeIcons(Widget parent);
	///
	void CreateIndexToggle(Widget parent);

	///
	DiagramViewer *GetDiagramViewer() const {return viewer;}

	///
	void SetShowLineStyleOptionMenu(bool b) {
		showLineStyleOptionMenu = b;}
	///
	Widget GetNodeIconsRC() const {return nodeIconsRC;}
	///
	Widget GetEdgeIconsRC() const {return edgeIconsRC;}
	///
	void CreateLineStyleOptionMenu(Widget w, bool nodes, bool minimize);

	///
	void InitMenuItems();
private:
	///
	DiagramViewer *viewer;

	/// parse the command line options.
	void ParseUserOptions(int argc, char** argv);

	///
	void WriteUsage(const char *prog);
 
	/// initialize window: create menubar, tiles, scrolled window, etc
	void CreateComponents(Widget window);

	///
	virtual Menu *BuildViewMenu(Widget bar);

	/// Motif RowColumn widget containing tiled buttons.
	Widget tiles;

	///
	void Finalize();
	///
	void CreateDocument();
	///
	virtual DiagramViewer *CreateViewer(Config *c) = 0;
	///
	virtual Graph *CreateGraph() = 0;
	///
	virtual Diagram *CreateDiagram(
		Config *c, DiagramViewer *v, Graph *g) = 0;

	/// Determine icon lists to be used for the window.
	virtual void DetermineIcons() = 0;

	///
	void GetNodeName(int i, string *name);
	///
	void GetEdgeName(int i, string *name);

	///
	static const Bitmap CURVE_ICON;
	///
	static const Bitmap SOLID_LINE_ICON;
	///
	static const Bitmap DASHED_LINE_ICON;
	///
	static const Bitmap DOTTED_LINE_ICON;

	///
	Widget edgeIconsRC;
	///
	Widget nodeIconsRC;
	///
	int iconColumns;
	///
	bool showLineStyleOptionMenu;
protected:
	///
	virtual bool ShowIndexToggle() {return False;}
	///
	void CalcIconColumns();
	///
	int GetIconsScrollHeight(int rows);
	///
	Menu *gridMenu;
	///
	MenuItem *diagramAlignItems;
	///
	MenuItem *defPropertiesItems;
	///
	MenuItem *gridItems;
	///
	MenuItem *nodeLineStyleItems;
	///
	MenuItem *edgeLineStyleItems;
	///
	MenuItem *updateNodeShapeTypeItems;
};
#endif
