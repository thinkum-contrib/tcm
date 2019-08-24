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
#include "appendtablecmd.h"
#include "tableviewer.h"
#include "table.h"
#include "addrowscmd.h"
#include "addcolumnscmd.h"
#include "inputfile.h"
 
AppendTableCmd::AppendTableCmd(Table *t, TableViewer *v): Command(t, v) {
	command1 = 0;
	command2 = 0;
	v->DeselectAll();
	double loadFormat = t->GetLoadFormat();
	InputFile *ifile = t->GetInputFile();
	unsigned rows, columns;
	if (!v->ReadAttributes(ifile, True, rows, columns, loadFormat))
		return;
	unsigned trows = v->GetNumberOfRows();
	unsigned tcolumns = v->GetNumberOfColumns();
	if (t->IsAppendBottom()) {
		command1 = new AddRowsCmd(t, v, rows, trows);
		command1->Execute();
		((TableViewer *)GetViewer())->SetVisible(False);
		if (tcolumns < columns) {
			command2 = new AddColumnsCmd(t, v, 
						columns - tcolumns, tcolumns);
			command2->Execute();
		}
		if (loadFormat >= 1.09) {
			if (v->ReadRows(ifile, rows, trows, 0, loadFormat))
				v->ReadColumns(ifile, columns, trows, 0, 
						loadFormat);
		}
		else {
			if (v->ReadColumns(ifile, columns, trows, 0, 
					   loadFormat))
				v->ReadRows(ifile, rows, trows, 0, loadFormat);
		}
	}
	else {  // append to right of the table.
		command1 = new AddColumnsCmd(t, v, columns, tcolumns);
		command1->Execute();
		if (trows < rows) {
			command2 = new AddRowsCmd(t, v, rows - trows, trows);
			command2->Execute();
		}
		((TableViewer *)GetViewer())->SetVisible(False);
		if (loadFormat >= 1.09) {
			if (v->ReadRows(ifile, rows, 0, tcolumns, loadFormat))
				v->ReadColumns(ifile, columns, 0, tcolumns, 
						loadFormat);
		}
		else {
			if (v->ReadColumns(ifile, columns, 0, tcolumns, 
						loadFormat))
				v->ReadRows(ifile, rows, 0, tcolumns, 
						loadFormat);
		}
	}
	((TableViewer *)GetViewer())->SetVisible(True);
}

AppendTableCmd::~AppendTableCmd() {
	if (command1)
		delete command1;
	if (command2)
		delete command2;
}

void AppendTableCmd::Execute() {
	Command::Execute();
	GetViewer()->Refresh();
}

void AppendTableCmd::ReExecute() {
	if (command1)
		command1->Execute();
	if (command2)
		command2->Execute();
	Command::Execute();
	GetViewer()->Refresh();
}

void AppendTableCmd::UnExecute() {
	if (command2)
		command2->UnExecute();
	if (command1)
		command1->UnExecute();
	Command::UnExecute();
	GetViewer()->Refresh();
}
