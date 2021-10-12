/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Collision.cpp
\author Wong Zhihao	(33%)| Tan Zhi Quan (33%)| Sng Zhi Ren Zachary (33%)
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

#ifndef COLLISION_H
#define COLLISION_H

#include "AEVec2.h"

// Forward declaration of classes
typedef class Path Path;
typedef class GameObject GameObject;
typedef class Soldier Soldier;
typedef class Combatant Combatant;
typedef enum OBJECT_TYPES OBJECT_TYPES;
typedef class Tower Tower;

// Types of collision
enum Collision_Mode {
	check_range = 0,   // checks when unit enters another unit's range
	check_unit,		   // checks when unit collides with another unit
};

// Returns the midpoint between two points
AEVec2 Find_Midpoint(AEVec2 first, AEVec2 second);

// Checks if an object has collided with a movement node (point rectangle collision)
bool Collision_Pt_w_Node(GameObject &, Path& node);

// Checks if an projectile has collided with another object ( point circle collision)
bool Collision_Pt_w_Circle(GameObject &, GameObject &);

// Checks if two circles collide. Can be modified with the enum to check for a input range instead of a fixed radius
bool Collision_Circle_w_Circle(GameObject &, float, GameObject &, Collision_Mode);

// Finds the nearest valid SOLDIER that the unit can attack within its range
Soldier* Find_Nearest_Enemy_Soldier(Combatant& attacker, float range, bool check_if_rusher = false, bool check_if_poisoned = false, bool check_if_slowed = false);

// Finds the nearest valid TOWER that the unit can attack within its range
Tower* Find_Nearest_Enemy_Tower(Combatant & attacker, float range);

// Finds the nearest ally within range from the support
Soldier* Find_Furthest_Ally(Combatant & healer, float range);

// Checks whether any enemies are within the range set, by calling circle - circle collision. if there are any, returns true.
bool Find_Soldiers_AOE_Check(Combatant & attacker, float range, bool allycheck);

#endif COLLISION_H