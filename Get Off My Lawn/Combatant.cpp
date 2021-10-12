/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Combatant.cpp
\author Wong Zhihao(90%)		| Zachary Sng Zhi Ren (10%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date
\brief
	This file contains the implementation of the Combatant class, which holds
	combat variables and functions.

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Combatant.h"	// Class and function declarations

Combatant::Combatant()
{

}

Combatant::Combatant(
	bool is_aoe, int health, int cost, int loot, int attack_power, float attack_rate, float range,
	SIDES side, float x, float y, float scale_x, float scale_y, OBJECT_TYPES object_type, UNIT_TYPES unit_type)

	: 

	GameObject(
		side,			// Which side this unit is on
		x, y,			// Spawn position
		scale_x,			// Scale/Radius of object
		scale_y,
		object_type,	// What type of object it is
		unit_type		// What specific type of unit it is
	),
	is_aoe_{is_aoe},
	health_{health},
	max_health_{health},
	cost_{cost},
	loot_{loot},
	attack_power_{attack_power},
	attack_rate_{attack_rate},
	attack_cooldown_{attack_rate},
	range_{range + scale_x}
{
}

bool Combatant::Get_Is_AOE() const
{
	return is_aoe_;
}

// Get the cost of the combatant
int Combatant::Get_Cost() const
{
	return cost_;
}

// Get the health of the combatant
int Combatant::Get_Health() const
{
	return health_;
}

// Set the health of the combatant
void Combatant::Set_Health(int input_health)
{
	// some code
	health_ = input_health;
}

// Gets the amount of lunch money this unit drops
int Combatant::Get_Loot() const
{
	return loot_;
}

// Get the attack power of the combatant
int Combatant::Get_Attack_Power() const
{
	return attack_power_;
}

// Set the attack power of the combatant
void Combatant::Set_Attack_Power(int input_attack_power)
{
	// some code
	attack_power_ = input_attack_power;
}

// Get the range of the combatant
float Combatant::Get_Range() const
{
	return range_;
}

// gets the target of the combatant
// if AOE unit with multiple targets, gets the last in the list
Combatant * Combatant::Get_Target() const
{
	return targets_.back();
}

// Adds a target of the combatant to the list
// Limited to 1 if not AOE unit
// Return error message if it tries to add more than 1 unit to non-AOE unit
void Combatant::Add_Target(Combatant * target)
{
	targets_.push_back(target);
}

// Gets how many units this unit is targetting
int Combatant::Get_Target_List_Size() const
{
	return targets_.size();
}

void Combatant::Remove_Target()
{
	targets_.pop_back();
}

/******************************* COOLDOWN FUNCTIONS *******************************/

// Checks if the unit is ready to attack
bool Combatant::Cooldown_Is_Ready()
{
	if (attack_cooldown_ >= attack_rate_)
		return true;

	else
		return false;
}

// Advances the unit's cooldown if it is not ready to attack
void Combatant::Advance_Cooldown()
{
	// Set the attack cooldown to time elapsed since last attack and current time
	attack_cooldown_ = AEGetTime(nullptr) - cooldown_start_time_;
}

// Resets the unit's cooldown after it has attacked
void Combatant::Reset_Cooldown()
{
	attack_cooldown_ = 0;

	Reset_Cooldown_Start_Time();
}

// Sets the time in system seconds since the last attack
void Combatant::Reset_Cooldown_Start_Time()
{
	AEGetTime(&cooldown_start_time_);
}

int Combatant::Get_Max_Health() const
{
	return max_health_;
}