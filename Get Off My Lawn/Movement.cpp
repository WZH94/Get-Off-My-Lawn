/******************************************************************************/
/*!
\game	Get Off My Lawn!
\file   Movement.cpp
\author Tan Zhi Quan (90%)		 | Zachary Sng Zhi Ren (10%)
\par    email: zhiquan.tan\@digipen.edu | z.sng\@digipen.edu	
\par    DigiPen login: zhiquan.tan | zhihao.wong
\par    Course: GAM150
\date	
\brief
This file contains the implementation for movement functions of GameObjects
that can move.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Movement.h"			// Function declarations
#include "Path.h"				// Pathing data
#include "CombatSystem.h"		// Combat functions
#include "Collision.h"			// checks collision
#include "Soldier.h"			// Soldier class
#include "Projectiles.h"		// Projectile class
#include "ObjectList.h"			// Object enums
#include "GameStateList.h"		// Game over state
#include "LogicComponents.h"	
#include "SystemComponents.h"	
#include "Particle.h"

#define GRAVITY 100.0f

/******************************************************************************/
/*!
Moves all objects that have been added to the movement list
*/
/******************************************************************************/
void Move_Objects()
{
	// loops until the list is empty
	while (!Movement_List.empty())
	{
		// moves the last object in the list
		Move_Object_To_Node(*Movement_List.back());
		// removes the moved object from the list
		Movement_List.pop_back();
	}
}

/******************************************************************************/
/*!
Moves a projectile towards its target
*/
/******************************************************************************/
void Move_Projectile(Projectile &projectile, Combatant &combatant)
{
	// stores target and projectile's position
	AEVec2 target_pos = { combatant.Get_x(), combatant.Get_y() };
	AEVec2 proj_pos = { projectile.Get_x(),projectile.Get_y()};
	// calculates speed of projectile
	float speed = projectile.Get_Speed() * system_components.framerate_manager->Get_Game_Time();
	float time_taken = 1.0f;
	AEVec2 result_speed = { speed, speed };

	//magnitude of displacement, sets to positive
	float x_displacement = ((proj_pos.x - target_pos.x) > 0) ? (proj_pos.x - target_pos.x) : (target_pos.x - proj_pos.x);
	float y_displacement = ((proj_pos.y - target_pos.y) > 0) ? (proj_pos.y - target_pos.y) : (target_pos.y - proj_pos.y);
	AEVec2 displacement_from_combatant = { x_displacement, y_displacement };

	// if displacement aren't the same, and neither are 0
	if (displacement_from_combatant.x != displacement_from_combatant.y && displacement_from_combatant.y && displacement_from_combatant.x)
	{
		// sets speed of the shorter side to pace with the longer side, such that the object will move in an even manner
		if (displacement_from_combatant.x > displacement_from_combatant.y)
		{
			time_taken = displacement_from_combatant.x / speed;
			result_speed.y = displacement_from_combatant.y / time_taken;
		}

		else if (displacement_from_combatant.y > displacement_from_combatant.x)
		{
			time_taken = displacement_from_combatant.y / speed;
			result_speed.x = displacement_from_combatant.x / time_taken;
		}
	}

	// following code sets direction or sets to 0 if there is no difference in x / y coordinates
	if (proj_pos.x > target_pos.x)
	{
		result_speed.x *= -1;
		projectile.Set_x_Speed(result_speed.x);
	}
	else if (proj_pos.x < target_pos.x)
		projectile.Set_x_Speed(result_speed.x);

	else if (proj_pos.x == target_pos.x)
		projectile.Set_x_Speed(0);

	if (proj_pos.y > target_pos.y)
	{
		result_speed.y *= -1;
		projectile.Set_y_Speed(result_speed.y);
	}
	else if (proj_pos.y < target_pos.y)
		projectile.Set_y_Speed(result_speed.y);

	else if (proj_pos.y == target_pos.y)
		projectile.Set_y_Speed(0);

	// Moves the projectile to it's new position after speed
	projectile.Set_x(projectile.Get_x_Speed());
	projectile.Set_y(projectile.Get_y_Speed());
}

///******************************************************************************/
///*!
//Moves a particle
//*/
///******************************************************************************/
void Move_Particle(Particle & particle)
{
	// Stores the particles position, calculates velocity, sets the new position
	AEVec2 particle_pos = { particle.Get_x(),particle.Get_y() };
	float X_speed = particle.Get_x_Speed() * system_components.framerate_manager->Get_Game_Time();
	float Y_speed = particle.Get_y_Speed() * system_components.framerate_manager->Get_Game_Time();
	particle.Set_x(X_speed);
	particle.Set_y(Y_speed);
}

//Moves particle with gravity acting on it
void Move_Particle_With_Gravity(Particle & particle)
{
	// Stores the particles position, calculates velocity with gravity, sets the new position
	AEVec2 particle_pos = { particle.Get_x(),particle.Get_y() };
	float X_speed = particle.Get_x_Speed() * system_components.framerate_manager->Get_Game_Time();
	float Y_speed = (particle.Get_y_Speed() - GRAVITY) * system_components.framerate_manager->Get_Game_Time();
	particle.Set_x(X_speed);
	particle.Set_y(Y_speed);
}

/******************************************************************************/
/*!
Sets the speed for a Soldier to move towards a movement node at an even manner
*/
/******************************************************************************/
void Set_Speed(Soldier &object, Path node)
{
	// stores soldier and movement node's position
	AEVec2 node_pos = { node.Get_x(), node.Get_y() };
	AEVec2 object_pos = { object.Get_x(),object.Get_y() };
	float speed = object.Get_Speed();
	float time_taken = 1.0f;
	AEVec2 result_speed = { speed, speed };

	//magnitude of displacement, sets to positive
	float x_displacement = ((node_pos.x - object_pos.x) > 0) ? (node_pos.x - object_pos.x) : (object_pos.x - node_pos.x);
	float y_displacement = ((node_pos.y - object_pos.y) > 0) ? (node_pos.y - object_pos.y) : (object_pos.y - node_pos.y);
	AEVec2 displacement_from_node = { x_displacement, y_displacement };

	// if displacement aren't the same, and neither are 0
	if (displacement_from_node.x != displacement_from_node.y && displacement_from_node.y && displacement_from_node.x)
	{
		// sets speed of the shorter side to pace with the longer side
		if (displacement_from_node.x > displacement_from_node.y)
		{
			time_taken = displacement_from_node.x / speed;
			result_speed.y = displacement_from_node.y / time_taken;
		}

		else if (displacement_from_node.y > displacement_from_node.x)
		{
			time_taken = displacement_from_node.y / speed;
			result_speed.x = displacement_from_node.x / time_taken;
		}
	}

	// following code sets direction or sets to 0 if there is no different in x / y coordinates
	if (object_pos.x > node_pos.x)
	{
		result_speed.x *= -1;
		object.Set_x_Speed(result_speed.x);
	}
	else if (object_pos.x < node_pos.x)
		object.Set_x_Speed(result_speed.x);

	else if (object_pos.x == node_pos.x)
		object.Set_x_Speed(0);

	if (object_pos.y > node_pos.y)
	{
		result_speed.y *= -1;
		object.Set_y_Speed(result_speed.y);
	}
	else if (object_pos.y < node_pos.y)
		object.Set_y_Speed(result_speed.y);

	else if (object_pos.y == node_pos.y)
		object.Set_y_Speed(0);
}

//Moves a soldier to the next movement node in the path
void Move_Object_To_Node(Soldier &object)
{
	// check for collision with the node
	bool collision = Collision_Pt_w_Node(object, *object.Get_Move_Target());

	if (collision) //if there's collision, reset the changed variables, plot course for new node
	{
		// resets changed variables
		object.Set_Speed_Check_Flag(0); // speed check flag ensures that the object does not recalculate when there's no need, aka no change in direction
		object.Set_x_Speed(object.Get_Speed() * system_components.framerate_manager->Get_Game_Time());
		object.Set_y_Speed(object.Get_Speed() * system_components.framerate_manager->Get_Game_Time());

		unsigned current_node = object.Get_Move_Target()->Get_Node_Placement();
		unsigned size = logic_components.object_manager->Get_Size_Path_List();

		//if object hits opposing base, disappears
		if ((object.Get_Side() == GRANDMA && current_node == size - 1))	
		{
			//Damages Base
			logic_components.level_data->players->Damage_Kid_Base(logic_components.level_data->Get_Level_Number());
			logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SMOKE, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y, 100.0f, 0.3f);
			logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_RUBBLE, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y + 100.0f, 100.0f, 1.0f);
			logic_components.object_manager->Queue_Kill_Object(&object);
			return;
		}
		if ((object.Get_Side() == KIDS && current_node == 0))
		{
			//Checks if Boss has reached the base
			if (object.Get_Unit_Type() == K_S_BIGBOB)
			{
				// Sets Next Game State to Game Over
				system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
				logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
				gAEGameStateNext = GS_GAMEOVER;
			}
			else
			{
				//Damages Base
				logic_components.level_data->players->Damage_Grandma_Base();
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_SMOKE, 0.0f, 0.0f, 100.0f, 0.3f);
				logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_RUBBLE, 0.0f, 100.0f, 100.0f, 1.0f);
				logic_components.object_manager->Queue_Kill_Object(&object);
			}
			return;
		}

		// sets to move towards the next movement node
		if (object.Get_Side() == GRANDMA && current_node < size - 1)
		{
			Path* checkNode = nullptr;

			do
			{
				++current_node; //grandmas start from 0th node and move to the last node
				checkNode = logic_components.object_manager->Get_Path(current_node);

			} while (checkNode->Get_Skip_Node() == true && current_node < size - 1);

			object.Set_Move_Target(checkNode);
		}

		// sets to move towards the next movement node
		else if (object.Get_Side() == KIDS && current_node > 0)
		{
			Path* checkNode = nullptr;

			do
			{
				--current_node; //kids move opposite to grandmas
				checkNode = logic_components.object_manager->Get_Path(current_node);

			} while (checkNode->Get_Skip_Node() == true && current_node > 0);

			object.Set_Move_Target(checkNode);
		}

	}
	else //if no collision, move (via changing coordinates of object)
	{
		if (object.Get_Speed_Check_Flag() == 0)
		{
			Set_Speed(object, *object.Get_Move_Target());
			object.Set_Speed_Check_Flag(1);
		}
		//Gets the current velocity in x, y direction, adds that to obj x and y
		object.Set_x(object.Get_x_Speed() * system_components.framerate_manager->Get_Game_Time());
		object.Set_y(object.Get_y_Speed() * system_components.framerate_manager->Get_Game_Time());
	}

	//Removes attack buff
	if (object.Get_is_Buffed())
	{
		Attack_Normal(object);
	}
}

//Makes units spread out instead of stacking on one another
void Spread_Objects(Combatant* Attacker, Soldier* Collidee)
{
	UNIT_TYPES Attacker_Type = Attacker->Get_Unit_Type();
	UNIT_TYPES Collidee_Type = Collidee->Get_Unit_Type();
	
	// saboteurs don't engage in combat with other soldiers, so this prevents normal soldiers from pushing saboteurs
	switch (Attacker_Type)
	{
	case G_S_SABOTEUR:
		if (Collidee_Type != G_S_SABOTEUR)
			return;
		break;
	case K_S_SABOTEUR:
		if (Collidee_Type != K_S_SABOTEUR)
			return;
		break;
	default:
		break;
	}

	// shifts unit depending on relative position
	if (Attacker->Get_y() >= Collidee->Get_y())
		Attacker->Set_y(+0.25f);
	else Attacker->Set_y(-0.25f);

	if (Attacker->Get_x() >= Collidee->Get_x())
		Attacker->Set_x(+0.25f);
	else Attacker->Set_x(-0.25f);

}

//makes units spread out, moving in a circle
void Spread_Objects_Circle(Combatant* Attacker, Soldier* Collidee)
{
	Soldier* Current = (dynamic_cast<Soldier*>(Attacker));
	Soldier* Target = Collidee;
	
	static bool midpoint_flag = false;
	AEVec2 midpoint = Target->Get_Pos();

	//finds the midpoint between the 2 combatants, saves it for all units
	if (midpoint_flag == false)
	{
		midpoint = Find_Midpoint(Current->Get_Pos(), Target->Get_Pos());
		midpoint_flag = true;
	}
	// ASTC => which trig is positive -> A = all, S = sin, T = tan, C = cos
	enum ASTC {
	A = 1,
	S = 2,
	T = 3,
	C = 4
	};

	int quad = 0;
	// Finds where the object is relative to the other
	if (Current->Get_x() > midpoint.x && Current->Get_y() > midpoint.y)
	quad = A;

	else if (Current->Get_x() < midpoint.x && Current->Get_y() > midpoint.y)
	quad = S;

	else if (Current->Get_x() < midpoint.x && Current->Get_y() < midpoint.y)
	quad = T;

	else if (Current->Get_x() > midpoint.x && Current->Get_y() < midpoint.y)
	quad = C;

	// switch case based on what quadrant the unit is in
	switch (quad)
	{
	case A:
		Current->Set_y((float)AECos(Current->Get_Speed() / Current->Get_Range()));
		Current->Set_x((float)AESin(Current->Get_Speed() / Current->Get_Range()));
		break;
	case S:
		Current->Set_y((float)-AECos(Current->Get_Speed() / Current->Get_Range()));
		Current->Set_x((float)AESin(Current->Get_Speed() / Current->Get_Range()));
		break;
	case T:
		Current->Set_y((float)-AECos(Current->Get_Speed() / Current->Get_Range()));
		Current->Set_x((float)-AESin(Current->Get_Speed() / Current->Get_Range()));
		break;
	case C:
		Current->Set_y((float)AECos(Current->Get_Speed() / Current->Get_Range()));
		Current->Set_x((float)-AESin(Current->Get_Speed() / Current->Get_Range()));
		break;
	case 0: // default case to shift units a bit
		if (Current->Get_x() == Target->Get_x() || Current->Get_y() == Target->Get_y())
		{
			Current->Set_y(+0.25f);
			Current->Set_x(+0.25f);
		}
		break;
	}

	//resets flag for the last combatant in list
	if (Combat_List.begin() == Combat_List.end())
		midpoint_flag = false;
}