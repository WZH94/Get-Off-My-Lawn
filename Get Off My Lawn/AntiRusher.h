/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   AntiRusher.h
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the AntiRusher class.

Functions include:
Anti_Rusher
~Anti_Rusher
Update
Draw
Free

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content � 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef ANTIRUSHER_H
#define ANTIRUSHER_H

#include "Soldier.h" // Soldier functions

typedef enum UNIT_TYPES UNIT_TYPES;

class Anti_Rusher : public Soldier
{
public:
	Anti_Rusher(
		// Soldier variables
		float speed,			// Speed of the unit

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
		float scale_y,				// Scale/Radius of the unit
		UNIT_TYPES unit_type		// What type of unit it is
	);

	virtual ~Anti_Rusher();

	void Update();
	void Draw();
	void Free();
};
#endif ANTIRUSHER_H
