/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Projectiles.cpp
\author Wong Zhihao (80%) | Sng Zhi Ren Zachary (20%)
\par    email: zhihao.wong\@digipen.edu	| z.sng\@digipen.edu
\par    DigiPen login: zhihao.wong | z.sng | zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
	This file contains the implementation for Projectiles and their targeting.

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Projectiles.h"		// Class and function declarations
#include "Movement.h"			// Movement function for projectile
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "Collision.h"			// Collision with traget
#include "CombatSystem.h"		// Damaging target
#include "Combatant.h"			// Combatant class
#include "ObjectList.h"			// UNIT_TYPES

/******************************************************************************/
/*!
	Constructor for Projectile Class
*/
/******************************************************************************/
Projectile::Projectile()
	:
	GameObject(
		NONE,
		0, 0,
		10.0f, 10.0f,
		PROJECTILE,
		P_BLANK
	),
	active_{ false },
	target_is_dead_{ false },
	target_flag_{ false },
	speed_{ 300.0f },
	target_ID_{ 0 },
	damage_{ 0 }
{
	/* Variables that need to be reinitialised when set to active:
	Unit Type
	Position
	Texture
	Target Stats
	*/
}

Projectile::Projectile(float x, float y, UNIT_TYPES type, SIDES side, int damage, GameObject & target)
	:
	GameObject(side, x, y, 10.0f, 10.0f, PROJECTILE, type),
	active_{false},
	target_is_dead_{false},
	target_flag_{false},
	speed_{ 300.0f },
	target_ID_{ target.Get_ID() },
	damage_{ damage },
	Target_Stats{ target.Get_Pos(), target.Get_Side(), target.Get_Object_Type(), target.Get_Radius() }

{
}

void Projectile::Set_Active(UNIT_TYPES type, float x, float y, int damage, GameObject & target)
{
	active_ = true;
	unit_type_ = type;
	pos_.x = x;
	pos_.y = y;
	damage_ = damage;
	texture_ = system_components.graphics_manager_->Get_Texture(type);

	target_ID_ = target.Get_ID();
	Target_Stats.pos_ = target.Get_Pos();
	Target_Stats.unit_side_ = target.Get_Side(); 
	Target_Stats.object_type_ = target.Get_Object_Type();
	Target_Stats.radius_ = target.Get_Radius();

	target_flag_ = false;
	target_is_dead_ = false;
}

void Projectile::Set_Inactive()
{
	active_ = false;
	unit_type_ = P_BLANK;
	pos_.x = 0;
	pos_.y = 0;
	damage_ = 0;
	texture_ = system_components.graphics_manager_->Get_Texture(P_BLANK);

	target_ID_ = 0;
	Target_Stats.pos_.x = 0;
	Target_Stats.pos_.y = 0;
	Target_Stats.unit_side_ = NONE;
	Target_Stats.radius_ = 0;

	target_flag_ = false;
	target_is_dead_ = false;
}

/******************************************************************************/
/*!
Get if the projectile is active and in play
*/
/******************************************************************************/
bool Projectile::Get_Active() const
{
	return active_;
}

/******************************************************************************/
/*!
Get the speed of the projectile
*/
/******************************************************************************/
float Projectile::Get_Speed() const
{
	return speed_;
}

/******************************************************************************/
/*!
Set the speed of the projectile
*/
/******************************************************************************/
void Projectile::Set_Speed(float input_speed)
{
	speed_ = input_speed;
}

/******************************************************************************/
/*!
Get the x-directional speed of the projectile
*/
/******************************************************************************/
float Projectile::Get_x_Speed() const
{
	return vel_.x;
}

/******************************************************************************/
/*!
Set the x-directional speed of the projectile
*/
/******************************************************************************/
void Projectile::Set_x_Speed(float x_speed)
{
	vel_.x = x_speed;
}

/******************************************************************************/
/*!
Get the y-directional speed of the projectile
*/
/******************************************************************************/
float Projectile::Get_y_Speed() const
{
	return vel_.y;
}

/******************************************************************************/
/*!
Set the y-directional speed of the projectile
*/
/******************************************************************************/
void Projectile::Set_y_Speed(float y_speed)
{
	vel_.y = y_speed;
}

/******************************************************************************/
/*!
"Update" function of Projectile Class
*/
/******************************************************************************/
void Projectile::Update(void)
{
	Combatant * Target = nullptr;

	if (Target_Stats.object_type_ == SOLDIER)
	{
		if (Target_Stats.unit_side_ == GRANDMA)
			Target = logic_components.object_manager->Find_Grandma_Soldier(target_ID_);

		else if (Target_Stats.unit_side_ == KIDS)
			Target = logic_components.object_manager->Find_Kid_Soldier(target_ID_);
	}

	else if (Target_Stats.object_type_ == TOWER)
		Target = logic_components.object_manager->Find_Tower(target_ID_);

	// Check if target is still alive, and that it exists (meaning it has not died and been delete)
	if (Target && target_is_dead_ == false)
	{
		// Set the projectile target to the found target
		target_ = Target;

		// Saves the last known target's stats in case it dies before the projectile reaches it
		Target_Stats.pos_ = Target->Get_Pos();
		Target_Stats.radius_ = Target->Get_Radius();
	}

	// Target is dead
	else if (target_flag_ == false)
	{
		// Set flag to be true
		target_is_dead_ = true;
		target_flag_ = true;
	}

	if (target_flag_ == true)
	{
		// Create a dummy target with the last known stats of the target
		Combatant Dummy_Target;
		Dummy_Target.Set_Pos(Target_Stats.pos_);
		Dummy_Target.Set_Radius(Target_Stats.radius_);

		// Set the projectile to travel towards the dummy target, so it doesn't just poof on the spot
		target_ = &Dummy_Target;

		// Move the projectile to its target
		Move_Projectile(*this, *target_);
	}
	
	else
		// Move the projectile to its target
		Move_Projectile(*this, *target_);

	// Check if it has collided with its target
	if (Collision_Pt_w_Circle(*this, *target_))
	{
		// If the target is still alive, damage it
		if (target_is_dead_ == false)
			Damage( *target_, damage_);

		if (Target_Stats.object_type_ == SOLDIER && 
			(unit_type_ == G_P_SLOW || unit_type_ == K_P_SLOW || unit_type_ == GT_P_SLOW || unit_type_ == KT_P_SLOW) &&
			target_->Get_Unit_Type() != K_S_BIGBOB)
			Slowed(*(Soldier *)target_);

		if (Target_Stats.object_type_ == SOLDIER &&
			(unit_type_ == G_P_STUN || unit_type_ == K_P_STUN || unit_type_ == GT_P_STUN || unit_type_ == KT_P_STUN) &&
			target_->Get_Unit_Type() != K_S_BIGBOB)
			Stunned(*(Soldier *)target_);

		if (Target_Stats.object_type_ == SOLDIER &&
			(unit_type_ == GT_P_POISON || unit_type_ == KT_P_POISON) &&
			target_->Get_Unit_Type() != K_S_BIGBOB)
			Poisoned(*(Soldier *)target_);

		Select_SFX();

		// Set projectile to be inactive
		Set_Inactive();
	}
}
	
void Projectile::Select_SFX()
{
	switch (unit_type_)
	{
	case P_MELEE:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_TANK_HIT_1, pos_.x, pos_.y);
		break;

	case G_P_SHOOTER:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_SHOOTER_HIT_1, pos_.x, pos_.y);
		break;

	case G_P_SABOTEUR:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_SABOTEUR_HIT_1, pos_.x, pos_.y);
		break;

	case G_P_SLOW:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_SLOW_HIT_1, pos_.x, pos_.y);
		break;

	case G_P_ATTACKSPEEDUP:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_ATTACKSPEEDUP_HIT_1, pos_.x, pos_.y);
		break;

	case G_P_STUN:
	case K_P_STUN:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_STUN_HIT_1, pos_.x, pos_.y);
		break;

	case K_P_SHOOTER:
		system_components.audio_manager->Play_Sound(SFX_KID_SHOOTER_HIT, pos_.x, pos_.y);
		break;

	case K_P_SABOTEUR:
		system_components.audio_manager->Play_Sound(SFX_KID_SABOTEUR_HIT_1, pos_.x, pos_.y);
		break;

	case K_P_ATTACKSPEEDUP:
		system_components.audio_manager->Play_Sound(SFX_KID_ATTACKSPEEDUP_HIT_1, pos_.x, pos_.y);
		break;

	case K_P_BIGBOB:
		system_components.audio_manager->Play_Sound(SFX_KID_BIGBOB_HIT, pos_.x, pos_.y);
		break;

	case GT_P_SHOOTER:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_OVEN_HIT, pos_.x, pos_.y);
		break;

	case GT_P_AOE:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_DENTURES_HIT, pos_.x, pos_.y);
		break;

	case GT_P_POISON:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_VEGGIES_HIT, pos_.x, pos_.y);
		break;

	case GT_P_SLOW:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_PUPPIES_HIT, pos_.x, pos_.y);
		break;

	case GT_P_STUN:
		system_components.audio_manager->Play_Sound(SFX_GRANDMA_CAKE_HIT, pos_.x, pos_.y);
		break;

	case KT_P_SHOOTER:
		system_components.audio_manager->Play_Sound(SFX_KID_SLINGSHOT_HIT, pos_.x, pos_.y);
		break;

	case KT_P_AOE:
		system_components.audio_manager->Play_Sound(SFX_KID_PILLOW_HIT, pos_.x, pos_.y);
		break;

	case KT_P_POISON:
		system_components.audio_manager->Play_Sound(SFX_KID_WHOOPEE_HIT, pos_.x, pos_.y);
		break;

	case KT_P_SLOW:
		system_components.audio_manager->Play_Sound(SFX_KID_MUD_HIT, pos_.x, pos_.y);
		break;

	case KT_P_STUN:
		system_components.audio_manager->Play_Sound(SFX_KID_CAR_HIT, pos_.x, pos_.y);
		break;
	}
}