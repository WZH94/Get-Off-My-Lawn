/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   CombatSystem.cpp
\author Sng Zhi Ren Zachary		(90%)  | Tan Zhi Quan (10%)
\par    email: z.sng\@digipen.edu      | zhiquan.tan\@digipen.edu
\par    DigiPen login: z.sng
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation of Combat functions.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

// Forward declaration of classes
typedef class Combatant Combatant;
typedef class Soldier Soldier;

// Handles the combat of units that will be attacking in the current frame.
void Initiate_Combat();

// Damages Combatant's health
void Damage(Combatant &, int damage);

// Stuns enemy soldiers
void Stunned(Soldier &);

// Removes the stun status from soldiers
void Recover_From_Stun(Soldier &);

// Advances the unit's cooldown if it is not ready to attack
void Advance_Stun_Cooldown(Soldier &);

// Poisons enemy soldiers
void Poisoned(Soldier &);

// Removes the poison status from soldiers
void Recover_From_Poison(Soldier &);

// Advances the unit's cooldown if poison timer is not over
void Advance_Poison_Cooldown(Soldier &);

// Slows enemy soldiers
void Slowed(Soldier &);

// Removes the slow status from soldiers
void Recover_From_Slow(Soldier &);

// Advances the unit's cooldown if it is not ready to attack
void Advance_Slow_Cooldown(Soldier &);

// Increases ally soldiers' attack
void Attack_Up(Soldier &);

// Removes attack buff from soldiers
void Attack_Normal(Soldier &);

#endif COMBATSYSTEM_H