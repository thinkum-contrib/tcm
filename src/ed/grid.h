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
#ifndef _GRID_H
#define _GRID_H

#include "point.h"
#include "util.h"
class DrawWindow;
class Config;
class Viewer;
class ScaleDialog;

/// class for showing the grid and snapping points to discrete point positions.
class Grid {
/*@Doc: {\large {\bf scope:} editor} */
public:
	///
	Grid(Config *c, DrawWindow *d, Viewer *v);
	///
	virtual ~Grid();

	/// set snapping to continuous or discrete.
	void SetSnap(bool set); 

	/// make popup for asking the point distance.
	void PointDistance();

	/// make popup for asking the grid size.
	void GridSize();	

	/// set showing of grid.
	void SetShowGrid(bool set); 

	///
	bool IsShowGrid() const { return showGrid; }

	/// Snap point to point-position.
	void Snap(Point *); 	

	/// Snap int to point-position.
	int Snap(int); 		

	/// draw grid.
	void DrawGrid();	

	/// set point distance to i.
	void SetPointDistance(int i); 	
	/// set grid size to i.
	void SetGridSize(int i); 	

	///
	DrawWindow *GetMainWindow() const {return mainwindow;}
	///
	Config *GetConfig() const {return config;}
	///
	ScaleDialog *GetScaleDialog() const {return scaleDialog;}
private:
	///
	DrawWindow *mainwindow;
	///
	Viewer *viewer;
	///
	Config *config;
	///
	ScaleDialog *scaleDialog;

	///
	int pointDistance;
	///
	bool snap;
	///
	bool showGrid;
	///
	int gridSize;
	///
	int defaultPointDistance;
	///
	int defaultGridSize;

	///
	static const int MAX_POINT_DISTANCE;
	///
	static const int MIN_POINT_DISTANCE;
	///
	static const int MAX_GRID_SIZE;
	///
	static const int MIN_GRID_SIZE;
};
#endif
