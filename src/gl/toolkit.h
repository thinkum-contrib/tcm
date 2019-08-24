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
//------------------------------------------------------------------------------
#ifndef _TOOLKIT_H
#define _TOOLKIT_H

#include "bool.h"

/// information about the different tools.
class Toolkit {
/*@Doc: {\large {\bf scope:} editor} */
public:
	/// The application (toolkit) name.
	static const char TOOLKIT_NAME[];

	// Note: the order of the values is important for the lists of titles,
	// document types and sufixes !!!
	/// Definitions of the different editors (tools) that are implemented.
	enum ToolType {
	// GD = Generic Diagrams
		GD,
	// ERD = Entity Relationship Diagram (Classic).
		ERD, 
	// CRD = Class Relationship Diagram.
		CRD, 
	// STD = State Transition Diagram (Mealy).
		STD, 
	// PSD = Process Structure Diagram (JSD).
		PSD, 
	// RPG = Recursive Process Graph.
		RPG, 
	// DFD = Dataflow Diagram (Classic).
		DFD, 
	// EFD = Data and Event Flow Diagram (was Data and Control F.D. resp. DEFD).
		EFD,
	// SND = System Network Diagram (JSD).
		SND,
	// GT = Generic Tables
		GT,
	// TDT = Transaction decomposition table.
		TDT, 
	// TUT = Transaction use table.
		TUT, 
	// FET = Function entity-type table.
		FET, 
	// GTT = Generic Textual Trees
		GTT,
	// FDT = Function Refinement Tree (was Function Decomposition Tree).
		FDT,
	// T = Text
		T,
	// CSOD = COLOR-X Static Object Diagram.
		CSOD, 
	// CED = COLOR-X Static Object Diagram.
		CED,
	// SSD = Static Structure Diagram.
                SSD,
	// CBD = Collaboration Diagram.
		CBD,
	// SQD = Sequence Diagram.
		SQD,
	// CPD = Component Diagram.
		CPD,
	// DPD = Deployment Diagram.
		DPD,
	// UCD = Use Case Diagram.
		UCD,
	// SCD = Statechart Diagram.
		SCD,
	// ATD = Activity Diagram.
		ATD,
	// ESD = Static Structure Diagram (ERD subset).
                ESD };

	/// is tool table editor.
	static bool TableEditor(int tool);

	/// is tool diagram editor.
	static bool DiagramEditor(int tool);

	/// is tool tree editor.
	static bool TreeEditor(int tool);

	/// is tool text editor.
	static bool TextEditor(int tool);

	/// tool can not have curved edges.
	static bool EditorWithoutCurves(int tool);

	/// tool can not have duplicate shapes.
	static bool EditorWithoutDuplicates(int tool);

	/// tool can edit hierarchic documents.
	static bool HierarchicEditor(int tool);

	/// tool has no soft constraints
	static bool GenericEditor(int tool);

	/// tool is diagram editor in which edges can connect to edges
	static bool EditorWithInterEdgeConnections(int tool);

	/// tool is diagram editor with model checking facilities
        static bool EditorWithModelChecker(int tool);

	/// The name (in upper case) of the startup tool.
	static const char STARTUP_TOOL_NAME[];

	/// Window titles for the different tools.
	static const char* TOOL_TITLES[];

	/// Short names (in upper case) of the editing tools.
	static const char* TOOL_NAMES[];

	/// Names of the tool executables.
	static const char* EXECUTABLE_NAMES[];

	/// The full names of the document types.
	static const char* DOCUMENT_TYPES[];

	/// Document name suffixes.
	static const char* DOCUMENT_SUFFIXES[];

	/// Default document name.
	static const char DOCUMENT_DEFAULT[];

	/// The help info of the document types.
	static const char* DOCUMENT_TYPES_INFO[];
};
#endif
