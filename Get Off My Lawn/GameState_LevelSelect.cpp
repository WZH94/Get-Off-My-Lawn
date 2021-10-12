/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_LevelSelect.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       14/02/18
\brief

This file contains the implementation for functions used in the Level Select
gamestate.
Functions include:
GameStateLevelSelectLoad
GameStateLevelSelectInit
GameStateLevelSelectUpdate
GameStateLevelSelectDraw
GameStateLevelSelectFree
GameStateLevelSelectUnload

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_LevelSelect.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "Input.h"

// creating font

/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectLoad(void)
{
	// Spawns background
	Spawn_Object(LEVEL1_BACKGROUND, 0.0f, 0.0f);			// spawns background image

	// Spawns level selection buttons
	logic_components.level_data->Spawn_Level_Selection_Buttons();

	Spawn_Object(BACK_BUTTON, 550.0f, 250.0f);			// spawns back button

	Spawn_Object(SHOP_BUTTON, 0.0f, -250.0f);			// spawns shop

	system_components.audio_manager->Stream_Music(MUSIC_MAIN_MENU); //starts music
}

/******************************************************************************/
/*!
	"Initialize" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUpdate(void)
{
	logic_components.object_manager->Update_Objects();
	Input_Handle_Level_Selection();

	// Keyboard shortcuts for various levels / shops
	if (AEInputCheckReleased(AEVK_BACK))
	{
		std::cout << "Going to player select" << std::endl;
		gAEGameStateNext = GS_LOADPLAYER;
	}


	if (AEInputCheckTriggered(AEVK_1))
	{
		std::cout << "Loading level 1" << std::endl;
		gAEGameStateNext = GS_LEVEL_1;
	}

	if (AEInputCheckTriggered(AEVK_2))
	{
		std::cout << "Loading level 2" << std::endl;
		gAEGameStateNext = GS_LEVEL_2;
	}

	if (AEInputCheckTriggered(AEVK_3))
	{
		std::cout << "Loading level 3" << std::endl;
		gAEGameStateNext = GS_LEVEL_3;
	}

	if (AEInputCheckTriggered(AEVK_4))
	{
		std::cout << "Loading level 4" << std::endl;
		gAEGameStateNext = GS_LEVEL_4;
	}

	if (AEInputCheckTriggered(AEVK_5))
	{
		std::cout << "Loading level 5" << std::endl;
		gAEGameStateNext = GS_LEVEL_5;
	}

	if (AEInputCheckTriggered(AEVK_6))
	{
		std::cout << "Loading level 6" << std::endl;
		gAEGameStateNext = GS_LEVEL_6;
	}

	if (AEInputCheckTriggered(AEVK_7))
	{
		std::cout << "Loading level 7" << std::endl;
		gAEGameStateNext = GS_LEVEL_7;
	}

	if (AEInputCheckTriggered(AEVK_8))
	{
		std::cout << "Loading level 8" << std::endl;
		gAEGameStateNext = GS_LEVEL_8;
	}

	if (AEInputCheckTriggered(AEVK_9))
	{
		std::cout << "Loading level 9" << std::endl;
		gAEGameStateNext = GS_LEVEL_9;
	}

	if (AEInputCheckTriggered(AEVK_0))
	{
		std::cout << "Loading level 10" << std::endl;
		gAEGameStateNext = GS_LEVEL_10;
	}
	
	if (AEInputCheckTriggered(AEVK_SPACE))
	{
		std::cout << "Loading level 0" << std::endl;
		gAEGameStateNext = GS_LEVEL_0;
	}

	if (AEInputCheckTriggered(AEVK_S))
	{
		std::cout << "Entering the Shop" << std::endl;
		gAEGameStateNext = GS_SHOP;
	}

	// fades game, pauses music when switching gamestates
	if (gAEGameStateNext >= GS_LEVEL_0 && gAEGameStateNext <= GS_LEVEL_10)
	{
		system_components.audio_manager->Initiate_Fade_Music(MUSIC_MAIN_MENU, false);
		logic_components.pause_state_manager->Set_Pause(PAUSE_FADE);
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateLevelSelectUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}