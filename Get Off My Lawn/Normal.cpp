/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Normal.cpp
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: zhihao.wong\@digipen.edu | z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of the Normal Soldier class.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content ? 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "Normal.h"           // Function declarations
#include "RenderManager.h"	  // Render functions for soldiers
#include "ObjectManager.h"	  // Object manager
#include "Collision.h"		  // Collision functions
#include "ObjectList.h"		  // Object enums
#include "SystemComponents.h" // System components
#include "CombatSystem.h"	  // Combat functions
#include "LogicComponents.h"  // Logic components

/******************************************************************************/
/*!
Constructor for Normal Class
*/
/******************************************************************************/
Normal::Normal(
	float speed,
	bool is_aoe, int health, int cost, int loot, int attack_power, float attack_rate, float range,
	SIDES side, float x, float y, float scale_x, float scale_y, UNIT_TYPES unit_type)
	
	:
	Soldier(
		speed,					// Speed		
		NORMAL,					// Soldier category

		is_aoe,					// Not AOE
		health,					// Health
		cost,					// Cost
		loot,					// Loot
		attack_power,			// Damage
		attack_rate,			// Attack speed
		range,					// Range, will be added on with unit's radius

		side,					// Which side this unit is on
		x, y,					// Spawn position
		scale_x,					// Scale/Radius of object
		scale_y,
		SOLDIER,				// What type of object it is
		unit_type				// What specific type of unit it is
	)
{
}

/******************************************************************************/
/*!
Destructor for Normal Class
*/
/******************************************************************************/
Normal::~Normal()
{
}

/******************************************************************************/
/*!
"Update" function of Normal class
*/
/******************************************************************************/
void Normal::Update()
{
	//Updates status effects
	Status_Updates();

	//Caps the health at max health
	if (health_ > max_health_)
		health_ = max_health_;

	// Check if object has died
	if (health_ <= 0)
	{
		//Checks if object was a kid
		if (this->Get_Side() == KIDS)
		{
			// Adds the loot drops to the player's data
			logic_components.level_data->players->Granny_Mojo_Drop(loot_);
			logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_MONEY_DROPS, pos_.x, pos_.y, 0, 0.0f);

			system_components.audio_manager->Play_Sound(SFX_KID_FAINT_1, pos_.x, pos_.y);
		}

		else if (side_ == GRANDMA)
		{
			system_components.audio_manager->Play_Sound(SFX_GRANDMA_FAINT_1, pos_.x, pos_.y);
			logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_POOF, pos_.x, pos_.y, 60.0f, 0.5f);
		}

		//Moves object to death list to be deleted
		logic_components.object_manager->Queue_Kill_Object(this);
		return;
	}
	// Checks for any status effects or if the soldier is at half health
	if (is_poisoned_ || is_slowed_ || health_ <= (max_health_ / 2))
	{
		if (bubble_counter_ >= 1.0f)
		{
			if (health_ <= (max_health_ / 2))
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SWEAT, pos_.x, pos_.y, 0, 0.0f);
			if (is_poisoned_)
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_POISON, pos_.x, pos_.y, 0, 0.0f);
			if (is_slowed_)
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SLEEPY_BUBBLE, pos_.x, pos_.y, 0, 0.0f);
			bubble_counter_ = 0.0f;
		}
		else
			bubble_counter_ += system_components.framerate_manager->Get_Game_Time();
	}
	// Checks if the soldier is stunned
	if (is_stunned_)
		return;

	// Checks if there are any units in range that it can attack
	Combatant* checkEnemy;

	// if checkEnemy is not a nullptr, it means a unit is found
	checkEnemy = Find_Nearest_Enemy_Soldier(*this, this->Get_Range());

	// If there is an enemy to attack
	if (checkEnemy)
	{
		// Adds the found enemy to this unit's target list
		Add_Target(checkEnemy);
		Combat_List.push_back(this);
	}

	//if (Find_Soldiers_AOE_Check(*this, range_))
	//	Combat_List.push_back(this);

	/*if (Find_Soldiers_AOE_Check(*this, range_, false))
		Combat_List.push_back(this);*/

	// Nothing to attack, unit moves towards the nodes
	else
		Movement_List.push_back(this);

	// Continues the attack cooldown
	if (!Cooldown_Is_Ready())
		Advance_Cooldown();
}

/******************************************************************************/
/*!
"Draw" function of Normal class
*/
/******************************************************************************/
void Normal::Draw()
{
	Render_Object(*this);
	Animate_Soldier(*this);
}

/******************************************************************************/
/*!
"Free" function of Normal class
*/
/******************************************************************************/
void Normal::Free()
{
}
