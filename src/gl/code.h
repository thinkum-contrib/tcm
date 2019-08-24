//------------------------------------------------------------------------------
//
// This file is part of Toolkit for Conceptual Modeling (TCM).
// (c) copyright 1997, Vrije Universiteit Amsterdam.
// Author: Frank Dehne (frank@cs.vu.nl).
//
// TCM is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published
// by
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
#ifndef _CODE_H
#define _CODE_H
#include "typename.h"


// This include file contains all codes of all types of subjects (nodes and
// edges) and of all types of shapes.
 
/// Functions and constants for shape and subject codes.
class Code {
/*@Doc: {\large {\bf scope:} global} */
public:
	///
	enum Type {
		// general node shape types
		BOX=1,
		SQUARE,
		DOUBLE_BOX,
		TRIPLE_BOX,
		UR_LABELED_BOX,
		ARROW_BOX,
		TEXT_BOX,
		ARROW_TEXT_BOX,
		ELLIPSE,
		CIRCLE,	
		BLACK_DOT,
		WHITE_DOT,
		ELLIPSIS,
		BULLS_EYE,
		MINI_ARROW_ELLIPSE,
		LEFT_LINE_CIRCLE,
		ROUNDED_BOX,
		ELLIPSED_BOX,
		DIAMOND,
		HORIZONTAL_BAR,
		VERTICAL_BAR,
		TRIANGLE,	
		HEXAGON,
		MINI_BOX,
		MINI_DIAMOND,
		MINI_ELLIPSE,
		MINI_TRIANGLE,
		NOTE_BOX,
		SOLID_HORIZONTAL_BAR,
		SOLID_VERTICAL_BAR,
		STICKMAN,
		BUILDING_BLOCK,
		CUBE,
		FOLDER,
		SUB_FOLDER,
		DISK,

		// general line types.
		LINE=100,		
		FLASH_ARROW,
		T1_LINE,
		T2_LINE,
		T4_LINE,
		T4_TLIST_LINE,
		TRANSITION_ARROW,
		C2R2_LINE,
		C2R2_MLIST_LINE,
		// next 4 are for backwards compatibility
		ARROW,
		T1_ARROW,
		DOUBLE_ARROW,
		DOUBLE_HEADED_ARROW,

		// standard node types.
		COMMENT=200,	
		GENERIC_NODE,
		NOTE,
		EMPTY_NODE,
		ENTITY_TYPE,
		VALUE_TYPE,
		TAXONOMY_JUNCTION,
		RELATIONSHIP_NODE,
		SUBJECT_AREA,
		CLASS_NODE,
		MODE_JUNCTION,
		DATA_PROCESS,	
		DATA_STORE,
		EVENT_STORE,
		EXTERNAL_ENTITY,
		SPLIT_MERGE_NODE,
		CONTROL_PROCESS,
		PS_PROCESS,
		DATA_STREAM,
		STATE_VECTOR,
		CONTROLLED_DATA_STREAM,
		SN_PROCESS,	
		STATE,
		INITIAL_STATE,
		DECISION_POINT,
		PROCESS_GRAPH_NODE,
		PROCESS_GRAPH_ROOT,
		TEXT_ROOT,
		TEXT_NODE,
		FINAL_STATE,

		// standard edge types
		GENERIC_EDGE=300,
		COMMENT_LINK,
		EMPTY_EDGE,
		TEXT_EDGE,
		BINARY_RELATIONSHIP,
		FUNCTION,
		ISA_RELATIONSHIP,
		COMPONENT_FUNCTION,
		DATA_FLOW,
		BIDIRECTIONAL_DATA_FLOW,
		CONTINUOUS_DATA_FLOW,
		EVENT_FLOW,
		CONTINUOUS_EVENT_FLOW,
		CONNECTION_START,
		CONNECTION_END,	
		TRANSITION,
		EVENT,

		// UML nodes
		SSD_CLASS_NODE=400,
		SSD_OBJECT_NODE,
		SSD_ASSOCIATION_NODE,
		SSD_GENERALIZATION_NODE,
		SSD_AGGREGATION_NODE,
		UCD_ACTOR_NODE,
		UCD_USE_CASE_NODE,
		UCD_SYSTEM_NODE,
		ATD_SYNCHRONIZATION_NODE,
		ATD_ACTION_STATE_NODE,
		ATD_WAIT_STATE_NODE,
		ATD_DECISION_STATE_NODE,
		ATD_INITIAL_STATE_NODE,
		ATD_FINAL_STATE_NODE,
		CPD_COMPONENT_NODE,
		CPD_INTERFACE_NODE,
		DPD_RESOURCE_NODE,
		CBD_ACTOR_NODE,
		CBD_CLASS_NODE,
		CBD_OBJECT_NODE,
		SCD_AND_STATE,
		SCD_DECISION_STATE,
		SCD_DEFAULT_STATE,
		SCD_FINAL_STATE,
		SCD_OR_STATE,
		SCD_SYNCHRONIZATION_STATE,

		// UML edges
		SSD_BINARY_ASSOCIATION_EDGE,
		SSD_GENERALIZATION_EDGE,
		SSD_OBJECT_LINK_EDGE,
		SSD_PARTICIPANT_LINK_EDGE,
		SSD_ASSOCIATION_LINK_EDGE,
		SSD_AGGREGATION_EDGE,
		SSD_COMPOSITION_EDGE,
		UCD_BINARY_ASSOCIATION_EDGE,
		UCD_GENERALIZATION_EDGE,
		ATD_TRANSITION_EDGE,
		CPD_DEPENDENCY_EDGE,
		CPD_REALIZATION_EDGE,
		DPD_COMMUNICATION_EDGE,
		CBD_CLASS_LINK_EDGE,
		CBD_OBJECT_LINK_EDGE,
		SCD_TRANSITION_EDGE,
		SCD_AND_EDGE,
		
		// specific UML node shapes and lines
		SSD_SINGLE_OBJECT_BOX=500,
		SSD_DOUBLE_OBJECT_BOX,
		SSD_SINGLE_CLASS_BOX,
		SSD_DOUBLE_CLASS_BOX,
		SSD_TRIPLE_CLASS_BOX,
		SSD_RCLINE,
		SSD_R2LINE,
		UCD_SINGLE_CLASS_BOX,
		UCD_BOUNDARY_BOX,
		CBD_SINGLE_CLASS_BOX,
		CBD_SINGLE_OBJECT_BOX,
		SCD_AND_STATE_BOX,
		SCD_AND_LINE,
		OBJECT_STICKMAN,
		ACTOR_CLASS_BOX,
		ACTOR_OBJECT_BOX,
		GD_BOUNDARY_SHAPE,
		GD_CONTROLLER_SHAPE,
		GD_ENTITY_SHAPE,

		// a shape view.
		VIEW=600,			

		// types for the COLOR-X tools.
		CSO_CLASS=700,
		CSO_OBJECT,
		CSO_RELATIONSHIP,
		CSO_PARTICIPANT,
		CSO_JUNCTION,
		CSO_INSTANTIATION,	
		CSO_POSSESSION,		
		CSO_GENERALIZATION,
		CSO_AGGREGATION,
		CSO_SUBCLASSES,
		CSO_CONSTRAINT_EDGE,
		CSO_CLASS_BOX,		
		CSO_OBJECT_BOX,
		CE_PERMIT_EVENT_NODE,
		CE_MUST_EVENT_NODE,
		CE_NEC_EVENT_NODE,
		CE_START_NODE,	
		CE_FINAL_NODE,
		CE_EVENT_EDGE,		
		CE_NONEVENT_EDGE};

	/// returns the name of a type having this code (0 if it doesn't exist).
	static const char* GetName(int code); 

	/// returns the code of type name (0 if it doesn't exist).
	static int GetCode(const char* name); 

	/// returns code subject index (> 1) or 0 if code isn't in code list.
	static int GetIndex(int code, const int codelist[]); 

	///
	static TypeName typeNames[];
};
#endif
