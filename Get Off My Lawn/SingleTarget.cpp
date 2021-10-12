/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   SingleTarget.cpp
\author Wong Zhihao (40%) | Zachary Sng Zhi Ren(60%)
\par    email: z.sng\@digipen.edu	| zhihao.wong\@digipen.edu
\par    DigiPen login: z.sng		| zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the algorithmn to handle Single Target Towers

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "SingleTarget.h"     // Function declarations
#include "RenderManager.h"	  // Render functions for soldiers
#include "Collision.h"		  // Collision functions
#include "TowerNode.h"		  // Tower Node functions
#include "Players.h"		  // Player functions
#include "LogicComponents.h"  // Logic components
#include "TowernodeButton.h"  // Tower Node button functions
#include "SystemComponents.h" // System components

/******************************************************************************/
/*!
Default constructor of Single target shooting Towers
*/
/******************************************************************************/
Single_Target::Single_Target(
	int health, int cost, int loot, int attack_power, float attack_rate, float range,
	SIDES side, float x, float y, float scale_x, float scale_y, UNIT_TYPES unit_type)

	: Tower(
		SINGLE_TARGET,			// Tower Type

		false,					// Not AOE
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
		TOWER,					// What type of object it is
		unit_type				// What specific type of unit it is
	)
{
}

/******************************************************************************/
/*!
"Update" Function of Single_Target
*/
/******************************************************************************/
void Single_Target::Update(void)
{
	float nodeX = 0, nodeY = 0;
	// Check if object has died
	if (Get_Health() <= 0 || (gAEGameStateNext == AE_GS_RESTART && side_ == GRANDMA)) {
		for (unsigned i = 0; i < logic_components.object_manager->Get_Size_Button_List(); ++i)
		{
			TowerNodeButton * node = dynamic_cast<TowerNodeButton*>(logic_components.object_manager->Get_Button(i));
			if (!node) continue;
			nodeX = node->Get_x();
			nodeY = node->Get_y();
			if (node->Get_x() == this->Get_x() && node->Get_y() == this->Get_y()) {
				node->Set_Active(INACTIVE);
				node->Set_Alive(true);
				break;
			}

			if (side_ == KIDS)
			{
				for (unsigned j = 0; j < logic_components.object_manager->Get_Size_Tower_Node_List(); ++j)
				{
					TowerNode * tower_node = (logic_components.object_manager->Get_Tower_Node(j));
					if (!tower_node) continue;
					nodeX = tower_node->Get_x();
					nodeY = tower_node->Get_y();

					if (tower_node->Get_x() == this->Get_x() && tower_node->Get_y() == this->Get_y()) {
						tower_node->Set_Active(EMPTY);
						tower_node->Set_Alive(true);
						break;
					}
				}
			}
		}
		logic_components.level_data->players->Granny_Mojo_Drop(loot_);
		logic_components.object_manager->Queue_Kill_Object(this);

		system_components.audio_manager->Play_Sound(SFX_TOWER_DESTROY, pos_.x, pos_.y);
	}
	// If not search for enemies to attack
	else
	{
		// Checks if there are any units in range that it can attack
		Combatant* checkEnemy;

		// if checkEnemy is not a nullptr, it means a unit is found, searches for rushers
		checkEnemy = (Combatant*)Find_Nearest_Enemy_Soldier(*this, this->Get_Range(), true, false);

		// No rushers found, search for any soldier
		if (checkEnemy == nullptr)
			checkEnemy = (Combatant*)Find_Nearest_Enemy_Soldier(*this, this->Get_Range(), false, false);

		// If there is an enemy to attack
		if (checkEnemy)
		{
			// Adds the found enemy to this unit's target list
			Add_Target(checkEnemy);
			Combat_List.push_back(this);
			attacking_ = true;
		}
		else
			attacking_ = false;

		if (!Cooldown_Is_Ready())
			Advance_Cooldown();
	}
	if (health_ <= (max_health_ / 2))
	{
		if (fire_counter_ >= 1.0f)
		{
			logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_FIRE, pos_.x, pos_.y, 1.0f, 0.0f);
			fire_counter_ = 0.0f;
		}
		else
			fire_counter_ += system_components.framerate_manager->Get_Game_Time();
	}
		
}

/******************************************************************************/
/*!
"Draw" Function of Single_Target
*/
/******************************************************************************/
void Single_Target::Draw()
{
	Render_Object(*this);
	Animate_Tower(*this);
}