/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   CombatSystem.cpp
\author Sng Zhi Ren Zachary		(90%)  | Tan Zhi Quan (10%)
\par    email: z.sng\@digipen.edu      | zhiquan.tan\@digipen.edu
\par    email: z.sng\@digipen.edu
\par    DigiPen login: z.sng
\par    Course: GAM150
\date	13/04/18
\brief
	This file handles the combat functions of every combat type unit 

	Copyright (C) 2018 DigiPen Institute of Technology.
	Reproduction or disclosure of this file or its contents without the
	prior written consent of DigiPen Institute of Technology is prohibited.
	All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "CombatSystem.h"		// Function declarations
#include "Combatant.h"			// Combatant class
#include "LogicComponents.h"	// Logic components
#include "SystemComponents.h"	// System components
#include "ObjectList.h"			// Object type enums
#include "ObjectSpawner.h"		// Spawning of projectiles
#include "Collision.h"			// Collision detection
#include "Movement.h"			// Movement functions

/******************************************************************************/
/*!
Handles the combat of units that will be attacking in the current frame.
*/
/******************************************************************************/
void Initiate_Combat()
{
	// Loop through the whole combat list
	while (!Combat_List.empty())
	{
		Combatant* attacker = Combat_List.back();

		unsigned size = 0;

		if (attacker->Get_Side() == GRANDMA)
			size = logic_components.object_manager->Get_Size_Grandma_Soldier_List();

		else if (attacker->Get_Side() == KIDS)
			size = logic_components.object_manager->Get_Size_Kid_Soldier_List();

		// Loops through the list
		for (unsigned i = 0; i < size; ++i)
		{
			Soldier* Check_Collision = nullptr;

			if (attacker->Get_Side() == GRANDMA)
				Check_Collision = logic_components.object_manager->Get_Grandma_Soldier(i);

			else if (attacker->Get_Side() == KIDS)
				Check_Collision = logic_components.object_manager->Get_Kid_Soldier(i);

			// checks if same side, not same object
			if (Check_Collision->Get_ID() != attacker->Get_ID())
			{
				// if the two objects collide within 1/8 of the current combat's range
				if (Collision_Circle_w_Circle(*attacker, attacker->Get_Radius() / 8, *Check_Collision, check_range))
				{
					/* this segment of code makes units spread out in a non circular manner*/
					Spread_Objects(attacker, Check_Collision);


					attacker->Set_Speed_Check_Flag(0); //to let units move back to the path after combat
				}
			}
		}

		// Check if unit is ready to attack
		if (attacker->Cooldown_Is_Ready() )
		{
			UNIT_TYPES attacker_type = attacker->Get_Unit_Type();
			UNIT_TYPES proj_type;
			//Checks the attacker's type and spawns the correct projectile
			switch (attacker_type)
			{
			case G_S_SHOOTER:
				proj_type = G_P_SHOOTER;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_SHOOTER_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_S_TANK:
				proj_type = P_MELEE;
				break;
			case G_S_SABOTEUR:
				proj_type = G_P_SABOTEUR;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_SABOTEUR_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_S_ATTACKSPEEDUP:
				proj_type = G_P_ATTACKSPEEDUP;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_ATTACKSPEEDUP_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_S_HEALER:
				proj_type = G_P_HEAL;
				break;
			case G_S_SLOW:
				proj_type = G_P_SLOW;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_SLOW_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_S_STUN:
				proj_type = G_P_STUN;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_STUN_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_T_SHOOTING:
				proj_type = G_P_SHOOTER;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_OVEN_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_T_SWING:
				proj_type = GT_P_AOE;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_DENTURES_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_T_SLOW:
				proj_type = GT_P_SLOW;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_PUPPIES_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_T_STUN:
				proj_type = GT_P_STUN;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_CAKE_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case G_T_POISON:
				proj_type = GT_P_POISON;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_VEGGIES_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_S_SHOOTER:
				proj_type = K_P_SHOOTER;
				system_components.audio_manager->Play_Sound(SFX_KID_SHOOTER_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_S_TANK:
			case K_S_ATTACKSPEEDUP:
				proj_type = K_P_ATTACKSPEEDUP;
				system_components.audio_manager->Play_Sound(SFX_KID_ATTACKSPEEDUP_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_S_BIGBOB:
				proj_type = K_P_BIGBOB;
				system_components.audio_manager->Play_Sound(SFX_KID_BIGBOB_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_S_SABOTEUR:
				proj_type = K_P_SABOTEUR;
				system_components.audio_manager->Play_Sound(SFX_KID_SABOTEUR_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_S_HEALER:
				proj_type = K_P_HEAL;
				break;
			case K_S_SLOW:
				proj_type = K_P_SLOW;
				break;
			case K_S_STUN:
				proj_type = K_P_STUN;
				system_components.audio_manager->Play_Sound(SFX_GRANDMA_STUN_ATTACK_1, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_T_SHOOTING:
				proj_type = KT_P_SHOOTER;
				system_components.audio_manager->Play_Sound(SFX_KID_SLINGSHOT_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_T_SWING:
				proj_type = KT_P_AOE;
				system_components.audio_manager->Play_Sound(SFX_KID_PILLOW_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_T_SLOW:
				proj_type = KT_P_SLOW;
				system_components.audio_manager->Play_Sound(SFX_KID_MUD_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_T_POISON:
				proj_type = KT_P_POISON;
				system_components.audio_manager->Play_Sound(SFX_KID_WHOOPEE_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			case K_T_STUN:
				proj_type = KT_P_STUN;
				system_components.audio_manager->Play_Sound(SFX_KID_CAR_ATTACK, attacker->Get_Pos().x, attacker->Get_Pos().y);
				break;
			default:
				proj_type = G_P_SHOOTER;
				break;
			}

			// Spawns projectile for as many targets it has.
			while (attacker->Get_Target_List_Size())
			{
				// Spawns a projectile
				Spawn_Projectile(
					proj_type,
					attacker->Get_Pos().x,
					attacker->Get_Pos().y,
					attacker->Get_Attack_Power(),
					*attacker->Get_Target()
				);

				attacker->Remove_Target();
			}

			// Resets the attacker's cooldown to 0s
			attacker->Reset_Cooldown();
		}

		// Final check to remove all attackers in the list
		else while (attacker->Get_Target_List_Size())
			attacker->Remove_Target();

		// Removes any buff on soldiers
		Soldier * remove_buff = dynamic_cast<Soldier*>(attacker);
		if (remove_buff)
		{
			if (remove_buff->Get_is_Buffed())
			{
				Attack_Normal(*remove_buff);
			}
		}

		Combat_List.pop_back();
	}
}

/******************************************************************************/
/*!
	Damages Combatant's health
*/
/******************************************************************************/
void Damage(Combatant &Target, int damage)
{
	int Health = Target.Get_Health();
	// Damages the target's health from the attacker's attack power
	Target.Set_Health(Health - damage);
	logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_HIT_EFFECT, Target.Get_x(), Target.Get_y(), 0, 0);
}

/******************************************************************************/
/*!
Stuns enemy soldiers
*/
/******************************************************************************/
void Stunned(Soldier &Target)
{
	if (&Target) {
		Target.Set_is_Stunned(true);
		//Starts the stun timer
		//Target.Set_Stun_Start_Time();
	}
	return;
}

/******************************************************************************/
/*!
Removes the stun status from soldiers
*/
/******************************************************************************/
void Recover_From_Stun(Soldier & unit)
{
	//Checks if the stun timer has past 1 second
	if (unit.Get_Stun_Recovery_Time() >= 2.5)
	{
		//Changes soldier back to it's orignal state
		unit.Set_is_Stunned(false);
		unit.Set_Stun_Recovery_Time(0.0);
	}

	else
		Advance_Stun_Cooldown(unit); //Continues the stun timer
}

/******************************************************************************/
/*!
Advances the unit's cooldown if it is not ready to attack
*/
/******************************************************************************/
void Advance_Stun_Cooldown(Soldier & unit)
{
	//// Gets the time elapsed from when it last attacked to the current time in seconds
	//double time_elapsed = AEGetTime(nullptr) - unit.Get_Stun_Start_Time();
	// Sets the attack cooldown to that time
	unit.Set_Stun_Recovery_Time(system_components.framerate_manager->Get_Game_Time());
}

/******************************************************************************/
/*!
Poisons enemy soldiers
*/
/******************************************************************************/
void Poisoned(Soldier &Target)
{
	if (&Target) {
		if (!(Target.Get_is_Poisoned()))
		{
			Target.Set_is_Poisoned(true);
			//Starts the stun timer
			Target.Set_Poison_Start_Time();

			system_components.audio_manager->Play_Sound(SFX_ATTACK_POISON, Target.Get_Pos().x, Target.Get_Pos().y);
		}

	}
	return;
}

/******************************************************************************/
/*!
Removes the poison status from soldiers
*/
/******************************************************************************/
void Recover_From_Poison(Soldier & unit)
{
	//Checks if the stun timer has past 1 second
	if (unit.Get_Poison_Recovery_Time() >= 5.0)
	{
		//Changes soldier back to it's orignal state
		unit.Set_is_Poisoned(false);
		unit.Set_Poison_Start_Time();
		unit.Set_Poison_Flag(0);
	}
	else
		Advance_Poison_Cooldown(unit); //Continues the stun timer
}

/******************************************************************************/
/*!
Advances the unit's cooldown if poison timer is not over
*/
/******************************************************************************/
void Advance_Poison_Cooldown(Soldier & unit)
{
	enum POISON_FLAG
	{
		POISON1 = 1,
		POISON2 = 2,
		POISON3 = 4,
		POISON4 = 8
	};

	// Gets the time elapsed from when it last attacked to the current time in seconds

	if (unit.Get_Poison_Recovery_Time() > 1.0f && !(unit.Get_Poison_Flag() & POISON1))
	{
		Damage(unit, 1);
		unit.Set_Poison_Flag(unit.Get_Poison_Flag() + POISON1);
	}
	if (unit.Get_Poison_Recovery_Time() > 2.0f && !(unit.Get_Poison_Flag() & POISON2))
	{
		Damage(unit, 2);
		unit.Set_Poison_Flag(unit.Get_Poison_Flag() + POISON2);
	}
	if (unit.Get_Poison_Recovery_Time() > 3.0f && !(unit.Get_Poison_Flag() & POISON3))
	{
		Damage(unit, 3);
		unit.Set_Poison_Flag(unit.Get_Poison_Flag() + POISON3);
	}
	if (unit.Get_Poison_Recovery_Time() > 4.0f && !(unit.Get_Poison_Flag() & POISON4))
	{
		Damage(unit, 4);
		unit.Set_Poison_Flag(unit.Get_Poison_Flag() + POISON4);
	}
	// Sets the attack cooldown to that time
	unit.Set_Poison_Recovery_Time(system_components.framerate_manager->Get_Game_Time());
}

/******************************************************************************/
/*!
Slows enemy soldiers
*/
/******************************************************************************/
void Slowed(Soldier &Target)
{
	if (&Target) {
		if (!(Target.Get_is_Slowed()))
		{
			Target.Set_is_Slowed(true);
			//Starts the stun timer
			Target.Set_Slow_Start_Time();
			Target.Set_Speed(Target.Get_Speed() * 0.5f);

			system_components.audio_manager->Play_Sound(SFX_ATTACK_SLOW, Target.Get_Pos().x, Target.Get_Pos().y);
		}

	}
	return;
}

/******************************************************************************/
/*!
Removes the slow status from soldiers
*/
/******************************************************************************/
void Recover_From_Slow(Soldier & unit)
{
	//Checks if the stun timer has past 1 second
	if (unit.Get_Slow_Recovery_Time() >= 3.0)
	{
		//Changes soldier back to it's orignal state
		unit.Set_is_Slowed(false);
		unit.Set_Slow_Start_Time();
		unit.Set_Speed(unit.Get_Speed() * 2.0f);
	}
	else
		Advance_Slow_Cooldown(unit); //Continues the stun timer
}

/******************************************************************************/
/*!
Advances the unit's cooldown if it is not ready to attack
*/
/******************************************************************************/
void Advance_Slow_Cooldown(Soldier & unit)
{
	// Sets the attack cooldown to that time
	unit.Set_Slow_Recovery_Time(system_components.framerate_manager->Get_Game_Time());
}

/******************************************************************************/
/*!
Increases ally soldiers' attack
*/
/******************************************************************************/
void Attack_Up(Soldier &Target)
{
	if (&Target) {
		Target.Set_is_Buffed(true);
		//Checks if the target is a healer type
		if(Target.Get_Unit_Type() == G_S_HEALER || Target.Get_Unit_Type() == K_S_HEALER)
			Target.Set_Attack_Power(Target.Get_Attack_Power() - 3);
		else
			Target.Set_Attack_Power(Target.Get_Attack_Power() + 3);
	}
	return;
}

/******************************************************************************/
/*!
Removes attack buff from soldiers
*/
/******************************************************************************/
void Attack_Normal(Soldier & unit)
{
	if (&unit) {
		unit.Set_is_Buffed(false);
		// Checks if the attacker is a healer type 
		if (unit.Get_Unit_Type() == G_S_HEALER || unit.Get_Unit_Type() == K_S_HEALER)
			unit.Set_Attack_Power(unit.Get_Attack_Power() + 3);
		else
			unit.Set_Attack_Power(unit.Get_Attack_Power() - 3);
	}
	return;
}
