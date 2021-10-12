/******************************************************************************/
/*!
\file   Level10.cpp
\author Wong Zhihao				(25%)| Ngm Hui Min, Lois		(25%)
Zachary Sng ZhiRen		(25%)| Tan Zhi Quan				(25%)
\par    email: zhihao.wong\@digipen.edu		| lois.ngm\@digipen.edu
z.sng\@digipen.edu			| zhiquan.tan\@digipen.edu
\par    DigiPen login: zhihao.wong			| lois.ngm
z.sng				| zhiquan.tan
\par    Course: GAM150
\date	13/04/18
\brief
This file contains the implementation for level 10 of Get off my Lawn

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Level10.h"			// Function declarations
#include "Input.h"				// Cursor Position
#include "ObjectList.h"			// Unit Types
#include "ObjectSpawner.h"		// Spawn_Object
#include "RenderManager.h"		// Print frame rate
#include "Movement.h"			// Move functions
#include "CombatSystem.h"       // Combat functions
#include "SystemComponents.h"
#include "LogicComponents.h"

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void Level10_Load()
{
	// Load Level Movement Nodes
	/******* SET THE PATH HERE *******/
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_TURN);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_TURN);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_TURN);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_TURN);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_TURN);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_TURN);
	Create_Path(LEFT, PATH_STRAIGHT);
	Create_Path(LEFT, PATH_TURN);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_STRAIGHT);
	Create_Path(DOWN, PATH_TURN);
	Create_Path(LEFT, PATH_STRAIGHT);
	Create_Path(LEFT, PATH_TURN);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_TURN);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_TURN);
	Create_Path(UP, PATH_STRAIGHT);

	logic_components.object_manager->Set_Rotation(); //rotates the turning paths

	logic_components.Load_Level_Components(10); //loads level 10 assets

	// Load level Tower Nodes
	/******* SET THE TOWER POSITIONS HERE *******/

	logic_components.level_data->Create_Granny_Tower_Nodes(1, UP, GRANDMA, TOWER_NULL);
	logic_components.level_data->Create_Granny_Tower_Nodes(1, DOWN, GRANDMA, TOWER_NULL);
	logic_components.level_data->Create_Granny_Tower_Nodes(3, UP, GRANDMA, TOWER_NULL);
	logic_components.level_data->Create_Granny_Tower_Nodes(3, DOWN, GRANDMA, TOWER_NULL);

	logic_components.level_data->Create_Tower_Nodes(7, RIGHT, KIDS, K_T_SWING);
	logic_components.level_data->Create_Tower_Nodes(7, LEFT, KIDS, K_T_SLOW);
	logic_components.level_data->Create_Tower_Nodes(13, RIGHT, KIDS, K_T_SLOW);
	logic_components.level_data->Create_Tower_Nodes(17, UP, KIDS, K_T_STUN);
	logic_components.level_data->Create_Tower_Nodes(29, RIGHT, KIDS, K_T_SHOOTING);
	logic_components.level_data->Create_Tower_Nodes(33, UP, KIDS, K_T_POISON);

	
	

	//Set background colour
	AEGfxSetBackgroundColor(0.0f, 0.4f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	/////////////////////////////////////////////////////////
	// Spawn objects that will not change within the level

	// Background of the level
	Spawn_Object(LEVEL1_BACKGROUND, 500.0f, 0.0f);

	// UI Panel of the buttons
	Spawn_Object(UI_PANEL, 0.0f, -SCREEN_HEIGHT / 2 + 75.0f);
	Spawn_Object(ICON_GRANNY, 450.0f, -205.0f);
	Spawn_Object(HEALTH, 500.0f, -205.0f);
	Spawn_Object(ICON_KID, 450.0f, -255.0f);
	Spawn_Object(HEALTH, 500.0f, -255.0f);

	Spawn_Object(GRANNY_MOJO, -550.0f, -200.0f);

	logic_components.level_data->Spawn_Granny_Buttons();
	Spawn_Object(LEVEL_MULTIPLIER, -510.0f, -245.0f);

	Create_Wave_Indicator(logic_components.level_data->Get_Max_Waves());
	Spawn_Object(BUTTON_PAUSE, 550.0f, 250.0f);			// spawns pause button
	Spawn_Object(BUTTON_TIME_ADJUST, 470.0f, 250.0f);			// spawns time adjust button

}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void Level10_Init()
{
	system_components.audio_manager->Stream_Music(MUSIC_LEVEL); //starts music

	logic_components.Initialise_Level_Components(); // inits level comps

	// Spawn the bases
	Spawn_Object(G_BASE, 0, 0);
	Spawn_Object(K_BASE, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y);

	Create_Wave_Indicator(logic_components.level_data->Get_Max_Waves());
}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void Level10_Update()
{

	Input_Handle_In_Game(); // input functions

	// Updates camera position and zoom levels if there are changes from the input
	logic_components.camera->Update_Camera();

	// Updates the logic of every game object
	logic_components.object_manager->Update_Objects();

	// Increases player's granny mojo
	logic_components.level_data->players->Granny_Mojo_Earn();

	// Game object action functions
	Move_Objects();
	Initiate_Combat();

	// Kills and frees objects that have died in the game
	logic_components.object_manager->Kill_Objects();

	// Updates the level data
	logic_components.level_data->Update_Level_Data();

	if (logic_components.level_data->players->Get_Grandma_Base_HP() == 0)
	{
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_EXPLOSION, 0.0f, 0.0f, 50.0f, 2.0f);
	}

	if (logic_components.level_data->players->Get_Kid_Base_HP() == 0)
	{
		logic_components.object_manager->Activate_Particle_Emitter(PARTICLE_EXPLOSION, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y, 50.0f, 2.0f);
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void Level10_Draw()
{
	// Draws every game object in the game
	logic_components.object_manager->Draw_Objects();
	// Prints out the player's stats
	logic_components.level_data->players->Print_Currency();
}


/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void Level10_Free()
{
	logic_components.Free_Level_Components(); //free all level components
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void Level10_Unload()
{
	logic_components.Unload_Level_Components(); //unloads all level components
}
