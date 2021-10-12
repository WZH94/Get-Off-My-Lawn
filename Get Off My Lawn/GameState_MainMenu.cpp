/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_MainMenu.cpp
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Main Menu
gamestate.
Functions include:
GameStateMainMenuLoad
GameStateMainMenuInit
GameStateMainMenuUpdate
GameStateMainMenuDraw
GameStateMainMenuFree
GameStateMainMenuUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/


#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameState_MainMenu.h"
#include "GameStateList.h"
#include "stdio.h"
#include "ObjectList.h"
#include "ObjectSpawner.h"
#include "Input.h"

std::vector <Combatant*> Combat_List; // externed list containing units in combat
std::vector <Soldier*> Movement_List; // externed list containing units moving

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateMainMenuLoad(void)
{
	AEGfxSetBackgroundColor((f32)1, (f32)1, (f32)1);

	Spawn_Object(MAIN_MENU_BACKGROUND, 0.0f, 0.0f); // spawns main menu background image
	Spawn_Object(START_BUTTON, -450.0f, -220.0f);   // spawns start button
	Spawn_Object(OPTIONS_BUTTON, -150.0f, -220.0f); // spawns options button
	Spawn_Object(CREDITS_BUTTON, 150.0f, -220.0f);  // spawns quit button
	Spawn_Object(QUIT_BUTTON, 450.0f, -220.0f);     // spawns quit button
	Spawn_Object(GAME_STAT, 0.0f, 0.0f);			// spawns game
	Spawn_Object(BUTTON_YES, -150.0f, -150.0f);		// spawns yes button
	Spawn_Object(BUTTON_NO, 150.0f, -150.0f);		// spawns no button

	system_components.audio_manager->Stream_Music(MUSIC_MAIN_MENU); //starts music
}

/******************************************************************************/
/*!
	"Initialize" function of this state
*/
/******************************************************************************/
void GameStateMainMenuInit(void)
{
	// loads all buttons
	for (unsigned i = 0; i < logic_components.object_manager->Get_Size_General_List(); ++i)
	{
		GameObject * all_type_button = logic_components.object_manager->Get_General(i);
		if (all_type_button->Get_Unit_Type() == GAME_STAT)
		{
			all_type_button->Set_Texture_Change(0.75f);
			break;
		}
	}
}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUpdate(void)
{
	logic_components.object_manager->Update_Objects(); 	// updates all objects
	Input_Handle_Main_Menu();							// handles input for main menu


}

/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateMainMenuDraw(void)
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	logic_components.object_manager->Draw_Objects(); //renders objects
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateMainMenuFree(void)
{

}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateMainMenuUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}