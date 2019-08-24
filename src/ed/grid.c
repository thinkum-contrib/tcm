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
#include "grafport.h"
#include "scaledialog.h"
#include "editstubs.h"
#include "viewer.h"
#include "config.h"
#include "grid.h"

const int Grid::MAX_POINT_DISTANCE = 50;
const int Grid::MIN_POINT_DISTANCE = 1;
const int Grid::MAX_GRID_SIZE = 50;
const int Grid::MIN_GRID_SIZE = 10;

Grid::Grid(Config *c, DrawWindow *d, Viewer *v) {
	mainwindow = d;
	viewer = v;
	config = c;
	SetPointDistance(config->GetPointDistance());
	snap = config->GetPointSnapping();
	showGrid = config->GetShowGrid();
	gridSize = min(MAX_GRID_SIZE, max(MIN_GRID_SIZE, config->GetGridSize()));
	defaultPointDistance = pointDistance;
	defaultGridSize = gridSize;
	scaleDialog = new ScaleDialog(d->GetWidget());
	scaleDialog->Initialize();
}

Grid::~Grid() {
	delete scaleDialog;
}

void Grid::SetSnap(bool s) {
	string txt = "point position is ";
	if (s)
		txt += "discrete";
	else
		txt += "continuous";
	mainwindow->SetStatus(&txt);
	snap = s;
}

void Grid::PointDistance() {
	mainwindow->SetStatus("action: point distance");
	scaleDialog->SetTitle("Point distance");
	scaleDialog->SetScaleLabel("Point distance (in pixels)");
	scaleDialog->SetValueChangedCallback(
		EditStubs::PointDistanceOKCB, this);
	scaleDialog->SetScaleValues(MIN_POINT_DISTANCE, MAX_POINT_DISTANCE, 
		pointDistance, 0, defaultPointDistance);
	scaleDialog->Popup();
}

void Grid::SetPointDistance(int n) {
	pointDistance = min(MAX_POINT_DISTANCE, max(MIN_POINT_DISTANCE, n));
	string txt = "point distance set to ";
	txt += pointDistance;
	mainwindow->SetStatus(&txt);
}

void Grid::SetShowGrid(bool set) {
	string txt = "grid is ";
	if (set)
		txt += "visible";
	else
		txt += "invisible";
	mainwindow->SetStatus(&txt);
	// if no change then don't draw.
	if (showGrid == set)
		return;
	showGrid = set;
	DrawGrid();
}

void Grid::GridSize() {
	mainwindow->SetStatus("action: grid size");
	scaleDialog->SetTitle("Grid size");
	scaleDialog->SetScaleLabel("Grid size (in pixels)");
	scaleDialog->SetValueChangedCallback(EditStubs::GridSizeOKCB, this);
	scaleDialog->SetScaleValues(MIN_GRID_SIZE, MAX_GRID_SIZE, 
		gridSize, 0, defaultGridSize);
	scaleDialog->Popup();
}

void Grid::SetGridSize(int n) {
	string txt = "grid size set to ";
	txt += n;
	mainwindow->SetStatus(&txt);
	// if no change then do nothing.
	if (gridSize == n)
		return;
	if (showGrid) {
		// undraw old.
		DrawGrid();
		gridSize = n;
		gridSize = min(MAX_GRID_SIZE, max(MIN_GRID_SIZE, n));
		// draw new.
		DrawGrid();
	}
	else
		gridSize = min(MAX_GRID_SIZE, max(MIN_GRID_SIZE, n));
}

void Grid::Snap(Point *pt) {
	pt->x = Snap(pt->x);
	pt->y = Snap(pt->y);
}

int Grid::Snap(int x) {
	if (snap) {
		int save = x;
		x = (x / pointDistance) * pointDistance;
		int rest = (save % pointDistance) * 2;
		if ( rest >= pointDistance)
			x = x + pointDistance;
	}
	return x;
}

void Grid::DrawGrid() {
	Grafport *grafport = viewer->GetGrafport();
	if (!check(grafport))
		return;
	int width = int(0.5 + grafport->GetWidth());
	int height = int(0.5 + grafport->GetHeight());
	int n_x = width / gridSize;
	int n_y = height / gridSize;
	int i;
	for(i=0; i<=n_x; i++) {
		int x = i * gridSize;
		grafport->DrawEditDottedGridLine(x, 0, x, height-1);
	}
	for(i=0; i<=n_y; i++) {
		int y = i * gridSize;
		grafport->DrawEditDottedGridLine(0, y, width-1, y);
	}
}
