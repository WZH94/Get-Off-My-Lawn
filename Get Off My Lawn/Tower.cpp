/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Tower.cpp
\author Zachary Sng Zhi Ren			(60%)| Wong Zhihao (40%)
\par    email: z.sng\@digipen.edu	| zhihao.wong\@digipen.edu
\par    DigiPen login: z.sng		| zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to handle Towers 
(parent class/base class of Towers)

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Tower.h"           // Function Declarations
#include "GraphicsManager.h" // Graphics manager
#include "RenderManager.h"   // Render manager

/******************************************************************************/
/*!
Constructor for Towers
*/
/******************************************************************************/
Tower::Tower(
	TOWER_TYPE type,
	bool is_aoe, int health, int cost, int loot, int attack_power, float attack_rate, float range,
	SIDES side, float x, float y, float scale_x, float scale_y, OBJECT_TYPES object_type, UNIT_TYPES unit_type)

	: Combatant(
		is_aoe,			// Whether AOE or not
		health,			// Health
		cost,			// Cost
		loot,			// Loot
		attack_power,	// Damage
		attack_rate,	// Attack speed
		range,			// Range, will be added on with unit's radius

		side,			// Which side this unit is on
		x, y,			// Spawn position
		scale_x,			// Scale/Radius of object
		scale_y,
		object_type,	// What type of object it is
		unit_type		// What specific type of unit it is
	),
	type_(type),
	attacking_(false),
	fire_counter_{0.0f}
{
	Set_Texture_Width(0.25f);
	Set_Texture_Timer(1.0f);
	Set_Texture_Change(0.0f);
}

/******************************************************************************/
/*!
Default constructor of Towers
*/
/******************************************************************************/
Tower::~Tower()
{

}

/******************************************************************************/
/*!
Gets the tower type
*/
/******************************************************************************/
TOWER_TYPE Tower::Get_Tower_Type() const{
	return type_;
}

/******************************************************************************/
/*!
Sets the tower type
*/
/******************************************************************************/
void Tower::Set_Tower_Type(TOWER_TYPE tower_type_) {
	type_ = tower_type_;
}

/******************************************************************************/
/*!
Gets whether the tower is attacking
*/
/******************************************************************************/
void Tower::Set_Attacking(bool attacking)
{
	attacking_ = attacking;
}

/******************************************************************************/
/*!
Sets whether the tower is attacking
*/
/******************************************************************************/
bool Tower::Get_Attacking() const
{
	return attacking_;
}