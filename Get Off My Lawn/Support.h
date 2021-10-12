/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Support.h
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Support class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SUPPORT_H
#define SUPPORT_H

#include "Soldier.h" // Soldier functions

typedef enum UNIT_TYPES UNIT_TYPES;

class Support : public Soldier
{
public:
	Support(
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
		float scale_y,
		UNIT_TYPES unit_type		// What type of unit it is
	);

	virtual ~Support();

	void Update();
	void Draw();
	void Free();
};
#endif SUPPORT_H