/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   TowerNode.cpp
\author Ngm Hui Min, Lois		(100%)
\par    email: lois.ngm\@digipen.edu
\par    DigiPen login:lois.ngm
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the impementations of the Tower Node class. Tower Nodes
handle the construction of towers only in allocated places in the level.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "TowerNode.h"			// Function declarations
#include "ObjectSpawner.h"		// Spawning of the tower nodes
#include "ObjectList.h"			// Object enums
#include "LogicComponents.h"	// Logic components
#include "SystemComponents.h"	// System componenets

/******************************************************************************/
/*!
	Constructor for the tower node. Sets various base values.
*/
/******************************************************************************/
TowerNode::TowerNode(float node_x, float node_y, SIDES side, UNIT_TYPES type)
	:
	// Constructs its parent class
	GameObject(side, node_x, node_y, 100.0f, 100.0f, TOWER_NODES, (side == GRANDMA)?type:K_TOWER_NODE), active_((side==GRANDMA)?EMPTY:TOWER_CHOICE),
	tower_type_{ type },
	respawn_timer_{ 0.0 },
	is_respawning_{false},
	selection_width_height_{31.25},
	selection_spacing_{3.125}
{
	Set_Texture_Width(0.25f);
	Set_Texture_Change(0.0f);
}

/******************************************************************************/
/*!
Deconstructor for the TowerNode
*/
/******************************************************************************/
TowerNode::~TowerNode() {

}

/******************************************************************************/
/*!
	Updates the tower node logic
*/
/******************************************************************************/
void TowerNode::Update()
{
	// Check if the towernode is a kid and it is empty, meaning its tower has been destroyed
	if (side_ == KIDS && active_ == EMPTY)
	{
		// Advances its respawn time
		respawn_timer_ += system_components.framerate_manager->Get_Game_Time();
		is_respawning_ = true;
	}

	// If it is respawning and has already reached 30 seconds
	if (is_respawning_ && (respawn_timer_ >= 30.0))
	{
		// Set the kid tower node to respawn its tower
		if (side_ == KIDS)
			Set_Active(TOWER_PLACED, tower_type_);
		else
			Set_Active(TOWER_CHOICE);

		respawn_timer_ = 0.0;
		is_respawning_ = false;
	}
}

/******************************************************************************/
/*!
	Get the active state of the towernode.
*/
/******************************************************************************/
ACTIVE_TYPE TowerNode::Get_Active() {
	return active_;
}

/******************************************************************************/
/*!
Set the active state of the towernode.
*/
/******************************************************************************/
void TowerNode::Set_Active(ACTIVE_TYPE a, UNIT_TYPES t) {
	// Do nothing if state is the same
	if (a == active_)
		return;

	// Check the state it is changing to and changes its texture and behaviour accordingly.
	switch (a)
	{
	case EMPTY:
	{
		Set_Texture_Change(0.0f);
		Set_Alive(true);
		break;
	}
	case TOWER_HOVER:
	{
		Set_Texture_Change(Get_Texture_Width());
		break;
	}
	case TOWER_CHOICE:
	{
		Set_Texture_Change(Get_Texture_Width() * 2);

		break;
	}
	case TOWER_PLACED:
	{
		Set_Alive(false);
		Spawn_Object(t, Get_x(), Get_y());			

		break;
	}
	default:
		break;
	}
	active_ = a;
}

/******************************************************************************/
/*!
Gets the type of the tower this tower node will spawn.
*/
/******************************************************************************/
UNIT_TYPES TowerNode::Get_Tower_Type() {
	return tower_type_;
}

/******************************************************************************/
/*!
Set the tower type of the grandma node
*/
/******************************************************************************/
void TowerNode::Set_Tower_Type(UNIT_TYPES type) {
	if(type >= G_T_SHOOTING && type <= G_T_STUN)
		tower_type_ = type;
}

/******************************************************************************/
/*!
Reset the tower node status to empty.
*/
/******************************************************************************/
void TowerNode::Reset_Tower_Node() {

	active_ = EMPTY;
}

/******************************************************************************/
/*!
Gets the width of the nodes collision space.
*/
/******************************************************************************/
float TowerNode::Get_Selection_Width_Height() const
{
	return selection_width_height_;
}

/******************************************************************************/
/*!
Gets the spacing of the nodes collision space.
*/
/******************************************************************************/
float TowerNode::Get_Selection_Spacing() const
{
	return selection_spacing_;
}