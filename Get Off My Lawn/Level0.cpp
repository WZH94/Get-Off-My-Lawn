/* Start Header **************************************************************/
/*!
\game	Get Off My Lawn!
\file		Level0.cpp
\author		Tan Zhi Quan (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the level 0
gamestate.

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header ****************************************************************/

#include "Level0.h"				// Function declarations
#include "Input.h"				// Input Handler
#include "ObjectList.h"			// Unit Types
#include "ObjectSpawner.h"		// Spawn_Object
#include "RenderManager.h"		// Print frame rate
#include "Movement.h"			// Move functions
#include "CombatSystem.h"       // Combat functions
#include "SystemComponents.h"
#include "LogicComponents.h"
#include "PlayerData.h"
#include "GameStateList.h"

/******************************************************************************/
/*!
"Load" function of this state
*/
/******************************************************************************/
void Level0_Load()
{
	// Load Level Paths
	// Load Level Movement Nodes
	/******* SET THE PATH HERE *******/
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_TURN);
	Create_Path(UP, PATH_STRAIGHT);
	Create_Path(UP, PATH_TURN);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);
	Create_Path(RIGHT, PATH_STRAIGHT);

	logic_components.object_manager->Set_Rotation(); //rotates tiles

	logic_components.Load_Level_Components(0);

	// Load level Tower Nodes
	/******* SET THE TOWER POSITIONS HERE *******/

	logic_components.level_data->Create_Granny_Tower_Nodes(5, LEFT, GRANDMA, TOWER_NULL);

	logic_components.level_data->Create_Tower_Nodes(8, DOWN, KIDS, K_T_SHOOTING);

	
	

	//Set background colour
	AEGfxSetBackgroundColor(0.0f, 0.4f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);


	/////////////////////////////////////////////////////////
	// Spawn objects that will not change within the level

	// Background of the level
	Spawn_Object(LEVEL1_BACKGROUND, 500.0f, 0.0f);

	// UI Panel of the buttons
	Spawn_Object(UI_PANEL, 0.0f, -SCREEN_HEIGHT / 2 + 75.0f);

	logic_components.level_data->Spawn_Granny_Buttons();
	Spawn_Object(LEVEL_MULTIPLIER, -500.0f, -230.0f);

	Create_Wave_Indicator(logic_components.level_data->Get_Max_Waves());
	//Create_Countdown_Bars();
	Spawn_Object(TUTORIAL_SPEECH_01, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_02, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_03, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_04, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_05, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_06, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_07, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_08, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_09, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_10, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_11, -350.0f, 175.0f);
	Spawn_Object(TUTORIAL_SPEECH_12, -350.0f, 175.0f);
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void Level0_Init()
{
	system_components.audio_manager->Stream_Music(MUSIC_LEVEL);

	logic_components.Initialise_Level_Components();

	// Spawn the bases
	Spawn_Object(G_BASE, 0, 0);
	Spawn_Object(K_BASE, logic_components.level_data->Get_Enemy_Base_Location().x, logic_components.level_data->Get_Enemy_Base_Location().y);
	Spawn_Object(BUTTON_PAUSE, 550.0f, 250.0f);			// spawns pause button
	Spawn_Object(BUTTON_TIME_ADJUST, 470.0f, 250.0f);			// spawns time adjust button
}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void Level0_Update()
{	
	Tutorial(playdata.Get_Stage());

	// Handles keyboard and mouse inputs
	Input_Handle_Tutorial();

	// Updates camera position and zoom levels if there are changes from the input
	logic_components.camera->Update_Camera();

	// Updates the logic of every game object
	logic_components.object_manager->Update_Objects();

	// Increases player's granny Mojo
	logic_components.level_data->players->Granny_Mojo_Earn();

	// Game object action functions
	Move_Objects();
	Initiate_Combat();

	// Kills and frees objects that have died in the game
	logic_components.object_manager->Kill_Objects();

	// Updates the level data
	logic_components.level_data->Update_Level_Data();
}

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void Level0_Draw()
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
void Level0_Free()
{
	logic_components.Free_Level_Components();
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void Level0_Unload()
{
	logic_components.Unload_Level_Components();
}

/******************************************************************************/
/*!
Tutorial handler
*/
/******************************************************************************/
void Tutorial(int stage)
{
	static bool once = false; // spawns enemy once only

	switch (stage)
	{
	case 1:
	{
		// Spawns text bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_01) 
					desc->Set_Alive(true);
		}
		// Moves to next description
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_01)
						desc->Set_Alive(false);
			}
			playdata.Set_Stage(2); // Sets to stage 2 of tutorial
		}
		break;
	}
	case 2:
	{
		// Spawns text bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_02)
					desc->Set_Alive(true);
		}

		// Moves to next description
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_02)
						desc->Set_Alive(false);
			}
			playdata.Set_Stage(3); // Sets to next stage
		}
		break;
	}
	case 3:
	{
		// Spawns text bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_03)
					desc->Set_Alive(true);
		}
	
		// Moves to next description
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_03)
						desc->Set_Alive(false);
			}

			playdata.Set_Stage(4); // Sets to next stage
		}
		break;
	}
	case 4:
	{
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_04)
					desc->Set_Alive(true);
		}
	
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_04)
						desc->Set_Alive(false);
			}
		
			playdata.Set_Stage(5); // Sets to next stage
		}		
		break;
	}
	case 5:
	{

		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_05)
					desc->Set_Alive(true);
		}
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_05)
						desc->Set_Alive(false);
			}
		
			playdata.Set_Stage(6); // Sets to next stage
		}
		break;
	}
	case 6:
	{
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_06)
					desc->Set_Alive(true);
		}
	
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_06)
						desc->Set_Alive(false);
			}
		
			playdata.Set_Stage(7); // Sets to next stage
		}
		break;
	}
	case 7:
	{
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_07)
					desc->Set_Alive(true);
		}
		if (!once)
		{
			Spawn_Object(K_S_SHOOTER, 500.0f, 0.0f);
			once = true;
		}
		if(Tutorial_G_S_Shooter())
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_07)
						desc->Set_Alive(false);
			}
		
			playdata.Set_Stage(8); // Sets to next stage
		}
		break;
	}
	case 8:
	{
		// Spawns text bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_08)
					desc->Set_Alive(true);
		}
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_08)
						desc->Set_Alive(false);
			}
			
			playdata.Set_Stage(9); // Sets to next stage
		}
		break;
	}
	case 9 :
	{
		// Spawns text bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_09)
					desc->Set_Alive(true);
		}
		logic_components.level_data->players->Tutorial_Give_Granny_Mojo(100.0f);
		char tutorial = 0;
		if (Input_Handle_Granny_Tower_Nodes(tutorial)) //checks if the tower has been spawned
		{
			playdata.Set_Stage(10); // Sets to next stage
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_09)
						desc->Set_Alive(false);
			}
		}
		break;
	}
	case 10:
	{
		// Spawns bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_10)
					desc->Set_Alive(true);
		}
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_10)
						desc->Set_Alive(false);
			}
			playdata.Set_Stage(11); // Sets to next stage
		}
		break;
	}
	case 11:
	{
		// Spawns bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_11)
					desc->Set_Alive(true); // Sets to next stage
		}
	
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_11)
						desc->Set_Alive(false);
			}
		
				playdata.Set_Stage(12); // Sets to next stage
		}
		break;
	}
	case 12:
	{
		// Spawns bubble
		for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
		{
			GameObject *desc = logic_components.object_manager->Get_Description(i);
			if (desc)
				if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_12)
					desc->Set_Alive(true);
		}
	
		if (AEInputCheckReleased(AEVK_LBUTTON))
		{
			for (unsigned int i = 0; i < logic_components.object_manager->Get_Size_Description_List(); ++i)
			{
				GameObject *desc = logic_components.object_manager->Get_Description(i);
				if (desc)
					if (desc->Get_Unit_Type() == TUTORIAL_SPEECH_12)
						desc->Set_Alive(false);
			}
			playdata.Set_Tutorial_Completion(true);
			playdata.Set_Stage(1);					// resets tutorial for future runs
			once = false;							// resets tutorial for future runs
		
			playdata.Save_Save_File();
			system_components.audio_manager->Initiate_Fade_Music(MUSIC_LEVEL, false);
			logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
			gAEGameStateNext = GS_LEVEL_1;

		}
		break;
	}
	default:
	{
		gAEGameStateNext = GS_LEVELSELECT;
	}

	}
}