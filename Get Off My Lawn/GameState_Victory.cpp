/* Start Header **************************************************************/
/*!
\game		Get Off My Lawn!
\file		GameState_Victory.cpp 
\author		Tan Zhi Quan, zhiquan.tan, (100%)
\par        zhiquan.tan\@digipen.edu
\date       13/04/18
\brief

This file contains the implementation for functions used in the Victory
gamestate.
Functions include:
GameStateVictoryLoad
GameStateVictoryInit
GameStateVictoryUpdate
GameStateVictoryDraw
GameStateVictoryFree
GameStateVictoryUnload
Spawn_Stars

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
All content © 2018 DigiPen (SINGAPORE) Corporation, all rights reserved.
*/
/* End Header ****************************************************************/

#include "GameState_Victory.h" // header files
#include "LogicComponents.h"
#include "SystemComponents.h"
#include "main.h"				// Libraries
#include "GameStateList.h"      // Game states
#include "ObjectSpawner.h"		// Spawns objects
#include "ObjectList.h"			// Unit Types
#include "LevelData.h"			// Enum for all levels
#include "PlayerData.h"			// Access last earned star count


/******************************************************************************/
/*!
	"Load" function of this state
*/
/******************************************************************************/
void GameStateVictoryLoad(void)
{
	// Spawns background
	Spawn_Object(LEVEL1_BACKGROUND, 0.0f, 0.0f);

	// Spawns stars
	Spawn_Stars(playdata.Get_Stars_Earned());
}

/******************************************************************************/
/*!
"Initialize" function of this state
*/
/******************************************************************************/
void GameStateVictoryInit(void)
{}

/******************************************************************************/
/*!
"Update" function of this state
*/
/******************************************************************************/
void GameStateVictoryUpdate(void)
{
	//updates all objects
	logic_components.object_manager->Update_Objects(); 

	//switches to main menu 
	if (AEInputCheckCurr(AEVK_BACK))
	{
		std::cout << "Going to main menu" << std::endl;
		gAEGameStateNext = GS_MAINMENU;
	}

	//switches to level select
	if (AEInputCheckCurr(AEVK_RETURN))
	{
		std::cout << "Going to level select" << std::endl;
		gAEGameStateNext = GS_LEVELSELECT;
	}
}


/******************************************************************************/
/*!
"Draw" function of this state
*/
/******************************************************************************/
void GameStateVictoryDraw(void)
{
	logic_components.object_manager->Draw_Objects(); //renders objects

	char strBuffer[1024]; //buffer to contain string
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	//prints string
	sprintf_s(strBuffer, "VICTORY");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)250, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK BACKSPACE TO RETURN TO MAIN MENU");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)200, (f32)0, (f32)0, (f32)1);

	sprintf_s(strBuffer, "CLICK ENTER TO RETURN TO LEVEL SELECT");
	AEGfxPrint(system_components.font_manager_->Get_Font(F_TEST_MAIN_MENU), (s8*)strBuffer, (s32)-300, (s32)150, (f32)0, (f32)0, (f32)1);

}

/******************************************************************************/
/*!
"Free" function of this state
*/
/******************************************************************************/
void GameStateVictoryFree(void)
{
}

/******************************************************************************/
/*!
"Unload" function of this state
*/
/******************************************************************************/
void GameStateVictoryUnload(void)
{
	logic_components.object_manager->Clear_Object_Manager(); // clears the list of objects
}

/******************************************************************************/
/*!
Spawns Stars depending on how many were earned in the level
*/
/******************************************************************************/
void Spawn_Stars(int stars_earned)
{
	switch (stars_earned)
	{
	case 3:
		Spawn_Object(VICTORY_STAR, 0.0f, 50.0f); // lack of break is intended, spawns all 3 stars
	case 2:
		Spawn_Object(VICTORY_STAR, -50.0f, 0.0f); // spawns two stars
		Spawn_Object(VICTORY_STAR, 50.0f, 0.0f);	
		break;
	case 1:
		Spawn_Object(VICTORY_STAR, 0.0f, 50.0f); //spawns 1 star
		break;
	}
}