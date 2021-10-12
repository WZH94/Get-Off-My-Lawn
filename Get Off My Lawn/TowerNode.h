/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   TowerNode.h
\author Ngm Hui Min, Lois			(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login:lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the declaration of the Tower Node class and its functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef TOWERNODE_H
#define TOWERNODE_H

#include "GameObject.h"			// Inherits from GameObject
#include "ObjectList.h"			// Object types

// Statuses of the Tower Nodes
enum ACTIVE_TYPE {
	EMPTY = 0,		
	TOWER_CHOICE,
	TOWER_HOVER,
	TOWER_PLACED,
	OPTION_1,
	OPTION_2,
	OPTION_3
};


class TowerNode : public GameObject {
private:
	double respawn_timer_;				// Kids towers, how long before it respawns after getting to destroyed
	bool is_respawning_;				// If it is respawning
	ACTIVE_TYPE active_;				// Checks if the node is active or not
	UNIT_TYPES tower_type_;				// The tower type this node holds.
	float selection_width_height_;		// Selection height the cursor can hit
	float selection_spacing_;			// Selection spacing the cursor can hit

public:
	// Constructor for the tower node. Sets various base values.
	TowerNode(float node_x, float node_y, SIDES side, UNIT_TYPES type);

	// Deconstructor for the TowerNode
	virtual ~TowerNode();

	// Updates the tower node logic
	void Update();

	// Get the active state of the towernode.
	ACTIVE_TYPE Get_Active();

	// Set the active state of the towernode.
	void Set_Active(ACTIVE_TYPE, UNIT_TYPES=NOTHING);

	// Gets the type of the tower this tower node will spawn. 
	UNIT_TYPES Get_Tower_Type();

	// Set the tower type of the grandma node
	void Set_Tower_Type(UNIT_TYPES);

	// Reset the tower node status to empty.
	void Reset_Tower_Node();

	// Gets the width of the nodes collision space.
	float Get_Selection_Width_Height() const;

	// Gets the spacing of the nodes collision space.
	float Get_Selection_Spacing() const;
};


#endif TOWERNODE_H