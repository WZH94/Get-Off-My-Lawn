/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SlowDown.h
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: z.sng\@digipen.edu | zhihao.wong\@digipen.edu
\par    DigiPen login: z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to handle Slow Towers

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content � 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SLOWDOWN_H
#define SLOWDOWN_H

#include "Tower.h" // Tower functions

class SlowDown : public Tower
{
protected:

public:
	SlowDown(
		// Combatant variables
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
	void Update(void);
	void Draw();
};

#endif SLOWDOWN_H