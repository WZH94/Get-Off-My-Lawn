/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Combatant.h
\author Wong Zhihao(90%)		| Zachary Sng Zhi Ren (10%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong
\par    Course: GAM150
\date
\brief
This file contains the declarations of the Combatant class, which holds
combat variables and functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef COMBATANT_H
#define COMBATANT_H

#include "GameObject.h"
#include <vector>

class Combatant : public GameObject
{
protected:
	bool is_aoe_;							// Whether unit is AOE and can have multiple targets
	int health_;							// The health point of a combatant
	int max_health_;						// Maximum health of a combatant
	int cost_;								// The cost to purchase a combatant (available for player only)
	int loot_;								// How much lunch money this unit provides
	int attack_power_;						// The attack power of a combatant (e.g. dmg/s)
	float range_;							// Attack range of a combatant
	float attack_rate_;						// The attack speed/rate of a combatant
	double attack_cooldown_;				// The cooldown timer of the unit, time difference between cooldown_start_time and current time
	double cooldown_start_time_;			// The time in system seconds since the last attack
	//Combatant * target;					// Target of the combatant
	std::vector <Combatant *> targets_;		// Target list of the unit
	
public:
	Combatant();
	Combatant(
		// Combatant variables
		bool is_aoe,				// Whether unit is AOE
		int health,					// Health AND max health
		int cost,					// Cost to buy unit
		int loot,					// Amount of lunch money unit gives when it is defeated
		int attack_power,			// Damage of the unit
		float attack_rate,			// Attack speed
		float range,				// Attack range

		// GameObject variables
		SIDES side,					// Grandma or Kid?
		float x, float y,			// Spawn position
		float scale_x,				// Scale/Radius of the unit
		float scale_y,
		OBJECT_TYPES object_type,	// What kind of object it is
		UNIT_TYPES unit_type		// What type of unit it is
	);

	bool Get_Is_AOE() const;

	// Get the cost of the combatant
	int Get_Cost() const;

	// Get the health of the combatant
	int Get_Health() const;
	// Set the health of the combatant
	void Set_Health(int);

	// Gets the amount of lunch money this unit drops
	int Get_Loot() const;

	// Get the attack power of the combatant
	int Get_Attack_Power() const;
	// Set the attack power of the combatant
	void Set_Attack_Power(int);

	// Get the range of the combatant
	float Get_Range() const;
	
	// Gets the target of the combatant
	// If AOE unit with multiple targets, Gets the last in the list
	Combatant* Get_Target() const;

	// Adds a target of the combatant to the list
	// Limited to 1 if not AOE unit
	// Return error message if it tries to add more than 1 unit to non-AOE unit
	void Add_Target(Combatant *);

	// Gets how many units this unit is targetting
	int Get_Target_List_Size() const;

	// Removes the last target in the list
	void Remove_Target();

	/******************************* COOLDOWN FUNCTIONS *******************************/

	// Checks if unit is ready to attack
	bool Cooldown_Is_Ready();

	// Advances the unit's cooldown
	void Advance_Cooldown();

	// Resets the unit's cooldown after it has attacked
	void Reset_Cooldown();

	// Sets the time in system seconds since the last attack
	void Reset_Cooldown_Start_Time();

	int Get_Max_Health() const;
};

#endif