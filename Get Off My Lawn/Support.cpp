/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Support.cpp
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
#include "Support.h"          // Function declarations
#include "RenderManager.h"	  // Render functions for soldiers
#include "ObjectManager.h"	  // Object manager
#include "Collision.h"		  // Collision functions
#include "ObjectList.h"		  // Object enums
#include "ObjectSpawner.h"	  // Object spawner
#include "CombatSystem.h"	  // Combat functions
#include "LogicComponents.h"  // Logic components
#include "SystemComponents.h" // System components

/******************************************************************************/
/*!
Constructor for Anti Support Class
*/
/******************************************************************************/
Support::Support(
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
Destructor for Support class
*/
/******************************************************************************/
Support::~Support()
{
}

/******************************************************************************/
/*!
"Update" function of Support class
*/
/******************************************************************************/
void Support::Update()
{
	//Updates status effects
	Status_Updates();

	// Check if object has died
	if (Get_Health() <= 0)
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
	// Checks if the soldier is an attack buff type
	if (unit_type_ == G_S_ATTACKBUFF || unit_type_ == K_S_ATTACKBUFF)
	{
		// Finds all soldiers in range
		Find_Soldiers_AOE_Check(*this, range_, true);
		// Buffs all the soldiers in range
		while (targets_.size())
		{
			Soldier * buffed = dynamic_cast<Soldier*> (targets_.back());
			if (buffed)
			{
				Attack_Up(*buffed);
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_ATTACK_AURA, buffed->Get_x(), buffed->Get_y(), 0, 0.5f);
			}
			targets_.pop_back();
		}
	}
	else if (Cooldown_Is_Ready())
	{
		// Checks if there are any units in range that it can attack
		GameObject * checkAlly;

		// if checkEnemy is not a nullptr, it means a unit is found
		checkAlly = Find_Furthest_Ally(*this, this->Get_Range());

		// If there is an ally in range
		if (checkAlly)
		{
			Spawn_Projectile(G_P_SHOOTER, Get_Pos().x, Get_Pos().y, Get_Attack_Power(), *checkAlly);
		}
		// Resets the support's cooldown to 0s
		Reset_Cooldown();
	}
	// Checks if there is any soldier to attack
	if (Find_Nearest_Enemy_Soldier(*this, range_))
		Combat_List.push_back(this);
	else
		Movement_List.push_back(this);

	// Continues the attack cooldown
	if (!Cooldown_Is_Ready())
		Advance_Cooldown();
}

/******************************************************************************/
/*!
"Draw" function of Support class
*/
/******************************************************************************/
void Support::Draw()
{
	Render_Object(*this);
	Animate_Soldier(*this);
}

/******************************************************************************/
/*!
"Free" function of Support class
*/
/******************************************************************************/
void Support::Free()
{
}