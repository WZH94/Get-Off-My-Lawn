/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Collision.cpp
\author Wong Zhihao	(33%)| Tan Zhi Quan (33%)| Sng Zhi Ren Zachary(33%)
\par    email: zhihao.wong\@digipen.edu | zhiquan.tan\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | zhiquan.tan | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of Collision functions, and handles collision
detection between objects.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Collision.h"			// Class and function declarations
#include "Path.h"				// Paths class
#include "LogicComponents.h"	// Retrieve game objects
#include "Soldier.h"			// Soldier class
#include "GameObject.h"			// GameObject class
#include "Tower.h"				// Tower class

/******************************************************************************/
/*!
Takes in two points and gives the mid point between the two
*/
/******************************************************************************/
AEVec2 Find_Midpoint(AEVec2 first, AEVec2 second)
{
	AEVec2 result;
	result.x = (first.x + second.x) / 2;  // finds the mid point for the x coord
	result.y = (first.y + second.y) / 2;  // finds the mid point for the y coord
	return result;
}

/******************************************************************************/
/*!
Checks if there was a collision with the node (square)
*/
/******************************************************************************/

bool Collision_Pt_w_Node(GameObject& object, Path& node)
{
	AEVec2 fp_error_allowance = { 5.0f, 5.0f }; // allowance for floating point error or speed overflow
	AEVec2 node_pos = { node.Get_x() , node.Get_y() };
	AEVec2 obj_pos = { object.Get_x() , object.Get_y() };

	//node point is centred for floating pt allowance, checks if obj position is in the node's square
	if (obj_pos.x < node_pos.x - fp_error_allowance.x || obj_pos.x > (node_pos.x + fp_error_allowance.x) 
		|| obj_pos.y < node_pos.y - fp_error_allowance.y || obj_pos.y > (node_pos.y + fp_error_allowance.y))
		return false;

	else return true;
}

/******************************************************************************/
/*!
Checks if an object has collided with a movement node (point rectangle collision)
*/
/******************************************************************************/
bool Collision_Pt_w_Circle(GameObject& projectile, GameObject& object)
{
	// stores position of the projectile and object
	AEVec2 proj_pos = { projectile.Get_x(), projectile.Get_y() };
	AEVec2 obj_pos = { object.Get_x(), object.Get_y() };
	// stores radius of object
	float obj_radius = object.Get_Radius();
	// finds the displacement from the object
	float displacement_x = obj_pos.x - proj_pos.x;
	float displacement_y = obj_pos.y - proj_pos.y;
	// checks pythagoras theorum to see if pt is colliding with circle
	if ((obj_radius * obj_radius) >= (displacement_x * displacement_x) + (displacement_y * displacement_y))
		return true;

	else return false;
}

/******************************************************************************/
/*!
	Checks collision between unit 1 range / radius and unit 2 radius
*/
/******************************************************************************/

bool Collision_Circle_w_Circle(GameObject &object1, float range, GameObject &object2, Collision_Mode mode)
{
	//init object 1 stats
	float obj1_x = object1.Get_x();
	float obj1_y = object1.Get_y();
	float obj1_radius = 0.0f;

	//init object 2 stats
	float obj2_x = object2.Get_x();
	float obj2_y = object2.Get_y();
	float obj2_radius = object2.Get_Radius();

	//if checking for collision between unit and unit
	if (mode == check_unit)
	{
		obj1_radius = object1.Get_Radius();
	}
	//if checking for unit 2 entering unit 1's range
	if (mode == check_range)
	{
		obj1_radius = range;
	}

	//distance from unit 2 to unit 1 in x and y
	float displacement_x = obj2_x - obj1_x;
	float displacement_y = obj2_y - obj1_y;

	//max distance between the two objects possible to still allow collision
	float collision_displacement = obj2_radius + obj1_radius;

	//pythagorean theorum
	if ((collision_displacement * collision_displacement) >= (displacement_x * displacement_x) + (displacement_y * displacement_y))
		return true;

	else return false;
}

// Finds the nearest valid SOLDIER that the unit can attack within its range
Soldier* Find_Nearest_Enemy_Soldier(Combatant & attacker, float range, bool check_if_rusher, bool check_if_poisoned, bool check_if_slowed)
{
	SIDES side = attacker.Get_Side();

	// Pointer to the nearest valid enemy found
	Soldier* nearestEnemy = nullptr;

	// Nearest current enemy to the attacker, initialised to largest float value
	float nearest_vector = FLT_MAX;

	// Size of the soldier list
	unsigned soldier_list_size = 0;
	
	if (side == GRANDMA)
		soldier_list_size = logic_components.object_manager->Get_Size_Kid_Soldier_List();

	else if (side == KIDS)
		soldier_list_size = logic_components.object_manager->Get_Size_Grandma_Soldier_List();

	// If finding for any specific unit, set this to be true
	bool specific_check = (check_if_rusher == true || check_if_poisoned == true || check_if_slowed == true) ? true : false;
	// If specific unit type has been found already, set this to true so it skips every type it is not looking for
	bool specific_check_found = specific_check;
	// If specific type has been found and is the first to be found, override the last found normal unit
	bool skip_nearest_check = false;

	// Loops through entire Soldier List
	for (unsigned i = 0; i < soldier_list_size; ++i)
	{
		Soldier* CheckEnemy = nullptr;

		if (side == GRANDMA)
			CheckEnemy = logic_components.object_manager->Get_Kid_Soldier(i);

		else if (side == KIDS)
			CheckEnemy = logic_components.object_manager->Get_Grandma_Soldier(i);

		// Check if the enemy is not the attacker and is a type that the attacker can attack
		if (attacker.Get_Side() != CheckEnemy->Get_Side() && CheckEnemy != &attacker)
		{
			// Checks if the unit is a rusher and if attacker is not Anti-Rusher, and skips the rusher, since only anti-rushers can attack rushers
			if (check_if_rusher == false && CheckEnemy->Get_Category() == RUSHER)
				continue;

			// Check if a unique type has already been found so it skips every type it is not looking for.
			if (specific_check_found)
			{
				if (check_if_rusher && CheckEnemy->Get_Category() != RUSHER)
					continue;

				else if (check_if_poisoned && CheckEnemy->Get_is_Poisoned())
					continue;

				else if (check_if_slowed && CheckEnemy->Get_is_Slowed())
					continue;
			}

			// Check if that enemy is within range of the attacker
			if (Collision_Circle_w_Circle(attacker, range, *CheckEnemy, check_range))
			{
				// Check if the checked enemy is of the specific type to find, and if it is the first to be found
				if (specific_check && specific_check_found == false)
				{
					// If it is, then set to skip the check if this unit is the nearest unit found.
					if (check_if_rusher && CheckEnemy->Get_Category() == RUSHER)
						skip_nearest_check = true;

					else if (check_if_poisoned && CheckEnemy->Get_is_Poisoned() == false)
						skip_nearest_check = true;

					else if (check_if_slowed && CheckEnemy->Get_is_Slowed() == false)
						skip_nearest_check = true;
				}

				// Gets the positions of the attacker and enemy
				AEVec2 attacker_position = attacker.Get_Pos();
				AEVec2 enemy_position = CheckEnemy->Get_Pos();

				// Finds the distance between the enemy and the attacker
				float vector_mag = AECalcDistPointToCircle(&attacker_position, &enemy_position, CheckEnemy->Get_Radius());

				// Checks if this enemy is the nearest to the attacker
				if (skip_nearest_check == false && vector_mag < nearest_vector)
				{
					// Change nearest stats
					nearest_vector = vector_mag;
					nearestEnemy = CheckEnemy;

					if (skip_nearest_check)
						skip_nearest_check = false;
				}
			}
		}
	}

	// Returns the nearest enemy, if nullptr, no valid enemy found within range
	return nearestEnemy;
}

// Finds the nearest valid TOWER that the unit can attack within its range
Tower* Find_Nearest_Enemy_Tower(Combatant & attacker, float range)
{
	// Pointer to the nearest valid enemy found
	Tower * nearestEnemy = nullptr;

	// Nearest current enemy to the attacker, initialised to largest float value
	float nearest_vector = FLT_MAX;

	// Size of the tower list
	unsigned tower_list_size = logic_components.object_manager->Get_Size_Tower_List();

	// Loops through entire Tower List
	for (unsigned i = 0; i < tower_list_size; ++i)
	{
		Tower* CheckEnemy = logic_components.object_manager->Get_Tower(i);

		// Check if the enemy is not the attacker and is a type that the attacker can attack
		if (attacker.Get_Side() != CheckEnemy->Get_Side() &&
			CheckEnemy != &attacker)
		{
			// Check if that enemy is within range of the attacker
			if (Collision_Circle_w_Circle(attacker, range, *CheckEnemy, check_range))
			{
				// Finds the distance between the enemy and the attacker
				AEVec2 attacker_position = attacker.Get_Pos();
				AEVec2 enemy_position = CheckEnemy->Get_Pos();

				float vector_mag = AECalcDistPointToCircle(&attacker_position, &enemy_position, CheckEnemy->Get_Radius());

				// Checks if this enemy is the nearest to the attacker
				if (vector_mag < nearest_vector)
				{
					// Change nearest stats
					nearest_vector = vector_mag;
					nearestEnemy = CheckEnemy;
				}
			}
		}
	}

	// Returns the nearest enemy, if nullptr, no valid enemy found within range
	return nearestEnemy;
}

// Finds the nearest valid ally SOLDIER that the unit can support within its range
Soldier* Find_Furthest_Ally(Combatant & healer, float range)
{
	SIDES side = healer.Get_Side();

	// Pointer to the furthest valid ally found
	Soldier * furthestAlly = nullptr;

	// Furthest all to the support, initialised to smallest float value
	float furthest_vector = FLT_MIN;

	// Size of the soldier list
	unsigned soldier_list_size = 0;

	if (side == GRANDMA)
		soldier_list_size = logic_components.object_manager->Get_Size_Grandma_Soldier_List();

	else if (side == KIDS)
		soldier_list_size = logic_components.object_manager->Get_Size_Kid_Soldier_List();

	// Loops through entire Soldier List
	for (unsigned i = 0; i < soldier_list_size; ++i)
	{
		Soldier* CheckAlly = nullptr;

		if (side == GRANDMA)
			CheckAlly = logic_components.object_manager->Get_Grandma_Soldier(i);

		else if (side == KIDS)
			CheckAlly = logic_components.object_manager->Get_Kid_Soldier(i);

		// Check if the ally is not the support and is a type that support can heal
		if (healer.Get_Side() == CheckAlly->Get_Side() &&
			CheckAlly != &healer &&
			healer.Get_Unit_Type() != CheckAlly->Get_Unit_Type())
		{
			// Check if that ally is within range of the support
			if (Collision_Circle_w_Circle(healer, range, *CheckAlly, check_range))
			{
				// Finds the distance between the ally and the support
				AEVec2 support_position = healer.Get_Pos();
				AEVec2 ally_position = CheckAlly->Get_Pos();

				float vector_mag = AECalcDistPointToCircle(&support_position, &ally_position, CheckAlly->Get_Radius());

				// Checks if this ally is the furthest from the support
				if (vector_mag > furthest_vector)
				{
					// Change nearest stats
					furthest_vector = vector_mag;
					furthestAlly = CheckAlly;
				}
			}
		}
	}

	// Returns the nearest enemy, if nullptr, no valid enemy found within range
	return furthestAlly;
}

// Checks whether any enemies are within the range set, by calling circle - circle collision. if there are any, returns true.
bool Find_Soldiers_AOE_Check(Combatant & attacker, float range, bool allycheck)
{
	SIDES side = attacker.Get_Side();

	// Pointer to the any enemy found
	Soldier* check_soldier = nullptr;

	// Size of the soldier list
	unsigned soldier_list_size = 0;

	if ((side == GRANDMA && allycheck) || side == KIDS && !allycheck)
		soldier_list_size = logic_components.object_manager->Get_Size_Grandma_Soldier_List();

	else if ((side == KIDS && allycheck) || side == GRANDMA && !allycheck)
		soldier_list_size = logic_components.object_manager->Get_Size_Kid_Soldier_List();

	// Loops through entire Soldier List
	for (unsigned i = 0; i < soldier_list_size; ++i)
	{
		if ((side == GRANDMA && allycheck) || side == KIDS && !allycheck)
			check_soldier = logic_components.object_manager->Get_Grandma_Soldier(i);

		else if ((side == KIDS && allycheck) || side == GRANDMA && !allycheck)
			check_soldier = logic_components.object_manager->Get_Kid_Soldier(i);

		// Check if the ally is not the support and is a type that support can heal
		if (Collision_Circle_w_Circle(attacker, range, *check_soldier, check_range))
			attacker.Add_Target(check_soldier);
	}

	if (attacker.Get_Target_List_Size())
		return true;

	else return false;
}
