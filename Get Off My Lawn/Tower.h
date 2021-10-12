/******************************************************************************/
/*!
\file   Tower.h
\author Zachary Sng Zhi Ren			(60%)| Wong Zhihao(40%)
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
#include "Combatant.h" // Combat Functions

#ifndef TOWER_H
#define TOWER_H

// What type of tower it is
enum TOWER_TYPE
{
	SINGLE_TARGET = 0,
	AREA_OF_EFFECT,
	SLOW_DOWN,
	POISON,
	STUN_TOWER,
};

class Tower : public Combatant
{
protected:
	// some code
	TOWER_TYPE type_;        // The way that the tower attacks units 
	bool attacking_;
	float fire_counter_;

public:
	// Constructor and Destructor
	Tower(
		// Tower variables
		TOWER_TYPE type,			// Speed of the unit

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
	~Tower();

	// getter and setters
	TOWER_TYPE Get_Tower_Type() const;
	void Set_Tower_Type(TOWER_TYPE);

	void Set_Attacking(bool attacking);
	bool Get_Attacking() const;

};
#endif TOWER_H
