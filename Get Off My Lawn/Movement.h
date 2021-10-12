/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Movement.cpp
\author Sng Zhi Ren Zachary		(10%)  | Tan Zhi Quan (90%)
\par    email: z.sng\@digipen.edu      | zhiquan.tan\@digipen.edu
\par    DigiPen login: zhiquan.tan | zhihao.wong
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation for movement functions of GameObjects
that can move.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef MOVEMENT_H
#define MOVEMENT_H

typedef class Soldier Soldier;
typedef class Combatant Combatant;
typedef class Projectile Projectile;
typedef class Path Path;
typedef class Particle Particle;

//Moves all objects that have been added to the movement list
void Move_Objects();

//Moves projectile towards target
void Move_Projectile(Projectile &, Combatant &);

//Moves particle
void Move_Particle(Particle &);

//Moves particle with gravity acting on it
void Move_Particle_With_Gravity(Particle &);

//Moves a soldier to the next movement node in the path
void Move_Object_To_Node(Soldier &);

//Sets the velocity of the soldier depending on where the next movement node is relative to it
void Set_Speed(Soldier &, Path);

//Makes units spread out instead of stacking on one another
void Spread_Objects(Combatant* Attacker, Soldier* Collidee);

//makes units spread out, moving in a circle
void Spread_Objects_Circle(Combatant* Attacker, Soldier* Collidee);

#endif MOVEMENT_H